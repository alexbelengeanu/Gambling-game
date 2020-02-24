#include <iostream>
#include <string>
#include <stdlib.h>
#include <random>
#include <ctime>
using namespace std;
char nickname[30];
float amount;
int nicknameValidation(char name[30]) // a function used to see if the nickname only contains lower/upper cases
{
	int i, k = 0;
	for (i = 0;i < strlen(name);i++)
	{
		if ((name[i] >= 'a' && name[i] <= 'z') || (name[i] >= 'A' && name[i] <= 'Z'))
		{
			k++;
		}
		else
		{

			k = 0;
			break;
		}
	}
	return k;
}
int amountValidation(float n) // a function used to validate if the number is between 0 and 1.000.000
{
	if (n > 0 && n < 1000000)
		return 1;
	else
		return 0;
}
void drawHeader() // it shows the header message
{
	int i;
	for (i = 0;i < 50;i++)
		cout << "=";
	cout << "\n* Project:\tCASINO GAMBLING GAME v1.1";
	cout << "\n* Author:\tAlexandru-Florin BELENGEANU\n";
	for (i = 0;i < 50;i++)
		cout << "=";
}
void getNickname() // a function used to get the user's nickname
{
	char name[30];
	int ok=0;
	system("cls");
	drawHeader();
	cout << "\n\nHello there, dear player! We are happy to see you. \nMaybe before you start, you could tell us what nickname would you want to use?\n\n*note*ONLY upper/lower cases allowed!(no blank spaces, numbers or symbols)";
	do {
		cout << "\nInsert nickname: ";
		cin.getline(name, 30);
		ok = nicknameValidation(name);
		if (ok == 0) cout << "You entered an invalid nickname, let's try again!";
		else strcpy(nickname, name);
	} while (ok == 0);
}
void getAmount() // a function used to get the amount of money the player wants to gamble
{
	int ok = 0;
	system("cls");
	drawHeader();
	cout << "\n\nNow, we can get started " << nickname << " !";
	cout << "\nTell us what how much money are you willing to gamble today, below.\n\n*note*The amount of money you will gamble should not be lower than 0$ and bigger than 1.000.000$.";
	do {
		cout << "\nInsert amount: ";
		cin >> amount;
		ok = amountValidation(amount);
		if (ok == 0) cout << "You entered an invalid amount of money, let's do this one more time buddy!";
	} while (ok == 0);
}
int getGuess() // function to get the user's guess for the lucky number
{
	int opt, ok = 0;
	do {
		cout << "And now, dear " << nickname << " your lucky number is: ";
		cin >> opt;
		if (opt == 0) return opt;
		if (opt < 0 || opt>10) cout << "Your number should be between 1-10. Try again!"; 
	} while (opt < 0 || opt>10);
	return opt;
}
int getRandomNumber() // generates the random lucky number
{
	default_random_engine randomGenerator(time(0));
	uniform_int_distribution<int> randomNum(1,10);
	return randomNum(randomGenerator);
}
void addAmount() // a function used to add an amount of money to the player's deposit
{
	float money;
	int ok = 0;
	system("cls");
	drawHeader();
	do {
		cout << "\n\nEnter the amount of money you want to add to your deposit: ";
		cin >> money;
		ok = amountValidation(money);
		if (ok == 0) cout << "You entered an invalid amount of money, let's give it one more chance!";
		else if (money + amount >= 1000000 && ok == 1) {
			cout << "Please try again with a lower number, because your deposit is exceeding our limit of 1.000.000$.";
			ok--;
		}
		else amount += money;
	} while (ok == 0);
}
void cashOut() // function used to cash out an amount of money
{
	float money;
	int ok = 0;
	system("cls");
	drawHeader();
	cout << "\n**balance: " << amount << " $ left.";
	do {
		cout << "\n\nEnter the amount of money you want to take away from your deposit: ";
		cin >> money;
		if (money > amount) cout << "You don't have that money! Go check your balance and then try again ;)";
		else if (money < 0) cout << "You cant cash out a negative amount of money :c";
		else {
			ok = 1;
			amount -= money;
		}
	} while (ok == 0);
}
void startGame() // the game itself
{
	system("cls");
	drawHeader();
	float betAmount;
	int guess, random_number;
	do {
		cout << '\n' << nickname << ", enter the amount of money you would like to bet: ";
		cin >> betAmount;
		if (betAmount > amount) cout << "You can't bet more money than you have got in your deposit, try again! :s\n";
		if (betAmount <= 0) cout << "You can't bet a negative amount of money, or a bet equal to 0$! Let's do this one more time.\n";
	} while (betAmount > amount || betAmount<=0);
	do {
		system("cls");
		drawHeader();
		cout << "\nCURRENT BET: "<<betAmount;
		cout << "\n**balance: " << amount << " $ left.";
		cout << "\n**choose '0' as your lucky number if you want to exit to the main menu.\n\n";
		guess = getGuess();
		if (guess == 0) break;
		else {
			random_number = getRandomNumber();
			if (guess == random_number) {
				cout << "You are the LUCKY WINNER! " << betAmount * 10 << "$ were added to your balance.\n";
				cout << "The random generated number was: " << random_number << '\n';
				amount += betAmount * 10;
				system("pause");
			}
			else {
				cout << "Bad luck bro ! You just lost " << betAmount << "$.\n";
				cout << "The random generated number was: " << random_number << '\n';
				amount -= betAmount;
				system("pause");
				if (betAmount > amount && amount!=0) {
					system("cls");
					drawHeader();
					cout << "\nCURRENT BET: " << betAmount;
					cout << "\n**balance: " << amount << " $ left.";
					cout << "\n**choose '0' as your lucky number if you want to exit to the main menu.\n\n\n";
					cout << "You don't have that much money left !! Please change the betting amount into a lower one.\n\n";
					system("pause");
					break;
				}
				else if (betAmount > amount && amount == 0) {
					system("cls");
					drawHeader();
					cout << "\nCURRENT BET: " << betAmount;
					cout << "\n**balance: " << amount << " $ left.";
					cout << "\n**choose '0' as your lucky number if you want to exit to the main menu.\n\n\n";
					cout << "You are BROKE :( !! Go add some $$ into your deposit if you want to play again.\n\n";
					system("pause");
					break;
				}
			}
		}

	} while (guess != 0);
}
void drawMenu() // shows the menu of the game
{
	int opt;
	do {
		system("cls");
		drawHeader();
		cout << "\n1. Gamble on numbers between 1-10.(prize = bet * 10)\n";
		cout << "2. Add more money.\n";
		cout << "3. Cash out.\n";
		cout << "0. Exit.\n\n";
		cout << "**balance: " << amount << " $ left.\n\n";
		cout << "Choose an option: ";
		cin >> opt;
		switch (opt){
		case 1:
			if(amountValidation(amount)) startGame();
			else if (amount <= 0) {
				cout << "Please add some paper to your deposit, you got 0$ left :)\n";
				system("pause");
			}
			break;
		
		case 2:
			addAmount();
			break;

		case 3:
			cashOut();
			break;

		case 4:
			exit(0);
			break;
		}
	} while (1);
}
int main() 
{
	getNickname();
	getAmount();
	drawMenu();
	system("pause");
	return 0;
}
