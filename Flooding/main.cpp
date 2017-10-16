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

using namespace std;


int main(int argc, const char * argv[]) {
	int NODENUM = 5;
	Node node[NODENUM];
	
	node[0].Node::setXY(0, 1);
	node[1].Node::setXY(2, 0);
	node[2].Node::setXY(2, 3);
	node[3].Node::setXY(4, 1);
	node[4].Node::setXY(4, 4);
	
	for (int i = 0; i < NODENUM; i++) {
		for (int j = 0; j < NODENUM; j++) {
			/* ノード間の距離計算(△x+△y) */
			int range = abs(node[i].getX() - node[j].getX()) +
						abs(node[i].getY() - node[j].getY());
			
			/* ブロードキャスト可能範囲であれば受け取り相手としてリストに保存 */
			if ((range != 0) && (range <= 3)) {
				//node[i].addReceiver(node[j]);
				cout << i << " -> " << j << endl;
			}
		}
	}
	
	
	return 0;
}