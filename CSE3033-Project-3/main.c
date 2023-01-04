#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>
#include <string.h>
#include <ctype.h>

#define LINE_LENGTH 1024

int NUMBER_OF_READ_THREADS;
int NUMBER_OF_UPPER_THREADS;
int NUMBER_OF_REPLACE_THREADS;
int NUMBER_OF_WRITE_THREADS;
char* fileName;
pthread_mutex_t mutex;

typedef struct thread_data {
    int thread_id;
} thread_data;

typedef struct line {
    char lineString[LINE_LENGTH];
    int lineNumber;
    int isLineUppered;
    int isLineReplaced;
} lines;

lines* textLines;

int sizeOfLines = 0;

void addNewLine(char newLine[], int lineNumber) {
    if(sizeOfLines == 0) {
        textLines = (lines*) malloc(lineNumber * sizeof(lines));
        textLines[lineNumber-1].lineNumber = lineNumber;
        strcpy(textLines[lineNumber-1].lineString, newLine);
        sizeOfLines = lineNumber;
        return;
    }
    if(lineNumber > sizeOfLines) {
        sizeOfLines = lineNumber;
        textLines = realloc(textLines, (lineNumber) * sizeof(lines));
        textLines[lineNumber-1].lineNumber = lineNumber;
        strcpy(textLines[lineNumber-1].lineString, newLine);
        return;
    }
    textLines[lineNumber-1].lineNumber = lineNumber;
    strcpy(textLines[lineNumber-1].lineString, newLine);
}

void* read_thread(void* threadType) {
    thread_data* read_thread_data = (thread_data*) threadType;
    int thread_id = read_thread_data->thread_id;
    
    FILE* textFile = fopen(fileName, "r");
    if(textFile == NULL) {
        perror("Error while opening text file");
        exit(1);
    }

    char readLine[LINE_LENGTH];
    int lineNumber = 0;

    while(fgets(readLine, LINE_LENGTH, textFile) != NULL) {
        if(lineNumber % NUMBER_OF_READ_THREADS == thread_id) {
            pthread_mutex_lock(&mutex);
            // deleting new line character ('\n') from the line 
            for(int i = 0; i < LINE_LENGTH; i++) {
                if(readLine[i] == '\n') readLine[i] = '\0';
            }
            printf("Thread ID: %d\tLine: %s\n", thread_id, readLine);
            addNewLine(readLine, lineNumber);
            pthread_mutex_unlock(&mutex);
        }
        lineNumber++;
    }

    //printf("Thread ID: %d\n", thread_id);    
    fclose(textFile);
    pthread_exit(NULL);
}

void printLines() {
    for(int i = 0; i < sizeOfLines; i++) {
        textLines[i].isLineReplaced = 0;
        textLines[i].isLineUppered = 0;
        printf("Line: %d\t Replace and Upper states: %d %d\tLine: %s\n", textLines[i].lineNumber, textLines[i].isLineReplaced, textLines[i].isLineUppered, textLines[i].lineString);
        
    }
}

int main(int argc, char* argv[]) {
    if(argc != 3) {
        printf("Usage: %s <fileName> readThreadNumber\n", argv[0]);
        exit(1);
    }

    pthread_mutex_init(&mutex, NULL);

    fileName = argv[1];
    NUMBER_OF_READ_THREADS = atoi(argv[2]);

    pthread_t readThreads[NUMBER_OF_READ_THREADS];
    thread_data readThreadsData[NUMBER_OF_READ_THREADS];
    for(int i = 0; i < NUMBER_OF_READ_THREADS; i++) {
        readThreadsData[i].thread_id = i;
        int isReadThreadSuccessful = pthread_create(&readThreads[i], NULL, read_thread, &readThreadsData[i]);
        if(isReadThreadSuccessful != 0) {
            perror("Error creating read thread");
            exit(1);
        }
    }

    for(int i = 0; i < NUMBER_OF_READ_THREADS; i++) {
        int isReadThreadTerminated = pthread_join(readThreads[i], NULL);
        if(isReadThreadTerminated != 0) {
            perror("Error waiting read thread");
            exit(1);
        }
    }

    printLines();

    pthread_mutex_destroy(&mutex);
}