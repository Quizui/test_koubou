/*
 * AudioPlayerTaskManager.cpp
 *
 *  Created on: 2023/10/20
 *      Author: owner
 */

#include "AudioPlayerTaskManager.h"
#include "../../FunctionObject/FunctionObjectSystemImpl.hpp"

namespace SonikAudioPlayerTask
{
	//コンストラクタ
	SonikAudioPlayerTaskManager::SonikAudioPlayerTaskManager(void)
	:mp_TaskQueue(nullptr)
	,mp_TaskThread(nullptr)
	{


	};
	//デストラクタ
	SonikAudioPlayerTaskManager::~SonikAudioPlayerTaskManager(void)
	{
		if(mp_TaskThread != nullptr)
		{
			mp_TaskThread->SetFunctionloopEndFlagOn();
			mp_TaskThread->SetThreadExitFlagOn();

			delete mp_TaskThread;
		};

		SonikAudioTaskInterface::PlayerTaskInterface* l_task;
		if(mp_TaskQueue != nullptr)
		{
			while( mp_TaskQueue->DeQueue(l_task) )
			{
				delete l_task;
			};

			delete mp_TaskQueue;

		};

	};

	//イニシャライザ
	bool SonikAudioPlayerTaskManager::Initialize(uint32_t QueueItemNum)
	{
		//２回目以降よばれた時はデストラクタ処理をしてから再クリエイト
		if(mp_TaskThread != nullptr)
		{
			mp_TaskThread->SetFunctionloopEndFlagOn();
			mp_TaskThread->SetThreadExitFlagOn();

			delete mp_TaskThread;
		};

		SonikAudioTaskInterface::PlayerTaskInterface* l_task = nullptr;
		if(mp_TaskQueue != nullptr)
		{
			while( mp_TaskQueue->DeQueue(l_task) )
			{
				delete l_task;
			};

			delete mp_TaskQueue;

		};

		//===================
		mp_TaskThread = new(std::nothrow) SonikLib::WorkThreadEx();
		if(mp_TaskThread == nullptr)
		{
			return false;
		};

		SonikLib::SharedSmtPtr<SonikLib::SonikFOSInterface> l_cls_func_obj;;
		l_cls_func_obj = SonikLib::Members_0_Func<SonikAudioPlayerTaskManager>::New(this, static_cast<void (SonikAudioPlayerTaskManager::*)(void)>(&SonikAudioPlayerTaskManager::ThreadProcFunc));
		if(l_cls_func_obj.IsNullptr())
		{
			delete mp_TaskThread;

			mp_TaskThread = nullptr;
			return false;
		};

		l_cls_func_obj->Set_DestroyObjectFlag(false);

		mp_TaskQueue = new(std::nothrow) SonikLib::Container::SonikAtomicQueue<SonikAudioTaskInterface::PlayerTaskInterface*>(QueueItemNum);
		if(mp_TaskQueue == nullptr)
		{
			l_cls_func_obj.ResetPointer(nullptr);
			delete mp_TaskThread;

			mp_TaskThread = nullptr;
			return false;
		}

		//スレッド関数駆動開始。
		mp_TaskThread->SetCallFunction(l_cls_func_obj, true);

		return true;
	};

	//純粋仮想関数の実装。
	bool SonikAudioPlayerTaskManager::AddTask(SonikAudioTaskInterface::PlayerTaskInterface* pTask)
	{
		//基本的にQueueが生成されていない(=nullptr)の時にコールされることはないはずなのでnullチェックをしない。
		if( !mp_TaskQueue->EnQueue(pTask) )
		{
			delete pTask;
			return false;
		};

		return true;
	};

	//スレッドで回す用の関数。Queueから1回のDequeueとRunを実行する。
	//この関数もQueueがnullptrの状態のときには実行されないのでnullチェックを省く。
	void SonikAudioPlayerTaskManager::ThreadProcFunc(void)
	{
		SonikAudioTaskInterface::PlayerTaskInterface* l_task = nullptr;

		if( mp_TaskQueue->DeQueue(l_task) )
		{
			l_task->TaskRun();
			delete l_task;
		};

	};

};

