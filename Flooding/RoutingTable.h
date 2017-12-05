//
//  RoutingTable.h
//  Flooding
//
//  Created by neos on 2017/11/23.
//  Copyright (c) 2017年 Tatsuro Seno. All rights reserved.
//

#ifndef __Flooding__RoutingTable__
#define __Flooding__RoutingTable__

#include <iostream>
#include <list>
#include <unordered_map>

using namespace std;

/* Pastry方式のルーティングテーブル用クラス */
class RoutingTable {
private:
	//vectorにしよう 添字アクセス出来る
	unordered_map<list<int>, int> table; //Key:Z記法座標, Value:NextHop
	
public:
	/* RTの初期設定 */
	void setUp(list<int> z_id);
	
	/* NextHopの追加 */
	void addNextHop(list<int> z_id, int nodenum);
	
};

#endif /* defined(__Flooding__RoutingTable__) */
