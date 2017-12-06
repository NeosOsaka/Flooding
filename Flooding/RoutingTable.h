
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
#include <unordered_map>
#include "Hash.h"

using namespace std;

/* Pastry方式のルーティングテーブル用クラス */
class RoutingTable {
	private:
		//vectorにしよう 添字アクセス出来る
		unordered_map<vector<int>, int, Hash> table; //Key:Z記法座標, Value:NextHop
	
	public:
		/* RTの初期設定 */
		void setUp(vector<int> z_id);
	
};

#endif /* defined(__Flooding__RoutingTable__) */