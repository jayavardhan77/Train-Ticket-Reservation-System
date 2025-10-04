// ticket_operations.c
#include "header.h"

int reserve_ticket()
{
    display_train();

    unsigned int train_No;
    int found_tr_No = 0, i, no_seats, found_date = 0, cur_seat = 0;
    train_info *temp = train_head;
    char date[12];

    puts("Enter the train number:");
    scanf("%u", &train_No);

    while (temp)
    {
        if (train_No == temp->train_number)
        {
            found_tr_No = 1;
            break;
        }
        temp = temp->train_info_link;
    }

    if (!found_tr_No)
    {
        puts("Train number not found");
        return 0;
    }

    reserve_info *Rnode = (reserve_info *)malloc(sizeof(reserve_info));
    if (!Rnode)
    {
        puts("Memory allocation failed");
        return 0;
    }

    puts("Enter the date (dd/mm/yy) of travelling:");
    __fpurge(stdin);
    scanf("%s", date);

    for (i = 0; i < 3; i++)
    {
        if (strcmp(date, temp->dates[i].data) == 0)
        {
            found_date = 1;
            cur_seat = temp->dates[i].booked_seats;

            Rnode->train_No = train_No;
            strcpy(Rnode->date, date);

            puts("Enter the number of seats to reserve:");
            scanf("%u", &Rnode->No_of_seats);
            no_seats = Rnode->No_of_seats;

            if (no_seats > temp->dates[i].avaliable_seats)
            {
                printf("Only %d seats available. Cannot reserve %d seats.\n",temp->dates[i].avaliable_seats, no_seats);
                free(Rnode);
                return 0;
            }

            temp->dates[i].booked_seats += no_seats;
            temp->dates[i].avaliable_seats -= no_seats;
            save_trains_to_file();
            break;
        }
    }

    if (!found_date)
    {
        puts("Date not found");
        free(Rnode);
        return 0;
    }

    strcpy(Rnode->Rusr_name, cur_usr);
    Rnode->passenger_list_head = NULL;
    Rnode->reserve_link = NULL;

    if (reserve_head == NULL)
    {
        reserve_head = Rnode;
    }
    else
    {
        reserve_info *temp_reserve = reserve_head;
        while (temp_reserve->reserve_link)
            temp_reserve = temp_reserve->reserve_link;
        temp_reserve->reserve_link = Rnode;
    }

    passenger_info *last_passenger = NULL;
    for (i = 0; i < no_seats; i++)
    {
        passenger_info *new_passenger = (passenger_info *)malloc(sizeof(passenger_info));
        if (!new_passenger)
        {
            puts("Memory allocation failed for passenger");
            return 0;
        }

        printf("Enter details for passenger %d:\n", i + 1);
        __fpurge(stdin);
        printf("Name: ");
        scanf("%99s", new_passenger->name);

        __fpurge(stdin);
        printf("Age: ");
        scanf("%hu", &new_passenger->age);

        char gen;
        __fpurge(stdin);
    GEN:
        printf("Gender (M/F/O): ");
        scanf("%c",&gen);
           if(!((gen=='m')|(gen=='f')|(gen=='M')|(gen=='F')|(gen=='o')|(gen=='O')))
           {
                   puts("invalid gender please enter again");
                   goto GEN;
           }
        new_passenger->gender=gen;
        new_passenger->seat_no = ++cur_seat;
        strcpy(new_passenger->pusr_name, cur_usr);
        new_passenger->passenger_link = NULL;

        if (Rnode->passenger_list_head == NULL)
        {
            Rnode->passenger_list_head = new_passenger;
            last_passenger = new_passenger;
        }
        else
        {
            last_passenger->passenger_link = new_passenger;
            last_passenger = new_passenger;
        }
    }

    if (save_passenger())
        puts("Passenger data saved successfully.");
    else
        puts("Failed to save passenger data.");

    return 1;
}

int cancell_ticket()
{
    unsigned int train_num;
    char travel_date[15];
    int seat_num;

    printf("Enter Train Number: ");
    __fpurge(stdin);
    scanf("%u", &train_num);

    printf("Enter Travel Date (dd/mm/yy): ");
    __fpurge(stdin);
    scanf("%s", travel_date);

    printf("Enter Seat Number to Cancel: ");
    __fpurge(stdin);
    scanf("%d", &seat_num);

    train_info *train = train_head;
    while (train)
    {
        if (train->train_number == train_num)
        {
            for (int i = 0; i < 3; i++)
            {
                if (strcmp(train->dates[i].data, travel_date) == 0)
                {
                    train->dates[i].booked_seats--;
                    train->dates[i].avaliable_seats++;
                    break;
                }
            }
            break;
        }
        train = train->train_info_link;
    }

    reserve_info *res = reserve_head;
    while (res)
    {
        if (res->train_No == train_num && strcmp(res->date, travel_date) == 0 && strcmp(res->Rusr_name, cur_usr) == 0)
        {

            passenger_info *prev = NULL, *curr = res->passenger_list_head;
            while (curr)
            {
                if (curr->seat_no == seat_num)
                {
                    if (prev == NULL)
                        res->passenger_list_head = curr->passenger_link;
                    else
                        prev->passenger_link = curr->passenger_link;
                    free(curr);
                    save_trains_to_file();
                    save_passenger();
                    printf("Seat %d cancelled successfully.\n", seat_num);
                    return 1;
                }
                prev = curr;
                curr = curr->passenger_link;
            }
        }
        res = res->reserve_link;
    }

    printf("No matching reservation found.\n");
    return 0;
}

void Booking_Details()
{
    reserve_info *res = reserve_head;
    int found = 0;

    printf("\n-------------------- Booking Details for %s --------------------\n", cur_usr);
    while (res != NULL)
    {
        if (strcmp(res->Rusr_name, cur_usr) == 0)
        {
            printf("\nTrain No: %u\nDate: %s\n", res->train_No, res->date);
            printf("Passenger Details:\n");
            printf("----------------------------------------------------\n");
            printf("Name\t\tAge\tGender\tSeat No\n");
            printf("----------------------------------------------------\n");

            passenger_info *p = res->passenger_list_head;
            while (p)
            {
                printf("%-10s\t%3d\t  %c\t   %d\n", p->name, p->age, p->gender, p->seat_no);
                p = p->passenger_link;
            }
            found = 1;
        }
        res = res->reserve_link;
    }

    if (!found)
        printf("No bookings found for you.\n");
}
