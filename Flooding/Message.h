//
//  Message.h
//  Flooding
//
//  Created by neos on 2017/10/16.
//  Copyright (c) 2017年 Tatsuro Seno. All rights reserved.
//

#ifndef __Flooding__Message__
#define __Flooding__Message__

#include <iostream>
#include <list>

using namespace std;

/* Pub/Subメッセージ用基底クラス */
class Message {
private:
	list<int> path; //経路中に辿ったノード
	int ID; //識別子

public:
	/* 経路履歴に追加 */
	void setPath(int node_num);
	
	/* 経路履歴の取得 */
	list<int> getPath();
	
	/* 識別子の設定 */
	void setID(int ID);
	
	/* 識別子の取得 */
	int getID();
};

#endif /* defined(__Flooding__Message__) */
