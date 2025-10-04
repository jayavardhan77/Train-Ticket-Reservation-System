// signin_signfun.c
#include "header.h"

//char cur_usr[100];

void to_upper(char *s)
{
        if (*s >= 'a' && *s <= 'z')
        {
        *s = *s - 32;
        }
}

int is_upper(char *s)
{
    for (int i = 0; s[i]; i++)
    {
        if (s[i] >= 'A' && s[i] <= 'Z')
            return 1;
    }
    return 0;
}

int is_lower(char *s)
{
    for (int i = 0; s[i]; i++)
    {
        if (s[i] >= 'a' && s[i] <= 'z')
            return 1;
    }
    return 0;
}

int is_numeric(char *s)
{
    for (int i = 0; s[i]; i++)
    {
        if (s[i] >= '0' && s[i] <= '9')
            return 1;
    }
    return 0;
}

int is_special(char *s)
{
    for (int i = 0; s[i]; i++)
    {
        if (s[i] == '@' || s[i] == '#' || s[i] == '!' || s[i] == '$' || s[i] == '%' || s[i] == '&' || s[i] == '_')
            return 1;
    }
    return 0;
}

int sign_up()
{
    FILE *fp = fopen("usr_logins.txt", "a+");
    if (!fp)
    {
        puts("Unable to open user login file.");
        return 0;
    }

    char name[100], psw[50], str[100];
    int count = 0;

    puts("Enter username (no spaces): ");
    __fpurge(stdin);
    fgets(name, 100, stdin);
    if (name[strlen(name) - 1] == '\n')
            name[strlen(name) - 1] = '\0';

    rewind(fp);
    while (fscanf(fp, "%s", str) == 1)
    {
        if (strcmp(name, str) == 0)
        {
            puts("Username already exists. Try another.");
            fclose(fp);
            return 0;
        }
    }

retry_password:
    puts("Enter password (min 8 chars, mix of upper, lower, digit, special): ");
    __fpurge(stdin);
    fgets(psw, 50, stdin);
    if (psw[strlen(psw) - 1] == '\n')
            psw[strlen(psw) - 1] = '\0';

    if (!(strlen(psw) >= 8 && is_upper(psw) && is_lower(psw) && is_numeric(psw) && is_special(psw)))
    {
        count++;
        puts("Invalid password. Try again.");
        if (count < 5)
                goto retry_password;
        puts("Too many failed attempts.");
        fclose(fp);
        return 0;
    }

    fprintf(fp, "%s %s\n", name, psw);
    fclose(fp);
    return 1;
}

int sign_in()
{
    FILE *fp = fopen("usr_logins.txt", "r");
    if (!fp)
    {
        puts("Login file not found.");
        return 0;
    }

    char user_name[100], password[50], fileusr[100], filepassword[50];
    int found = 0, attempts = 0;

retry_login:
    puts("Enter username:");
    __fpurge(stdin);
    fgets(user_name, 100, stdin);
    if (user_name[strlen(user_name) - 1] == '\n')
            user_name[strlen(user_name) - 1] = '\0';

    puts("Enter password:");
    __fpurge(stdin);
    fgets(password, 50, stdin);
    if (password[strlen(password) - 1] == '\n')
            password[strlen(password) - 1] = '\0';

    rewind(fp);
    while (fscanf(fp, "%s %s", fileusr, filepassword) != EOF)
    {
        if (strcmp(user_name, fileusr) == 0 && strcmp(password, filepassword) == 0)
        {
            found = 1;
            break;
        }
    }

    if (found)
    {
        strcpy(cur_usr, user_name);
        if (strcmp(user_name, "officer") == 0)
        {
            int ch;
            while (1)
            {
                printf("\n----- Officer Menu -----\n");
                printf("1. Add Train\n");
                printf("2. Delete Train\n");
                printf("3. Display Trains\n");
                printf("4. Quit\n");
                printf("Choice: ");
                __fpurge(stdin);
                scanf("%d", &ch);

                if (ch == 1)
                {
                    if (add_train())
                            puts("Train added successfully.");
                }
                else if (ch == 2)
                {
                    if (delete_train())
                            puts("Train deleted successfully.");
                }
                else if (ch == 3)
                {
                    display_train();
                }
                else if (ch == 4)
                {
                    puts("Returning to main menu...");
                    return 0;
                }
                else
                {
                    puts("Invalid option.");
                }
            }
        }

        return 1;
    }
    else
    {
        attempts++;
        if (attempts >= 3)
        {
            puts("Too many failed attempts. Please try again later.");
            sleep(1);
            return 0;
        }
        puts("Login failed. Try again.");
        goto retry_login;
    }
}
