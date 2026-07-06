# Expense Tracker

A simple command-line expense tracker built in C to help track daily spending.

## Features
- Add new expenses with date, category, description, and amount
- View all recorded expenses
- Calculate total spending
- View total expenses grouped by category
- Delete an expense

## Tech Stack
- Language: `C`
- Libraries: `string.h`

## How to Run
```bash
gcc main.c -o expense_tracker
./expense_tracker
```

## Usage
1. Choose "Add Expense" and enter date (dd-mm-yyyy), category, description, and amount
2. Choose "View Expenses" to see all entries
3. Choose "Total of all Expenses" to calculate total spending
4. Choose "Total expenses per category" to see spending grouped by category
5. Choose "Delete Expense" to remove a specific entry
6. Choose "Exit" to close the program

## How It Works
- Each expense is stored as a line in `expense_tracker.csv` in the format `date,category,description,amount`
- Reading back a line uses `sscanf` with the `%[^,]` specifier, which reads a field up to the next comma
- Totaling by category keeps a running list of categories seen so far — if a category already exists, its total is updated; otherwise, it's added as a new entry
- Deleting an expense works by reading the file line by line into a temporary file, skipping the one to delete, then replacing the original file with the temp file

## Output
- Expenses are stored in `expense_tracker.csv`, created automatically on first run
- Each expense's details are displayed in a formatted block
- All output is displayed directly in the terminal

## What I Learnt
- File I/O in C (`fopen`, `fgets`, `fprintf`, `remove`, `rename`)
- Parsing CSV lines with string functions like `sscanf` and `strcspn` and format specifiers like `%[^,]` and `%*[^,]`
- Implementing delete-by-rewrite using a temporary file
