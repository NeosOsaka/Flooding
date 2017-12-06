//
//  Hash.h
//  Flooding
//
//  Created by neos on 2017/12/06.
//  Copyright (c) 2017年 Tatsuro Seno. All rights reserved.
//

#ifndef __Flooding__Hash__
#define __Flooding__Hash__

#include <iostream>
#include <vector>

using namespace std;

/* vetorをmapのkeyとして使う為のハッシュ関数クラス */
class Hash {
public:
	size_t operator()(const vector<int> &x) const {
		const int C = 997;      // 素数
		size_t t = 0;
		for (int i = 0; i != x.size(); ++i) {
			t = t * C + x[i];
		}
		return t;
	}
};

#endif /* defined(__Flooding__Hash__) */
