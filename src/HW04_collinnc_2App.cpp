#pragma once
#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/Texture.h"
#include "CollinncStarbucks.h"
#include "Resources.h"
#include <iostream>
#include <fstream>

using namespace ci;
using namespace ci::app;
using namespace std;

class HW04_collinnc_2App : public AppBasic {
  public:
	  //In this solution, this method constructs the inital array, 
	  // initializes the collinncStarbucks object and uses the build and getNearest methods.
	void setup();
	void mouseDown( MouseEvent event );	
	void update();
	void draw();

	Surface* mySurface_;
	void colorSurface(uint8_t* pixels, CollinncStarbucks* map);
	// Constructs the inital array of all the data after reading it in
	Entry* makeArray();
	void showPoints(uint8_t* pixels, Item* locs);
	int num_items;
	Entry* entries;

	static const int kAppWidth=700;
	static const int kAppHeight=700;
	static const int kTextureSize=1024;

	uint8_t* dataArray;
	CollinncStarbucks* test;
	
};

void HW04_collinnc_2App::setup()
{
	//gl::color(Color8u(0,0,0));
	
	mySurface_ = new Surface(kTextureSize,kTextureSize,false);
	
	num_items=0;
	
	dataArray = (*mySurface_).getData();

	ifstream in("Starbucks_2006.csv");
	
	entries = makeArray();
	test = new CollinncStarbucks;
	test->num_items = num_items;
	test->build(entries, num_items);
	showPoints(dataArray, test->items);
	//colorSurface(dataArray, test);
	//Use the following line to manipulate the getNearest parameters
	Entry* squirtle = test->getNearest(.7,.6);
	console()<<squirtle->identifier+" "<<squirtle->x<<" "<<squirtle->y<<endl;
}

void  HW04_collinnc_2App::colorSurface(uint8_t* pixels, CollinncStarbucks* map){
	//int offset = 3*(i+j*1024);
	
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
		int x1 = (int)(((locs +i)->data->x)*600);
		int y1 = (int)((1-((locs +i)->data->y))*600);
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
	//for(int i = 0; i<num_items; i++){
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

void HW04_collinnc_2App::mouseDown( MouseEvent event )
{
	console() << "clicked!" <<endl;
	double click_x = (double)event.getX()/kAppWidth;
	double click_y = 1-((double)event.getY()/kAppHeight);
	Entry* place = test->getNearest(click_x,click_y);
	console()<<place->identifier+" "<<place->x<<" "<<place->y<<endl;
}

void HW04_collinnc_2App::update()
{
	//uint8_t* dataArray = (*mySurface_).getData();
	//colorSurface(dataArray, test);
	//Entry* entries = makeArray();
	/*CollinncStarbucks* cat = new CollinncStarbucks;
	cat->num_items = num_items;
	cat->build(entries, num_items);

	colorSurface(dataArray, cat);*/

}

void HW04_collinnc_2App::draw()
{
	// clear out the window with black
	gl::clear();
	gl::draw( *mySurface_ ); 
	
}

CINDER_APP_BASIC( HW04_collinnc_2App, RendererGl )
