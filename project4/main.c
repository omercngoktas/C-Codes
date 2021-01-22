#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 60

struct Student
{
    char name[SIZE/3];
    char surname[SIZE/3];
    long int ID;
    struct Student *name_next;
    struct Student *surname_next;
    struct Student *ID_next;
};

struct Student * insertNode(struct Student *root, char currentName[SIZE/3], char currentSurname[SIZE/3], long int currentID){
    if(root == NULL)
    {
        root = (struct Student*) malloc(sizeof(struct Student));
        root->ID_next = NULL;
        strcpy(root->name, currentName);
        strcpy(root->surname, currentSurname);
        root->ID = currentID;
        return root;
    }

    if(root->ID > currentID)
    {
        struct Student * temp = (struct Student*) malloc(sizeof(struct Student));
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

struct Student *sortName(struct Student *root, char currentName[SIZE/3], char currentSurname[SIZE/3], long int currentID)
{
    if(root == NULL)
    {
        root = (struct Student *) malloc(sizeof(struct Student));
        strcpy(root->name, currentName);
        strcpy(root->surname, currentSurname);
        root->ID = currentID;
        root->name_next = NULL;
        return root;
    }
    if(strcmp(currentName, root->name) < 0)
    {
        struct Student *temp = (struct Student *) malloc(sizeof(struct Student));
        strcpy(temp->name, currentName);
        strcpy(temp->surname, currentSurname);
        temp->ID = currentID;
        temp->name_next = root;
        return temp;
    }
    struct Student *iter = root;
    while(iter->name_next != NULL && strcmp(iter->name_next->name, currentName) < 0)
    {
        iter = iter->name_next;
    }
    struct Student *temp = (struct Student *) malloc(sizeof(struct Student));
    temp->name_next = iter->name_next;
    iter->name_next = temp;
    strcpy(temp->name, currentName);
    strcpy(temp->surname, currentSurname);
    temp->ID = currentID;
    return root;
}

struct Student *sortSurname(struct Student *root, char currentName[SIZE/3], char currentSurname[SIZE/3], long int currentID)
{
    if(root == NULL)
    {
        root = (struct Student *) malloc(sizeof(struct Student));
        strcpy(root->name, currentName);
        strcpy(root->surname, currentSurname);
        root->ID = currentID;
        root->surname_next = NULL;
        return root;
    }
    if(strcmp(currentSurname, root->surname) < 0)
    {
        struct Student *temp = (struct Student *) malloc(sizeof(struct Student));
        strcpy(temp->name, currentName);
        strcpy(temp->surname, currentSurname);
        temp->ID = currentID;
        temp->surname_next = root;
        return temp;
    }
    struct Student *iter = root;
    while(iter->surname_next != NULL && strcmp(iter->surname_next->surname, currentSurname) < 0)
    {
        iter = iter->surname_next;
    }
    struct Student *temp = (struct Student *) malloc(sizeof(struct Student));
    temp->surname_next = iter->surname_next;
    iter->surname_next = temp;
    strcpy(temp->name, currentName);
    strcpy(temp->surname, currentSurname);
    temp->ID = currentID;
    return root;
}

struct Student *deleteNode(struct Student *root, long int searchID) // PROJECT FUNCTION.
{
    if(root == NULL)
    {
        printf("There is no student to delete.");
    }
    struct Student *iter = root;
    while(iter->ID_next != NULL && iter->ID_next->ID != searchID)
    {
        iter = iter->ID_next;
    }
    printf("The student '%s %s\t\t%d' is deleted from the list!\n", iter->ID_next->name, iter->ID_next->surname, iter->ID_next->ID);
    iter->ID_next = iter->ID_next->ID_next;
    return iter;
}

void printList(struct Student *root, int process) // PROJECT FUNCTION.
{
    int number = 0;
    switch (process)
    {
        case 1: // it prints students list which sorted according to ID.
            printf("The list in ID sorted order:\n");
            while(root != NULL)
            {
                number++;
                printf("%d. %s %s\t%ld\n", number, root->name, root->surname, root->ID);
                root = root->ID_next;
            }
            printf("\n"); break;
            
        case 2: // it prints students list which sorted according to name.
            printf("The list in name-alphabetical sorted order:\n");
            while(root != NULL)
            {
                number++;
                printf("%d. %s %s\t%ld\n", number, root->name, root->surname, root->ID);
                root = root->name_next;
            }
            printf("\n"); break;
        
        case 3: // it prints students list which sorted according to surname.
            printf("The list in surname-alphabetical sorted order:\n");
            while(root != NULL)
            {
                number++;
                printf("%d. %s %s\t%ld\n", number, root->name, root->surname, root->ID);
                root = root->surname_next;
            }
            printf("\n"); break;

        default:
            printf("Some problem has occured while printing students.");
            break;
    }
}

int main()
{
    struct Student *studentID; // creating var from struct Student.
    studentID = NULL;
    struct Student *studentName; // creating var from struct Student.
    studentName = NULL;
    struct Student *studentSurname; // creating var from struct Student.
    studentSurname = NULL;
    
    int choice;
    char name[SIZE/3], surname[SIZE/3];
    long int ID;

    FILE *students = fopen("students.txt", "r"); // opening txt file with name of 'students'.
    if (students == NULL) // checking if text file exists.
    {
        printf("File students.txt could not open. Please make sure that it is on same direction with .exe file.");
        return 0;
    }

    
    studentID = insertNode(studentID, "Ayse", "Yilmaz", 1204);
    studentID = insertNode(studentID, "Veli", "Arslan", 1515);
    studentID = insertNode(studentID, "Fatma", "Ozde", 1001);
    studentID = insertNode(studentID, "Mehmet", "Ari", 1441);
    studentID = insertNode(studentID, "Ela", "Kara", 1980);
    studentID = insertNode(studentID, "Ismail", "Celik", 1345);
    studentID = insertNode(studentID, "Selin", "Ergul", 24566);
    studentID = insertNode(studentID, "Emre", "Kiraz", 17895);

    studentName = sortName(studentName, "Ayse", "Yilmaz", 1204);
    studentName = sortName(studentName, "Veli", "Arslan", 1515);
    studentName = sortName(studentName, "Fatma", "Ozde", 1001);
    studentName = sortName(studentName, "Mehmet", "Ari", 1441);
    studentName = sortName(studentName, "Ela", "Kara", 1980);
    studentName = sortName(studentName, "Ismail", "Celik", 1345);
    studentName = sortName(studentName, "Selin", "Ergul", 24566);
    studentName = sortName(studentName, "Emre", "Kiraz", 17895);

    studentSurname = sortSurname(studentSurname, "Ayse", "Yilmaz", 1204);
    studentSurname = sortSurname(studentSurname, "Veli", "Arslan", 1515);
    studentSurname = sortSurname(studentSurname, "Fatma", "Ozde", 1001);
    studentSurname = sortSurname(studentSurname, "Mehmet", "Ari", 1441);
    studentSurname = sortSurname(studentSurname, "Ela", "Kara", 1980);
    studentSurname = sortSurname(studentSurname, "Ismail", "Celik", 1345);
    studentSurname = sortSurname(studentSurname, "Selin", "Ergul", 24566);
    studentSurname = sortSurname(studentSurname, "Emre", "Kiraz", 17895);

    printList(studentName, 2);
    printList(studentSurname, 3);
    printList(studentID, 1);
    while(1)
    {
        printf("Enter your choice:\n");
        printf("\t1 to insert a student into the list.\n");
        printf("\t2 to delete a student from the list.\n");
        printf("\t3 to print the students in the list.\n");
        printf("\t4 to print the students to an output file.\n");
        printf("\t5 to end.\n");
        printf("? ");
        scanf("%d", &choice);
        printf("\n");
        switch (choice)
        {
        case 1:
            printf("Enter a student name, surname and ID:\n");
            scanf("%s", name);
            scanf("%s", surname);
            scanf("%ld", &ID);
            studentID = insertNode(studentID, name, surname, ID);
            studentName = sortName(studentName, name, surname, ID);
            studentSurname = sortSurname(studentSurname, name, surname, ID);
            printf("\n");
            break;

        case 2:
            printf("Enter a student ID:\n");
            scanf("%ld", &ID);
            studentID = deleteNode(studentID, ID);
            break;

        case 3:
            printList(studentName, 2);
            printList(studentSurname, 3);
            printList(studentID, 1);
            break;

        case 4:
            break;

        case 5:
            break;

        default:
            break;
        }
    }

    fclose(students); // closing student.txt file.
    return 0;
}