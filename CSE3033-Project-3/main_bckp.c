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

pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

typedef struct thread_data {
    int thread_id;
} thread_data;

typedef struct line {
    char lineString[LINE_LENGTH];
    int lineNumber;
    int isLineUppered;
    int isLineReplaced;
    int isLineUpperingOrReplacing;
} lines;

lines* textLines;

int sizeOfLines = 0;

void unlockAllLines() {
    for(int i = 0; i < sizeOfLines; i++) {
        textLines[i].isLineUpperingOrReplacing = 0;
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
            printf("Read_%d\t\t\tRead_%d read the line %d which is '%s'\n", thread_id, thread_id, lineNumber, readLine);
            addNewLine(readLine, lineNumber);
            pthread_mutex_unlock(&mutex);
        }
        lineNumber++;
    }  
    fclose(textFile);
    pthread_exit(NULL);
}

void* upper_thread(void* threadType) {
    thread_data* upper_thread_data = (thread_data*) threadType;
    int thread_id = upper_thread_data->thread_id;

    int readLineNumber = 0;
    for(int i = 0; i < sizeOfLines; i++) {
        if(readLineNumber % NUMBER_OF_UPPER_THREADS == thread_id) {
            /* with while loop, if replace thread is working on this line, it waits until replace thread is done with its job */
            while(textLines[readLineNumber].isLineUpperingOrReplacing == 1);
            /* locking the current line, so it can be modified with only this thread */
            textLines[readLineNumber].isLineUpperingOrReplacing = 1;
            pthread_mutex_lock(&mutex);    
            printf("Upper_%d\t\t\tUpper_%d read index %d and converted '%s' to\n", thread_id, thread_id, readLineNumber, textLines[readLineNumber].lineString);
            for(int j = 0; j < LINE_LENGTH; j++) {
                textLines[readLineNumber].lineString[j] = toupper(textLines[readLineNumber].lineString[j]);
            }
            printf("\t\t\t\t'%s'\n", textLines[readLineNumber].lineString);
            /* unlocking the current line, so it can be modified with only this thread */
            textLines[readLineNumber].isLineUpperingOrReplacing = 0;
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
            while(textLines[readLineNumber].isLineUpperingOrReplacing == 1);
            textLines[readLineNumber].isLineUpperingOrReplacing = 1;
            pthread_mutex_lock(&mutex);
            printf("Replace_%d\t\tReplace_%d read index %d and converted '%s' to\n", thread_id, thread_id, readLineNumber, textLines[readLineNumber].lineString);
            for(int j = 0; j < LINE_LENGTH; j++) {
                if(textLines[readLineNumber].lineString[j] == ' ') { textLines[readLineNumber].lineString[j] = '_'; }
            }
            printf("\t\t\t\t'%s'\n", textLines[readLineNumber].lineString);
            textLines[readLineNumber].isLineUpperingOrReplacing = 0;
            pthread_mutex_unlock(&mutex);
        }
        readLineNumber++;
    }
    pthread_exit(NULL);
}

void* write_thread(void* threadType) {
    thread_data* data = (thread_data*) threadType;
    int thread_id = data->thread_id;

    FILE* textFile = fopen("output.txt", "r");
    if(textFile == NULL) {
        textFile = fopen("output.txt", "w");
    }

    int lineNumber = 0;

    while(1) {
        if(lineNumber % NUMBER_OF_WRITE_THREADS == thread_id) {
            pthread_mutex_lock(&mutex);
            printf("Thread_id: %d\tOkunan satir: %s\n", thread_id, textLines[lineNumber].lineString);
            pthread_mutex_unlock(&mutex);
            break;
        }
        lineNumber++;
    }  
    fclose(textFile);
    pthread_exit(NULL);
    
}

void printLines() {
    for(int i = 0; i < sizeOfLines; i++) {
        textLines[i].isLineReplaced = 0;
        textLines[i].isLineUppered = 0;
        printf("Line: %d\t\tLine: %s\n", textLines[i].lineNumber, textLines[i].lineString);
        
    }
}

int main(int argc, char* argv[]) {
    if(argc != 6) {
        printf("Usage: %s <fileName> readThreadNumber upperThreadNumber replaceThreadNumber writeThreadNumber\n", argv[0]);
        exit(1);
    }

    pthread_mutex_init(&mutex, NULL);

    fileName = argv[1];
    NUMBER_OF_READ_THREADS = atoi(argv[2]);
    NUMBER_OF_UPPER_THREADS = atoi(argv[3]);
    NUMBER_OF_REPLACE_THREADS = atoi(argv[4]);
    NUMBER_OF_WRITE_THREADS = atoi(argv[5]);

    pthread_t readThreads[NUMBER_OF_READ_THREADS];
    thread_data readThreadsData[NUMBER_OF_READ_THREADS];

    pthread_t upperThreads[NUMBER_OF_UPPER_THREADS];
    thread_data upperThreadsData[NUMBER_OF_UPPER_THREADS];

    pthread_t replaceThreads[NUMBER_OF_REPLACE_THREADS];
    thread_data replaceThreadsData[NUMBER_OF_REPLACE_THREADS];

    pthread_t writeThreads[NUMBER_OF_WRITE_THREADS];
    thread_data writeThreadsData[NUMBER_OF_WRITE_THREADS];

    printf("<Thread-type and ID>\t\t<Output>\n");

    /* creating read threads */
    for(int i = 0; i < NUMBER_OF_READ_THREADS; i++) {
        readThreadsData[i].thread_id = i;
        int isReadThreadSuccessful = pthread_create(&readThreads[i], NULL, read_thread, &readThreadsData[i]);
        if(isReadThreadSuccessful != 0) {
            perror("Error while creating read thread");
            exit(1);
        }
    }
    /* waiting for read threads to finish their job */
    for(int i = 0; i < NUMBER_OF_READ_THREADS; i++) {
        int isReadThreadTerminated = pthread_join(readThreads[i], NULL);
        if(isReadThreadTerminated != 0) {
            perror("Error while waiting read thread");
            exit(1);
        }
    }
    unlockAllLines();
    // /* creating upper threads */
    // for(int i = 0; i < NUMBER_OF_UPPER_THREADS; i++) {
    //     upperThreadsData[i].thread_id = i;
    //     int isUpperThreadSuccessful = pthread_create(&upperThreads[i], NULL, upper_thread, &upperThreadsData[i]);
    //     if(isUpperThreadSuccessful != 0) {
    //         perror("Error while creating upper thread");
    //         exit(1);
    //     }
    // }
    // /* creating replace threads */
    // for(int i = 0; i < NUMBER_OF_REPLACE_THREADS; i++) {
    //     replaceThreadsData[i].thread_id = i;
    //     int isReplaceThreadSuccessful = pthread_create(&replaceThreads[i], NULL, replace_thread, &replaceThreadsData[i]);
    //     if(isReplaceThreadSuccessful != 0) {
    //         perror("Error while creating replace thread");
    //         exit(1);
    //     }
    // }
    // /* waiting for upper threads to finish their job */
    // for(int i = 0; i < NUMBER_OF_UPPER_THREADS; i++) {
    //     int isUpperThreadTerminated = pthread_join(upperThreads[i], NULL);
    //     if(isUpperThreadTerminated != 0) {
    //         perror("Error while waiting upper thread");
    //         exit(1);
    //     }
    // }
    // /* waiting for replace threads to finish their job */
    // for(int i = 0; i < NUMBER_OF_REPLACE_THREADS; i++) {
    //     int isReplaceThreadTerminated = pthread_join(replaceThreads[i], NULL);
    //     if(isReplaceThreadTerminated != 0) {
    //         perror("Error while waiting replace thread");
    //         exit(1);
    //     }
    // }
    
    // /* creating write threads */
    // for(int i = 0; i < NUMBER_OF_WRITE_THREADS; i++) {
    //     writeThreadsData[i].thread_id = i;
    //     int isWriteThreadSuccessful = pthread_create(&writeThreads[i], NULL, write_thread, &writeThreadsData[i]);
    //     if(isWriteThreadSuccessful != 0) {
    //         perror("Error while creating write thread");
    //         exit(1);
    //     }
    // }
    // /* waiting for write threads to finish their job */
    // for(int i = 0; i < NUMBER_OF_WRITE_THREADS; i++) {
    //     int isWriteThreadTerminated = pthread_join(writeThreads[i], NULL);
    //     if(isWriteThreadTerminated != 0) {
    //         perror("Error while waiting write thread");
    //         exit(1);
    //     }
    // }

    //printLines();

    pthread_mutex_destroy(&mutex);
}