/*
 * SonikAtomicQueue.h
 *
 *  Created on: 2015/09/22
 *      Author: SONIK
 */

#ifndef SONIKATOMICQUEUE_H_
#define SONIKATOMICQUEUE_H_

//一般的なQueue機構を提供します。

#include <stdint.h>
#include <new>
#include "../SonikCAS/SonikAtomicLock.h"

namespace SonikLib
{
	namespace Container
	{
		template<class QueueType>
		class SonikAtomicQueue
		{
			private:
				//インナークラス。ノードを外に出す実装はないので...。
				template<class ClsType>
				class QueueNode
				{
					public:
						ClsType m_TemplateObject;						//実際のオブジェクト
						QueueNode<ClsType>* Next;	//次のQueueへのポインタ

					public:
						//construcotr
						inline QueueNode(void) noexcept
						:Next(0)
						{
						};
						//destructor
						inline ~QueueNode(void) noexcept
						{

						};
				};

				using TypeNode = QueueNode<QueueType>;

			private:
				//フリーアイテムリスト
				TypeNode* m_QueueAllocArea; //配列先頭のポインタ。
				TypeNode* m_Free; // リンクリストを操作するポインタ。

				//QueueされたNode
				TypeNode* _first;
				TypeNode* _last;

				//設定した最大キュー数
				uint32_t Queue_RoundCount;

				//アトミックブロッククラス。マルチスレッド対応にするための排他制御クラスです。
				SonikLib::S_CAS::SonikAtomicLock shortblock;

			private:
				SonikAtomicQueue(const SonikAtomicQueue& _copy_) =delete;
				SonikAtomicQueue(SonikAtomicQueue&& _move_) = delete;
				SonikAtomicQueue& operator =(const SonikAtomicQueue& _copy_) = delete;
				SonikAtomicQueue& operator =(SonikAtomicQueue&& _move_) = delete;

			public:
				inline SonikAtomicQueue(uint32_t QueueItemNum = 100)
				:_first(nullptr)
				, _last(nullptr)
				,Queue_RoundCount(QueueItemNum)
				{

					if(Queue_RoundCount >= UINT32_MAX)
					{
						--Queue_RoundCount;
					};

					try
					{
						//オブジェクトをカウント分ヒープからnewして再利用しまくる。
						m_QueueAllocArea = new TypeNode[QueueItemNum];

					}catch(std::bad_alloc&)
					{
						delete[] m_QueueAllocArea;
					};

					//リンクをつなげる。
					m_Free = m_QueueAllocArea;
					for(uint32_t  i =0; i < (QueueItemNum -1); ++i)
					{
						m_Free[i].Next = &m_Free[ i + 1];
					};

				};

				inline ~SonikAtomicQueue(void)
				{
					//Queue内のオブジェクトの破棄までの責任は持たないので、そのまま配列delete
					if(m_QueueAllocArea != nullptr)
					{
						delete[] m_QueueAllocArea;
					};


				};

				inline bool Initialize(uint32_t QueueItemMax) noexcept
				{
					if(QueueItemMax >= UINT32_MAX)
					{
						--QueueItemMax;
					};

					//オブジェクトをカウント分ヒープからnewして再利用しまくる。
					m_QueueAllocArea = new(std::nothrow) TypeNode[QueueItemMax];
					if( m_QueueAllocArea == nullptr )
					{
						return false;
					};
					//リンクをつなげる。
					m_Free = m_QueueAllocArea;
					for(uint32_t  i =0; i < (QueueItemMax -1); ++i)
					{
						m_Free[i].Next = &m_Free[ i + 1];
					};

					//変数セットして終了
					Queue_RoundCount = QueueItemMax;
					return true;
				};

				//書き込み(エンキュー)
				inline bool EnQueue(QueueType SetData) noexcept
				{
					TypeNode* lp_ptr;

					shortblock.lock();

					if(m_Free == nullptr)
					{
						//フリーリストがなかったら失敗。
						shortblock.unlock();
						return false;
					};

					//フリーリストから取得。
					lp_ptr = m_Free;
					m_Free = m_Free->Next;

					//nextをnullptrに初期化。
					lp_ptr->Next = nullptr;

					if( _first == nullptr && _last == nullptr)
					{
						//初回ならそれぞれ挿入。
						_first = lp_ptr;
						_last = lp_ptr;
					}else
					{
						//すでにオブジェクトがあるなら最後尾に挿入
						//フリーリストから取得。
						_last->Next = lp_ptr;
						_last = lp_ptr;
					};

					//値設定。
					lp_ptr->m_TemplateObject = SetData;

					//ポインタの付替えは終わったのでブロック解除
					shortblock.unlock();

					//終了
					return true;
				};

				//取得（デキュー)
				//TryLock版(ロックが取れなければすぐに処理が返ります。
				inline bool TryDeQueue(QueueType& GetValue) noexcept
				{

					if( !shortblock.try_lock() )
					{
						return false;
					};

					if( _first == nullptr && _last == nullptr )
					{
						//要素がないよ。
						shortblock.unlock();
						return false;
					};

					//要素がある場合。
					TypeNode* pTmp;

					//とりあえず取得してポインタを進める。
					pTmp = _first;

					if(_first == _last)
					{
						//要素トップのポインタとラストのポインタが一緒なら最終要素のため、lastを更新。
						_last = nullptr;
					}

					_first = _first->Next;

					//DeQueueしたものはフリーブロックへ移動させる。
					pTmp->Next = m_Free;
					m_Free = pTmp;

					//値取得
					//すでにフリーリストに入っているのでブロック解除のタイミングで値が代入されてしまう可能性があるため
					//ブロック解除前のタイミングで取得する。
					GetValue = pTmp->m_TemplateObject;

					//ブロック解除
					shortblock.unlock();

					//正常終了。
					return true;
				};

				//取得（デキュー)
				//通常ロック版(ビジーループでロックが取れるまで待ちます。)
				inline bool DeQueue(QueueType& GetValue) noexcept
				{

					shortblock.lock();

					if( _first == nullptr && _last == nullptr )
					{
						//要素がないよ。
						shortblock.unlock();
						return false;
					};

					//要素がある場合。
					TypeNode* pTmp;

					//とりあえず取得してポインタを進める。
					pTmp = _first;

					if(_first == _last)
					{
						//要素トップのポインタとラストのポインタが一緒なら最終要素のため、lastを更新。
						_last = nullptr;
					}

					_first = _first->Next;

					//DeQueueしたものはフリーブロックへ移動させる。
					pTmp->Next = m_Free;
					m_Free = pTmp;

					//値取得
					//すでにフリーリストに入っているのでブロック解除のタイミングで値が代入されてしまう可能性があるため
					//ブロック解除前のタイミングで取得する。
					GetValue = pTmp->m_TemplateObject;

					//ブロック解除
					shortblock.unlock();

					//正常終了。
					return true;
				};
		};

	}; //end namespace Container

}; //end namespace SonikLib


#endif /* SONIKATOMICQUEUE_H_ */
