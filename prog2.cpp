//Miles Sanguinetti CS163 October 28th 2014
#include "prog2.h"
#include <iostream>
#include <cstring>
using namespace std;

//Constructor and destructor for class
stores::stores()
{
	rear = NULL;
	head = NULL;
	top_index = 0;
}

stores::~stores()
{

	if(rear)
	{
		queuenode * temp = rear -> next;
		rear -> next = NULL; //turn CLL into LLL
		while(temp) //deallocate queue
		{
			node * stemp = temp -> nextfeature -> next;
			temp -> nextfeature -> next = NULL;
			while(stemp) //deallocate subqueue
			{
				node * snext = stemp -> next;
				delete stemp;
				stemp = snext;
			}
			queuenode * next = temp -> next;
			delete temp; //deallocate as an LLL
			temp = next;
		}
	}
	
	while(head) //deallocate the stack
	{
		for(int i = 0; i < 5; ++i)
		{
			if(head -> features[i])
				delete head -> features[i];
		}
		stacknode * temp = head;
		head = head -> next;
		delete temp;
	}

	top_index = 0; //deallocate top index
}

//Stack/reject pile for stores
int stores::push(char const * store_info) //Add to top of stack
{
	if(!head)
	{
		stacknode * temp = new stacknode;
		(temp -> features) = new char*[5];
		temp -> features[0] = new char[strlen(store_info) + 1];
		strcpy(temp -> features[0], store_info);
		head = temp;
		temp -> next = NULL;
		top_index = 1; //not 0 since there's already an entry
	}
	else
	{
		if(top_index == 4)
		{
			stacknode * temp = new stacknode;
			temp -> features = new char*[5];
			temp -> features[0] = new char[strlen(
			store_info) + 1];
			strcpy(temp -> features[0], store_info);
			temp -> next = head;
			head = temp;
			top_index = 1; //same deal
		}
		else
		{
			head -> features[top_index] = new char
			[strlen(store_info) + 1];
			strcpy(head -> features[top_index],
			store_info);
			++top_index; //increment top index
		}
	}
	return 1;
}

int stores::pop() //Remove from top of stack
{
	if(!head || !head -> features[top_index - 1]) //can't remove
						      //nothing.
		return 0;
	head -> features[top_index - 1] == NULL;
	delete head -> features[top_index - 1];
	--top_index; //delete entry and reduce top index
	if(top_index == -1) //if there are no entries,
	{                   //delete the node itself
		stacknode * temp = head;
		if(head -> next) //if there are more nodes
		{		 //go to the top of the next one
			top_index = 4;
			head = head -> next;
		}
		delete temp;
	}
	return 1;
}

int stores::peek() const
{
	if(!head || !head -> features[top_index])
		return 0; //can't peek at nothing
	cout << head -> features[top_index] << endl;
	return 1;	
}

int stores::stackdisplay() const
{
	if(!head || !head -> features[top_index -1])
		return 0;
	stacknode * current = head;
	int i = top_index - 1; //don't want to augment index itself
	while(current) //while there are nodes
	{
		for(i; i >= 0; --i)
			if(current -> features[i])
				cout << current -> features[i] << endl;
		i = 4; //go to the top of the next node
		current = current -> next;
	}
	return 1;
}

//Queue/list of stores by availability
int stores::enqueue(char const * store_info, char const * product_info)
{
	if(!store_info || !product_info)
		return 0;
	if(!rear) //No store queue; no product queue;
	{ 
		queuenode * temp = new queuenode;
		temp -> storename = new char[strlen(store_info)];
		strcpy(temp -> storename, store_info);
		temp -> next = temp; //CLL
		rear = temp;
		temp -> nextfeature = new node;
		temp -> nextfeature -> feature = new
		char[strlen(product_info)];
		strcpy(temp -> nextfeature -> feature, product_info);
		temp -> nextfeature -> next = temp -> nextfeature;
	}
	else
	{
		bool extantstore = false;
		queuenode * current = rear;
		do{
			if(strcmp(current -> storename, store_info
			) == 0) //If there's already a qnode for that store

			{ 		
				extantstore = true; 
				node * temp = new node;
				temp -> feature = new
				char[strlen(product_info)];
				strcpy(temp -> feature, product_info);
				if(current -> nextfeature)
				{
					temp -> next = current ->
					nextfeature -> next;
					current -> nextfeature -> next = temp;
				}
				else
					temp -> next = temp;
				current -> nextfeature = temp;
				break; //No sense in continuing if we found
			}	       //the store node already.
			current = current -> next;
		}while(current != rear);
		if(extantstore == false) //There's no existing store node
		{			 //by that name
			queuenode * temp = new queuenode;
			temp -> next = rear -> next;
			rear -> next = temp;
			rear = temp;
			temp -> storename = new char[strlen(store_info)];
			strcpy(temp -> storename, store_info);
			temp -> nextfeature = new node;
			temp -> nextfeature -> feature = new\
			char[strlen(store_info)];
			strcpy(temp -> nextfeature -> feature, product_info);
			temp -> nextfeature -> next = temp -> nextfeature;
		}
	}
	return 1;
}

int stores::dequeue(char * store_info, char * product_info)
{
	if(!store_info || !product_info || ! rear)
		return 0; //can't dequeue nothing
	queuenode * current = rear;
	do{ //we compare the next node rather than the current
	    //in the case that we need to delete and relink the list
		if(strcmp(current -> next -> storename, store_info
		) == 0) //A qnode for that store exists
		{
			/*node * subtemp = current -> nextfeature -> next;
			strcpy(product_info, subtemp -> feature);
			//Copy first product detail into the
			//passed product info variable
			current -> nextfeature -> next = subtemp -> next;
			//next in line goes to front
			delete subtemp; //removed from queue*/
			node * subcurrent = current -> nextfeature;
			do{ //search for a subnode w/ product name
				if(strcmp(subcurrent -> next -> feature
				, product_info) == 0)
				{//if found, delete it.
					if(current -> nextfeature ==
					subcurrent -> next) //need new 'rear'
						current -> nextfeature
						== subcurrent;
					node * subtemp = subcurrent -> next;
					subcurrent -> next = subtemp -> next;
					delete subtemp;
					break; //no need to continue
				}
			}while(subcurrent != current -> nextfeature);

			if(!current -> next -> nextfeature)
			{ //if the next node's subqueue is empty
			  //we delete it from the main queue
				if(current -> next == rear)
				{//need a new rear if we delete it
					current -> next = rear -> next;
					delete rear;
					rear = current;
				}
				else
				{//all other cases
					queuenode * temp = current -> next;
					current -> next = temp -> next;
					delete temp;
				}
			}		         
			return 1; //No sense in continuing if we found
		}		  //the store node already.
		current = current -> next;
	}while(current != rear);
	return 0; //Failure due to nonexistent store
}

int stores::queuedisplay() const
{
	if(!rear)
		return 0; //can't display an empty list.
	queuenode * current = rear -> next;
	do{
		cout << endl << current -> storename << endl;
		node * subcurrent = current -> nextfeature -> next;
		do{
			cout << "\t" << subcurrent -> feature << endl;
			subcurrent = subcurrent -> next;
		}while(subcurrent != current -> nextfeature -> next);
		current = current -> next;
	}while(current != rear -> next);
	return 1; //Success
}

/*int stores::crossreference(char const * product_info)
{ //compare queue products with array products
  //and push storenames with nonlisted items into the stack
	if(!rear || !product_info)
		return 0;
	queuenode * current = rear -> next;
	do{ //for each node in the queue
		node * subcurrent = current -> nextfeature -> next;
		do{ //for each node in the nested subqueue
			if(strcmp(subcurrent -> feature, product_info) != 0)
			{ //if the subnode's product matches the passed one
				if(!head)
					push(current -> storename);
				else if(!head -> features[top_index])
					push(current -> storename);
				//No need to worry about duplicates
				//if head or its array are empty
				else
				{
					if(strcmp(current -> storename, head ->\
					features[top_index]) != 0) 
					//We push onto the stack if the
					//feature isn't in our array and the
					//store name isn't already in the
					//stack (avoids repeats)
						push(current -> storename);
				}
				node * subtemp = subcurrent;
				dequeue(current -> storename, subcurrent\
				-> feature); //remove from queue without
				subcurrent = subtemp; //disrupting traversal
			}
			else
				subcurrent = subcurrent -> next;
		}while(subcurrent != current -> nextfeature -> next);
		current = current -> next;
	}while(current != rear -> next);
	return 1;
}*/

/*int stores::crossreference(mdarray * ftarray)
{ we pass the original feature array and its size
  //then compare queuenodes and nodes to the features.
	if(!rear || !ftarray)
		return 0;
	queuenode * current = rear;
	bool noitems;
	do{//for each queuenode in the queue 
		noitems = true; //to remove from queue/add to stack
				     //if no items are found
		node * subcurrent = current -> next -> nextfeature;
		bool nomatch;
		do{//for each node in the nested subqueue
			nomatch = true; //to remove from subqueue
					     //if no matches are found
			for(int i = ftarray -> passedsize; i >= 0; --i)
			{
				if(ftarray -> passedarray[i])
				{ //if this doesn't exist, it will cause
				  //a seg fault.
					if(strcmp(ftarray -> passedarray[i],
					subcurrent -> next -> feature) == 0)
					{//if there's a match in the array
						noitems = false;
						nomatch = false;
						break;
					}//noitems/match get true, we test the
				 	//next node and we break the for loop.
				}
			}
			if(nomatch == true)
			{//in the absence of a match, we delete the node
				if(subcurrent -> next == subcurrent)
				{
					delete current -> next -> nextfeature;
					current -> next -> nextfeature = NULL;
					subcurrent = NULL;
				}
				else
				{
					if(subcurrent -> next == current -> next\
					-> nextfeature)
						current -> next -> nextfeature\
						== subcurrent;
					node * temp = subcurrent -> next;
					subcurrent -> next = temp -> next;
					delete temp;
					temp = NULL;
				}
			}
			else
				subcurrent = subcurrent -> next;	
		}while(subcurrent != current -> next -> nextfeature
		&& subcurrent);
		 //don't exit if we just deleted a node and it wasn't
		 //the only node in the queue
		if(noitems == true)
		{ //in the absence of any found items, we delete the node
			if(current -> next == current)
			{
				delete current;
				current = NULL;
				rear = NULL;
			}
			else
			{
			//replace the rear if we need to.
				if(current -> next == rear)
					rear = current;
				queuenode * temp = current -> next;
				push(temp -> storename); //add to stack.
				current -> next = temp -> next;
				delete temp;
				temp = NULL;
			}	
		}
		else //traverse as normal if an item is found.
			current = current -> next;
	}while(current != rear && current);
	for(int i = 0; i <= ftarray -> passedsize; ++i)
		delete ftarray -> passedarray[i];
	delete ftarray; //deallocate memory.
	return 1; //success
}*/

int stores::crossreference(mdarray * ftarray)
{
	if(!ftarray || !rear)
		return 0;
	bool noitems; //Checking a store for a case in which
		      //none of its products are on the list
	queuenode * current = rear -> next;
	rear -> next = NULL;
	while(current)
	{ //for each node in the queue
		noitems = true; //set this to true for each node
		node * subcurrent = current -> nextfeature -> next;
		current -> nextfeature -> next = NULL;
		while(subcurrent)
		{ //for each subnode in a node's subqueue
			for(int i = ftarray -> passedsize; i >= 0; --i)
			{
				if(ftarray -> passedarray[i])
				{ //if this doesn't exist, it will cause
			  	//a seg fault.
					if(strcmp(ftarray -> passedarray[i],
					subcurrent -> feature) == 0)
					{//if there's a match in the array
						noitems = false;
						break;
					}
				}//noitems/match get true, we test the
			 	//next node and we break the for loop.
			}
			subcurrent = subcurrent -> next;
		}
		if(noitems == true) //if there are no matches, push it
			push(current -> storename); //onto the stack
		current = current -> next;
	}
	return 1; //success
}
