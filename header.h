// header.h
#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdio_ext.h>
#include <unistd.h>

int sign_up();
int sign_in();
int reserve_ticket();
int cancell_ticket();
void Booking_Details();
int add_train();
int update_train();
int delete_train();
void display_train();
void save_trains_to_file();
int load_trains_from_file();
void to_upper(char *);
int validnum(char *);
int my_atoi(char *);
int valid_date(char *);
int save_passenger();
int load_passenger();

typedef struct usr {
    char username[100];
    char password[50];
    struct usr *usr_link;
} usr_login;

typedef struct data {
    char data[9];
    int total_seats;
    int booked_seats;
    int waiting_list;
    unsigned int avaliable_seats;
} train_data_info;

typedef struct train {
    char train_name[100];
    unsigned int train_number;
    char source[100];
    char destination[100];
    train_data_info dates[3];
    struct train *train_info_link;
} train_info;

typedef struct passenger {
    char name[100];
    unsigned short int age;
    char gender;
    int seat_no;
    char pusr_name[100];
    struct passenger *passenger_link;
} passenger_info;

typedef struct reserve {
    unsigned int train_No;
    char date[9];
    unsigned int No_of_seats;
    passenger_info *passenger_list_head;
    char Rusr_name[100];
    struct reserve *reserve_link;
} reserve_info;

extern train_info *train_head;
extern reserve_info *reserve_head;
extern passenger_info *passenger_head;
extern char cur_usr[100];

#endif
