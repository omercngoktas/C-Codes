#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define SIZE 60

int main()
{
    FILE *students = fopen("students.txt", "r"); // opening txt file with name of 'students'.
    if (students == NULL) // checking if text file exists.
    {
        printf("File students.txt could not open. Please make sure that it is on same direction with .exe file.");
        return 0;
    }

    char student_name[SIZE/3], student_surname[SIZE/3], student_id[SIZE/3];
    char hole_line[SIZE];
    int i, j;


    while(!feof(students))
    {
        i = 0; j = 0;
        fgets(hole_line, SIZE, students);
        /*while(hole_line[i] != 32)
        {
            student_name[j] = hole_line[i];
            i++;
        } i++; j = 0;
        while(hole_line[i] != '\t')
        {
            student_surname[j] = hole_line[i];
            i++;
        } i++; j = 0;
        while(hole_line[i] != '\n')
        {
            student_id[j] = hole_line[i];
            i++;
        }
        printf("%s ", student_id);*/
        
        while(hole_line[i] != 32)
        {
            printf("%c ", hole_line[i]);
            student_name[i] = hole_line[i];
            printf("%c ", student_name[i]);
            i++;
        } i++;
        printf("  *******  ");
        while(hole_line[i] != '\t')
        {
            printf("%c ", hole_line[i]);
            student_surname[j] = hole_line[i];
            i++;
        }printf("\t\t"); i++; j = 0;
        while(hole_line[i] != '\n')
        {
            printf("%c ", hole_line[i]);
            student_id[j] = hole_line[i];
            i++;
        } printf("\n");

        //printf("%s", hole_line);
    }
    

    return 0;    
}