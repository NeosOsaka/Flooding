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
	
	node[0].Node::setXY(0, 1);
	node[1].Node::setXY(2, 0);
	node[2].Node::setXY(2, 3);
	node[3].Node::setXY(4, 1);
	node[4].Node::setXY(4, 4);
	
	/* ノードを1つだけ送信状態に */
	node[4].Node::changeState();
	
	for (int i = 0; i < NODENUM; i++) {
		for (int j = 0; j < NODENUM; j++) {
			/* ノード間の距離計算(△x+△y) */
			int range = abs(node[i].getX() - node[j].getX()) +
						abs(node[i].getY() - node[j].getY());
			
			/* ブロードキャスト可能範囲であれば受け取り相手としてリストに保存 */
			if ((range != 0) && (range <= 3)) {
				//node[i].addReceiver(node[j]);
				cout << "(" << node[i].getX() << "," << node[i].getY() << ") -> "
					 << "(" << node[j].getX() << "," << node[j].getY() << ")" << endl;
			}
		}
	}
	
	
	return 0;
}