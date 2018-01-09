//
//  Message.cpp
//  Flooding
//
//  Created by neos on 2017/10/16.
//  Copyright (c) 2017年 Tatsuro Seno. All rights reserved.
//

#include <iostream>
#include <list>
#include "Message.h"

using namespace std;

/* 経路履歴に追加 */
void Message::setPath(int node_num) {
	path.push_back(node_num);
}

/* 経路履歴を表示 */
list<int> Message::getPath() {
	return path;
}

/* 識別子の設定 */
void Message::setID(int ID) {
	this->ID = ID;
}

/* 識別子の取得 */
int Message::getID() {
	return ID;
}

/* 経路のHop数を取得 */
int Message::getHopNum() {
	return path.size()-1;
}