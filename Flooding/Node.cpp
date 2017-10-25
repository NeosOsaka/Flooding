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

/* ノード番号の指定 */
void Node::setNodeNum(int node_num) {
	this->node_num = node_num;
}

/* ノード番号の取得 */
int Node::getNodeNum() {
	return node_num;
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

/* 送信回数の取得 */
int Node::getCount() {
	return send_number;
}

/* メッセージの送信 */
list<Message> Node::sendMessage() {
	/* 送信回数のカウント */
	for (Message a : msg) {
	}
	return msg;
}

/* メッセージの受信 */
bool Node::receiveMessage(list<Message> msg) {
	bool flag = false;
	
	/* 受信したメッセージをリストに追加 */
	for (Message rcv : msg) {
		/* 重複していないメッセージなら追加 */
		if (!hasMessage(rcv.getID())) {
			rcv.setPath(node_num);
			this->msg.push_back(rcv);
			flag = true;
		}
	}
	return flag;
}

/* メッセージの設定 */
void Node::setMessage(Message msg) {
	this->msg.clear();
	this->msg.push_back(msg);
}

/* メッセージの取得 */
list<Message> Node::getMessage() {
	return msg;
}

/* ある識別子のメッセージを持っているか否か */
bool Node::hasMessage(int ID) {
	for (Message a : msg) {
		if (a.getID() == ID) {
			return true;
		}
	}
	
	return false;
}