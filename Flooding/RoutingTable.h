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
#include <vector>

using namespace std;

/* Pastry方式のルーティングテーブル用クラス */
class RoutingTable {
private:
	/* 経路表(Key:zID,Value:NextHop) */
	vector<vector<int>> rt;
	
	
public:
	/* 初期化(サイズの決定) */
	/* 値を付与する */
	void addValue();
};

#endif /* defined(__Flooding__RoutingTable__) */
