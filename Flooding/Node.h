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
	int counter; //送信回数
	//list<Node> *receivers; //受け取り相手
	Message *msg; //メッセージ
	
public:
	/* (x,y)の指定 */
	void setXY(int x, int y);
	
	/* (x,y)を返す */
	int getX();
	int getY();
	
	/* メッセージの送信 */
	void sendMessage();
};

#endif /* defined(__Flooding__Node__) */
