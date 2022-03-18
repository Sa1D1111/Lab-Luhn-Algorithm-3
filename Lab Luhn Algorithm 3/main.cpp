#include <iostream>
#include<ctime>
#include <iomanip>
//#include <bits/stdc++.h>
//#include <cstdlib>			   
using namespace std;

// Global Constants
//Enum for cards provided
enum CrdCard { AmericanExpress, Visa, MasterCard, Discover, ALL };
//            0                1     2           3         4
//Global Constants
//Function Prototypes
char rndDgit();           //Randomly generates digit characters
void prpLuhn(char[], int); //Prepares the Luhn Sequence
int  cnvrt(char);         //Convert 1 digit char to integer
char cnvrt(int);          //Convert 1 digit integer to a char
void output(char[], int);  //Output the sequence as integers
//Function you are to create
void Luhn(char[], int);    //Calculate and append the Luhn Digit
// added functions
void genCC(CrdCard, char[]);
void flipDig(char[]);
bool validCC(char[]);
void pCard(char[]);
void printCType(char[], CrdCard);
void transpose(char[]);

void switchDig(char[]);

//generate card numbers
int main(int argc, char** argv)
{
	//system("Color 0D");
	// set random number seed
	srand(static_cast<unsigned int>(time(0)));
	char card[17];
	int loops = 10000;

	CrdCard cardCo = ALL;
	genCC(cardCo, card);
	//generate until a final valid card output
	while (!validCC(card)) {
		genCC(cardCo, card);
		cout << " Generate\n";
	}
	cout << " Card validity : ";
	if (validCC(card)) {
		cout << "Valid" << endl;
	}
	cout << " Card #                          : ";
	pCard(card);
	cout << endl;
	transpose(card); // not transposing. its flipping 2 numbers though
	cout << " Card # after flipping 2 numbers : ";
	pCard(card);
	cout << endl;
	cout << " Credit Card Company : ";
	printCType(card, cardCo);
	int valid = 0, invalid = 0;
	for (int i = 0; i < loops; i++) {
		//cout << "card before flipping: " << card << endl;
		//flipDig(card);
		transpose(card);
		if (validCC(card)) {
			//cout << "Card after transpose " << card << endl;
			valid++;
		}
		else {
			invalid++;
		}
		// Deallocate memory
		//delete []card;
	}
	// Stats
	cout << "\n\n Stats " << endl;
	cout << setfill('*') << setw(140);
	cout << "\n\n Total cards generated: " << loops << endl;
	cout << " Valid cards : " << valid << endl;
	cout << " Invalid cards : " << invalid << endl;
	float perc = static_cast<float>(valid) / loops * 100;
	cout << "\n Percentage of valid : " << perc << " %" << endl;
	float perc2 = static_cast<float>(invalid) / loops * 100;
	cout << " Percentage of Invalid : " << perc2 << " %" << endl;

	system("pause>0");
	return 0;
}

//void transpose(int cc[])
//{
//	int i;
//	cc[i] = (rand() % (6 - 3 + 1)) + 3 + '0';
//
//	for (int i = 0; i < 16; i++)
//		for (int j = i + 1; j < 16; j++)
//			swap(cc[i], cc[j]);
//}

void switchDig(char cc[]) {
	//get length
	string num = cc;
	int length = num.length();
	//get random indexes
	int i = 1 + rand() % (length - 1);
	int j;
	do 
	{
		j = 1 + rand() % (length - 1);
	}
	while (j == i);
	//swap two numbers
	/*char num2 = cc[i];
	cc[i] = cc[j];
	cc[j] = num2;*/

	swap(cc[i], cc[j]);

}


void transpose(char cc[]) {
	    //get length
	    string num = cc;
	    int length = num.length();
	    //get random indexes
	    int index = 1 + rand()% (length-1);
		int index2;
		index2 = index + 1;

	   /* do{
	       index2 = 1 + rand()% (length-1); 
	    }while(index2==index);*/

	   //swap two indexes

		char num2 = cc[index];
		cc[index] = cc[index2];
		cc[index2] = num2;
	}




void genCC(CrdCard card, char cc[]) {
	int cLength, iD;
	//set first digit based on card type
	if (card == AmericanExpress) {
		cc[0] = '3'; // AMEX cards starts with 3
		cLength = 15;
	}
	else if (card == Visa) {
		cc[0] = '4'; // Visa cards starts with 4
		cLength = 16;
	}
	else if (card == MasterCard) {
		cc[0] = '5'; // Mastercards start with 5
		cLength = 16;
	}
	else if (card == Discover) {
		cc[0] = '6'; // Discover cards starts with 6
		cLength = 16;
	}
	else if (card == ALL) {
		cc[0] = (rand() % (6 - 3 + 1)) + 3 + '0'; // generate random first digit 3-6
		cLength = 16;
	}
	for (iD = 1; iD < cLength; iD++) {
		//generate random # 0-9-->store in card
		int number = rand() % 10;
		cc[iD] = number + '0';
	}
	cc[iD] = '\0'; // \0 = NULL ASCII
}

//print card number function
void pCard(char cc[]) {
	int j = 0;
	while (cc[j] != '\0') {
		cout << cc[j] << "";
		j++;
	}
}

// print card type function
void printCType(char cc[], CrdCard card)
{
	if (card == AmericanExpress) {
		cout << "American Express" << endl;
	}
	else if (card == Visa) {
		cout << "Visa" << endl;
	}
	else if (card == MasterCard) {
		cout << "Mastercard" << endl;
	}
	else if (card == Discover) {
		cout << "Discover" << endl;
	}
	else if (card == ALL) {
		cout << "ALL" << endl;
	}
}

//Flip digit function
void flipDig(char cc[])
{
	int flipD = rand() % 10, iD = rand() % 15;
	cc[iD] = flipD + '0';
}

// function for CC validity
bool validCC(char cc[])
{
	int cLength = 16;
	int sum = 0;
	int sD = false; // second digit
	for (int i = cLength - 1; i >= 0; i--)
	{
		int num = cc[i] - 'a';
		if (sD == true) {
			num = (num * 2);
		}
		sum += num % 10;
		sum += num / 10;
		sD = !sD; // loops out and returns when done
	}
	return (sum % 10 == 0);
}


void Luhn(char ccc[], int n) {

	cout << "You have to make it work" << endl;
	cout << "Here is the last digit for the prpLuhn output." << endl;
	int sum = 0;

//int sD = false;
//for each digit
	for (int i = n - 3; i >= 0; i--) {
		//converting char to int
		int num = cnvrt(ccc[i]);

		//if it is a second digit then double it
		if (i % 2 != 0)
		{
			num = num * 2;
		}
		if (num > 9)
		{
			num = num - 9;
		}
		//sD = !sD;
		sum += num;
	}

	int checkDigit = sum % 10 == 0;
	cout << checkDigit << endl;
	ccc[15] = cnvrt(checkDigit);
}

void output(char cc[], int n) {
	cout << "The char array output as each integer digit" << endl;
	for (int i = 0; i < n; i++) {
		cout << cnvrt(cc[i]);
	}
	cout << endl;
}

char  cnvrt(int digit) {
	if (digit < 0 || digit>9) {
		cout << "You don't know what you are doing" << endl;
		exit(0);
	}
	return digit + '0';
	return digit + 48;
}

int  cnvrt(char digit) {
	if (digit < '0' || digit>'9') {
		cout << "You don't know what you are doing" << endl;
		exit(0);
	}
	return digit - '0';
}

void prpLuhn(char cc[], int n) {
	//Create a random cc in prep for Luhn checksum
	for (int i = 0; i < n; i++) {
		cc[i] = rndDgit();
	}
	//Put null terminator at the end
	for (int i = n; i <= n + 1; i++) {
		cc[i] = '\0';
	}
}

char rndDgit() {
	return rand() % 10 + '0';//Ascii Code for numbers '0'=48 and '9'=57
	//return rand()%10+48;//Ascii Code for numbers '0'=48 and '9'=57
}


