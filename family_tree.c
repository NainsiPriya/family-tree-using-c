#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<ctype.h>   
#include<errno.h>

typedef struct Person {
    char name[50];
    int age;
    struct Person *father;
    struct Person *mother;
} Person;


Person *create_person(const char *name, int age);
void read_person_info(const char *role, char *name_out, int *age_out);
void link_parents(Person *child, Person *father, Person *mother);
void print_family_relationships(const Person *me);
void print_tree_visual(const Person *root, int level);
void free_family_tree(Person *people[], int count);


Person *create_person(const char *name, int age)
{
    Person *p = malloc(sizeof(Person));
    if (p == NULL) {
        fprintf(stderr, "Error: out of memory\n");
        exit(EXIT_FAILURE);
    }
    strncpy(p->name, name, sizeof(p->name) - 1);
    p->name[sizeof(p->name) - 1] = '\0';
    p->age = age;
    p->father = NULL;
    p->mother = NULL;
    return p;
}

void read_person_info(const char *role, char *name_out, int *age_out)
{
    char buf[100];

 /* Name */
    while (1) {
        printf("Enter name for %s (maximum 49 characters): ", role);


     if (fgets(buf, sizeof(buf), stdin) == NULL) {
        fprintf(stderr, "\nUnexpected end of input.\n");
        exit(EXIT_FAILURE);
     }

     if (strchr(buf, '\n') == NULL && !feof(stdin)) {
        int ch;

        while ((ch = getchar()) != '\n' && ch != EOF) {
        }

        printf("Name is too long (maximum 49 characters).\n");
        continue;
     }

     buf[strcspn(buf, "\n")] = '\0';
  
     if (strlen(buf) > 49) {
        printf("Name is too long (maximum 49 characters).\n");
        continue;
    }   
    int valid_name = (buf[0] != '\0');
     int has_letter = 0;

      for (size_t i = 0; buf[i] != '\0'; i++) 
      {
           if (isalpha((unsigned char)buf[i])) 
           {
            has_letter = 1;
           } 
           else if (buf[i] != ' ') 
           {
           valid_name = 0;
          }
      }

       if (valid_name && has_letter) {
      break; } 

        printf("Name must contain letters and spaces only.\n");
        
     }
    strncpy(name_out, buf, 49);                   /* name[50] in Person */
    name_out[49] = '\0';

  /* Age */
    int min_age = (strcmp(role, "Yourself") == 0) ? 0 : 18;

     while (1) {
     printf("Enter age for %s (%d-150): ", role, min_age);

     if (fgets(buf, sizeof(buf), stdin) == NULL) {
        fprintf(stderr, "\nUnexpected end of input.\n");
        exit(EXIT_FAILURE);
     } 

     if (strchr(buf, '\n') == NULL && !feof(stdin)) {
        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF) {
        }
        printf("Invalid age. Try again.\n");
        continue;
     }

     buf[strcspn(buf, "\n")] = '\0';

     int valid_age = (buf[0] != '\0');

     for (size_t i = 0; buf[i] != '\0'; i++) {
        if (!isdigit((unsigned char)buf[i])) {
            valid_age = 0;
            break;
        }
     }

     if (valid_age) {
        char *end;
        errno = 0;
        long parsed_age = strtol(buf, &end, 10);

        if (errno == 0 && *end == '\0' &&
            parsed_age >= min_age && parsed_age <=150) {
            *age_out = (int)parsed_age;
            break;
        }
     }

      printf("Invalid age. Enter a whole number from %d to 150.\n",
           min_age);
      }
}


/*  main */

int main(void)
{
    enum { PGF, PGM, MGF, MGM, FATHER, MOTHER, ME, TOTAL };
    const char *roles[TOTAL] = {
        "Paternal Grandfather", "Paternal Grandmother",
        "Maternal Grandfather", "Maternal Grandmother",
        "Father", "Mother", "Yourself"
    };
    Person *people[TOTAL];
    char name[50];
    int age;

    /* Step 1: collect input and create each person exactly once */
    for (int i = 0; i < TOTAL; i++) {
        read_person_info(roles[i], name, &age);
        people[i] = create_person(name, age);
        printf("\n");
    }

    return 0;
}