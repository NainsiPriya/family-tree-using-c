# Family Tree Program in C

## 1. Project Overview

This project implements a three-generation family tree using the C programming language. It collects information about seven family members, establishes their relationships using pointers, and displays the family tree in two formats:

1. **Family Relationships:** Displays the names and ages of family members according to their relationships.
2. **Visual Family Tree:** Displays the family hierarchy using indentation and tree branches.

## 2. Features

- Uses a `Person` structure to store names, ages, and parent pointers.
- Collects information about seven family members across three generations.
- Uses dynamic memory allocation with `malloc()`.
- Connects family members using pointers.
- Validates names and ages before accepting input.
- Displays family relationships in a structured format.
- Prints a visual family tree using recursion.
- Frees dynamically allocated memory using `free()`.
- Handles memory allocation failure.

## 3. Input Validation Rules

### Name Rules
- Names cannot be empty.
- Only English letters and spaces are allowed.
- Maximum name length is 49 characters.

### Age Rules
- Grandparents, father, and mother: 18–150 years.
- Yourself: 0–150 years.
- Only whole numbers are accepted.
- Letters, decimals, negative ages, and values outside the allowed range are rejected.

## 4. Technologies Used

- C programming language
- GCC compiler
- Visual Studio Code
- Valgrind for memory debugging

## 5. How to Compile and Run

The program is expected to run on most of the compilers. I used 'termide' inside ssh terminal or bash.

Compile the program:

```bash
gcc family_tree.c 
./a.out 
```

Run the program:

```bash
./family_tree
```

Follow the prompts to enter the names and ages of all seven family members.

## 6. Memory Leak Testing

 Valgrind command was run in the termide inside ssh terminal to check for memory leaks and memory errors:

```bash
valgrind 


Checked the Valgrind report to verify whether any memory leaks or errors are present.

## 7. Program Execution Screenshot
1. Execution : The screenshots below are given to show the running program.  

![Program Execution](programWorking2main.png)  
Image 1 : running program prints the standard fmaily output and diagramatic family tree

![Program Execution](programWorkin1.png)
Image 2 : rules being followed in the program 

2. Memory leak testing : The screenshot below gives the output after running valgrind command for memory leak testing. 

![Program Execution](valgrind-Copy.png )
Image 3 : valgrind memory leak testing 


## 8. Development history

The project was built in four stages, each committed separately:

1. feat: add Person struct and create_person allocation helper
2. feat: collect input for all 7 family members
3. feat: link parent pointers and implement relationship print
4. fix: add memory cleanup with free and polish output

## 9. Author

**Nainsi Priya**


