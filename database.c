#include <stdio.h>
#include <string.h>
#include <Kernel/stdbool.h>
#include "readfile.h"
#define MAXNAMELENGTH 64
#define MAXEMPLOYEES 1024

char *filename; // Declare the variable filename

// Define the structure of the employee
struct employee
{
    int id;
    int salary;
    char firstName[MAXNAMELENGTH];
    char lastName[MAXNAMELENGTH];
};

struct employee database[MAXEMPLOYEES]; // Array to store all the employees 
int employeeCount = 0; // Number of employees in the database

// Sorting the database by ID
void SortByID()
{
    struct employee temp;
    for (int i = 0; i < employeeCount; i++)
    {
        for (int j = i + 1; j < employeeCount; j++)
        {
            if (database[i].id > database[j].id)
            {
                temp = database[i];
                database[i] = database[j];
                database[j] = temp;
            }
        }
    }
}


//  Functions for adding, displaying and searching an employee in the database
int SearchByID(int id)
{
    // Doing linear search
    for (int i = 0; i < employeeCount; i++)
    {
        if (database[i].id == id)
        {
            return i;
        }
    }
    return -1;
}

// Function to print the database
void PrintDatabase(struct employee employees[], int employeeCount)
{
    printf("\nName\t\t\t\tSALARY\tID\n");
    printf("----------------------------------------------\n");
    for (int i = 0; i < employeeCount; i++)
    {
        printf("%-15s\t%-15s\t%d\t%d\n", employees[i].firstName,employees[i].lastName, employees[i].salary, employees[i].id);
    }
    printf("----------------------------------------------\n");
    printf(" Number of Employees (%d)\n", employeeCount);    
}

// Function to search an employee by first name
int SearchByFirstName(char *firstName)
{
    for (int i = 0; i < employeeCount; i++)
    {
        if (strcmp(database[i].firstName, firstName) == 0)
        {
            return i;
        }
    }
    return -1;
}

// Function to add an employee to the database.
int AddEmployee(int id, int salary, char *firstName, char *lastName)
{
    if (employeeCount >= MAXEMPLOYEES)
    {
        return -1;
    }
    database[employeeCount].id = id;
    database[employeeCount].salary = salary;
    strcpy(database[employeeCount].firstName, firstName);
    strcpy(database[employeeCount].lastName, lastName);
    employeeCount++;
    return 0;
}

// Function to read the employee data from a file
void ReadEmployeeData(char *filename)
{
    printf("File %s has been read.\n", filename);
    
    char buffer[1024];
    int id, salary;
    char firstName[MAXNAMELENGTH], lastName[MAXNAMELENGTH];
    int open_file(char *filename); // Declare the function open_file

    if (open_file(filename) == -1)
    {
        printf("Error opening file\n");
        return;
    }
    while (read_line(buffer, 1024) != -1)
    {
        sscanf(buffer, "%d %s %s %d", &id, firstName, lastName, &salary);
        AddEmployee(id, salary, firstName, lastName);
    }
    close_file();
}

// Function to generate a random ID number for new employees
int generateID() {
    int maxID = 0;
    for (int i = 0; i < employeeCount; i++) {
        if (database[i].id > maxID) {
            maxID = database[i].id;
        }
    }
    return maxID + 1;
}

// Function to check if the ID is already used
bool isIDUsed(int id) {
    int index = SearchByID(id);
    return (index != -1);
}

//Function to remove the employee
int RemoveEmployee(int id)
{
    int index = SearchByID(id);
    if (index == -1)
    {
        return -1;
    }
    for (int i = index; i < employeeCount - 1; i++)
    {
        database[i] = database[i + 1];
    }
    employeeCount--;
    return 0;
}

//Function to update an employee
int UpdateEmployee(int index)
{
    int option;
    int newSalary;
    char newFirstName[MAXNAMELENGTH], newLastName[MAXNAMELENGTH];
    int newID;
    printf("Which field do you want to update?\n");
    printf("\t(1) First Name\n");
    printf("\t(2) Last Name\n");
    printf("\t(3) Salary\n");
    printf("\t(4) Employee ID\n");
    printf("\t(5) All fields\n");
    printf("Enter your choice: ");
    scanf("%d", &option);
    switch (option)
    {
        case 1:
            printf("Enter new First Name: ");
            scanf("%s", newFirstName);
            strcpy(database[index].firstName, newFirstName);
            printf("Employee updated successfully\n");
            break;
        case 2:
            printf("Enter new Last Name: ");
            scanf("%s", newLastName);
            strcpy(database[index].lastName, newLastName);
            printf("Employee updated successfully\n");
            break;
        case 3:
            printf("Enter new Salary: ");
            scanf("%d", &newSalary);
            database[index].salary = newSalary;
            printf("Employee updated successfully\n");
            break;
        case 4:
            printf("Enter new Employee ID: ");
            scanf("%d", &newID);
            // check if the new ID already exists
            do {
                if (isIDUsed(newID)) {
                    printf("ID already exists.\nPlease enter a new ID: ");
                    scanf("%d", &newID);
                } else {
                    database[index].id = newID;
                    SortByID();
                    printf("Employee updated successfully\n");
                    break;
                }
            } while(1);
            break;
        case 5:
            printf("Enter new First Name: ");
            scanf("%s", newFirstName);
            strcpy(database[index].firstName, newFirstName);
            printf("Enter new Last Name: ");
            scanf("%s", newLastName);
            strcpy(database[index].lastName, newLastName);
            printf("Enter new Salary: ");
            scanf("%d", &newSalary);
            do
            {
                if (newSalary < 30000 || newSalary > 150000)
                {
                    printf("Invalid Salary. Salary should be 30000 to 150000.\n");
                    printf("Please enter a new Salary: ");
                    scanf("%d", &newSalary);
                }
                else
                {
                    database[index].salary = newSalary;
                    break;
                }
            } while (1);
            
            printf("Enter new Employee ID: ");
            scanf("%d", &newID);
            do {
                if (isIDUsed(newID)) {
                    printf("ID already exists.\nPlease enter a new ID: ");
                    scanf("%d", &newID);
                } 
                else if(newID < 100000 || newID > 999999) {
                    printf("Invalid ID.\nPlease enter a new ID: ");
                    scanf("%d", &newID);
                } 
                else {
                    database[index].id = newID;
                    SortByID();
                    printf("Employee updated successfully\n");
                    break;
                }
            } while(1);
            printf("Employee updated successfully\n");
            break;
        default:
            printf("Invalid Input\n");
            break;
    }
    return 1;
}


// min heapify
void minHeapify(struct employee Mthsalary[], int i, int m)
{
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    int smallest = i;
    if (left < m && Mthsalary[left].salary < Mthsalary[i].salary)
    {
        smallest = left;
    }
    if (right < m && Mthsalary[right].salary < Mthsalary[smallest].salary)
    {
        smallest = right;
    }
    if (smallest != i)
    {
        struct employee temp = Mthsalary[i];
        Mthsalary[i] = Mthsalary[smallest];
        Mthsalary[smallest] = temp;
        minHeapify(Mthsalary, smallest, m);
    }
}

// Function to find First Mth highest salary
// Using min heap to find the Mth highest salary
int MthHighestSalary(int m)
{
    int i, j, temp;
    //create an array to store the salary of the employees
    struct employee Mthsalary[m];
    int choice;
    for (i = 0; i < m; i++)
    {
        Mthsalary[i] = database[i];
    }
    //build a min heap
    for (i = m / 2 - 1; i >= 0; i--)
    {
        minHeapify(Mthsalary, i, m);
    }
    //iterate through the rest of the database
    for (i = m; i < employeeCount; i++)
    {
        if (database[i].salary > Mthsalary[0].salary)
        {
            Mthsalary[0] = database[i];
            minHeapify(Mthsalary, 0, m);
        }
    }
    //sort the array by salary
    for (i = 0; i < m; i++)
    {
        for (j = i + 1; j < m; j++)
        {
            if (Mthsalary[i].salary < Mthsalary[j].salary)
            {
                temp = Mthsalary[i].salary;
                Mthsalary[i].salary = Mthsalary[j].salary;
                Mthsalary[j].salary = temp;
            }
        }
    }
    printf("\nName\t\t\t\tSALARY\t   ID\n");
    printf("----------------------------------------------\n");
    for (i = 0; i < m; i++)
    {
        printf("%-15s\t%-15s\t%d\t%d\n", Mthsalary[i].firstName, Mthsalary[i].lastName, Mthsalary[i].salary, Mthsalary[i].id);
    }
    printf("----------------------------------------------\n");
    return 0;
}



// Function to find all with the same last name(Case insensitive)
int SearchTheSameLastName(char *lastName)
{
    //declare an array to store the index of the employee with same last name
    int index[MAXEMPLOYEES];
    int count = 0;
    
    // iterate through the database to find the employee with the same last name
    for (int i = 0; i < employeeCount; i++)
    {
        if (strcasecmp(database[i].lastName, lastName) == 0)
        {
            index[count] = i;
            count++;
        }
    }

    // print the result
    if (count == 0)
    {
        printf("Not found\n");
    }
    else
    {
        printf("\nName\t\t\t\tSALARY\t   ID\n");
        printf("----------------------------------------------\n");
        for (int i = 0; i < count; i++)
        {
            printf("%-15s\t%-15s\t%d\t%d\n", database[index[i]].firstName, database[index[i]].lastName, database[index[i]].salary, database[index[i]].id);
        }
        printf("----------------------------------------------\n");
    }
    return 0;
}


int confirm; // Declare the variable confirm

int main(int argc, char *argv[])
{
    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    filename = argv[1];
    int choice;
    int id, salary;
    char firstName[MAXNAMELENGTH], lastName[MAXNAMELENGTH];
    int index;
    int m;
    ReadEmployeeData(filename);
    SortByID();

    while (1)
    {
        printf("1. Print the Database\n");
        printf("2. Lookup employee by ID\n");
        printf("3. Lookup employee by last name\n");
        printf("4. Add an Employee\n");
        printf("5. Quit\n");
        printf("6. Remove an Employee\n");
        printf("7. Update an Employee\n");
        printf("8. Find Mth highest salary\n");
        printf("9. Find all with the same last name\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice)
        {
            case 1:
                PrintDatabase(database, employeeCount);
                break;
            case 2: 
                printf("Enter ID: ");
                scanf("%d", &id);
                index = SearchByID(id);
                if (index == -1)
                {
                    printf("Not found\n");
                }
                else
                {
                    printf("\nName\t\t\t\tSALARY\t   ID\n");
                    printf("----------------------------------------------\n");
                    printf("%-15s\t%-15s\t%d\t%d\n", database[index].firstName,database[index].lastName,database[index].salary, database[index].id);
                    printf("----------------------------------------------\n");
                }
                break;
            case 3:
                printf("Enter First Name: ");
                scanf("%s", firstName);
                index = SearchByFirstName(firstName);
                if (index == -1)
                {
                    printf("Not found\n");
                }
                else
                {
                    printf("\nName\t\t\t\tSALARY\t   ID\n");
                    printf("----------------------------------------------\n");
                    printf("%-15s\t%-15s\t%d\t%d\n", database[index].firstName,database[index].lastName,database[index].salary, database[index].id);
                    printf("----------------------------------------------\n");
                }
                break;
            case 4:                             
                do {
                    printf("Enter First Name: ");
                    scanf("%s", firstName);
                    // The condition checks if the input is empty or longer than allowed
                    if (firstName[0] == '\0' || strlen(firstName) > 64) {
                        printf("Invalid input. Please enter again.\n");
                    } else {
                        break; // Exit the loop if input is valid
                    }
                } while(1);
                

                do {
                    printf("Enter Last Name: ");
                    scanf("%s", lastName);
                    if(lastName[0] == '\0' || strlen(lastName) > 64) 
                    {
                        printf("Invalid input. Please enter again.\n");
                    } else {
                        break;
                    }
                } while(1);

                do {
                    printf("Enter Salary (30000 to 150000): ");
                    scanf("%d", &salary);
                    if (salary > 150000 || salary < 30000)
                    {
                        printf("Invalid input. Please enter again.\n");
                    } else {
                        break;
                    }
                } while(1);
            

                printf("\nIs the following information correct?\n");
                printf("\tFirst Name: %s, \tLast Name:%s, \tSalary: %d\n", firstName, lastName, salary);
                printf("\nEnter 1 for yes, 0 for no: ");
                scanf("%d", &confirm);

                if(confirm == 1)
                {
                    int id;
                    do {
                        id = generateID();
                    } while (isIDUsed(id));

                    printf("ID of the new employee: %d\n", id);

                    AddEmployee(id, salary, firstName, lastName);
                    printf("Employee added successfully\n");
                }
                else
                {
                    printf("Employee not added\n");
                }
                break;
            case 5:
                printf("Exiting...\n");
                return 0;
                break;
            default:
                printf("Invalid Input\n");
                break;
            case 6:
                //remove employee
                printf("Enter ID: ");  
                scanf("%d", &id);
                index = SearchByID(id);
                if (index == -1)
                {
                    printf("Not found\n");
                }
                else
                {
                    printf("\nName\t\t\t\tSALARY\t   ID\n");
                    printf("----------------------------------------------\n");
                    printf("%-15s\t%-15s\t%d\t%d\n", database[index].firstName,database[index].lastName,database[index].salary, database[index].id);
                    printf("----------------------------------------------\n");
                    printf("Do you want to delete this employee? Enter 1 for Yes, or 0 for No:");
                    scanf("%d", &choice);   
                    if (choice == 1)
                    {
                        RemoveEmployee(id);
                        printf("Employee removed successfully\n");
                    }
                    else
                    {
                        printf("Employee not removed\n");
                    }
                }
                break;
            case 7:
                //update employee
                printf("Which employee do you want to update? Enter ID: ");
                scanf("%d", &id);
                index = SearchByID(id);
                if (index == -1)
                {
                    printf("Not found\n");
                    break;
                } else {
                    UpdateEmployee(index);
                }            
                break;
            case 8:
                //find Mth highest salary
                printf("Enter the value of M: ");
                scanf("%d", &m);
                do {
                    if (m > employeeCount || m < 1)
                    {
                        printf("Invalid Input\n");
                        printf("Enter the value of M: ");
                        scanf("%d", &m);
                    } else {
                        break;
                    }
                } while(1);
                MthHighestSalary(m);
                break;
            case 9:
                //find all with the same last name
                printf("Enter Last Name: ");
                scanf("%s", lastName);
                SearchTheSameLastName(lastName);
                break;
        }
    }
    return 0;
}



