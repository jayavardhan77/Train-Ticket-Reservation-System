// atoi.c
#include "header.h"

int validnum(char *p) {
    int i = 1;
    if (!((p[0] == '-') || (p[0] >= '0' && p[0] <= '9')))
        return 0;
    while (p[i]) {
        if (!(p[i] >= '0' && p[i] <= '9'))
            return 0;
        i++;
    }
    return 1;
}

int my_atoi(char *p) {
    int i = 0, value = 0, sign = 1;

    if (p[0] == '-') {
        sign = -1;
        i = 1;
    }

    for (; p[i]; i++) {
        value = value * 10 + (p[i] - '0');
    }

    return value * sign;
}

int valid_date(char *p) {
    int len = strlen(p);
    if (len != 8 || p[2] != '/' || p[5] != '/')
        return 0;

    char temp[3];
    temp[2] = '\0';

    strncpy(temp, p, 2);
    int date = my_atoi(temp);
    if (date < 1 || date > 31)
        return 0;

    strncpy(temp, p + 3, 2);
    int month = my_atoi(temp);
    if (month < 1 || month > 12)
        return 0;

    strncpy(temp, p + 6, 2);
    int year = my_atoi(temp);
    if (year < 25)
        return 0;

    return 1;
}
