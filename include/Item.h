#pragma once
#include "Starbucks.h"
#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/Texture.h"

/*
Items hold an entry, a color, and a population for each starbucks
*/
class Item{
public:
	Entry* data;
	int r,g,b;
	int population;
};
