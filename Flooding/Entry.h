//
//  Entry.h
//  Flooding
//
//  Created by neos on 2017/12/14.
//  Copyright (c) 2017年 Tatsuro Seno. All rights reserved.
//

#ifndef __Flooding__Entry__
#define __Flooding__Entry__

#include <iostream>
#include <vector>

using namespace std;

/* Routing Tableのエントリ用クラス */
class Entry {
private:
	
public:
	vector<int> policy; //宛先の条件
	vector<int> destination; //宛先
	int hop_num; //Hop数
	int next_hop; //Next Hop(=ノード番号)
};

#endif /* defined(__Flooding__Entry__) */
