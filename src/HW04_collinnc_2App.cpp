#pragma once
#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/Texture.h"
#include "CollinncStarbucks.h"
#include "cinder/ImageIo.h"
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
*	(A) upon pressing an unassigned key
*   (B) upon left clicking
*   (C) upon pressing 'c' (after some substantial delay)
*   (D) upon right clicking
*   (F) upon pressing 'p' (after some delay)
*
*@citation: Brandon Sonoda helped inspire a few lines here and there, 
*	notably those is makeArray() and getCensus().
*	All other code is original or inspired by Bo Brinkman from given files
*   or class. 
*   Thanks!
*/

using namespace ci;
using namespace ci::app;
using namespace std;


class HW04_collinnc_2App : public AppBasic {
  public:
	  //In this solution, this method constructs the inital array, 
	  // initializes the collinncStarbucks object and uses the build and getNearest methods.
	void setup();
	void mouseDown( MouseEvent event );	
	void keyDown(KeyEvent event);
	void update();
	void draw();
	void prepareSettings(Settings* settings);

	static const int kAppWidth=700;
	static const int kAppHeight=700;
	static const int kTextureSize=1024;
	
	//Used for showPoint and colorSurface
	Surface* mySurface_;
	
	// Used when zooming
	Surface* zoomer;
	
	// Used for goal F
	Surface* deltaDensity;
	
	// Used to satisfy goal C
	void colorSurface(uint8_t* pixels, CollinncStarbucks* map);
	
	// Constructs the inital array of all the data after reading it in
	Entry* makeArray();
	
	// Used to visualize goal A
	void showPoints(uint8_t* pixels, Item* locs);
	
	//Press any key to show the map Satisfies goal A
	bool showMap;

	// Used for goal F
	void getCensus();
	void colorDensity(uint8_t* pixels, CollinncStarbucks* map);

	// Used for goal D. Zooms in at the location of the mouse
	void zoomIn(uint8_t* pixels, Item* locs, int cx, int cy);
	
	int getMaxPop(Item* locs);

	int num_items;
	Entry* entries;
	uint8_t* dataArray;
	uint8_t* data2;
	uint8_t* regionalData;
	uint8_t* zoom;
	CollinncStarbucks* test;
	double proxX, proxY;
	int zoomX, zoomY;

	bool clicked;
	bool zoomed;
	bool showDensity;
	gl::Texture map;
	
};

void HW04_collinnc_2App::prepareSettings(Settings* settings){
	(*settings).setWindowSize(kAppWidth, kAppHeight);
	(*settings).setResizable(false);

}

void HW04_collinnc_2App::setup()
{
	// Pic obtained from mapsof.net/map/united-states
	map = gl::Texture(loadImage("usa3.png"));
	mySurface_ = new Surface(kTextureSize,kTextureSize,false);
	deltaDensity = new Surface(kTextureSize, kTextureSize, false);
	zoomer = new Surface(kTextureSize, kTextureSize, false);

	//census = new vector<census_point>();
	zoomed=false;
	showMap=false;
	clicked=false;
	showDensity = false;
	num_items=0;
	
	dataArray = (*mySurface_).getData();
	data2= (*deltaDensity).getData();
	zoom = (*zoomer).getData();
	
	ifstream in("Starbucks_2006.csv");
	
	entries = makeArray();
	test = new CollinncStarbucks;
	test->num_items = num_items;
	test->build(entries, num_items);
	showPoints(dataArray, test->items);
	
	// The following method is what causes the lag in run-time
	getCensus();
		
}

void  HW04_collinnc_2App::colorSurface(uint8_t* pixels, CollinncStarbucks* map){	
	double transformed_y, transformed_x;
	Item* prox;
	int offset;
	
	for(int i = 0; i<kAppWidth;i++){
		for(int j=0; j<kAppHeight;j++){
			transformed_y=1-(double)j/kAppHeight;
			transformed_x=(double)i/kAppWidth;
			prox = map->getNearestItem(transformed_x,transformed_y);
			offset = 3*(i+j*1024);
			pixels[offset] = prox->r;
			pixels[offset+1] = prox->g;
			pixels[offset+2] = prox->b;

		}
	}
}

void HW04_collinnc_2App::showPoints(uint8_t* pixels, Item* locs){
	//Clear out the screen with black
	for(int h=0;h<3*kTextureSize*kTextureSize;h++)
		pixels[h]=0;

	for(int i=0; i< num_items; i++){
		int x1 = (int)(((locs+i)->data->x)*kAppWidth);
		int y1 = (int)((1-((locs+i)->data->y))*kAppHeight);
		int offset = 3*(x1+y1*1024);
		pixels[offset] = (locs+i)->r;
		pixels[offset+1] = (locs+i)->g;
		pixels[offset+2] = (locs+i)->b;
	}
}

void HW04_collinnc_2App::zoomIn(uint8_t* pixels, Item* locs, int cx, int cy){

	// Bounds checking
	if(cx < 50) cx= 50;
	if(cx > kAppWidth-50) cx = kAppWidth-50;
	if(cy < 50) cy=50;
	if(cy > kAppHeight - 50) cy = kAppHeight-50;

	// Clear out the screen
	for(int h=0;h<3*kTextureSize*kTextureSize;h++)
		pixels[h] =0;

	int num_valid =0;
	// Find the size of the array
	for(int i=0;i<num_items; i++){
		if(((locs+i)->data->x)*kAppWidth >= cx-50 && ((locs+i)->data->x)*kAppWidth <= cx+50 
			&& (1-(locs+i)->data->y)*kAppHeight >= cy-50 && (1-(locs+i)->data->y)*kAppHeight <= cy+50)
			num_valid++;
	}

	Item* valid_points = new Item[num_valid];
	int valid_index =0;

	//Populate the array
	for(int j=0; j<num_items; j++){
		if(((locs+j)->data->x)*kAppWidth >= cx-50 && ((locs+j)->data->x)*kAppWidth <= cx+50 
			&& (1-((locs+j)->data->y))*kAppHeight >= cy-50 && (1-((locs+j)->data->y))*kAppHeight <= cy+50){
		
				(valid_points+valid_index)->data = (locs+j)->data;
				(valid_points+valid_index)->r = (locs+j)->r;
				(valid_points+valid_index)->g = (locs+j)->g;
				(valid_points+valid_index)->b = (locs+j)->b;
				valid_index++;
		}
	}

	// Write to the Surface
	int new_x, new_y, offset;
	for(int k=0; k<num_valid;k++){
		new_x = ((int)(((valid_points+k)->data->x)*kAppWidth)-(cx-50))*7;
		new_y = ((int)((1-((valid_points+k)->data->y))*kAppHeight)-(cy-50))*7;
		offset = 3*(new_x+new_y*kTextureSize);
		pixels[offset] = (valid_points+k)->r;
		pixels[offset+1] = (valid_points+k)->g;
		pixels[offset+2] = (valid_points+k)->b;

	}
}

// Uses a method similar to Brandon Sonoda
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

	int pop;
	double lon, lat;
	Item* close;
	while(cen1.good()){
		cen1 >> buffer;
        cen1.get();
        cen1 >> buffer;
        cen1.get();
        cen1 >> buffer;
        cen1.get();
        cen1 >> buffer;
        cen1.get();
		cen1 >> pop;
		cen1.get();
		cen1 >> lon;
		cen1.get();
		cen1 >> lat;

		close = test->getNearestItem(lon, lat);
		close->population = pop;
	}

	cen1.close();

}

int HW04_collinnc_2App::getMaxPop(Item* locs){
	int maxPop = 0;
	for(int i =0; i<num_items; i++){
		if(locs->population >maxPop)
			maxPop = locs->population;
	}

	return maxPop;

}

void HW04_collinnc_2App::colorDensity(uint8_t* pixels, CollinncStarbucks* map){

	int offset;

	int maxPop = getMaxPop(test->items);

	double transformed_y,transformed_x;
	Item* prox;
		
	for(int i = 0; i<kAppWidth;i++){
		for(int j=0; j<kAppHeight;j++){
			transformed_y=1-(double)j/kAppHeight;
			transformed_x=(double)i/kAppWidth;
			prox = map->getNearestItem(transformed_x,transformed_y);
			offset = 3*(i+j*1024);
			pixels[offset] = ((double)prox->population/(double)maxPop)*255;
			pixels[offset+1] = 255-((double)prox->population/(double)maxPop)*255;
			pixels[offset+2] = 150;
		}
	}
}

void HW04_collinnc_2App::mouseDown( MouseEvent event )
{
	// Left click to highlight nearest starbucks
	if(event.isLeft()){
		double click_x, click_y;

		if(zoomed){
			click_x = ((zoomX-50)+(100.0*((double)event.getX()/kAppWidth)))/kAppWidth;
			click_y = 1-(((zoomY-50)+(100.0*((double)event.getY()/kAppHeight)))/kAppHeight);

		}
		else{
			click_x = (double)event.getX()/kAppWidth;
			click_y = 1-((double)event.getY()/kAppHeight);
		}


		Entry* place = test->getNearest(click_x,click_y);

		if(zoomed){
			proxX = (((place->x)*kAppWidth)-(zoomX-50))*(kAppWidth/100);
			proxY = (((1-(place->y))*kAppHeight)-(zoomY-50))*(kAppHeight/100);

		}
		
		else{
			proxX = (place->x)*kAppWidth;
			proxY = (1-place->y)*kAppHeight;
		}
		
	}

	// Right Click to zoom
	if(event.isRight()){
		
		zoomed = true;
		zoomX = event.getX();
		zoomY = event.getY();
		zoomIn(zoom, test->items, zoomX, zoomY);

	}
}

void HW04_collinnc_2App::keyDown(KeyEvent event){
	
	// Press 'u' to zoom out
	if(event.getChar()=='u'){
		zoomed=false;
		for(int i=0;i<3*kTextureSize*kTextureSize; i++)
			zoom[i]=0;
	}

	// Press 'c' to switch between coloring the surface with regions
	// and showing the points
	if(event.getChar()=='c'){
		clicked = !clicked;
		if(clicked)
			colorSurface(dataArray, test);
		else
			showPoints(dataArray, test->items);
	}

	// Press 'p' to show the density of each starbucks,
	// Satisfies goal F
	if(event.getChar()=='p'){
		showDensity = !showDensity;
		colorDensity(data2, test);
	}

	// Show the map by pressing any other key
	else{
		if(!zoomed)
		showMap=!showMap;
	}

}

void HW04_collinnc_2App::update()
{

}

void HW04_collinnc_2App::draw()
{
	// clear out the window with black
	gl::clear();
	if(zoomed)
		gl::draw(*zoomer);
	else{
		gl::draw(*mySurface_);
	}
	if(showDensity)
		gl::draw(*deltaDensity);

	if(showMap)	
		gl::draw(map, getWindowBounds());
	gl::drawSolidCircle(Vec2f(proxX, proxY), 5.0f,0);
	
}

CINDER_APP_BASIC( HW04_collinnc_2App, RendererGl )
