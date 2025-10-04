// main.c
#include "header.h"

train_info *train_head = NULL;
reserve_info *reserve_head = NULL;
passenger_info *passenger_head = NULL;
char cur_usr[100];

void menu1() 
{
    puts("-------------MENU-1-----------------");
    puts("1: Sign-Up");
    puts("2: Sign-In");
    puts("3: Quit");
    puts("Enter your choice:");
}

void menu2() 
{
    puts("-------------MENU-2-----------------");
    puts("R/r: To Reserve Ticket");
    puts("C/c: To Cancel Ticket");
    puts("B/b: Booking Details");
    puts("Q/q: Quit from App");
    puts("Enter your option:");
}

int main() 
{
    char choice1, choice2;
    int login = 0;

    load_trains_from_file();
    load_passenger();

    while (1) 
    {
        menu1();
        __fpurge(stdin);
        scanf("%c", &choice1);
        switch (choice1) 
	{
            case '1':
        	        if (sign_up())
                	    puts("Sign up successful. Please login to proceed.");
	                break;
            case '2':
        	        if (sign_in()) 
			{
                	    puts("Sign in successful.");
	                    login = 1;
        	        }
                	break;
            case '3':
	                puts("Application closed.");
        	        exit(0);
            default:
                	puts("Invalid input. Try again.");
        }

        while (login) 
	{
            menu2();
            __fpurge(stdin);
            scanf("%c", &choice2);
            to_upper(&choice2);
            switch (choice2) 
	    {
                case 'R': if (reserve_ticket())
                        	puts("Reservation successful.");
			  else
		                puts("Reservation unsuccessful.");
                	  break;

                case 'C': if (cancell_ticket())
		                puts("Cancellation successful.");
			  else
		                puts("Cancellation unsuccessful.");
        	          break;

                case 'B': Booking_Details();
	                  break;

                case 'Q': puts("Quitting from App");
                          exit(0);

                default:
	                    puts("Invalid option. Please enter again.");
            }
        }
    }

    return 0;
}
