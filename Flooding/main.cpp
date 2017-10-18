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

#define NODENUM 20

using namespace std;



int main(int argc, const char * argv[]) {
	Node node[NODENUM]; //ノード
	int total = 0; //全ノードの総送信回数
	list<int> senders_now; //現スロットで送信を行うノード集合
	list<int> senders_next; //次スロットで送信を行うノード集合
	senders_now.clear();
	senders_next.clear();
	
	/********** 初期設定 **********/
	/* 各ノードを配置 */
//	node[0].Node::setXY(0, 1);
//	node[1].Node::setXY(2, 0);
//	node[2].Node::setXY(2, 3);
//	node[3].Node::setXY(4, 1);
//	node[4].Node::setXY(4, 4);

	node[0].Node::setXY(0, 2);
	node[1].Node::setXY(0, 5);
	node[2].Node::setXY(1, 0);
	node[3].Node::setXY(1, 3);
	node[4].Node::setXY(1, 8);
	node[5].Node::setXY(2, 5);
	node[6].Node::setXY(3, 1);
	node[7].Node::setXY(3, 9);
	node[8].Node::setXY(4, 4);
	node[9].Node::setXY(4, 7);
	node[10].Node::setXY(5, 0);
	node[11].Node::setXY(5, 6);
	node[12].Node::setXY(6, 2);
	node[13].Node::setXY(6, 9);
	node[14].Node::setXY(7, 8);
	node[15].Node::setXY(8, 0);
	node[16].Node::setXY(8, 4);
	node[17].Node::setXY(8, 6);
	node[18].Node::setXY(9, 2);
	node[19].Node::setXY(9, 8);
	
	/* 送信元を1つ指定 */
	node[NODENUM-1].changeState();
	senders_now.push_back(NODENUM-1);
	
	
	/********** Flooding開始 **********/
	for (int timeslot = 1; ; timeslot++) {
		/* タイムスロット表示 */
		cout << "Time Slot : " << timeslot << endl;
		
		/* 送信ノードが残っている場合 */
		if (senders_now.size() != 0) {
			for (int i : senders_now) {
				/* 送信相手を探す */
				for (int j = 0; j < NODENUM; j++) {
					/* ノード間の距離計算(△x+△y) */
					int range = abs(node[i].getX() - node[j].getX()) +
								abs(node[i].getY() - node[j].getY());
					
					/* ブロードキャスト可能範囲であれば送信 */
//					/* 受信済みノードには送らない場合 */
//					if ((range != 0) && (range <= 3) && (node[j].getState() == false)) {
//						cout << "	(" << node[i].getX() << "," << node[i].getY();
//						cout << ") -> " << "(" << node[j].getX() << ",";
//						cout << node[j].getY() << ")" << endl;
//						
//						/* 送信回数の増加 */
//						node[i].addCount();
//						
//						/* "未所持"から"所持"へ */
//						node[j].changeState();
//						
//						/* 受信ノードを次スロットの送信ノード集合に追加 */
//						senders_next.push_back(j);
//					}
					
					/* 受信済みノードにも送る場合 */
					if ((range != 0) && (range <= 3)) {
						cout << "	(" << node[i].getX() << "," << node[i].getY();
						cout << ") -> " << "(" << node[j].getX() << ",";
						cout << node[j].getY() << ")" << endl;

						/* 送信回数の増加 */
						node[i].addCount();
						
						/* 受信ノードを次スロットの送信ノード集合に追加 */
						if (node[j].getState() == false) {
							senders_next.push_back(j);
						}
						
						/* "未所持"から"所持"へ */
						node[j].changeState();
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
			//cout << "Send Number" << endl;
			for (int i=0; i < NODENUM; i++) {
				//cout << "NODE[" << i << "] : " << node[i].getCount() <<endl;
				total += node[i].getCount();
			}
			cout << "TOTAL : " << total << endl;

			cout << endl;
			cout << "Program finished." << endl;
			break;
		}
	}
	
	return 0;
}