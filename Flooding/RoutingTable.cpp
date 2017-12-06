//
//  RoutingTable.cpp
//  Flooding
//
//  Created by neos on 2017/11/23.
//  Copyright (c) 2017年 Tatsuro Seno. All rights reserved.
//

#include "RoutingTable.h"
#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

/* RTの初期設定 */
//void RoutingTable::setUp(vector<int> z_id) {
//	for (int i = 0; i < z_id.size(); i++) {
//		for (int j = 0; j < 4; i++) {
//			vector<int> temp = z_id;
//			
//			/* tempの値を1つだけ変えてKeyとして保存 */
//			if (temp[i] != j) {
//				/* RTのZ記法の要素生成 */
//				temp[i] = j;
//				table[temp] = 0;
//			}
//		}
//	}
//}