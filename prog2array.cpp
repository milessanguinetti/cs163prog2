//Miles Sanguinetti CS163 October 28th 2014
#include "prog2array.h"
#include <cstring>
#include <iostream>
using namespace std;

array::array(int asize)
{ //constructor
	arraysize = asize;
	features = new char *[asize];
	for(int i = 0; i < arraysize; ++i)
		features[i] = NULL;
}

array::~array()
{ //destructor
	for(int i = 0; i < arraysize; ++i)
		delete features[i];
	arraysize = 0;
}

int array::insert(int position, const char * product_info)
{ //insert node by position and passed char array
	if(!product_info || position >= arraysize)
		return 0;
	features[position] = new char[strlen(product_info)];
	strcpy(features[position], product_info);
	return 1;
}

int array::remove(int position)
{ //remove a node based on position
	if(!features[position])
		return 0; //no sense in removing nothing
	features[position] = NULL;
	return 1;
}

int array::retrieve(int position, char * &product_info) const
{ //copy product info from array based on position
	if(!features[position])
		return 0; //that's not gonna work
	product_info = new char[strlen(features[position])];
	strcpy(product_info, features[position]);
	return 1;
}

int array::display() const
{ //simple display function
	if(!features)
		return 0;
	for(int i = 0; i < arraysize; ++i)
		if(features[i])
			cout << "#" << i << ": " << features[i] << endl;
	return 1;
}

mdarray * array::returnarray()
{ //we copy and return the array and its size
  //so that it can be used by the stores class in
  //crossreferencing
	mdarray * t = new mdarray; //allocate mdarray
	t -> passedarray = new char * [arraysize]; //allocate its chars
	for(int i = 0; i < arraysize; ++i)
	{
		if(features[i])
		{
			t -> passedarray[i] = new char[strlen(features[i]) + 1];
			strcpy(t -> passedarray[i], features[i]); //copy chars
		}
	}
	t -> passedsize = arraysize - 1; //so this can be used as an index
	return t; //return the mdarray
}
