#include "CollinncStarbucks.h"
#include "Item.h"
#include "Resources.h"
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

	
	/*entries = new Entry[this->num_items];
    for(int i = 0; i<n; i++){
        (entries+i)->identifier = (c+i)->identifier;
        (entries+i)->x = (c+i)->x;
        (entries+i)->y = (c+i)->y;
    }*/

	items= new Item[arr_len];
	for(int i = 0; i<arr_len; i++){
		
		(items+i)->data=(arr+i);
		
		//(items+i)->data->identifier = (arr+i)->identifier;
		//(items+i)->data->x = (arr+i)->x;
		//(items+i)->data->y = (arr+i)->y;
		(items+i)->r = (int)(rand()*255);
		(items+i)->g = (int)(rand()*255);
		(items+i)->b = (int)(rand()*255);
    }

	
	/*panda->data->identifier = (arr+arr_len/2)->identifier;
	panda->data->x = (arr+arr_len/2)->x;
	panda->data->y = (arr+arr_len/2)->y;*/
	
	
	
	/*Entry* ent = new Entry;
	ent->identifier = "cat";
	ent->x = 0.5;
	ent->y = 0.5;

	panda->data = ent;*/
	
	
	/*panda->data->identifier = "dog";
	panda->data->x= .7;
	panda->data->y=.7;*/
	
	/*tree = new KdTree;
	Item* panda = new Item;
	
	panda->data=(entries+(n/2));
	tree->root=panda;
	

	for(int i=0; i<n;i++){

	panda = buildKdTree((entries+i), tree->root, true);
	tree->root=panda;
	}*/
}

//Item* CollinncStarbucks::buildKdTree(Entry* c, Item* root, bool xLevel){
//	
//	
//	Item* r = root;
//
//	/*
//	r->data->identifier = "cat";
//	r->data->x = .5;
//	r->data->y = .5;
//	*/
//	
//	
//	/*r->left=NULL;
//	r->right=NULL;*/
//	//Item* r = NULL;
//	if(c==NULL||r->data==NULL) return NULL;
//	
//	if(xLevel){
//		if(c->x < r->data->x)
//			//return buildKdTree(c, r->left, !xLevel);
//			r->left = buildKdTree(c, r->left,!xLevel);
//		else
//			//return buildKdTree(c, r->right, !xLevel);
//			r->right = buildKdTree(c, r->right, !xLevel);
//	}
//	else{
//		if(c->y < r->data->y)
//			//return buildKdTree(c,r->left,!xLevel);
//			r->left = buildKdTree(c, r->left, !xLevel);
//		else 
//			//return buildKdTree(c, r->right, !xLevel);
//			r->right = buildKdTree(c, r->right, !xLevel);
//	}
//
//	return r;
//	
//	
//}

Entry* CollinncStarbucks::getNearest(double x, double y){
	//Entry* c = new Entry;
	//c = this->entries;

	
	//Item* r = tree->root;
	//return tree->root->data;
		//slowGetNearest(x,y,r);
		
	
	double smallestDistSoFar=sqrt((((((items)->data->x)-x)*(((items)->data->x)-x))+((((items)->data->y)-y)*(((items)->data->y)-y))));
	int shortestIndex =0;
	for(int i=1; i<this->num_items;  i++){
		double dist = sqrt((((((items+i)->data->x)-x)*(((items+i)->data->x)-x))+((((items+i)->data->y)-y)*(((items+i)->data->y)-y))));
		if(dist<smallestDistSoFar){
			smallestDistSoFar = dist;
			shortestIndex = i;
		}

	}

	return (items+shortestIndex)->data;
	//return NULL;
	
}

Item* CollinncStarbucks::getNearestItem(double x, double y){
	//Entry* c = new Entry;
	//c = this->entries;

	
	//Item* r = tree->root;
	//return tree->root->data;
		//slowGetNearest(x,y,r);
		
	
	double smallestDistSoFar=sqrt((((((items)->data->x)-x)*(((items)->data->x)-x))+((((items)->data->y)-y)*(((items)->data->y)-y))));
	int shortestIndex =0;
	for(int i=1; i<this->num_items;  i++){
		double dist = sqrt((((((items+i)->data->x)-x)*(((items+i)->data->x)-x))+((((items+i)->data->y)-y)*(((items+i)->data->y)-y))));
		if(dist<smallestDistSoFar){
			smallestDistSoFar = dist;
			shortestIndex = i;
		}

	}

	return (items+shortestIndex);
	
	
}
//Entry* CollinncStarbucks::slowGetNearest(double x, double y, Item* r){
//	Item* sln = r;
//	return sln->data;
//}
