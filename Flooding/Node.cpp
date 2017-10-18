//
//  Node.cpp
//  Flooding
//
//  Created by neos on 2017/10/16.
//  Copyright (c) 2017年 Tatsuro Seno. All rights reserved.
//

#include <iostream>
#include <list>
#include "Node.h"

using namespace std;

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

/* 状態の取得 */
bool Node::getState() {
	return state;
}

/* 送信/受信状態の変更 */
void Node::changeState() {
	if (!state) {
		state = true;
	}
}

/* 送信回数の増加 */
void Node::addCount() {
	send_number++;
}

/* 送信回数の取得 */
int Node::getCount() {
	return send_number;
}