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
	/* 各エントリのポリシーを決定し、エントリをRTに追加する */
	/* N桁合致(=自分自身)のZ_IDを追加 */
	Entry myself;
	myself.policy = z_id;
	myself.hop_num = 0;
	myself.next_hop = -1; //自分自身のNextHopどうするか?
	entry.push_back(myself);
	
	for (int i = 0; i < z_id.size(); i++) {
		Entry temp;
		temp.hop_num = INFINITY;
		temp.next_hop = GHOST;
		vector<int> policy = z_id;
		
		for (int j = 0; j <= i; j++) {
			policy.pop_back();
		}
		
		for (int k = 0; k < 4; k++) {
			if (z_id[policy.size()] != k) {
				policy.push_back(k);
				temp.policy = policy;
				entry.push_back(temp);
				policy.pop_back();
			}
		}
	}
}

/* RTの更新 */
void RoutingTable::update(RoutingTable rt, int node_num){
	
}