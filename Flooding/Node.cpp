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

/* 送信回数の増加 */
void Node::addCount() {
	send_number++;
}

/* 送信回数の取得 */
int Node::getCount() {
	return send_number;
}

/* メッセージの送信 */
Message Node::sendMessage() {
	return msg;
}

/* メッセージの受信 */
void Node::receiveMessage(Message msg) {
	/* 受信したメッセージをリストに追加 */
	this->msg = msg;
	
	/* 自身のノード番号を追加 */
	this->msg.addPath(node_num);
}

/* メッセージ履歴に追加 */
void Node::addMsgPath(int node_num) {
	this->msg.addPath(node_num);
}

/* メッセージ履歴の取得 */
list<int> Node::getMsgPath() {
	return this->msg.getPath();
}

/* メッセージ識別子の設定 */
void Node::setMsgID(int ID) {
	this->msg.setID(ID);
}

/* メッセージ識別子の取得 */
int Node::getMsgID() {
	return this->msg.getID();
}