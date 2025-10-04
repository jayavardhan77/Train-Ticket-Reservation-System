// admin_operations.c
#include "header.h"

int add_train()
{
    int add = 0;
    train_info *new_node = (train_info *)malloc(sizeof(train_info));
    if (!new_node)
    {
        printf("Memory allocation failed\n");
        return 0;
    }

    printf("Enter Train Name: ");
    __fpurge(stdin);
    scanf("%s", new_node->train_name);

    printf("Enter Train Number: ");
    scanf("%u", &new_node->train_number);

    printf("Enter Source: ");
    __fpurge(stdin);
    scanf("%s", new_node->source);

    printf("Enter Destination: ");
    __fpurge(stdin);
    scanf("%s", new_node->destination);

    printf("Enter 3 travel dates and total seats:\n");
    for (int i = 0; i < 3; i++)
    {
    l1:
        printf("Date %d (dd/mm/yy): ", i + 1);
        __fpurge(stdin);
        scanf("%s", new_node->dates[i].data);

        if (!valid_date(new_node->dates[i].data))
        {
            puts("Invalid date format.");
            goto l1;
        }

        printf("Total seats: ");
        scanf("%d", &new_node->dates[i].total_seats);

        new_node->dates[i].booked_seats = 0;
        new_node->dates[i].waiting_list = 0;
        new_node->dates[i].avaliable_seats = new_node->dates[i].total_seats;
    }

    new_node->train_info_link = NULL;

    if (train_head == NULL)
    {
        train_head = new_node;
    }
    else
    {
        train_info *temp = train_head;
        while (temp->train_info_link != NULL)
        {
            temp = temp->train_info_link;
        }
        temp->train_info_link = new_node;
    }

    save_trains_to_file();
    return 1;
}

int delete_train() 
{
    unsigned int number;
    printf("Enter the train number to delete: ");
    __fpurge(stdin);
    scanf("%u", &number);

    train_info *temp = train_head, *prev = NULL;
    while (temp != NULL && temp->train_number != number)
    {
        prev = temp;
        temp = temp->train_info_link;
    }

    if (temp == NULL)
    {
        puts("Train not found.");
        return 0;
    }

    if (prev == NULL)
        train_head = temp->train_info_link;
    else
        prev->train_info_link = temp->train_info_link;

    free(temp);
    save_trains_to_file();
    return 1;
}

void display_train()
{
    train_info *temp = train_head;
    while (temp != NULL)
    {
        printf("\n-----------------------------------------------------------------------------\n");
        printf("T-No    Train Name      Source     Destination\n");
        printf("%-7u %-15s %-10s %-12s\n", temp->train_number, temp->train_name, temp->source, temp->destination);
        printf("-----------------------------------------------------------------------------\n");
        printf("Date         Total Seat   Waiting List   Booked   Available\n");
        printf("-----------------------------------------------------------------------------\n");

        for (int i = 0; i < 3; i++)
        {
            printf("%-12s %-12d %-14d %-8d %-12d\n",
                   temp->dates[i].data,
                   temp->dates[i].total_seats,
                   temp->dates[i].waiting_list,
                   temp->dates[i].booked_seats,
                   temp->dates[i].avaliable_seats);
        }

        temp = temp->train_info_link;
    }
}

void save_trains_to_file()
{
    FILE *fp = fopen("train_data.txt", "w");
    if (!fp)
    {
        puts("Failed to open train_data.txt");
        return;
    }

    train_info *temp = train_head;
    while (temp)
    {
        fprintf(fp, "%u %s %s %s\n", temp->train_number, temp->train_name, temp->source, temp->destination);

        for (int i = 0; i < 3; i++)
        {
            fprintf(fp, "%s %d %d %d %d\n",
                    temp->dates[i].data,
                    temp->dates[i].total_seats,
                    temp->dates[i].booked_seats,
                    temp->dates[i].waiting_list,
                    temp->dates[i].avaliable_seats);
        }

        temp = temp->train_info_link;
    }

    fclose(fp);
}

int load_trains_from_file()
{
    FILE *fp = fopen("train_data.txt", "r");
    if (!fp)
    {
        puts("train_data.txt not found.");
        return 0;
    }

    train_info *new_node;
    while (!feof(fp))
    {
        new_node = (train_info *)malloc(sizeof(train_info));
        if (!new_node)
        {
            puts("Memory allocation failed");
            return 0;
        }

        if(fscanf(fp,"%u %s %s %s",&new_node->train_number,new_node->train_name,new_node->source,new_node->destination) != 4) {
            free(new_node);
            break;
        }

        for (int i = 0; i < 3; i++)
        {
        fscanf(fp,"%s %d %d %d %d",
                   new_node->dates[i].data,
                   &new_node->dates[i].total_seats,
                   &new_node->dates[i].booked_seats,
                   &new_node->dates[i].waiting_list,
                   &new_node->dates[i].avaliable_seats);
        }

        new_node->train_info_link = NULL;

        if (train_head == NULL)
            train_head = new_node;
        else
        {
            train_info *temp = train_head;
            while (temp->train_info_link)
                temp = temp->train_info_link;
            temp->train_info_link = new_node;
        }
    }

    fclose(fp);
    return 1;
}
