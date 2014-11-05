//Miles Sanguinetti CS163 October 28th 2014
#include "prog2mdarray.h"

class array //Lists features in prioritized order
{
	public:
		array(int asize);
		~array();
		int insert(int position, const char * product_info);
		int remove(int position);
		int retrieve(int position, char * &product_info) const;
		int display() const;
		int canretrieve();
		mdarray * returnarray();

	private:
		char ** features;
		int arraysize;
};


