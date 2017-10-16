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
	bool state = false; //メッセージを既に持っているか否か
	int counter; //送信回数
	list<Node> receivers; //受け取り相手
	
public:
	/* (x,y)座標の指定 */
	void setXY(int x, int y);
	
	/* x座標の取得 */
	int getX();
	
	/* y座標の取得 */
	int getY();
	
	/* 送信/受信状態の変更 */
	void changeState();
	
	/* 送信相手の追加 */
	void addReceiver(Node receiver);
};

#endif /* defined(__Flooding__Node__) */
