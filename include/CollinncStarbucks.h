#pragma once
#include "Starbucks.h"
#include "Item.h"
#include "KdTree.h"



class CollinncStarbucks : public Starbucks {
public:
	virtual void build(Entry* c, int n);
	virtual Entry* getNearest(double x, double y);
	Item* buildKdTree(Entry* c, Item* root , bool xLevel);
	KdTree* tree;
	int num_items;
	Entry* entries;
};