#include "CollinncStarbucks.h"
#include "Item.h"
#include <math.h>


void CollinncStarbucks::build(Entry* c, int n){
	
	int arr_len =0;
	Entry* arr = new Entry[n];
	
	for(int i =0; i<n; i++){
		for(int j = 0; j<= arr_len; j++){
			if(((c+i)->x!= (arr+j)->x)||((c+i)->y!=(arr+j)->y)){
				*(arr+j)=*(c+i);
				arr_len++;
				break;
			}
		}
	}

	entries = new Entry[this->num_items];
    for(int i = 0; i<n; i++){
        (entries+i)->identifier = (c+i)->identifier;
        (entries+i)->x = (c+i)->x;
        (entries+i)->y = (c+i)->y;
    }
	//this->entries = entries;

	/*
	tree = new KdTree;
	tree->root->data->identifier = (arr+arr_len/2)->identifier;
	tree->root->data->x = (arr+arr_len/2)->x;
	tree->root->data->y = (arr+arr_len/2)->y;
	//tree->root = buildKdTree(arr, tree->root,true);

}

Item* buildKdTree(Entry* c, Item* root ,bool xLevel){
	//Item* root = new Item;
	/*
	if(c==NULL||root->data==NULL) return NULL;
	if(xLevel){
		if(c->x<root->data->x)
			return buildKdTree(c, root->left, !xLevel);
			//root->left = buildKdTree(c, !xLevel);
		else
			return buildKdTree(c, root->right, !xLevel);
			//root->right = buildKdTree(c, !xLevel);
	}
	else{
		if(c->y<root->data->y)
			return buildKdTree(c,root->left,!xLevel);
			//root->left = buildKdTree(c, !xLevel);
		else 
			return buildKdTree(c, root->right, !xLevel);
			//root->right = buildKdTree(c, !xLevel);
	}*/

	
	
	
}

Entry* CollinncStarbucks::getNearest(double x, double y){
	//Entry* c = new Entry;
	//c = this->entries;
	double smallestDistSoFar=sqrt((((((entries)->x)-x)*(((entries)->x)-x))+((((entries)->y)-y)*(((entries)->y)-y))));
	int shortestIndex =0;
	for(int i=1; i<this->num_items;  i++){
		double dist = sqrt((((((entries+i)->x)-x)*(((entries+i)->x)-x))+((((entries+i)->y)-y)*(((entries+i)->y)-y))));
		if(dist<smallestDistSoFar){
			smallestDistSoFar = dist;
			shortestIndex = i;
		}

	}

	return entries+shortestIndex;
	//return NULL;

}
