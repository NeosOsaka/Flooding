
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
#include "Entry.h"

using namespace std;

/* Pastry方式のルーティングテーブル用クラス */
class RoutingTable {
	private:

	public:
		vector<Entry> entry; //RT(=エントリの集合)
	
		/* RTの初期設定 */
		void setUp(vector<int> z_id);
	
};

#endif /* defined(__Flooding__RoutingTable__) */