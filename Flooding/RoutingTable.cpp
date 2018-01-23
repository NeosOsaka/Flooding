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
#include <algorithm>

using namespace std;

/* RTの初期設定 */
void RoutingTable::setUp(vector<int> z_id) {
	/* 各エントリのポリシーを決定し、エントリをRTに追加する */
	/* N桁合致(=自分自身)のZ_IDを追加 */
	Entry myself;
	myself.policy = z_id;
	myself.address = z_id;
	myself.hop_num = 0;
	myself.next_hop = -1;
	table.push_back(myself);
	
	for (int i = 0; i < z_id.size(); i++) {
		Entry temp;
		temp.hop_num = 100000; //INFINITYとして初期値100000
		temp.next_hop = -1;
		vector<int> policy = z_id;
		
		for (int j = 0; j <= i; j++) {
			policy.pop_back();
		}
		
		for (int k = 0; k < 4; k++) {
			if (z_id[policy.size()] != k) {
				policy.push_back(k);
				temp.policy = policy;
				table.push_back(temp);
				policy.pop_back();
			}
		}
	}
}

/* RTの更新 */
void RoutingTable::update(RoutingTable rt, int node_num){
	/* 受け取ったRTの各エントリを取り出し、自身のどのエントリのポリシーと合致しているか比較 */
	for (Entry entry : rt.table) {
		/* エントリに宛先があれば自分のどのエントリに入れるか比較 */
		if (!(entry.address.empty())) {
			for (int i = 0; i < this->table.size(); i++) {
				/* 受信側ノードのポリシーと送信側ノードのエントリの宛先の比較 */
				bool match = true;
				for (int j = 0; j < table[i].policy.size(); j++) {
					if (entry.address[j] != table[i].policy[j]) {
						match = false;
						break;
					}
				}
				
				if (match) {
					/* まだ宛先が無いorホップ数がより短くなる場合 */
					if (table[i].address.empty() || ((entry.hop_num)+1 < table[i].hop_num)) {
						/* エントリの更新 */
						table[i].address = entry.address;
						table[i].hop_num = entry.hop_num + 1;
						table[i].next_hop = node_num;
						return;
					}
				}
			}
		}
	}
}

/* 目的地に対するNextHopの取得 */
int RoutingTable::getNextHop(vector<int> destination) {
	/* 自身のRTのどの宛先と最も近いか比較 */
	for (int i = 0; i < this->table.size(); i++) {
		/* 宛先が空でないエントリで */
		if (!table[i].address.empty()) {
			bool match = true;
			/* ポリシーがマッチしていれば */
			for (int j = 0; j < table[i].policy.size(); j++) {
				if (destination[j] != table[i].policy[j]) {
					match = false;
					break;
				}
			}
			
			/* NextHopを返し、次の経由先へ */
			if (match) {
				return table[i].next_hop;
			}
		}
	}
	
	/* どのポリシーにもマッチしなければ到達不能 */
	return -1;
}