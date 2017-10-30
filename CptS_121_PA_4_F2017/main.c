#include "craps.h"//including header file


//*(20 pts) A main() function that makes use of the above functions in order to play 
//the game of craps as explained above.Note that you will most likely have a loop in 
//your main() function(or you could have another function that loops through the game play).

int main(void)
{

	//declaring all my variables
	int input = 0, choice = 0, die1_value = 0, die2_value = 0, sum_dice = 0, point_value = 0, add_or_subtract = 0, roll_num = 0, win_loss_neither = 0;
	double wager = 0.0, balance = 0.0, bank_balance = 0.0, wager_amount = 0.0, initial_bank_balance = 0.0, current_bank_balance = 0.0;

	srand(time(NULL)); //srand for dice rolls

	do //do while to keep calling the my_menu function which handles most of the games functions
	{

	input = my_menu(get_choice());
		
	} while (input != 3);

	return 0;
} //end of main