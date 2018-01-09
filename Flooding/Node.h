//
//  Node.h
//  Flooding
//
//  Created by neos on 2017/10/16.
//  Copyright (c) 2017年 Tatsuro Seno. All rights reserved.
//

#ifndef __Flooding__Node__
#define __Flooding__Node__

#include <iostream>
#include <list>
#include <vector>
#include "Message.h"
#include "RoutingTable.h"

using namespace std;

/* ノード用クラス */
class Node {
private:
	int x,y; //(x,y)座標
	vector<int> z_id; //Z記法座標
	int node_num = -1; //ノード番号
	int send_number = 0; //送信回数

public:
	/* Routing用の変数 */
	vector<int> neighbors; //近隣ノード集合
	RoutingTable rt; //Routing Table(宛先/Hop数:Next Hop)
	list<Message> msg; //メッセージ

	/* (x,y)座標の指定 */
	void setXY(int x, int y);

	/* x座標の取得 */
	int getX();

	/* y座標の取得 */
	int getY();

	/* ノード番号の指定 */
	void setNodeNum(int node_num);

	/* ノード番号の取得 */
	int getNodeNum();

	/* 送信回数の取得 */
	int getCount();

	/* メッセージの送信 */
	list<Message> sendMessage();

	/* メッセージの受信 */
	bool receiveMessage(list<Message> msg);

	/* メッセージの取得 */
	list<Message> getMessage();

	/* メッセージの設定 */
	void setMessage(Message msg);

	/* メッセージを一通以上持っているか否か */
	bool hasMessage();

	/* ある識別子のメッセージを持っているか否か */
	bool hasMessage(int ID);

	/* Z記法座標の設定 */
	void setZ(int num);

	/* Z記法座標の取得 */
	vector<int> getZ();

	/* RTの初期設定 */
	void setUpRT();

	/* RTの送信 */
	RoutingTable sendRT();

	/* RTの受信 */
	void receiveRT(RoutingTable rt, int node_num);
};


#endif /* defined(__Flooding__Node__) */
