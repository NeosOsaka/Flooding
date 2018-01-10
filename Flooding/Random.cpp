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
vector<vector<bool>> Random::genNodeState(int map_side) {
	vector<vector<bool>> node_state(map_side, vector<bool>(map_side));
	for (int i = 0; i < map_side; i++) {
		for (int j = 0; j < map_side; j++) {
			
			random_device rnd;
			mt19937 mt(rnd());
			uniform_int_distribution<int> rand(0,1);
			
			if (rand(mt) == 0) {
				node_state[i][j] = true;
			} else {
				node_state[i][j] =false;
			}
		}
	}
	
	return node_state;
}