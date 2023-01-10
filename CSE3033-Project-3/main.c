#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>
#include <string.h>
#include <ctype.h>

#define LINE_LENGTH 1024

/* this values are taken from argc argv */
int NUMBER_OF_READ_THREADS;
int NUMBER_OF_UPPER_THREADS;
int NUMBER_OF_REPLACE_THREADS;
int NUMBER_OF_WRITE_THREADS;
char* fileName;

/* creating a mutex*/
pthread_mutex_t mutex;

/* this struct is for identifying a thread with int value */
typedef struct thread_data {
    int thread_id;
} thread_data;

typedef struct line {
    char lineString[LINE_LENGTH];
    int lineNumber;
    int isLineUppered;
    int isLineReplaced;
    int isLineModified;
    int isLineUpperingOrReplacing;
} lines;

/* this pointer holds the data of lines */
lines* textLines;

/* this variable holds the size of 'textLines' */
int sizeOfLines = 0;

/* this function unlocks all the lines for threads to use lines */
void unlockAllLines() {
    for(int i = 0; i < sizeOfLines; i++) {
        textLines[i].isLineUppered = 0;
        textLines[i].isLineReplaced = 0;
        textLines[i].isLineUpperingOrReplacing = 0;
        textLines[i].isLineModified = 0;
    }
}

/*
addNewLine function takes 2 parameters which are newLine and lineNumber.
this line is added to 'textLines'.
*/
void addNewLine(char newLine[], int lineNumber) {
    /* if there is no line added before */
    if(sizeOfLines == 0) {
        /* creating a new pointer and allocatin a memory place with malloc */
        lines* newTextLines = (lines*) malloc((lineNumber + 1) * sizeof(lines));
        newTextLines[lineNumber].lineNumber = lineNumber;
        strcpy(newTextLines[lineNumber].lineString, newLine);
        textLines = newTextLines;
        /* changing the size of 'textLines' */
        sizeOfLines = lineNumber + 1;
        return;
    }
    /*
    if the new line's linenumber is greater or equal to size of current 'textLines',
    that means we need to allocate more memory place for the pointer, because we cannot
    store the line 6 to pointer that has 4 place in memory. because the values are assigned
    to indexes of textLines according to their linenumber.
    */
    if(lineNumber >= sizeOfLines) {
        lines* newTextLines = (lines*) malloc((lineNumber + 1) * sizeof(lines));
        
        for(int i = 0; i < sizeOfLines; i++) {
            newTextLines[i].lineNumber = textLines[i].lineNumber;
            strcpy(newTextLines[i].lineString, textLines[i].lineString);
        }
        newTextLines[lineNumber].lineNumber = lineNumber;
        strcpy(newTextLines[lineNumber].lineString, newLine);
        textLines = newTextLines;
        sizeOfLines = lineNumber + 1;
        return;
    }
    /*
    new line's linenumber is smaller than current size, so there is no need to allocate new memory place,
    new line can be stored directly to its index.
    */
    textLines[lineNumber].lineNumber = lineNumber;
    strcpy(textLines[lineNumber].lineString, newLine);
}

/* this is the function for read threads */
void* readThread(void* threadType) {
    thread_data* read_thread_data = (thread_data*) threadType;
    int thread_id = read_thread_data->thread_id;
    
    /* opening the input file */
    FILE* textFile = fopen(fileName, "r");
    /* if the file does not exist */
    if(textFile == NULL) {
        perror("Error while opening text file");
        exit(1);
    }

    /* initializing new variables for a line */
    char readLine[LINE_LENGTH];
    int lineNumber = 0;

    while(fgets(readLine, LINE_LENGTH, textFile) != NULL) {
        /* using % operator for assigning a line to a thread */
        if(lineNumber % NUMBER_OF_READ_THREADS == thread_id) {
            /* mutex is locked */
            pthread_mutex_lock(&mutex);
            // deleting new line character ('\n') from the line 
            for(int i = 0; i < LINE_LENGTH; i++) {
                if(readLine[i] == '\n') readLine[i] = '\0';
            }
            printf("Read_%d\t\t\tRead_%d read the line %d which is '%s'\n", thread_id, thread_id, lineNumber, readLine);
            /* passing data of line to add it to textLine pointer */
            addNewLine(readLine, lineNumber);
            /* mutex is unlocked */
            pthread_mutex_unlock(&mutex);
        }
        /* incrementing the number of current line according to % operator and id of thread */
        lineNumber++;
    }  
    /* closing the opened input file */
    fclose(textFile);
    /* terminating the current thread */
    pthread_exit(NULL);
}

/* this is the function for upper threads */
void* upperThread(void* threadType) {
    thread_data* upper_thread_data = (thread_data*) threadType;
    int thread_id = upper_thread_data->thread_id;

    int readLineNumber = 0;
    for(int i = 0; i < sizeOfLines; i++) {
        if(readLineNumber % NUMBER_OF_UPPER_THREADS == thread_id) {
            /* with while loop, if replace thread is working on this line, it waits until replace thread is done with its job */
            while(textLines[readLineNumber].isLineUpperingOrReplacing == 1);
            /* locking the current line, so it can be modified by only this thread */
            textLines[readLineNumber].isLineUpperingOrReplacing = 1;
            /* locking the mutex */
            pthread_mutex_lock(&mutex);
            if(textLines[readLineNumber].isLineReplaced == 1) {
                textLines[readLineNumber].isLineModified = 1;
            }   
            printf("Upper_%d\t\t\tUpper_%d read index %d and converted '%s' to\n", thread_id, thread_id, readLineNumber, textLines[readLineNumber].lineString);
            /* converting lowercase letters to uppercase letters */
            for(int j = 0; j < LINE_LENGTH; j++) {
                textLines[readLineNumber].lineString[j] = toupper(textLines[readLineNumber].lineString[j]);
            }
            printf("\t\t\t\t'%s'\n", textLines[readLineNumber].lineString);
            /* unlocking the current line, so it can be modified by only this thread */
            textLines[readLineNumber].isLineUpperingOrReplacing = 0;
            textLines[readLineNumber].isLineUppered = 1;
            /* unlocking the mutex */
            pthread_mutex_unlock(&mutex);
        }
        readLineNumber++;
    }
    /* terminating the current thread */
    pthread_exit(NULL);
}

/* this is the function for replace threads */
void* replaceThread(void* threadType) {
    thread_data* data = (thread_data*) threadType;
    int thread_id = data->thread_id;

    int readLineNumber = 0;
    for(int i = 0; i < sizeOfLines; i++) {
        if(readLineNumber % NUMBER_OF_REPLACE_THREADS == thread_id) {
            /* with while loop, if read thread is working on this line, it waits until read thread is done with its job */
            while(textLines[readLineNumber].isLineUpperingOrReplacing == 1);
            /* locking the current line, so upper thread cannot access it */
            textLines[readLineNumber].isLineUpperingOrReplacing = 1;
            /* mutex is unlocked */
            pthread_mutex_lock(&mutex);
            if(textLines[readLineNumber].isLineUppered == 1) {
                textLines[readLineNumber].isLineModified = 1;
            }
            printf("Replace_%d\t\tReplace_%d read index %d and converted '%s' to\n", thread_id, thread_id, readLineNumber, textLines[readLineNumber].lineString);
            /* changing the space characters to underscore character in the current line */
            for(int j = 0; j < LINE_LENGTH; j++) {
                if(textLines[readLineNumber].lineString[j] == ' ') { textLines[readLineNumber].lineString[j] = '_'; }
            }
            printf("\t\t\t\t'%s'\n", textLines[readLineNumber].lineString);
            /* unlocking the line so upper thread can also use it */
            textLines[readLineNumber].isLineUpperingOrReplacing = 0;
            textLines[readLineNumber].isLineReplaced = 1;
            /* mutex is unlocked */
            pthread_mutex_unlock(&mutex);
        }
        readLineNumber++;
    }
    /* terminating the current thread */
    pthread_exit(NULL);
}

int isNumber(char argm2[], char argm3[], char argm4[], char argm5[]) {
    int incr = 0;
    if(argm2[0] == '-') { incr = 1; }
    for(; argm2[incr] != 0; incr++) { if(!isdigit(argm2[incr])) return 0; }
    incr = 0;
    if(argm3[0] == '-') { incr = 1; }
    for(; argm3[incr] != 0; incr++) { if(!isdigit(argm3[incr])) return 0; }
    incr = 0;
    if(argm4[0] == '-') { incr = 1; }
    for(; argm4[incr] != 0; incr++) { if(!isdigit(argm4[incr])) return 0; }
    incr = 0;
    if(argm5[0] == '-') { incr = 1; }
    for(; argm5[incr] != 0; incr++) { if(!isdigit(argm5[incr])) return 0; }
    return 1;
}

void isFileExist(char checkFile[]) {
    FILE* textFile = fopen(checkFile, "r");
    if(textFile == NULL) {
        printf("Error while opening text file: No such file or directory\n");
        exit(1);
    }
}

/* changing the line with modified line */
void changeLineInFile(char line[], int indexOfLine) {
    char lineToChange[LINE_LENGTH];
    int currentLine = 0;
    FILE* textFile = fopen(fileName, "r+");

    /* adding a '\n' character to end of the line*/
    for(int i = 0; i < LINE_LENGTH; i++) {
        if(line[i] == '\0') {
            line[i] = '\n';
            line[i+1] = '\0';
            break;
        }
    }

    /* if the given line is the first line */
    if(indexOfLine == 0) {
        fputs(line,textFile);
        return;
    }

    /* updating the old line with modified line */
    while(fgets(lineToChange, LINE_LENGTH, textFile) != NULL) {
        currentLine++;
        if(currentLine == indexOfLine) {
            fputs(line, textFile);
            break;
        }
    }
    /* closing the file */
    fclose(textFile);
}

/* this is the function for write threads */
void* writeThread(void* threadType) {
    thread_data* data = (thread_data*) threadType;
    int thread_id = data->thread_id;

    /* opening the file to modify */
    FILE* textFile = fopen(fileName, "r+");
    /* if file does not happen, file has to be created firstly */
    if(textFile == NULL) {
        textFile = fopen(fileName, "r+");
    }
    fclose(textFile);

    int lineNumber = 0;
    for(int i = 0; i < sizeOfLines; i++) {
        /* assigning a line to current thread */
        if(lineNumber % NUMBER_OF_WRITE_THREADS == thread_id) {
            while(textLines[lineNumber].isLineModified == 0);
            /* locking mutex */
            pthread_mutex_lock(&mutex);
            printf("Write_%d\t\t\tWrite_%d write line %d back which is '%s'\n", thread_id, thread_id, lineNumber, textLines[lineNumber].lineString);
            /* passing values to function */
            changeLineInFile1(textLines[lineNumber].lineString, lineNumber);
            /* unlocking mutex */
            pthread_mutex_unlock(&mutex);
        }
        lineNumber++;
    }
    /* terminating current write thread */
    pthread_exit(NULL);
}

int main(int argc, char* argv[]) {
    /* if given argument number is not 6, the program is going to be terminated */
    if(argc != 6) {
        printf("Usage: %s <fileName> <numberOfReadThreads> <numberOfUpperThreads> <numberOfReplaceThreads> <numberOfWriteThreads>\n", argv[0]);
        exit(1);
    }
    isFileExist(argv[1]);

    int isArgNumber = isNumber(argv[2], argv[3], argv[4], argv[5]);
    if(isArgNumber == 0) {
        printf("Usage: %s <fileName> <numberOfReadThreads> <numberOfUpperThreads> <numberOfReplaceThreads> <numberOfWriteThreads>\n", argv[0]);
        exit(1);
    }

    /* initializing a mutex */
    pthread_mutex_init(&mutex, NULL);

    /* assigning arguments given for main */
    fileName = argv[1];
    NUMBER_OF_READ_THREADS = atoi(argv[2]);
    NUMBER_OF_UPPER_THREADS = atoi(argv[3]);
    NUMBER_OF_REPLACE_THREADS = atoi(argv[4]);
    NUMBER_OF_WRITE_THREADS = atoi(argv[5]);

    /* creating thread id read threads */
    pthread_t readThreads[NUMBER_OF_READ_THREADS];
    thread_data readThreadsData[NUMBER_OF_READ_THREADS];
    /* creating thread id upper threads */
    pthread_t upperThreads[NUMBER_OF_UPPER_THREADS];
    thread_data upperThreadsData[NUMBER_OF_UPPER_THREADS];
    /* creating thread id replace threads */
    pthread_t replaceThreads[NUMBER_OF_REPLACE_THREADS];
    thread_data replaceThreadsData[NUMBER_OF_REPLACE_THREADS];
    /* creating thread id write threads */
    pthread_t writeThreads[NUMBER_OF_WRITE_THREADS];
    thread_data writeThreadsData[NUMBER_OF_WRITE_THREADS];

    printf("<Thread-type and ID>\t\t<Output>\n");

    /* creating read threads */
    for(int i = 0; i < NUMBER_OF_READ_THREADS; i++) {
        /* assigning int value from 0 to max number of threads created to identify a thread */
        readThreadsData[i].thread_id = i;
        int isReadThreadSuccessful = pthread_create(&readThreads[i], NULL, readThread, &readThreadsData[i]);
        /* if an error occurs while creating read thread */
        if(isReadThreadSuccessful != 0) {
            perror("Error while creating read thread");
            exit(1);
        }
    }
    /* waiting for read threads to finish their job */
    for(int i = 0; i < NUMBER_OF_READ_THREADS; i++) {
        int isReadThreadTerminated = pthread_join(readThreads[i], NULL);
        /* if an error occurs while terminating read thread */
        if(isReadThreadTerminated != 0) {
            perror("Error while waiting read thread");
            exit(1);
        }
    }
    /*
        when we tried to assing a value of 0 to a variable to check if line is using by upper or replace thread
        so the thread should wait if it is using by another thread. however, we got an error. so, after reading
        all the lines from file, we change this lock value in a function which is called unlockAllLines.
    */
    unlockAllLines();
    /* creating write threads */
    for(int i = 0; i < NUMBER_OF_WRITE_THREADS; i++) {
        /* assigning int value from 0 to max number of threads created to identify a thread */
        writeThreadsData[i].thread_id = i;
        int isWriteThreadSuccessful = pthread_create(&writeThreads[i], NULL, writeThread, &writeThreadsData[i]);
        /* if an error occurs while creating write thread */
        if(isWriteThreadSuccessful != 0) {
            perror("Error while creating write thread");
            exit(1);
        }
    }
    /* creating upper threads */
    for(int i = 0; i < NUMBER_OF_UPPER_THREADS; i++) {
        /* assigning int value from 0 to max number of threads created to identify a thread */
        upperThreadsData[i].thread_id = i;
        int isUpperThreadSuccessful = pthread_create(&upperThreads[i], NULL, upperThread, &upperThreadsData[i]);
        /* if an error occurs while creating upper thread */
        if(isUpperThreadSuccessful != 0) {
            perror("Error while creating upper thread");
            exit(1);
        }
    }
    /* creating replace threads */
    for(int i = 0; i < NUMBER_OF_REPLACE_THREADS; i++) {
        /* assigning int value from 0 to max number of threads created to identify a thread */
        replaceThreadsData[i].thread_id = i;
        int isReplaceThreadSuccessful = pthread_create(&replaceThreads[i], NULL, replaceThread, &replaceThreadsData[i]);
        /* if an error occurs while creating replace thread */
        if(isReplaceThreadSuccessful != 0) {
            perror("Error while creating replace thread");
            exit(1);
        }
    }
    /* waiting for upper threads to finish their job */
    for(int i = 0; i < NUMBER_OF_UPPER_THREADS; i++) {
        int isUpperThreadTerminated = pthread_join(upperThreads[i], NULL);
        /* if an error occurs while terminating upper thread */
        if(isUpperThreadTerminated != 0) {
            perror("Error while waiting upper thread");
            exit(1);
        }
    }
    /* waiting for replace threads to finish their job */
    for(int i = 0; i < NUMBER_OF_REPLACE_THREADS; i++) {
        int isReplaceThreadTerminated = pthread_join(replaceThreads[i], NULL);
        /* if an error occurs while terminating replace thread */
        if(isReplaceThreadTerminated != 0) {
            perror("Error while waiting replace thread");
            exit(1);
        }
    }
    
    /* waiting for write threads to finish their job */
    for(int i = 0; i < NUMBER_OF_WRITE_THREADS; i++) {
        int isWriteThreadTerminated = pthread_join(writeThreads[i], NULL);
        /* if an error occurs while terminating write thread */
        if(isWriteThreadTerminated != 0) {
            perror("Error while waiting write thread");
            exit(1);
        }
    }
    /* killing the mutex */
    pthread_mutex_destroy(&mutex);
}