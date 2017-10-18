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
	int x,y; //(x,y)座標
	Message *msg; //メッセージ
	bool state = false; //メッセージ受信済/未受信状態
	int send_number = 0; //送信回数
	
public:
	/* (x,y)座標の指定 */
	void setXY(int x, int y);
	
	/* x座標の取得 */
	int getX();
	
	/* y座標の取得 */
	int getY();
	
	/* 状態の取得 */
	bool getState();
	
	/* 送信/受信状態の変更 */
	void changeState();
	
	/* 送信回数の増加 */
	void addCount();
	
	/* 送信回数の取得 */
	int getCount();
};

#endif /* defined(__Flooding__Node__) */
