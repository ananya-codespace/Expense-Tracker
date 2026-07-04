# Expense Tracker

A simple command-line expense tracker built in C to help track daily spending.

## Features
- Add new expenses with date, category, description, and amount
- View all recorded expenses
- Calculate total spending
- View total expenses grouped by category
- Delete an expense

## Tech Stack
- Language: C

## How to Run
```bash
gcc expense_tracker.c -o expense_tracker
./expense_tracker
```

## Usage
1. Choose "Add Expense" and enter date (dd-mm-yyyy), category, description, and amount
2. Choose "View Expenses" to see all entries
3. Choose "Total of all Expenses" to calculate total spending
4. Choose "Total expenses per category" to see spending grouped by category
5. Choose "Delete Expense" to remove a specific entry
6. Choose "Exit" to close the program

## Output
- Expenses are stored in `expense_tracker.csv`, created automatically on first run
- Data is saved in the format: `date,category,description,amount`
- All output is displayed directly in the terminal

## What I Learned
- File I/O in C (`fopen`, `fgets`, `fprintf`, `remove`, `rename`)
- Parsing CSV lines with string functions like `sscanf` and `strcspn` and format specifiers like `%[^,]` and `%*[^,]`
- Implementing delete-by-rewrite using a temporary file