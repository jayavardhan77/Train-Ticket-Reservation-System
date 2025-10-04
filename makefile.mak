myirctc: main.o signIn_signUp.o ticket_operations.o admin_operations.o Atoi.o save_sync.o
        gcc main.o signIn_signUp.o ticket_operations.o admin_operations.o Atoi.o save_sync.o -o myirctc

main.o: main.c
        gcc -c main.c

signIn_signUp.o: signIn_signUp.c
        gcc -c signIn_signUp.c -o signIn_signUp.o

ticket_operations.o: ticket_operations.c
        gcc -c ticket_operations.c

admin_operations.o: admin_operations.c
        gcc -c admin_operations.c

Atoi.o: Atoi.c
        gcc -c Atoi.c

save_sync.o: save_sync.c
        gcc -c save_sync.c




