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
	vector<int> destination = {3,3,3}; //目的地
	Random r;
	vector<vector<bool>> node_state = r.genNodeState(SIDE); //各ノードの状態




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


	/* 到達不能なノードは除外 */
//	for (int i = 0; i < SIDE; i++) {
//		for (int j = 0; j < SIDE; j++) {
//			if (node_state[i][j]) {
//				/* 近隣ノードが存在すればbreakして次のノードへ */
//				for (int k = 1; k <= 3; k++) {
//
//				}
//			}
//		}
//	}

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

	/* Routing Tableの更新,全宛先を補完 */
	/* 毎回半径3以内確認するのは無駄だから近隣ノード覚えさせよう */
	for (int timeslot = 0; timeslot < SIDE; timeslot++) {
		for (int i = 0; i < node.size(); i++) {
			for (int j = 0; j < node.size(); j++) {
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

	/* デバッグ用(各ノードのRTが持つ宛先を出力) */
	cout << "Routing Table" << endl;
	for (int i = 0; i < node.size(); i++) {
		cout << "Node[" << i << "]" << endl;
		for (int j = 0; j < node[i].rt.table.size(); j++) {
			/* Policy */
			for (int p : node[i].rt.table[j].policy) {
				cout << p << "/";
			}
			cout << " : ";

			/* Address */
			if (!node[i].rt.table[j].address.empty()) {
				for (int z : node[i].rt.table[j].address) {
					cout << z << "/";
				}
				cout << " : ";
			} else {
				cout << "EMPTY : ";
			}

			/* Hop Num */
			if (node[i].rt.table[j].hop_num != 10000) {
				cout << node[i].rt.table[j].hop_num << " : ";
			} else {
				cout << "INFINITY : ";
			}

			/* Next Hop */
			if (node[i].rt.table[j].next_hop != -1) {
				cout << "Node[" << node[i].rt.table[j].next_hop << "]" << endl;
			} else {
				cout << "NOT EXIST" << endl;
			}
		}
		cout << endl;
	}





	/* * * * * * * * * * Forwarding * * * * * * * * * */
	/* 全ノード間の経路とホップ数を出力 */
	for (int s = 0; s < node.size(); s++) {
		for (int r = 0; r < node.size(); r++) {

		}
	}
	cout << "(" << node[sender].getX() << "," << node[sender].getY() << ")";
	while ((next_hop = node[sender].rt.getNextHop(destination)) != -1) {
		/* メッセージの送信 */
		cout << " -> ";
		cout << "(" << node[next_hop].getX() << "," << node[next_hop].getY() << ")";
		node[next_hop].rt.getNextHop(destination);

		/* 受信側が次の送信側へ */
		sender = next_hop;
	}
	cout << endl << endl;




	return 0;
}
