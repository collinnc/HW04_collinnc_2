#pragma once
#include "Starbucks.h"
#include "Item.h"
#include "KdTree.h"


/**
The CollinncStarbucks class extends the given Starbucks.h,
which hill create and manipulate the data structure.
*/
class CollinncStarbucks : public Starbucks {
public:
	// Builds the data structure, in this solution by simply copying the array,
	// but filtering out the duplicates
	virtual void build(Entry* c, int n);
	
	// The getNearest method runs in linear time to find the closest location
	// to a single point (x,y). Looks through each element to compare.
	virtual Entry* getNearest(double x, double y);
	Item* getNearestItem(double x, double y);
	
	//Number of items in the given array
	int num_items;

	//Gives access to the data in the array
	Entry* entries;

	Item* items;

	
};