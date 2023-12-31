/*
 * RangedForContainer.hpp
 *
 *  Created on: 2019/02/25
 *      Author: SONIK
 */

#ifndef SONIKSTRING_RANGEDFORCONTAINER_HPP_
#define SONIKSTRING_RANGEDFORCONTAINER_HPP_

//拡張式配列の機能を提供します。
//配列サイズは拡張方向のみで、縮小はしません。
//つまりpushbackにより１つ拡張された場合は拡張されたままになります。

#include <stdint.h>
#include <new>
#include <string>

namespace SonikLib
{
	template <class T>
	class SonikVariableArrayContainer
	{
	private:
		uint8_t* AllocAreaPtr;
		uint32_t AllocCount;
		uint32_t MaxCnt;

	public:
		SonikVariableArrayContainer(uint32_t ElemCnt = 100)
		:AllocCount(0)
		,MaxCnt(ElemCnt)
		{
			if(MaxCnt >= UINT32_MAX)
			{
				--MaxCnt;
			};

			try
			{
				AllocAreaPtr = new uint8_t[ sizeof(T) * ElemCnt ];

			}catch(std::bad_alloc& e)
			{
				//メモリの確保に失敗。
				delete[] AllocAreaPtr;
				throw std::bad_alloc(e);
			};

		};

		~SonikVariableArrayContainer(void)
		{
			T* item = reinterpret_cast<T*>(AllocAreaPtr);
			for(uint32_t i=0; i < AllocCount; ++i)
			{
				item[i].~T();
			};

			delete[] AllocAreaPtr;
		};

		T* begin(void)
		{
			return &reinterpret_cast<T*>(AllocAreaPtr)[0];
		};

		T* end(void)
		{
			return &reinterpret_cast<T*>(AllocAreaPtr)[AllocCount];
		};

		T& operator [](uint32_t ArrayPoint)
		{
			return reinterpret_cast<T*>(AllocAreaPtr)[ArrayPoint];
		};

		bool PushBack(T& PushItem)
		{
			if( MaxCnt < AllocCount )
			{
				uint8_t* pTmpArea = nullptr;
				uint8_t TmpCount  = AllocCount << 1;
				uint8_t* TmpControl = 0;
				T* tmpItem = nullptr;

				pTmpArea = new(std::nothrow) uint8_t[ (sizeof(T) * AllocCount ) ];
				if( pTmpArea == nullptr )
				{
					return false;
				};

				TmpControl = pTmpArea;

				uint32_t pTmpIndex = AllocCount;
				T* alp = reinterpret_cast<T*>(AllocAreaPtr);
				for( uint32_t i=0; i < pTmpIndex; ++i)
				{
					tmpItem = new(TmpControl) T;
					(*tmpItem) = alp[i];

					TmpControl += sizeof(T);
				};

				delete[] AllocAreaPtr;
				AllocAreaPtr = pTmpArea;
				MaxCnt = TmpCount;
			};

			T* pTmpObj = new(&reinterpret_cast<T*>(AllocAreaPtr)[AllocCount]) T;

			(*pTmpObj) = PushItem;

			++AllocCount;
			return true;
		};

		bool PopBack(void)
		{
			if( AllocCount == 0 )
			{
				return true;
			};

			reinterpret_cast<T*>(AllocAreaPtr)[ (AllocCount -1) ].~T();

			--AllocCount;
			return true;
		};

		void Clear(void)
		{
			if( AllocCount == 0 )
			{
				return;
			};

			for( T& item : (*this) )
			{
				item.~T();
			};

			memset(AllocAreaPtr, 0, (sizeof(T) * MaxCnt));
			AllocCount = 0;
			return;
		};
	};

}; //end namespace SonikLib



#endif /* SONIKSTRING_RANGEDFORCONTAINER_HPP_ */
