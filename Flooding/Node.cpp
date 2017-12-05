//
//  Node.cpp
//  Flooding
//
//  Created by neos on 2017/10/16.
//  Copyright (c) 2017年 Tatsuro Seno. All rights reserved.
//

#include <iostream>
#include <list>
#include <vector>
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

/* 送信回数の取得 */
int Node::getCount() {
	return send_number;
}

/* メッセージの送信 */
list<Message> Node::sendMessage() {
	/* 送信回数のカウント */
	for (Message a : msg) {
		//送信済みのメッセージもまとめてカウントして送ってるからいずれ修正
		send_number++;
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

/* メッセージを一通以上持っているか否か */
bool Node::hasMessage() {
	return !msg.empty();
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

/* Z記法座標の設定 */
void Node::setZ(int num) {
	z_id.push_back(num);
}

/* Z記法座標の取得 */
vector<int> Node::getZ() {
	return z_id;
}