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

	// A helper method for the build method for creating the KdTree.
	// Never fully implemented due to the switch
	//Item* buildKdTree(Entry* c, Item* root , bool xLevel);

	Item* getNearestItem(double x, double y);
	//Entry* slowGetNearest(double x, double y, Item* r);
	
	//Item* reorder(Item* arr, int arr_len, bool onLeft);

	// A pointer to the root of the tree.
	//KdTree* tree;
	
	//Number of items in the given array
	int num_items;

	//Gives access to the data in the array
	Entry* entries;

	Item* items;

	
};