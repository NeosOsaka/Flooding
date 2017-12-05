//
//  main.cpp
//  Flooding
//
//  Created by neos on 2017/10/16.
//  Copyright (c) 2017年 Tatsuro Seno. All rights reserved.
//

#include <iostream>
#include <list>
#include <vector>
#include <fstream>
#include <string>
#include "Message.h"
#include "Node.h"


using namespace std;

const static int SIDE = 8; //マップの一辺
const static int NODENUM = 5; //ノード数
Node node[NODENUM]; //ノード

int main(int argc, const char * argv[]) {
	const static int RADIUS = 3; //送信可能範囲の半径
	int total = 0; //全ノードの総送信回数
	list<int> senders_now; //現スロットで送信を行うノード集合
	list<int> senders_next; //次スロットで送信を行うノード集合
	senders_now.clear();
	senders_next.clear();
	
	
	/* * * * * * * * * * 初期設定 * * * * * * * * * */
	/* 各ノードを配置 */
	node[0].setXY(0, 0);
	node[1].setXY(2, 1);
	node[2].setXY(3, 3);
	node[3].setXY(5, 4);
	node[4].setXY(6, 6);
	
	for (int i = 0; i < NODENUM; i++) {
		node[i].setNodeNum(i);
	}
	
	/* 送信元を1つ指定 */
	Message a;
	a.setID(1);
	a.setPath(NODENUM-1);
	node[0].setMessage(a);
	senders_now.push_back(0);
	
	
	
	
	
	/* * * * * * * * * * Routing * * * * * * * * * */
	/* (x,y)座標をZ記法に */
	for (int i = 0; i < NODENUM; i++) {
		int side = SIDE / 2;
		int x = node[i].getX();
		int y = node[i].getY();
		
		while (side >= 1) {
			if (y < side) {
				if (x < side) {
					node[i].setZ(0);
				} else {
					node[i].setZ(1);
					x -= side;
				}
			} else {
				if (x < side) {
					node[i].setZ(2);
					y -= side;
				} else {
					node[i].setZ(3);
					x -= side;
					y -= side;
				}
			}
			
			side = side / 2;
		}
	}

//	/* Leaf Setの設定 */
//	for (int i = 0; i < NODENUM; i++) {
//		for (int j = 0; j < NODENUM; j++) {
//			/* ノード間の距離計算(△x+△y) */
//			int x = abs(node[i].getX() - node[j].getX());
//			int y = abs(node[i].getY() - node[j].getY());
//			int range = x*x + y*y;
//			
//			/* ブロードキャスト可能範囲であればLSに追加 */
//			if ((range != 0) && (range <= RADIUS*RADIUS)) {
//				
//			}
//			
//		}
//	}
//	
//	/* Routing Tableの設定 */
//	for (int i = 0; i < NODENUM; i++) {
//	}
//	
	
	
	
	
	/* * * * * * * * * * Forwarding * * * * * * * * * */
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