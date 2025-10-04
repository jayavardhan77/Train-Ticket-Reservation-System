# Train-Ticket-Reservation-System
Developed a CLI-based train ticket booking system in C using linked lists and file handling. Added user/admin login and efficient seat allocation. Improved debugging and modular programming skills while handling a larger codebase.

## Features

-   **User Authentication**: Secure sign-up and sign-in system.
-   **Admin Panel**: An "officer" user can add, delete, and view train schedules.
-   **Ticket Booking**: Users can search for trains and book multiple seats.
-   **Ticket Cancellation**: Users can cancel a specific seat from their booking.
-   **Booking Details**: Users can view a list of all their reservations.
-   **Data Persistence**: All user, train, and booking data is saved to text files.

## How to Compile and Run

1.  **Prerequisites**: You need `gcc` and `make` installed.

2.  **Compile the project**:
    ```bash
    make -f Makefile.mak
    ```

3.  **Run the application**:
    ```bash
    ./myirctc
    ```

4.  **Admin Login**:
    -   **Username**: `officer`
    -   **Password**: The password you set for the officer during sign-up.
