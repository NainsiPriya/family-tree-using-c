#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Person 
{
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

int main(void)
{
    Person *check = create_person("checking_code",19 );
    printf("%s %d\n",  check->name,check->age);
    free (check); 
    
    return 0;
}