#include <iostream>
#include <cstdlib>
#include "Rating.h"

using namespace std;

// Creates a node in the linked list where the data is a rating struct.    
Node * createNode (Rating rating) {
	Node * newNode = NULL;
	
	newNode = new Node;
	newNode->data.personName = rating.personName;
	newNode->data.numStars = rating.numStars;
	newNode->next = NULL;
   
   	return newNode;
}

// Inserts a new rating struct at the top of the linked list and returns the new top.
Node * insertAtHead (Node * top, Rating rating) {
   Node * newNode = NULL;
   
   newNode = createNode (rating);
   newNode->next = top;
   top = newNode;
   
   return top;
} 
  
// Returns the node in the linked list where 'personName' rated the product.
// If 'personName' did not rate the product, return NULL.
Node * contains (Node * top, string personName) {
	Node * curr = NULL;
	
	curr = top;
	while (curr != NULL) {
	    if (curr->data.personName == personName)
	    	return curr;
	    else
	    	 curr = curr->next;
	}
	
   return NULL;      
}

// Returns the amount of nodes in the linked list of ratings.
int size (Node * top) {

	Node * curr;
    int numNodes = 0;
   
    curr = top;
    while (curr != NULL) {
    	numNodes++;;
    	curr = curr->next;
   }
   return numNodes;
}

// Finds and returns the average rating in the linked list of ratings.
int getAvgRating (Node * top) {
	
	Node * curr = NULL;
	int sum =0, numNodes =0; 
	int avg = 0;
	
	if (top == NULL)
		return 0;
	
	curr = top;
	while (curr != NULL){
		sum = sum + curr->data.numStars;
		curr= curr->next;
	}
	numNodes = size (top);
	
	avg = (sum*1.0)/numNodes;
		
   return avg;
}

// Prints the all ratings for a product (person and number of stars given)
void printRatings (Node * top) {
	Node * curr;
    curr = top;
    
    if (top == NULL){
    	cout << " No rating found\n";
	}
	
    while (curr != NULL) {
    	cout << " Person Name: " << curr->data.personName << "\t\t Number of stars given: " << curr->data.numStars <<endl;
    	curr = curr->next;
    }

    cout << "\n";
}

// Utility function to print a certain amount of stars on the monitor	
void printStars (int amount) {
	for (int i =1; i <= amount; i++){
		cout << "* ";
	}
}
