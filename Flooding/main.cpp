//
//  main.cpp
//  Flooding
//
//  Created by neos on 2017/10/16.
//  Copyright (c) 2017年 Tatsuro Seno. All rights reserved.
//

#include <iostream>
#include <list>
#include "Message.h"
#include "Node.h"

using namespace std;


int main(int argc, const char * argv[]) {
	const static int NODENUM = 5; //ノード数
	const static int LENGTH = 3; //ブロードキャスト可能範囲
	Node node[NODENUM]; //ノード
	int total = 0; //全ノードの総送信回数
	list<int> senders_now; //現スロットで送信を行うノード集合
	list<int> senders_next; //次スロットで送信を行うノード集合
	senders_now.clear();
	senders_next.clear();
	
	/********** 初期設定 **********/
	/* 各ノードを配置 */
	node[0].Node::setXY(0, 1);
	node[1].Node::setXY(2, 0);
	node[2].Node::setXY(2, 3);
	node[3].Node::setXY(4, 1);
	node[4].Node::setXY(4, 4);
	
	//	node[0].Node::setXY(0, 2);
	//	node[1].Node::setXY(0, 5);
	//	node[2].Node::setXY(1, 0);
	//	node[3].Node::setXY(1, 3);
	//	node[4].Node::setXY(1, 8);
	//	node[5].Node::setXY(2, 5);
	//	node[6].Node::setXY(3, 1);
	//	node[7].Node::setXY(3, 9);
	//	node[8].Node::setXY(4, 4);
	//	node[9].Node::setXY(4, 7);
	//	node[10].Node::setXY(5, 0);
	//	node[11].Node::setXY(5, 6);
	//	node[12].Node::setXY(6, 2);
	//	node[13].Node::setXY(6, 9);
	//	node[14].Node::setXY(7, 8);
	//	node[15].Node::setXY(8, 0);
	//	node[16].Node::setXY(8, 4);
	//	node[17].Node::setXY(8, 6);
	//	node[18].Node::setXY(9, 2);
	//	node[19].Node::setXY(9, 8);
	
	for (int i = 0; i < NODENUM; i++) {
		node[i].Node::setNodeNum(i);
	}
	
	/* 送信元を1つ指定 */
	Message a;
	a.setID(1);
	a.setPath(NODENUM-1);
	node[NODENUM-1].setMessage(a);
	node[NODENUM-1].changeState();
	senders_now.push_back(NODENUM-1);
	
	
	/********** Flooding開始 **********/
	cout << "----- Time Slot -----" << endl;
	
	for (int timeslot = 1; ; timeslot++) {
		/* 送信ノードが残っている場合 */
		if (senders_now.size() != 0) {
			/* タイムスロット表示 */
			cout << "T" << timeslot << " : " << endl;
			
			for (int i : senders_now) {
				/* 送信相手を探す */
				for (int j = 0; j < NODENUM; j++) {
					/* ノード間の距離計算(△x+△y) */
					int range = abs(node[i].getX() - node[j].getX()) +
					abs(node[i].getY() - node[j].getY());
					
					/***** 受信済みノードには送らない場合 *****/
					/* ブロードキャスト可能範囲であれば送信 */
					if ((range != 0) && (range <= LENGTH) && (node[j].getState() == false)) {
						/* ノードの表示 */
						cout << "	(" << node[i].getX() << "," << node[i].getY();
						cout << ") -> " << "(" << node[j].getX() << ",";
						cout << node[j].getY() << ")" << endl;
						
						/* メッセージ受け渡し */
						node[j].receiveMessage(node[i].sendMessage());
						
						/* "未受信"から"受信済み"へ */
						node[j].changeState();
						
						/* 受信ノードを次スロットの送信ノード集合に追加 */
						senders_next.push_back(j);
					}

				}
			}
			
			senders_now.clear();
			senders_now = senders_next;
			senders_next.clear();
		}
		
		/* 送信ノードが無ければFlooding終了 */
		else {
			cout << endl;
			
			/* 送信回数の出力 */
			for (Node a : node) {
				total += a.getCount();
			}
			cout << "----- Transmission Times -----" << endl;
			cout << total << endl;
			cout << endl;
			
			/* 各メッセージの経路履歴の出力 */
			cout << "----- Message Route -----" << endl;
			for (int i = 0; i < NODENUM; i++) {
				cout << "Node[" << i << "] : " << endl;
				for (Message msg : node[i].getMessage()) {
					cout << "	";
					for (int j : msg.getPath()) {
						cout << j << " -> ";
					}
				}
				cout << endl;
			}
			
			break;
		}
	}
	
	return 0;
}