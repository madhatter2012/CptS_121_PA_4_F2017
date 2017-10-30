#include "craps.h"//including header file

//option function for my_menu
int get_choice(void)
{
	int choice = 0;

	do
	{
		print_menu();
		scanf("%d", &choice);

	} while ((choice < 1) || (choice > 4));

	return choice;
}

//priniting the menu
void print_menu()
{

	printf("Welcome to My Craps Game\n\n");

	printf("MAIN MENU:\n\n"
		"1. Rules of the Game\n"
		"2. Play\n"
		"3. Exit\n"
		"enter number to choose your destiny: \n");
}

//menu function
int my_menu(int input)
{
	//my_menu variables
	double bank_balance = 0;
	double  wager_check = 0;
	double wager_amount = 0;
	int result_roll = 0;
	int sum_dice = 0;
	int add_or_subtract = 0;
	int point_value = 0;
	int roll_num = 1;
	int win_loss_neither = 0; 
	double initial_bank_balance = 0.0, current_bank_balance = 0.0;

	//my_menu switch statement
	switch (input)
	{
	case 1: //case 1 prints the rules
	{
		print_game_rules();
		break;
	}
	case 2: //case 2 runs the game
		bank_balance = get_bank_balance();
		wager_amount = get_wager_amount();

		do {//do while for getting and checking the wager

		wager_amount = get_wager_amount();
		wager_check = check_wager_amount(wager_amount, bank_balance);

		} while (wager_check == 0);


		//when you call calculate_sum_dice, use roll_dice as your arguments
		//so you don't have to worry about trying to get roll_die to return two variables
		sum_dice = calculate_sum_dice(roll_die(), roll_die());
		
		result_roll = is_win_loss_or_point(sum_dice); //tells results of the roll
		printf("This is role #: %d\n", roll_num);

		if (result_roll == 1)//1st roll win
		{
			
			initial_bank_balance = bank_balance;
			add_or_subtract = 1;
			bank_balance = adjust_bank_balance(bank_balance, wager_amount, add_or_subtract);
			current_bank_balance = bank_balance;
			win_loss_neither = 1;

			chatter_messages(roll_num, win_loss_neither, initial_bank_balance, current_bank_balance);

		}
		else if (result_roll == 0)//1st roll lose
		{
			add_or_subtract = 0;
			initial_bank_balance = bank_balance;
			bank_balance = adjust_bank_balance(bank_balance, wager_amount, add_or_subtract);
			current_bank_balance = bank_balance;
			win_loss_neither = 0;

			chatter_messages(roll_num, win_loss_neither, initial_bank_balance, current_bank_balance);

		}
		else // 1st roll point
		{
			initial_bank_balance = bank_balance;
			add_or_subtract = -1;
			bank_balance = adjust_bank_balance(bank_balance, wager_amount, add_or_subtract);
			current_bank_balance = bank_balance;
			win_loss_neither = -1;

			chatter_messages(roll_num, win_loss_neither, initial_bank_balance, current_bank_balance);
			
			point_value = sum_dice;
			do {//another nested do while for rolls past the first
				do {
					wager_amount = get_wager_amount();

					wager_check = check_wager_amount(wager_amount, bank_balance);
				} while (wager_check == 0);

				sum_dice = calculate_sum_dice(roll_die(), roll_die());

				result_roll = is_point_loss_or_neither(sum_dice, point_value);
				roll_num++;
				printf("This is role #: %d\n", roll_num);

				if (result_roll == 1)//win on 2nd+ roll
				{
					
					initial_bank_balance = bank_balance;
					add_or_subtract = 1;
					bank_balance = adjust_bank_balance(bank_balance, wager_amount, add_or_subtract);
					current_bank_balance = bank_balance;
					win_loss_neither = 1;

					chatter_messages(roll_num, win_loss_neither, initial_bank_balance, current_bank_balance);
				}
				else if (result_roll == 0)//lose on 2nd+ roll
				{
					
					add_or_subtract = 0;
					initial_bank_balance = bank_balance;
					bank_balance = adjust_bank_balance(bank_balance, wager_amount, add_or_subtract);
					current_bank_balance = bank_balance;
					win_loss_neither = 0;

					chatter_messages(roll_num, win_loss_neither, initial_bank_balance, current_bank_balance);
				}

				initial_bank_balance = bank_balance;
				point_value = sum_dice;
				add_or_subtract = -1;
				current_bank_balance = bank_balance;
				win_loss_neither = -1;

				chatter_messages(roll_num, win_loss_neither, initial_bank_balance, current_bank_balance);

			} while (result_roll == -1);

			printf("Gaaaaame Ooooover, Booooooiiiii!!!\n\n"); //game ends
			break;
		}
	case 3:
		printf("Bu Bye!\n\n"); //exits game
		break;
	}
	return input;
}

//prinits the rules of the game
void print_game_rules(void)
{
	printf("A player rolls two dice. Each die has six faces. These faces contain 1, 2, 3, 4, 5, and 6 spots,\n"
		"after the dice have come to rest, the sum of the spots on the two upward faces is calculated.\n"
		"If the sum is 7 or 11 on the first throw, the player wins.If the sum is 2, 3, or 12 on the first throw (called \"craps\"),\n"
		"the player loses(i.e.the \"house\" wins).If the sum is 4, 5, 6, 8, 9, or 10 on the first throw, then the sum becomes the player's \"point.\"\n"
		"To win, you must continue rolling the dice until you \"make your point.\" The player loses by rolling a 7 before making the point.\n\n");
}

//Prompts the player for an initial bank balance from which wagering will be added or subtracted.
//The player entered bank balance(in dollars, i.e.$100.00) is returned.
double get_bank_balance(void)
{
	double bank_balance = 0.0;
	printf("\nWhat is your starting Bank Balance, muhaha?\n");
	scanf("%lf", &bank_balance);
	return bank_balance;
}

//Prompts the player for a wager on a particular roll.The wager is returned.
double get_wager_amount(void)
{
	double wager = 0.0;
	printf("\nOk. Now what is your ridiculous wager?\n");
	scanf("%lf", &wager);
	return wager;
}

//Checks to see if the wager is within the limits of the player's available balance. 
//If the wager exceeds the player's allowable balance, then 0 is returned; otherwise 1 is returned.
int check_wager_amount(double wager, double balance)
{
	if (wager > balance)
	{
		printf("Lol, you don't have enough stacks for that, yo!\n");
		return 0;
	}
	else
	{
		printf("...wager set.\n");
		return 1;
	}
}

//- Rolls one die.This function should randomly generate a value between 1 and 6, inclusively.Returns the value of the die.
int roll_die(void)
{
	//die roll between 1-6
	int roll = 0;
	for (int i = 0; i < 1; i++)//what does the counter # need to be?
	{
		roll = (rand() % 6) + 1;
		//printf("%d\n", roll);
	}
	return roll;

}

//- Sums together the values of the two dice and returns the result.Note: this result may become the player's point in future rolls.
int calculate_sum_dice(int die1_value, int die2_value)
{
	int sum = 0.0;

	printf("Check out your roll...\n");
	printf("Dice #1: %d\n", die1_value);
	printf("Dice #2: %d\n", die2_value);

	sum = die1_value + die2_value;

	printf("So that's a total roll of: %d\n", sum);
	
	return sum;
}

//Determines the result of the the first dice roll.If the sum is 7 or 11 on the roll, the player wins and 1 is returned.
//If the sum is 2, 3, or 12 on the first throw (called "craps"), the player loses(i.e.the "house" wins) and 0 is returned.
//If the sum is 4, 5, 6, 8, 9, or 10 on the first throw, then the sum becomes the player's "point" and -1 is returned.
int is_win_loss_or_point(int sum_dice)
{
	
	int result = 0;

	if (sum_dice == 7 || sum_dice == 11)
	{
		printf("Player wins on the first roll. Good job...I guess. -_-\n");
		return 1;
	}
	else if (sum_dice == 2 || sum_dice == 3 || sum_dice == 12)
	{
		printf("YOU LOSE! GOOD DAY, SIR!\n");
		return 0;
	}
	else
	{
		printf("Eh, that's a point, I suppose.\n");
		return -1;
	}
}

//Determines the result of any successive roll after the first roll.If the sum of the roll is the point_value, then 1 is returned.
//If the sum of the roll is a 7, then 0 is returned.Otherwise, -1 is returned.
int is_point_loss_or_neither(int sum_dice, int point_value)
{
	int result = 0;
	
	if (sum_dice == point_value)
	{
		printf("Well, FINALLY! Jeez, took you long enough to win one.\n");
		return 1;
	}
	else if (sum_dice == 7)
	{
		printf("YOU LOSE! GOOD DAY, SIR!\n");
		return 0;
	}
	else
	{
		printf("Yeah, ok, that's a point, bfd.\n");
		return -1;
	}
}

//If add_or_subtract is 0, then the wager amount is subtracted from the bank_balance.
//Otherwise, the bank_balance remains the same.The bank_balance result is returned.
double adjust_bank_balance(double bank_balance, double wager_amount, int add_or_subtract)
{
	double result = 0.0;
	
	if (add_or_subtract == 0)
	{
		result = bank_balance - wager_amount;

		printf("Bank Balance: %lf\n", bank_balance);
		printf("Wager: -%lf\n", wager_amount);
		printf("New Bank Balance: %lf\n", result);
		printf("Ahaha, I'll be taking thiis.\n");

		return result;
	}

	else if (add_or_subtract == 1)
	{
		result = bank_balance + wager_amount;
		printf("Bank Balance: %lf\n", bank_balance);
		printf("Wager: -%lf\n", wager_amount);
		printf("New Bank Balance: %lf\n", result);
		printf("Lol...whatever, here's your money...\n");

		return bank_balance;
	}
	else
	{
		printf("No change to your bank balance\n");
		return bank_balance;
	}
}

//Prints an appropriate message dependent on the number of rolls taken so far by the player, the current balance, 
//and whether or not the player just won his roll.
//The parameter win_loss_neither indicates the result of the previous roll.
void chatter_messages(int roll_num, int win_loss_neither, double initial_bank_balance, double current_bank_balance)
{

	if (roll_num > 3)
		printf("I think something's about to happen...\n");
	
	if (current_bank_balance < initial_bank_balance)
		printf("Your Bank Balance is %lf, pal. This is your life, and it's ending one moment at a time.\n", current_bank_balance);
	else
		printf("Your Bank Balance is %lf. Welcome to the party, pal!\n", current_bank_balance);

	if (win_loss_neither == 1)
		printf("*golf clap*\n");
	else if (win_loss_neither == 0)
		printf("Life comes at you fast.\n");
	else
		printf("You're on thin ice, pal.\n");

}
