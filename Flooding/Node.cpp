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

/* (x,y)座標からZ記法座標を得る */
void Node::setZ(int side) {
	int x = this->x;
	int y = this->y;
	int center = side;
	
	/* 0~3のどの領域にいるか判定しつつ、辺を半分にし続ける */
	while (center > 1) {
		center /= 2;
		
		if (y < center) {
			if (x < center) {
				z_id.push_back(0);
			} else {
				z_id.push_back(1);
				x -= center;
			}
		} else {
			if (x < center) {
				z_id.push_back(2);
				y -= center;
			} else {
				z_id.push_back(3);
				x -= center;
				y -= center;
			}
		}
	}
	
}