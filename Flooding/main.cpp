//
//  main.cpp
//  Flooding
//
//  Created by neos on 2017/10/16.
//  Copyright (c) 2017年 Tatsuro Seno. All rights reserved.
//

#include <iostream>
#include <list>
#include <fstream>
#include <string>
#include "Message.h"
#include "Node.h"

using namespace std;


int main(int argc, const char * argv[]) {
//	const static int SIDE = 90; //マップの一辺
//	const static int NODENUM = (SIDE/2 + 1)*(SIDE/2 + 1); //ノード数
	const static int NODENUM = 30;
	const static int RADIUS = 3; //送信可能範囲の半径
	Node node[NODENUM]; //ノード
	int total = 0; //全ノードの総送信回数
	list<int> senders_now; //現スロットで送信を行うノード集合
	list<int> senders_next; //次スロットで送信を行うノード集合
	senders_now.clear();
	senders_next.clear();
	
	
	/********** 初期設定 **********/
	/* 各ノードを配置 */
//	int num = 0;
//	for (int x = 0; x <= SIDE; x+=2) {
//		for (int y = 0; y <= SIDE; y+=2) {
//			node[num].setXY(x,y);
//			num++;
//		}
//	}

	node[0].setXY(0, 9);
	node[1].setXY(1, 0);
	node[2].setXY(1, 1);
	node[3].setXY(1, 5);
	node[4].setXY(1, 6);
	node[5].setXY(2, 3);
	node[6].setXY(2, 4);
	node[7].setXY(2, 8);
	node[8].setXY(2, 9);
	node[9].setXY(3, 5);
	node[10].setXY(3, 9);
	node[11].setXY(4, 2);
	node[12].setXY(4, 4);
	node[13].setXY(4, 5);
	node[14].setXY(4, 7);
	node[15].setXY(4, 8);
	node[16].setXY(5, 0);
	node[17].setXY(5, 1);
	node[18].setXY(5, 6);
	node[19].setXY(5, 9);
	node[20].setXY(6, 1);
	node[21].setXY(6, 2);
	node[22].setXY(6, 7);
	node[23].setXY(7, 3);
	node[24].setXY(7, 7);
	node[25].setXY(7, 9);
	node[26].setXY(8, 2);
	node[27].setXY(8, 4);
	node[28].setXY(9, 5);
	node[29].setXY(9, 7);
	
	for (int i = 0; i < NODENUM; i++) {
		node[i].setNodeNum(i);
	}
	
	/* 送信元を1つ指定 */
	Message a;
	a.setID(1);
	a.setPath(NODENUM-1);
	node[NODENUM-1].setMessage(a);
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
					int x = abs(node[i].getX() - node[j].getX());
					int y = abs(node[i].getY() - node[j].getY());
					int range = x*x + y*y;
					
					/* ブロードキャスト可能範囲であれば送信 */
					if ((range != 0) && (range <= RADIUS*RADIUS)) {
						/* 送受信ノードの表示 */
						cout << "	" << i << " -> " << "" << j << "" << endl;

						/* メッセージ受け渡し */
						bool next = node[j].receiveMessage(node[i].sendMessage());
						
						/* 受信ノードが新規のメッセージを受信したなら次スロットで送信する */
						if (next) {
							bool flag = true;
							for (int a : senders_next) {
								if (a == j) {
									flag = false;
									break;
								}
							}
							
							/* 次スロット送信リストにまだ含まれていなければ含む */
							if (flag) {
								senders_next.push_back(j);
							}
						}
					}

				}
			}
			
			senders_now.clear();
			senders_now = senders_next;
			senders_next.clear();
			senders_now.sort();
		}
		
		/* 送信ノードが無ければFlooding終了 */
		else {
			/* 各メッセージの経路履歴の出力 */
			cout << endl;
			cout << "----- Message Route -----" << endl;
			for (int i = 0; i < NODENUM; i++) {
				cout << "Node[" << i << "] : " << endl;
				for (Message msg : node[i].getMessage()) {
					cout << "	" << "Msg[" << msg.getID() << "] : ";
					for (int j : msg.getPath()) {
						cout << j << " ";
					}
				}
				cout << endl;
			}

			/* 送信回数の出力 */
			cout << endl;
			for (Node a : node) {
				total += a.getCount();
			}
			cout << "----- Transmission Times -----" << endl;
			cout << total << endl;
			cout << endl;
			
			/* 未受信ノードのノード番号出力 */
			cout << "----- Not Received Nodes -----" << endl;
			for (Node a : node) {
				if (!a.hasMessage()) {
					cout << "Node[" << a.getNodeNum() << "]";
					cout << endl;
				}
			}
			cout << endl;

			break;
		}
	}
	
	return 0;
}