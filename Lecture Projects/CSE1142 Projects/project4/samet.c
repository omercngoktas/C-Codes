#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 60

struct Student
{
    char name[50];
    char surname[50];
    long int ID;
    struct Student *name_next;
    struct Student *surname_next;
    struct Student *ID_next;
};

struct Student * insertNode(struct Student *root, char currentName[SIZE/3], char currentSurname[SIZE/3], long int currentID){
    if(root == NULL)
    {
        root = (struct Student*)malloc(sizeof(struct Student));
        root->ID_next = NULL;
        strcpy(root->name, currentName);
        strcpy(root->surname, currentSurname);
        root->ID = currentID;
        return root;
    }

    if(root->ID > currentID)
    {
        struct Student * temp = (struct Student*)malloc(sizeof(struct Student));
        strcpy(temp->name, currentName);
        strcpy(temp->surname, currentSurname);
        temp->ID = currentID;
        temp ->ID_next = root;
        return temp;
    }

    struct Student *iter = root;
    while(iter->ID_next != NULL && iter->ID_next->ID < currentID)
    {
        iter = iter->ID_next;
    }
    struct Student *temp = (struct Student*)malloc(sizeof(struct Student));
    temp->ID_next = iter->ID_next;
    iter->ID_next = temp;
    strcpy(temp->name, currentName);
    strcpy(temp->surname, currentSurname);
    temp->ID = currentID;
    return root;

}

struct Student *sortName(struct Student *root)
{
    struct Student *iter = root;
    char tempName[20], tempSurname[20];
    long int tempID;
    strcpy(tempName, iter->name);
    strcpy(tempSurname, iter->surname);
    tempID = iter->ID;
    while(iter != NULL)
    {
        printf("while\n");
        if(iter != NULL)
        {
            iter = iter->ID_next;
        }
        printf("---------------------%s\n", tempName);
        if(strcmp(tempName, iter->name) > 0)
        {
            printf("%s %s %ld**********\n", tempName, tempSurname, tempID);
            strcpy(tempName, iter->name);
            strcpy(tempSurname, iter->surname);
            tempID = iter->ID;
            printf("--------%s %s %ld\n", tempName, tempSurname, tempID);  
        }
        printf("linked list dongusu -> %s %s\t%ld\n", iter->name, iter->surname, iter->ID);
        if(iter->ID_next == NULL)
        {
            break;
        }
        
    }
    printf("deneme");
    printf("%s %s %ld\n", tempName, tempSurname, tempID);
    return root;


}

void deleteNode(struct Student *root) // PROJECT FUNCTION.
{

}

void printList(struct Student *root) // PROJECT FUNCTION.
{
    while(root != NULL)
    {
        printf("%s %s\t%ld\n", root->name, root->surname, root->ID);
        root = root->ID_next;
    }
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

    
    currentStudent = insertNode(currentStudent, "Ayse", "Yilmaz", 1204);
    currentStudent = insertNode(currentStudent, "Veli", "Arslan", 1515);
    currentStudent = insertNode(currentStudent, "Fatma", "Ozde", 1001);
    currentStudent = insertNode(currentStudent, "Mehmet", "Ari", 1441);
    currentStudent = insertNode(currentStudent, "Ela", "Kara", 1980);
    currentStudent = insertNode(currentStudent, "Ismail", "Celik", 1345);
    currentStudent = insertNode(currentStudent, "Selin", "Ergul", 24566);
    currentStudent = insertNode(currentStudent, "Emre", "Kiraz", 17895);


    printList(currentStudent);

    sortName(currentStudent);
    


    fclose(students); // closing student.txt file.
    return 0;
}