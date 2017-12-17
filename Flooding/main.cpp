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
#include <string>
#include "Message.h"
#include "Node.h"
#include "RoutingTable.h"
#include "Entry.h"


using namespace std;

const static int SIDE = 8; //マップの一辺
const static int NODENUM = 20; //ノード数
Node node[NODENUM]; //ノード

int main(int argc, const char * argv[]) {
	const static int RADIUS = 3; //送信可能範囲の半径
	int sender = 0; //最初の送信者のノード番号
	int next_hop = -1;
	vector<int> destination = {2,0,2}; //目的地
	
	/* * * * * * * * * * 初期設定 * * * * * * * * * */
	/* 各ノードを配置 */
	node[0].setXY(0, 0);
	node[1].setXY(3, 0);
	node[2].setXY(5, 0);
	node[3].setXY(2, 1);
	node[4].setXY(7, 1);
	node[5].setXY(0, 2);
	node[6].setXY(5, 2);
	node[7].setXY(2, 3);
	node[8].setXY(4, 3);
	node[9].setXY(1, 4);
	node[10].setXY(5, 4);
	node[11].setXY(7, 4);
	node[12].setXY(2, 5);
	node[13].setXY(4, 5);
	node[14].setXY(0, 6);
	node[15].setXY(6, 6);
	node[16].setXY(1, 7);
	node[17].setXY(3, 7);
	node[18].setXY(5, 7);
	node[19].setXY(7, 7);
	
	for (int i = 0; i < NODENUM; i++) {
		node[i].setNodeNum(i);
	}
	
	/* 送信元を1つ指定 */
	Message a;
	a.setID(1);
	a.setPath(0);
	node[0].setMessage(a);
	
	
	
	
	
	/* * * * * * * * * * Routing * * * * * * * * * */
	/* (x,y)座標をZ記法に */
	for (int i = 0; i < NODENUM; i++) {
		int center = SIDE / 2;
		int x = node[i].getX();
		int y = node[i].getY();
		
		while (center >= 1) {
			if (y < center) {
				if (x < center) {
					node[i].setZ(0);
				} else {
					node[i].setZ(1);
					x -= center;
				}
			} else {
				if (x < center) {
					node[i].setZ(2);
					y -= center;
				} else {
					node[i].setZ(3);
					x -= center;
					y -= center;
				}
			}
			center = center / 2;
		}
		/* Routing Tableの初期設定 */
		node[i].setUpRT();
	}
	
	/* Routing Tableの更新,全宛先を補完 */
	/* 毎回半径3以内確認するのは無駄だから近隣ノード覚えさせよう */
	for (int timeslot = 0; timeslot < 4; timeslot++) {
		for (int i = 0; i < NODENUM; i++) {
			for (int j = 0; j < NODENUM; j++) {
				/* ノード間の距離計算(△x+△y) */
				int x = abs(node[i].getX() - node[j].getX());
				int y = abs(node[i].getY() - node[j].getY());
				int range = x*x + y*y;
				
				/* ブロードキャスト可能範囲であればRTを渡す */
				if ((range != 0) && (range <= RADIUS*RADIUS)) {
					node[i].receiveRT(node[j].sendRT(), j);
				}
			}
		}
	}

//	/* デバッグ用(各ノードのRTが持つ宛先を出力) */
//	cout << "Routing Table" << endl;
//	for (int i = 0; i < NODENUM; i++) {
//		cout << "Node[" << i << "]" << endl;
//		for (int j = 0; j < node[i].rt.table.size(); j++) {
//			/* Policy */
//			for (int p : node[i].rt.table[j].policy) {
//				cout << p << "/";
//			}
//			cout << " : ";
//			
//			/* Address */
//			if (!node[i].rt.table[j].address.empty()) {
//				for (int z : node[i].rt.table[j].address) {
//					cout << z << "/";
//				}
//				cout << " : ";
//			} else {
//				cout << "Empty : ";
//			}
//			
//			/* Hop Num */
//			if (node[i].rt.table[j].hop_num != 10000) {
//				cout << node[i].rt.table[j].hop_num << " : ";
//			} else {
//				cout << "INFINITY : ";
//			}
//			
//			/* Next Hop */
//			if (node[i].rt.table[j].next_hop != -1) {
//				cout << "Node[" << node[i].rt.table[j].next_hop << "]" << endl;
//			} else {
//				cout << "Empty" << endl;
//			}
//		}
//		cout << endl;
//	}
	
	
	
	
	
	/* * * * * * * * * * Forwarding * * * * * * * * * */
	cout << "Route:" << endl;
	cout << sender;
	while ((next_hop = node[sender].rt.getNextHop(destination)) != -1) {
		/* メッセージの送信 */
//		node[next_hop].receiveMessage(node[sender].sendMessage());
		cout << " -> " << next_hop;
		node[next_hop].rt.getNextHop(destination);
		
		/* 受信側が次の送信側へ */
		sender = next_hop;
	}
	cout << endl;
	
	return 0;
}