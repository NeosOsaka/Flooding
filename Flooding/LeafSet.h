//
//  LeafSet.h
//  Flooding
//
//  Created by neos on 2017/11/30.
//  Copyright (c) 2017年 Tatsuro Seno. All rights reserved.
//

#ifndef __Flooding__LeafSet__
#define __Flooding__LeafSet__

#include <iostream>
#include <list>

using namespace std;

class LeafSet {
private:

public:
	int nodenum; //ノード番号
	list<int> z_id; //Z記法座標
	int x,y; //(x,y)座標
	
	/* Z記法座標の設定 */
	void setNodeNum(int nodenum);
	
	/* Z記法座標の取得 */
	int getNodeNum();
	
	/* Z記法座標の設定 */
	void setZID(list<int> z_id);
	
	/* Z記法座標の取得 */
	list<int> getZID();
	

};

#endif /* defined(__Flooding__LeafSet__) */
