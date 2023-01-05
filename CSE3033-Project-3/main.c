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

void unlockAllLines() {
    for(int i = 0; i < sizeOfLines; i++) {
        textLines[i].isLineReplaced = 0;
        textLines[i].isLineUppered = 0;
        printf("Line %d has unlocked\n", i);
    }
}

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

void* upper_thread(void* threadType) {
    thread_data* upper_thread_data = (thread_data*) threadType;
    int thread_id = upper_thread_data->thread_id;

    int readLineNumber = 0;
    for(int i = 0; i < sizeOfLines; i++) {
        if(readLineNumber % NUMBER_OF_UPPER_THREADS == thread_id) {
            pthread_mutex_lock(&mutex);    
            printf("Upper thread_id: %d\tLine which is gonna be uppered is: %d\n", thread_id, readLineNumber);
            printf("Line: %s\n", textLines[readLineNumber].lineString);
            for(int j = 0; j < LINE_LENGTH; j++) {
                textLines[readLineNumber].lineString[j] = toupper(textLines[readLineNumber].lineString[j]);
            }
            printf("Line: %s\n\n", textLines[readLineNumber].lineString);
            pthread_mutex_unlock(&mutex);
        }
        readLineNumber++;
    }
    
    pthread_exit(NULL);
}

void* replace_thread(void* threadType) {
    thread_data* data = (thread_data*) threadType;
    int thread_id = data->thread_id;

    int readLineNumber = 0;
    for(int i = 0; i < sizeOfLines; i++) {
        if(readLineNumber % NUMBER_OF_REPLACE_THREADS == thread_id) {
            pthread_mutex_lock(&mutex);
            printf("Replace thread_id: %d\tLine which is gonna be replaced is: %d\n", thread_id, readLineNumber);
            printf("Line: %s\n", textLines[readLineNumber].lineString);
            for(int j = 0; j < LINE_LENGTH; j++) {
                if(textLines[readLineNumber].lineString[j] == ' ') { textLines[readLineNumber].lineString[j] = '_'; }
            }
            printf("Line: %s\n\n", textLines[readLineNumber].lineString);
            pthread_mutex_unlock(&mutex);
        }
    }

}

void printLines() {
    for(int i = 0; i < sizeOfLines; i++) {
        textLines[i].isLineReplaced = 0;
        textLines[i].isLineUppered = 0;
        printf("Line: %d\t Replace and Upper states: %d %d\tLine: %s\n", textLines[i].lineNumber, textLines[i].isLineReplaced, textLines[i].isLineUppered, textLines[i].lineString);
        
    }
}

int main(int argc, char* argv[]) {
    if(argc != 5) {
        printf("Usage: %s <fileName> readThreadNumber upperThreadNumber replaceThreadNumber\n", argv[0]);
        exit(1);
    }

    pthread_mutex_init(&mutex, NULL);

    fileName = argv[1];
    NUMBER_OF_READ_THREADS = atoi(argv[2]);
    NUMBER_OF_UPPER_THREADS = atoi(argv[3]);
    NUMBER_OF_REPLACE_THREADS = atoi(argv[4]);

    pthread_t readThreads[NUMBER_OF_READ_THREADS];
    thread_data readThreadsData[NUMBER_OF_READ_THREADS];

    pthread_t upperThreads[NUMBER_OF_UPPER_THREADS];
    thread_data upperThreadsData[NUMBER_OF_UPPER_THREADS];

    pthread_t replaceThreads[NUMBER_OF_REPLACE_THREADS];
    thread_data replaceThreadsData[NUMBER_OF_REPLACE_THREADS];

    for(int i = 0; i < NUMBER_OF_READ_THREADS; i++) {
        readThreadsData[i].thread_id = i;
        int isReadThreadSuccessful = pthread_create(&readThreads[i], NULL, read_thread, &readThreadsData[i]);
        if(isReadThreadSuccessful != 0) {
            perror("Error while creating read thread");
            exit(1);
        }
    }

    for(int i = 0; i < NUMBER_OF_READ_THREADS; i++) {
        int isReadThreadTerminated = pthread_join(readThreads[i], NULL);
        if(isReadThreadTerminated != 0) {
            perror("Error while waiting read thread");
            exit(1);
        }
    }

    unlockAllLines();

    for(int i = 0; i < NUMBER_OF_UPPER_THREADS; i++) {
        upperThreadsData[i].thread_id = i;
        int isUpperThreadSuccessful = pthread_create(&upperThreads[i], NULL, upper_thread, &upperThreadsData[i]);
        if(isUpperThreadSuccessful != 0) {
            perror("Error while creating upper thread");
            exit(1);
        }
    }

    for(int i = 0; i < NUMBER_OF_REPLACE_THREADS; i++) {
        replaceThreadsData[i].thread_id = i;
        int isReplaceThreadSuccessful = pthread_create(&replaceThreads[i], NULL, replace_thread, &replaceThreadsData[i]);
        if(isReplaceThreadSuccessful != 0) {
            perror("Error while creating replace thread");
            exit(1);
        }
    }

    for(int i = 0; i < NUMBER_OF_REPLACE_THREADS; i++) {
        int isReplaceThreadTerminated = pthread_join(replaceThreads[i], NULL);
        if(isReplaceThreadTerminated != 0) {
            perror("Error while waiting replace thread");
            exit(1);
        }
    }

    for(int i = 0; i < NUMBER_OF_UPPER_THREADS; i++) {
        int isUpperThreadTerminated = pthread_join(upperThreads[i], NULL);
        if(isUpperThreadTerminated != 0) {
            perror("Error while waiting upper thread");
            exit(1);
        }
    }



    printLines();

    pthread_mutex_destroy(&mutex);
}