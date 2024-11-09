#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 100
#define BASIC_PAY 20000

struct Employee {
    char id[10];
    char name[20];
    char gender;
    char role[30];
    int experience;
    float pay;
};

void printStd(struct Employee employee);
void readData(struct Employee record[], int *count);
void addRecord(struct Employee record[], int *count);
void searchByID(char reg[], struct Employee rec[], int count);
void showAllRecord(struct Employee rec[], int count);
void employeesWithPayLessThanBasicPay(struct Employee rec[], int count);
void giveBonus(struct Employee rec[], int count);

int main(int argc, char *argv[]) {
    
    struct Employee employees[MAX_SIZE];
    int employeesCount = 0;

    readData(employees, &employeesCount);

    while(1) {
        int choice;
        printf("1. Add a record\n");
        printf("2. Search a record by ID\n");
        printf("3. Show all records\n");
        printf("4. Show employees having pay less then basic pay (20000)\n");
        printf("5. Give bonus to employees\n");
        printf("0. Save and Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            addRecord(employees, &employeesCount);
            break;

        case 2: {
            char id[10];
            printf("Enter ID: ");
            scanf("%s", id);
            searchByID(id, employees, employeesCount);
            break;
        }
        
        case 3:
            showAllRecord(employees, employeesCount);
            break;

        case 4:
            employeesWithPayLessThanBasicPay(employees, employeesCount);
            break;

        case 5:
            giveBonus(employees, employeesCount);
            printf("Bonus given successfully.\n");
            break;

        case 0:
            printf("Exiting...\n");
            return 0;

        default:
            printf("Invalid choice.\n");
            break;
        }

    }
}

void printStd(struct Employee employee)
{
    printf("ID: %s\n", employee.id);
    printf("Name: %s\n", employee.name);
    printf("Gender: %c\n", employee.gender);
    printf("Role: %s\n", employee.role);
    printf("Experience: %d\n", employee.experience);
    printf("Pay: %.2f\n", employee.pay);
}

void readData(struct Employee record[], int *count)
{
    FILE * file = fopen("task8.txt", "r");
    if(!file) {
        printf("Error opening file.\n");
        exit(-1);
    }

    while (fscanf(file, "%s %s %c %s %d %f", record[*count].id, record[*count].name, &record[*count].gender, record[*count].role, &record[*count].experience, &record[*count].pay) == 6) {
        (*count)++;
    }

    fclose(file);
}

void addRecord(struct Employee record[], int *count)
{
    FILE * file = fopen("task8.txt", "a");
    if(!file) {
        printf("Error opening file.\n");
        exit(-1);
    }

    printf("Enter ID: ");
    scanf("%s", record[*count].id);
    printf("Enter Name: ");
    scanf("%s", record[*count].name);
    printf("Enter Gender: ");
    scanf(" %c", &record[*count].gender);
    printf("Enter Role: ");
    scanf("%s", record[*count].role);
    printf("Enter Experience: ");
    scanf("%d", &record[*count].experience);
    printf("Enter Pay: ");
    scanf("%f", &record[*count].pay);
    fprintf(file, "%s %s %c %s %d %.2f\n",
            record[*count].id,
            record[*count].name,
            record[*count].gender,
            record[*count].role,
            record[*count].experience,
            record[*count].pay);
    (*count)++;

    printf("Record added successfully.\n");

    fclose(file);
}

void searchByID(char reg[], struct Employee rec[], int count)
{
    for(int i = 0; i < count; i++) {
        if(strcmp(reg, rec[i].id) == 0) {
            printStd(rec[i]);
            return;
        }
    }
    printf("Record not found.\n");
}

void showAllRecord(struct Employee rec[], int count)
{
    if(count == 0) {
        printf("No record found.\n");
    }
    
    for(int i = 0; i < count; i++) {
        printf("Employee %d:\n", i + 1);
        printStd(rec[i]);
        printf("\n");
    }
}

void employeesWithPayLessThanBasicPay(struct Employee rec[], int count) {
    int flag = 0;
    for(int i = 0; i < count; i++) {
        if(rec[i].pay < BASIC_PAY) {
            printStd(rec[i]);
            flag = 1;
        }
    }

    if(flag == 0) {
        printf("No record found.\n");
    }
}

void giveBonus(struct Employee rec[], int count) {
    for(int i = 0; i < count; i++) {
        if(rec[i].pay > 10000 && rec[i].pay < 30000) {
            rec[i].pay = rec[i].pay + (0.1 * rec[i].pay);
        } else if(rec[i].pay > 30000 && rec[i].pay < 50000) {
            rec[i].pay = rec[i].pay + (0.2 * rec[i].pay);
        } else if(rec[i].pay > 50000) {
            rec[i].pay = rec[i].pay + (0.3 * rec[i].pay);
        }
    }
}