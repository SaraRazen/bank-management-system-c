🏦 Bank Account Management System (C)

A console-based bank account management system written in C, built as a first-year project in Computer & Communications Engineering (CCE). It stores all data in plain text files and supports the everyday operations of a small bank: creating accounts, deposits, withdrawals, transfers, searching, sorting, and transaction reports.

Features
Login: staff must authenticate against a users file before accessing the menu
Add account: with input validation
Name: letters and spaces only
Account number: exactly 10 digits and unique
Mobile: 11 digits, unique, Egyptian format (starts with 01 followed by 0, 1, 2, or 5)
Email: unique, with a yahoo.com, gmail.com, or outlook.com domain
Opening date is recorded automatically
Delete account: only allowed when the balance is zero
Modify account: update name, mobile number, or email, with a confirmation before saving
Search: by account number
Advanced search: by keyword across name (partial match), mobile, email, account number, or opening month/year
Withdraw / Deposit: per-transaction limit below 10,000, with a confirm/undo step
Transfer: move money between two accounts
Report: shows the last 5 transactions of an account
Print: list all accounts sorted by name, balance, or date opened
Tech Concepts Used
Structs and arrays of structs
File I/O (fopen, fgets, fprintf, fscanf)
String handling and parsing (strtok, strcmp, strstr, atoi, atof)
Input validation with ctype.h
Bubble sort on structured data
Windows API (GetSystemTime) for the current date
Getting Started
Requirements
Windows (the code uses Windows.h and hard-coded C:\Project\ paths)
A C compiler such as GCC (MinGW) or Code::Blocks
Setup
Create the folder C:\Project\.
Inside it, create these files: users.txt: one username password pair per line
admin 1234

accounts.txt: one account per line (can start empty)

1234567890,Ahmed Ali,ahmed@gmail.com,1500.00,01012345678,11-2023

Format: account_number,name,email,balance,mobile,month-year

Compile and run:
bash
gcc main.c -o bank.exe
bank.exe

Each account also gets its own transaction log at C:\Project\<account_number>.txt, which the Report option reads.

Menu
1-Add          2-Delete        3-Modify
4-Search       5-Advanced search   6-Withdraw
7-Deposit      8-Transfer      9-Report
10-Print       11-Quit
Known Limitations & Future Improvements

This was an early learning project, so there are things I would do differently today:

Windows-only with hard-coded file paths. Make paths configurable and portable.
Passwords are stored in plain text. They should be hashed.
gets() is used for input. It is unsafe and removed from modern C. It should be replaced with fgets().
Withdrawals don't check for insufficient balance, and transfers don't enforce a limit.
Recursive menu calls (MENU2() calling itself) could be replaced with a loop.
Some validation logic can be tightened (e.g., name validation, email parsing edge cases).
Split the single file into modules (accounts.c, auth.c, utils.c) and add unit tests.
