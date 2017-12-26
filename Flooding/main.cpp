//
//  main.cpp
//  Flooding
//
//  Created by neos on 2017/10/16.
//  Copyright (c) 2017年 Tatsuro Seno. All rights reserved.
//

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "Message.h"
#include "Node.h"
#include "RoutingTable.h"
#include "Entry.h"
#include "Random.h"


using namespace std;

const static int SIDE = 8; //マップの一辺
vector<Node> node; //ノード集合

int main(int argc, const char * argv[]) {
	const static int RADIUS = 3; //送信可能範囲の半径
	int sender = 0; //最初の送信者のノード番号
	int next_hop = -1;
	vector<int> destination = {3,3,3,3,3,3,3}; //目的地
	Random r;
	vector<vector<bool>> node_state = r.genNodeState(SIDE); //各ノードの状態

	/* Test用ここから */
	for (int i = 0; i < SIDE; i++) {
		for (int j = 0; j < SIDE; j++) {
			node_state[i][j] = false;
		}
	}
	
	node_state[0][0] = true;
	node_state[0][3] = true;
	node_state[0][5] = true;
	node_state[1][2] = true;
	node_state[1][7] = true;
	node_state[2][0] = true;
	node_state[2][5] = true;
	node_state[3][2] = true;
	node_state[3][4] = true;
	node_state[4][1] = true;
	node_state[4][5] = true;
	node_state[4][7] = true;
	node_state[5][2] = true;
	node_state[5][4] = true;
	node_state[6][0] = true;
	node_state[6][6] = true;
	node_state[7][1] = true;
	node_state[7][3] = true;
	node_state[7][5] = true;
	node_state[7][7] = true;
	/* ここまで */
	
	//	/* 到達不能なノードの削除 */
	//	//時間かからない方法考えとく
	//	for (int i = 0; i < SIDE; i++) {
	//		for (int j = 0; j < SIDE; j++) {
	//			/* (j,i)にノードが居る場合 */
	//			if (node_state[i][j]) {
	//				bool flag = true;
	//
	//				for (int k = i-RADIUS; k <= i+RADIUS; k++) {
	//					for (int l = j-RADIUS; l <= j+RADIUS; l++) {
	//						if (k>=0 && l>=0 && k<SIDE && l<SIDE && !((k==i)&&(l==j)) ) {
	//							int x = j - l;
	//							int y = i - k;
	//							if (x*x + y*y <= RADIUS*RADIUS) {
	//								flag = false;
	//							}
	//						}
	//					}
	//				}
	//
	//				/* もし近隣ノードが存在しなければ */
	//				if (flag) {
	//					/* (j,i)を削除 */
	//					node_state[i][j] = false;
	//				}
	//			}
	//		}
	//	}
	
	/* マップとノードの描画 */
	for (int i = 0; i < SIDE; i++) {
		cout << "__";
	}
	cout << "_" <<endl;
	
	for (int i = 0; i < SIDE; i++) {
		cout << "|";
		for (int j = 0; j < SIDE; j++) {
			if (node_state[i][j]) {
				cout << "◯|";
				/* ノードの生成 */
				Node n;
				n.setXY(j, i);
				node.push_back(n);
			} else {
				cout << " |";
			}
		}
		cout << endl;
	}
	
	for (int i = 0; i < SIDE; i++) {
		cout << "‾‾";
	}
	cout << "‾" << endl;
	
	
	
	
	
	/* * * * * * * * * * 初期設定 * * * * * * * * * */
	/* 各ノードを配置 */
	for (int i = 0; i < node.size(); i++) {
		node[i].setNodeNum(i);
	}
	
	/* 送信元を1つ指定 */
	Message a;
	a.setID(1);
	a.setPath(0);
	node[0].setMessage(a);
	
	
	
	
	
	/* * * * * * * * * * Routing * * * * * * * * * */
	/* (x,y)座標をZ記法に */
	for (int i = 0; i < node.size(); i++) {
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
	
	/* 近隣ノードを把握する */
	for (int i = 0; i < node.size(); i++) {
		for (int j = 0; j < node.size(); j++) {
			/* ノード間の距離計算(△x+△y) */
			int x = abs(node[i].getX() - node[j].getX());
			int y = abs(node[i].getY() - node[j].getY());
			int range = x*x + y*y;
			
			/* ブロードキャスト可能範囲であればNeighborに追加 */
			if ((range != 0) && (range <= RADIUS*RADIUS)) {
				node[i].neighbors.push_back(j);
			}
		}
	}
	
	/* Routing Tableの更新,全宛先を補完 */
	for (int timeslot = 0; timeslot < SIDE; timeslot++) {
		/* 近隣ノード宛にRT送信 */
		for (int i = 0; i < node.size(); i++) {
			for (int j : node[i].neighbors) {
				node[j].receiveRT(node[i].sendRT(), i);
			}
		}
	}
	

	
	
	
	/* * * * * * * * * * Forwarding * * * * * * * * * */
	/* 全ノード間の経路とホップ数を出力 */
	int hop_num[node.size()];
	for (int i = 0; i < node.size(); i++) {
		hop_num[i] = 0;
	}
	
	/* 経路の出力 */
	for (int start = 0; start < node.size(); start++) {
		cout << "Node[" << start << "] :" << endl;
		for (int end = 0; end < node.size(); end++) {
			/* 送受信ノードの記載 */
			cout << " ->Node[" << end << "]" <<endl;
			cout << "   ";
			
			/* 経路の計算 */
			cout << start;
			int a = start;
			while ((next_hop = node[a].rt.getNextHop(node[end].getZ())) != -1) {
				/* メッセージの送信 */
				cout << " " << next_hop;
				
				/* ホップ数をカウント */
				hop_num[next_hop]++;
				
				/* 受信側が次の送信側へ */
				a = next_hop;
			}
			
			cout << endl;
		}
		cout << endl;
	}

	/* ホップ数を出力 */
	cout << "Hop Num" << endl;
	for (int i = 0; i < node.size(); i++) {
		cout << "Node[" << i << "] : " << hop_num[i]-node.size()+1 << endl;
	}
	
	
	
//	cout << "(" << node[sender].getX() << "," << node[sender].getY() << ")";
//	while ((next_hop = node[sender].rt.getNextHop(destination)) != -1) {
//		/* メッセージの送信 */
//		cout << " -> ";
//		cout << "(" << node[next_hop].getX() << "," << node[next_hop].getY() << ")";
//		node[next_hop].rt.getNextHop(destination);
//		
//		/* 受信側が次の送信側へ */
//		sender = next_hop;
//	}
//	cout << endl << endl;
	

	
	
//	/* デバッグ用(各ノードのRTが持つ宛先を出力) */
//	cout << "Routing Table" << endl;
//	for (int i = 0; i < node.size(); i++) {
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
//				cout << "EMPTY : ";
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
//				cout << "NOT EXIST" << endl;
//			}
//		}
//		cout << endl;
//	}
	
	return 0;
}