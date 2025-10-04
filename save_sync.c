// save_sync_passenger.c
#include "header.h"

// SAVE PASSENGERS TO FILE
int save_passenger() {
    FILE *fp = fopen("passenger_data.txt", "w");
    if (!fp) {
        perror("Failed to open passenger_data.txt");
        return 0;
    }

    reserve_info *res = reserve_head;
    while (res) {
        fprintf(fp, "Train No: %u, Date: %s, Seats Reserved: %u, usr_name: %s\n",
                res->train_No, res->date, res->No_of_seats, res->Rusr_name);

        passenger_info *pax = res->passenger_list_head;
        int count = 1;
        while (pax) {
            fprintf(fp, " Passenger %d: Name: %s, Age: %hu, Gender: %c, Seat: %d, User: %s\n",
                    count++, pax->name, pax->age, pax->gender, pax->seat_no, pax->pusr_name);
            pax = pax->passenger_link;
        }

        fprintf(fp, "----------------------------------------\n");
        res = res->reserve_link;
    }

    fclose(fp);
    return 1;
}

// LOAD PASSENGERS FROM FILE
int load_passenger() {
    FILE *fp = fopen("passenger_data.txt", "r");
    if (!fp) {
        perror("Failed to open passenger_data.txt");
        return 0;
    }

    char line[256];
    reserve_info *last_reserve = NULL;

    while (fgets(line, sizeof(line), fp)) {
        if (strncmp(line, "Train No:", 9) == 0) {
            reserve_info *new_res = (reserve_info *)malloc(sizeof(reserve_info));
            if (!new_res) {
                perror("Memory allocation failed");
                fclose(fp);
                return 0;
            }

            if (sscanf(line, "Train No: %u, Date: %8s, Seats Reserved: %u, usr_name: %s",
                       &new_res->train_No, new_res->date, &new_res->No_of_seats, new_res->Rusr_name) != 4) {
                free(new_res);
                continue;
            }

            new_res->reserve_link = NULL;
            new_res->passenger_list_head = NULL;

            if (reserve_head == NULL) {
                reserve_head = new_res;
                last_reserve = new_res;
            } else {
                last_reserve->reserve_link = new_res;
                last_reserve = new_res;
            }

        } else if (strncmp(line, " Passenger", 9) == 0) {
            if (!last_reserve) continue;

            passenger_info *new_pax = (passenger_info *)malloc(sizeof(passenger_info));
            if (!new_pax) {
                perror("Memory allocation failed");
                fclose(fp);
                return 0;
            }

            char *name_start = strstr(line, "Name: ");
            char *age_start = strstr(line, ", Age: ");
            char *gender_start = strstr(line, ", Gender: ");
            char *seat_start = strstr(line, ", Seat: ");
            char *user_start = strstr(line, ", User: ");

            if (!name_start || !age_start || !gender_start || !seat_start || !user_start) {
                free(new_pax);
                continue;
            }

            name_start += 6;
            int name_len = age_start - name_start;
            if (name_len >= sizeof(new_pax->name)) name_len = sizeof(new_pax->name) - 1;
            strncpy(new_pax->name, name_start, name_len);
            new_pax->name[name_len] = '\0';

            sscanf(age_start, ", Age: %hu", &new_pax->age);
            sscanf(gender_start, ", Gender: %c", &new_pax->gender);
            sscanf(seat_start, ", Seat: %d", &new_pax->seat_no);
            sscanf(user_start, ", User: %s", new_pax->pusr_name);

            new_pax->passenger_link = NULL;

            if (last_reserve->passenger_list_head == NULL) {
                last_reserve->passenger_list_head = new_pax;
            } else {
                passenger_info *temp = last_reserve->passenger_list_head;
                while (temp->passenger_link)
                    temp = temp->passenger_link;
                temp->passenger_link = new_pax;
            }
        }
    }

    fclose(fp);
    return 1;
}
