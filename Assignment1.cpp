//Tamika Ramkissoon
//816010368 
//tamika.ramkissoon@my.uwi.edu
//COMP2611: Assignment 1

#include <iostream>
#include <fstream>
#include <limits>
#include <iomanip>
#include "Rating.h"
#include "Product.h"

using namespace std;


// insert your additional function prototypes here (if needed) 
void menu ();
int option1 (Product products[], char filename [100]);
void option2 (Product products[], int numProducts);
void option3 (Product products[], int numProducts);
void option4 (Product products[], int numProducts);
void option5 (Product products[], int numProducts);
void option6 (Product products[], int numProducts);
void option7 ();

// functions
int option1 (Product products[], char filename [100]){
	int	numProducts =  readProducts (products, filename);
	cout << "\nProducts and rating read and stored in memory " <<endl;
	
	sortProducts (products, numProducts);
	cout << "\nData sorted in ascending order of product code" <<endl;
	
	system("pause");
	system("cls");
	return numProducts;	
}

void option2 (Product products[], int numProducts){
	
	string pCode ="";
	
	cout << "\nPlease enter a product code ";
	cin >> pCode;
	printProductRatings (products, numProducts, pCode);
	int found = searchProducts (products, numProducts, pCode);
	if (found != -1){
		int avg = getAvgRating (products[found].top);
		cout << "\nThe average rating is " << setprecision(2) << avg << " ";
		printStars (avg);
	}
	system("pause");
	system("cls");
}


void option3 (Product products[], int numProducts){
	
	string personName ="";
	
	cout << "\nPlease enter a person name ";
	cin >> personName;
	printRatingsByPerson (products, numProducts, personName);
	system("pause");
	system("cls");
}

void option4 (Product products[], int numProducts){
	float stars = 0.0;
	cout << "\nPlease specify the number of stars ";
	cin >> stars;
	printProductRatingsGTE (products, numProducts, stars);
	system("pause");
	system("cls");
}

void option5 (Product products[], int numProducts){
	Rating rating;
	rating.numStars=0;
	rating.personName="";
	string code = "";
	cout << "\nPlease enter the code of the product " ;
	cin>>code;
	addRating (products, numProducts, code, rating);
	system("pause");
	system("cls");
}

void option6 (Product products[], int numProducts){
	Rating rating;
	rating.numStars=0;
	rating.personName="";
	string code = "";
	cout << "\nPlease enter the code of the product " ;
	cin>>code;
	updateRating (products, numProducts, code, rating);
	system("pause");
	system("cls");
}

void option7 (){
	system("cls");
	cout << "MENU QUIT\n";
	cout << "\n\n\n\t\tEND OF COMP2611 ASSIGNMENT 1";
}


void menu (){
	cout <<"\n\n\n";
	cout << "\t1. Read data from Product.txt\n";
	cout << "\t2. Display all the ratings for a product and the average rating\n";
	cout << "\t3. Find the ratings for all products by a certain person\n";
	cout << "\t4. Find the products which have an average rating >= n stars\n";
	cout << "\t5. Add a rating for a product\n";
	cout << "\t6. Update the rating for a product\n";
	cout << "\t7. Quit\n";
	cout << "\n\nPlease enter your menu option ";
}

int main() {

	Product products[1000];
	char filename [100] = "Product.txt";
	int numProducts =0;
	system("cls");
	
	string choice = "1";
	
	// write code to display menu and process options selected by user
	cout << "\n\n\n\n\t\tCOMP2611: Assignment 1\n";
	cout << "\t\tTamika Ramkissoon\n";
	cout << "\t\t816010368\n";
	cout << "\t\ttamika.ramkissoon@my.uwi.edu\n\n";
	
	system("pause");
	system("cls");
	
	cout << "\tSTART OF ASSIGNMENT\n\n";
	
	while (choice != "7"){
		menu();
		cin	>> choice;
		// OPTION 1
		if(choice == "1"){
		numProducts = option1 (products, filename);
		
		//OPTION 2
		} else if (choice == "2"){
			option2 (products, numProducts);
			
		//OPTION 3	
		}else if(choice == "3"){
			option3 (products, numProducts);
		
		//OPTION 4		
		}else if (choice == "4"){
			option4 (products, numProducts);
			
		//OPTION 5	
		}else if (choice == "5"){
			option5 (products, numProducts);
			
		//OPTION 6	
		}else if (choice == "6"){
			option6 (products, numProducts);
		} 
	}
	if (choice == "7"){
		option7();
	}		
	return 0;	
		
}
