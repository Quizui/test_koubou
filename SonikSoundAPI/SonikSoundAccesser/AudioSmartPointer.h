/*
 * AudioSmartPointer.h
 *
 *  Created on: 2017/10/10
 *      Author: SONIC
 */

#ifndef SMARTPOINTER_AUDIOSMARTPOINTER_H_
#define SMARTPOINTER_AUDIOSMARTPOINTER_H_

#include <stdint.h>

namespace SonikAudioPointer
{
//friend作るための前方宣言
template <class PointerType>
class SonikAudioInterfaceSmtPtr;
template <class PointerType>
class SonikAudioPlayerSmtPtr;

template<class BeforeType, class AfterType>
void SmtPtrUpCast(SonikAudioInterfaceSmtPtr<BeforeType>& be_smtptr, SonikAudioInterfaceSmtPtr<AfterType>& af_smtptr);
template<class BeforeType, class AfterType>
void SmtPtrUpCast(SonikAudioPlayerSmtPtr<BeforeType>& be_smtptr, SonikAudioPlayerSmtPtr<AfterType>& af_smtptr);



	template <class PointerType, std::enable_if_t<!std::is_pointer_v<pType>, bool> = true>
	class SonikAudioInterfaceSmtPtr
	{
		template<class BeforeType, class AfterType>
		friend void SmtPtrUpCast(SonikAudioInterfaceSmtPtr<BeforeType>& be_smtptr, SonikAudioInterfaceSmtPtr<AfterType>& af_smtptr);

	private:
		PointerType* m_Pointer;

		unsigned long* m_Count;

	private:
		void AddRef(void)
		{
			++(*m_Count);
		};

		void Release(void)
		{
			--(*m_Count);

			if( (*m_Count) == 0 )
			{
				delete m_Pointer;
				delete m_Count;

			};

		};

	public:

		//constructor
		explicit SonikAudioInterfaceSmtPtr(PointerType* Pointer = nullptr)
		{
			m_Count = new unsigned long;
			(*m_Count) = 1;

			m_Pointer = Pointer;

		};

		//コピーコンストラクタ
		SonikAudioInterfaceSmtPtr(const SonikAudioInterfaceSmtPtr<PointerType>& SmtPtr)
		{
			m_Pointer = SmtPtr.m_Pointer;
			m_Count = SmtPtr.m_Count;

			AddRef();

		};

		//Destructor
		~SonikAudioInterfaceSmtPtr(void)
		{
			Release();

		};

		SonikAudioInterfaceSmtPtr<PointerType>& operator =(const SonikAudioInterfaceSmtPtr<PointerType>& SmtPtr)
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

		template<class BeforType>
		SonikAudioInterfaceSmtPtr<PointerType>& operator =(const SonikAudioInterfaceSmtPtr<BeforType>& SmtPtr)
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


		bool operator ==(const SonikAudioInterfaceSmtPtr<PointerType>& SmtPtr)
		{
			if( m_Pointer == SmtPtr.m_Pointer )
			{
				return true;
			};

			return false;
		};

		bool operator ==(const uint64_t PtrVal)
		{
			if( reinterpret_cast<uint64_t>(m_Pointer) == PtrVal )
			{
				return true;
			};

			return false;
		};

		void ResetPointer(PointerType* SetPointer = nullptr)
		{
			Release();

			//再初期化
			m_Count = new unsigned long;
			(*m_Count) = 1;

			m_Pointer = SetPointer;
		};

//		template <class SmtPtrType>
//		SonikAudioInterfaceSmtPtr<SmtPtrType> CastGet(void)
//		{
////			m_Count = SmtPtr.m_Count;
////			m_Pointer = SmtPtr.m_Pointer;
//
//			SetArg.m_Pointer = m_Pointer;
//			SetArg.m_Count = m_Count;
//
//			AddRef();
//
//		};

		PointerType* operator ->(void)
		{
			return m_Pointer;

		};
	};




	template <class PointerType, std::enable_if_t<!std::is_pointer_v<pType>, bool> = true>
	class SonikAudioPlayerSmtPtr
	{
		template<class BeforeType, class AfterType>
		friend void SmtPtrUpCast(SonikAudioPlayerSmtPtr<BeforeType>& be_smtptr, SonikAudioPlayerSmtPtr<AfterType>& af_smtptr);


	private:
		PointerType* m_Pointer;

		unsigned long* m_Count;

	private:
		void AddRef(void)
		{
			++(*m_Count);
		};

		void Release(void)
		{
			--(*m_Count);

			if( (*m_Count) == 0 )
			{
				delete m_Pointer;
				delete m_Count;

			};

		};

	public:

		//constructor
		explicit SonikAudioPlayerSmtPtr(PointerType* Pointer = nullptr)
		{
			m_Count = new unsigned long;
			(*m_Count) = 1;

			m_Pointer = Pointer;

		};

		//コピーコンストラクタ
		SonikAudioPlayerSmtPtr(const SonikAudioPlayerSmtPtr<PointerType>& SmtPtr)
		{
			m_Pointer = SmtPtr.m_Pointer;
			m_Count = SmtPtr.m_Count;

			AddRef();

		};

		//Destructor
		~SonikAudioPlayerSmtPtr(void)
		{
			Release();

		};

		SonikAudioPlayerSmtPtr& operator =(const SonikAudioInterfaceSmtPtr<PointerType>& SmtPtr)
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

		bool operator ==(const SonikAudioInterfaceSmtPtr<PointerType>& SmtPtr)
		{
			if( m_Pointer == SmtPtr.m_Pointer )
			{
				return true;
			};

			return false;
		};

		bool operator ==(const unsigned long PtrVal)
		{
			if( m_Pointer == PtrVal )
			{
				return true;
			};

			return false;
		};

		void ResetPointer(PointerType* SetPointer = nullptr)
		{
			Release();

			//再初期化
			m_Count = new unsigned long;
			(*m_Count) = 1;

			m_Pointer = SetPointer;
		};

		PointerType* operator ->(void)
		{
			return m_Pointer;

		};
	};




	template <class PointerType, std::enable_if_t<!std::is_pointer_v<pType>, bool> = true>
	class SonikAudioNormalSmtPtr
	{

	private:
		PointerType* m_Pointer;

		unsigned long* m_Count;

	private:
		void AddRef(void)
		{
			++(*m_Count);
		};

		void Release(void)
		{
			--(*m_Count);

			if( (*m_Count) == 0 )
			{
				delete m_Pointer;
				delete m_Count;

			};

		};

	public:

		//constructor
		explicit SonikAudioNormalSmtPtr(PointerType* Pointer = nullptr)
		{
			m_Count = new unsigned long;
			(*m_Count) = 1;

			m_Pointer = Pointer;

		};

		//コピーコンストラクタ
		SonikAudioNormalSmtPtr(const SonikAudioNormalSmtPtr<PointerType>& SmtPtr)
		{
			m_Pointer = SmtPtr.m_Pointer;
			m_Count = SmtPtr.m_Count;

			AddRef();

		};

		//Destructor
		~SonikAudioNormalSmtPtr(void)
		{
			Release();

		};

		SonikAudioNormalSmtPtr& operator =(const SonikAudioNormalSmtPtr<PointerType>& SmtPtr)
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

		bool operator ==(const SonikAudioNormalSmtPtr<PointerType>& SmtPtr)
		{
			if( m_Pointer == SmtPtr.m_Pointer )
			{
				return true;
			};

			return false;
		};

		bool operator ==(const unsigned long PtrVal)
		{
			if( m_Pointer == PtrVal )
			{
				return true;
			};

			return false;
		};

		void ResetPointer(PointerType* SetPointer = nullptr)
		{
			Release();

			//再初期化
			m_Count = new unsigned long;
			(*m_Count) = 1;

			m_Pointer = SetPointer;
		};

		PointerType* operator ->(void)
		{
			return m_Pointer;

		};
	};



	template<class BeforeType, class AfterType>
	void SmtPtrUpCast(SonikAudioInterfaceSmtPtr<BeforeType>& be_smtptr, SonikAudioInterfaceSmtPtr<AfterType>& af_smtptr)
	{
		//自身への代入は意味が無いので行わない。
		if( be_smtptr.m_Pointer == af_smtptr.m_Pointer )
		{
			return;
		};

		af_smtptr.m_Pointer = reinterpret_cast<AfterType*>(be_smtptr.m_Pointer);
		af_smtptr.m_Count = be_smtptr.m_Count;

		af_smtptr.AddRef();
	};

	template<class BeforeType, class AfterType>
	void SmtPtrUpCast(SonikAudioPlayerSmtPtr<BeforeType>& be_smtptr, SonikAudioPlayerSmtPtr<AfterType>& af_smtptr)
	{
		//自身への代入は意味が無いので行わない。
		if( be_smtptr.m_Pointer == af_smtptr.m_Pointer )
		{
			return;
		};

		af_smtptr.m_Pointer = reinterpret_cast<AfterType*>(be_smtptr.m_Pointer);
		af_smtptr.m_Count = be_smtptr.m_Count;

		af_smtptr.AddRef();
	};


};




#endif /* SMARTPOINTER_AUDIOSMARTPOINTER_H_ */
