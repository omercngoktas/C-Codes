#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 60

struct Student
{
    char *name;
    char *surname;
    long int ID;
    struct Student *name_next;
    struct Student *surname_next;
    struct Student *ID_next;
};

struct Student *insertNode(struct Student *root, char *name, char *surname, long int id) // PROJECT FUNCTION.
{
    if(root == NULL)
    {
        root = (struct Student *) malloc(sizeof(struct Student));
        root->name = name;
        root->name_next = NULL;
        root->surname = surname;
        root->surname_next = NULL;
        root->ID = id;
        root->ID_next = NULL;
    }
}

void deleteNode(struct Student *root) // PROJECT FUNCTION.
{

}

void printList(struct Student *root) // PROJECT FUNCTION.
{

}

int main()
{
    struct Student *currentStudent; // creating var from struct Student.
    currentStudent = NULL;

    FILE *students = fopen("students.txt", "r"); // opening txt file with name of 'students'.
    if (students == NULL) // checking if text file exists.
    {
        printf("File students.txt could not open. Please make sure that it is on same direction with .exe file.");
        return 0;
    }

    char *studentLine = (char *) malloc(sizeof(char) * SIZE);
    char *name = (char *) malloc(sizeof(char) * SIZE/3);
    char *surname = (char *) malloc(sizeof(char) * SIZE/3);
    char *id = (char *) malloc(sizeof(char) * SIZE/3);
    int i = 0, j = 0, k;
    long int ID;
    
    fgets(studentLine, SIZE, students);
    
    while(studentLine[i] != 32)
    {
        name[j] = studentLine[i];
        i++; j++;
    }   i++; j = 0;

    while(studentLine[i] != '\t')
    {
        surname[j] = studentLine[i];
        i++; j++;
    }   i++; j = 0;

    while(studentLine[i] != '\n')
    {
        id[j] = studentLine[i];
        i++; j++;
    }   ID = atoi(id);
    











    fclose(students); // closing student.txt file.
    return 0;
}