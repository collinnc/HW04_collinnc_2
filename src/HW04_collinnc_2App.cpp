#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "CollinncStarbucks.h"
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

	// Constructs the inital array of all the data after reading it in
	Entry* makeArray();
	int num_items;
};

void HW04_collinnc_2App::setup()
{
	num_items=0;
	
	ifstream in("Starbucks_2006.csv");
	
	Entry* entries = makeArray();
	CollinncStarbucks* test = new CollinncStarbucks;
	test->num_items = num_items;
	test->build(entries, num_items);

	//Use the following line to manipulate the getNearest parameters
	Entry* squirtle = test->getNearest(.05,.05);
	console()<<squirtle->identifier+" "<<squirtle->x<<" "<<squirtle->y<<endl;
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
	in.close();
	return arr;
}

void HW04_collinnc_2App::mouseDown( MouseEvent event )
{
}

void HW04_collinnc_2App::update()
{
}

void HW04_collinnc_2App::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) ); 
}

CINDER_APP_BASIC( HW04_collinnc_2App, RendererGl )
