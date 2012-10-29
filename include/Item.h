#pragma once
#include "Starbucks.h"

/*
The Items are what make up the KdTree
Each one has a right and left pointer to point to the 
right and left subtrees.
Not implemented fully becuase of the switch to unsorted arrays.
*/
class Item{
public:
	Entry* data;
	Item* left;
	Item* right;
};
