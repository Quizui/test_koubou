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
#include "../SmartPointer/SonikSmartPointer.hpp"
#include "../SonikCAS/SonikAtomicLock.h"

#include <stdint.h>
#include <new>
#include <algorithm>

namespace SonikLib
{
	namespace Container
	{
		template <class T>
		class SonikVariableArrayContainer
		{
		public:
			//コンテナオブジェクト操作用のイテレータ
			//ローカルでの使用を想定。イテレータ取得後にオブジェクトの配列がreserveされたり操作が入ると無効(たんぐリング)が発生します。
			//これは一般的にあstdと同様の条件です。
			class VACIterator
			{
			private:
				T* TopPointer;
				T* ControlPointer;

			public:
				inline VACIterator(T* _pointer_ = nullptr) noexcept
					:TopPointer(_pointer_)
					, ControlPointer(_pointer_)
				{
					//no process
				};

				inline VACIterator(const VACIterator& _copy_) noexcept
					:TopPointer(_copy_.TopPointer)
					, ControlPointer(_copy_.ControlPointer)
				{
					//no process
				};

				inline VACIterator(VACIterator&& _move_) noexcept
				{
					TopPointer = std::move(_move_.TopPointer);
					ControlPointer = std::move(_move_.ControlPointer);

					_move_.TopPointer = nullptr;
					_move_.ControlPointer = nullptr;
				};

				inline VACIterator& operator ++(void) noexcept
				{
					++ControlPointer;
					return (*this);
				};

				inline VACIterator& operator ++(int) noexcept
				{
					VACIterator tmp = (*this);

					++ControlPointer;
					return tmp;
				};

				inline VACIterator& operator --(void) noexcept
				{
					--ControlPointer;
					return (*this);
				};

				inline VACIterator& operator --(int) noexcept
				{

					VACIterator tmp = (*this);

					--ControlPointer;
					return tmp;
				};

				inline bool operator ==(const VACIterator& _compare_) const noexcept
				{
					return ControlPointer == _compare_.ControlPointer;
				};

				inline bool operator !=(const VACIterator& _compare_) const noexcept
				{
					return ControlPointer != _compare_.ControlPointer;
				};

				inline const T& operator[](uint64_t _index_) const
				{
					return TopPointer[_index_];
				};

				inline T& operator[](uint64_t _index_)
				{
					return TopPointer[_index_];
				};

				inline const T& operator*(void) const
				{
					return (*ControlPointer);
				};

				inline T& operator*(void)
				{
					return (*ControlPointer);
				};

				inline const T* operator ->(void) const noexcept
				{
					return ControlPointer;
				};

				inline T* operator ->(void) noexcept
				{
					return ControlPointer;
				};
			};

		private:
			T* AllocAreaPtr;
			uint64_t AllocCount;
			uint64_t MaxCnt;

			SonikLib::S_CAS::SonikAtomicLock m_lock;

		private:
			SonikVariableArrayContainer(void)
				:AllocAreaPtr(nullptr)
				, AllocCount(0)
				, MaxCnt(0)
			{
				// no process;
			};

			//コピーとムーヴ禁止
			SonikVariableArrayContainer(const SonikVariableArrayContainer& _copy_) = delete;
			SonikVariableArrayContainer(SonikVariableArrayContainer&& _move_) = delete;
			SonikVariableArrayContainer& operator =(const SonikVariableArrayContainer& _copy_) = delete;
			SonikVariableArrayContainer& operator =(SonikVariableArrayContainer&& _move_) = delete;

			//リザーブ
			inline bool __RESERVE__(uint64_t _size_) noexcept
			{
				int8_t* l_tmparea = new(std::nothrow) int8_t[(sizeof(T) * _size_)]{};
				if (l_tmparea == nullptr)
				{
					return false;
				};

				T* l_new_area = reinterpret_cast<T*>(l_tmparea);
				T* old_area = AllocAreaPtr;

				for (uint64_t i = 0; i < AllocCount; ++i)
				{
					new(&l_new_area[i]) T(old_area[i]);
				};

				delete[] reinterpret_cast<int8_t*>(AllocAreaPtr);
				AllocAreaPtr = reinterpret_cast<T*>(l_tmparea);
				MaxCnt = _size_;

				return true;
			};

		public:
			inline static bool CreateContainer(SonikLib::SharedSmtPtr<SonikVariableArrayContainer<T>>& _out_smtptr_, int32_t _ElemCount_ = 300)
			{
				if (_ElemCount_ == 0)
				{
					return false;
				};

				SonikVariableArrayContainer<T>* l_vacobj = nullptr;

				try
				{
					l_vacobj = new SonikVariableArrayContainer<T>;
					int8_t* l_tmp = new int8_t[(sizeof(T) * _ElemCount_)]{};

					l_vacobj->AllocAreaPtr = reinterpret_cast<T*>(l_tmp);
					l_vacobj->MaxCnt = _ElemCount_;

					
					if (!SonikLib::SharedSmtPtr<SonikVariableArrayContainer<T>>::SmartPointerCreate(l_vacobj, _out_smtptr_))
					{
						delete l_vacobj;
						throw std::bad_alloc();
					};

				}
				catch (std::bad_alloc&)
				{
					if (l_vacobj != nullptr)
					{
						delete l_vacobj;
					};

					return false;
				};

				return true;
			};

			inline ~SonikVariableArrayContainer(void)
			{
				if (AllocAreaPtr != nullptr)
				{
					for (uint64_t i = 0; i < AllocCount; ++i)
					{
						AllocAreaPtr[i].~T();
					};

					delete[] reinterpret_cast<int8_t*>(AllocAreaPtr);
				};

			};

			inline VACIterator begin(void) noexcept
			{
				return VACIterator(AllocAreaPtr);
			};

			inline VACIterator back(void) noexcept
			{
				return (AllocCount > 0) ? VACIterator(&AllocAreaPtr[(AllocCount - 1)])
					: VACIterator(AllocAreaPtr);
			};

			inline VACIterator end(void) noexcept
			{
				return VACIterator(&AllocAreaPtr[AllocCount]);
			};

			inline VACIterator rend(void) noexcept
			{
				return VACIterator(&(AllocAreaPtr - 1));
			};

			inline uint64_t GetAllocCount(void) noexcept
			{
				return AllocCount;
			};

			inline uint64_t GetSizeMax(void) noexcept
			{
				return MaxCnt;
			};

			inline bool PushBack(const T& PushItem) noexcept
			{
				m_lock.lock();

				++AllocCount;

				if (MaxCnt < AllocCount)
				{
					if (!__RESERVE__(AllocCount))
					{
						--AllocCount;
						m_lock.unlock();
						return false;
					};
				};

				T* lp_placement = &AllocAreaPtr[(AllocCount - 1)];

				new(lp_placement) T(PushItem);

				m_lock.unlock();
				return true;
			};

			inline bool PopBack(void) noexcept
			{
				m_lock.lock();

				if (AllocCount == 0)
				{
					m_lock.unlock();
					return true;
				};

				AllocAreaPtr[AllocCount - 1].~T();

				--AllocCount;

				m_lock.unlock();
				return true;
			};

			inline bool Reserve(uint64_t _reserve_size_) noexcept
			{
				m_lock.lock();

				bool ret = false;

				ret = __RESERVE__(_reserve_size_);

				m_lock.unlock();

				return ret;
			};

			inline void Clear(void) noexcept
			{
				m_lock.lock();

				if (AllocCount == 0)
				{
					m_lock.unlock();
					return;
				};

				for (uint64_t i = 0; i < AllocCount; ++i)
				{
					AllocAreaPtr[i].~T();
				};

				std::fill_n(reinterpret_cast<int8_t*>(AllocAreaPtr), (sizeof(T) * AllocCount), 0);

				AllocCount = 0;

				m_lock.unlock();
				return;
			};

			inline const T& operator[](uint64_t _index_) const
			{
				return AllocAreaPtr[_index_];
			};

			inline T& operator[](uint64_t _index_)
			{
				return AllocAreaPtr[_index_];
			};

		}; //end class

	}; //end namespace Container

}; //end namespace SonikLib

#endif /* SONIKSTRING_RANGEDFORCONTAINER_HPP_ */