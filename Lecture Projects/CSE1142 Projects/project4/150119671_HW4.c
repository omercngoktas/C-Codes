/* Omercan Goktas 150119671

First of all, I am sorry about not being able to implement a singly linked list. I tried too hard to figure out, but I could not find any
way to solve this situation. That is why, I had to use 3 signly linked lists for name_next, surname_next and ID_next.
Apart from these, I tried to implement function according to their usage and write codes understandable.

In this project, I read txt file and get strings line by line and I opened txt file and printed some strings to this file. I also learned singly linked list.

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 60

struct Student // creating struct with name Stundet.
{
    char name[SIZE/3];
    char surname[SIZE/3];
    long int ID;
    struct Student *name_next;
    struct Student *surname_next;
    struct Student *ID_next;
};

struct Student * insertNode(struct Student *root, char currentName[SIZE/3], char currentSurname[SIZE/3], long int currentID)
// this function sort students according to ID order.
{
    if(root == NULL) // checking if root is NULL.
    {
        root = (struct Student*) malloc(sizeof(struct Student)); // allocating memory for root.
        root->ID_next = NULL; // assigning NULL to next value of ID_next.
        strcpy(root->name, currentName); // assigning name to the name for ID sorting.
        strcpy(root->surname, currentSurname); // assigning surname to the surname for ID sorting.
        root->ID = currentID; // assigning ID to the ID for ID sorting.
        return root;
    }

    if(root->ID > currentID) // checking if first value bigger than currentID.
    {
        struct Student * temp = (struct Student*) malloc(sizeof(struct Student)); // allocating memory for temp.
        strcpy(temp->name, currentName);
        strcpy(temp->surname, currentSurname);
        temp->ID = currentID;
        temp ->ID_next = root; // connecting next ID value of temp to the root.
        return temp;
    }

    struct Student *iter = root; // assigning root to the iter.
    while(iter->ID_next != NULL && iter->ID_next->ID < currentID)
    {
        iter = iter->ID_next;
    }
    // implementing process for assigning values.
    struct Student *temp = (struct Student*)malloc(sizeof(struct Student));
    temp->ID_next = iter->ID_next;
    iter->ID_next = temp;
    strcpy(temp->name, currentName);
    strcpy(temp->surname, currentSurname);
    temp->ID = currentID;
    return root;
}

struct Student *sortName(struct Student *root, char currentName[SIZE/3], char currentSurname[SIZE/3], long int currentID)
// this function sorts students according to name order.
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
// this function sorts students according to surname order.
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

struct Student *deleteNode(struct Student *root, long int searchID, int operator)
// this function deletes student which was sent by user with ID.
{
    struct Student *temp; // creating temp struct.
    struct Student *iter = root; // assigning root to the iter.
    switch (operator) // checking what is the operator.
    {
        case 1: // if operator is '1', student is deleted from name sorted struct.
            if(root->ID == searchID) // checking if first element of struct matches with searchID.
            {
                temp = root;
                root = root->name_next;
                free(temp);
                return root;
            }
            while(iter->name_next != NULL && iter->name_next->ID != searchID)
            {
                iter = iter->name_next;
            }
            if(iter->name_next == NULL)
            {
            }
            temp = iter->name_next;
            iter->name_next = iter->name_next->name_next;
            free(temp);
            return root;
            break;
        
        case 2: // if operator is '2', student is deleted from surname sorted struct.
            if(root->ID == searchID)
            {
                temp = root;
                root = root->surname_next;
                free(temp);
                return root;
            }
            while(iter->surname_next != NULL && iter->surname_next->ID != searchID)
            {
                iter = iter->surname_next;
            }
            if(iter->surname_next == NULL)
            {
                
            }
            temp = iter->surname_next;
            iter->surname_next = iter->surname_next->surname_next;
            free(temp);
            return root;
            break;
        
        case 3: // if operator is '3', student is deleted from ID sorted struct.
            if(root->ID == searchID)
            {
                temp = root;
                root = root->ID_next;
                free(temp);
                return root;
            }
            while(iter->ID_next != NULL && iter->ID_next->ID != searchID)
            {
                iter = iter->ID_next;
            }
            if(iter->ID_next == NULL)
            {
                printf("There is no student matches with ID %ld.\n", searchID);
            }
            printf("The student '%s %s\t\t%ld' is deleted from the list!\n", iter->ID_next->name, iter->ID_next->surname, iter->ID_next->ID);
            temp = iter->ID_next;
            iter->ID_next = iter->ID_next->ID_next;
            free(temp);
            
            return root;
            break;
        
        default:
            break;
    } 
}

void printList(struct Student *root, int process) // printing students with order to the console.
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

void writeToFile(struct Student *root, char fileName[],int operator)
// this function prints all of the orders to the file which is taken from user.
{
    FILE *outputStudents = fopen(fileName, "a");
    if (outputStudents == NULL) // checking if file does not exist.
    {
        FILE *outputStudents = fopen(fileName, "w");
    }
    int number = 0;
    switch (operator)
    {
        case 1: // printing name order to the file.
            fprintf(outputStudents, "The list in name-alphabetical order:\n");
            while(root != NULL)
            {
                number++;
                fprintf(outputStudents, "\t%d. %s %s\t%ld\n", number, root->name, root->surname, root->ID);
                root = root->name_next;
            }   fprintf(outputStudents, "\n");
        
            break;
        
        case 2: // printing surname order to the file.
            fprintf(outputStudents, "The list in surname-alphabetical order:\n");
            while(root != NULL)
            {
                number++;
                fprintf(outputStudents, "\t%d. %s %s\t%ld\n", number, root->name, root->surname, root->ID);
                root = root->surname_next;
            }  fprintf(outputStudents, "\n");
            break;

        case 3: // printing ID order to the file.
            fprintf(outputStudents, "The list in ID sorted order:\n");
            while(root != NULL)
            {
                number++;
                fprintf(outputStudents, "\t%d. %s %s\t%ld\n", number, root->name, root->surname, root->ID);
                root = root->ID_next;
            }  
            break;
        default:
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
    char outputFile[SIZE];

    FILE *students = fopen("students.txt", "r"); // opening txt file with name of 'students'.
    if (students == NULL) // checking if text file exists.
    {
        printf("File students.txt could not open. Please make sure that it is on same direction with .exe file.");
        return 0;
    }

    //char student_name[SIZE/3], student_surname[SIZE/3], student_id[SIZE/3];
    char hole_line[SIZE];
    int i, j;
    char *student_name, *student_surname, *student_id;
    long int student_ID;


    while(!feof(students))
    {
        student_name = (char *) malloc(sizeof(char) * (SIZE/3));
        student_surname = (char *) malloc(sizeof(char) * (SIZE/3));
        student_id = (char *) malloc(sizeof(char) * (SIZE/3));

        i = 0; j = 0;
        fgets(hole_line, SIZE, students);
        
        while(hole_line[i] != 32)
        {
            student_name[i] = hole_line[i];
            i++;
        } i++;
        
        while(hole_line[i] != '\t')
        {
            student_surname[j] = hole_line[i];
            i++; j++;
        }i++; j = 0;
        while(hole_line[i] != '\n')
        {
            student_id[j] = hole_line[i];
            i++; j++;
        }; student_ID = atoi(student_id);
        studentID = insertNode(studentID, student_name, student_surname, student_ID);
        studentName = sortName(studentName, student_name, student_surname, student_ID);
        studentSurname = sortSurname(studentSurname, student_name, student_surname, student_ID);
        free(student_name);
        free(student_surname);
        free(student_id);
    }
    
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
            studentName = deleteNode(studentName, ID, 1);
            studentSurname = deleteNode(studentSurname, ID, 2);
            studentID = deleteNode(studentID, ID, 3);
            break;

        case 3:
            printList(studentName, 2);
            printList(studentSurname, 3);
            printList(studentID, 1);
            break;

        case 4:
            printf("Enter a file name:\n");
            scanf("%s", outputFile);
            printf("Output is printed to the file %s\n\n", outputFile);
            writeToFile(studentName, outputFile, 1);
            writeToFile(studentSurname, outputFile, 2);
            writeToFile(studentID, outputFile, 3);
            break;

        case 5:
            printf("--------------------------------\n");
            fclose(students);
            return 0;
            break;

        default:
            break;
        }
    }

    fclose(students); // closing student.txt file.
    return 0;
}