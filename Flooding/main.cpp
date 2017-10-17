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

#define NODENUM 5

using namespace std;



int main(int argc, const char * argv[]) {
	Node node[NODENUM]; //ノード
	list<Node> senders_now(24); //現スロットで送信を行うノード集合
	list<Node> senders_next(24); //次スロットで送信を行うノード集合
	senders_now.clear();
	senders_next.clear();
	
	/* 各ノードを配置 */
	node[0].Node::setXY(0, 1);
	node[1].Node::setXY(2, 0);
	node[2].Node::setXY(2, 3);
	node[3].Node::setXY(4, 1);
	node[4].Node::setXY(4, 4);
	
	/* ノードを1つだけ送信状態に */
	node[4].changeState();
	senders_now.push_back(node[4]);
	
	/********** Flooding開始 **********/
	for (int i = 1; i < 20; i++) {
		/* タイムスロット表示 */
		cout << "Time Slot : " << i << endl;
		
		/* 送信ノードが残っている場合 */
		if (senders_now.size() != 0) {
			for (Node sender : senders_now) {
				/* 送信相手を探す */
				for (int j = 0; j < NODENUM; j++) {
					/* ノード間の距離計算(△x+△y) */
					int range = abs(sender.getX() - node[j].getX()) +
								abs(sender.getY() - node[j].getY());
					
					/* ブロードキャスト可能範囲であれば送信 */
					if ((range != 0) && (range <= 3) && (node[j].getState() == false)) {
						cout << "(" << sender.getX() << "," << sender.getY() << ") -> "
						<< "(" << node[j].getX() << "," << node[j].getY() << ")" << endl;
						
						/* "未所持"から"所持"へ */
						node[j].changeState();
						
						/* 受信ノードを次スロットの送信ノード集合に追加 */
						senders_next.push_back(node[j]);
					}
				}
			}
			senders_now.clear();
			senders_now = senders_next;
			senders_next.clear();
			
			/* 送信ノードが無ければFlooding終了 */
		} else {
			cout << endl;
			cout << "Program finished." << endl;
			break;
		}
	}
	
//	for (int i = 0; i < NODENUM; i++) {
//		/* ノードが送信状態であれば送信 */
//		if (node[i].Node::getState()) {
//			/* 送信相手を探す */
//			for (int j = 0; j < NODENUM; j++) {
//				/* ノード間の距離計算(△x+△y) */
//				int range = abs(node[i].getX() - node[j].getX()) +
//				abs(node[i].getY() - node[j].getY());
//				
//				/* ブロードキャスト可能範囲であれば受け取り相手としてリストに保存 */
//				if ((range != 0) && (range <= 3)) {
//					//node[i].addReceiver(node[j]);
//					cout << "(" << node[i].getX() << "," << node[i].getY() << ") -> "
//					<< "(" << node[j].getX() << "," << node[j].getY() << ")" << endl;
//				}
//			}
//		}
//	}
	
	return 0;
}