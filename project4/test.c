#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Student
{
    char *name;
    struct Student *name_next;
};

struct Student *addStudent(struct Student *root, char *name)
{
    if(root == NULL)
    {
        root->name = name;
        root->name_next = NULL;
        return root;
    }
    if(root->name_next == NULL &&)
}

int main()
{
    struct Student *currentStudent;

    return 0;    
}