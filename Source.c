#define _CRT_SECURE_NO_WARNINGS
#define NUMITEM 10
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

struct item {

	int id;
	char itemName[30];
	float price;
	int amount;

};

//global variable

float total_cash = 0;

struct item stock[NUMITEM] = { { 1, "Dry Food", 150.00, 0 },{ 2, "Treats", 240.00, 0 },{ 3, "Plush Toys", 82.50, 0 },{ 4, "Litter Boxes", 35.00, 0 },
{ 5, "Collars", 99.00,0 },{ 6, "Flea Shampoos", 185.00, 0 },{ 7, "Pet Mat", 299.00, 0 },{ 8, "Cuddler Beds", 755.00, 0 },
{ 9, "Treatments", 450.00, 0 },{ 10, "Scratchers", 599.00, 0 } };

//function prototype
void read_File();
void update_File();
int integerScan(char x[50]);
int ID_check();
int to_Stock(int itemID);
void purchasing_Stock();
void adding_Stock();
void checking_Stock();
void modeSelect();
void main();

//function
void read_File() {

	FILE *openFile;
	int i, id;
	char temp[50];

	openFile = fopen("Stock.txt", "r");
	if (openFile == NULL) {
		printf("File not successfully opened");
		exit(1);
	}
	while ((fscanf(openFile, "%s", &temp)) != EOF) { 		

			id = 0;
			while ((fscanf(openFile, "%d", &stock[id].amount)) != '\n') { //receive value after hit \n
				id++;
				if (id == 10) {
					while ((fscanf(openFile, "%f", &total_cash)) != '.') {
						return; //finish function after receive total_cash data
					}

				}
			}
	}
	fclose(openFile);
}

void update_File() {

	FILE *outFile;

	outFile = fopen("Stock.txt", "w");
	if (update_File == NULL) {
		printf("File not successfully opened");
		exit(1);
	}
	fprintf(outFile, "%.2f\n", total_cash); //Token for reading file next time
	for (int i = 0; i < 10; i++) {

		fprintf(outFile, "%d\n", stock[i].amount);
	}
	fprintf(outFile, "%.2fBaht", total_cash);
	fclose(outFile);
}

int integerScan(char x[50]) {

	char number;
	int test;

	for (int i = 0; i < strlen(x); i++) {
		number = x[i];	//check each character
		test = isdigit(number); // if not a digit means !test(flase)
		if (!test)
			return 0;
	}
	return 1;
}

int ID_check() {

	char input[10];
	int checkInt, num;

	while (1) {

		printf("Enter item ID from the stock : ");
		scanf("%s", input);
		checkInt = integerScan(input);

		if (!checkInt) { // check user input

			printf("\nInvalid input (Must be a postive integer) \n");
			continue;
		}
		num = atoi(input); //if user input is an integer then convert to integer (from string)

		if (num <= 0 || num >= 11) {

			printf("\nInvalid ID(Must be \'1-10\')\n");
			continue;
		}
		return num;
	}
}

int to_Stock(int itemID) {

	char input[10];
	int checkInt;
	int amount;

	while (1) {

		printf("\nAmount : ");
		scanf("%s", input);
		checkInt = integerScan(input);

		if (!checkInt) { // check user input

			printf("Invalid input (Must be a positive integer)");
			continue;
		}
		amount = atoi(input); //if user input is an integer then convert to integer (from string)
		return amount;
	}
}

void purchasing_Stock() { //press (B)

	int id, number;

	id = ID_check();
	printf("\n%s was selected to export from the stock", stock[id - 1].itemName); //check the name of stock ID
	printf("\nCurrently in stock : ->%d<-\n", stock[id - 1].amount);

	number = to_Stock(id); //do the function that relate to the item ID

	if (stock[id - 1].amount < number) {

		printf("Supply not enough for purchase.\n");
	}
	else if (stock[id - 1].amount >= number) {
		stock[id - 1].amount -= number; //send data to decrease from global variable
		printf("Total cost : %.2f\n", stock[id - 1].price * number); //calculate total price
		total_cash += (stock[id - 1].price * number);
	}

	return;
}

void adding_Stock() { //press (S)

	int id, number;

	while (1) {

		id = ID_check();
		printf("\n%s was selected to add to the stock\n", stock[id - 1].itemName);

		number = to_Stock(id);
		stock[id - 1].amount += number; //increase stock in global variable
		printf("\nAdded %s for %d ea to stock.\n\n", stock[id - 1].itemName, number);
		break;
	}
	return;
}

void checking_Stock() { //press (C)

	int i;

	printf("\n\n\t-------  Items  -------\n");

	for (i = 0; i < NUMITEM; i++) {
		//print all data items
		printf("\n    ID %02d %s", (stock[i].id), (stock[i].itemName)); 
		printf("\t(Price %6.2f Baht) : %5d", stock[i].price, stock[i].amount);

	}

	printf("\n\n  --------------------------------------------\n");
	return;
}

void reset_Stock() {

	int i;

	for (i = 0; i <= 9; i++) {

		stock[i].amount = 0;
		total_cash = 0;
	}
	printf("\nAll data have been reset!\n");
}

void modeSelect() {

	char mode[50];
	int a, checkInt;


	while (1) {

		printf("\nPress \"1\" for export items\nPress \"2\" for import items\nPress \"3\" to check a stock\nPress \"4\" to reset all data\n");
		printf("Press \"5\" to quit a program\n");
		printf("\nSelect mode : ");
		scanf("%s", &mode);
		checkInt = integerScan(mode);
		if (!checkInt) {

			printf("\nMust be integer only!\n");
			continue;
		}
		a = atoi(mode);

		if (a == 1)
			purchasing_Stock();
		else if (a == 2)
			adding_Stock();
		else if (a == 3)
			checking_Stock();
		else if (a == 4)
			reset_Stock();
		else if (a == 5)
			return;
		else {
			printf("\nMust be number 1, 2, 3 or 4 only\n");
			continue; //user input an integer but not in a choice
		}
	}
}

void main() {

	printf("\n-----Welcome to SE-Cat Healthy Shop-----\n");
	read_File();
	modeSelect();	
	update_File();
	printf("\n\nTotal cash : %10.2f Baht", total_cash);
	printf("\n\nEnd of the program");
	printf("\n\n--------------------------------------------\n\n");

	system("pause");
}
