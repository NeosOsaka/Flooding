//
//  Node.cpp
//  Flooding
//
//  Created by neos on 2017/10/16.
//  Copyright (c) 2017年 Tatsuro Seno. All rights reserved.
//

#include "Node.h"


/* (x,y)座標の指定 */
void Node::setXY(int x, int y) {
	this->x = x;
	this->y = y;
}

/* x座標の取得 */
int Node::getX() {
	return x;
}

/* y座標の取得 */
int Node::getY() {
	return y;
}

/* 送信相手の追加 */
void addReceiver(Node Receiver) {
	
}