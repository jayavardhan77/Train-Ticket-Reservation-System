# 🚆 Train Ticket Reservation System

A **C-based Train Ticket Reservation System** implemented with **single linked lists** and **file handling**, designed for managing train bookings efficiently in a console-based environment.

---

## 📌 Project Overview

This project simulates a train ticket booking system with functionalities similar to real-world railway booking platforms. It is implemented in **C** with a modular, multi-file architecture, providing a robust and interactive experience.

**Key Features:**
- View available trains and train details.
- Reserve tickets with user information.
- Cancel tickets and manage seat availability.
- Search and display bookings.
- Persistent data storage using file handling.

**Technology Stack:**
- **Language:** C
- **Data Structure:** Single Linked List
- **File Handling:** Read/Write booking information
- **Platform:** Console Application (Cross-platform)

---

## 🛠️ Functionalities

| Functionality | Description |
|---------------|-------------|
| `Display Trains` | List all available trains with details. |
| `Reserve Ticket` | Book a ticket for a selected train and date. |
| `Cancel Ticket` | Cancel a ticket and update seat availability. |
| `Search Booking` | Search for a reservation using ticket ID or name. |
| `File Handling` | Save and load ticket & train data for persistence. |

---

## 📂 Project Structure
Train-Ticket-Reservation-System/
│
├── header.h # Header file for function declarations and structs |
├── main.c # Main program file |
├── train_operations.c # Functions for train management
├── ticket_operations.c # Functions for ticket booking & cancellation
├── file_handling.c # Functions for persistent storage
├── Makefile # Compilation rules
└── README.md # Project documentation

## 📚 Learnings

Developed a modular C program with multiple source files.
Implemented dynamic memory management using linked lists.
Learned file handling for persistent storage of bookings.
Improved understanding of user input validation and console-based UI.
