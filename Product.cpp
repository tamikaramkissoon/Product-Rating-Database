#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include <iomanip>
#include "Rating.h"
#include "Product.h"
 
using namespace std;

// Reads the product data from 'filename' and stores in the 'products' array.
// Return the amount of products read.
int readProducts (Product products[], char filename [100]) {
	int numProducts =0;
	string Codes = "";
	string Names = "", space ="";
	Rating rating[1000];
	int numRating =0;
	string personname="";
	int stars =0;
	ifstream input;
	input.open(filename);
	
	for (int i =0; i < 1000; i++){
		rating[i].personName = "";
		rating[i].numStars = 0;
	}
	
	// if statement to check whether the input file was successfully opened.
	if (!input.is_open())
	{
		cout << "There was an error opening the data file!  Operation aborting!!..." << endl;
		exit(1);
	}
	else 
		cout <<  "Product.txt file sucessfully opened...  reading data from file" << endl;
	
	input >> Codes >> Names;
	while (Codes != "END" && numProducts < 1000 ){ 		
		products[numProducts].code = Codes;
		products[numProducts].name = Names;
				
		input >> personname >> stars;
		numRating =0;	
		while(personname != "###" && numRating < 1000){	
			rating[numRating].personName = personname;
			rating[numRating].numStars = stars;	
			numRating++;
			input.clear();
			input >> personname >> stars;
		}
			
		Node * top = NULL;
		numRating = numRating-1;
		for (int i = numRating; i >= 0; i--){
			top = insertAtHead (top, rating[i]);		
		}
		products[numProducts].top = top;
		  		
 		input.clear();
		numProducts++;
		input >> Codes >> Names;
		
	}
	input.close();
	return numProducts;
}


// Sort the products in the 'products' array in ascending order by code
void sortProducts (Product products[], int numProducts) {
	
	string tempCode = "";
	string tempName = "";
	Node * tempTop = NULL;
	
	for (int i =0; i < numProducts; i++){
		for (int j = i+1; j < numProducts; j++){
			if (products[i].code > products[j].code){
				tempCode = products[i].code;
				tempName = products[i].name;
				tempTop = products[i].top;
				
				products[i].code = products[j].code;
				products[i].name = products[j].name;
				products[i].top = products[j].top;
				
				products[j].code = tempCode;
				products[j].name = tempName;
				products[j].top = tempTop;
			}
		}
	}
	return;
}


// Searches the products in the 'products' array for 'key'.
// Binary search must be used.
int searchProducts (Product products[], int numProducts, string key) {
	
int low =0;
int high = numProducts - 1;
int mid = 0;

	while (low <= high){	
		mid = (low + high) /2; 	
	 	if (products[mid].code == key)
	 		return mid;		
		else 
			if (products[mid].code > key)
				high = mid - 1;		
		else
			low = mid + 1;	
	}
	return -1;
}


// Prints all the ratings for the product with the given 'code'.
void printProductRatings (Product products[], int numProducts, string code) {
	
	int found = searchProducts (products, numProducts, code);
	if (found != -1){
		cout << "The list of rating for product " << code << " : "<<endl;
		printRatings(products[found].top);
	}else {
		cout << "No Product was found for the given code: " << code << endl;
	}	
	return;
}


void printRatingsbyPersonHelper (Node * top, string personName) {
	Node * curr;
    curr = top;
    
    if (top == NULL){
    	cout << "List is empty\n";
	}
    while (curr != NULL) {
    	if (curr->data.personName == personName){
    		cout  << "\t\t Number of stars given: " << curr->data.numStars <<endl;
    	}
			curr = curr->next;	
    }
    cout << "\n";
}

// Prints all the ratings made by 'personName'.	
void printRatingsByPerson (Product product[], int numProducts, string personName) {
	
	int numRating=0;
	Node * found = NULL;
	
	for (int i=0; i < numProducts; i++){
		found =	contains (product[i].top, personName);
		if (found != NULL){
			cout << product[i].code << "\t" << product[i].name ;
			printRatingsbyPersonHelper (product[i].top, personName);
			numRating++;
		}	
	}
	if (numRating == 0){
		cout << personName << " did not rate any of the products" << endl;
	}
	return;
}	


// Prints product data for all products where the average rating is >= 'n'.
void printProductRatingsGTE (Product product[], int numProducts, int n) {
	
	int avg =0;
	int num=0;
	for ( int i =0; i < numProducts; i++){
		avg = getAvgRating (product[i].top);
		if (avg >= n){
			cout << product[i].code << "\t" << product[i].name<< " The average rating is " << setprecision(2) << avg << endl <<endl;
			num++;
		}
	}
	if (num == 0){
		cout << "No product have a rating that is greater than or equal to " << n << endl << endl;
	}
	return;
}
	

// Adds a new rating for the product with the given 'code'.
void addRating (Product products[], int numProducts, string code, Rating rating) {
	int found = searchProducts (products, numProducts, code);
	Node* rated = NULL;
	
	if (found == -1){
		cout << "The products with code " << code << " was not found" << endl;
	}else {
		cout << "PLease enter the name of the person who rated the product ";
		cin >> rating.personName;
		cout << "Please enter the amount of star the person gave the product ";
		cin >> rating.numStars;
		rated = contains (products[found].top, rating.personName);
		if (rated == NULL){
			products[found].top = insertAtHead (products[found].top, rating);	
		}else {
			cout << rating.personName << " cannot rate the product twice " << endl;
		}
	}
	return;
}


// Updates a rating of the product with the given 'code'.
void updateRating (Product products[], int numProducts, string code, Rating rating) {
	int found = searchProducts (products, numProducts, code);
	Node*rated=products[0].top;
	Node*curr=NULL;
	
	if (found != -1){
		cout << "PLease enter the name of the person who rated the product ";
		cin >> rating.personName;
		cout << "Please enter the amount of star the person gave the product ";
		cin >> rating.numStars;
		rated = contains (products[found].top, rating.personName);
		if (rated != NULL){
			curr = products[found].top;
			while (curr != NULL){
				if (curr->data.personName == rating.personName){
					curr->data.numStars = rating.numStars;
					break;
				}
				curr=curr->next;
			}
		}	
	}
		if(found == -1 ){
			cout << "\nERROR Unable to update rating, Product not found" <<endl;
		}
		
		if(rated == NULL){
			cout << "\nERROR Unable to update rating, the specified person was not found" <<endl;
		}	
	return;
}







