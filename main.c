#include <stdio.h>
#include <string.h>

// Storing the information in struct
struct expenses{
    char date[20];
    char category[30];
    char descr[50];
    float amt;
};
typedef struct expenses EXPENSES;

// Adding expenses into the file
void addExpense()
{
    EXPENSES exp;  
    printf("Enter date (dd-mm-yyyy): ");
    scanf("%s", exp.date);

    printf("Enter category: ");
    scanf("%s", exp.category);
    
    printf("Enter description: ");
    getchar();      // removes extra '/n' from buffer due to scanf (for 'opt')
    fgets(exp.descr, 50, stdin);
    exp.descr[strcspn(exp.descr, "\n")] = '\0';  // replaces the newline char at the end of descr with \0 (end of string); otherwise csv will have a line break in the middle of the row
    // 'strcspn' returns the index of '\n' and we replace it with '\0'; second argument must be a str

    printf("Enter amount: ");
    scanf("%f", &exp.amt);

    FILE *fp = fopen("expense_tracker.csv", "a");
    if (fp == NULL)
    {
        printf("\nFailed to open the file\n\n");
        return;
    }
    fprintf(fp, "%s,%s,%s,%.2f\n", exp.date, exp.category, exp.descr, exp.amt);
    fclose(fp);
}

// Viewing expenses
void viewExpenses()
{
    EXPENSES exp;
    FILE *fp = fopen("expense_tracker.csv", "r");
    if (fp == NULL)
    {
        printf("\nFailed to open the file\n\n");
        return;
    }

    int count = 1;
    int found = 0;   // checks if expenses are present before viewing or deleting expenses

    char line[200];
    while (fgets(line, 200, fp) != NULL)    // to read each line 
    // fgets returns NULL when end of file is reached
    {
        found = 1;
        sscanf(line, "%[^,],%[^,],%[^,],%f", exp.date, exp.category, exp.descr, &exp.amt);   // to extract the individual fields ('[^,]' - reads till ',')
        // first argument - string that needs to be parsed
        printf("\n ==================== \n");
        printf("%d.\nDate : %s\nCategory : %s\nDescription : %s\nAmount : %.2f\n", count, exp.date, exp.category, exp.descr, exp.amt);
        printf(" ==================== \n");
        count++;
    }
    printf("\n");

    if (found == 0)
    {
        printf("\nNo expenses present. Add expenses to continue.\n\n");
        fclose(fp);
        return;
    }
    fclose(fp);
}

// Adding the total expense
float totalExpenses()
{
    EXPENSES exp;
    float sum = 0;
    FILE *fp = fopen("expense_tracker.csv", "r");
    if (fp == NULL)
    {
        printf("\nFile cannot be opened\n\n");
        return 0;
    }

    char line[200];
    while (fgets(line, 200, fp) != NULL)
    {
        sscanf(line, "%*[^,],%*[^,],%*[^,],%f", &exp.amt);  // %*[^,] - reads till ',' and then discards it; reading only amount, hence only &exp.amt
        sum += exp.amt;
    }
    fclose(fp);
    return sum;
}

// Adding the total expenses based on category
void totalCategories()
{
    EXPENSES exp;
    char categories[100][30];  // stores upto 100 strings of 30 chars 
    float total[100];
    int count = 0;

    FILE *fp = fopen("expense_tracker.csv", "r");
    if (fp == NULL)
    {
        printf("\nFile cannot be opened\n\n");
        return;
    }

    char line[200];
    while (fgets(line, 200, fp) != NULL)
    {
        int found = 0;   // reset for every line
        sscanf(line, "%*[^,],%[^,],%*[^,],%f",exp.category, &exp.amt);
        for (int i=0; i<count; i++)
        {
            if (strcmp(categories[i], exp.category) == 0)
            {
                total[i] += exp.amt;
                found = 1;
                break;
            }
        }
        if (found == 0)
        {
            strcpy(categories[count], exp.category);
            total[count] = exp.amt;
            count++;
        }
    }

    printf("\nThe total expenses per category is as follows :\n\n");
    for (int i=0; i<count; i++)
    {
        printf("%s : %.2f\n", categories[i], total[i]);
    }
    printf("\n");
    fclose(fp); 
}

// Counting the number of expenses present in the file
int countExpenses()
{
    FILE *fp = fopen("expense_tracker.csv", "r");
    if (fp == NULL)
        return 0;

    char line[200];
    int count = 0;
    while (fgets(line, 200, fp) != NULL)
        count++;

    fclose(fp);    
    return count;
}

// Deleting an expense
void deleteExpense(int choice)
{
    FILE *fp1 = fopen("expense_tracker.csv", "r");
    FILE *fp2 = fopen("temp.csv", "w");
    if (fp1 == NULL || fp2 == NULL)
    {
        printf("\nFile cannot be opened\n\n");
        return;
    }

    char line[200];
    int current = 1;
    while (fgets(line, 200, fp1) != NULL)
    {
        if (current != choice)
            fprintf(fp2, "%s", line);
        current++;
    }

    fclose(fp1);
    fclose(fp2);
    remove("expense_tracker.csv");    // to delete a file
    rename("temp.csv", "expense_tracker.csv");   // to rename a file - rename(old, new)
}

int main()
{
    int opt;
    printf("\n---------- EXPENSE TRACKER ----------\n\n");
    printf("WELCOME!\n\n");
    printf("This tool helps you track your daily expenses.\n");
    printf("You can add expenses, view them, see totals, analyze spending by category and can delete expenses as well.\n\n");
    // to ensure that the file exists 
    FILE *fp = fopen("expense_tracker.csv", "a");
    fclose(fp);

    while (1)
    {
        printf("Enter you choice:\n");
        printf("1. Add Expense\n2. View Expenses\n3. Total of all Expenses (Sum)\n4. Total expenses per category\n5. Delete Expense\n6. Exit\n");
        scanf("%d", &opt);
        switch (opt)
        {
            case 1:
            {
                addExpense();
                printf("\nExpense added successfully!\n\n");
                break;
            }

            case 2:
            {
                viewExpenses();
                break;
            }

            case 3:
            {
                float sum;
                sum = totalExpenses();
                printf("\nTotal of all expenses: %.2f\n\n", sum);
                break;
            }

            case 4:
            {
                totalCategories();
                break;
            }

            case 5:
            {
                int choice, count;
                viewExpenses();
                count = countExpenses();
                
                // if the entered choice is negative or greater than the number of expenses present in the file
                int valid = 0;
                do 
                {
                    printf("Enter the number of the expense to delete: ");
                    scanf("%d", &choice);
                    if (choice < 1 || choice > count)
                        printf("\nWrong choice, choose again to delete the expense...\n\n");
                    else
                        valid = 1;
                } while (valid == 0);
                
                deleteExpense(choice);
                printf("\nExpense deleted successfully!\n\n");
                break;
            }

            case 6:
            {
                printf("\nExiting.....\n\n");
                printf("THANK YOU!\n\n");
                return 0;
            }

            default:
            {
                // wrong input entered by the user
                printf("\nInvalid choice, choose again...\n\n");
                break;
            }
        }
        printf("--------------------\n\n");
    }
    return 0;
}



