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
#include <list>
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
	//	int sender = 0; //最初の送信者のノード番号
	int next_hop = -1;
	vector<int> destination = {3,3,3,3,3,3,3}; //目的地
	Random r;
	vector<vector<bool>> node_state = r.genNodeState(SIDE); //各ノードの状態
	ifstream ifs; //入力ファイル
	ofstream ofs; //出力ファイル
	
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
	int pass_num[node.size()];
	int hop_num[node.size()];
	
	/***** DVA + Pastry *****/
	cout << "----- Pastry&DVA -----" << endl;
	for (int i = 0; i < node.size(); i++) {
		pass_num[i] = 0;
		hop_num[i] = 0;
	}
	
	/* 経路の出力 */
	for (int start = 0; start < node.size(); start++) {
		for (int end = 0; end < node.size(); end++) {
			/* 送受信ノードの記載 */
			cout << start << " -> " << end << ",  ";
			
			/* 経路の計算 */
			cout << start;
			int a = start;
			int hop = 0;
			while ((next_hop = node[a].rt.getNextHop(node[end].getZ())) != -1) {
				/* メッセージの送信 */
				cout << "-" << next_hop;
				
				/* 通過回数とホップ数をカウント */
				pass_num[next_hop]++;
				hop++;
				/* 受信側が次の送信側へ */
				a = next_hop;
			}
			cout << ",  " << hop << "Hop" << endl;
			hop_num[start] += hop;
		}
		cout << endl;
	}
	
	/* Hop数を出力 */
	cout << "Pass Num" << endl;
	for (int i = 0; i < node.size(); i++) {
		cout << "Node[" << i << "] : " << pass_num[i]-node.size()+1 << endl;
	}
	cout << endl;
	
	
	
	
	
	/***** Greedy *****/
	cout << "----- Greedy -----" << endl;
	for (int i = 0; i < node.size(); i++) {
		pass_num[i] = 0;
		hop_num[i] = 0;
	}
	
	/* 経路の出力 */
	for (int start = 0; start < node.size(); start++) {
		for (int end = 0; end < node.size(); end++) {
			/* 送受信ノードの記載 */
			cout << start << " -> " << end << ",  ";
			
			/* 経路の計算 */
			cout << start;
			int a = start;
			int hop = 0;
			
			while (a != end) {
				int length = 2*SIDE*SIDE;
				
				/* 宛先に最も近い近隣ノードの計算 */
				for (int neighbor : node[a].neighbors) {
					int x = node[end].getX() - node[neighbor].getX();
					int y = node[end].getY() - node[neighbor].getY();
					
					if(x*x + y*y < length) {
						length = x*x + y*y;
						next_hop = neighbor;
					}
				}
				
				/* メッセージの送信 */
				cout << "-" << next_hop;
				
				/* 通過回数とホップ数をカウント */
				pass_num[next_hop]++;
				hop++;
				/* 受信側が次の送信側へ */
				a = next_hop;
			}
			
			cout << ",  " << hop << "Hop" << endl;
			hop_num[start] += hop;
		}
		cout << endl;
	}
	
	/* Hop数を出力 */
	cout << "Pass Num" << endl;
	for (int i = 0; i < node.size(); i++) {
		cout << "Node[" << i << "] : " << pass_num[i]-node.size()+1 << endl;
	}
	cout << endl;
	
	
	
	
	
	/***** Flooding *****/
	cout << "----- Flooding -----" << endl;
	for (int i = 0; i < node.size(); i++) {
		pass_num[i] = 0;
		hop_num[i] = 0;
	}
	
	list<int> senders_now; //現スロットで送信を行うノード集合
	list<int> senders_next; //次スロットで送信を行うノード集合
	senders_now.clear();
	senders_next.clear();
	
	for (int i = 0; i < node.size(); i++) {
		/* 初期化 */
		for (int j = 0; j < node.size(); j++) {
			node[j].msg.clear();
		}
		
		/* メッセージの設定 */
		Message a;
		a.setID(1);
		node[i].setMessage(a);
		senders_now.push_back(i);
		
		/* Flooding開始 */
		for (int timeslot = 1; ; timeslot++) {
			/* 送信ノードが残っている場合 */
			if (senders_now.size() != 0) {
				for (int s : senders_now) {
					for (int r : node[s].neighbors) {
						/* メッセージの受け渡し */
						bool next = node[r].receiveMessage(node[s].sendMessage());
						
						/* 受信ノードが新規メッセージを受信したなら次スロットで送信ノードになる */
						if (next) {
							bool flag = true;
							for (int a : senders_next) {
								if (a == r) {
									flag = false;
									break;
								}
							}
							
							if (flag) {
								senders_next.push_back(r);
							}
						}
					}
				}
				
				senders_now.clear();
				senders_now = senders_next;
				senders_next.clear();
				senders_now.sort();
			}
			/* 送信ノードが残っていない場合,Flooding終了 */
			else {
				/* 経路の出力 */
				for (int j = 0; j < node.size(); j++) {
					cout << i << " -> " << j <<",  ";
					cout << i;
					for (Message a : node[j].msg) {
						int num = 0;
						for (int point : a.getPath()) {
							cout << "-" << point;
							num++;
							
							/* Hop数を足す */
							pass_num[point]++;
						}
						cout << ",  " << num << "Hop" << endl;
						
					}
				}
				break;
			}
		}
		cout << endl;
	}
	
	
	/* Hop数を出力 */
	cout << "Pass Num" << endl;
	for (int i = 0; i < node.size(); i++) {
		cout << "Node[" << i << "] : " << pass_num[i]-node.size()+1 << endl;
	}
	cout << endl;
	

	
	
	return 0;
}
