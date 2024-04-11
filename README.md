# SPLab2: Employee Database Management Program



# Building and Running the Program

This is a simple Employee Database Management Program implemented in C. This guide will walk you through the process of building and running the program.

## Prerequisites

Before you can build and run the program, you need to have a C compiler installed on your system. The GNU Compiler Collection (GCC) is a popular choice and is available on most systems.

## Building the Program

First, ensure all source code files are located in the same directory. 
Then, open your terminal or command prompt, navigate to this directory, and execute the following command to compile the program:

```bash
clang database.c readfile.c -o main
```

Feel free to replace main with any name you prefer for the executable.


### Compilation
After compilation, run the program by providing a data file as a command-line argument:

```bash
./main input.txt
```

Feel free to replace "input.txt" with any file you prefer for the input.

### Program Menu

The program menu offers the following options:

1. Print the Database: Displays a table of all employees in the database, including their first name, last name, salary, and employee ID.
2. Lookup by ID: Search for an employee by their Employee ID.
3. Lookup by Last Name: Searches for an employee by their last name.
4. Add an Employee: Allows you to add a new employee to the database by providing their first name, last name, and salary.
5. Quit: Exits the program.
6. Remove an employee: Allows you to delete an employee from the database.
7. Update an employee's information: Enables you to update the employee's information.
8. Print the M employees with the highest salaries: Print the top Mth salary, sorted by salary.
9. Find all employees with matching last name: Return information for every employee whose last name matches case-insensitively.
