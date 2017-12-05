//
//  LeafSet.cpp
//  Flooding
//
//  Created by neos on 2017/11/30.
//  Copyright (c) 2017年 Tatsuro Seno. All rights reserved.
//

#include <iostream>
#include <vector>
#include "LeafSet.h"

/* Z記法座標の設定 */
void LeafSet::setNodeNum(int nodenum) {
	this->nodenum = nodenum;
}

/* Z記法座標の取得 */
int LeafSet::getNodeNum() {
	return this->nodenum;
}

/* Z記法座標の設定 */
void LeafSet::setZID(vector<int> z_id) {
	this->z_id.clear();
	this->z_id = z_id;
}

/* Z記法座標の取得 */
vector<int> LeafSet::getZID() {
	return this->z_id;
}