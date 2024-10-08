#ifndef WORKER_FUNCTOR_DEFINITION_SONIKLIBRARY_
#define WORKER_FUNCTOR_DEFINITION_SONIKLIBRARY_

#include "FunctionObjectSystemInterface.hpp"
#include "../SmartPointer/SonikSmartPointer.hpp"

//引数を10個まで取れるテンプレートクラスを定義します。
//それぞれクラスのメンバ関数を登録する場合において、ポインタのポインタ型は指定できません。
//指定しようとした場合は型不一致のコンパイルエラーが出ます。
//インスタンス作成時のテンプレートのTypeに対して、オブジェクトのポインタ型は指定できません。
//同じく指定しようとした場合は型不一致のコンパイルエラーが出ます。

//戻り値があるものについてはベースクラスは FunctionObjectSystemInterface となっています
//継承元がテンプレートクラスであるため、一括して扱うことはできません。
//ただし、戻り値の型が同一の場合は一括で扱うことが可能です。構文例は下記の通り
//FunctionSystemTemplate_Base<int>* 等... <型名>はたとえポインタであっても必要です。

//戻り値が無いものについてはベースクラスは FunctionObjectSystemTemplateInterface となっています。
//継承元は非テンプレートであるため、型は同一の物として一括で扱うことが可能です。

//基本的にインターフェースが提供するのはメソッドを実行する。という機能だけになります。

//Typeがvoid型の特殊化引数については、グローバル関数用の実装となります。
//ベースクラスは戻り値があるもの、無いもので上記二つと一緒です。
//いずれのクラスもローカル変数として生成し、スレッドに渡されてほしくないため、
//NEW関数を経由しての作成を強制しています。


namespace SonikLib
{

	//戻り値有り、引数10
	template<class Rtype, class Type, class Arg1_Val, class Arg2_Val, class Arg3_Val, class Arg4_Val, class Arg5_Val, class Arg6_Val, class Arg7_Val, class Arg8_Val, class Arg9_Val, class Arg10_Val, std::enable_if_t<!std::is_pointer_v<Type>, bool> = true>
	class Members_10_FuncR : public SonikFOSTemplateInterface<Rtype>
	{
	private:
		Arg1_Val  Arg1Val;
		Arg2_Val  Arg2Val;
		Arg3_Val  Arg3Val;
		Arg4_Val  Arg4Val;
		Arg5_Val  Arg5Val;
		Arg6_Val  Arg6Val;
		Arg7_Val  Arg7Val;
		Arg8_Val  Arg8Val;
		Arg9_Val  Arg9Val;
		Arg10_Val Arg10Val;

		SonikLib::SharedSmtPtr<Type> object_;
		Rtype (Type::*p_mfunc_)(Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val, Arg6_Val, Arg7_Val, Arg8_Val, Arg9_Val, Arg10_Val);

	private:
		Members_10_FuncR(void)
		:object_(nullptr)
		,p_mfunc_(nullptr)
		{
			//member value initialize only
		};

		Members_10_FuncR(Arg1_Val Val1_, Arg2_Val Val2_, Arg3_Val Val3_, Arg4_Val Val4_, Arg5_Val Val5_, Arg6_Val Val6_, Arg7_Val Val7_, Arg8_Val Val8_, Arg9_Val Val9_, Arg10_Val Val10_)
		:Arg1Val(Val1_)
		,Arg2Val(Val2_)
		,Arg3Val(Val3_)
		,Arg4Val(Val4_)
		,Arg5Val(Val5_)
		,Arg6Val(Val6_)
		,Arg7Val(Val7_)
		,Arg8Val(Val8_)
		,Arg9Val(Val9_)
		,Arg10Val(Val10_)
		,object_(nullptr)
		,p_mfunc_(nullptr)
		{
			//member value initialize only
		};

	public:
		~Members_10_FuncR(void)
		{
			if(this->Destroy_ == false)
			{
				//オブジェクト削除フラグがfalseなら勝手にdeleteしてはいけないので
				//ダミーを使ってスマートポインタからオーナー権限を除去し、dummyのdeleteを呼ばない。
				Type* _dymmy = nullptr;
				object_.GetOwnerPointer(_dymmy);
			};
		};

		//SharedSmtPtr指定
		inline static  SonikLib::SharedSmtPtr<SonikFOSTemplateInterface<Rtype>> New(SonikLib::SharedSmtPtr<Type> _SetObj_, Rtype (Type::*set_func)(Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val, Arg6_Val, Arg7_Val, Arg8_Val, Arg9_Val, Arg10_Val) , Arg1_Val Val1_, Arg2_Val Val2_, Arg3_Val Val3_, Arg4_Val Val4_, Arg5_Val Val5_, Arg6_Val Val6_, Arg7_Val Val7_, Arg8_Val Val8_, Arg9_Val Val9_, Arg10_Val Val10_, void* _allocate_ = nullptr)
		{
			Members_10_FuncR<Rtype, Type, Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val, Arg6_Val, Arg7_Val, Arg8_Val, Arg9_Val, Arg10_Val>* lp = nullptr;

			//三項演算子 　(条件) ? 真の時の処理 : 偽の時の処理
			//長いので縦にしただけ。つまり下記。
			//(条件)
			//? 真の時の処理
			//: 偽の時の処理
			(_allocate_ != nullptr)
			? lp = new(_allocate_) Members_10_FuncR<Rtype, Type, Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val, Arg6_Val, Arg7_Val, Arg8_Val, Arg9_Val, Arg10_Val>(Val1_, Val2_, Val3_, Val4_, Val5_, Val6_, Val7_, Val8_, Val9_, Val10_)
			: lp = new(std::nothrow) Members_10_FuncR<Rtype, Type, Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val, Arg6_Val, Arg7_Val, Arg8_Val, Arg9_Val, Arg10_Val>(Val1_, Val2_, Val3_, Val4_, Val5_, Val6_, Val7_, Val8_, Val9_, Val10_);

			if(lp == nullptr)
			{
				//失敗時はnullptrとして返却
				return SonikLib::SharedSmtPtr<SonikFOSTemplateInterface<Rtype>>();
			};

			lp->object_ = _SetObj_;
			lp->p_mfunc_ = set_func;

			return SonikLib::SharedSmtPtr<SonikFOSTemplateInterface<Rtype>>(lp);
		};
		//RawPointer指定
		inline static  SonikLib::SharedSmtPtr<SonikFOSTemplateInterface<Rtype>> New(Type* _SetObj_, Rtype (Type::*set_func)(Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val, Arg6_Val, Arg7_Val, Arg8_Val, Arg9_Val, Arg10_Val) , Arg1_Val Val1_, Arg2_Val Val2_, Arg3_Val Val3_, Arg4_Val Val4_, Arg5_Val Val5_, Arg6_Val Val6_, Arg7_Val Val7_, Arg8_Val Val8_, Arg9_Val Val9_, Arg10_Val Val10_, void* _allocate_ = nullptr)
		{
			Members_10_FuncR<Rtype, Type, Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val, Arg6_Val, Arg7_Val, Arg8_Val, Arg9_Val, Arg10_Val>* lp = nullptr;

			if(_SetObj_ == nullptr)
			{
				//Global版ではないのにnullptrを指定されたらそのまま返却。
				return SonikLib::SharedSmtPtr<SonikFOSTemplateInterface<Rtype>>();
			};

			//三項演算子 　(条件) ? 真の時の処理 : 偽の時の処理
			//長いので縦にしただけ。つまり下記。
			//(条件)
			//? 真の時の処理
			//: 偽の時の処理
			(_allocate_ != nullptr)
			? lp = new(_allocate_) Members_10_FuncR<Rtype, Type, Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val, Arg6_Val, Arg7_Val, Arg8_Val, Arg9_Val, Arg10_Val>(Val1_, Val2_, Val3_, Val4_, Val5_, Val6_, Val7_, Val8_, Val9_, Val10_)
			: lp = new(std::nothrow) Members_10_FuncR<Rtype, Type, Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val, Arg6_Val, Arg7_Val, Arg8_Val, Arg9_Val, Arg10_Val>(Val1_, Val2_, Val3_, Val4_, Val5_, Val6_, Val7_, Val8_, Val9_, Val10_);

			if(lp == nullptr)
			{
				//失敗時はnullptrとして返却
				return SonikLib::SharedSmtPtr<SonikFOSTemplateInterface<Rtype>>();
			};

			lp->object_ = SonikLib::SharedSmtPtr<Type>(_SetObj_);
			lp->p_mfunc_ = set_func;

			return SonikLib::SharedSmtPtr<SonikFOSTemplateInterface<Rtype>>(lp);
		};

		inline Rtype Run(void)
		{
			Rtype ret;

			if( object_.IsNullptr() )
			{

				return 0;
			};

			ret = (object_->*p_mfunc_)(Arg1Val, Arg2Val, Arg3Val, Arg4Val, Arg5Val, Arg6Val, Arg7Val, Arg8Val, Arg9Val, Arg10Val);
			this->MethodStatus = true;

			return ret;
		};

	};
	//戻り値無し、引数10
	template<class Type, class Arg1_Val, class Arg2_Val, class Arg3_Val, class Arg4_Val, class Arg5_Val, class Arg6_Val, class Arg7_Val, class Arg8_Val, class Arg9_Val, class Arg10_Val, std::enable_if_t<!std::is_pointer_v<Type>, bool> = true>
	class Members_10_Func : public SonikFOSInterface
	{
	private:
		Arg1_Val  Arg1Val;
		Arg2_Val  Arg2Val;
		Arg3_Val  Arg3Val;
		Arg4_Val  Arg4Val;
		Arg5_Val  Arg5Val;
		Arg6_Val  Arg6Val;
		Arg7_Val  Arg7Val;
		Arg8_Val  Arg8Val;
		Arg9_Val  Arg9Val;
		Arg10_Val Arg10Val;

		SonikLib::SharedSmtPtr<Type> object_;
		void (Type::*p_mfunc_)(Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val, Arg6_Val, Arg7_Val, Arg8_Val, Arg9_Val, Arg10_Val);

	private:
		Members_10_Func(void)
		:object_(nullptr)
		,p_mfunc_(nullptr)
		{
			//member value initliaze only
		};

		Members_10_Func(Arg1_Val Val1_, Arg2_Val Val2_, Arg3_Val Val3_, Arg4_Val Val4_, Arg5_Val Val5_, Arg6_Val Val6_, Arg7_Val Val7_, Arg8_Val Val8_, Arg9_Val Val9_, Arg10_Val Val10_)
		:Arg1Val(Val1_)
		,Arg2Val(Val2_)
		,Arg3Val(Val3_)
		,Arg4Val(Val4_)
		,Arg5Val(Val5_)
		,Arg6Val(Val6_)
		,Arg7Val(Val7_)
		,Arg8Val(Val8_)
		,Arg9Val(Val9_)
		,Arg10Val(Val10_)
		,object_(nullptr)
		,p_mfunc_(nullptr)
		{
			//member value initliaze only
		};

	public:
		~Members_10_Func(void)
		{
			if(this->Destroy_ == false)
			{
				//オブジェクト削除フラグがfalseなら勝手にdeleteしてはいけないので
				//ダミーを使ってスマートポインタからオーナー権限を除去し、dummyのdeleteを呼ばない。
				Type* _dymmy = nullptr;
				object_.GetOwnerPointer(_dymmy);
			};

		};

		//SharedSmtPtr指定
		inline static  SonikLib::SharedSmtPtr<SonikFOSInterface> New(SonikLib::SharedSmtPtr<Type> _SetObj_, void (Type::*set_func)(Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val, Arg6_Val, Arg7_Val, Arg8_Val, Arg9_Val, Arg10_Val) , Arg1_Val Val1_, Arg2_Val Val2_, Arg3_Val Val3_, Arg4_Val Val4_, Arg5_Val Val5_, Arg6_Val Val6_, Arg7_Val Val7_, Arg8_Val Val8_, Arg9_Val Val9_, Arg10_Val Val10_, void* _allocate_ = nullptr)
		{
			Members_10_Func<Type, Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val, Arg6_Val, Arg7_Val, Arg8_Val, Arg9_Val, Arg10_Val>* lp = nullptr;

			//三項演算子 　(条件) ? 真の時の処理 : 偽の時の処理
			//長いので縦にしただけ。つまり下記。
			//(条件)
			//? 真の時の処理
			//: 偽の時の処理
			(_allocate_ != nullptr)
			? lp = new(_allocate_) Members_10_Func<Type, Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val, Arg6_Val, Arg7_Val, Arg8_Val, Arg9_Val, Arg10_Val>(Val1_, Val2_, Val3_, Val4_, Val5_, Val6_, Val7_, Val8_, Val9_, Val10_)
			: lp = new(std::nothrow) Members_10_Func<Type, Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val, Arg6_Val, Arg7_Val, Arg8_Val, Arg9_Val, Arg10_Val>(Val1_, Val2_, Val3_, Val4_, Val5_, Val6_, Val7_, Val8_, Val9_, Val10_);

			if(lp == nullptr)
			{
				//失敗時はnullptrとして返却
				return SonikLib::SharedSmtPtr<SonikFOSInterface>();
			};

			lp->object_ = _SetObj_;
			lp->p_mfunc_ = set_func;

			return SonikLib::SharedSmtPtr<SonikFOSInterface>(lp);
		};
		//RawPointer指定
		inline static  SonikLib::SharedSmtPtr<SonikFOSInterface> New(Type* _SetObj_, void (Type::*set_func)(Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val, Arg6_Val, Arg7_Val, Arg8_Val, Arg9_Val, Arg10_Val) , Arg1_Val Val1_, Arg2_Val Val2_, Arg3_Val Val3_, Arg4_Val Val4_, Arg5_Val Val5_, Arg6_Val Val6_, Arg7_Val Val7_, Arg8_Val Val8_, Arg9_Val Val9_, Arg10_Val Val10_, void* _allocate_ = nullptr)
		{
			Members_10_Func<Type, Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val, Arg6_Val, Arg7_Val, Arg8_Val, Arg9_Val, Arg10_Val>* lp = nullptr;

			if(_SetObj_ == nullptr)
			{
				//Global版ではないのにnullptrを指定されたらそのまま返却。
				return  SonikLib::SharedSmtPtr<SonikFOSInterface>();
			};

			//三項演算子 　(条件) ? 真の時の処理 : 偽の時の処理
			//長いので縦にしただけ。つまり下記。
			//(条件)
			//? 真の時の処理
			//: 偽の時の処理
			(_allocate_ != nullptr)
			? lp = new(_allocate_) Members_10_Func<Type, Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val, Arg6_Val, Arg7_Val, Arg8_Val, Arg9_Val, Arg10_Val>(Val1_, Val2_, Val3_, Val4_, Val5_, Val6_, Val7_, Val8_, Val9_, Val10_)
			: lp = new(std::nothrow) Members_10_Func<Type, Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val, Arg6_Val, Arg7_Val, Arg8_Val, Arg9_Val, Arg10_Val>(Val1_, Val2_, Val3_, Val4_, Val5_, Val6_, Val7_, Val8_, Val9_, Val10_);

			if(lp == nullptr)
			{
				//失敗時はnullptrとして返却
				return SonikLib::SharedSmtPtr<SonikFOSInterface>();
			};

			lp->object_ = SonikLib::SharedSmtPtr<Type>(_SetObj_);
			lp->p_mfunc_ = set_func;

			return SonikLib::SharedSmtPtr<SonikFOSInterface>(lp);
		};

		inline void Run(void)
		{
			if( object_.IsNullptr() )
			{
				return;
			};

			(object_->*p_mfunc_)(Arg1Val, Arg2Val, Arg3Val, Arg4Val, Arg5Val, Arg6Val, Arg7Val, Arg8Val, Arg9Val, Arg10Val);
			MethodStatus = true;

		};

	};
	//戻り値有り、引数10 グローバル用
	template<class Rtype, class Arg1_Val, class Arg2_Val, class Arg3_Val, class Arg4_Val, class Arg5_Val, class Arg6_Val, class Arg7_Val, class Arg8_Val, class Arg9_Val, class Arg10_Val>
	class Members_10_FuncRG : public SonikFOSTemplateInterface<Rtype>
	{
	private:
		Arg1_Val  Arg1Val;
		Arg2_Val  Arg2Val;
		Arg3_Val  Arg3Val;
		Arg4_Val  Arg4Val;
		Arg5_Val  Arg5Val;
		Arg6_Val  Arg6Val;
		Arg7_Val  Arg7Val;
		Arg8_Val  Arg8Val;
		Arg9_Val  Arg9Val;
		Arg10_Val Arg10Val;

		Rtype (*p_mfunc_)(Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val, Arg6_Val, Arg7_Val, Arg8_Val, Arg9_Val, Arg10_Val);

	private:
		Members_10_FuncRG(void)
		:p_mfunc_(nullptr)
		{
			//member value initialize only
		};

		Members_10_FuncRG(Arg1_Val Val1_, Arg2_Val Val2_, Arg3_Val Val3_, Arg4_Val Val4_, Arg5_Val Val5_, Arg6_Val Val6_, Arg7_Val Val7_, Arg8_Val Val8_, Arg9_Val Val9_, Arg10_Val Val10_)
		:Arg1Val(Val1_)
		,Arg2Val(Val2_)
		,Arg3Val(Val3_)
		,Arg4Val(Val4_)
		,Arg5Val(Val5_)
		,Arg6Val(Val6_)
		,Arg7Val(Val7_)
		,Arg8Val(Val8_)
		,Arg9Val(Val9_)
		,Arg10Val(Val10_)
		,p_mfunc_(nullptr)
		{
			//member value initialize only
		};

	public:
		~Members_10_FuncRG(void)
		{
			//no process;
		};

		//グローバル関数指定なので、クラス指定のようにshared版とか無い。
		inline static  SonikLib::SharedSmtPtr<SonikFOSTemplateInterface<Rtype>> New(Rtype (*set_func)(Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val, Arg6_Val, Arg7_Val, Arg8_Val, Arg9_Val, Arg10_Val) , Arg1_Val Val1_, Arg2_Val Val2_, Arg3_Val Val3_, Arg4_Val Val4_, Arg5_Val Val5_, Arg6_Val Val6_, Arg7_Val Val7_, Arg8_Val Val8_, Arg9_Val Val9_, Arg10_Val Val10_, void* _allocate_ = nullptr)
		{
			Members_10_FuncRG<Rtype, Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val, Arg6_Val, Arg7_Val, Arg8_Val, Arg9_Val, Arg10_Val>* lp = nullptr;

			//三項演算子 　(条件) ? 真の時の処理 : 偽の時の処理
			//長いので縦にしただけ。つまり下記。
			//(条件)
			//? 真の時の処理
			//: 偽の時の処理
			(_allocate_ != nullptr)
			? lp = new(_allocate_) Members_10_FuncRG<Rtype, Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val, Arg6_Val, Arg7_Val, Arg8_Val, Arg9_Val, Arg10_Val>(Val1_, Val2_, Val3_, Val4_, Val5_, Val6_, Val7_, Val8_, Val9_, Val10_)
			: lp = new(std::nothrow) Members_10_FuncRG<Rtype, Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val, Arg6_Val, Arg7_Val, Arg8_Val, Arg9_Val, Arg10_Val>(Val1_, Val2_, Val3_, Val4_, Val5_, Val6_, Val7_, Val8_, Val9_, Val10_);

			if(lp == nullptr)
			{
				//失敗時はnullptrとして返却
				return SonikLib::SharedSmtPtr<SonikFOSTemplateInterface<Rtype>>();
			};

			lp->p_mfunc_ = set_func;

			return SonikLib::SharedSmtPtr<SonikFOSTemplateInterface<Rtype>>(lp);
		};

		inline Rtype Run(void)
		{
			Rtype ret;

			ret = (*p_mfunc_)(Arg1Val, Arg2Val, Arg3Val, Arg4Val, Arg5Val, Arg6Val, Arg7Val, Arg8Val, Arg9Val, Arg10Val);
			this->MethodStatus = true;

			return ret;
		};

	};
	//戻り値無し、引数10 グローバル用
	template<class Arg1_Val, class Arg2_Val, class Arg3_Val, class Arg4_Val, class Arg5_Val, class Arg6_Val, class Arg7_Val, class Arg8_Val, class Arg9_Val, class Arg10_Val>
	class Members_10_FuncG : public SonikFOSInterface
	{
	private:
		Arg1_Val  Arg1Val;
		Arg2_Val  Arg2Val;
		Arg3_Val  Arg3Val;
		Arg4_Val  Arg4Val;
		Arg5_Val  Arg5Val;
		Arg6_Val  Arg6Val;
		Arg7_Val  Arg7Val;
		Arg8_Val  Arg8Val;
		Arg9_Val  Arg9Val;
		Arg10_Val Arg10Val;

		void (*p_mfunc_)(Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val, Arg6_Val, Arg7_Val, Arg8_Val, Arg9_Val, Arg10_Val);

	private:
		Members_10_FuncG(void)
		:p_mfunc_(nullptr)
		{
			//member value initialize only
		};

		Members_10_FuncG(Arg1_Val Val1_, Arg2_Val Val2_, Arg3_Val Val3_, Arg4_Val Val4_, Arg5_Val Val5_, Arg6_Val Val6_, Arg7_Val Val7_, Arg8_Val Val8_, Arg9_Val Val9_, Arg10_Val Val10_)
		:Arg1Val(Val1_)
		,Arg2Val(Val2_)
		,Arg3Val(Val3_)
		,Arg4Val(Val4_)
		,Arg5Val(Val5_)
		,Arg6Val(Val6_)
		,Arg7Val(Val7_)
		,Arg8Val(Val8_)
		,Arg9Val(Val9_)
		,Arg10Val(Val10_)
		,p_mfunc_(nullptr)
		{
			//member value initialize only
		};

	public:
		~Members_10_FuncG(void)
		{
			//no process;
		};

		//グローバル関数指定なので、クラス指定のようにshared版とか無い。
		inline static  SonikLib::SharedSmtPtr<SonikFOSInterface> New(void (*set_func)(Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val, Arg6_Val, Arg7_Val, Arg8_Val, Arg9_Val, Arg10_Val) , Arg1_Val Val1_, Arg2_Val Val2_, Arg3_Val Val3_, Arg4_Val Val4_, Arg5_Val Val5_, Arg6_Val Val6_, Arg7_Val Val7_, Arg8_Val Val8_, Arg9_Val Val9_, Arg10_Val Val10_, void* _allocate_ = nullptr)
		{
			Members_10_FuncG< Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val, Arg6_Val, Arg7_Val, Arg8_Val, Arg9_Val, Arg10_Val>* lp = nullptr;

			//三項演算子 　(条件) ? 真の時の処理 : 偽の時の処理
			//長いので縦にしただけ。つまり下記。
			//(条件)
			//? 真の時の処理
			//: 偽の時の処理
			(_allocate_ != nullptr)
			? lp = new(_allocate_) Members_10_FuncG<Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val, Arg6_Val, Arg7_Val, Arg8_Val, Arg9_Val, Arg10_Val>(Val1_, Val2_, Val3_, Val4_, Val5_, Val6_, Val7_, Val8_, Val9_, Val10_)
			: lp = new(std::nothrow) Members_10_FuncG<Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val, Arg6_Val, Arg7_Val, Arg8_Val, Arg9_Val, Arg10_Val>(Val1_, Val2_, Val3_, Val4_, Val5_, Val6_, Val7_, Val8_, Val9_, Val10_);

			if(lp == nullptr)
			{
				//失敗時はnullptrとして返却
				return SonikLib::SharedSmtPtr<SonikFOSInterface>();
			};

			lp->p_mfunc_ = set_func;

			return SonikLib::SharedSmtPtr<SonikFOSInterface>(lp);
		};

		inline void Run(void)
		{
			(*p_mfunc_)(Arg1Val, Arg2Val, Arg3Val, Arg4Val, Arg5Val, Arg6Val, Arg7Val, Arg8Val, Arg9Val, Arg10Val);
			MethodStatus = true;
		};

	};

	//戻り値有り、引数9
	template<class Rtype, class Type, class Arg1_Val, class Arg2_Val, class Arg3_Val, class Arg4_Val, class Arg5_Val, class Arg6_Val, class Arg7_Val, class Arg8_Val, class Arg9_Val, std::enable_if_t<!std::is_pointer_v<Type>, bool> = true>
	class Members_9_FuncR : public SonikFOSTemplateInterface<Rtype>
	{
	private:
		Arg1_Val  Arg1Val;
		Arg2_Val  Arg2Val;
		Arg3_Val  Arg3Val;
		Arg4_Val  Arg4Val;
		Arg5_Val  Arg5Val;
		Arg6_Val  Arg6Val;
		Arg7_Val  Arg7Val;
		Arg8_Val  Arg8Val;
		Arg9_Val  Arg9Val;

		SonikLib::SharedSmtPtr<Type> object_;
		Rtype (Type::*p_mfunc_)(Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val, Arg6_Val, Arg7_Val, Arg8_Val, Arg9_Val);

	private:
		Members_9_FuncR(void)
		:object_(nullptr)
		,p_mfunc_(nullptr)
		{
			//member value initialize only
		};

		Members_9_FuncR(Arg1_Val Val1_, Arg2_Val Val2_, Arg3_Val Val3_, Arg4_Val Val4_, Arg5_Val Val5_, Arg6_Val Val6_, Arg7_Val Val7_, Arg8_Val Val8_, Arg9_Val Val9_)
		:Arg1Val(Val1_)
		,Arg2Val(Val2_)
		,Arg3Val(Val3_)
		,Arg4Val(Val4_)
		,Arg5Val(Val5_)
		,Arg6Val(Val6_)
		,Arg7Val(Val7_)
		,Arg8Val(Val8_)
		,Arg9Val(Val9_)
		,object_(nullptr)
		,p_mfunc_(nullptr)
		{
			//member value initialize only
		};

	public:
		~Members_9_FuncR(void)
		{
			if(this->Destroy_ == false)
			{
				//オブジェクト削除フラグがfalseなら勝手にdeleteしてはいけないので
				//ダミーを使ってスマートポインタからオーナー権限を除去し、dummyのdeleteを呼ばない。
				Type* _dymmy = nullptr;
				object_.GetOwnerPointer(_dymmy);
			};

		};

		//SharedSmtPtr指定
		inline static  SonikLib::SharedSmtPtr<SonikFOSTemplateInterface<Rtype>> New(SonikLib::SharedSmtPtr<Type> _SetObj_, Rtype (Type::*set_func)(Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val, Arg6_Val, Arg7_Val, Arg8_Val, Arg9_Val) , Arg1_Val Val1_, Arg2_Val Val2_, Arg3_Val Val3_, Arg4_Val Val4_, Arg5_Val Val5_, Arg6_Val Val6_, Arg7_Val Val7_, Arg8_Val Val8_, Arg9_Val Val9_, void* _allocate_ = nullptr)
		{
			Members_9_FuncR<Rtype, Type, Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val, Arg6_Val, Arg7_Val, Arg8_Val, Arg9_Val>* lp = nullptr;

			//三項演算子 　(条件) ? 真の時の処理 : 偽の時の処理
			//長いので縦にしただけ。つまり下記。
			//(条件)
			//? 真の時の処理
			//: 偽の時の処理
			(_allocate_ != nullptr)
			? lp = new(_allocate_) Members_9_FuncR<Rtype, Type, Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val, Arg6_Val, Arg7_Val, Arg8_Val, Arg9_Val>(Val1_, Val2_, Val3_, Val4_, Val5_, Val6_, Val7_, Val8_, Val9_)
			: lp = new(std::nothrow) Members_9_FuncR<Rtype, Type, Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val, Arg6_Val, Arg7_Val, Arg8_Val, Arg9_Val>(Val1_, Val2_, Val3_, Val4_, Val5_, Val6_, Val7_, Val8_, Val9_);

			if(lp == nullptr)
			{
				//失敗時はnullptrとして返却
				return SonikLib::SharedSmtPtr<SonikFOSTemplateInterface<Rtype>>();
			};

			lp->object_ = _SetObj_;
			lp->p_mfunc_ = set_func;

			return SonikLib::SharedSmtPtr<SonikFOSTemplateInterface<Rtype>>(lp);
		};
		//RawPointer指定
		inline static  SonikLib::SharedSmtPtr<SonikFOSTemplateInterface<Rtype>> New(Type* _SetObj_, Rtype (Type::*set_func)(Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val, Arg6_Val, Arg7_Val, Arg8_Val, Arg9_Val) , Arg1_Val Val1_, Arg2_Val Val2_, Arg3_Val Val3_, Arg4_Val Val4_, Arg5_Val Val5_, Arg6_Val Val6_, Arg7_Val Val7_, Arg8_Val Val8_, Arg9_Val Val9_, void* _allocate_ = nullptr)
		{
			Members_9_FuncR<Rtype, Type, Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val, Arg6_Val, Arg7_Val, Arg8_Val, Arg9_Val>* lp = nullptr;

			if(_SetObj_ == nullptr)
			{
				//Global版ではないのにnullptrを指定されたらそのまま返却。
				return SonikLib::SharedSmtPtr<SonikFOSTemplateInterface<Rtype>>();
			};

			//三項演算子 　(条件) ? 真の時の処理 : 偽の時の処理
			//長いので縦にしただけ。つまり下記。
			//(条件)
			//? 真の時の処理
			//: 偽の時の処理
			(_allocate_ != nullptr)
			? lp = new(_allocate_) Members_9_FuncR<Rtype, Type, Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val, Arg6_Val, Arg7_Val, Arg8_Val, Arg9_Val>(Val1_, Val2_, Val3_, Val4_, Val5_, Val6_, Val7_, Val8_, Val9_)
			: lp = new(std::nothrow) Members_9_FuncR<Rtype, Type, Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val, Arg6_Val, Arg7_Val, Arg8_Val, Arg9_Val>(Val1_, Val2_, Val3_, Val4_, Val5_, Val6_, Val7_, Val8_, Val9_);

			if(lp == nullptr)
			{
				//失敗時はnullptrとして返却
				return SonikLib::SharedSmtPtr<SonikFOSTemplateInterface<Rtype>>();
			};

			lp->object_ = SonikLib::SharedSmtPtr<Type>(_SetObj_);
			lp->p_mfunc_ = set_func;

			return SonikLib::SharedSmtPtr<SonikFOSTemplateInterface<Rtype>>(lp);
		};

		inline Rtype Run(void)
		{
			Rtype ret;

			if( object_.IsNullptr())
			{
				return 0;
			};

			ret = (object_->*p_mfunc_)(Arg1Val, Arg2Val, Arg3Val, Arg4Val, Arg5Val, Arg6Val, Arg7Val, Arg8Val, Arg9Val);
			this->MethodStatus = true;

			return ret;
		};

	};
	//戻り値無し、引数9
	template<class Type, class Arg1_Val, class Arg2_Val, class Arg3_Val, class Arg4_Val, class Arg5_Val, class Arg6_Val, class Arg7_Val, class Arg8_Val, class Arg9_Val, std::enable_if_t<!std::is_pointer_v<Type>, bool> = true>
	class Members_9_Func : public SonikFOSInterface
	{
	private:
		Arg1_Val  Arg1Val;
		Arg2_Val  Arg2Val;
		Arg3_Val  Arg3Val;
		Arg4_Val  Arg4Val;
		Arg5_Val  Arg5Val;
		Arg6_Val  Arg6Val;
		Arg7_Val  Arg7Val;
		Arg8_Val  Arg8Val;
		Arg9_Val  Arg9Val;

		SonikLib::SharedSmtPtr<Type> object_;
		void (Type::*p_mfunc_)(Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val, Arg6_Val, Arg7_Val, Arg8_Val, Arg9_Val);

	private:
		Members_9_Func(void)
		:object_(nullptr)
		,p_mfunc_(nullptr)
		{
			//member value initialize only
		};

		Members_9_Func(Arg1_Val Val1_, Arg2_Val Val2_, Arg3_Val Val3_, Arg4_Val Val4_, Arg5_Val Val5_, Arg6_Val Val6_, Arg7_Val Val7_, Arg8_Val Val8_, Arg9_Val Val9_)
		:Arg1Val(Val1_)
		,Arg2Val(Val2_)
		,Arg3Val(Val3_)
		,Arg4Val(Val4_)
		,Arg5Val(Val5_)
		,Arg6Val(Val6_)
		,Arg7Val(Val7_)
		,Arg8Val(Val8_)
		,Arg9Val(Val9_)
		,object_(nullptr)
		,p_mfunc_(nullptr)
		{
			//member value initialize only
		};

	public:
		~Members_9_Func(void)
		{
			if(this->Destroy_ == false)
			{
				//オブジェクト削除フラグがfalseなら勝手にdeleteしてはいけないので
				//ダミーを使ってスマートポインタからオーナー権限を除去し、dummyのdeleteを呼ばない。
				Type* _dymmy = nullptr;
				object_.GetOwnerPointer(_dymmy);
			};

		};

		//SharedSmtPtr指定
		inline static  SonikLib::SharedSmtPtr<SonikFOSInterface> New(SonikLib::SharedSmtPtr<Type> _SetObj_, void (Type::*set_func)(Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val, Arg6_Val, Arg7_Val, Arg8_Val, Arg9_Val) , Arg1_Val Val1_, Arg2_Val Val2_, Arg3_Val Val3_, Arg4_Val Val4_, Arg5_Val Val5_, Arg6_Val Val6_, Arg7_Val Val7_, Arg8_Val Val8_, Arg9_Val Val9_, void* _allocate_ = nullptr)
		{
			Members_9_Func<Type, Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val, Arg6_Val, Arg7_Val, Arg8_Val, Arg9_Val>* lp = nullptr;

			//三項演算子 　(条件) ? 真の時の処理 : 偽の時の処理
			//長いので縦にしただけ。つまり下記。
			//(条件)
			//? 真の時の処理
			//: 偽の時の処理
			(_allocate_ != nullptr)
			? lp = new(_allocate_) Members_9_Func<Type, Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val, Arg6_Val, Arg7_Val, Arg8_Val, Arg9_Val>(Val1_, Val2_, Val3_, Val4_, Val5_, Val6_, Val7_, Val8_, Val9_)
			: lp = new(std::nothrow) Members_9_Func<Type, Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val, Arg6_Val, Arg7_Val, Arg8_Val, Arg9_Val>(Val1_, Val2_, Val3_, Val4_, Val5_, Val6_, Val7_, Val8_, Val9_);

			if(lp == nullptr)
			{
				//失敗時はnullptrとして返却
				return SonikLib::SharedSmtPtr<SonikFOSInterface>();
			};

			lp->object_ = _SetObj_;
			lp->p_mfunc_ = set_func;

			return SonikLib::SharedSmtPtr<SonikFOSInterface>(lp);
		};
		//RawPointer指定
		inline static  SonikLib::SharedSmtPtr<SonikFOSInterface> New(Type* _SetObj_, void (Type::*set_func)(Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val, Arg6_Val, Arg7_Val, Arg8_Val, Arg9_Val) , Arg1_Val Val1_, Arg2_Val Val2_, Arg3_Val Val3_, Arg4_Val Val4_, Arg5_Val Val5_, Arg6_Val Val6_, Arg7_Val Val7_, Arg8_Val Val8_, Arg9_Val Val9_, void* _allocate_ = nullptr)
		{
			Members_9_Func<Type, Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val, Arg6_Val, Arg7_Val, Arg8_Val, Arg9_Val>* lp = nullptr;

			if(_SetObj_ == nullptr)
			{
				//Global版ではないのにnullptrを指定されたらそのまま返却。
				return  SonikLib::SharedSmtPtr<SonikFOSInterface>();
			};

			//三項演算子 　(条件) ? 真の時の処理 : 偽の時の処理
			//長いので縦にしただけ。つまり下記。
			//(条件)
			//? 真の時の処理
			//: 偽の時の処理
			(_allocate_ != nullptr)
			? lp = new(_allocate_) Members_9_Func<Type, Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val, Arg6_Val, Arg7_Val, Arg8_Val, Arg9_Val>(Val1_, Val2_, Val3_, Val4_, Val5_, Val6_, Val7_, Val8_, Val9_)
			: lp = new(std::nothrow) Members_9_Func<Type, Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val, Arg6_Val, Arg7_Val, Arg8_Val, Arg9_Val>(Val1_, Val2_, Val3_, Val4_, Val5_, Val6_, Val7_, Val8_, Val9_);

			if(lp == nullptr)
			{
				//失敗時はnullptrとして返却
				return SonikLib::SharedSmtPtr<SonikFOSInterface>();
			};

			lp->object_ = SonikLib::SharedSmtPtr<Type>(_SetObj_);
			lp->p_mfunc_ = set_func;

			return SonikLib::SharedSmtPtr<SonikFOSInterface>(lp);
		};

		inline void Run(void)
		{
			if( object_.IsNullptr())
			{
				return;
			};

			(object_->*p_mfunc_)(Arg1Val, Arg2Val, Arg3Val, Arg4Val, Arg5Val, Arg6Val, Arg7Val, Arg8Val, Arg9Val);
			MethodStatus = true;

		};

	};
	//戻り値有り、引数9 グローバル用
	template<class Rtype, class Arg1_Val, class Arg2_Val, class Arg3_Val, class Arg4_Val, class Arg5_Val, class Arg6_Val, class Arg7_Val, class Arg8_Val, class Arg9_Val>
	class Members_9_FuncRG : public SonikFOSTemplateInterface<Rtype>
	{
	private:
		Arg1_Val  Arg1Val;
		Arg2_Val  Arg2Val;
		Arg3_Val  Arg3Val;
		Arg4_Val  Arg4Val;
		Arg5_Val  Arg5Val;
		Arg6_Val  Arg6Val;
		Arg7_Val  Arg7Val;
		Arg8_Val  Arg8Val;
		Arg9_Val  Arg9Val;

		Rtype (*p_mfunc_)(Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val, Arg6_Val, Arg7_Val, Arg8_Val, Arg9_Val);

	private:
		Members_9_FuncRG(void)
		:p_mfunc_(nullptr)
		{
			//member value initialize only
		};

		Members_9_FuncRG(Arg1_Val Val1_, Arg2_Val Val2_, Arg3_Val Val3_, Arg4_Val Val4_, Arg5_Val Val5_, Arg6_Val Val6_, Arg7_Val Val7_, Arg8_Val Val8_, Arg9_Val Val9_)
		:Arg1Val(Val1_)
		,Arg2Val(Val2_)
		,Arg3Val(Val3_)
		,Arg4Val(Val4_)
		,Arg5Val(Val5_)
		,Arg6Val(Val6_)
		,Arg7Val(Val7_)
		,Arg8Val(Val8_)
		,Arg9Val(Val9_)
		,p_mfunc_(nullptr)
		{
			//member value initialize only
		};

	public:
		~Members_9_FuncRG(void)
		{
			//no process;
		};

		//グローバル関数指定なので、クラス指定のようにshared版とか無い。
		inline static  SonikLib::SharedSmtPtr<SonikFOSTemplateInterface<Rtype>> New(Rtype (*set_func)(Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val, Arg6_Val, Arg7_Val, Arg8_Val, Arg9_Val) , Arg1_Val Val1_, Arg2_Val Val2_, Arg3_Val Val3_, Arg4_Val Val4_, Arg5_Val Val5_, Arg6_Val Val6_, Arg7_Val Val7_, Arg8_Val Val8_, Arg9_Val Val9_, void* _allocate_ = nullptr)
		{
			Members_9_FuncRG<Rtype, Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val, Arg6_Val, Arg7_Val, Arg8_Val, Arg9_Val>* lp = nullptr;

			//三項演算子 　(条件) ? 真の時の処理 : 偽の時の処理
			//長いので縦にしただけ。つまり下記。
			//(条件)
			//? 真の時の処理
			//: 偽の時の処理
			(_allocate_ != nullptr)
			? lp = new(_allocate_) Members_9_FuncRG<Rtype, Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val, Arg6_Val, Arg7_Val, Arg8_Val, Arg9_Val>(Val1_, Val2_, Val3_, Val4_, Val5_, Val6_, Val7_, Val8_, Val9_)
			: lp = new(std::nothrow) Members_9_FuncRG<Rtype, Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val, Arg6_Val, Arg7_Val, Arg8_Val, Arg9_Val>(Val1_, Val2_, Val3_, Val4_, Val5_, Val6_, Val7_, Val8_, Val9_);

			if(lp == nullptr)
			{
				//失敗時はnullptrとして返却
				return SonikLib::SharedSmtPtr<SonikFOSTemplateInterface<Rtype>>();
			};

			lp->p_mfunc_ = set_func;

			return SonikLib::SharedSmtPtr<SonikFOSTemplateInterface<Rtype>>(lp);
		};

		inline Rtype Run(void)
		{
			Rtype ret;

			ret = (*p_mfunc_)(Arg1Val, Arg2Val, Arg3Val, Arg4Val, Arg5Val, Arg6Val, Arg7Val, Arg8Val, Arg9Val);
			this->MethodStatus = true;

			return ret;
		};

	};
	//戻り値無し、引数9 グローバル用
	template<class Arg1_Val, class Arg2_Val, class Arg3_Val, class Arg4_Val, class Arg5_Val, class Arg6_Val, class Arg7_Val, class Arg8_Val, class Arg9_Val>
	class Members_9_FuncG : public SonikFOSInterface
	{
	private:
		Arg1_Val  Arg1Val;
		Arg2_Val  Arg2Val;
		Arg3_Val  Arg3Val;
		Arg4_Val  Arg4Val;
		Arg5_Val  Arg5Val;
		Arg6_Val  Arg6Val;
		Arg7_Val  Arg7Val;
		Arg8_Val  Arg8Val;
		Arg9_Val  Arg9Val;

		void (*p_mfunc_)(Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val, Arg6_Val, Arg7_Val, Arg8_Val, Arg9_Val);

	private:
		Members_9_FuncG(void)
		:p_mfunc_(nullptr)
		{
			//member value initialize only
		};

		Members_9_FuncG(Arg1_Val Val1_, Arg2_Val Val2_, Arg3_Val Val3_, Arg4_Val Val4_, Arg5_Val Val5_, Arg6_Val Val6_, Arg7_Val Val7_, Arg8_Val Val8_, Arg9_Val Val9_)
		:Arg1Val(Val1_)
		,Arg2Val(Val1_)
		,Arg3Val(Val1_)
		,Arg4Val(Val1_)
		,Arg5Val(Val1_)
		,Arg6Val(Val1_)
		,Arg7Val(Val1_)
		,Arg8Val(Val1_)
		,Arg9Val(Val1_)
		,p_mfunc_(nullptr)
		{
			//member value initialize only
		};

	public:
		~Members_9_FuncG(void)
		{
			//no process;
		};

		//グローバル関数指定なので、クラス指定のようにshared版とか無い。
		inline static  SonikLib::SharedSmtPtr<SonikFOSInterface> New(void (*set_func)(Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val, Arg6_Val, Arg7_Val, Arg8_Val, Arg9_Val) , Arg1_Val Val1_, Arg2_Val Val2_, Arg3_Val Val3_, Arg4_Val Val4_, Arg5_Val Val5_, Arg6_Val Val6_, Arg7_Val Val7_, Arg8_Val Val8_, Arg9_Val Val9_, void* _allocate_ = nullptr)
		{
			Members_9_FuncG< Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val, Arg6_Val, Arg7_Val, Arg8_Val, Arg9_Val>* lp = nullptr;

			//三項演算子 　(条件) ? 真の時の処理 : 偽の時の処理
			//長いので縦にしただけ。つまり下記。
			//(条件)
			//? 真の時の処理
			//: 偽の時の処理
			(_allocate_ != nullptr)
			? lp = new(_allocate_) Members_9_FuncG< Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val, Arg6_Val, Arg7_Val, Arg8_Val, Arg9_Val>(Val1_, Val2_, Val3_, Val4_, Val5_, Val6_, Val7_, Val8_, Val9_)
			: lp = new(std::nothrow) Members_9_FuncG< Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val, Arg6_Val, Arg7_Val, Arg8_Val, Arg9_Val>(Val1_, Val2_, Val3_, Val4_, Val5_, Val6_, Val7_, Val8_, Val9_);

			if(lp == nullptr)
			{
				//失敗時はnullptrとして返却
				return SonikLib::SharedSmtPtr<SonikFOSInterface>();
			};

			lp->p_mfunc_ = set_func;

			return SonikLib::SharedSmtPtr<SonikFOSInterface>(lp);
		};

		inline virtual void Run(void)
		{

			(*p_mfunc_)(Arg1Val, Arg2Val, Arg3Val, Arg4Val, Arg5Val, Arg6Val, Arg7Val, Arg8Val, Arg9Val);

		};

	};

	//戻り値有り、引数8
	template<class Rtype, class Type, class Arg1_Val, class Arg2_Val, class Arg3_Val, class Arg4_Val, class Arg5_Val, class Arg6_Val, class Arg7_Val, class Arg8_Val, std::enable_if_t<!std::is_pointer_v<Type>, bool> = true>
	class Members_8_FuncR : public SonikFOSTemplateInterface<Rtype>
	{
	private:
		Arg1_Val  Arg1Val;
		Arg2_Val  Arg2Val;
		Arg3_Val  Arg3Val;
		Arg4_Val  Arg4Val;
		Arg5_Val  Arg5Val;
		Arg6_Val  Arg6Val;
		Arg7_Val  Arg7Val;
		Arg8_Val  Arg8Val;

		SonikLib::SharedSmtPtr<Type> object_;
		Rtype (Type::*p_mfunc_)(Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val, Arg6_Val, Arg7_Val, Arg8_Val);

	private:
		Members_8_FuncR(void)
		:object_(0)
		,p_mfunc_(0)
		{
			//member value initialize only
		};

		Members_8_FuncR(Arg1_Val Val1_, Arg2_Val Val2_, Arg3_Val Val3_, Arg4_Val Val4_, Arg5_Val Val5_, Arg6_Val Val6_, Arg7_Val Val7_, Arg8_Val Val8_)
		:Arg1Val(Val1_)
		,Arg2Val(Val2_)
		,Arg3Val(Val3_)
		,Arg4Val(Val4_)
		,Arg5Val(Val5_)
		,Arg6Val(Val6_)
		,Arg7Val(Val7_)
		,Arg8Val(Val8_)
		,object_(0)
		,p_mfunc_(0)
		{
			//member value initialize only
		};

	public:
		~Members_8_FuncR(void)
		{
			if(this->Destroy_ == false)
			{
				//オブジェクト削除フラグがfalseなら勝手にdeleteしてはいけないので
				//ダミーを使ってスマートポインタからオーナー権限を除去し、dummyのdeleteを呼ばない。
				Type* _dymmy = nullptr;
				object_.GetOwnerPointer(_dymmy);
			};

		};

		//SharedSmtPtr指定
		inline static  SonikLib::SharedSmtPtr<SonikFOSTemplateInterface<Rtype>> New(SonikLib::SharedSmtPtr<Type> _SetObj_, Rtype (Type::*set_func)(Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val, Arg6_Val, Arg7_Val, Arg8_Val) , Arg1_Val Val1_, Arg2_Val Val2_, Arg3_Val Val3_, Arg4_Val Val4_, Arg5_Val Val5_, Arg6_Val Val6_, Arg7_Val Val7_, Arg8_Val Val8_, void* _allocate_ = nullptr)
		{
			Members_8_FuncR<Rtype, Type, Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val, Arg6_Val, Arg7_Val, Arg8_Val>* lp = nullptr;

			//三項演算子 　(条件) ? 真の時の処理 : 偽の時の処理
			//長いので縦にしただけ。つまり下記。
			//(条件)
			//? 真の時の処理
			//: 偽の時の処理
			(_allocate_ != nullptr)
			? lp = new(_allocate_) Members_8_FuncR<Rtype, Type, Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val, Arg6_Val, Arg7_Val, Arg8_Val>(Val1_, Val2_, Val3_, Val4_, Val5_, Val6_, Val7_, Val8_)
			: lp = new(std::nothrow) Members_8_FuncR<Rtype, Type, Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val, Arg6_Val, Arg7_Val, Arg8_Val>(Val1_, Val2_, Val3_, Val4_, Val5_, Val6_, Val7_, Val8_);

			if(lp == nullptr)
			{
				//失敗時はnullptrとして返却
				return SonikLib::SharedSmtPtr<SonikFOSTemplateInterface<Rtype>>();
			};

			lp->object_ = _SetObj_;
			lp->p_mfunc_ = set_func;

			return SonikLib::SharedSmtPtr<SonikFOSTemplateInterface<Rtype>>(lp);
		};
		//RawPointer指定
		inline static  SonikLib::SharedSmtPtr<SonikFOSTemplateInterface<Rtype>> New(Type* _SetObj_, Rtype (Type::*set_func)(Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val, Arg6_Val, Arg7_Val, Arg8_Val) , Arg1_Val Val1_, Arg2_Val Val2_, Arg3_Val Val3_, Arg4_Val Val4_, Arg5_Val Val5_, Arg6_Val Val6_, Arg7_Val Val7_, Arg8_Val Val8_, void* _allocate_ = nullptr)
		{
			Members_8_FuncR<Rtype, Type, Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val, Arg6_Val, Arg7_Val, Arg8_Val>* lp = nullptr;

			if(_SetObj_ == nullptr)
			{
				//Global版ではないのにnullptrを指定されたらそのまま返却。
				return SonikLib::SharedSmtPtr<SonikFOSTemplateInterface<Rtype>>();
			};

			//三項演算子 　(条件) ? 真の時の処理 : 偽の時の処理
			//長いので縦にしただけ。つまり下記。
			//(条件)
			//? 真の時の処理
			//: 偽の時の処理
			(_allocate_ != nullptr)
			? lp = new(_allocate_) Members_8_FuncR<Rtype, Type, Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val, Arg6_Val, Arg7_Val, Arg8_Val>(Val1_, Val2_, Val3_, Val4_, Val5_, Val6_, Val7_, Val8_)
			: lp = new(std::nothrow) Members_8_FuncR<Rtype, Type, Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val, Arg6_Val, Arg7_Val, Arg8_Val>(Val1_, Val2_, Val3_, Val4_, Val5_, Val6_, Val7_, Val8_);

			if(lp == nullptr)
			{
				//失敗時はnullptrとして返却
				return SonikLib::SharedSmtPtr<SonikFOSTemplateInterface<Rtype>>();
			};

			lp->object_ = SonikLib::SharedSmtPtr<Type>(_SetObj_);
			lp->p_mfunc_ = set_func;

			return SonikLib::SharedSmtPtr<SonikFOSTemplateInterface<Rtype>>(lp);
		};

		inline Rtype Run(void)
		{
			Rtype ret;

			if( object_.IsNullptr() )
			{
				return 0;
			};

			ret = (object_->*p_mfunc_)(Arg1Val, Arg2Val, Arg3Val, Arg4Val, Arg5Val, Arg6Val, Arg7Val, Arg8Val);
			this->MethodStatus = true;

			return ret;
		};

	};
	//戻り値無し、引数8 (自作スレッドプールで使用する型です。でも他に使いたければどうぞ)
	template<class Type, class Arg1_Val, class Arg2_Val, class Arg3_Val, class Arg4_Val, class Arg5_Val, class Arg6_Val, class Arg7_Val, class Arg8_Val, std::enable_if_t<!std::is_pointer_v<Type>, bool> = true>
	class Members_8_Func : public SonikFOSInterface
	{
	private:
		Arg1_Val  Arg1Val;
		Arg2_Val  Arg2Val;
		Arg3_Val  Arg3Val;
		Arg4_Val  Arg4Val;
		Arg5_Val  Arg5Val;
		Arg6_Val  Arg6Val;
		Arg7_Val  Arg7Val;
		Arg8_Val  Arg8Val;

		SonikLib::SharedSmtPtr<Type> object_;
		void (Type::*p_mfunc_)(Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val, Arg6_Val, Arg7_Val, Arg8_Val);

	private:
		Members_8_Func(void)
		:object_(nullptr)
		,p_mfunc_(nullptr)
		{
			//member value initialize only
		};

		Members_8_Func(Arg1_Val Val1_, Arg2_Val Val2_, Arg3_Val Val3_, Arg4_Val Val4_, Arg5_Val Val5_, Arg6_Val Val6_, Arg7_Val Val7_, Arg8_Val Val8_)
		:Arg1Val(Val1_)
		,Arg2Val(Val2_)
		,Arg3Val(Val3_)
		,Arg4Val(Val4_)
		,Arg5Val(Val5_)
		,Arg6Val(Val6_)
		,Arg7Val(Val7_)
		,Arg8Val(Val8_)
		,object_(nullptr)
		,p_mfunc_(nullptr)
		{
			//member value initialize only
		};

	public:
		~Members_8_Func(void)
		{
			if(this->Destroy_ == false)
			{
				//オブジェクト削除フラグがfalseなら勝手にdeleteしてはいけないので
				//ダミーを使ってスマートポインタからオーナー権限を除去し、dummyのdeleteを呼ばない。
				Type* _dymmy = nullptr;
				object_.GetOwnerPointer(_dymmy);
			};

		};

		//SharedSmtPtr指定
		inline static  SonikLib::SharedSmtPtr<SonikFOSInterface> New(SonikLib::SharedSmtPtr<Type> _SetObj_, void (Type::*set_func)(Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val, Arg6_Val, Arg7_Val, Arg8_Val) , Arg1_Val Val1_, Arg2_Val Val2_, Arg3_Val Val3_, Arg4_Val Val4_, Arg5_Val Val5_, Arg6_Val Val6_, Arg7_Val Val7_, Arg8_Val Val8_, void* _allocate_ = nullptr)
		{
			Members_8_Func<Type, Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val, Arg6_Val, Arg7_Val, Arg8_Val>* lp = nullptr;

			//三項演算子 　(条件) ? 真の時の処理 : 偽の時の処理
			//長いので縦にしただけ。つまり下記。
			//(条件)
			//? 真の時の処理
			//: 偽の時の処理
			(_allocate_ != nullptr)
			? lp = new(_allocate_) Members_8_Func<Type, Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val, Arg6_Val, Arg7_Val, Arg8_Val>(Val1_, Val2_, Val3_, Val4_, Val5_, Val6_, Val7_, Val8_)
			: lp = new(std::nothrow) Members_8_Func<Type, Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val, Arg6_Val, Arg7_Val, Arg8_Val>(Val1_, Val2_, Val3_, Val4_, Val5_, Val6_, Val7_, Val8_);

			if(lp == nullptr)
			{
				//失敗時はnullptrとして返却
				return SonikLib::SharedSmtPtr<SonikFOSInterface>();
			};

			lp->object_ = _SetObj_;
			lp->p_mfunc_ = set_func;

			return SonikLib::SharedSmtPtr<SonikFOSInterface>(lp);
		};
		//RawPointer指定
		inline static  SonikLib::SharedSmtPtr<SonikFOSInterface> New(Type* _SetObj_, void (Type::*set_func)(Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val, Arg6_Val, Arg7_Val, Arg8_Val) , Arg1_Val Val1_, Arg2_Val Val2_, Arg3_Val Val3_, Arg4_Val Val4_, Arg5_Val Val5_, Arg6_Val Val6_, Arg7_Val Val7_, Arg8_Val Val8_, void* _allocate_ = nullptr)
		{
			Members_8_Func<Type, Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val, Arg6_Val, Arg7_Val, Arg8_Val>* lp = nullptr;

			if(_SetObj_ == nullptr)
			{
				//Global版ではないのにnullptrを指定されたらそのまま返却。
				return  SonikLib::SharedSmtPtr<SonikFOSInterface>();
			};

			//三項演算子 　(条件) ? 真の時の処理 : 偽の時の処理
			//長いので縦にしただけ。つまり下記。
			//(条件)
			//? 真の時の処理
			//: 偽の時の処理
			(_allocate_ != nullptr)
			? lp = new(_allocate_) Members_8_Func<Type, Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val, Arg6_Val, Arg7_Val, Arg8_Val>(Val1_, Val2_, Val3_, Val4_, Val5_, Val6_, Val7_, Val8_)
			: lp = new(std::nothrow) Members_8_Func<Type, Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val, Arg6_Val, Arg7_Val, Arg8_Val>(Val1_, Val2_, Val3_, Val4_, Val5_, Val6_, Val7_, Val8_);

			if(lp == nullptr)
			{
				//失敗時はnullptrとして返却
				return SonikLib::SharedSmtPtr<SonikFOSInterface>();
			};

			lp->object_ = SonikLib::SharedSmtPtr<Type>(_SetObj_);
			lp->p_mfunc_ = set_func;

			return SonikLib::SharedSmtPtr<SonikFOSInterface>(lp);
		};

		inline void Run(void)
		{
			if( object_.IsNullptr() )
			{
				return;
			};

			(object_->*p_mfunc_)(Arg1Val, Arg2Val, Arg3Val, Arg4Val, Arg5Val, Arg6Val, Arg7Val, Arg8Val);
			MethodStatus = true;
		};

	};
	//戻り値有り、引数8 グローバル用
	template<class Rtype, class Arg1_Val, class Arg2_Val, class Arg3_Val, class Arg4_Val, class Arg5_Val, class Arg6_Val, class Arg7_Val, class Arg8_Val>
	class Members_8_FuncRG : public SonikFOSTemplateInterface<Rtype>
	{
	private:
		Arg1_Val  Arg1Val;
		Arg2_Val  Arg2Val;
		Arg3_Val  Arg3Val;
		Arg4_Val  Arg4Val;
		Arg5_Val  Arg5Val;
		Arg6_Val  Arg6Val;
		Arg7_Val  Arg7Val;
		Arg8_Val  Arg8Val;

		Rtype (*p_mfunc_)(Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val, Arg6_Val, Arg7_Val, Arg8_Val);

	private:
		Members_8_FuncRG(void)
		:p_mfunc_(nullptr)
		{
			//member value initialize only
		};

		Members_8_FuncRG(Arg1_Val Val1_, Arg2_Val Val2_, Arg3_Val Val3_, Arg4_Val Val4_, Arg5_Val Val5_, Arg6_Val Val6_, Arg7_Val Val7_, Arg8_Val Val8_)
		:Arg1Val(Val1_)
		,Arg2Val(Val2_)
		,Arg3Val(Val3_)
		,Arg4Val(Val4_)
		,Arg5Val(Val5_)
		,Arg6Val(Val6_)
		,Arg7Val(Val7_)
		,Arg8Val(Val8_)
		,p_mfunc_(nullptr)
		{
			//member value initialize only
		};

	public:
		~Members_8_FuncRG(void)
		{
			//no process;
		};

		//グローバル関数指定なので、クラス指定のようにshared版とか無い。
		inline static  SonikLib::SharedSmtPtr<SonikFOSTemplateInterface<Rtype>> New(Rtype (*set_func)(Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val, Arg6_Val, Arg7_Val, Arg8_Val) , Arg1_Val Val1_, Arg2_Val Val2_, Arg3_Val Val3_, Arg4_Val Val4_, Arg5_Val Val5_, Arg6_Val Val6_, Arg7_Val Val7_, Arg8_Val Val8_, void* _allocate_ = nullptr)
		{
			Members_8_FuncRG<Rtype, Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val, Arg6_Val, Arg7_Val, Arg8_Val>* lp = nullptr;

			//三項演算子 　(条件) ? 真の時の処理 : 偽の時の処理
			//長いので縦にしただけ。つまり下記。
			//(条件)
			//? 真の時の処理
			//: 偽の時の処理
			(_allocate_ != nullptr)
			? lp = new(_allocate_) Members_8_FuncRG<Rtype, Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val, Arg6_Val, Arg7_Val, Arg8_Val>(Val1_, Val2_, Val3_, Val4_, Val5_, Val6_, Val7_, Val8_)
			: lp = new(std::nothrow) Members_8_FuncRG<Rtype, Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val, Arg6_Val, Arg7_Val, Arg8_Val>(Val1_, Val2_, Val3_, Val4_, Val5_, Val6_, Val7_, Val8_);

			if(lp == nullptr)
			{
				//失敗時はnullptrとして返却
				return SonikLib::SharedSmtPtr<SonikFOSTemplateInterface<Rtype>>();
			};

			lp->p_mfunc_ = set_func;

			return SonikLib::SharedSmtPtr<SonikFOSTemplateInterface<Rtype>>(lp);
		};

		inline Rtype Run(void)
		{
			Rtype ret;

			ret = (*p_mfunc_)(Arg1Val, Arg2Val, Arg3Val, Arg4Val, Arg5Val, Arg6Val, Arg7Val, Arg8Val);
			this->MethodStatus = true;

			return ret;
		};

	};
	//戻り値無し、引数8 グローバル用
	template<class Arg1_Val, class Arg2_Val, class Arg3_Val, class Arg4_Val, class Arg5_Val, class Arg6_Val, class Arg7_Val, class Arg8_Val>
	class Members_8_FuncG : public SonikFOSInterface
	{
	private:
		Arg1_Val  Arg1Val;
		Arg2_Val  Arg2Val;
		Arg3_Val  Arg3Val;
		Arg4_Val  Arg4Val;
		Arg5_Val  Arg5Val;
		Arg6_Val  Arg6Val;
		Arg7_Val  Arg7Val;
		Arg8_Val  Arg8Val;

		void (*p_mfunc_)(Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val, Arg6_Val, Arg7_Val, Arg8_Val);

	private:
		Members_8_FuncG(void)
		:p_mfunc_(nullptr)
		{
			//member value initialize only
		};

		Members_8_FuncG(Arg1_Val Val1_, Arg2_Val Val2_, Arg3_Val Val3_, Arg4_Val Val4_, Arg5_Val Val5_, Arg6_Val Val6_, Arg7_Val Val7_, Arg8_Val Val8_)
		:Arg1Val(Val1_)
		,Arg2Val(Val2_)
		,Arg3Val(Val3_)
		,Arg4Val(Val4_)
		,Arg5Val(Val5_)
		,Arg6Val(Val6_)
		,Arg7Val(Val7_)
		,Arg8Val(Val8_)
		,p_mfunc_(nullptr)
		{
			//member value initialize only
		};

	public:
		~Members_8_FuncG(void)
		{
			//no process;
		};

		//グローバル関数指定なので、クラス指定のようにshared版とか無い。
		inline static  SonikLib::SharedSmtPtr<SonikFOSInterface> New(void (*set_func)(Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val, Arg6_Val, Arg7_Val, Arg8_Val) , Arg1_Val Val1_, Arg2_Val Val2_, Arg3_Val Val3_, Arg4_Val Val4_, Arg5_Val Val5_, Arg6_Val Val6_, Arg7_Val Val7_, Arg8_Val Val8_, void* _allocate_ = nullptr)
		{
			Members_8_FuncG< Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val, Arg6_Val, Arg7_Val, Arg8_Val>* lp = nullptr;

			//三項演算子 　(条件) ? 真の時の処理 : 偽の時の処理
			//長いので縦にしただけ。つまり下記。
			//(条件)
			//? 真の時の処理
			//: 偽の時の処理
			(_allocate_ != nullptr)
			? lp = new(_allocate_) Members_8_FuncG< Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val, Arg6_Val, Arg7_Val, Arg8_Val>(Val1_, Val2_, Val3_, Val4_, Val5_, Val6_, Val7_, Val8_)
			: lp = new(std::nothrow) Members_8_FuncG< Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val, Arg6_Val, Arg7_Val, Arg8_Val>(Val1_, Val2_, Val3_, Val4_, Val5_, Val6_, Val7_, Val8_);

			if(lp == nullptr)
			{
				//失敗時はnullptrとして返却
				return SonikLib::SharedSmtPtr<SonikFOSInterface>();
			};

			lp->p_mfunc_ = set_func;

			return SonikLib::SharedSmtPtr<SonikFOSInterface>(lp);
		};

		inline void Run(void)
		{
			(*p_mfunc_)(Arg1Val, Arg2Val, Arg3Val, Arg4Val, Arg5Val, Arg6Val, Arg7Val, Arg8Val);
			MethodStatus = true;
		};

	};

	//戻り値有り、引数7
	template<class Rtype, class Type, class Arg1_Val, class Arg2_Val, class Arg3_Val, class Arg4_Val, class Arg5_Val, class Arg6_Val, class Arg7_Val, std::enable_if_t<!std::is_pointer_v<Type>, bool> = true>
	class Members_7_FuncR : public SonikFOSTemplateInterface<Rtype>
	{
	private:
		Arg1_Val  Arg1Val;
		Arg2_Val  Arg2Val;
		Arg3_Val  Arg3Val;
		Arg4_Val  Arg4Val;
		Arg5_Val  Arg5Val;
		Arg6_Val  Arg6Val;
		Arg7_Val  Arg7Val;

		SonikLib::SharedSmtPtr<Type> object_;
		Rtype (Type::*p_mfunc_)(Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val, Arg6_Val, Arg7_Val);

	private:
		Members_7_FuncR(void)
		:object_(nullptr)
		,p_mfunc_(nullptr)
		{
			//member value initialize only
		};

		Members_7_FuncR(Arg1_Val Val1_, Arg2_Val Val2_, Arg3_Val Val3_, Arg4_Val Val4_, Arg5_Val Val5_, Arg6_Val Val6_, Arg7_Val Val7_)
		:Arg1Val(Val1_)
		,Arg2Val(Val2_)
		,Arg3Val(Val3_)
		,Arg4Val(Val4_)
		,Arg5Val(Val5_)
		,Arg6Val(Val6_)
		,Arg7Val(Val7_)
		,object_(nullptr)
		,p_mfunc_(nullptr)
		{
			//member value initialize only
		};

	public:
		~Members_7_FuncR(void)
		{
			if(this->Destroy_ == false)
			{
				//オブジェクト削除フラグがfalseなら勝手にdeleteしてはいけないので
				//ダミーを使ってスマートポインタからオーナー権限を除去し、dummyのdeleteを呼ばない。
				Type* _dymmy = nullptr;
				object_.GetOwnerPointer(_dymmy);
			};

		};

		//SharedSmtPtr指定
		inline static  SonikLib::SharedSmtPtr<SonikFOSTemplateInterface<Rtype>> New(SonikLib::SharedSmtPtr<Type> _SetObj_, Rtype (Type::*set_func)(Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val, Arg6_Val, Arg7_Val) , Arg1_Val Val1_, Arg2_Val Val2_, Arg3_Val Val3_, Arg4_Val Val4_, Arg5_Val Val5_, Arg6_Val Val6_, Arg7_Val Val7_, void* _allocate_ = nullptr)
		{
			Members_7_FuncR<Rtype, Type, Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val, Arg6_Val, Arg7_Val>* lp = nullptr;

			//三項演算子 　(条件) ? 真の時の処理 : 偽の時の処理
			//長いので縦にしただけ。つまり下記。
			//(条件)
			//? 真の時の処理
			//: 偽の時の処理
			(_allocate_ != nullptr)
			? lp = new(_allocate_) Members_7_FuncR<Rtype, Type, Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val, Arg6_Val, Arg7_Val>(Val1_, Val2_, Val3_, Val4_, Val5_, Val6_, Val7_)
			: lp = new(std::nothrow) Members_7_FuncR<Rtype, Type, Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val, Arg6_Val, Arg7_Val>(Val1_, Val2_, Val3_, Val4_, Val5_, Val6_, Val7_);

			if(lp == nullptr)
			{
				//失敗時はnullptrとして返却
				return SonikLib::SharedSmtPtr<SonikFOSTemplateInterface<Rtype>>();
			};

			lp->object_ = _SetObj_;
			lp->p_mfunc_ = set_func;

			return SonikLib::SharedSmtPtr<SonikFOSTemplateInterface<Rtype>>(lp);
		};
		//RawPointer指定
		inline static  SonikLib::SharedSmtPtr<SonikFOSTemplateInterface<Rtype>> New(Type* _SetObj_, Rtype (Type::*set_func)(Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val, Arg6_Val, Arg7_Val) , Arg1_Val Val1_, Arg2_Val Val2_, Arg3_Val Val3_, Arg4_Val Val4_, Arg5_Val Val5_, Arg6_Val Val6_, Arg7_Val Val7_, void* _allocate_ = nullptr)
		{
			Members_7_FuncR<Rtype, Type, Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val, Arg6_Val, Arg7_Val>* lp = nullptr;

			if(_SetObj_ == nullptr)
			{
				//Global版ではないのにnullptrを指定されたらそのまま返却。
				return SonikLib::SharedSmtPtr<SonikFOSTemplateInterface<Rtype>>();
			};

			//三項演算子 　(条件) ? 真の時の処理 : 偽の時の処理
			//長いので縦にしただけ。つまり下記。
			//(条件)
			//? 真の時の処理
			//: 偽の時の処理
			(_allocate_ != nullptr)
			? lp = new(_allocate_) Members_7_FuncR<Rtype, Type, Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val, Arg6_Val, Arg7_Val>(Val1_, Val2_, Val3_, Val4_, Val5_, Val6_, Val7_)
			: lp = new(std::nothrow) Members_7_FuncR<Rtype, Type, Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val, Arg6_Val, Arg7_Val>(Val1_, Val2_, Val3_, Val4_, Val5_, Val6_, Val7_);

			if(lp == nullptr)
			{
				//失敗時はnullptrとして返却
				return SonikLib::SharedSmtPtr<SonikFOSTemplateInterface<Rtype>>();
			};

			lp->object_ = SonikLib::SharedSmtPtr<Type>(_SetObj_);
			lp->p_mfunc_ = set_func;

			return SonikLib::SharedSmtPtr<SonikFOSTemplateInterface<Rtype>>(lp);
		};

		inline Rtype Run(void)
		{
			Rtype ret;

			if( object_.IsNullptr() )
			{
				return 0;
			};

			ret = (object_->*p_mfunc_)(Arg1Val, Arg2Val, Arg3Val, Arg4Val, Arg5Val, Arg6Val, Arg7Val);
			this->MethodStatus = true;

			return ret;
		};

	};
	//戻り値無し、引数7
	template<class Type, class Arg1_Val, class Arg2_Val, class Arg3_Val, class Arg4_Val, class Arg5_Val, class Arg6_Val, class Arg7_Val, std::enable_if_t<!std::is_pointer_v<Type>, bool> = true>
	class Members_7_Func : public SonikFOSInterface
	{
	private:
		Arg1_Val  Arg1Val;
		Arg2_Val  Arg2Val;
		Arg3_Val  Arg3Val;
		Arg4_Val  Arg4Val;
		Arg5_Val  Arg5Val;
		Arg6_Val  Arg6Val;
		Arg7_Val  Arg7Val;

		SonikLib::SharedSmtPtr<Type> object_;
		void (Type::*p_mfunc_)(Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val, Arg6_Val, Arg7_Val);

	private:
		Members_7_Func(void)
		:object_(nullptr)
		,p_mfunc_(nullptr)
		{
			//member value initialize only
		};

		Members_7_Func(Arg1_Val Val1_, Arg2_Val Val2_, Arg3_Val Val3_, Arg4_Val Val4_, Arg5_Val Val5_, Arg6_Val Val6_, Arg7_Val Val7_)
		:Arg1Val(Val1_)
		,Arg2Val(Val2_)
		,Arg3Val(Val3_)
		,Arg4Val(Val4_)
		,Arg5Val(Val5_)
		,Arg6Val(Val6_)
		,Arg7Val(Val7_)
		,object_(nullptr)
		,p_mfunc_(nullptr)
		{
			//member value initialize only
		};

	public:
		~Members_7_Func(void)
		{
			if(this->Destroy_ == false)
			{
				//オブジェクト削除フラグがfalseなら勝手にdeleteしてはいけないので
				//ダミーを使ってスマートポインタからオーナー権限を除去し、dummyのdeleteを呼ばない。
				Type* _dymmy = nullptr;
				object_.GetOwnerPointer(_dymmy);
			};

		};

		//SharedSmtPtr指定
		inline static  SonikLib::SharedSmtPtr<SonikFOSInterface> New(SonikLib::SharedSmtPtr<Type> _SetObj_, void (Type::*set_func)(Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val, Arg6_Val, Arg7_Val) , Arg1_Val Val1_, Arg2_Val Val2_, Arg3_Val Val3_, Arg4_Val Val4_, Arg5_Val Val5_, Arg6_Val Val6_, Arg7_Val Val7_, void* _allocate_ = nullptr)
		{
			Members_7_Func<Type, Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val, Arg6_Val, Arg7_Val>* lp = nullptr;

			//三項演算子 　(条件) ? 真の時の処理 : 偽の時の処理
			//長いので縦にしただけ。つまり下記。
			//(条件)
			//? 真の時の処理
			//: 偽の時の処理
			(_allocate_ != nullptr)
			? lp = new(_allocate_) Members_7_Func<Type, Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val, Arg6_Val, Arg7_Val>(Val1_, Val2_, Val3_, Val4_, Val5_, Val6_, Val7_)
			: lp = new(std::nothrow) Members_7_Func<Type, Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val, Arg6_Val, Arg7_Val>(Val1_, Val2_, Val3_, Val4_, Val5_, Val6_, Val7_);

			if(lp == nullptr)
			{
				//失敗時はnullptrとして返却
				return SonikLib::SharedSmtPtr<SonikFOSInterface>();
			};

			lp->object_ = _SetObj_;
			lp->p_mfunc_ = set_func;

			return SonikLib::SharedSmtPtr<SonikFOSInterface>(lp);
		};
		//RawPointer指定
		inline static  SonikLib::SharedSmtPtr<SonikFOSInterface> New(Type* _SetObj_, void (Type::*set_func)(Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val, Arg6_Val, Arg7_Val) , Arg1_Val Val1_, Arg2_Val Val2_, Arg3_Val Val3_, Arg4_Val Val4_, Arg5_Val Val5_, Arg6_Val Val6_, Arg7_Val Val7_, void* _allocate_ = nullptr)
		{
			Members_7_Func<Type, Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val, Arg6_Val, Arg7_Val>* lp = nullptr;

			if(_SetObj_ == nullptr)
			{
				//Global版ではないのにnullptrを指定されたらそのまま返却。
				return  SonikLib::SharedSmtPtr<SonikFOSInterface>();
			};

			//三項演算子 　(条件) ? 真の時の処理 : 偽の時の処理
			//長いので縦にしただけ。つまり下記。
			//(条件)
			//? 真の時の処理
			//: 偽の時の処理
			(_allocate_ != nullptr)
			? lp = new(_allocate_) Members_7_Func<Type, Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val, Arg6_Val, Arg7_Val>(Val1_, Val2_, Val3_, Val4_, Val5_, Val6_, Val7_)
			: lp = new(std::nothrow) Members_7_Func<Type, Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val, Arg6_Val, Arg7_Val>(Val1_, Val2_, Val3_, Val4_, Val5_, Val6_, Val7_);

			if(lp == nullptr)
			{
				//失敗時はnullptrとして返却
				return SonikLib::SharedSmtPtr<SonikFOSInterface>();
			};

			lp->object_ = SonikLib::SharedSmtPtr<Type>(_SetObj_);
			lp->p_mfunc_ = set_func;

			return SonikLib::SharedSmtPtr<SonikFOSInterface>(lp);
		};

		inline void Run(void)
		{
			if( object_.IsNullptr() )
			{
				return;
			};

			(object_->*p_mfunc_)(Arg1Val, Arg2Val, Arg3Val, Arg4Val, Arg5Val, Arg6Val, Arg7Val);
			MethodStatus = true;
		};

	};
	//戻り値有り、引数7 グローバル用
	template<class Rtype, class Arg1_Val, class Arg2_Val, class Arg3_Val, class Arg4_Val, class Arg5_Val, class Arg6_Val, class Arg7_Val>
	class Members_7_FuncRG : public SonikFOSTemplateInterface<Rtype>
	{
	private:
		Arg1_Val  Arg1Val;
		Arg2_Val  Arg2Val;
		Arg3_Val  Arg3Val;
		Arg4_Val  Arg4Val;
		Arg5_Val  Arg5Val;
		Arg6_Val  Arg6Val;
		Arg7_Val  Arg7Val;

		Rtype (*p_mfunc_)(Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val, Arg6_Val, Arg7_Val);

	private:
		Members_7_FuncRG(void)
		:p_mfunc_(nullptr)
		{
			//member value initialize only
		};

		Members_7_FuncRG(Arg1_Val Val1_, Arg2_Val Val2_, Arg3_Val Val3_, Arg4_Val Val4_, Arg5_Val Val5_, Arg6_Val Val6_, Arg7_Val Val7_)
		:Arg1Val(Val1_)
		,Arg2Val(Val2_)
		,Arg3Val(Val3_)
		,Arg4Val(Val4_)
		,Arg5Val(Val5_)
		,Arg6Val(Val6_)
		,Arg7Val(Val7_)
		,p_mfunc_(nullptr)
		{
			//member value initialize only
		};

	public:
		~Members_7_FuncRG(void)
		{
			//no process;
		};

		//グローバル関数指定なので、クラス指定のようにshared版とか無い。
		inline static  SonikLib::SharedSmtPtr<SonikFOSTemplateInterface<Rtype>> New(Rtype (*set_func)(Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val, Arg6_Val, Arg7_Val) , Arg1_Val Val1_, Arg2_Val Val2_, Arg3_Val Val3_, Arg4_Val Val4_, Arg5_Val Val5_, Arg6_Val Val6_, Arg7_Val Val7_, void* _allocate_ = nullptr)
		{
			Members_7_FuncRG<Rtype, Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val, Arg6_Val, Arg7_Val>* lp = nullptr;

			//三項演算子 　(条件) ? 真の時の処理 : 偽の時の処理
			//長いので縦にしただけ。つまり下記。
			//(条件)
			//? 真の時の処理
			//: 偽の時の処理
			(_allocate_ != nullptr)
			? lp = new(_allocate_) Members_7_FuncRG<Rtype, Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val, Arg6_Val, Arg7_Val>(Val1_, Val2_, Val3_, Val4_, Val5_, Val6_, Val7_)
			: lp = new(std::nothrow) Members_7_FuncRG<Rtype, Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val, Arg6_Val, Arg7_Val>(Val1_, Val2_, Val3_, Val4_, Val5_, Val6_, Val7_);

			if(lp == nullptr)
			{
				//失敗時はnullptrとして返却
				return SonikLib::SharedSmtPtr<SonikFOSTemplateInterface<Rtype>>();
			};

			lp->p_mfunc_ = set_func;

			return SonikLib::SharedSmtPtr<SonikFOSTemplateInterface<Rtype>>(lp);
		};

		inline Rtype Run(void)
		{
			Rtype ret;

			ret = (*p_mfunc_)(Arg1Val, Arg2Val, Arg3Val, Arg4Val, Arg5Val, Arg6Val, Arg7Val);
			this->MethodStatus = true;

			return ret;
		};

	};
	//戻り値無し、引数7 グローバル用
	template<class Arg1_Val, class Arg2_Val, class Arg3_Val, class Arg4_Val, class Arg5_Val, class Arg6_Val, class Arg7_Val>
	class Members_7_FuncG : public SonikFOSInterface
	{
	private:
		Arg1_Val  Arg1Val;
		Arg2_Val  Arg2Val;
		Arg3_Val  Arg3Val;
		Arg4_Val  Arg4Val;
		Arg5_Val  Arg5Val;
		Arg6_Val  Arg6Val;
		Arg7_Val  Arg7Val;

		void (*p_mfunc_)(Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val, Arg6_Val, Arg7_Val);

	private:
		Members_7_FuncG(void)
		:p_mfunc_(nullptr)
		{
			//member value initialize only
		};

		Members_7_FuncG(Arg1_Val Val1_, Arg2_Val Val2_, Arg3_Val Val3_, Arg4_Val Val4_, Arg5_Val Val5_, Arg6_Val Val6_, Arg7_Val Val7_)
		:Arg1Val(Val1_)
		,Arg2Val(Val2_)
		,Arg3Val(Val3_)
		,Arg4Val(Val4_)
		,Arg5Val(Val5_)
		,Arg6Val(Val6_)
		,Arg7Val(Val7_)
		,p_mfunc_(nullptr)
		{
			//member value initialize only
		};

	public:
		~Members_7_FuncG(void)
		{
			//no process;
		};

		//グローバル関数指定なので、クラス指定のようにshared版とか無い。
		inline static  SonikLib::SharedSmtPtr<SonikFOSInterface> New(void (*set_func)(Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val, Arg6_Val, Arg7_Val) , Arg1_Val Val1_, Arg2_Val Val2_, Arg3_Val Val3_, Arg4_Val Val4_, Arg5_Val Val5_, Arg6_Val Val6_, Arg7_Val Val7_, void* _allocate_ = nullptr)
		{
			Members_7_FuncG< Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val, Arg6_Val, Arg7_Val>* lp = nullptr;

			//三項演算子 　(条件) ? 真の時の処理 : 偽の時の処理
			//長いので縦にしただけ。つまり下記。
			//(条件)
			//? 真の時の処理
			//: 偽の時の処理
			(_allocate_ != nullptr)
			? lp = new(_allocate_) Members_7_FuncG< Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val, Arg6_Val, Arg7_Val>(Val1_, Val2_, Val3_, Val4_, Val5_, Val6_, Val7_)
			: lp = new(std::nothrow) Members_7_FuncG< Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val, Arg6_Val, Arg7_Val>(Val1_, Val2_, Val3_, Val4_, Val5_, Val6_, Val7_);

			if(lp == nullptr)
			{
				//失敗時はnullptrとして返却
				return SonikLib::SharedSmtPtr<SonikFOSInterface>();
			};

			lp->p_mfunc_ = set_func;

			return SonikLib::SharedSmtPtr<SonikFOSInterface>(lp);
		};

		inline void Run(void)
		{
			(*p_mfunc_)(Arg1Val, Arg2Val, Arg3Val, Arg4Val, Arg5Val, Arg6Val, Arg7Val);
			MethodStatus = true;
		};

	};

	//戻り値有り、引数6
	template<class Rtype, class Type, class Arg1_Val, class Arg2_Val, class Arg3_Val, class Arg4_Val, class Arg5_Val, class Arg6_Val, std::enable_if_t<!std::is_pointer_v<Type>, bool> = true>
	class Members_6_FuncR : public SonikFOSTemplateInterface<Rtype>
	{
	private:
		Arg1_Val  Arg1Val;
		Arg2_Val  Arg2Val;
		Arg3_Val  Arg3Val;
		Arg4_Val  Arg4Val;
		Arg5_Val  Arg5Val;
		Arg6_Val  Arg6Val;

		SonikLib::SharedSmtPtr<Type> object_;
		Rtype (Type::*p_mfunc_)(Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val, Arg6_Val);

	private:
		Members_6_FuncR(void)
		:object_(nullptr)
		,p_mfunc_(nullptr)
		{
			//member value initialize only
		};

		Members_6_FuncR(Arg1_Val Val1_, Arg2_Val Val2_, Arg3_Val Val3_, Arg4_Val Val4_, Arg5_Val Val5_, Arg6_Val Val6_)
		:Arg1Val(Val1_)
		,Arg2Val(Val2_)
		,Arg3Val(Val3_)
		,Arg4Val(Val4_)
		,Arg5Val(Val5_)
		,Arg6Val(Val6_)
		,object_(nullptr)
		,p_mfunc_(nullptr)
		{
			//member value initialize only
		};

	public:
		~Members_6_FuncR(void)
		{
			if(this->Destroy_ == false)
			{
				//オブジェクト削除フラグがfalseなら勝手にdeleteしてはいけないので
				//ダミーを使ってスマートポインタからオーナー権限を除去し、dummyのdeleteを呼ばない。
				Type* _dymmy = nullptr;
				object_.GetOwnerPointer(_dymmy);
			};

		};

		//SharedSmtPtr指定
		inline static  SonikLib::SharedSmtPtr<SonikFOSTemplateInterface<Rtype>> New(SonikLib::SharedSmtPtr<Type> _SetObj_, Rtype (Type::*set_func)(Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val, Arg6_Val) , Arg1_Val Val1_, Arg2_Val Val2_, Arg3_Val Val3_, Arg4_Val Val4_, Arg5_Val Val5_, Arg6_Val Val6_, void* _allocate_ = nullptr)
		{
			Members_6_FuncR<Rtype, Type, Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val, Arg6_Val>* lp = nullptr;

			//三項演算子 　(条件) ? 真の時の処理 : 偽の時の処理
			//長いので縦にしただけ。つまり下記。
			//(条件)
			//? 真の時の処理
			//: 偽の時の処理
			(_allocate_ != nullptr)
			? lp = new(_allocate_) Members_6_FuncR<Rtype, Type, Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val, Arg6_Val>(Val1_, Val2_, Val3_, Val4_, Val5_, Val6_)
			: lp = new(std::nothrow) Members_6_FuncR<Rtype, Type, Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val, Arg6_Val>(Val1_, Val2_, Val3_, Val4_, Val5_, Val6_);

			if(lp == nullptr)
			{
				//失敗時はnullptrとして返却
				return SonikLib::SharedSmtPtr<SonikFOSTemplateInterface<Rtype>>();
			};

			lp->object_ = _SetObj_;
			lp->p_mfunc_ = set_func;

			return SonikLib::SharedSmtPtr<SonikFOSTemplateInterface<Rtype>>(lp);
		};
		//RawPointer指定
		inline static  SonikLib::SharedSmtPtr<SonikFOSTemplateInterface<Rtype>> New(Type* _SetObj_, Rtype (Type::*set_func)(Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val, Arg6_Val) , Arg1_Val Val1_, Arg2_Val Val2_, Arg3_Val Val3_, Arg4_Val Val4_, Arg5_Val Val5_, Arg6_Val Val6_, void* _allocate_ = nullptr)
		{
			Members_6_FuncR<Rtype, Type, Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val, Arg6_Val>* lp = nullptr;

			if(_SetObj_ == nullptr)
			{
				//Global版ではないのにnullptrを指定されたらそのまま返却。
				return SonikLib::SharedSmtPtr<SonikFOSTemplateInterface<Rtype>>();
			};

			//三項演算子 　(条件) ? 真の時の処理 : 偽の時の処理
			//長いので縦にしただけ。つまり下記。
			//(条件)
			//? 真の時の処理
			//: 偽の時の処理
			(_allocate_ != nullptr)
			? lp = new(_allocate_) Members_6_FuncR<Rtype, Type, Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val, Arg6_Val>(Val1_, Val2_, Val3_, Val4_, Val5_, Val6_)
			: lp = new(std::nothrow) Members_6_FuncR<Rtype, Type, Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val, Arg6_Val>(Val1_, Val2_, Val3_, Val4_, Val5_, Val6_);

			if(lp == nullptr)
			{
				//失敗時はnullptrとして返却
				return SonikLib::SharedSmtPtr<SonikFOSTemplateInterface<Rtype>>();
			};

			lp->object_ = SonikLib::SharedSmtPtr<Type>(_SetObj_);
			lp->p_mfunc_ = set_func;

			return SonikLib::SharedSmtPtr<SonikFOSTemplateInterface<Rtype>>(lp);
		};

		inline Rtype Run(void)
		{
			Rtype ret;

			if( object_.IsNullptr() )
			{
				return 0;
			};

			ret = (object_->*p_mfunc_)(Arg1Val, Arg2Val, Arg3Val, Arg4Val, Arg5Val, Arg6Val);
			this->MethodStatus = true;

			return ret;
		};

	};
	//戻り値無し、引数6
	template<class Type, class Arg1_Val, class Arg2_Val, class Arg3_Val, class Arg4_Val, class Arg5_Val, class Arg6_Val, std::enable_if_t<!std::is_pointer_v<Type>, bool> = true>
	class Members_6_Func : public SonikFOSInterface
	{
	private:
		Arg1_Val  Arg1Val;
		Arg2_Val  Arg2Val;
		Arg3_Val  Arg3Val;
		Arg4_Val  Arg4Val;
		Arg5_Val  Arg5Val;
		Arg6_Val  Arg6Val;

		SonikLib::SharedSmtPtr<Type> object_;
		void (Type::*p_mfunc_)(Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val, Arg6_Val);

	private:
		Members_6_Func(void)
		:object_(nullptr)
		,p_mfunc_(nullptr)
		{
			//member value initialize only
		};

		Members_6_Func(Arg1_Val Val1_, Arg2_Val Val2_, Arg3_Val Val3_, Arg4_Val Val4_, Arg5_Val Val5_, Arg6_Val Val6_)
		:Arg1_Val(Val1_)
		,Arg2_Val(Val1_)
		,Arg3_Val(Val1_)
		,Arg4_Val(Val1_)
		,Arg5_Val(Val1_)
		,Arg6_Val(Val1_)
		,object_(nullptr)
		,p_mfunc_(nullptr)
		{
			//member value initialize only
		};

	public:
		~Members_6_Func(void)
		{
			if(this->Destroy_ == false)
			{
				//オブジェクト削除フラグがfalseなら勝手にdeleteしてはいけないので
				//ダミーを使ってスマートポインタからオーナー権限を除去し、dummyのdeleteを呼ばない。
				Type* _dymmy = nullptr;
				object_.GetOwnerPointer(_dymmy);
			};

		};

		//SharedSmtPtr指定
		inline static  SonikLib::SharedSmtPtr<SonikFOSInterface> New(SonikLib::SharedSmtPtr<Type> _SetObj_, void (Type::*set_func)(Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val, Arg6_Val) , Arg1_Val Val1_, Arg2_Val Val2_, Arg3_Val Val3_, Arg4_Val Val4_, Arg5_Val Val5_, Arg6_Val Val6_, void* _allocate_ = nullptr)
		{
			Members_6_Func<Type, Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val, Arg6_Val>* lp = nullptr;

			//三項演算子 　(条件) ? 真の時の処理 : 偽の時の処理
			//長いので縦にしただけ。つまり下記。
			//(条件)
			//? 真の時の処理
			//: 偽の時の処理
			(_allocate_ != nullptr)
			? lp = new(_allocate_) Members_6_Func<Type, Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val, Arg6_Val>(Val1_, Val2_, Val3_, Val4_, Val5_, Val6_)
			: lp = new(std::nothrow) Members_6_Func<Type, Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val, Arg6_Val>(Val1_, Val2_, Val3_, Val4_, Val5_, Val6_);

			if(lp == nullptr)
			{
				//失敗時はnullptrとして返却
				return SonikLib::SharedSmtPtr<SonikFOSInterface>();
			};

			lp->object_ = _SetObj_;
			lp->p_mfunc_ = set_func;

			return SonikLib::SharedSmtPtr<SonikFOSInterface>(lp);
		};
		//RawPointer指定
		inline static  SonikLib::SharedSmtPtr<SonikFOSInterface> New(Type* _SetObj_, void (Type::*set_func)(Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val, Arg6_Val) , Arg1_Val Val1_, Arg2_Val Val2_, Arg3_Val Val3_, Arg4_Val Val4_, Arg5_Val Val5_, Arg6_Val Val6_, void* _allocate_ = nullptr)
		{
			Members_6_Func<Type, Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val, Arg6_Val>* lp = nullptr;

			if(_SetObj_ == nullptr)
			{
				//Global版ではないのにnullptrを指定されたらそのまま返却。
				return  SonikLib::SharedSmtPtr<SonikFOSInterface>();
			};

			//三項演算子 　(条件) ? 真の時の処理 : 偽の時の処理
			//長いので縦にしただけ。つまり下記。
			//(条件)
			//? 真の時の処理
			//: 偽の時の処理
			(_allocate_ != nullptr)
			? lp = new(_allocate_) Members_6_Func<Type, Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val, Arg6_Val>(Val1_, Val2_, Val3_, Val4_, Val5_, Val6_)
			: lp = new(std::nothrow) Members_6_Func<Type, Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val, Arg6_Val>(Val1_, Val2_, Val3_, Val4_, Val5_, Val6_);

			if(lp == nullptr)
			{
				//失敗時はnullptrとして返却
				return SonikLib::SharedSmtPtr<SonikFOSInterface>();
			};

			lp->object_ = SonikLib::SharedSmtPtr<Type>(_SetObj_);
			lp->p_mfunc_ = set_func;

			return SonikLib::SharedSmtPtr<SonikFOSInterface>(lp);
		};

		inline void Run(void)
		{
			if( object_.IsNullptr() )
			{
				return;
			};

			(object_->*p_mfunc_)(Arg1Val, Arg2Val, Arg3Val, Arg4Val, Arg5Val, Arg6Val);
			MethodStatus = true;
		};

	};
	//戻り値有り、引数6
	template<class Rtype, class Arg1_Val, class Arg2_Val, class Arg3_Val, class Arg4_Val, class Arg5_Val, class Arg6_Val>
	class Members_6_FuncRG : public SonikFOSTemplateInterface<Rtype>
	{
	private:
		Arg1_Val  Arg1Val;
		Arg2_Val  Arg2Val;
		Arg3_Val  Arg3Val;
		Arg4_Val  Arg4Val;
		Arg5_Val  Arg5Val;
		Arg6_Val  Arg6Val;

		Rtype (*p_mfunc_)(Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val, Arg6_Val);

	private:
		Members_6_FuncRG()
		:p_mfunc_(nullptr)
		{
			//member value initialize only
		};

		Members_6_FuncRG(Arg1_Val Val1_, Arg2_Val Val2_, Arg3_Val Val3_, Arg4_Val Val4_, Arg5_Val Val5_, Arg6_Val Val6_)
		:Arg1Val(Val1_)
		,Arg2Val(Val2_)
		,Arg3Val(Val3_)
		,Arg4Val(Val4_)
		,Arg5Val(Val5_)
		,Arg6Val(Val6_)
		,p_mfunc_(nullptr)
		{
			//member value initialize only
		};

	public:
		~Members_6_FuncRG(void)
		{
			//no process;
		};

		//グローバル関数指定なので、クラス指定のようにshared版とか無い。
		inline static  SonikLib::SharedSmtPtr<SonikFOSTemplateInterface<Rtype>> New(Rtype (*set_func)(Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val, Arg6_Val) , Arg1_Val Val1_, Arg2_Val Val2_, Arg3_Val Val3_, Arg4_Val Val4_, Arg5_Val Val5_, Arg6_Val Val6_, void* _allocate_ = nullptr)
		{
			Members_6_FuncRG<Rtype, Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val, Arg6_Val>* lp = nullptr;

			//三項演算子 　(条件) ? 真の時の処理 : 偽の時の処理
			//長いので縦にしただけ。つまり下記。
			//(条件)
			//? 真の時の処理
			//: 偽の時の処理
			(_allocate_ != nullptr)
			? lp = new(_allocate_) Members_6_FuncRG<Rtype, Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val, Arg6_Val>(Val1_, Val2_, Val3_, Val4_, Val5_, Val6_)
			: lp = new(std::nothrow) Members_6_FuncRG<Rtype, Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val, Arg6_Val>(Val1_, Val2_, Val3_, Val4_, Val5_, Val6_);

			if(lp == nullptr)
			{
				//失敗時はnullptrとして返却
				return SonikLib::SharedSmtPtr<SonikFOSTemplateInterface<Rtype>>();
			};

			lp->p_mfunc_ = set_func;

			return SonikLib::SharedSmtPtr<SonikFOSTemplateInterface<Rtype>>(lp);
		};

		inline Rtype Run(void)
		{
			Rtype ret;

			ret = (*p_mfunc_)(Arg1Val, Arg2Val, Arg3Val, Arg4Val, Arg5Val, Arg6Val);
			this->MethodStatus = true;

			return ret;
		};

	};
	//戻り値無し、引数6 グローバル用
	template<class Arg1_Val, class Arg2_Val, class Arg3_Val, class Arg4_Val, class Arg5_Val, class Arg6_Val>
	class Members_6_FuncG : public SonikFOSInterface
	{
	private:
		Arg1_Val  Arg1Val;
		Arg2_Val  Arg2Val;
		Arg3_Val  Arg3Val;
		Arg4_Val  Arg4Val;
		Arg5_Val  Arg5Val;
		Arg6_Val  Arg6Val;

		void (*p_mfunc_)(Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val, Arg6_Val);

	private:
		Members_6_FuncG(void)
		:p_mfunc_(nullptr)
		{
			//member value initialzie only
		};

		Members_6_FuncG(Arg1_Val Val1_, Arg2_Val Val2_, Arg3_Val Val3_, Arg4_Val Val4_, Arg5_Val Val5_, Arg6_Val Val6_)
		:Arg1Val(Val1_)
		,Arg2Val(Val2_)
		,Arg3Val(Val3_)
		,Arg4Val(Val4_)
		,Arg5Val(Val5_)
		,Arg6Val(Val6_)
		,p_mfunc_(nullptr)
		{
			//member value initialzie only
		};

	public:
		~Members_6_FuncG(void)
		{
			//no process;
		};

		//グローバル関数指定なので、クラス指定のようにshared版とか無い。
		inline static  SonikLib::SharedSmtPtr<SonikFOSInterface> New(void (*set_func)(Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val, Arg6_Val) , Arg1_Val Val1_, Arg2_Val Val2_, Arg3_Val Val3_, Arg4_Val Val4_, Arg5_Val Val5_, Arg6_Val Val6_, void* _allocate_ = nullptr)
		{
			Members_6_FuncG< Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val, Arg6_Val>* lp = nullptr;

			//三項演算子 　(条件) ? 真の時の処理 : 偽の時の処理
			//長いので縦にしただけ。つまり下記。
			//(条件)
			//? 真の時の処理
			//: 偽の時の処理
			(_allocate_ != nullptr)
			? lp = new(_allocate_) Members_6_FuncG< Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val, Arg6_Val>(Val1_, Val2_, Val3_, Val4_, Val5_, Val6_)
			: lp = new(std::nothrow) Members_6_FuncG< Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val, Arg6_Val>(Val1_, Val2_, Val3_, Val4_, Val5_, Val6_);

			if(lp == nullptr)
			{
				//失敗時はnullptrとして返却
				return SonikLib::SharedSmtPtr<SonikFOSInterface>();
			};

			lp->p_mfunc_ = set_func;

			return SonikLib::SharedSmtPtr<SonikFOSInterface>(lp);
		};

		inline void Run(void)
		{
			(*p_mfunc_)(Arg1Val, Arg2Val, Arg3Val, Arg4Val, Arg5Val, Arg6Val);
			MethodStatus = true;
		};

	};

	//戻り値有り、引数5
	template<class Rtype, class Type, class Arg1_Val, class Arg2_Val, class Arg3_Val, class Arg4_Val, class Arg5_Val, std::enable_if_t<!std::is_pointer_v<Type>, bool> = true>
	class Members_5_FuncR : public SonikFOSTemplateInterface<Rtype>
	{
	private:
		Arg1_Val  Arg1Val;
		Arg2_Val  Arg2Val;
		Arg3_Val  Arg3Val;
		Arg4_Val  Arg4Val;
		Arg5_Val  Arg5Val;

		SonikLib::SharedSmtPtr<Type> object_;
		Rtype (Type::*p_mfunc_)(Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val);

	private:
		Members_5_FuncR(void)
		:object_(nullptr)
		,p_mfunc_(nullptr)
		{
			//member value initialize only
		};

		Members_5_FuncR(Arg1_Val Val1_, Arg2_Val Val2_, Arg3_Val Val3_, Arg4_Val Val4_, Arg5_Val Val5_)
		:Arg1Val(Val1_)
		,Arg2Val(Val2_)
		,Arg3Val(Val3_)
		,Arg4Val(Val4_)
		,Arg5Val(Val5_)
		,object_(nullptr)
		,p_mfunc_(nullptr)
		{
			//member value initialize only
		};

	public:
		~Members_5_FuncR(void)
		{
			if(this->Destroy_ == false)
			{
				//オブジェクト削除フラグがfalseなら勝手にdeleteしてはいけないので
				//ダミーを使ってスマートポインタからオーナー権限を除去し、dummyのdeleteを呼ばない。
				Type* _dymmy = nullptr;
				object_.GetOwnerPointer(_dymmy);
			};

		};

		//SharedSmtPtr指定
		inline static  SonikLib::SharedSmtPtr<SonikFOSTemplateInterface<Rtype>> New(SonikLib::SharedSmtPtr<Type> _SetObj_, Rtype (Type::*set_func)(Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val) , Arg1_Val Val1_, Arg2_Val Val2_, Arg3_Val Val3_, Arg4_Val Val4_, Arg5_Val Val5_, void* _allocate_ = nullptr)
		{
			Members_5_FuncR<Rtype, Type, Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val>* lp = nullptr;

			//三項演算子 　(条件) ? 真の時の処理 : 偽の時の処理
			//長いので縦にしただけ。つまり下記。
			//(条件)
			//? 真の時の処理
			//: 偽の時の処理
			(_allocate_ != nullptr)
			? lp = new(_allocate_) Members_5_FuncR<Rtype, Type, Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val>(Val1_, Val2_, Val3_, Val4_, Val5_)
			: lp = new(std::nothrow) Members_5_FuncR<Rtype, Type, Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val>(Val1_, Val2_, Val3_, Val4_, Val5_);

			if(lp == nullptr)
			{
				//失敗時はnullptrとして返却
				return SonikLib::SharedSmtPtr<SonikFOSTemplateInterface<Rtype>>();
			};

			lp->object_ = _SetObj_;
			lp->p_mfunc_ = set_func;

			return SonikLib::SharedSmtPtr<SonikFOSTemplateInterface<Rtype>>(lp);
		};
		//RawPointer指定
		inline static  SonikLib::SharedSmtPtr<SonikFOSTemplateInterface<Rtype>> New(Type* _SetObj_, Rtype (Type::*set_func)(Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val) , Arg1_Val Val1_, Arg2_Val Val2_, Arg3_Val Val3_, Arg4_Val Val4_, Arg5_Val Val5_, void* _allocate_ = nullptr)
		{
			Members_5_FuncR<Rtype, Type, Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val>* lp = nullptr;

			if(_SetObj_ == nullptr)
			{
				//Global版ではないのにnullptrを指定されたらそのまま返却。
				return SonikLib::SharedSmtPtr<SonikFOSTemplateInterface<Rtype>>();
			};

			//三項演算子 　(条件) ? 真の時の処理 : 偽の時の処理
			//長いので縦にしただけ。つまり下記。
			//(条件)
			//? 真の時の処理
			//: 偽の時の処理
			(_allocate_ != nullptr)
			? lp = new(_allocate_) Members_5_FuncR<Rtype, Type, Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val>(Val1_, Val2_, Val3_, Val4_, Val5_)
			: lp = new(std::nothrow) Members_5_FuncR<Rtype, Type, Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val>(Val1_, Val2_, Val3_, Val4_, Val5_);

			if(lp == nullptr)
			{
				//失敗時はnullptrとして返却
				return SonikLib::SharedSmtPtr<SonikFOSTemplateInterface<Rtype>>();
			};

			lp->object_ = SonikLib::SharedSmtPtr<Type>(_SetObj_);
			lp->p_mfunc_ = set_func;

			return SonikLib::SharedSmtPtr<SonikFOSTemplateInterface<Rtype>>(lp);
		};

		inline Rtype Run(void)
		{
			Rtype ret;

			if( object_.IsNullptr() )
			{
				return 0;
			};

			ret = (object_->*p_mfunc_)(Arg1Val, Arg2Val, Arg3Val, Arg4Val, Arg5Val);
			this->MethodStatus = true;

			return ret;
		};

	};
	//戻り値無し、引数5
	template<class Type, class Arg1_Val, class Arg2_Val, class Arg3_Val, class Arg4_Val, class Arg5_Val, std::enable_if_t<!std::is_pointer_v<Type>, bool> = true>
	class Members_5_Func : public SonikFOSInterface
	{
	private:
		Arg1_Val  Arg1Val;
		Arg2_Val  Arg2Val;
		Arg3_Val  Arg3Val;
		Arg4_Val  Arg4Val;
		Arg5_Val  Arg5Val;

		SonikLib::SharedSmtPtr<Type> object_;
		void (Type::*p_mfunc_)(Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val);

	private:
		Members_5_Func(void)
		:object_(nullptr)
		,p_mfunc_(nullptr)
		{
			//member value initialize only
		};

		Members_5_Func(Arg1_Val Val1_, Arg2_Val Val2_, Arg3_Val Val3_, Arg4_Val Val4_, Arg5_Val Val5_)
		:Arg1Val(Val1_)
		,Arg2Val(Val2_)
		,Arg3Val(Val3_)
		,Arg4Val(Val4_)
		,Arg5Val(Val5_)
		,object_(nullptr)
		,p_mfunc_(nullptr)
		{
			//member value initialize only
		};

	public:
		~Members_5_Func(void)
		{
			if(this->Destroy_ == false)
			{
				//オブジェクト削除フラグがfalseなら勝手にdeleteしてはいけないので
				//ダミーを使ってスマートポインタからオーナー権限を除去し、dummyのdeleteを呼ばない。
				Type* _dymmy = nullptr;
				object_.GetOwnerPointer(_dymmy);
			};

		};

		//SharedSmtPtr指定
		inline static  SonikLib::SharedSmtPtr<SonikFOSInterface> New(SonikLib::SharedSmtPtr<Type> _SetObj_, void (Type::*set_func)(Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val) , Arg1_Val Val1_, Arg2_Val Val2_, Arg3_Val Val3_, Arg4_Val Val4_, Arg5_Val Val5_, void* _allocate_ = nullptr)
		{
			Members_5_Func<Type, Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val>* lp = nullptr;

			//三項演算子 　(条件) ? 真の時の処理 : 偽の時の処理
			//長いので縦にしただけ。つまり下記。
			//(条件)
			//? 真の時の処理
			//: 偽の時の処理
			(_allocate_ != nullptr)
			? lp = new(_allocate_) Members_5_Func<Type, Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val>(Val1_, Val2_, Val3_, Val4_, Val5_)
			: lp = new(std::nothrow) Members_5_Func<Type, Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val>(Val1_, Val2_, Val3_, Val4_, Val5_);

			if(lp == nullptr)
			{
				//失敗時はnullptrとして返却
				return SonikLib::SharedSmtPtr<SonikFOSInterface>();
			};

			lp->object_ = _SetObj_;
			lp->p_mfunc_ = set_func;

			return SonikLib::SharedSmtPtr<SonikFOSInterface>(lp);
		};
		//RawPointer指定
		inline static  SonikLib::SharedSmtPtr<SonikFOSInterface> New(Type* _SetObj_, void (Type::*set_func)(Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val) , Arg1_Val Val1_, Arg2_Val Val2_, Arg3_Val Val3_, Arg4_Val Val4_, Arg5_Val Val5_, void* _allocate_ = nullptr)
		{
			Members_5_Func<Type, Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val>* lp = nullptr;

			if(_SetObj_ == nullptr)
			{
				//Global版ではないのにnullptrを指定されたらそのまま返却。
				return  SonikLib::SharedSmtPtr<SonikFOSInterface>();
			};

			//三項演算子 　(条件) ? 真の時の処理 : 偽の時の処理
			//長いので縦にしただけ。つまり下記。
			//(条件)
			//? 真の時の処理
			//: 偽の時の処理
			(_allocate_ != nullptr)
			? lp = new(_allocate_) Members_5_Func<Type, Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val>(Val1_, Val2_, Val3_, Val4_, Val5_)
			: lp = new(std::nothrow) Members_5_Func<Type, Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val>(Val1_, Val2_, Val3_, Val4_, Val5_);

			if(lp == nullptr)
			{
				//失敗時はnullptrとして返却
				return SonikLib::SharedSmtPtr<SonikFOSInterface>();
			};

			lp->object_ = SonikLib::SharedSmtPtr<Type>(_SetObj_);
			lp->p_mfunc_ = set_func;

			return SonikLib::SharedSmtPtr<SonikFOSInterface>(lp);
		};

		inline void Run(void)
		{
			if( object_.IsNullptr() )
			{
				return;
			};

			(object_->*p_mfunc_)(Arg1Val, Arg2Val, Arg3Val, Arg4Val, Arg5Val);
			MethodStatus = true;
		};

	};
	//戻り値有り、引数5 グローバル用
	template<class Rtype, class Arg1_Val, class Arg2_Val, class Arg3_Val, class Arg4_Val, class Arg5_Val>
	class Members_5_FuncRG : public SonikFOSTemplateInterface<Rtype>
	{
	private:
		Arg1_Val  Arg1Val;
		Arg2_Val  Arg2Val;
		Arg3_Val  Arg3Val;
		Arg4_Val  Arg4Val;
		Arg5_Val  Arg5Val;

		Rtype (*p_mfunc_)(Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val);

	private:
		Members_5_FuncRG(void)
		:p_mfunc_(nullptr)
		{
			//member value initialize only
		};

		Members_5_FuncRG(Arg1_Val Val1_, Arg2_Val Val2_, Arg3_Val Val3_, Arg4_Val Val4_, Arg5_Val Val5_)
		:Arg1Val(Val1_)
		,Arg2Val(Val2_)
		,Arg3Val(Val3_)
		,Arg4Val(Val4_)
		,Arg5Val(Val5_)
		,p_mfunc_(nullptr)
		{
			//member value initialize only
		};

	public:
		~Members_5_FuncRG(void)
		{
			//no process;
		};

		//グローバル関数指定なので、クラス指定のようにshared版とか無い。
		inline static  SonikLib::SharedSmtPtr<SonikFOSTemplateInterface<Rtype>> New(Rtype (*set_func)(Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val) , Arg1_Val Val1_, Arg2_Val Val2_, Arg3_Val Val3_, Arg4_Val Val4_, Arg5_Val Val5_, void* _allocate_ = nullptr)
		{
			Members_5_FuncRG<Rtype, Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val>* lp = nullptr;

			//三項演算子 　(条件) ? 真の時の処理 : 偽の時の処理
			//長いので縦にしただけ。つまり下記。
			//(条件)
			//? 真の時の処理
			//: 偽の時の処理
			(_allocate_ != nullptr)
			? lp = new(_allocate_) Members_5_FuncRG<Rtype, Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val>(Val1_, Val2_, Val3_, Val4_, Val5_)
			: lp = new(std::nothrow) Members_5_FuncRG<Rtype, Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val>(Val1_, Val2_, Val3_, Val4_, Val5_);

			if(lp == nullptr)
			{
				//失敗時はnullptrとして返却
				return SonikLib::SharedSmtPtr<SonikFOSTemplateInterface<Rtype>>();
			};

			lp->p_mfunc_ = set_func;

			return SonikLib::SharedSmtPtr<SonikFOSTemplateInterface<Rtype>>(lp);
		};

		inline Rtype Run(void)
		{
			Rtype ret;

			ret = (*p_mfunc_)(Arg1Val, Arg2Val, Arg3Val, Arg4Val, Arg5Val);
			this->MethodStatus = true;

			return ret;
		};

	};
	//戻り値無し、引数5 グローバル用
	template<class Arg1_Val, class Arg2_Val, class Arg3_Val, class Arg4_Val, class Arg5_Val>
	class Members_5_FuncG : public SonikFOSInterface
	{
	private:
		Arg1_Val  Arg1Val;
		Arg2_Val  Arg2Val;
		Arg3_Val  Arg3Val;
		Arg4_Val  Arg4Val;
		Arg5_Val  Arg5Val;

		void (*p_mfunc_)(Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val);

	public:
		Members_5_FuncG(void)
		:p_mfunc_(nullptr)
		{
			//member value initialize only
		};

		Members_5_FuncG(Arg1_Val Val1_, Arg2_Val Val2_, Arg3_Val Val3_, Arg4_Val Val4_, Arg5_Val Val5_)
		:Arg1Val(Val1_)
		,Arg2Val(Val2_)
		,Arg3Val(Val3_)
		,Arg4Val(Val4_)
		,Arg5Val(Val5_)
		,p_mfunc_(nullptr)
		{
			//member value initialize only
		};

		~Members_5_FuncG(void)
		{
			//no process;
		};

		//グローバル関数指定なので、クラス指定のようにshared版とか無い。
		inline static  SonikLib::SharedSmtPtr<SonikFOSInterface> New(void (*set_func)(Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val) , Arg1_Val Val1_, Arg2_Val Val2_, Arg3_Val Val3_, Arg4_Val Val4_, Arg5_Val Val5_, void* _allocate_ = nullptr)
		{
			Members_5_FuncG< Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val>* lp = nullptr;

			//三項演算子 　(条件) ? 真の時の処理 : 偽の時の処理
			//長いので縦にしただけ。つまり下記。
			//(条件)
			//? 真の時の処理
			//: 偽の時の処理
			(_allocate_ != nullptr)
			? lp = new(_allocate_) Members_5_FuncG< Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val>(Val1_, Val2_, Val3_, Val4_, Val5_)
			: lp = new(std::nothrow) Members_5_FuncG< Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val, Arg5_Val>(Val1_, Val2_, Val3_, Val4_, Val5_);

			if(lp == nullptr)
			{
				//失敗時はnullptrとして返却
				return SonikLib::SharedSmtPtr<SonikFOSInterface>();
			};

			lp->p_mfunc_ = set_func;

			return SonikLib::SharedSmtPtr<SonikFOSInterface>(lp);
		};

		inline void Run(void)
		{
			(*p_mfunc_)(Arg1Val, Arg2Val, Arg3Val, Arg4Val, Arg5Val);
			MethodStatus = true;
		};

	};

	//戻り値有り、引数4
	template<class Rtype, class Type, class Arg1_Val, class Arg2_Val, class Arg3_Val, class Arg4_Val, std::enable_if_t<!std::is_pointer_v<Type>, bool> = true>
	class Members_4_FuncR : public SonikFOSTemplateInterface<Rtype>
	{
	private:
		Arg1_Val  Arg1Val;
		Arg2_Val  Arg2Val;
		Arg3_Val  Arg3Val;
		Arg4_Val  Arg4Val;

		SonikLib::SharedSmtPtr<Type> object_;
		Rtype (Type::*p_mfunc_)(Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val);

	private:
		Members_4_FuncR(void)
		:object_(nullptr)
		,p_mfunc_(nullptr)
		{
			//member value initialize only
		};

		Members_4_FuncR(Arg1_Val Val1_, Arg2_Val Val2_, Arg3_Val Val3_, Arg4_Val Val4_)
		:Arg1Val(Val1_)
		,Arg2Val(Val2_)
		,Arg3Val(Val3_)
		,Arg4Val(Val4_)
		,object_(nullptr)
		,p_mfunc_(nullptr)
		{
			//member value initialize only
		};

	public:
		~Members_4_FuncR(void)
		{
			if(this->Destroy_ == false)
			{
				//オブジェクト削除フラグがfalseなら勝手にdeleteしてはいけないので
				//ダミーを使ってスマートポインタからオーナー権限を除去し、dummyのdeleteを呼ばない。
				Type* _dymmy = nullptr;
				object_.GetOwnerPointer(_dymmy);
			};

		};

		//SharedSmtPtr指定
		inline static  SonikLib::SharedSmtPtr<SonikFOSTemplateInterface<Rtype>> New(SonikLib::SharedSmtPtr<Type> _SetObj_, Rtype (Type::*set_func)(Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val) , Arg1_Val Val1_, Arg2_Val Val2_, Arg3_Val Val3_, Arg4_Val Val4_, void* _allocate_ = nullptr)
		{
			Members_4_FuncR<Rtype, Type, Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val>* lp = nullptr;

			//三項演算子 　(条件) ? 真の時の処理 : 偽の時の処理
			//長いので縦にしただけ。つまり下記。
			//(条件)
			//? 真の時の処理
			//: 偽の時の処理
			(_allocate_ != nullptr)
			? lp = new(_allocate_) Members_4_FuncR<Rtype, Type, Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val>(Val1_, Val2_, Val3_, Val4_)
			: lp = new(std::nothrow) Members_4_FuncR<Rtype, Type, Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val>(Val1_, Val2_, Val3_, Val4_);

			if(lp == nullptr)
			{
				//失敗時はnullptrとして返却
				return SonikLib::SharedSmtPtr<SonikFOSTemplateInterface<Rtype>>();
			};

			lp->object_ = _SetObj_;
			lp->p_mfunc_ = set_func;

			return SonikLib::SharedSmtPtr<SonikFOSTemplateInterface<Rtype>>(lp);
		};
		//RawPointer指定
		inline static  SonikLib::SharedSmtPtr<SonikFOSTemplateInterface<Rtype>> New(Type* _SetObj_, Rtype (Type::*set_func)(Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val) , Arg1_Val Val1_, Arg2_Val Val2_, Arg3_Val Val3_, Arg4_Val Val4_, void* _allocate_ = nullptr)
		{
			Members_4_FuncR<Rtype, Type, Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val>* lp = nullptr;

			if(_SetObj_ == nullptr)
			{
				//Global版ではないのにnullptrを指定されたらそのまま返却。
				return SonikLib::SharedSmtPtr<SonikFOSTemplateInterface<Rtype>>();
			};

			//三項演算子 　(条件) ? 真の時の処理 : 偽の時の処理
			//長いので縦にしただけ。つまり下記。
			//(条件)
			//? 真の時の処理
			//: 偽の時の処理
			(_allocate_ != nullptr)
			? lp = new(_allocate_) Members_4_FuncR<Rtype, Type, Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val>(Val1_, Val2_, Val3_, Val4_)
			: lp = new(std::nothrow) Members_4_FuncR<Rtype, Type, Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val>(Val1_, Val2_, Val3_, Val4_);

			if(lp == nullptr)
			{
				//失敗時はnullptrとして返却
				return SonikLib::SharedSmtPtr<SonikFOSTemplateInterface<Rtype>>();
			};

			lp->object_ = SonikLib::SharedSmtPtr<Type>(_SetObj_);
			lp->p_mfunc_ = set_func;

			return SonikLib::SharedSmtPtr<SonikFOSTemplateInterface<Rtype>>(lp);
		};

		inline Rtype Run(void)
		{
			Rtype ret;

			if( object_.IsNullptr() )
			{
				return 0;
			};

			ret = (object_->*p_mfunc_)(Arg1Val, Arg2Val, Arg3Val, Arg4Val);
			this->MethodStatus = true;

			return ret;
		};

	};
	//戻り値無し、引数4
	template<class Type, class Arg1_Val, class Arg2_Val, class Arg3_Val, class Arg4_Val, std::enable_if_t<!std::is_pointer_v<Type>, bool> = true>
	class Members_4_Func : public SonikFOSInterface
	{
	private:
		Arg1_Val  Arg1Val;
		Arg2_Val  Arg2Val;
		Arg3_Val  Arg3Val;
		Arg4_Val  Arg4Val;

		SonikLib::SharedSmtPtr<Type> object_;
		void (Type::*p_mfunc_)(Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val);

	private:
		Members_4_Func(void)
		:object_(nullptr)
		,p_mfunc_(nullptr)
		{
			//member value initialize only
		};

		Members_4_Func(Arg1_Val Val1_, Arg2_Val Val2_, Arg3_Val Val3_, Arg4_Val Val4_)
		:Arg1Val(Val1_)
		,Arg2Val(Val2_)
		,Arg3Val(Val3_)
		,Arg4Val(Val4_)
		,object_(nullptr)
		,p_mfunc_(nullptr)
		{
			//member value initialize only
		};

	public:
		~Members_4_Func(void)
		{
			if(this->Destroy_ == false)
			{
				//オブジェクト削除フラグがfalseなら勝手にdeleteしてはいけないので
				//ダミーを使ってスマートポインタからオーナー権限を除去し、dummyのdeleteを呼ばない。
				Type* _dymmy = nullptr;
				object_.GetOwnerPointer(_dymmy);
			};

		};

		//SharedSmtPtr指定
		inline static  SonikLib::SharedSmtPtr<SonikFOSInterface> New(SonikLib::SharedSmtPtr<Type> _SetObj_, void (Type::*set_func)(Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val) , Arg1_Val Val1_, Arg2_Val Val2_, Arg3_Val Val3_, Arg4_Val Val4_, void* _allocate_ = nullptr)
		{
			Members_4_Func<Type, Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val>* lp = nullptr;

			//三項演算子 　(条件) ? 真の時の処理 : 偽の時の処理
			//長いので縦にしただけ。つまり下記。
			//(条件)
			//? 真の時の処理
			//: 偽の時の処理
			(_allocate_ != nullptr)
			? lp = new(_allocate_) Members_4_Func<Type, Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val>(Val1_, Val2_, Val3_, Val4_)
			: lp = new(std::nothrow) Members_4_Func<Type, Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val>(Val1_, Val2_, Val3_, Val4_);

			if(lp == nullptr)
			{
				//失敗時はnullptrとして返却
				return SonikLib::SharedSmtPtr<SonikFOSInterface>();
			};

			lp->object_ = _SetObj_;
			lp->p_mfunc_ = set_func;

			return SonikLib::SharedSmtPtr<SonikFOSInterface>(lp);
		};
		//RawPointer指定
		inline static  SonikLib::SharedSmtPtr<SonikFOSInterface> New(Type* _SetObj_, void (Type::*set_func)(Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val) , Arg1_Val Val1_, Arg2_Val Val2_, Arg3_Val Val3_, Arg4_Val Val4_, void* _allocate_ = nullptr)
		{
			Members_4_Func<Type, Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val>* lp = nullptr;

			if(_SetObj_ == nullptr)
			{
				//Global版ではないのにnullptrを指定されたらそのまま返却。
				return  SonikLib::SharedSmtPtr<SonikFOSInterface>();
			};

			//三項演算子 　(条件) ? 真の時の処理 : 偽の時の処理
			//長いので縦にしただけ。つまり下記。
			//(条件)
			//? 真の時の処理
			//: 偽の時の処理
			(_allocate_ != nullptr)
			? lp = new(_allocate_) Members_4_Func<Type, Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val>(Val1_, Val2_, Val3_, Val4_)
			: lp = new(std::nothrow) Members_4_Func<Type, Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val>(Val1_, Val2_, Val3_, Val4_);

			if(lp == nullptr)
			{
				//失敗時はnullptrとして返却
				return SonikLib::SharedSmtPtr<SonikFOSInterface>();
			};

			lp->object_ = SonikLib::SharedSmtPtr<Type>(_SetObj_);
			lp->p_mfunc_ = set_func;

			return SonikLib::SharedSmtPtr<SonikFOSInterface>(lp);
		};

		inline void Run(void)
		{
			if( object_.IsNullptr())
			{
				return;
			};

			(object_->*p_mfunc_)(Arg1Val, Arg2Val, Arg3Val, Arg4Val);
			MethodStatus = true;
		};

	};
	//戻り値有り、引数4 グローバル用
	template<class Rtype, class Arg1_Val, class Arg2_Val, class Arg3_Val, class Arg4_Val>
	class Members_4_FuncRG : public SonikFOSTemplateInterface<Rtype>
	{
	private:
		Arg1_Val  Arg1Val;
		Arg2_Val  Arg2Val;
		Arg3_Val  Arg3Val;
		Arg4_Val  Arg4Val;

		Rtype (*p_mfunc_)(Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val);

	private:
		Members_4_FuncRG(void)
		:p_mfunc_(nullptr)
		{
			//member value initialzie only
		};

		Members_4_FuncRG(Arg1_Val Val1_, Arg2_Val Val2_, Arg3_Val Val3_, Arg4_Val Val4_)
		:Arg1Val(Val1_)
		,Arg2Val(Val2_)
		,Arg3Val(Val3_)
		,Arg4Val(Val4_)
		,p_mfunc_(nullptr)
		{
			//member value initialzie only
		};

	public:
		~Members_4_FuncRG(void)
		{
			//no process;
		};

		//グローバル関数指定なので、クラス指定のようにshared版とか無い。
		inline static  SonikLib::SharedSmtPtr<SonikFOSTemplateInterface<Rtype>> New(Rtype (*set_func)(Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val) , Arg1_Val Val1_, Arg2_Val Val2_, Arg3_Val Val3_, Arg4_Val Val4_, void* _allocate_ = nullptr)
		{
			Members_4_FuncRG<Rtype, Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val>* lp = nullptr;

			//三項演算子 　(条件) ? 真の時の処理 : 偽の時の処理
			//長いので縦にしただけ。つまり下記。
			//(条件)
			//? 真の時の処理
			//: 偽の時の処理
			(_allocate_ != nullptr)
			? lp = new(_allocate_) Members_4_FuncRG<Rtype, Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val>(Val1_, Val2_, Val3_, Val4_)
			: lp = new(std::nothrow) Members_4_FuncRG<Rtype, Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val>(Val1_, Val2_, Val3_, Val4_);

			if(lp == nullptr)
			{
				//失敗時はnullptrとして返却
				return SonikLib::SharedSmtPtr<SonikFOSTemplateInterface<Rtype>>();
			};

			lp->p_mfunc_ = set_func;

			return SonikLib::SharedSmtPtr<SonikFOSTemplateInterface<Rtype>>(lp);
		};

		inline Rtype Run(void)
		{
			Rtype ret;

			ret = (*p_mfunc_)(Arg1Val, Arg2Val, Arg3Val, Arg4Val);
			this->MethodStatus = true;

			return ret;
		};

	};
	//戻り値無し、引数4 グローバル用
	template<class Arg1_Val, class Arg2_Val, class Arg3_Val, class Arg4_Val>
	class Members_4_FuncG : public SonikFOSInterface
	{
	private:
		Arg1_Val  Arg1Val;
		Arg2_Val  Arg2Val;
		Arg3_Val  Arg3Val;
		Arg4_Val  Arg4Val;

		void (*p_mfunc_)(Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val);

	private:
		Members_4_FuncG(void)
		:p_mfunc_(nullptr)
		{
			//member value initialize only
		};

		Members_4_FuncG(Arg1_Val Val1_, Arg2_Val Val2_, Arg3_Val Val3_, Arg4_Val Val4_)
		:Arg1Val(Val1_)
		,Arg2Val(Val2_)
		,Arg3Val(Val3_)
		,Arg4Val(Val4_)
		,p_mfunc_(nullptr)
		{
			//member value initialize only
		};

	public:
		~Members_4_FuncG(void)
		{
			//no process;
		};

		//グローバル関数指定なので、クラス指定のようにshared版とか無い。
		inline static  SonikLib::SharedSmtPtr<SonikFOSInterface> New(void (*set_func)(Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val) , Arg1_Val Val1_, Arg2_Val Val2_, Arg3_Val Val3_, Arg4_Val Val4_, void* _allocate_ = nullptr)
		{
			Members_4_FuncG< Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val>* lp = nullptr;

			//三項演算子 　(条件) ? 真の時の処理 : 偽の時の処理
			//長いので縦にしただけ。つまり下記。
			//(条件)
			//? 真の時の処理
			//: 偽の時の処理
			(_allocate_ != nullptr)
			? lp = new(_allocate_) Members_4_FuncG< Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val>(Val1_, Val2_, Val3_, Val4_)
			: lp = new(std::nothrow) Members_4_FuncG< Arg1_Val, Arg2_Val, Arg3_Val, Arg4_Val>(Val1_, Val2_, Val3_, Val4_);

			if(lp == nullptr)
			{
				//失敗時はnullptrとして返却
				return SonikLib::SharedSmtPtr<SonikFOSInterface>();
			};

			lp->p_mfunc_ = set_func;

			return SonikLib::SharedSmtPtr<SonikFOSInterface>(lp);
		};

		inline void Run(void)
		{
			(*p_mfunc_)(Arg1Val, Arg2Val, Arg3Val, Arg4Val);
			MethodStatus = true;
		};

	};

	//戻り値有り、引数3
	template<class Rtype, class Type, class Arg1_Val, class Arg2_Val, class Arg3_Val, std::enable_if_t<!std::is_pointer_v<Type>, bool> = true>
	class Members_3_FuncR : public SonikFOSTemplateInterface<Rtype>
	{
	private:
		Arg1_Val  Arg1Val;
		Arg2_Val  Arg2Val;
		Arg3_Val  Arg3Val;

		SonikLib::SharedSmtPtr<Type> object_;
		Rtype (Type::*p_mfunc_)(Arg1_Val, Arg2_Val, Arg3_Val);

	private:
		Members_3_FuncR(void)
		:object_(nullptr)
		,p_mfunc_(nullptr)
		{
			//member value initialize only
		};

		Members_3_FuncR(Arg1_Val Val1_, Arg2_Val Val2_, Arg3_Val Val3_)
		:Arg1Val(Val1_)
		,Arg2Val(Val2_)
		,Arg3Val(Val3_)
		,object_(nullptr)
		,p_mfunc_(nullptr)
		{
			//member value initialize only
		};

	public:
		~Members_3_FuncR(void)
		{
			if(this->Destroy_ == false)
			{
				//オブジェクト削除フラグがfalseなら勝手にdeleteしてはいけないので
				//ダミーを使ってスマートポインタからオーナー権限を除去し、dummyのdeleteを呼ばない。
				Type* _dymmy = nullptr;
				object_.GetOwnerPointer(_dymmy);
			};

		};

		//SharedSmtPtr指定
		inline static  SonikLib::SharedSmtPtr<SonikFOSTemplateInterface<Rtype>> New(SonikLib::SharedSmtPtr<Type> _SetObj_, Rtype (Type::*set_func)(Arg1_Val, Arg2_Val, Arg3_Val) , Arg1_Val Val1_, Arg2_Val Val2_, Arg3_Val Val3_, void* _allocate_ = nullptr)
		{
			Members_3_FuncR<Rtype, Type, Arg1_Val, Arg2_Val, Arg3_Val>* lp = nullptr;

			//三項演算子 　(条件) ? 真の時の処理 : 偽の時の処理
			//長いので縦にしただけ。つまり下記。
			//(条件)
			//? 真の時の処理
			//: 偽の時の処理
			(_allocate_ != nullptr)
			? lp = new(_allocate_) Members_3_FuncR<Rtype, Type, Arg1_Val, Arg2_Val, Arg3_Val>(Val1_, Val2_, Val3_)
			: lp = new(std::nothrow) Members_3_FuncR<Rtype, Type, Arg1_Val, Arg2_Val, Arg3_Val>(Val1_, Val2_, Val3_);

			if(lp == nullptr)
			{
				//失敗時はnullptrとして返却
				return SonikLib::SharedSmtPtr<SonikFOSTemplateInterface<Rtype>>();
			};

			lp->object_ = _SetObj_;
			lp->p_mfunc_ = set_func;

			return SonikLib::SharedSmtPtr<SonikFOSTemplateInterface<Rtype>>(lp);
		};
		//RawPointer指定
		inline static  SonikLib::SharedSmtPtr<SonikFOSTemplateInterface<Rtype>> New(Type* _SetObj_, Rtype (Type::*set_func)(Arg1_Val, Arg2_Val, Arg3_Val) , Arg1_Val Val1_, Arg2_Val Val2_, Arg3_Val Val3_, void* _allocate_ = nullptr)
		{
			Members_3_FuncR<Rtype, Type, Arg1_Val, Arg2_Val, Arg3_Val>* lp = nullptr;

			if(_SetObj_ == nullptr)
			{
				//Global版ではないのにnullptrを指定されたらそのまま返却。
				return SonikLib::SharedSmtPtr<SonikFOSTemplateInterface<Rtype>>();
			};

			//三項演算子 　(条件) ? 真の時の処理 : 偽の時の処理
			//長いので縦にしただけ。つまり下記。
			//(条件)
			//? 真の時の処理
			//: 偽の時の処理
			(_allocate_ != nullptr)
			? lp = new(_allocate_) Members_3_FuncR<Rtype, Type, Arg1_Val, Arg2_Val, Arg3_Val>(Val1_, Val2_, Val3_)
			: lp = new(std::nothrow) Members_3_FuncR<Rtype, Type, Arg1_Val, Arg2_Val, Arg3_Val>(Val1_, Val2_, Val3_);

			if(lp == nullptr)
			{
				//失敗時はnullptrとして返却
				return SonikLib::SharedSmtPtr<SonikFOSTemplateInterface<Rtype>>();
			};

			lp->object_ = SonikLib::SharedSmtPtr<Type>(_SetObj_);
			lp->p_mfunc_ = set_func;

			return SonikLib::SharedSmtPtr<SonikFOSTemplateInterface<Rtype>>(lp);
		};

		inline Rtype Run(void)
		{
			Rtype ret;

			if( object_.IsNullptr())
			{
				return 0;
			};

			ret = (object_->*p_mfunc_)(Arg1Val, Arg2Val, Arg3Val);
			this->MethodStatus = true;

			return ret;
		};

	};
	//戻り値無し、引数3(自作スレッドプールで使用する型です。でも他に使いたければどうぞ)
	template<class Type, class Arg1_Val, class Arg2_Val, class Arg3_Val, std::enable_if_t<!std::is_pointer_v<Type>, bool> = true>
	class Members_3_Func : public SonikFOSInterface
	{
	private:
		Arg1_Val  Arg1Val;
		Arg2_Val  Arg2Val;
		Arg3_Val  Arg3Val;

		SonikLib::SharedSmtPtr<Type> object_;
		void (Type::*p_mfunc_)(Arg1_Val, Arg2_Val, Arg3_Val);

	private:
		Members_3_Func(void)
		:object_(nullptr)
		,p_mfunc_(nullptr)
		{
			//member value initialize only
		};

		Members_3_Func(Arg1_Val Val1_, Arg2_Val Val2_, Arg3_Val Val3_)
		:Arg1Val(Val1_)
		,Arg2Val(Val2_)
		,Arg3Val(Val3_)
		,object_(nullptr)
		,p_mfunc_(nullptr)
		{
			//member value initialize only
		};

	public:
		~Members_3_Func(void)
		{
			if(this->Destroy_ == false)
			{
				//オブジェクト削除フラグがfalseなら勝手にdeleteしてはいけないので
				//ダミーを使ってスマートポインタからオーナー権限を除去し、dummyのdeleteを呼ばない。
				Type* _dymmy = nullptr;
				object_.GetOwnerPointer(_dymmy);
			};

		};

		//SharedSmtPtr指定
		inline static  SonikLib::SharedSmtPtr<SonikFOSInterface> New(SonikLib::SharedSmtPtr<Type> _SetObj_, void (Type::*set_func)(Arg1_Val, Arg2_Val, Arg3_Val) , Arg1_Val Val1_, Arg2_Val Val2_, Arg3_Val Val3_, void* _allocate_ = nullptr)
		{
			Members_3_Func<Type, Arg1_Val, Arg2_Val, Arg3_Val>* lp = nullptr;

			//三項演算子 　(条件) ? 真の時の処理 : 偽の時の処理
			//長いので縦にしただけ。つまり下記。
			//(条件)
			//? 真の時の処理
			//: 偽の時の処理
			(_allocate_ != nullptr)
			? lp = new(_allocate_) Members_3_Func<Type, Arg1_Val, Arg2_Val, Arg3_Val>(Val1_, Val2_, Val3_)
			: lp = new(std::nothrow) Members_3_Func<Type, Arg1_Val, Arg2_Val, Arg3_Val>(Val1_, Val2_, Val3_);

			if(lp == nullptr)
			{
				//失敗時はnullptrとして返却
				return SonikLib::SharedSmtPtr<SonikFOSInterface>();
			};

			lp->object_ = _SetObj_;
			lp->p_mfunc_ = set_func;

			return SonikLib::SharedSmtPtr<SonikFOSInterface>(lp);
		};
		//RawPointer指定
		inline static  SonikLib::SharedSmtPtr<SonikFOSInterface> New(Type* _SetObj_, void (Type::*set_func)(Arg1_Val, Arg2_Val, Arg3_Val) , Arg1_Val Val1_, Arg2_Val Val2_, Arg3_Val Val3_, void* _allocate_ = nullptr)
		{
			Members_3_Func<Type, Arg1_Val, Arg2_Val, Arg3_Val>* lp = nullptr;

			if(_SetObj_ == nullptr)
			{
				//Global版ではないのにnullptrを指定されたらそのまま返却。
				return  SonikLib::SharedSmtPtr<SonikFOSInterface>();
			};

			//三項演算子 　(条件) ? 真の時の処理 : 偽の時の処理
			//長いので縦にしただけ。つまり下記。
			//(条件)
			//? 真の時の処理
			//: 偽の時の処理
			(_allocate_ != nullptr)
			? lp = new(_allocate_) Members_3_Func<Type, Arg1_Val, Arg2_Val, Arg3_Val>(Val1_, Val2_, Val3_)
			: lp = new(std::nothrow) Members_3_Func<Type, Arg1_Val, Arg2_Val, Arg3_Val>(Val1_, Val2_, Val3_);

			if(lp == nullptr)
			{
				//失敗時はnullptrとして返却
				return SonikLib::SharedSmtPtr<SonikFOSInterface>();
			};

			lp->object_ = SonikLib::SharedSmtPtr<Type>(_SetObj_);
			lp->p_mfunc_ = set_func;

			return SonikLib::SharedSmtPtr<SonikFOSInterface>(lp);
		};

		inline void Run(void)
		{
			if( object_.IsNullptr() )
			{
				return;
			};

			(object_->*p_mfunc_)(Arg1Val, Arg2Val, Arg3Val);
			MethodStatus = true;
		};

	};
	//戻り値有り、引数3 グローバル用
	template<class Rtype, class Arg1_Val, class Arg2_Val, class Arg3_Val>
	class Members_3_FuncRG : public SonikFOSTemplateInterface<Rtype>
	{
	private:
		Arg1_Val  Arg1Val;
		Arg2_Val  Arg2Val;
		Arg3_Val  Arg3Val;

		Rtype (*p_mfunc_)(Arg1_Val, Arg2_Val, Arg3_Val);

	private:
		Members_3_FuncRG(void)
		:p_mfunc_(nullptr)
		{
			//member value initialize only
		};

		Members_3_FuncRG(Arg1_Val Val1_, Arg2_Val Val2_, Arg3_Val Val3_)
		:Arg1Val(Val1_)
		,Arg2Val(Val2_)
		,Arg3Val(Val3_)
		,p_mfunc_(nullptr)
		{
			//member value initialize only
		};

	public:
		~Members_3_FuncRG(void)
		{
			//no process;
		}

		//グローバル関数指定なので、クラス指定のようにshared版とか無い。
		inline static  SonikLib::SharedSmtPtr<SonikFOSTemplateInterface<Rtype>> New(Rtype (*set_func)(Arg1_Val, Arg2_Val, Arg3_Val) , Arg1_Val Val1_, Arg2_Val Val2_, Arg3_Val Val3_, void* _allocate_ = nullptr)
		{
			Members_3_FuncRG<Rtype, Arg1_Val, Arg2_Val, Arg3_Val>* lp = nullptr;

			//三項演算子 　(条件) ? 真の時の処理 : 偽の時の処理
			//長いので縦にしただけ。つまり下記。
			//(条件)
			//? 真の時の処理
			//: 偽の時の処理
			(_allocate_ != nullptr)
			? lp = new(_allocate_) Members_3_FuncRG<Rtype, Arg1_Val, Arg2_Val, Arg3_Val>(Val1_, Val2_, Val3_)
			: lp = new(std::nothrow) Members_3_FuncRG<Rtype, Arg1_Val, Arg2_Val, Arg3_Val>(Val1_, Val2_, Val3_);

			if(lp == nullptr)
			{
				//失敗時はnullptrとして返却
				return SonikLib::SharedSmtPtr<SonikFOSTemplateInterface<Rtype>>();
			};

			lp->p_mfunc_ = set_func;

			return SonikLib::SharedSmtPtr<SonikFOSTemplateInterface<Rtype>>(lp);
		};

		inline Rtype Run(void)
		{
			Rtype ret;

			ret = (*p_mfunc_)(Arg1Val, Arg2Val, Arg3Val);
			this->MethodStatus = true;

			return ret;
		};

	};
	//戻り値無し、引数3 グローバル用
	template<class Arg1_Val, class Arg2_Val, class Arg3_Val>
	class Members_3_FuncG : public SonikFOSInterface
	{
	private:
		Arg1_Val  Arg1Val;
		Arg2_Val  Arg2Val;
		Arg3_Val  Arg3Val;

		void (*p_mfunc_)(Arg1_Val, Arg2_Val, Arg3_Val);

	private:
		Members_3_FuncG(void)
		:p_mfunc_(nullptr)
		{
			//member value initialize only
		};

		Members_3_FuncG(Arg1_Val Val1_, Arg2_Val Val2_, Arg3_Val Val3_)
		:Arg1Val(Val1_)
		,Arg2Val(Val2_)
		,Arg3Val(Val3_)
		,p_mfunc_(nullptr)
		{
			//member value initialize only
		};

	public:
		~Members_3_FuncG(void)
		{
			//no process;
		};

		//グローバル関数指定なので、クラス指定のようにshared版とか無い。
		inline static  SonikLib::SharedSmtPtr<SonikFOSInterface> New(void (*set_func)(Arg1_Val, Arg2_Val, Arg3_Val) , Arg1_Val Val1_, Arg2_Val Val2_, Arg3_Val Val3_, void* _allocate_ = nullptr)
		{
			Members_3_FuncG< Arg1_Val, Arg2_Val, Arg3_Val>* lp = nullptr;

			//三項演算子 　(条件) ? 真の時の処理 : 偽の時の処理
			//長いので縦にしただけ。つまり下記。
			//(条件)
			//? 真の時の処理
			//: 偽の時の処理
			(_allocate_ != nullptr)
			? lp = new(_allocate_) Members_3_FuncG< Arg1_Val, Arg2_Val, Arg3_Val>(Val1_, Val2_, Val3_)
			: lp = new(std::nothrow) Members_3_FuncG< Arg1_Val, Arg2_Val, Arg3_Val>(Val1_, Val2_, Val3_);

			if(lp == nullptr)
			{
				//失敗時はnullptrとして返却
				return SonikLib::SharedSmtPtr<SonikFOSInterface>();
			};

			lp->p_mfunc_ = set_func;

			return SonikLib::SharedSmtPtr<SonikFOSInterface>(lp);
		};

		inline void Run(void)
		{

			(*p_mfunc_)(Arg1Val, Arg2Val, Arg3Val);
			MethodStatus = true;
		};

	};

	//戻り値有り、引数2
	template<class Rtype, class Type, class Arg1_Val, class Arg2_Val, std::enable_if_t<!std::is_pointer_v<Type>, bool> = true>
	class Members_2_FuncR : public SonikFOSTemplateInterface<Rtype>
	{
	private:
		Arg1_Val  Arg1Val;
		Arg2_Val  Arg2Val;

		SonikLib::SharedSmtPtr<Type> object_;
		Rtype (Type::*p_mfunc_)(Arg1_Val, Arg2_Val);

	private:
		Members_2_FuncR(void)
		:object_(nullptr)
		,p_mfunc_(nullptr)
		{
			//member value initialize only
		};

		Members_2_FuncR(Arg1_Val Val1_, Arg2_Val Val2_)
		:Arg1Val(Val1_)
		,Arg2Val(Val2_)
		,object_(nullptr)
		,p_mfunc_(nullptr)
		{
			//member value initialize only
		};

	public:
		~Members_2_FuncR(void)
		{
			if(this->Destroy_ == false)
			{
				//オブジェクト削除フラグがfalseなら勝手にdeleteしてはいけないので
				//ダミーを使ってスマートポインタからオーナー権限を除去し、dummyのdeleteを呼ばない。
				Type* _dymmy = nullptr;
				object_.GetOwnerPointer(_dymmy);
			};

		};

		//SharedSmtPtr指定
		inline static  SonikLib::SharedSmtPtr<SonikFOSTemplateInterface<Rtype>> New(SonikLib::SharedSmtPtr<Type> _SetObj_, Rtype (Type::*set_func)(Arg1_Val, Arg2_Val) , Arg1_Val Val1_, Arg2_Val Val2_, void* _allocate_ = nullptr)
		{
			Members_2_FuncR<Rtype, Type, Arg1_Val, Arg2_Val>* lp = nullptr;

			//三項演算子 　(条件) ? 真の時の処理 : 偽の時の処理
			//長いので縦にしただけ。つまり下記。
			//(条件)
			//? 真の時の処理
			//: 偽の時の処理
			(_allocate_ != nullptr)
			? lp = new(_allocate_) Members_2_FuncR<Rtype, Type, Arg1_Val, Arg2_Val>(Val1_, Val2_)
			: lp = new(std::nothrow) Members_2_FuncR<Rtype, Type, Arg1_Val, Arg2_Val>(Val1_, Val2_);

			if(lp == nullptr)
			{
				//失敗時はnullptrとして返却
				return SonikLib::SharedSmtPtr<SonikFOSTemplateInterface<Rtype>>();
			};

			lp->object_ = _SetObj_;
			lp->p_mfunc_ = set_func;

			return SonikLib::SharedSmtPtr<SonikFOSTemplateInterface<Rtype>>(lp);
		};
		//RawPointer指定
		static  SonikLib::SharedSmtPtr<SonikFOSTemplateInterface<Rtype>> New(Type* _SetObj_, Rtype (Type::*set_func)(Arg1_Val, Arg2_Val) , Arg1_Val Val1_, Arg2_Val Val2_, void* _allocate_ = nullptr)
		{
			Members_2_FuncR<Rtype, Type, Arg1_Val, Arg2_Val>* lp = nullptr;

			if(_SetObj_ == nullptr)
			{
				//Global版ではないのにnullptrを指定されたらそのまま返却。
				return SonikLib::SharedSmtPtr<SonikFOSTemplateInterface<Rtype>>();
			};

			//三項演算子 　(条件) ? 真の時の処理 : 偽の時の処理
			//長いので縦にしただけ。つまり下記。
			//(条件)
			//? 真の時の処理
			//: 偽の時の処理
			(_allocate_ != nullptr)
			? lp = new(_allocate_) Members_2_FuncR<Rtype, Type, Arg1_Val, Arg2_Val>(Val1_, Val2_)
			: lp = new(std::nothrow) Members_2_FuncR<Rtype, Type, Arg1_Val, Arg2_Val>(Val1_, Val2_);

			if(lp == nullptr)
			{
				//失敗時はnullptrとして返却
				return SonikLib::SharedSmtPtr<SonikFOSTemplateInterface<Rtype>>();
			};

			lp->object_ = SonikLib::SharedSmtPtr<Type>(_SetObj_);
			lp->p_mfunc_ = set_func;

			return SonikLib::SharedSmtPtr<SonikFOSTemplateInterface<Rtype>>(lp);
		};

		inline Rtype Run(void)
		{
			Rtype ret;

			if( object_.IsNullptr() )
			{
				return 0;
			};

			ret = (object_->*p_mfunc_)(Arg1Val, Arg2Val);
			this->MethodStatus = true;

			return ret;
		};

	};
	//戻り値無し、引数2(自作スレッドプールで使用する型です。でも他に使いたければどうぞ)
	template<class Type, class Arg1_Val, class Arg2_Val, std::enable_if_t<!std::is_pointer_v<Type>, bool> = true>
	class Members_2_Func : public SonikFOSInterface
	{
	private:
		Arg1_Val  Arg1Val;
		Arg2_Val  Arg2Val;

		SonikLib::SharedSmtPtr<Type> object_;
		void (Type::*p_mfunc_)(Arg1_Val, Arg2_Val);

	private:
		Members_2_Func(void)
		:object_(nullptr)
		,p_mfunc_(nullptr)
		{
			//member value initialize only
		};

		Members_2_Func(Arg1_Val Val1_, Arg2_Val Val2_)
		:Arg1Val(Val1_)
		,Arg2Val(Val2_)
		,object_(nullptr)
		,p_mfunc_(nullptr)
		{
			//member value initialize only
		};

	public:
		~Members_2_Func(void)
		{
			if(this->Destroy_ == false)
			{
				//オブジェクト削除フラグがfalseなら勝手にdeleteしてはいけないので
				//ダミーを使ってスマートポインタからオーナー権限を除去し、dummyのdeleteを呼ばない。
				Type* _dymmy = nullptr;
				object_.GetOwnerPointer(_dymmy);
			};

		};

		//SharedSmtPtr指定
		inline static  SonikLib::SharedSmtPtr<SonikFOSInterface> New(SonikLib::SharedSmtPtr<Type> _SetObj_, void (Type::*set_func)(Arg1_Val, Arg2_Val) , Arg1_Val Val1_, Arg2_Val Val2_, void* _allocate_ = nullptr)
		{
			Members_2_Func<Type, Arg1_Val, Arg2_Val>* lp = nullptr;

			//三項演算子 　(条件) ? 真の時の処理 : 偽の時の処理
			//長いので縦にしただけ。つまり下記。
			//(条件)
			//? 真の時の処理
			//: 偽の時の処理
			(_allocate_ != nullptr)
			? lp = new(_allocate_) Members_2_Func<Type, Arg1_Val, Arg2_Val>(Val1_, Val2_)
			: lp = new(std::nothrow) Members_2_Func<Type, Arg1_Val, Arg2_Val>(Val1_, Val2_);

			if(lp == nullptr)
			{
				//失敗時はnullptrとして返却
				return SonikLib::SharedSmtPtr<SonikFOSInterface>();
			};

			lp->object_ = _SetObj_;
			lp->p_mfunc_ = set_func;

			return SonikLib::SharedSmtPtr<SonikFOSInterface>(lp);
		};
		//RawPointer指定
		static  SonikLib::SharedSmtPtr<SonikFOSInterface> New(Type* _SetObj_, void (Type::*set_func)(Arg1_Val, Arg2_Val) , Arg1_Val Val1_, Arg2_Val Val2_, void* _allocate_ = nullptr)
		{
			Members_2_Func<Type, Arg1_Val, Arg2_Val>* lp = nullptr;

			if(_SetObj_ == nullptr)
			{
				//Global版ではないのにnullptrを指定されたらそのまま返却。
				return  SonikLib::SharedSmtPtr<SonikFOSInterface>();
			};

			//三項演算子 　(条件) ? 真の時の処理 : 偽の時の処理
			//長いので縦にしただけ。つまり下記。
			//(条件)
			//? 真の時の処理
			//: 偽の時の処理
			(_allocate_ != nullptr)
			? lp = new(_allocate_) Members_2_Func<Type, Arg1_Val, Arg2_Val>(Val1_, Val2_)
			: lp = new(std::nothrow) Members_2_Func<Type, Arg1_Val, Arg2_Val>(Val1_, Val2_);

			if(lp == nullptr)
			{
				//失敗時はnullptrとして返却
				return SonikLib::SharedSmtPtr<SonikFOSInterface>();
			};

			lp->object_ = SonikLib::SharedSmtPtr<Type>(_SetObj_);
			lp->p_mfunc_ = set_func;

			return SonikLib::SharedSmtPtr<SonikFOSInterface>(lp);
		};

		inline void Run(void)
		{
			if( object_.IsNullptr())
			{
				return;
			};

			(object_->*p_mfunc_)(Arg1Val, Arg2Val);
			MethodStatus = true;
		};

	};
	//戻り値有り、引数2 グローバル用
	template<class Rtype, class Arg1_Val, class Arg2_Val>
	class Members_2_FuncRG : public SonikFOSTemplateInterface<Rtype>
	{
	private:
		Arg1_Val  Arg1Val;
		Arg2_Val  Arg2Val;

		Rtype (*p_mfunc_)(Arg1_Val, Arg2_Val);

	private:
		Members_2_FuncRG(void)
		:p_mfunc_(nullptr)
		{
			//member value Initialize only
		};

		Members_2_FuncRG(Arg1_Val Val1_, Arg2_Val Val2_)
		:Arg1Val(Val1_)
		,Arg2Val(Val2_)
		,p_mfunc_(nullptr)
		{
			//member value Initialize only
		};

	public:
		~Members_2_FuncRG(void)
		{
			//no process;
		};

		//グローバル関数指定なので、クラス指定のようにshared版とか無い。
		inline static  SonikLib::SharedSmtPtr<SonikFOSTemplateInterface<Rtype>> New(Rtype (*set_func)(Arg1_Val, Arg2_Val) , Arg1_Val Val1_, Arg2_Val Val2_, void* _allocate_ = nullptr)
		{
			Members_2_FuncRG<Rtype, Arg1_Val, Arg2_Val>* lp = nullptr;

			//三項演算子 　(条件) ? 真の時の処理 : 偽の時の処理
			//長いので縦にしただけ。つまり下記。
			//(条件)
			//? 真の時の処理
			//: 偽の時の処理
			(_allocate_ != nullptr)
			? lp = new(_allocate_) Members_2_FuncRG<Rtype, Arg1_Val, Arg2_Val>(Val1_, Val2_)
			: lp = new(std::nothrow) Members_2_FuncRG<Rtype, Arg1_Val, Arg2_Val>(Val1_, Val2_);

			if(lp == nullptr)
			{
				//失敗時はnullptrとして返却
				return SonikLib::SharedSmtPtr<SonikFOSTemplateInterface<Rtype>>();
			};

			lp->p_mfunc_ = set_func;

			return SonikLib::SharedSmtPtr<SonikFOSTemplateInterface<Rtype>>(lp);
		};

		inline Rtype Run(void)
		{
			Rtype ret;

			ret = (*p_mfunc_)(Arg1Val, Arg2Val);
			this->MethodStatus = true;

			return ret;
		};

	};
	//戻り値無し、引数2 グローバル用
	template<class Arg1_Val, class Arg2_Val>
	class Members_2_FuncG : public SonikFOSInterface
	{
	private:
		Arg1_Val  Arg1Val;
		Arg2_Val  Arg2Val;

		void (*p_mfunc_)(Arg1_Val, Arg2_Val);

	private:
		Members_2_FuncG(void)
		:p_mfunc_(nullptr)
		{
			//member value initialize only
		};

		Members_2_FuncG(Arg1_Val Val1_, Arg2_Val Val2_)
		:Arg1Val(Val1_)
		,Arg2Val(Val2_)
		,p_mfunc_(nullptr)
		{
			//member value initialize only
		};

	public:
		~Members_2_FuncG(void)
		{
			//no process;
		};

		//グローバル関数指定なので、クラス指定のようにshared版とか無い。
		inline static  SonikLib::SharedSmtPtr<SonikFOSInterface> New(void (*set_func)(Arg1_Val, Arg2_Val) , Arg1_Val Val1_, Arg2_Val Val2_, void* _allocate_ = nullptr)
		{
			Members_2_FuncG< Arg1_Val, Arg2_Val>* lp = nullptr;

			//三項演算子 　(条件) ? 真の時の処理 : 偽の時の処理
			//長いので縦にしただけ。つまり下記。
			//(条件)
			//? 真の時の処理
			//: 偽の時の処理
			(_allocate_ != nullptr)
			? lp = new(_allocate_) Members_2_FuncG< Arg1_Val, Arg2_Val>(Val1_, Val2_)
			: lp = new(std::nothrow) Members_2_FuncG< Arg1_Val, Arg2_Val>(Val1_, Val2_);

			if(lp == nullptr)
			{
				//失敗時はnullptrとして返却
				return SonikLib::SharedSmtPtr<SonikFOSInterface>();
			};

			lp->p_mfunc_ = set_func;

			return SonikLib::SharedSmtPtr<SonikFOSInterface>(lp);
		};

		inline void Run(void)
		{
			(*p_mfunc_)(Arg1Val, Arg2Val);
			MethodStatus = true;
		};

	};

	//戻り値有り、引数1
	template<class Rtype, class Type, class Arg1_Val, std::enable_if_t<!std::is_pointer_v<Type>, bool> = true>
	class Members_1_FuncR : public SonikFOSTemplateInterface<Rtype>
	{
	private:
		Arg1_Val  Arg1Val;

		SonikLib::SharedSmtPtr<Type> object_;
		Rtype (Type::*p_mfunc_)(Arg1_Val);

	private:
		Members_1_FuncR(void)
		:object_(nullptr)
		,p_mfunc_(nullptr)
		{
			//member value initialize only
		};

		Members_1_FuncR(Arg1_Val Val1_)
		:Arg1Val(Val1_)
		,object_(nullptr)
		,p_mfunc_(nullptr)
		{
			//member value initialize only
		};

	public:
		~Members_1_FuncR(void)
		{
			if(this->Destroy_ == false)
			{
				//オブジェクト削除フラグがfalseなら勝手にdeleteしてはいけないので
				//ダミーを使ってスマートポインタからオーナー権限を除去し、dummyのdeleteを呼ばない。
				Type* _dymmy = nullptr;
				object_.GetOwnerPointer(_dymmy);
			};

		};

		//SharedSmtPtr指定
		inline static  SonikLib::SharedSmtPtr<SonikFOSTemplateInterface<Rtype>> New(SonikLib::SharedSmtPtr<Type> _SetObj_, Rtype (Type::*set_func)(Arg1_Val) , Arg1_Val Val1_, void* _allocate_ = nullptr)
		{
			Members_1_FuncR<Rtype, Type, Arg1_Val>* lp = nullptr;

			//三項演算子 　(条件) ? 真の時の処理 : 偽の時の処理
			//長いので縦にしただけ。つまり下記。
			//(条件)
			//? 真の時の処理
			//: 偽の時の処理
			(_allocate_ != nullptr)
			? lp = new(_allocate_) Members_1_FuncR<Rtype, Type, Arg1_Val>(Val1_)
			: lp = new(std::nothrow) Members_1_FuncR<Rtype, Type, Arg1_Val>(Val1_);

			if(lp == nullptr)
			{
				//失敗時はnullptrとして返却
				return SonikLib::SharedSmtPtr<SonikFOSTemplateInterface<Rtype>>();
			};

			lp->object_ = _SetObj_;
			lp->p_mfunc_ = set_func;

			return SonikLib::SharedSmtPtr<SonikFOSTemplateInterface<Rtype>>(lp);
		};
		//RawPointer指定
		inline static  SonikLib::SharedSmtPtr<SonikFOSTemplateInterface<Rtype>> New(Type* _SetObj_, Rtype (Type::*set_func)(Arg1_Val) , Arg1_Val Val1_, void* _allocate_ = nullptr)
		{
			Members_1_FuncR<Rtype, Type, Arg1_Val>* lp = nullptr;

			if(_SetObj_ == nullptr)
			{
				//Global版ではないのにnullptrを指定されたらそのまま返却。
				return SonikLib::SharedSmtPtr<SonikFOSTemplateInterface<Rtype>>();
			};

			//三項演算子 　(条件) ? 真の時の処理 : 偽の時の処理
			//長いので縦にしただけ。つまり下記。
			//(条件)
			//? 真の時の処理
			//: 偽の時の処理
			(_allocate_ != nullptr)
			? lp = new(_allocate_) Members_1_FuncR<Rtype, Type, Arg1_Val>(Val1_)
			: lp = new(std::nothrow) Members_1_FuncR<Rtype, Type, Arg1_Val>(Val1_);

			if(lp == nullptr)
			{
				//失敗時はnullptrとして返却
				return SonikLib::SharedSmtPtr<SonikFOSTemplateInterface<Rtype>>();
			};

			lp->object_ = SonikLib::SharedSmtPtr<Type>(_SetObj_);
			lp->p_mfunc_ = set_func;

			return SonikLib::SharedSmtPtr<SonikFOSTemplateInterface<Rtype>>(lp);
		};

		inline Rtype Run(void)
		{
			Rtype ret;

			if( object_.IsNullptr() )
			{
				return 0;
			};

			ret = (object_->*p_mfunc_)(Arg1Val);
			this->MethodStatus = true;

			return ret;
		};

	};
	//戻り値無し、引数1
	template<class Type, class Arg1_Val, std::enable_if_t<!std::is_pointer_v<Type>, bool> = true>
	class Members_1_Func : public SonikFOSInterface
	{
	private:
		Arg1_Val  Arg1Val;

		SonikLib::SharedSmtPtr<Type> object_;
		void (Type::*p_mfunc_)(Arg1_Val);

	private:
		Members_1_Func(void)
		:object_(nullptr)
		,p_mfunc_(nullptr)
		{
			//member value initialize only
		};

		Members_1_Func(Arg1_Val Val1_)
		:Arg1Val(Val1_)
		,object_(nullptr)
		,p_mfunc_(nullptr)
		{
			//member value initialize only
		};

	public:
		~Members_1_Func(void)
		{
			if(this->Destroy_ == false)
			{
				//オブジェクト削除フラグがfalseなら勝手にdeleteしてはいけないので
				//ダミーを使ってスマートポインタからオーナー権限を除去し、dummyのdeleteを呼ばない。
				Type* _dymmy = nullptr;
				object_.GetOwnerPointer(_dymmy);
			};

		};

		//SharedSmtPtr指定
		inline static  SonikLib::SharedSmtPtr<SonikFOSInterface> New(SonikLib::SharedSmtPtr<Type> _SetObj_, void (Type::*set_func)(Arg1_Val) , Arg1_Val Val1_, void* _allocate_ = nullptr)
		{
			Members_1_Func<Type, Arg1_Val>* lp = nullptr;

			//三項演算子 　(条件) ? 真の時の処理 : 偽の時の処理
			//長いので縦にしただけ。つまり下記。
			//(条件)
			//? 真の時の処理
			//: 偽の時の処理
			(_allocate_ != nullptr)
			? lp = new(_allocate_) Members_1_Func<Type, Arg1_Val>(Val1_)
			: lp = new(std::nothrow) Members_1_Func<Type, Arg1_Val>(Val1_);

			if(lp == nullptr)
			{
				//失敗時はnullptrとして返却
				return SonikLib::SharedSmtPtr<SonikFOSInterface>();
			};

			lp->object_ = _SetObj_;
			lp->p_mfunc_ = set_func;

			return SonikLib::SharedSmtPtr<SonikFOSInterface>(lp);
		};
		//RawPointer指定
		inline static  SonikLib::SharedSmtPtr<SonikFOSInterface> New(Type* _SetObj_, void (Type::*set_func)(Arg1_Val) , Arg1_Val Val1_, void* _allocate_ = nullptr)
		{
			Members_1_Func<Type, Arg1_Val>* lp = nullptr;

			if(_SetObj_ == nullptr)
			{
				//Global版ではないのにnullptrを指定されたらそのまま返却。
				return  SonikLib::SharedSmtPtr<SonikFOSInterface>();
			};

			//三項演算子 　(条件) ? 真の時の処理 : 偽の時の処理
			//長いので縦にしただけ。つまり下記。
			//(条件)
			//? 真の時の処理
			//: 偽の時の処理
			(_allocate_ != nullptr)
			? lp = new(_allocate_) Members_1_Func<Type, Arg1_Val>(Val1_)
			: lp = new(std::nothrow) Members_1_Func<Type, Arg1_Val>(Val1_);

			if(lp == nullptr)
			{
				//失敗時はnullptrとして返却
				return SonikLib::SharedSmtPtr<SonikFOSInterface>();
			};

			lp->object_ = SonikLib::SharedSmtPtr<Type>(_SetObj_);
			lp->p_mfunc_ = set_func;

			return SonikLib::SharedSmtPtr<SonikFOSInterface>(lp);
		};

		inline void Run(void)
		{
			if( object_.IsNullptr())
			{
				return;

			};

			(object_->*p_mfunc_)(Arg1Val);
			MethodStatus = true;

		};

	};
	//戻り値有り、引数1 グローバル用
	template<class Rtype, class Arg1_Val>
	class Members_1_FuncRG : public SonikFOSTemplateInterface<Rtype>
	{
	private:
		Arg1_Val  Arg1Val;

		Rtype (*p_mfunc_)(Arg1_Val);

	private:
		Members_1_FuncRG(void)
		:p_mfunc_(nullptr)
		{
			//member value initialize only
		};

		Members_1_FuncRG(Arg1_Val Val1_)
		:Arg1Val(Val1_)
		,p_mfunc_(nullptr)
		{
			//member value initialize only
		};

	public:
		~Members_1_FuncRG(void)
		{
			//no process;
		};

		//グローバル関数指定なので、クラス指定のようにshared版とか無い。
		inline static  SonikLib::SharedSmtPtr<SonikFOSTemplateInterface<Rtype>> New(Rtype (*set_func)(Arg1_Val) , Arg1_Val Val1_, void* _allocate_ = nullptr)
		{
			Members_1_FuncRG<Rtype, Arg1_Val>* lp = nullptr;

			//三項演算子 　(条件) ? 真の時の処理 : 偽の時の処理
			//長いので縦にしただけ。つまり下記。
			//(条件)
			//? 真の時の処理
			//: 偽の時の処理
			(_allocate_ != nullptr)
			? lp = new(_allocate_) Members_1_FuncRG<Rtype, Arg1_Val>(Val1_)
			: lp = new(std::nothrow) Members_1_FuncRG<Rtype, Arg1_Val>(Val1_);

			if(lp == nullptr)
			{
				//失敗時はnullptrとして返却
				return SonikLib::SharedSmtPtr<SonikFOSTemplateInterface<Rtype>>();
			};

			lp->p_mfunc_ = set_func;

			return SonikLib::SharedSmtPtr<SonikFOSTemplateInterface<Rtype>>(lp);
		};

		inline Rtype Run(void)
		{
			Rtype ret;

			ret = (*p_mfunc_)(Arg1Val);
			this->MethodStatus = true;

			return ret;
		};

	};
	//戻り値無し、引数1 グローバル用
	template<class Arg1_Val>
	class Members_1_FuncG : public SonikFOSInterface
	{
	private:
		Arg1_Val  Arg1Val;

		void (*p_mfunc_)(Arg1_Val);

	private:
		Members_1_FuncG(void)
		:p_mfunc_(nullptr)
		{
			//member value initialize only
		};

		Members_1_FuncG(Arg1_Val Val1_)
		:Arg1Val(Val1_)
		,p_mfunc_(nullptr)
		{
			//member value initialize only
		};

	public:
		~Members_1_FuncG(void)
		{
			//no process;
		};

		//グローバル関数指定なので、クラス指定のようにshared版とか無い。
		inline static  SonikLib::SharedSmtPtr<SonikFOSInterface> New(void (*set_func)(Arg1_Val) , Arg1_Val Val1_, void* _allocate_ = nullptr)
		{
			Members_1_FuncG< Arg1_Val>* lp = nullptr;

			//三項演算子 　(条件) ? 真の時の処理 : 偽の時の処理
			//長いので縦にしただけ。つまり下記。
			//(条件)
			//? 真の時の処理
			//: 偽の時の処理
			(_allocate_ != nullptr)
			? lp = new(_allocate_) Members_1_FuncG< Arg1_Val>(Val1_)
			: lp = new(std::nothrow) Members_1_FuncG< Arg1_Val>(Val1_);

			if(lp == nullptr)
			{
				//失敗時はnullptrとして返却
				return SonikLib::SharedSmtPtr<SonikFOSInterface>();
			};

			lp->p_mfunc_ = set_func;

			return SonikLib::SharedSmtPtr<SonikFOSInterface>(lp);
		};

		inline void Run(void)
		{
			(*p_mfunc_)(Arg1Val);
			MethodStatus = true;
		};

	};

	//戻り値有り、引数0
	template<class Rtype, class Type, std::enable_if_t<!std::is_pointer_v<Type>, bool> = true>
	class Members_0_FuncR : public SonikFOSTemplateInterface<Rtype>
	{
	private:
		SonikLib::SharedSmtPtr<Type> object_;
		Rtype(Type::*p_mfunc_)(void);

	private:
		Members_0_FuncR(void)
		:object_(nullptr)
		,p_mfunc_(nullptr)
		{
			//member initialize only
		};

	public:
		~Members_0_FuncR(void)
		{
			if(this->Destroy_ == false)
			{
				//オブジェクト削除フラグがfalseなら勝手にdeleteしてはいけないので
				//ダミーを使ってスマートポインタからオーナー権限を除去し、dummyのdeleteを呼ばない。
				Type* _dymmy = nullptr;
				object_.GetOwnerPointer(_dymmy);
			};

		};

		//SharedSmtPtr指定
		inline static  SonikLib::SharedSmtPtr<SonikFOSTemplateInterface<Rtype>> New(SonikLib::SharedSmtPtr<Type> _SetObj_, Rtype (Type::*set_func)(void) , void* _allocate_ = nullptr)
		{
			Members_0_FuncR<Rtype, Type>* lp = nullptr;

			//三項演算子 　(条件) ? 真の時の処理 : 偽の時の処理
			//長いので縦にしただけ。つまり下記。
			//(条件)
			//? 真の時の処理
			//: 偽の時の処理
			(_allocate_ != nullptr)
			? lp = new(_allocate_) Members_0_FuncR<Rtype, Type>()
			: lp = new(std::nothrow) Members_0_FuncR<Rtype, Type>();

			if(lp == nullptr)
			{
				//失敗時はnullptrとして返却
				return SonikLib::SharedSmtPtr<SonikFOSTemplateInterface<Rtype>>();
			};

			lp->object_ = _SetObj_;
			lp->p_mfunc_ = set_func;

			return SonikLib::SharedSmtPtr<SonikFOSTemplateInterface<Rtype>>(lp);
		};
		//RawPointer指定
		inline static  SonikLib::SharedSmtPtr<SonikFOSTemplateInterface<Rtype>> New(Type* _SetObj_, Rtype (Type::*set_func)(void) , void* _allocate_ = nullptr)
		{
			Members_0_FuncR<Rtype, Type>* lp = nullptr;

			if(_SetObj_ == nullptr)
			{
				//Global版ではないのにnullptrを指定されたらそのまま返却。
				return SonikLib::SharedSmtPtr<SonikFOSTemplateInterface<Rtype>>();
			};

			//三項演算子 　(条件) ? 真の時の処理 : 偽の時の処理
			//長いので縦にしただけ。つまり下記。
			//(条件)
			//? 真の時の処理
			//: 偽の時の処理
			(_allocate_ != nullptr)
			? lp = new(_allocate_) Members_0_FuncR<Rtype, Type>()
			: lp = new(std::nothrow) Members_0_FuncR<Rtype, Type>();

			if(lp == nullptr)
			{
				//失敗時はnullptrとして返却
				return SonikLib::SharedSmtPtr<SonikFOSTemplateInterface<Rtype>>();
			};

			lp->object_ = SonikLib::SharedSmtPtr<Type>(_SetObj_);
			lp->p_mfunc_ = set_func;

			return SonikLib::SharedSmtPtr<SonikFOSTemplateInterface<Rtype>>(lp);
		};

		inline Rtype Run(void)
		{
			Rtype ret;

			if( object_.IsNullptr() )
			{
				return 0;
			};

			ret = (object_->*p_mfunc_)();
			this->MethodStatus = true;

			return ret;
		};

	};
	//戻り値無し、引数0(自作スレッドプールで使用する型です。でも他に使いたければどうぞ)
	template<class Type, std::enable_if_t<!std::is_pointer_v<Type>, bool> = true>
	class Members_0_Func : public SonikFOSInterface
	{
	private:

		SonikLib::SharedSmtPtr<Type> object_;
		void (Type::*p_mfunc_)(void);

	private:
		Members_0_Func(void)
		:object_(nullptr)
		,p_mfunc_(nullptr)
		{
			//memer value initialize only
		};

	public:
		~Members_0_Func(void)
		{
			if(this->Destroy_ == false)
			{
				//オブジェクト削除フラグがfalseなら勝手にdeleteしてはいけないので
				//ダミーを使ってスマートポインタからオーナー権限を除去し、dummyのdeleteを呼ばない。
				Type* _dymmy = nullptr;
				object_.GetOwnerPointer(_dymmy);
			};

		};

		//SharedSmtPtr指定
		inline static  SonikLib::SharedSmtPtr<SonikFOSInterface> New(SonikLib::SharedSmtPtr<Type> _SetObj_, void (Type::*set_func)(void), void* _allocate_ = nullptr)
		{
			Members_0_Func<Type>* lp = nullptr;

			//三項演算子 　(条件) ? 真の時の処理 : 偽の時の処理
			//長いので縦にしただけ。つまり下記。
			//(条件)
			//? 真の時の処理
			//: 偽の時の処理
			(_allocate_ != nullptr)
			? lp = new(_allocate_) Members_0_Func<Type>()
			: lp = new(std::nothrow) Members_0_Func<Type>();

			if(lp == nullptr)
			{
				//失敗時はnullptrとして返却
				return SonikLib::SharedSmtPtr<SonikFOSInterface>();
			};

			lp->object_ = _SetObj_;
			lp->p_mfunc_ = set_func;

			return SonikLib::SharedSmtPtr<SonikFOSInterface>(lp);
		};
		//RawPointer指定
		inline static  SonikLib::SharedSmtPtr<SonikFOSInterface> New(Type* _SetObj_, void (Type::*set_func)(void), void* _allocate_ = nullptr)
		{
			Members_0_Func<Type>* lp = nullptr;

			if(_SetObj_ == nullptr)
			{
				//Global版ではないのにnullptrを指定されたらそのまま返却。
				return  SonikLib::SharedSmtPtr<SonikFOSInterface>();
			};

			//三項演算子 　(条件) ? 真の時の処理 : 偽の時の処理
			//長いので縦にしただけ。つまり下記。
			//(条件)
			//? 真の時の処理
			//: 偽の時の処理
			(_allocate_ != nullptr)
			? lp = new(_allocate_) Members_0_Func<Type>()
			: lp = new(std::nothrow) Members_0_Func<Type>();

			if(lp == nullptr)
			{
				//失敗時はnullptrとして返却
				return SonikLib::SharedSmtPtr<SonikFOSInterface>();
			};

			lp->object_ = SonikLib::SharedSmtPtr<Type>(_SetObj_);
			lp->p_mfunc_ = set_func;

			return SonikLib::SharedSmtPtr<SonikFOSInterface>(lp);
		};

		inline void Run(void)
		{

			if( object_.IsNullptr() )
			{
				return;
			};

			(object_->*p_mfunc_)();
			MethodStatus = true;
		};

	};
	//戻り値有り、引数0 グローバル用
	template<class Rtype>
	class Members_0_FuncRG : public SonikFOSTemplateInterface<Rtype>
	{
	private:

		Rtype (*p_mfunc_)(void);

		Members_0_FuncRG()
		:p_mfunc_(nullptr)
		{
			//member value initialize only
		};

	public:
		~Members_0_FuncRG(void)
		{
			//no process;
		};

		//グローバル関数指定なので、クラス指定のようにshared版とか無い。
		inline static  SonikLib::SharedSmtPtr<SonikFOSTemplateInterface<Rtype>> New(Rtype (*set_func)(void), void* _allocate_ = nullptr)
		{
			Members_0_FuncRG<Rtype>* lp = nullptr;

			//三項演算子 　(条件) ? 真の時の処理 : 偽の時の処理
			//長いので縦にしただけ。つまり下記。
			//(条件)
			//? 真の時の処理
			//: 偽の時の処理
			(_allocate_ != nullptr)
			? lp = new(_allocate_) Members_0_FuncRG<Rtype>()
			: lp = new(std::nothrow) Members_0_FuncRG<Rtype>();

			if(lp == nullptr)
			{
				//失敗時はnullptrとして返却
				return SonikLib::SharedSmtPtr<SonikFOSTemplateInterface<Rtype>>();
			};

			lp->p_mfunc_ = set_func;

			return SonikLib::SharedSmtPtr<SonikFOSTemplateInterface<Rtype>>(lp);
		};

		inline Rtype Run(void)
		{

			return (*p_mfunc_)();
		};

	};
	//戻り値無し、引数0 グローバル用
	class Members_0_FuncG : public SonikFOSInterface
	{
	private:

		void (*p_mfunc_)(void);

	private:
		Members_0_FuncG(void)
		:p_mfunc_(nullptr)
		{
			//member value initialize only
		};

	public:
		~Members_0_FuncG(void)
		{
			//no process;
		};

		//グローバル関数指定なので、クラス指定のようにshared版とか無い。
		inline static  SonikLib::SharedSmtPtr<SonikFOSInterface> New(void (*set_func)(void), void* _allocate_ = nullptr)
		{
			Members_0_FuncG* lp = nullptr;

			//三項演算子 　(条件) ? 真の時の処理 : 偽の時の処理
			//長いので縦にしただけ。つまり下記。
			//(条件)
			//? 真の時の処理
			//: 偽の時の処理
			(_allocate_ != nullptr)
			? lp = new(_allocate_) Members_0_FuncG()
			: lp = new(std::nothrow) Members_0_FuncG();

			if(lp == nullptr)
			{
				//失敗時はnullptrとして返却
				return SonikLib::SharedSmtPtr<SonikFOSInterface>();
			};

			lp->p_mfunc_ = set_func;

			return SonikLib::SharedSmtPtr<SonikFOSInterface>(lp);
		};

		inline void Run(void)
		{

			(*p_mfunc_)();
			MethodStatus = true;
		};

	};

};


#endif
