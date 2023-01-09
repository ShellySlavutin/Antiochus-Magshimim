#include<stdio.h>
#include<conio.h>
#include<time.h>
#include<stdlib.h>

#define MAX 54
#define MIN 49

int pickChoice(int choice);
int welcome();
void randomize(char rand1, char rand2, char rand3, char rand4);
void message(int loseOrWin, int tryNum);

enum options {Easy = 1, Moderate, Hard, Crazy} choice;
char randCard1 = ' ', randCard2 = ' ', randCard3 = ' ', randCard4 = ' '; //the numbers of the credit card of Pancratius

int main()
{
	const char YES1 = 'y', NO1 = 'n', YES2 = 'Y', NO2 = 'N';
	int choice = 0, tryNum = 0, hit = 0, miss = 0;
	char card1 = ' ', card2 = ' ', card3 = ' ', card4 = ' '; //the numbers of the card you've gussed
	char continueChoice = ' ';
	srand(time(NULL));

	do {
		continueChoice = ' '; 
		choice = welcome(); //printing the rules and getting the user choice

		//giving each number in the card, a randomized value
		//this is the range we want in ascii charcters, 54 is the max and it's 6, 48 is the min and that's 1
		randCard1 = (char)(rand() % 6 + 49);
		randCard2 = (char)(rand() % 6 + 49);
		randCard3 = (char)(rand() % 6 + 49);
		randCard4 = (char)(rand() % 6 + 49);
		randomize(randCard1, randCard2, randCard3, randCard4);

		tryNum = pickChoice(choice); //getting how many tries the player picked

		//as long as the number of tries is not zero, or the user hasn't guessed all of the cards, continue letting the user guess
		while (tryNum > 0 && (randCard1 != card1 || randCard2 != card2 || randCard3 != card3 || randCard4 != card4)) {
			printf("Write your guess (only 1-6, no ENTER is needed) ");
			if (choice <= 3 && choice >= 1) {
				printf("\n%d guesses left\n", tryNum);
			}
			else {
				printf("\nCRAZY MODE!!\n");
			}

			card1 = getche();
			card2 = getche();
			card3 = getche();
			card4 = getche();
			printf("\n");
			hit = 0; miss = 0;

			//if the numbers are wrong, say that and don't remove a turn
			if ((card1 > MAX || card1 < MIN) || (card2 > MAX || card2 < MIN) || (card3 > MAX || card3 < MIN) || (card4 > MAX || card4 < MIN)) {
				printf("Only 1-6 are allowed, try again! \n");
			}
			else if(card1 == card2 || card1 == card3 || card1 == card4 || card2 == card3 || card2 == card4 || card3 == card4) {
				printf("You can't enter the same digit more than once, really tried to trick us here? >:( \n");
			}
			else
			{
				//if the user guessed a number correcdtly, add one to the hit variable, do it for evey right guess
				//if the user guessed a corret number but not in the right place add one to the miss variable
				if (card1 == randCard1) {
					hit++;
				}
				else if (card1 == randCard2 || card1 == randCard3 || card1 == randCard4) {
					miss++;
				}

				if (card2 == randCard2) {
					hit++;
				}
				else if(card2 == randCard1 || card2 == randCard3 || card2 == randCard4) {
					miss++;
				}

				if (card3 == randCard3) {
					hit++;
				}
				else if (card3 == randCard2 || card3 == randCard1 || card3 == randCard4) {
					miss++;
				}

				if (card4 == randCard4) {
					hit++;
				}
				else if(card4 == randCard2 || card4 == randCard3 || card4 == randCard1) {
					miss++;
				}

				--tryNum; //remove one from the number of tries one has

				printf("You got\t\t%d HITS\t\t%d MISSES.\n", hit, miss);
			}
		
		//determines the ending message :
		if (randCard1 == card1 && randCard2 == card2 && randCard3 == card3 && randCard4 == card4) { //if the user won, print this
			message(1, pickChoice(choice) - tryNum);
			}
		else if(tryNum == 0) { //if the user lost, meaning he is left with 0 tries and the card isn't right, print this
			message(0, 0); }
		}

		do {
			printf("Would you like to try again? (y/n): "); //asking the user if he wants to continue
			continueChoice = getche(); //puts the char picked choice 
			putchar('\n');
		} while ((continueChoice != NO1 && continueChoice != NO2) && (continueChoice != YES1 && continueChoice != YES2));

	} while (continueChoice == YES1 || continueChoice == YES2);
	
	printf("\nBye bye!\n");
	getchar();
	
	return 0;
}

/*this function prints the introduction and the rules of the game and gets the user's choice
input : none
output : the user's choice*/
int welcome()
{	
	//welcome message
	printf("\nWelcome to \"MAGSHIMIM CODE-BREAKER\"!!!\n\n");
	printf("A secret password was chosen to protect the credit card of Pancratius,\n");
	printf("the descendant of Antiochus.\nYour mission is to stop Pancratius by revealing his secret password.\n\n");
	
	//rules
	printf("The rules are as follows:\n");
	printf("1. In each round you try to guess the secret password (4 distinct digits)\n");
	printf("2. After every guess you'll receive two hints about the password\n   HITS:   The number of digits in your guess which were exactly right.\n   MISSES: The number of digits in your guess which belongs to\n           the password but were miss-placed.\n");
	printf("3. If you'll fail to guess the password after a certain number of rounds\n   Pancratius will buy all the gifts for Hanukkah!!!\n\n");
	
	//user's choice
	printf("Please choose the game level:\n1 - Easy (20 rounds)\n2 - Moderate (15 rounds)\n3 - Hard (10 rounds)\n4 - Crazy (random number of rounds 5-25)\n");

	do {
		printf("Make a choice : ");
		scanf("%d", &choice);
		getchar(); //cleans buffer incase of a char input
	} 
	while (choice < Easy || choice > Crazy); //if the choice doesn't fit the critera, make the user choose again

	return choice;
}

/*this function chaeck if the randomized numbers are correct and fit the criteara
input : rand1 - the 1 number
		rand2 - the 2 number
		rand3 - the 3 number
		rand4 - the 4 number
output : none */
void randomize(char rand1, char rand2, char rand3, char rand4)
{
	do {
		while (rand1 == rand2 || rand1 == rand3 || rand1 == rand4) //if rand1 is equal to any of the other chars, randomize it
			rand1 = (char)(rand() % 6 + 49);
		while (rand2 == rand1 || rand2 == rand3 || rand2 == rand4) //if rand2 is equal to any of the other chars, randomize it
			rand2 = (char)(rand() % 6 + 49);
		while (rand3 == rand2 || rand3 == rand1 || rand3 == rand4) //if rand3 is equal to any of the other chars, randomize it
			rand3 = (char)(rand() % 6 + 49);
		while (rand4 == rand2 || rand4 == rand1 || rand4 == rand3) //if rand4 is equal to any of the other chars, randomize it
			rand4 = (char)(rand() % 6 + 49);
	} while (rand4 == rand2 || rand4 == rand1 || rand4 == rand3 || rand3 == rand2 || rand3 == rand1 || rand2 == rand1); //aslong as they're still equal

	randCard1 = rand1; //after we made sure they are not equal, we can put the value back into them
	randCard2 = rand2;
	randCard3 = rand3;
	randCard4 = rand4;
}

/*this function determines the number of tries the usr has based on his choice
input : choice - the usser's choice
output : the number of tries*/
int pickChoice(int choice) {
	const int EASY = 20, MEDIUM = 15, HARD = 10, CRAZY = rand() % 21 + 1;
	srand(time(NULL));
	switch (choice) {
	case 1: return EASY;
		break;
	case 2: return MEDIUM;
		break;
	case 3: return HARD;
		break;
	case 4: return CRAZY;
		break;
	default: printf("something went wrong");
		return 0;
		break;
	}
}

/*prints a lose or a win message based on the input
input - loseOrWin - if it will be a win message or a lose message, 1 for win, 0 for lose
		tryNum - only matters if it's a win message, prints the number of trys it took
output - none */
void message(int loseOrWin, int tryNum){       
	switch (loseOrWin) {
		case 0 :
		printf("           ,  ,, ,                       \n");
		printf("      , ,; ; ;;  ; ;  ;                  \n");
		printf("   , ; ';  ;  ;; .-''\\ ; ;              \n");
		printf(", ;  ;`  ; ,; . / /8b \\ ; ;             \n");
		printf("`; ; .;'         ;,\\8 |  ;  ;           \n");
		printf(" ` ;/   / `_      ; ;;    ;  ; ;         \n");
		printf("    |/.'  /9)    ;  ; `    ;  ; ;        \n");
		printf("   ,/'          ; ; ;  ;   ; ; ; ;       \n");
		printf("  /_            ;    ;  `    ;  ;        \n");
		printf(" `?8P\"  .; ; ; ; ; ; ;;                 \n");
		printf("  | ;  .:: `     ;; ; ;   `  ;  ;        \n");
		printf(" `' `--._      ;;  ;;  ; ;   ;   ;       \n");
		printf("  `-..__..--''   ; ;    ;;   ; ;   ;     \n");
		printf("              ;    ; ; ;   ;     ;       \n");
		printf("OOOOHHHH!!! Pancratius won and bought all of Hanukkah's gifts.\n");
		printf("Nothing left for you...\n");
		printf("The secret password was %c%c%c%c\n\n",randCard1, randCard2, randCard3, randCard4);
		break;
		case 1 :
		printf("\t .----------------. \n");
		printf("\t| .--------------. |\n");
		printf("\t| |     __       | |\n");
		printf("\t| |    /  |      | |\n");
		printf("\t| |    `| |      | |\n");
		printf("\t| |     | |      | |\n");
		printf("\t| |    _| |_     | |\n");
		printf("\t| |   |_____|    | |\n");
		printf("\t| |              | |\n");
		printf("\t| '--------------' |\n");
		printf("\t '----------------' \n");
		printf("\t4 HITS YOU WON!!!\n\n");
		printf("It took you only %d guesses, you are a professional code breaker!\n\n",tryNum);
	}
}

	
	
	
	
	
	
