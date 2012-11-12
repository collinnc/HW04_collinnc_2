#pragma once
#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/Texture.h"
#include "CollinncStarbucks.h"
#include "Resources.h"
#include <iostream>
#include <fstream>
#include <vector>


/**
*@file HW04_collinnc_2App.cpp
*CSE 274 - Fall 2012
*A solution for HW04
*
*@author Nicholas Collins
*@date 2012-11-12
*
*@note This project attempts goals:
*	(B) upon left clicking
*   (C) upon right-clicking (after some substantial delay)
*   (EFG) by changing in code comments
*/

using namespace ci;
using namespace ci::app;
using namespace std;

// Creates a structure of census points
struct census_point{
	int popChange;
	double x;
	double y;
};

class HW04_collinnc_2App : public AppBasic {
  public:
	  //In this solution, this method constructs the inital array, 
	  // initializes the collinncStarbucks object and uses the build and getNearest methods.
	void setup();
	void mouseDown( MouseEvent event );	
	void update();
	void draw();

	static const int kAppWidth=700;
	static const int kAppHeight=700;
	static const int kTextureSize=1024;
	
	Surface* mySurface_;
	
	// Used to satisfy goal C
	void colorSurface(uint8_t* pixels, CollinncStarbucks* map);
	
	// Constructs the inital array of all the data after reading it in
	Entry* makeArray();
	
	// Used to visualize goal A
	void showPoints(uint8_t* pixels, Item* locs);

	// Used for goals EFG
	void getCensus();
	void colorDensity(uint8_t* pixels, vector<census_point>* census);
	
	int num_items;
	Entry* entries;
	uint8_t* dataArray;
	uint8_t* data2;
	CollinncStarbucks* test;

	bool clicked;

	Surface* deltaDensity;

	vector<census_point>* census;
	
};

void HW04_collinnc_2App::setup()
{
	mySurface_ = new Surface(kTextureSize,kTextureSize,false);
	deltaDensity = new Surface(kTextureSize, kTextureSize, false);

	census = new vector<census_point>();

	num_items=0;
	
	dataArray = (*mySurface_).getData();
	data2= (*deltaDensity).getData();

	ifstream in("Starbucks_2006.csv");
	
	entries = makeArray();
	test = new CollinncStarbucks;
	test->num_items = num_items;
	test->build(entries, num_items);
	showPoints(dataArray, test->items);
	//colorSurface(dataArray, test);
	
	// Comment in the following lines for goals EFG
	//getCensus();
	//colorDensity(data2, census);
}

void  HW04_collinnc_2App::colorSurface(uint8_t* pixels, CollinncStarbucks* map){	
	for(int i = 0; i<kAppWidth;i++){
		for(int j=0; j<kAppHeight;j++){
			double transformed_y=1-(double)j/kAppHeight;
			double transformed_x=(double)i/kAppWidth;
			Item* prox = map->getNearestItem(transformed_x,transformed_y);
			int offset = 3*(i+j*1024);
			pixels[offset] = prox->r;
			pixels[offset+1] = prox->g;
			pixels[offset+2] = prox->b;

		}
	}

}

void HW04_collinnc_2App::showPoints(uint8_t* pixels, Item* locs){
	
	for(int i=0; i< num_items; i++){
		int x1 = (int)(((locs+i)->data->x)*kAppWidth);
		int y1 = (int)((1-((locs+i)->data->y))*kAppHeight);
		int offset = 3*(x1+y1*1024);
		pixels[offset] = (locs+i)->r;
		pixels[offset+1] = (locs+i)->g;
		pixels[offset+2] = (locs+i)->b;
	}
}

Entry* HW04_collinnc_2App::makeArray(){
	
	ifstream in("Starbucks_2006.csv");
	string line;
	//find num_items
	while(in.good()){
		getline(in, line, '\r');
		num_items++;
	}	
	// Go back to beginning of input
	in.clear();
	in.seekg(0);

	double xPos, yPos;
	int i=0;
	Entry* arr = new Entry[num_items];
	while(in.good()){
		getline(in,line,',');
		in>>xPos;
		in.get();
		in>>yPos;
		(arr+i)->identifier = line;
		(arr+i)->x = xPos;
		(arr+i)->y = yPos;
		i++;
	}
	in.clear();
	in.seekg(0);
	in.close();
	return arr;
}

// Uses a method similar to @Sonodabe
void HW04_collinnc_2App::getCensus(){

	int buffer;
	ifstream cen1("Census_2000.csv");
	ifstream cen2("Census_2010.csv");
	census_point* tmp = new census_point;
	int pop1, pop2;
	double lon, lat;
	while(cen1.good() && cen2.good()){
		cen1 >> buffer;
        cen1.get();
        cen1 >> buffer;
        cen1.get();
        cen1 >> buffer;
        cen1.get();
        cen1 >> buffer;
        cen1.get();
		cen1 >> pop1;
		cen1.get();
		cen2 >> buffer;
        cen2.get();
        cen2 >> buffer;
        cen2.get();
        cen2 >> buffer;
        cen2.get();
        cen2 >> buffer;
        cen2.get();
		cen2 >> pop2;
		cen2.get();

		tmp->popChange = pop2-pop1;
		cen1 >> lon;
		cen1.get();
		cen1 >> lat;

		tmp->x = (lon+125.0)/62.0;
		tmp->y = (lat-24.0)/25.0;

		census->push_back(*tmp);
	}

	cen1.close();
	cen2.close();


}

void colorDensity(uint8_t* pixels, vector<census_point>* census){

	int red, green;
	int xPos, yPos;
	int offset;
	int tx, ty;

	for(int i = 0; i < (int)census->size(); i++){
		if(census->at(i).popChange<0){
			green = 0;
			if(census->at(i).popChange>3000)
				red = 255;
			else 
				red = (int)(255*((double)census->at(i).popChange/3000.0));
		}
		else{
			red =0;
			if(census->at(i).popChange>3000)
				green = 255;
			else
				green = (int)(255*((double)census->at(i).popChange/3000.0));
		}
		
		int tx = (int)((census->at(i).x)*700);
		int ty = (int)((census->at(i).y)*700);
		offset = 3*(tx+ty*1024);
		pixels[offset] = red;
		pixels[offset+1] = green;
		pixels[offset+2] = 0;


	}





}

void HW04_collinnc_2App::mouseDown( MouseEvent event )
{
	if(event.isLeft()){

		double click_x = (double)event.getX()/kAppWidth;
		double click_y = 1-((double)event.getY()/kAppHeight);
		Entry* place = test->getNearest(click_x,click_y);
		console()<<place->identifier+" "<<place->x<<" "<<place->y<<endl;
		//gl::color(Color8u(255,255,0));
		gl::drawSolidCircle(Vec2f((place->x)*kAppWidth,(1-(place->y))*kAppHeight), 25,0);
	}


	if(event.isRight()){
		if(clicked){
			colorSurface(dataArray, test);
			clicked = !clicked;
		}
		else{
			showPoints(dataArray, test->items);
			clicked = !clicked;
		}

	}
}

void HW04_collinnc_2App::update()
{

}

void HW04_collinnc_2App::draw()
{
	// clear out the window with black
	gl::clear();
	//gl::draw( *deltaDensity);
	gl::draw( *mySurface_ ); 
	
}

CINDER_APP_BASIC( HW04_collinnc_2App, RendererGl )
