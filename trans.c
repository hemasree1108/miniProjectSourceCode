// Advanced Bank Account Management System using Random Access File

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct clientData
{
    unsigned int acctNum;
    char lastName[15];
    char firstName[10];
    double balance;
};

unsigned int enterChoice(void);

void textFile(FILE *readPtr);
void updateRecord(FILE *fPtr);
void newRecord(FILE *fPtr);
void deleteRecord(FILE *fPtr);

/* NEW FEATURES */
void searchRecord(FILE *fPtr);
void displayAllRecords(FILE *fPtr);
void depositMoney(FILE *fPtr);
void withdrawMoney(FILE *fPtr);

int main()
{
    FILE *cfPtr;
    unsigned int choice;

    if ((cfPtr = fopen("credit.dat", "rb+")) == NULL)
    {
        cfPtr = fopen("credit.dat", "wb+");

        if (cfPtr == NULL)
        {
            printf("File could not be created.\n");
            exit(1);
        }

        struct clientData blankClient = {0, "", "", 0.0};

        for (int i = 0; i < 100; i++)
        {
            fwrite(&blankClient, sizeof(struct clientData), 1, cfPtr);
        }
    }

    while ((choice = enterChoice()) != 9)
    {
        switch (choice)
        {
        case 1:
            textFile(cfPtr);
            break;

        case 2:
            updateRecord(cfPtr);
            break;

        case 3:
            newRecord(cfPtr);
            break;

        case 4:
            deleteRecord(cfPtr);
            break;

        case 5:
            searchRecord(cfPtr);
            break;

        case 6:
            displayAllRecords(cfPtr);
            break;

        case 7:
            depositMoney(cfPtr);
            break;

        case 8:
            withdrawMoney(cfPtr);
            break;

        default:
            printf("Invalid choice.\n");
        }
    }

    fclose(cfPtr);

    return 0;
}

/* MENU FUNCTION */

unsigned int enterChoice(void)
{
    unsigned int choice;

    printf("\n========= BANK MANAGEMENT SYSTEM =========\n");
    printf("1 - Create text file\n");
    printf("2 - Update account\n");
    printf("3 - Add new account\n");
    printf("4 - Delete account\n");
    printf("5 - Search account\n");
    printf("6 - Display all accounts\n");
    printf("7 - Deposit money\n");
    printf("8 - Withdraw money\n");
    printf("9 - Exit\n");
    printf("Enter your choice : ");

    scanf("%u", &choice);

    return choice;
}

/* CREATE TEXT FILE */

void textFile(FILE *readPtr)
{
    FILE *writePtr;

    struct clientData client = {0, "", "", 0.0};

    rewind(readPtr);

    if ((writePtr = fopen("accounts.txt", "w")) == NULL)
    {
        printf("File could not be opened.\n");
    }
    else
    {
        fprintf(writePtr, "%-10s%-15s%-15s%-10s\n",
                "Acc No", "Last Name", "First Name", "Balance");

        while (fread(&client, sizeof(struct clientData), 1, readPtr))
        {
            if (client.acctNum != 0)
            {
                fprintf(writePtr,
                        "%-10u%-15s%-15s%-10.2f\n",
                        client.acctNum,
                        client.lastName,
                        client.firstName,
                        client.balance);
            }
        }

        fclose(writePtr);

        printf("accounts.txt file created successfully.\n");
    }
}

/* UPDATE ACCOUNT */

void updateRecord(FILE *fPtr)
{
    unsigned int account;
    double transaction;

    struct clientData client = {0, "", "", 0.0};

    printf("Enter account number to update : ");
    scanf("%u", &account);

    fseek(fPtr,
          (account - 1) * sizeof(struct clientData),
          SEEK_SET);

    fread(&client, sizeof(struct clientData), 1, fPtr);

    if (client.acctNum == 0)
    {
        printf("Account does not exist.\n");
    }
    else
    {
        printf("\nCurrent Balance : %.2f\n", client.balance);

        printf("Enter transaction amount (+/-) : ");
        scanf("%lf", &transaction);

        client.balance += transaction;

        fseek(fPtr,
              sizeof(struct clientData),
              SEEK_CUR);

        fwrite(&client,
               sizeof(struct clientData),
               1,
               fPtr);

        printf("Updated Balance : %.2f\n", client.balance);
    }
}

/* ADD NEW ACCOUNT */

void newRecord(FILE *fPtr)
{
    struct clientData client = {0, "", "", 0.0};

    unsigned int accountNum;

    printf("Enter new account number (1-100) : ");
    scanf("%u", &accountNum);

    fseek(fPtr,
          (accountNum - 1) * sizeof(struct clientData),
          SEEK_SET);

    fread(&client,
          sizeof(struct clientData),
          1,
          fPtr);

    if (client.acctNum != 0)
    {
        printf("Account already exists.\n");
    }
    else
    {
        printf("Enter lastname firstname balance : ");

        scanf("%14s %9s %lf",
              client.lastName,
              client.firstName,
              &client.balance);

        client.acctNum = accountNum;

        fseek(fPtr,
              (accountNum - 1) * sizeof(struct clientData),
              SEEK_SET);

        fwrite(&client,
               sizeof(struct clientData),
               1,
               fPtr);

        printf("Account added successfully.\n");
    }
}

/* DELETE ACCOUNT */

void deleteRecord(FILE *fPtr)
{
    struct clientData client;
    struct clientData blankClient = {0, "", "", 0.0};

    unsigned int accountNum;

    printf("Enter account number to delete : ");
    scanf("%u", &accountNum);

    fseek(fPtr,
          (accountNum - 1) * sizeof(struct clientData),
          SEEK_SET);

    fread(&client,
          sizeof(struct clientData),
          1,
          fPtr);

    if (client.acctNum == 0)
    {
        printf("Account does not exist.\n");
    }
    else
    {
        fseek(fPtr,
              (accountNum - 1) * sizeof(struct clientData),
              SEEK_SET);

        fwrite(&blankClient,
               sizeof(struct clientData),
               1,
               fPtr);

        printf("Account deleted successfully.\n");
    }
}

/* SEARCH ACCOUNT */

void searchRecord(FILE *fPtr)
{
    struct clientData client;

    unsigned int accountNum;

    printf("Enter account number to search : ");
    scanf("%u", &accountNum);

    fseek(fPtr,
          (accountNum - 1) * sizeof(struct clientData),
          SEEK_SET);

    fread(&client,
          sizeof(struct clientData),
          1,
          fPtr);

    if (client.acctNum == 0)
    {
        printf("Account not found.\n");
    }
    else
    {
        printf("\nAccount Found\n");

        printf("Account No : %u\n", client.acctNum);
        printf("Last Name  : %s\n", client.lastName);
        printf("First Name : %s\n", client.firstName);
        printf("Balance    : %.2f\n", client.balance);
    }
}

/* DISPLAY ALL RECORDS */

void displayAllRecords(FILE *fPtr)
{
    struct clientData client = {0, "", "", 0.0};

    rewind(fPtr);

    printf("\n%-10s%-15s%-15s%-10s\n",
           "Acc No",
           "Last Name",
           "First Name",
           "Balance");

    while (fread(&client,
                 sizeof(struct clientData),
                 1,
                 fPtr))
    {
        if (client.acctNum != 0)
        {
            printf("%-10u%-15s%-15s%-10.2f\n",
                   client.acctNum,
                   client.lastName,
                   client.firstName,
                   client.balance);
        }
    }
}

/* DEPOSIT MONEY */

void depositMoney(FILE *fPtr)
{
    struct clientData client;

    unsigned int accountNum;
    double amount;

    printf("Enter account number : ");
    scanf("%u", &accountNum);

    fseek(fPtr,
          (accountNum - 1) * sizeof(struct clientData),
          SEEK_SET);

    fread(&client,
          sizeof(struct clientData),
          1,
          fPtr);

    if (client.acctNum == 0)
    {
        printf("Account not found.\n");
    }
    else
    {
        printf("Enter amount to deposit : ");
        scanf("%lf", &amount);

        client.balance += amount;

        fseek(fPtr,
              sizeof(struct clientData),
              SEEK_CUR);

        fwrite(&client,
               sizeof(struct clientData),
               1,
               fPtr);

        printf("Deposit successful.\n");
        printf("New Balance : %.2f\n", client.balance);
    }
}

/* WITHDRAW MONEY */

void withdrawMoney(FILE *fPtr)
{
    struct clientData client;

    unsigned int accountNum;
    double amount;

    printf("Enter account number : ");
    scanf("%u", &accountNum);

    fseek(fPtr,
          (accountNum - 1) * sizeof(struct clientData),
          SEEK_SET);

    fread(&client,
          sizeof(struct clientData),
          1,
          fPtr);

    if (client.acctNum == 0)
    {
        printf("Account not found.\n");
    }
    else
    {
        printf("Enter amount to withdraw : ");
        scanf("%lf", &amount);

        if (amount > client.balance)
        {
            printf("Insufficient balance.\n");
        }
        else
        {
            client.balance -= amount;

            fseek(fPtr,
                  sizeof(struct clientData),
                  SEEK_CUR);

            fwrite(&client,
                   sizeof(struct clientData),
                   1,
                   fPtr);

            printf("Withdrawal successful.\n");
            printf("Remaining Balance : %.2f\n", client.balance);
        }
    }
}
