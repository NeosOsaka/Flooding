//
//  Random.cpp
//  Flooding
//
//  Created by neos on 2017/12/19.
//  Copyright (c) 2017年 Tatsuro Seno. All rights reserved.
//

#include "Random.h"
#include <random>
#include <ctime>

using namespace std;

/* マップにランダムにノード生成 */
bool Random::genRandBool() {
	// 被決定的な乱数生成器でシード生成器を生成
	random_device rnd;
	// メルセンヌ・ツイスタ 引数は初期シード値 ファンクタを渡す
	mt19937 mt(rnd());
	uniform_int_distribution<int> rand2(0,1); // [0, 4]の一様乱数
	
	return rand2(mt);
}

vector<vector<bool>> Random::genNodeState(int map_side) {
	vector<vector<bool>> node_state(map_side, vector<bool>(map_side));
	for (int i = 0; i < map_side; i++) {
		for (int j = 0; j < map_side; j++) {
			node_state[i][j] = genRandBool();
		}
	}
	
	return node_state;
}