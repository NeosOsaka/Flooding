//
//  RoutingTable.cpp
//  Flooding
//
//  Created by neos on 2017/11/23.
//  Copyright (c) 2017年 Tatsuro Seno. All rights reserved.
//

#include "RoutingTable.h"
#include <iostream>
#include <list>
#include <unordered_map>

using namespace std;

/* RTの初期設定 */
void RoutingTable::setUp(list<int> z_id) {
	for (int num : z_id) {
		for (int i = 0; i < 4; i++) {
			list<int> temp = z_id;
			
			/* tempの値を1つだけ変えてKeyとして保存 */
			if (num != i) {
				/* RTのZ記法の要素生成 */
				
			}
		}
	}
}

/* NextHopの追加 */
void RoutingTable::addNextHop(list<int> z_id, int nodenum) {
	
}