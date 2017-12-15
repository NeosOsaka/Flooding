
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
#include <algorithm>
#include "Entry.h"

using namespace std;

/* Pastry方式のルーティングテーブル用クラス */
class RoutingTable {
	private:

	public:
		vector<Entry> table; //RT(=エントリの集合)
	
		/* RTの初期設定 */
		void setUp(vector<int> z_id);
	
		/* 更新 */
		void update(RoutingTable rt, int node_num);
	
};

#endif /* defined(__Flooding__RoutingTable__) */