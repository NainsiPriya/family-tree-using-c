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

/*  Linking */

void link_parents(Person *child, Person *father, Person *mother)
{
    child->father = father;
    child->mother = mother;
}

/* Display */

void print_family_relationships(const Person *me)
{
    printf("\n=== 1. FAMILY TREE RELATIONSHIPS ===\n\n"); 

    if (me == NULL) {
        printf("No information available.\n");
        return;
    }
    
    printf("1. YOURSELF:\n");
    printf("   - Name: %s | Age: %d\n\n", me->name, me->age);

    printf("2. PARENTS:\n");
    printf("   - Father: %s | Age: %d\n", me->father->name, me->father->age);
    printf("   - Mother: %s | Age: %d\n\n", me->mother->name, me->mother->age);

    printf("3. PATERNAL GRANDPARENTS (via Father's Pointers):\n");
    printf("   - Grandfather: %s | Age: %d\n",
           me->father->father->name, me->father->father->age);
    printf("   - Grandmother: %s | Age: %d\n\n",
           me->father->mother->name, me->father->mother->age);

    printf("4. MATERNAL GRANDPARENTS (via Mother's Pointers):\n");
    printf("   - Grandfather: %s | Age: %d\n",
           me->mother->father->name, me->mother->father->age);
    printf("   - Grandmother: %s | Age: %d\n",
           me->mother->mother->name, me->mother->mother->age);
}

/* Recursive helper: prints the parents of `p`, using `prefix` for indentation.
 * level 0 -> p's parents are "Father"/"Mother"
 * level 1+ -> they are "Grandfather"/"Grandmother" */
static void print_branches(const Person *p, int level, const char *prefix)
{
    const char *fl = (level == 0) ? "Father" : "Grandfather";
    const char *ml = (level == 0) ? "Mother" : "Grandmother";
    char child_prefix[128];

    if (p->father != NULL) {
        const char *branch = (p->mother != NULL) ? "├── " : "└── ";
        const char *cont   = (p->mother != NULL) ? "│    " : "     ";
        printf("%s%s%s: %s (Age: %d)\n", prefix, branch, fl,
               p->father->name, p->father->age);
        snprintf(child_prefix, sizeof(child_prefix), "%s%s", prefix, cont);
        print_branches(p->father, level + 1, child_prefix);
    }
    if (p->mother != NULL) {
        printf("%s└── %s: %s (Age: %d)\n", prefix, ml,
               p->mother->name, p->mother->age);
        snprintf(child_prefix, sizeof(child_prefix), "%s     ", prefix);
        print_branches(p->mother, level + 1, child_prefix);
    }
}

void print_tree_visual(const Person *root, int level)
{
    if (root == NULL)
        return;
    if (level == 0)
        printf("\n=== 2. VISUAL FAMILY TREE ===\n\n");
    printf("%s (Age: %d)\n", root->name, root->age);
    print_branches(root, level, "  ");
}

/* Cleanup  */

void free_family_tree(Person *people[], int count)
{
    for (int i = 0; i < count; i++) {
        free(people[i]);
        people[i] = NULL;
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
    
    printf("\n========== INPUT RULES ==========\n\n");

    printf("\n1. NAME RULES:\n");
    printf("   - Name cannot be empty.\n");
    printf("   - Only English letters and spaces are allowed.\n");
    printf("   - Maximum name length: 49 characters.\n");
    printf("\n2. AGE RULES:\n");
    printf("   - Grandparents, Father and Mother: 18 to 150.\n");
    printf("   - Yourself: 0 to 150.\n");
    printf("   - Enter whole numbers only.\n");
    printf("   - Letters, decimals and negative ages are not allowed.\n");

    printf("\n=================================\n\n");


    /* Step 1: collect input and create each person exactly once */
    for (int i = 0; i < TOTAL; i++) {
        read_person_info(roles[i], name, &age);
        people[i] = create_person(name, age);
        printf("\n");
    }

    /* Step 2: wire pointers (grandparents keep NULL parents) */
    link_parents(people[FATHER], people[PGF], people[PGM]);
    link_parents(people[MOTHER], people[MGF], people[MGM]);
    link_parents(people[ME],     people[FATHER], people[MOTHER]);

    /* Step 3: output */
    print_family_relationships(people[ME]);
    print_tree_visual(people[ME], 0);

    /* Step 4: cleanup */
    free_family_tree(people, TOTAL);
    return 0;
}