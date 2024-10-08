/*
 * SonikSmartPointer.h
 *
 *  Created on: 2017/10/10
 *      Author: SONIK
 */

#ifndef SMARTPOINTER_SONIK_SMARTPOINTER_HPP_
#define SMARTPOINTER_SONIK_SMARTPOINTER_HPP_

#include <stdint.h>
#include <atomic>
#include <new>
#include <type_traits>

//前方宣言
namespace SonikLib
{
	template <class pType, class Enable = void>
	class SharedSmtPtr;
	template <class pType>
	class SharedSmtPtr<pType[]>;
	template <class pType, class Enable = void>
	class UniqueSmtPtr;
	template <class pType>
	class UniqueSmtPtr<pType[]>;

	//SharedSmtPtrのdynamic_castをサポートします。
	//失敗した場合はfalseを返却します。
	template <class before, class after>
	bool SharedCast_Dynamic(SharedSmtPtr<before>& _src_, SharedSmtPtr<after>& _dst_);
	template <class before, class after>
	bool SharedCast_Dynamic(SharedSmtPtr<before[]>& _src_, SharedSmtPtr<after[]>& _dst_);
	//SharedSmtPtrのreinterpret_castをサポートします。
	//ただし、普通にreinterpret_castをするだけです。通常のポインタをreinterpret_castをするのと違いはありません。
	//そのため、その先の例外処理、エラー処理等は使用者の責任になります。
	template <class before, class after>
	void SharedCast_Reinterpret(SharedSmtPtr<before>& _src_, SharedSmtPtr<after>& _dst_);
	template <class before, class after>
	void SharedCast_Reinterpret(SharedSmtPtr<before[]>& _src_, SharedSmtPtr<after[]>& _dst_);

	//UniqueSmtPtrのdynamic_castをサポートします。
	//失敗した場合はfalseを返却し、所有権を移譲せず終了します。
	template <class before, class after>
	bool UniqueCast_Dynamic(UniqueSmtPtr<before>& _src_, UniqueSmtPtr<after>& _dst_);
	template <class before, class after>
	bool UniqueCast_Dynamic( UniqueSmtPtr<before[]>& _src_,  UniqueSmtPtr<after[]>& _dst_);
	//UniqueSmtPtrのreinterpret_castをサポートします。
	//ただし、普通にreinterpret_castをするだけです。通常のポインタをreinterpret_castをするのと違いはありません。
	//そのため、その先の例外処理、エラー処理等は使用者の責任になります。
	//また、SharedSmtPtrと違い、唯一性保持のため所有権を問答無用で変換先(_dst_側)へ移譲し、_src_側はnullptr化されます。
	//_src_へのsegment faultにご注意ください。
	template <class before, class after>
	void UniqueCast_Reinterpret(UniqueSmtPtr<before>& _src_, UniqueSmtPtr<after>& _dst_);
	template <class before, class after>
	void UniqueCast_Reinterpret( UniqueSmtPtr<before[]>& _src_,  UniqueSmtPtr<after[]>& _dst_);

};


namespace SonikLib
{

	//最低限のスマートポインタ
	//配列版は<ptype[]>としてこの定義の下に特殊化定義しています。
	//初期化時以外の = による代入は同じSharedSmtPtr型以外は制限しています。
	//つまり、SharedSmtPtr<int> a = new int; は可能ですが、
	//SharedSmtPtr<int> a;
	//a = new int; はアウトです。これをしたい場合はResetPointer関数を使用してください。
	template <class pType, class Enable>
	class SharedSmtPtr
	{
		static_assert(!std::is_pointer_v<pType>, "Please Used NoPointerType");

		template <class before, class after>
		friend bool SharedCast_Dynamic(SharedSmtPtr<before>& _src_, SharedSmtPtr<after>& _dst_);
		template <class before, class after>
		friend void SharedCast_Reinterpret(SharedSmtPtr<before>& _src_, SharedSmtPtr<after>& _dst_);

	private:
		pType* m_Pointer;
		std::atomic<unsigned int>* m_Count; //もったいないがm_Pointerがnullptrのときもカウント1として領域をnewする。

	private:
		inline void AddRef(void) noexcept
		{
			if(m_Count == nullptr)
			{
				return;
			};

			unsigned int TmpCnt = m_Count->load(std::memory_order_acquire);
			while( !m_Count->compare_exchange_strong(TmpCnt, TmpCnt+1, std::memory_order_acq_rel) )
			{
				//no process
			};

		};

		inline void Release(void) noexcept
		{
			if(m_Count == nullptr)
			{
				return;
			};

			unsigned int TmpCnt = m_Count->load(std::memory_order_acquire);
			while( !m_Count->compare_exchange_strong(TmpCnt, TmpCnt-1, std::memory_order_acq_rel) )
			{
				//no process
			};


			if( TmpCnt == 1 )
			{
				delete m_Pointer;
				delete m_Count;

			};

			m_Pointer = nullptr;
			m_Count = nullptr;
		};

	public:

		//constructor
		explicit SharedSmtPtr(pType* _pointer_ = nullptr)
		:m_Pointer(_pointer_)
		,m_Count(nullptr)
		{

			if(_pointer_ == nullptr)
			{
				//何もしない。
				return;
			};

			try
			{
				m_Count = new std::atomic<unsigned int>;
			}catch(std::bad_alloc&)
			{
				delete m_Pointer; // コンストラクタでの例外処理はそのオブジェクトの作成が無効となるので再度nullptrを入れる必要なし。
				//m_Countのときに失敗した場合はm_Countは作成されていない状態=nullptrなので何もせず終了。
				throw;
			};
			m_Count->store(1);

		};

		//コピーコンストラクタ
		inline SharedSmtPtr(const SharedSmtPtr<pType>& _SmtPtr_) noexcept
		{
			m_Pointer = _SmtPtr_.m_Pointer;
			m_Count = _SmtPtr_.m_Count;

			AddRef();

		};

		//Destructor
		~SharedSmtPtr(void) noexcept
		{
			Release();
		};

		inline SharedSmtPtr& operator =(const SharedSmtPtr<pType>& _SmtPtr_) noexcept
		{
			//自己代入を解決する実装。
			if(m_Pointer != _SmtPtr_.m_Pointer)
			{
				SharedSmtPtr<pType> lsp;
				lsp.m_Pointer = m_Pointer;
				lsp.m_Count = m_Count;

				m_Pointer = _SmtPtr_.m_Pointer;
				m_Count = _SmtPtr_.m_Count;

				AddRef();
			};

			return (*this);
		};

       inline SharedSmtPtr& operator =(pType*& _pointer_) noexcept
       {
            Release();
            
            if(_pointer_ == nullptr)
            {
                return (*this);
            };
            
            m_Pointer = _pointer_;
            _pointer_ = nullptr;
            
            try
            {
                m_Count = new std::atomic<unsigned int>;
                
            }catch(std::bad_alloc& e)
            {
                delete m_Pointer;
                m_Pointer = nullptr;
                
                throw;
            };
            
            m_Count->store(1);
            return (*this);
        };
       
       inline SharedSmtPtr& operator =(pType*&& _pointer_) noexcept
       {
            Release();
            
            if(_pointer_ == nullptr)
            {
                return (*this);
            };
            
            m_Pointer = _pointer_;
            _pointer_ = nullptr;
            
            try
            {
                m_Count = new std::atomic<unsigned int>;
                
            }catch(std::bad_alloc& e)
            {
                delete m_Pointer;
                m_Pointer = nullptr;
                
                throw;
            };
            
            m_Count->store(1);
            return (*this);
        };

		//MoveEqual
		inline SharedSmtPtr& operator =(SharedSmtPtr<pType>&& _SmtPtr_) noexcept
		{
			//自己代入を解決する実装。
			if(m_Pointer != _SmtPtr_.m_Pointer)
			{
				SharedSmtPtr<pType> lsp;
				lsp.m_Pointer = m_Pointer;
				lsp.m_Count = m_Count;

				m_Pointer = _SmtPtr_.m_Pointer;
				m_Count = _SmtPtr_.m_Count;

				_SmtPtr_.m_Pointer = nullptr;
				_SmtPtr_.m_Count = nullptr;

				//moveなのでAddref()をコールする必要はない。
			};

			return (*this);
		};

		bool operator ==(const SharedSmtPtr<pType>& _SmtPtr_) noexcept
		{
			return (m_Pointer == _SmtPtr_.m_Pointer) ? true : false;
		};

		bool operator ==(const uintptr_t PtrVal) noexcept
		{
			return (static_cast<uintptr_t>(m_Pointer) == PtrVal) ? true : false;
		};

		bool operator ==(const void* _Ptrs_) noexcept
		{
			return (m_Pointer == _Ptrs_) ? true : false;
		};

		//operator = でShraedSmtPtr型の代入処理は実装済みなのでResetPointerは生ポのみ実装。
		bool ResetPointer(pType* _SetPointer_ = nullptr)
		{
			//アドレスが一緒(なことはそうそうないだろうけど)なら何もしない。
			if(m_Pointer == _SetPointer_)
			{
				return true;
			};

			//アドレスが違うなら処理。
			Release();

			if(_SetPointer_ == nullptr)
			{
				return true;
			};

			m_Count = new(std::nothrow) std::atomic<unsigned int>;
			if(m_Count == nullptr)
			{
				delete _SetPointer_; //new A など直接new で渡された時の対策。
				return false;
			};

			m_Count->store(1);
			m_Pointer = _SetPointer_;

			return true;
		};

		//生ポインタとして取得します。
		//所有権は手放しません。deleteしないように注意してください。
		pType* GetPointer(void) noexcept
		{
			return m_Pointer;
		};

		//生ポインタとして取得します。
		//所有権は手放します。（カウンタが0の場合は呼び出し元でdeleteを忘れないようにしてください。)
		//取得したポインタがSharedSmtPtrとして最後のポインタかどうかは、戻り値を確認してください。
		//0 なら最終ポインタです。
		uint32_t GetOwnerPointer(pType*& _get_) noexcept
		{
			_get_ = m_Pointer;
			m_Pointer = nullptr;

			unsigned int TmpCnt = 0;
			if( m_Count != nullptr )
			{
				TmpCnt = m_Count->load(std::memory_order_acquire);
				while( !m_Count->compare_exchange_strong(TmpCnt, TmpCnt-1, std::memory_order_acq_rel) )
				{
					//no process
				};

				if( TmpCnt == 1 )
				{
					delete m_Count;
				};
				//自分は使わなくなるので問答無用でnullptr化
				m_Count = nullptr;
			};

			return (TmpCnt -1);
		};

		//現在のリファレンスカウント値を取得します。
		uint32_t GetRefCount(void)
		{
			return m_Count->load(std::memory_order_acquire);
		};

		//NullptrならTrue
		bool IsNullptr(void) noexcept
		{
			return (m_Pointer == nullptr) ? true : false;
		};

		pType* operator ->(void)
		{
			return m_Pointer;

		};

		pType& operator*(void) const
		{
			return (*m_Pointer);
		};

		//C++11 以降 ->*演算子オーバーロード(メンバ関数ポインタ用)
		// メンバ関数ポインタを使用するためのオーバーロード演算子=========================
		template <class RetType, class ... Args>
		class MemberFunctionCaller
		{
			pType* object;
			RetType (pType::*func)(Args...);
		public:
			MemberFunctionCaller(pType* obj, RetType (pType::*f)(Args...))
			: object(obj)
			, func(f)
			{
				//no process;
			};

			RetType operator()(Args... args) const
			{
				return (object->*func)(std::forward<Args>(args)...);
			}
		};

		template <class RetType, class ... Args>
		MemberFunctionCaller<RetType, Args...> operator->*(RetType(pType::*func)(Args...))
		{
			return MemberFunctionCaller<RetType, Args...>(m_Pointer, func);
		};
		//==================================================

	};

	//リテラル型用特殊化＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
	template <class pType>
	class SharedSmtPtr<pType, typename std::enable_if<std::is_arithmetic<pType>::value>::type>
	{
		static_assert(!std::is_pointer_v<pType>, "Please Used NoPointerType");

		template <class before, class after>
		friend bool SharedCast_Dynamic(SharedSmtPtr<before>& _src_, SharedSmtPtr<after>& _dst_);
		template <class before, class after>
		friend void SharedCast_Reinterpret(SharedSmtPtr<before>& _src_, SharedSmtPtr<after>& _dst_);

	private:
		pType* m_Pointer;
		std::atomic<unsigned int>* m_Count; //もったいないがm_Pointerがnullptrのときもカウント1として領域をnewする。

	private:
		inline void AddRef(void) noexcept
		{
			if(m_Count == nullptr)
			{
				return;
			};

			unsigned int TmpCnt = m_Count->load(std::memory_order_acquire);
			while( !m_Count->compare_exchange_strong(TmpCnt, TmpCnt+1, std::memory_order_acq_rel) )
			{
				//no process
			};

		};

		inline void Release(void) noexcept
		{
			if(m_Count == nullptr)
			{
				return;
			};

			unsigned int TmpCnt = m_Count->load(std::memory_order_acquire);
			while( !m_Count->compare_exchange_strong(TmpCnt, TmpCnt-1, std::memory_order_acq_rel) )
			{
				//no process
			};


			if( TmpCnt == 1 )
			{
				delete m_Pointer;
				delete m_Count;

			};

			m_Pointer = nullptr;
			m_Count = nullptr;
		};

	public:

		//constructor
		explicit SharedSmtPtr(pType* _pointer_ = nullptr)
		:m_Pointer(_pointer_)
		,m_Count(nullptr)
		{

			if(_pointer_ == nullptr)
			{
				//何もしない。
				return;
			};

			try
			{
				m_Count = new std::atomic<unsigned int>;
			}catch(std::bad_alloc&)
			{
				delete m_Pointer; // コンストラクタでの例外処理はそのオブジェクトの作成が無効となるので再度nullptrを入れる必要なし。
				//m_Countのときに失敗した場合はm_Countは作成されていない状態=nullptrなので何もせず終了。
				throw;
			};
			m_Count->store(1);

		};

		//コピーコンストラクタ
		inline SharedSmtPtr(const SharedSmtPtr<pType>& _SmtPtr_) noexcept
		{
			m_Pointer = _SmtPtr_.m_Pointer;
			m_Count = _SmtPtr_.m_Count;

			AddRef();

		};

		//Destructor
		~SharedSmtPtr(void) noexcept
		{
			Release();
		};

		inline SharedSmtPtr& operator =(const SharedSmtPtr<pType>& _SmtPtr_) noexcept
		{
			//自己代入を解決する実装。
			if(m_Pointer != _SmtPtr_.m_Pointer)
			{
				SharedSmtPtr<pType> lsp;
				lsp.m_Pointer = m_Pointer;
				lsp.m_Count = m_Count;

				m_Pointer = _SmtPtr_.m_Pointer;
				m_Count = _SmtPtr_.m_Count;

				AddRef();
			};

			return (*this);
		};

        //MoveEqual
		SharedSmtPtr& operator =(SharedSmtPtr<pType>&& _SmtPtr_) noexcept
		{
			//自己代入を解決する実装。
			if(m_Pointer != _SmtPtr_.m_Pointer)
			{
				SharedSmtPtr<pType> lsp;
				lsp.m_Pointer = m_Pointer;
				lsp.m_Count = m_Count;

				m_Pointer = _SmtPtr_.m_Pointer;
				m_Count = _SmtPtr_.m_Count;

				//moveなのでAddref()をコールする必要はない。
			};

			return (*this);
		};

		bool operator ==(const SharedSmtPtr<pType>& _SmtPtr_) noexcept
		{
			return (m_Pointer == _SmtPtr_.m_Pointer) ? true : false;
		};

		bool operator ==(const uintptr_t PtrVal) noexcept
		{
			return (static_cast<uintptr_t>(m_Pointer) == PtrVal) ? true : false;
		};

		bool operator ==(const void* _Ptrs_) noexcept
		{
			return (m_Pointer == _Ptrs_) ? true : false;
		};

		//operator = でShraedSmtPtr型の代入処理は実装済みなのでResetPointerは生ポのみ実装。
		bool ResetPointer(pType* _SetPointer_ = nullptr)
		{
			//アドレスが一緒(なことはそうそうないだろうけど)なら何もしない。
			if(m_Pointer == _SetPointer_)
			{
				return true;
			};

			//アドレスが違うなら処理。
			Release();

			if(_SetPointer_ == nullptr)
			{
				return true;
			};

			m_Count = new(std::nothrow) std::atomic<unsigned int>;
			if(m_Count == nullptr)
			{
				delete _SetPointer_; //new A など直接new で渡された時の対策。
				return false;
			};

			m_Count->store(1);
			m_Pointer = _SetPointer_;

			return true;
		};

		//生ポインタとして取得します。
		//所有権は手放しません。deleteしないように注意してください。
		pType* GetPointer(void) noexcept
		{
			return m_Pointer;
		};

		//生ポインタとして取得します。
		//所有権は手放します。（カウンタが0の場合は呼び出し元でdeleteを忘れないようにしてください。)
		//取得したポインタがSharedSmtPtrとして最後のポインタかどうかは、戻り値を確認してください。
		//0 なら最終ポインタです。
		uint32_t GetOwnerPointer(pType*& _get_) noexcept
		{
			_get_ = m_Pointer;
			m_Pointer = nullptr;

			unsigned int TmpCnt = 0;
			if( m_Count != nullptr )
			{
				TmpCnt = m_Count->load(std::memory_order_acquire);
				while( !m_Count->compare_exchange_strong(TmpCnt, TmpCnt-1, std::memory_order_acq_rel) )
				{
					//no process
				};

				if( TmpCnt == 1 )
				{
					delete m_Count;
				};
				//自分は使わなくなるので問答無用でnullptr化
				m_Count = nullptr;
			};

			return (TmpCnt -1);
		};

		//現在のリファレンスカウント値を取得します。
		uint32_t GetRefCount(void)
		{
			return m_Count->load(std::memory_order_acquire);
		};

		//NullptrならTrue
		bool IsNullptr(void) noexcept
		{
			return (m_Pointer == nullptr) ? true : false;
		};

		pType* operator ->(void)
		{
			return m_Pointer;

		};

		pType& operator*(void) const
		{
			return (*m_Pointer);
		};

	};




	//配列特殊化==================================
	//最低限の配列用特殊化のスマートポインタ
	template <class pType>
	class SharedSmtPtr<pType[]>
	{
		static_assert(!std::is_pointer_v<pType>, "Please Used NoPointerType");

		template <class before, class after>
		friend bool SharedCast_Dynamic(SharedSmtPtr<before[]>& _src_, SharedSmtPtr<after[]>& _dst_);
		template <class before, class after>
		friend void SharedCast_Reinterpret(SharedSmtPtr<before[]>& _src_, SharedSmtPtr<after[]>& _dst_);

	private:
		pType* m_Pointer;
		std::atomic<unsigned int>* m_Count; //もったいないがm_Pointerがnullptrのときもカウント1として領域をnewする。

	private:
		inline void AddRef(void) noexcept
		{
			if(m_Count == nullptr)
			{
				return;
			};

			unsigned int TmpCnt = m_Count->load(std::memory_order_acquire);
			while( !m_Count->compare_exchange_strong(TmpCnt, TmpCnt+1, std::memory_order_acq_rel) )
			{
				//no process
			};

		};

		inline void Release(void) noexcept
		{
			if(m_Count == nullptr)
			{
				return;
			};

			unsigned int TmpCnt = m_Count->load(std::memory_order_acquire);
			while( !m_Count->compare_exchange_strong(TmpCnt, TmpCnt-1, std::memory_order_acq_rel) )
			{
				//no process
			};


			if( TmpCnt == 1 )
			{
				delete m_Pointer;
				delete m_Count;

			};

			m_Pointer = nullptr;
			m_Count = nullptr;
		};

	public:

		//constructor
		explicit SharedSmtPtr(pType* _pointer_ = nullptr)
		:m_Pointer(_pointer_)
		,m_Count(nullptr)
		{

			if(_pointer_ == nullptr)
			{
				//何もしない。
				return;
			};

			try
			{
				m_Count = new std::atomic<unsigned int>;
			}catch(std::bad_alloc&)
			{
				delete m_Pointer; // コンストラクタでの例外処理はそのオブジェクトの作成が無効となるので再度nullptrを入れる必要なし。
				//m_Countのときに失敗した場合はm_Countは作成されていない状態=nullptrなので何もせず終了。
				throw;
			};
			m_Count->store(1);

		};

		//コピーコンストラクタ
		inline SharedSmtPtr(const SharedSmtPtr<pType[]>& _SmtPtr_) noexcept
		{
			m_Pointer = _SmtPtr_.m_Pointer;
			m_Count = _SmtPtr_.m_Count;

			AddRef();

		};

		//Destructor
		~SharedSmtPtr(void) noexcept
		{
			Release();
		};

		inline SharedSmtPtr& operator =(const SharedSmtPtr<pType[]>& _SmtPtr_) noexcept
		{
			//自己代入を解決する実装。
			if(m_Pointer != _SmtPtr_.m_Pointer)
			{
				SharedSmtPtr<pType> lsp;
				lsp.m_Pointer = m_Pointer;
				lsp.m_Count = m_Count;

				m_Pointer = _SmtPtr_.m_Pointer;
				m_Count = _SmtPtr_.m_Count;

				AddRef();
			};

			return (*this);
		};

        //MoveEqual
		SharedSmtPtr& operator =(SharedSmtPtr<pType[]>&& _SmtPtr_) noexcept
		{
			//自己代入を解決する実装。
			if(m_Pointer != _SmtPtr_.m_Pointer)
			{
				SharedSmtPtr<pType> lsp;
				lsp.m_Pointer = m_Pointer;
				lsp.m_Count = m_Count;

				m_Pointer = _SmtPtr_.m_Pointer;
				m_Count = _SmtPtr_.m_Count;

				//moveなのでAddref()をコールする必要はない。
			};

			return (*this);
		};

		bool operator ==(const SharedSmtPtr<pType[]>& _SmtPtr_) noexcept
		{
			return (m_Pointer == _SmtPtr_.m_Pointer) ? true : false;
		};

		bool operator ==(const uintptr_t PtrVal) noexcept
		{
			return (static_cast<uintptr_t>(m_Pointer) == PtrVal) ? true : false;
		};

		bool operator ==(const void* _Ptrs_) noexcept
		{
			return (m_Pointer == _Ptrs_) ? true : false;
		};

		//operator = でShraedSmtPtr型の代入処理は実装済みなのでResetPointerは生ポのみ実装。
		bool ResetPointer(pType* _SetPointer_ = nullptr)
		{
			//アドレスが一緒(なことはそうそうないだろうけど)なら何もしない。
			if(m_Pointer == _SetPointer_)
			{
				return true;
			};

			//アドレスが違うなら処理。
			Release();

			if(_SetPointer_ == nullptr)
			{
				return true;
			};

			m_Count = new(std::nothrow) std::atomic<unsigned int>;
			if(m_Count == nullptr)
			{
				delete _SetPointer_; //new A など直接new で渡された時の対策。
				return false;
			};

			m_Count->store(1);
			m_Pointer = _SetPointer_;

			return true;
		};

		//生ポインタとして取得します。
		//所有権は手放しません。deleteしないように注意してください。
		pType* GetPointer(void) noexcept
		{
			return m_Pointer;
		};

		//生ポインタとして取得します。
		//所有権は手放します。（カウンタが0の場合は呼び出し元でdeleteを忘れないようにしてください。)
		//取得したポインタがSharedSmtPtrとして最後のポインタかどうかは、戻り値を確認してください。
		//0 なら最終ポインタです。
		uint32_t GetOwnerPointer(pType*& _get_) noexcept
		{
			_get_ = m_Pointer;
			m_Pointer = nullptr;

			unsigned int TmpCnt = 0;
			if( m_Count != nullptr )
			{
				TmpCnt = m_Count->load(std::memory_order_acquire);
				while( !m_Count->compare_exchange_strong(TmpCnt, TmpCnt-1, std::memory_order_acq_rel) )
				{
					//no process
				};

				if( TmpCnt == 1 )
				{
					delete m_Count;
				};
				//自分は使わなくなるので問答無用でnullptr化
				m_Count = nullptr;
			};

			return (TmpCnt -1);
		};

		const pType& operator[](uint64_t index) const
		{
			return m_Pointer[index];
		}

		pType& operator[](uint64_t index)
		{
			return m_Pointer[index];
		};

		//現在のリファレンスカウント値を取得します。
		uint32_t GetRefCount(void)
		{
			return m_Count->load(std::memory_order_acquire);
		};

		//NullptrならTrue
		bool IsNullptr(void) noexcept
		{
			return (m_Pointer == nullptr) ? true : false;
		};

		pType* operator ->(void)
		{
			return m_Pointer;

		};

		pType& operator*(void) const
		{
			return (*m_Pointer);
		};

	};


	//UniquePtr=========================================================
	//基本的に唯一性が担保出来ないため、生ポ代入系はあえて実装しない。
	template <class pType, class Enable>
	class UniqueSmtPtr
	{
		static_assert(!std::is_pointer_v<pType>, "Please Used NoPointerType");

		template <class before, class after>
		friend bool UniqueCast_Dynamic(UniqueSmtPtr<before>& _src_, UniqueSmtPtr<after>& _dst_);
		template <class before, class after>
		friend void UniqueCast_Reinterpret(UniqueSmtPtr<before>& _src_, UniqueSmtPtr<after>& _dst_);

	private:
		pType* m_pointer;

	public:
		UniqueSmtPtr(pType* _SetPointer_ = nullptr) noexcept
		:m_pointer(_SetPointer_)
		{
		};

		UniqueSmtPtr(pType*& _SetPointer_) noexcept
		:m_pointer(_SetPointer_)
		{
			_SetPointer_ = nullptr;
		};

		UniqueSmtPtr(pType*&& _SetPointer_) noexcept
		:m_pointer(_SetPointer_)
		{
			_SetPointer_ = nullptr;
		};

		UniqueSmtPtr(UniqueSmtPtr<pType>& _OwnerSwap_) noexcept
		:m_pointer(_OwnerSwap_.m_pointer)
		{
			_OwnerSwap_.m_pointer = nullptr;
		};

		UniqueSmtPtr(UniqueSmtPtr<pType>&& _OwnerSwap_) noexcept
		:m_pointer(_OwnerSwap_.m_pointer)
		{
			_OwnerSwap_.m_pointer = nullptr;
		};

		~UniqueSmtPtr(void)
		{
			if(m_pointer != nullptr)
			{
				delete m_pointer;
			};
		};

		UniqueSmtPtr& operator =(pType*& _SetPointer_ ) noexcept
		{
			if(m_pointer != _SetPointer_)
			{
				delete m_pointer;
				m_pointer = _SetPointer_;
				_SetPointer_ = nullptr;
			};

			return (*this);
		};

		UniqueSmtPtr& operator =(pType*&& _SetPointer_) noexcept
		{
			if(m_pointer != _SetPointer_)
			{
				delete m_pointer;
				m_pointer = _SetPointer_;
				_SetPointer_ = nullptr;
			};

			return (*this);
		};

		UniqueSmtPtr& operator =(UniqueSmtPtr<pType>& _SetObj_) noexcept
		{
			if(m_pointer != _SetObj_.m_pointer)
			{
				delete m_pointer;
				m_pointer = _SetObj_.m_pointer;
				_SetObj_.m_pointer = nullptr;
			};

			return (*this);
		};

		UniqueSmtPtr& operator =(UniqueSmtPtr<pType>&& _SetObj_) noexcept
		{
			if(m_pointer != _SetObj_.m_pointer)
			{
				delete m_pointer;
				m_pointer = _SetObj_.m_pointer;
				_SetObj_.m_pointer = nullptr;
			};

			return (*this);
		};

		//Null なら True
		bool IsNullptr(void) noexcept
		{
			return (m_pointer == nullptr) ? true : false;
		};

		void OwnerRelease(void) noexcept
		{
			delete m_pointer;
			m_pointer = nullptr;
		};

		SharedSmtPtr<pType> ChangeMangedPointer(void)
		{
			pType* lp = m_pointer;
			m_pointer = nullptr;

			return SharedSmtPtr<pType>(lp);
		};

		//生ポインタとして取得します。
		//所有権は手放します。(nullptrがセットされます。)
		pType* GetOwnerPointer(void)
		{
			pType* lp = m_pointer;
			m_pointer = nullptr;

			return lp;
		};

		pType* operator ->(void)
		{
			return m_pointer;

		};

		pType& operator*(void) const
		{
			return (*m_pointer);
		};

		//C++11 以降 ->*演算子オーバーロード(メンバ関数ポインタ用)
	    // メンバ関数ポインタを使用するためのオーバーロード演算子=========================
	    template <class RetType, class ... Args>
	    class MemberFunctionCaller
		{
	        pType* object;
	        RetType (pType::*func)(Args...);
	    public:
	        MemberFunctionCaller(pType* obj, RetType (pType::*f)(Args...))
	        : object(obj)
	        , func(f)
	        {
	        	//no process;
	        };

	        RetType operator()(Args... args) const
	        {
	            return (object->*func)(std::forward<Args>(args)...);
	        }
	    };

	    template <class RetType, class ... Args>
	    MemberFunctionCaller<RetType, Args...> operator->*(RetType(pType::*func)(Args...))
		{
	    	return MemberFunctionCaller<RetType, Args...>(m_pointer, func);
	    };
	    //==================================================

	};

	//リテラル型用特殊化
	template  <class pType>
	class UniqueSmtPtr<pType, typename std::enable_if<std::is_arithmetic<pType>::value>::type>
	{
		static_assert(!std::is_pointer_v<pType>, "Please Used NoPointerType");

		template <class before, class after>
		friend bool UniqueCast_Dynamic(UniqueSmtPtr<before>& _src_, UniqueSmtPtr<after>& _dst_);
		template <class before, class after>
		friend void UniqueCast_Reinterpret(UniqueSmtPtr<before>& _src_, UniqueSmtPtr<after>& _dst_);

	private:
		pType* m_pointer;

	public:
		UniqueSmtPtr(pType* _SetPointer_ = nullptr) noexcept
		:m_pointer(_SetPointer_)
		{
		};

		UniqueSmtPtr(pType*& _SetPointer_) noexcept
		:m_pointer(_SetPointer_)
		{
			_SetPointer_ = nullptr;
		};

		UniqueSmtPtr(pType*&& _SetPointer_) noexcept
		:m_pointer(_SetPointer_)
		{
			_SetPointer_ = nullptr;
		};

		UniqueSmtPtr(UniqueSmtPtr<pType>& _OwnerSwap_) noexcept
		:m_pointer(_OwnerSwap_.m_pointer)
		{
			_OwnerSwap_.m_pointer = nullptr;
		};

		UniqueSmtPtr(UniqueSmtPtr<pType>&& _OwnerSwap_) noexcept
		:m_pointer(_OwnerSwap_.m_pointer)
		{
			_OwnerSwap_.m_pointer = nullptr;
		};

		~UniqueSmtPtr(void)
		{
			if(m_pointer != nullptr)
			{
				delete m_pointer;
			};
		};

		UniqueSmtPtr& operator =(pType*& _SetPointer_ ) noexcept
		{
			if(m_pointer != _SetPointer_)
			{
				delete m_pointer;
				m_pointer = _SetPointer_;
				_SetPointer_ = nullptr;
			};

			return (*this);
		};

		UniqueSmtPtr& operator =(pType*&& _SetPointer_) noexcept
		{
			if(m_pointer != _SetPointer_)
			{
				delete m_pointer;
				m_pointer = _SetPointer_;
				_SetPointer_ = nullptr;
			};

			return (*this);
		};

		UniqueSmtPtr& operator =(UniqueSmtPtr<pType>& _SetObj_) noexcept
		{
			if(m_pointer != _SetObj_.m_pointer)
			{
				delete m_pointer;
				m_pointer = _SetObj_.m_pointer;
				_SetObj_.m_pointer = nullptr;
			};

			return (*this);
		};

		UniqueSmtPtr& operator =(UniqueSmtPtr<pType>&& _SetObj_) noexcept
		{
			if(m_pointer != _SetObj_.m_pointer)
			{
				delete m_pointer;
				m_pointer = _SetObj_.m_pointer;
				_SetObj_.m_pointer = nullptr;
			};

			return (*this);
		};

		//Null なら True
		bool IsNullptr(void) noexcept
		{
			return (m_pointer == nullptr) ? true : false;
		};

		void OwnerRelease(void) noexcept
		{
			delete m_pointer;
			m_pointer = nullptr;
		};

		SharedSmtPtr<pType> ChangeMangedPointer(void)
		{
			pType* lp = m_pointer;
			m_pointer = nullptr;

			return SharedSmtPtr<pType>(lp);
		};

		//生ポインタとして取得します。
		//所有権は手放します。(nullptrがセットされます。)
		pType* GetOwnerPointer(void)
		{
			pType* lp = m_pointer;
			m_pointer = nullptr;

			return lp;
		};

		pType* operator ->(void)
		{
			return m_pointer;

		};

		pType& operator*(void) const
		{
			return (*m_pointer);
		};

	};

	//UniquePtr=========================================================
	//配列特殊化
	template <class pType>
	class UniqueSmtPtr<pType[]>
	{
		static_assert(!std::is_pointer_v<pType>, "Please Used NoPointerType");

		template <class before, class after>
		friend bool UniqueCast_Dynamic( UniqueSmtPtr<before[]>& _src_,  UniqueSmtPtr<after[]>& _dst_);
		template <class before, class after>
		friend void UniqueCast_Reinterpret( UniqueSmtPtr<before[]>& _src_,  UniqueSmtPtr<after[]>& _dst_);

	private:
		pType* m_pointer;

	public:
		UniqueSmtPtr(void) noexcept
		:m_pointer(nullptr)
		{
		};

		UniqueSmtPtr(pType*& _SetPointer_) noexcept
		:m_pointer(_SetPointer_)
		{
			_SetPointer_ = nullptr;
		};

		UniqueSmtPtr(pType*&& _SetPointer_) noexcept
		:m_pointer(_SetPointer_)
		{
			_SetPointer_ = nullptr;
		};

		UniqueSmtPtr(UniqueSmtPtr<pType[]>& _OwnerSwap_) noexcept
		:m_pointer(_OwnerSwap_.m_pointer)
		{
			_OwnerSwap_.m_pointer = nullptr;
		};

		UniqueSmtPtr(UniqueSmtPtr<pType[]>&& _OwnerSwap_) noexcept
		:m_pointer(_OwnerSwap_.m_pointer)
		{
			_OwnerSwap_.m_pointer = nullptr;
		};

		~UniqueSmtPtr(void)
		{
			if(m_pointer != nullptr)
			{
				delete[] m_pointer;
			};
		};

		UniqueSmtPtr& operator =(pType*& _SetPointer_ ) noexcept
		{
			if(m_pointer != _SetPointer_)
			{
				delete[] m_pointer;
				m_pointer = _SetPointer_;
				_SetPointer_ = nullptr;
			};

			return (*this);
		};

		UniqueSmtPtr& operator =(pType*&& _SetPointer_) noexcept
		{
			if(m_pointer != _SetPointer_)
			{
				delete[] m_pointer;
				m_pointer = _SetPointer_;
				_SetPointer_ = nullptr;
			};

			return (*this);
		};

		UniqueSmtPtr& operator =(UniqueSmtPtr<pType[]>& _SetObj_) noexcept
		{
			if(m_pointer != _SetObj_.m_pointer)
			{
				delete[] m_pointer;
				m_pointer = _SetObj_.m_pointer;
				_SetObj_.m_pointer = nullptr;
			};

			return (*this);
		};

		UniqueSmtPtr& operator =(UniqueSmtPtr<pType[]>&& _SetObj_) noexcept
		{
			if(m_pointer != _SetObj_.m_pointer)
			{
				delete[] m_pointer;
				m_pointer = _SetObj_.m_pointer;
				_SetObj_.m_pointer = nullptr;
			};

			return (*this);
		};

		//Null なら True
		bool IsNullptr(void) noexcept
		{
			return (m_pointer == nullptr) ? true : false;
		};

		void OwnerRelease(void) noexcept
		{
			delete[] m_pointer;
			m_pointer = nullptr;
		};

		//生ポインタとして取得します。
		//所有権は手放します。(nullptrがセットされます。)
		pType* GetOwnerPointer(void)
		{
			pType* lp = m_pointer;
			m_pointer = nullptr;

			return lp;
		};

		SharedSmtPtr<pType[]> ChangeMangedPointer(void)
		{
			pType* lp = m_pointer;
			m_pointer = nullptr;

			return SharedSmtPtr<pType[]>(lp);
		};

		const pType& operator[](uint64_t index) const
		{
			return m_pointer[index];
		}

		pType& operator[](uint64_t index)
		{
			return m_pointer[index];
		};

		pType* operator ->(void)
		{
			return m_pointer;

		};

		pType& operator*(void) const
		{
			return (*m_pointer);
		};

	};


	//各Castの実装=======================================================
	template <class before, class after>
	bool SharedCast_Dynamic(SharedSmtPtr<before>& _src_, SharedSmtPtr<after>& _dst_)
	{
		after* l_po = dynamic_cast<after*>(_src_.m_Pointer);
		if(l_po == nullptr)
		{
			return false;
		};

		_dst_.ResetPointer(nullptr);
		_dst_.m_Pointer = l_po;
		_dst_.m_Count = _src_.m_Count;

		_dst_.AddRef();
		return true;
	};
	template <class before, class after>
	bool SharedCast_Dynamic(SharedSmtPtr<before[]>& _src_, SharedSmtPtr<after[]>& _dst_)
	{
		after* l_po = dynamic_cast<after*>(_src_.m_Pointer);
		if(l_po == nullptr)
		{
			return false;
		};

		_dst_.ResetPointer(nullptr);
		_dst_.m_Pointer = l_po;
		_dst_.m_Count = _src_.m_Count;

		_dst_.AddRef();
		return true;
	};
	template <class before, class after>
	void SharedCast_Reinterpret(SharedSmtPtr<before>& _src_, SharedSmtPtr<after>& _dst_)
	{
		_dst_.ResetPointer(nullptr);
		_dst_.m_Pointer = reinterpret_cast<after*>(_src_.m_Pointer);
		_dst_.m_Count = _src_.m_Count;

		_dst_.AddRef();
	};
	template <class before, class after>
	void SharedCast_Reinterpret(SharedSmtPtr<before[]>& _src_, SharedSmtPtr<after[]>& _dst_)
	{
		_dst_.ResetPointer(nullptr);
		_dst_.m_Pointer = reinterpret_cast<after*>(_src_.m_Pointer);
		_dst_.m_Count = _src_.m_Count;

		_dst_.AddRef();
	};

	//SRC側のポインタはnullptrになります。(唯一性によるキャスト移譲)
	template <class before, class after>
	bool UniqueCast_Dynamic(UniqueSmtPtr<before>& _src_, UniqueSmtPtr<after>& _dst_)
	{
		after* l_po = dynamic_cast<after*>(_src_.m_pointer);
		if(l_po == nullptr)
		{
			return false;
		};

		_dst_.OwnerRelease();
		_dst_.m_pointer = l_po;
		_src_.m_pointer = nullptr;
		return true;
	};
	template <class before, class after>
	bool UniqueCast_Dynamic( UniqueSmtPtr<before[]>& _src_,  UniqueSmtPtr<after[]>& _dst_)
	{
		after* l_po = dynamic_cast<after*>(_src_.m_pointer);
		if(l_po == nullptr)
		{
			return false;
		};

		_dst_.OwnerRelease();
		_dst_.m_pointer = l_po;
		_src_.m_pointer = nullptr;
		return true;
	};
	template <class before, class after>
	void UniqueCast_Reinterpret(UniqueSmtPtr<before>& _src_, UniqueSmtPtr<after>& _dst_)
	{
		_dst_.OwnerRelease();
		_dst_.m_pointer = reinterpret_cast<after*>(_dst_.m_ppinter);
		_src_.m_pointer = nullptr;
	};
	template <class before, class after>
	void UniqueCast_Reinterpret( UniqueSmtPtr<before[]>& _src_,  UniqueSmtPtr<after[]>& _dst_)
	{
		_dst_.OwnerRelease();
		_dst_.m_pointer = reinterpret_cast<after*>(_dst_.m_ppinter);
		_src_.m_pointer = nullptr;
	};
};




#endif /* SMARTPOINTER_SONIK_SMARTPOINTER_HPP_ */
