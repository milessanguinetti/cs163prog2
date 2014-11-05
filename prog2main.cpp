//Miles Sanguinetti CS163 October 28th, 2014
#include "prog2.h"
#include "prog2array.h"
#include <iostream>
#include <cstring>
using namespace std;

const int SIZE = 100;

int main()
{
	int exit = 0; //so we know when to stop
	stores storesvar; //make a queue/stack object
	char yesno;
	char response1[SIZE]; 
	char response2[SIZE]; //two character responses
	int response3; //and one for an int

	cout << "How many features would you like to look for?" << endl
	<< "Enter a response above 0 and as '1' rather than 'one'" << endl;
	cin >> response3;
	cin.ignore(SIZE, '\n');
	
	array features(response3); //make our array object at input size

	do{ //A loop to add as many features as requested.
		cout << "Would you like to enter a new feature? (y/n)" << endl;
		cin >> yesno;
		cin.ignore(SIZE, '\n');
		if(yesno == 'y')
		{
			int i = 0;
			while(i == 0)
			{
				cout << "Which position would you like"
				<<  " the feature to go in?" << endl <<
				"Enter an integer for its priority" << endl
				<< "0 for the first position, for instance"
				<< endl; //Take in position
				cin >> response3;
				cin.ignore(SIZE, '\n');
				cout << "Enter a feature name (case"
				<< " sensitive)" << endl; //Take in its name
				cin.get(response1, SIZE, '\n');
				cin.ignore(SIZE, '\n');
				i = features.insert(response3, response1);
				if(i == 0)
					cout << "Responses were invalid"
					<< endl; //Friendly error message
			}
		}
		else
			exit = 1;

	}while(exit == 0);
	
	exit = 0; //reset to unexited state

	features.display(); //see what we added

	do{ //A loop to delete as many features as are requested.
		cout << "Would you like to delete any features? (y/n)" << endl;
		cin >> yesno;
		cin.ignore(SIZE, '\n');
		if(yesno == 'y')
		{
			int i = 0;
			while(i == 0)
			{
				cout << "Which position would you like"
				<< " to delete?" << endl <<\
				"Enter an integer." << endl;
				cin >> response3;
				cin.ignore(SIZE, '\n');
				i = features.remove(response3);
				if(i == 0)
					cout << "Feature does not exist"
					<< endl;
			}
		}
		else
			exit = 1;

	}while(exit == 0);

	exit = 0; //reset

	features.display(); //see what we removed

	cout << "Now we add store information." << endl;

	do{ //A loop to add as many stores as are requested
		cout << "Would you like to add a new store?" << endl <<
		"or add a product to an existing store? (y/n)" << endl;
		cin >> yesno;
		cin.ignore(SIZE, '\n');
		if(yesno == 'y')
		{
			int i = 0;
			while(i == 0)
			{
				cout << "What is the store's name?" << endl; 
				cin.get(response1, SIZE, '\n');
				cin.ignore(SIZE, '\n');
				cout << "What product do they carry?" << endl;
				cin.get(response2, SIZE, '\n');
				cin.ignore(SIZE, '\n');
				i = storesvar.enqueue(response1, response2);
				if(i == 0)
					cout << "Input invalid." << endl;
			}
		}
		else
			exit = 1;
	}while(exit == 0);

	cout << "Stores added:" << endl;
	storesvar.queuedisplay(); //displaying added stores

	cout << "Press enter to cross-reference store and product info." << endl;
	cin.get(response1, SIZE, '\n'); //Just helps spread out the data
	cin.ignore(SIZE, '\n');

	cout << "Cross-referencing store info with features desired." << endl;
	

	storesvar.crossreference(features.returnarray());
	//Run queue through array values, push onto stack

	cout << "These stores had no items that"
	<< " met your specifications." << endl;
	storesvar.stackdisplay(); //We display the stack

	cout << "Removing first store from rejects." << endl;
	storesvar.pop();
	cout << "Displaying remaining items." << endl;
	storesvar.stackdisplay(); //These simply test my pop function

	return 0;
}
