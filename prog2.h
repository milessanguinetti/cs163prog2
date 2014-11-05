//Miles Sanguinetti
//This is a program for my CS163 class; it helps you make decisions
//about purchasing a car.
#include "prog2mdarray.h"

struct node //A common node struct
{
	char * feature;
	node * next;
};

struct stacknode
{
	char ** features;
	stacknode * next;
};

struct queuenode
{
	char * storename;
	node * nextfeature;
	queuenode * next;
};

class stores //Consolidated list of stores and reject pile
{
	public:
		//Constructor and destructor for class
		stores();
		~stores();
		//Stack/reject pile for stores
		int push(char const * store_info);
		int pop();
		int peek() const;
		int stackdisplay() const;
		//Queue/list of stores by availability
		int enqueue(char const * store_info, char const * product_info);
		int dequeue(char * store_info, char * product_info);
		int queuedisplay() const;
		int crossreference(mdarray * ftarray);

	private:
		stacknode * head;   //For the stack
		int top_index; //This keeps track of how many
			       //entries we have in the current array
		queuenode * rear; //For the queue

};

