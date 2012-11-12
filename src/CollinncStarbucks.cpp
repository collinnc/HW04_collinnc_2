#include "CollinncStarbucks.h"
#include "Item.h"
#include "Resources.h"
#include <math.h>


void CollinncStarbucks::build(Entry* c, int n){
	
	int arr_len =0;
	//Entry* arr = new Entry[n];
	
	/*
	for(int i =0; i<n; i++){
		for(int j = 0; j<= arr_len; j++){
			if(((c+i)->x!= (arr+j)->x)||((c+i)->y!=(arr+j)->y)){
				*(arr+j)=*(c+i);
				arr_len++;
				break;
			}
		}
	}
	*/
	
	entries = new Entry[n];
    for(int i = 0; i<n; i++){
        (entries+i)->identifier = (c+i)->identifier;
        (entries+i)->x = (c+i)->x;
        (entries+i)->y = (c+i)->y;
    }

	items= new Item[n];
	for(int i = 0; i<n; i++){
		
		(items+i)->data=(entries+i);
		
		/*
		(items+i)->data->identifier = (entries+i)->identifier;
		(items+i)->data->x = (entries+i)->x;
		(items+i)->data->y = (entries+i)->y;
		*/
		(items+i)->r = rand()%256;
		(items+i)->g = rand()%256;
		(items+i)->b = rand()%256;
    }
	




	/*tree = new KdTree;
	Item* panda = new Item;
	
	panda->data=(entries+(n/2));
	tree->root=panda;*/
	
	/*Item* left = reorder(panda,n,true);
	Item* right = reorder(panda, n, false);*/


	/*panda = buildKdTree(entries, tree->root, true);
	tree->root=panda;*/
}

// Completely inspired by @Sonodabe
//Item* CollinncStarbucks::reorder(Item* arr, int arr_len, bool onLeft){
//
//	Item* mid = (arr + arr_len/2);
//	float compare = mid->data->x;
//	int bottom_count = 0;
//	int top_count=0;
//	int iter_bottom =0;
//	int iter_top =0;
//	
//	for(int i = 0; i<arr_len ; i++){
//		if( (arr + i)->data->x < compare)
//			bottom_count++;
//		else
//			top_count++;
//	}
//
//	Item* bottom = new Item[bottom_count];
//	Item* top = new Item[top_count];
//	//Item* noob = new Item[arr_len];
//
//	if(onLeft){
//		for( int j = 0; j<arr_len; j++){
//			if((arr+j)->data-> x < compare){
//				bottom[iter_bottom]=*(arr+j);
//				iter_bottom++;
//			}
//		}
//		return bottom;
//	}else{
//		for( int k=0;k<arr_len; k++){
//			if((arr+k)->data-> x > compare){
//				top[iter_top]=*(arr+k);
//				iter_top++;
//			}
//		}
//		return top;
//	}
//
//
//}

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
//	r->left=NULL;
//	r->right=NULL;
//	//Item* r = NULL;
//	if(c==NULL||r->data==NULL) return NULL;
//
//	//if(xLevel){
//	//	if(c->x < r->data->x)
//	//		//return buildKdTree(c, r->left, !xLevel);
//	//		r->left = buildKdTree(c, r->left,!xLevel);
//	//	else
//	//		//return buildKdTree(c, r->right, !xLevel);
//	//		r->right = buildKdTree(c, r->right, !xLevel);
//	//}
//	//else{
//	//	if(c->y < r->data->y)
//	//		//return buildKdTree(c,r->left,!xLevel);
//	//		r->left = buildKdTree(c, r->left, !xLevel);
//	//	else 
//	//		//return buildKdTree(c, r->right, !xLevel);
//	//		r->right = buildKdTree(c, r->right, !xLevel);
//	//}
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
		


	return getNearestItem(x,y)->data;//(items+shortestIndex)->data;
	//return NULL;
	
}

Item* CollinncStarbucks::getNearestItem(double x, double y){
		
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
