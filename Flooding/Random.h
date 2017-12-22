//
//  Random.h
//  Flooding
//
//  Created by neos on 2017/12/19.
//  Copyright (c) 2017年 Tatsuro Seno. All rights reserved.
//

#ifndef __Flooding__Random__
#define __Flooding__Random__

#include <iostream>
#include <vector>

using namespace std;

class Random {
private:
	
public:
	/* 指定された要素数分0or1を返す */
	vector<vector<bool>> genNodeState(int map_side);

};

#endif /* defined(__Flooding__Random__) */
