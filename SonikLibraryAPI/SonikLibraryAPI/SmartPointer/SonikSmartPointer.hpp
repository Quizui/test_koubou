/*
 * SonikSmartPointer.h
 *
 *  Created on: 2017/10/10
 *      Author: SONIK
 */

#ifndef SMARTPOINTER_SONIK_SMARTPOINTER_HPP_
#define SMARTPOINTER_SONIK_SMARTPOINTER_HPP_

#include <atomic>
#include <new>

namespace SonikLib
{
	template <class PointerType>
	class NormalSmtPtr
	{
	private:
		PointerType* m_Pointer;

		std::atomic<unsigned int>* m_Count;

	private:
		void AddRef(void)
		{
			unsigned int TmpCnt = m_Count->load(std::memory_order_acquire);
			while( !m_Count->compare_exchange_strong(TmpCnt, TmpCnt+1, std::memory_order_acq_rel) )
			{
				//no process
			};

		};

		void Release(void)
		{
			unsigned int TmpCnt = m_Count->load(std::memory_order_acquire);
			while( !m_Count->compare_exchange_strong(TmpCnt, TmpCnt-1, std::memory_order_acq_rel) )
			{
				//no process
			};


			if( (TmpCnt -1) == 0 )
			{
				delete m_Pointer;
				delete m_Count;
			};

		};

	public:

		//constructor
		explicit NormalSmtPtr(PointerType* Pointer = nullptr)
		{

			try
			{
				m_Count = new std::atomic<unsigned int>;
			}catch(std::bad_alloc& e)
			{
				throw;
			}

			m_Count->store(1);
			m_Pointer = Pointer;

		};

		//コピーコンストラクタ
		NormalSmtPtr(const NormalSmtPtr<PointerType>& SmtPtr)
		{
			m_Pointer = SmtPtr.m_Pointer;
			m_Count = SmtPtr.m_Count;

			AddRef();

		};

		//Moveコンストラクタ
		NormalSmtPtr(NormalSmtPtr<PointerType>&& SmtPtr)
		{
			m_Pointer = SmtPtr.m_Pointer;
			m_Count = SmtPtr.m_Count;

			SmtPtr.m_Pointer = nullptr;
			SmtPtr.m_Count = nullptr;

		};

		//Destructor
		~NormalSmtPtr(void)
		{
			Release();
		};

        //MoveEqual
		NormalSmtPtr& operator =(NormalSmtPtr<PointerType>&& SmtPtr)
		{
			//自身への代入は意味が無いので行わない。
			if( SmtPtr.m_Pointer == m_Pointer )
			{
				return (*this);
			};

			Release();

			m_Pointer = SmtPtr.m_Pointer;
			m_Count = SmtPtr.m_Count;

//			SmtPtr.m_Pointer = nullptr;
//			SmtPtr.m_Count = nullptr;

			AddRef();

			return (*this);

		};


		NormalSmtPtr& operator =(const NormalSmtPtr<PointerType>& SmtPtr)
		{
			//自身への代入は意味が無いので行わない。
			if( SmtPtr.m_Pointer == m_Pointer )
			{
				return (*this);
			};

			Release();

			m_Count = SmtPtr.m_Count;
			m_Pointer = SmtPtr.m_Pointer;

			AddRef();

			return (*this);
		};

		bool operator ==(const NormalSmtPtr<PointerType>& SmtPtr)
		{
			if( m_Pointer == SmtPtr.m_Pointer )
			{
				return true;
			};

			return false;
		};

		bool operator ==(const uintptr_t PtrVal)
		{
			if( static_cast<uintptr_t>(m_Pointer) == PtrVal )
			{
				return true;
			};

			return false;
		};

		bool operator ==(const void* Ptrs)
		{
			if( m_Pointer == Ptrs )
			{
				return true;
			};

			return false;
		};

		void ResetPointer(PointerType* SetPointer = nullptr)
		{
			Release();

			//再初期化
            m_Count = new std::atomic<unsigned int>;
            m_Count->store(1);

            m_Pointer = SetPointer;
//			m_Count = new unsigned long;
//			(*m_Count) = 1;
//
//			m_Pointer = SetPointer;
		};

		PointerType* operator ->(void)
		{
			return m_Pointer;

		};
	};


};




#endif /* SMARTPOINTER_SONIK_SMARTPOINTER_HPP_ */