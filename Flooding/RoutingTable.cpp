//
//  RoutingTable.cpp
//  Flooding
//
//  Created by neos on 2017/11/23.
//  Copyright (c) 2017年 Tatsuro Seno. All rights reserved.
//

#include "RoutingTable.h"
#include "Entry.h"
#include <iostream>
#include <vector>

using namespace std;

const static int INFINITY = 10000; //到達不能
const static int GHOST = -1; //存在しないノード番号

/* RTの初期設定 */
void RoutingTable::setUp(vector<int> z_id) {
	/* 各エントリを要素数分だけ初期値を与える */
	Entry iv; //initial value
	iv.hop_num = INFINITY;
	iv.next_hop = GHOST;

	for (int i = 0; i < 3*(z_id.size())+1; i++) {
		entry.push_back(iv);
	}
	
//	/* 各エントリのポリシーを決定し、エントリにRTに追加する */
//	for (int i = 0; i <= z_id.size(); i++) {
//		Entry temp;
//		temp.hop_num = INFINITY;
//		temp.next_hop = GHOST;
//		vector<int> policy;
//		
//		for (int j = 0; j < i; j++) {
//			policy.push_back(z_id[j]);
//		}
//		
//		for (int k = 0; k < 4; k++) {
//			if (z_id[policy.size()] != k) {
//				policy.push_back(k);
//				temp.policy = policy;
//				entry.push_back(temp);
//				policy.pop_back();
//			}
//		}
//	}
}