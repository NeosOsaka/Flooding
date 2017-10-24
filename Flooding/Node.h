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
#include "Message.h"

using namespace std;

/* ノード用クラス */
class Node {
private:
	int node_num = -1; //ノード番号
	int x,y; //(x,y)座標
	Message msg; //メッセージ
	bool state = false; //メッセージ受信済/未受信状態
	int send_number = 0; //送信回数
	
public:
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
	
	/* 状態の取得 */
	bool getState();
	
	/* 送信/受信状態の変更 */
	void changeState();
	
	/* 送信回数の増加 */
	void addCount();
	
	/* 送信回数の取得 */
	int getCount();
	
	/* メッセージの送信 */
	Message sendMessage();
	
	/* メッセージの受信 */
	void receiveMessage(Message msg);
	
	/* メッセージ履歴に追加 */
	void addMsgPath(int node_num);
	
	/* メッセージ履歴の取得 */
	list<int> getMsgPath();
	
	/* メッセージ識別子の設定 */
	void setMsgID(int ID);
	
	/* メッセージ識別子の取得 */
	int getMsgID();
};

#endif /* defined(__Flooding__Node__) */
