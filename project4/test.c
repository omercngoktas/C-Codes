#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Student
{
    char *name;
    char *surname;
    long int ID;
    struct Student *name_next;
    struct Student *surname_next;
    struct Student *ID_next;
};

struct Student *addStudent(struct Student *root, char *name)
{
    if(root == NULL)
    {
        root = (struct Student *) malloc(sizeof(struct Student));
        root->name = name;
        root->name_next = NULL;
        return root;
    }
    if(strcmp(root->name, name) > 0)
    {
        struct Student *temp = (struct Student *) malloc(sizeof(struct Student));
        temp->name = name;
        temp->name_next = root;
        return temp;
    }
    if(strcmp(root->surname, name) > 0)
    {
        struct Student *temp = (struct Student *) malloc(sizeof(struct Student));
        temp->surname = name;
        name
    }

}

void displayStudent(struct Student *root)
{
    int i = 0;
    printf("deneme\n");
    while(root != NULL)
    {
        i++;
        printf("%d. %s\n", i, root->name);
        root = root->name_next;
    }
}

int main()
{
    struct Student *currentStudent;
    currentStudent = NULL;

    currentStudent = addStudent(currentStudent, "Omercan");
    currentStudent = addStudent(currentStudent, "Goktas");

    displayStudent(currentStudent);

    return 0;    
}