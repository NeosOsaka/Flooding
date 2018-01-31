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
	int next_hop = -1;
	vector<int> destination = {3,3,3,3,3,3,3,3,3,3}; //目的地
	Random r;
	vector<vector<bool>> node_state = r.genNodeState(SIDE); //各ノードの状態
	
		/* マップクリア */
		for (int i = 0; i < SIDE; i++) {
			for (int j = 0; j < SIDE; j++) {
				node_state[i][j] = false;
			}
		}
	
		node_state[0][0] = true;
		node_state[0][3] = true;
		node_state[0][4] = true;
		node_state[1][2] = true;
		node_state[1][7] = true;
		node_state[2][0] = true;
		node_state[2][4] = true;
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
	
//	/* 中央に8×8マスのホールを作る */
//	int s = SIDE/2 - 4;
//	for (int i = s; i < s+8 ; i++) {
//		for (int j = s; j < s+8; j++) {
//			node_state[i][j] = false;
//		}
//	}
	
	/* マップとノードの描画 */
	for (int i = 0; i < SIDE; i++) {
		for (int j = 0; j < SIDE; j++) {
			if (node_state[i][j]) {
				cout << "|●";
				/* ノードの生成 */
				Node n;
				n.setXY(j, i);
				node.push_back(n);
			} else {
				cout << "| ";
			}
		}
		cout << "|";
		cout << endl;
	}
	cout << endl;
	
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
			/* ノード間の距離計算 */
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
	vector<vector<int>> miss_hit(node.size());
	int pass_num_pd[node.size()];
	int hop_num_pd[node.size()];
	int unreachable_pd[node.size()];
	int pass_num_greedy[node.size()];
	int hop_num_greedy[node.size()];
	int unreachable_greedy[node.size()];
	int pass_num_greedy2[node.size()];
	int hop_num_greedy2[node.size()];
	int unreachable_greedy2[node.size()];
	
	/***** DVA + Pastry *****/
	cout << "----- Pastry+DVA -----" << endl;
	for (int i = 0; i < node.size(); i++) {
		pass_num_pd[i] = 0;
		hop_num_pd[i] = 0;
		unreachable_pd[i] = 0;
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
				pass_num_pd[next_hop]++;
				hop++;
				/* 受信側が次の送信側へ */
				a = next_hop;
			}
			
						cout << ",  " << hop << "Hop" << endl;
			hop_num_pd[start] += hop;
			
			/* 到達出来なかった場合 */
			if (a != end) {
				unreachable_pd[start]++;
			}
		}
				cout << endl;
	}
	
	/* Hop数を出力 */
	int total_hop = 0;
	cout << "Total Hop Num" << endl;
	for (int i = 0; i < node.size(); i++) {
		pass_num_pd[i] -= node.size()-1;
		//		cout << "Node[" << i << "] : " << pass_num[i] << endl;
		cout << i << "," << pass_num_pd[i] << "," << node[i].getX() << "," << node[i].getY() << endl;
		total_hop += pass_num_pd[i];
	}
	cout << "Total : " << total_hop << endl;
	cout << endl;
	
	
	//	//Test用ここから
	//	/* Hop数を降順にソート */
	//	sort(pass_num_pd, pass_num_pd+node.size(), greater<int>());
	//
	//	for (int i = 0; i < node.size(); i++) {
	//		cout << i << " ";
	//		cout << pass_num_pd[i] << endl;
	//	}
	//	cout << endl;
	//	//ここまで
	
	
	
	
	
	/***** Greedy *****/
	cout << "----- Greedy -----" << endl;
	for (int i = 0; i < node.size(); i++) {
		pass_num_greedy[i] = 0;
		hop_num_greedy[i] = 0;
		unreachable_greedy[i] = 0;
	}
	
	/* 経路の出力 */
	for (int start = 0; start < node.size(); start++) {
		for (int end = 0; end < node.size(); end++) {
			list<int> path; //経路(到達不能確認用)
			int flag = false;
			
			/* 送受信ノードの記載 */
			cout << start << " -> " << end << ",  ";
			
			/* 経路の計算 */
			cout << start;
			int a = start;
			int hop = 0;
			
			while (a != end) {
				/* 既に通ったノードでないかチェック */
				for (int num : path) {
					if (num == a) {
						/* 既に通っているので到達不能 */
						miss_hit[start].push_back(end);
						unreachable_greedy[start]++;
						flag = true;
						break;
					}
				}
				
				/* 到達不能な場合は打ち切り */
				if (flag) {
					cout << "-X";
					break;
				}
				
				/* 到達可能な場合 */
				path.push_front(a);
				
				
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
				pass_num_greedy[next_hop]++;
				hop++;
				/* 受信側が次の送信側へ */
				a = next_hop;
			}
			
			cout << ",  " << hop << "Hop" << endl;
			hop_num_greedy[start] += hop;
		}
		
		cout << endl;
	}
	cout << endl;
	
	/* Hop数を出力 */
	total_hop = 0;
	cout << "Total Hop Num" << endl;
	for (int i = 0; i < node.size(); i++) {
		pass_num_greedy[i] -= node.size()-1;
		//		cout << "Node[" << i << "] : " << pass_num[i] << endl;
		cout << i << "," << pass_num_greedy[i] << "," << node[i].getX() << "," << node[i].getY() << endl;
		total_hop += pass_num_greedy[i];
	}
	cout << "Total : " << total_hop << endl;
	cout << endl;
	
	//	//Test用ここから
	//	/* Hop数を降順にソート */
	//	sort(pass_num_greedy, pass_num_greedy+node.size(), greater<int>());
	//	for (int i = 0; i < node.size(); i++) {
	//		cout << i << " ";
	//		cout << pass_num_greedy[i] << endl;
	//	}
	//	cout << endl;
	//	//ここまで
	
	
	
	
	/***** Greedy2 *****/
	cout << "----- Greedy2 -----" << endl;
	for (int i = 0; i < node.size(); i++) {
		pass_num_greedy2[i] = 0;
		hop_num_greedy2[i] = 0;
		unreachable_greedy2[i] = 0;
		node[i].neighbors_used.clear();
	}
	
	/* 経路の出力 */
	for (int start = 0; start < node.size(); start++) {
		for (int end = 0; end < node.size(); end++) {
			vector<int> trace; //中継点
			int a = start;
			int hop = 0;
			
			/* 送受信ノードの記載 */
			cout << start << " -> " << end << ",  ";
			cout << start;
			
			while (a != end) {
				next_hop = -1;
				int flag = false;
				int length = 2*SIDE*SIDE;
				
				/* 中継点として記録 */
				trace.push_back(a);
				
				/* 宛先に最も近い近隣ノードの計算 */
				for (int neighbor : node[a].neighbors) {
					/* ノードが送信済みかどうか判定 */
					for (int i = 0; i < node[a].neighbors_used.size(); i++) {
						if (neighbor == node[a].neighbors_used[i]) {
							flag = true;
							break;
						}
					}
					
					
					/* 送信済みノードなら無視して次 */
					if (flag) {
						break;
					}
					
					int x = node[end].getX() - node[neighbor].getX();
					int y = node[end].getY() - node[neighbor].getY();
					
					if(x*x + y*y < length) {
						length = x*x + y*y;
						next_hop = neighbor;
					}
				}
				
				/* 送信出来るノードが無ければ到達不能扱い */
				if (next_hop == -1) {
					unreachable_greedy2[a]++;
					cout << "-X";
					break;
				}
				
				/* メッセージの送信 */
				cout << "-" << next_hop;
				
				/* 送信済み近隣ノードの追加 */
				node[a].neighbors_used.push_back(next_hop);
				
				/* 通過回数とホップ数をカウント */
				pass_num_greedy2[next_hop]++;
				hop++;
				/* 受信側が次の送信側へ */
				a = next_hop;
			}
			
			cout << ",  " << hop << "Hop" << endl;
			hop_num_greedy2[start] += hop;
			
			/* 中継点となった全てのノードの送信済みノードを初期化 */
			for (int i = 0;  i < trace.size(); i++) {
				node[trace[i]].neighbors_used.clear();
			}
		}
		cout << endl;
	}
	cout << endl;
	
	
	/* Hop数を出力 */
	total_hop = 0;
	cout << "Total Hop Num" << endl;
	for (int i = 0; i < node.size(); i++) {
		pass_num_greedy2[i] -= node.size()-1;
		cout << i << "," << pass_num_greedy2[i] << "," << node[i].getX() << "," << node[i].getY() << endl;
		total_hop += pass_num_greedy2[i];
	}
	cout << "Total : " << total_hop << endl;
	cout << endl;

	
	/* 到達不能回数 */
	int total_unreachable_pd = 0;
	int total_unreachable_greedy = 0;
	int total_unreachable_greedy2 = 0;
	cout << "Miss Hit Num" << endl;
	for (int i = 0; i < node.size(); i++) {
		total_unreachable_pd += unreachable_pd[i];
		total_unreachable_greedy += unreachable_greedy[i];
		total_unreachable_greedy2 += unreachable_greedy2[i];
	}
	cout << "Pastry+DVA : " << total_unreachable_pd << endl;
	cout << "Greedy : " << total_unreachable_greedy << endl;
	cout << "Greedy2 : " << total_unreachable_greedy2 << endl;
	
	/* Greedyの不到達経路 */
	cout << "Miss Hit" << endl;
	for (int i = 0;  i < node.size(); i++) {
		for (int j = 0; j < miss_hit[i].size(); j++) {
			cout << i << " -> " << miss_hit[i][j] <<endl;
		}
	}
	
	
	
	//	/***** Flooding *****/
	//	cout << "----- Flooding -----" << endl;
	//	for (int i = 0; i < node.size(); i++) {
	//		pass_num[i] = 0;
	//		hop_num[i] = 0;
	//	}
	//
	//	list<int> senders_now; //現スロットで送信を行うノード集合
	//	list<int> senders_next; //次スロットで送信を行うノード集合
	//	senders_now.clear();
	//	senders_next.clear();
	//
	//	for (int i = 0; i < node.size(); i++) {
	//		/* 初期化 */
	//		for (int j = 0; j < node.size(); j++) {
	//			node[j].msg.clear();
	//		}
	//
	//		/* メッセージの設定 */
	//		Message a;
	//		a.setID(1);
	//		node[i].setMessage(a);
	//		senders_now.push_back(i);
	//
	//		/* Flooding開始 */
	//		for (int timeslot = 1; ; timeslot++) {
	//			/* 送信ノードが残っている場合 */
	//			if (senders_now.size() != 0) {
	//				for (int s : senders_now) {
	//					for (int r : node[s].neighbors) {
	//						/* メッセージの受け渡し */
	//						bool next = node[r].receiveMessage(node[s].sendMessage());
	//
	//						/* 受信ノードが新規メッセージを受信したなら次スロットで送信ノードになる */
	//						if (next) {
	//							bool flag = true;
	//							for (int a : senders_next) {
	//								if (a == r) {
	//									flag = false;
	//									break;
	//								}
	//							}
	//
	//							if (flag) {
	//								senders_next.push_back(r);
	//							}
	//						}
	//					}
	//				}
	//
	//				senders_now.clear();
	//				senders_now = senders_next;
	//				senders_next.clear();
	//				senders_now.sort();
	//			}
	//			/* 送信ノードが残っていない場合,Flooding終了 */
	//			else {
	//				/* 経路の出力 */
	//				for (int j = 0; j < node.size(); j++) {
	////					cout << i << " -> " << j <<",  ";
	////					cout << i;
	//					for (Message a : node[j].msg) {
	//						int num = 0;
	//						for (int point : a.getPath()) {
	////							cout << "-" << point;
	//							num++;
	//
	//							/* Hop数を足す */
	//							pass_num[point]++;
	//						}
	////						cout << ",  " << num << "Hop" << endl;
	//
	//					}
	//				}
	//				break;
	//			}
	//		}
	////		cout << endl;
	//	}
	//
	//
	//	/* Hop数を出力 */
	//	total_hop = 0;
	//	cout << "Total Hop Num" << endl;
	//	for (int i = 0; i < node.size(); i++) {
	//		pass_num[i] -= node.size()-1;
	//		cout << "Node[" << i << "] : " << pass_num[i] << endl;
	//		total_hop += pass_num[i];
	//	}
	//	cout << "Total : " << total_hop << endl;
	//	cout << endl;
	
	
	
	
	
	
	return 0;
}
