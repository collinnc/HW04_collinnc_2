#include "CollinncStarbucks.h"
#include "Item.h"
#include "Resources.h"
#include <math.h>


void CollinncStarbucks::build(Entry* c, int n){
	
	int arr_len =0;
	
	entries = new Entry[n];
    for(int i = 0; i<n; i++){
        (entries+i)->identifier = (c+i)->identifier;
        (entries+i)->x = (c+i)->x;
        (entries+i)->y = (c+i)->y;
    }

	items= new Item[n];
	for(int i = 0; i<n; i++){
		
		(items+i)->data=(entries+i);
		(items+i)->r = rand()%256;
		(items+i)->g = rand()%256;
		(items+i)->b = rand()%256;
    }
	
}



Entry* CollinncStarbucks::getNearest(double x, double y){


	return getNearestItem(x,y)->data;
	
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

