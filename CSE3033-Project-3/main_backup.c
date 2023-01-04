#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>
#include <string.h>
#include <ctype.h>

int NUMBER_OF_READ_THREADS;
int NUMBER_OF_UPPER_THREADS;
int NUMBER_OF_REPLACE_THREADS;
int NUMBER_OF_WRITE_THREADS;
pthread_mutex_t mutex, mutex1;

int totalNumberOfLines = 0;

// Structure for passing data to threads
typedef struct read_thread_data {
    int thread_id;
    char* filename;
} read_thread_data;

typedef struct upper_thread_data {
    int thread_id;
} upper_thread_data;

typedef struct lines_data {
    char lineString[1024];
    struct lines_data* next;
    int lineNumber;
    int isLineUppered;
    int isLineReplaced;
} lines_data;

lines_data* lines = NULL;

void addNewLine(char newLine[], int lineNumber) {
    if(lines == NULL) {
        lines = (lines_data *) malloc(sizeof(lines_data));
        lines->lineNumber = lineNumber;
        lines->isLineReplaced = 0;
        lines->isLineUppered = 0;
        strcpy(lines->lineString, newLine);
        lines->next = NULL;
        totalNumberOfLines++;
        return;
    }
    
    lines_data* tempLines = lines;
    while(tempLines->next != NULL) { tempLines = tempLines->next; }
    tempLines->next = (lines_data *) malloc(sizeof(lines_data));
    tempLines->next->lineNumber = lineNumber;
    tempLines->next->isLineReplaced = 0;
    tempLines->next->isLineUppered = 0;
    strcpy(tempLines->next->lineString, newLine);
    tempLines->next->next = NULL;
    totalNumberOfLines++;
}

// Read Thread function
void* read_thread(void* threadType) {
    read_thread_data* data = (read_thread_data*) threadType;
    int thread_id = data->thread_id;
    char* filename = data->filename;
    FILE* file = fopen(filename, "r"); // opening the file with 'read' mode
    // checking if file exists or not, if it does not exist, program will be terminating
    if(file == NULL) {
        perror("Error opening file");
        exit(1);
    }
    // Read the file line by line
    char line[1024];
    int line_number = 0;
    
    while(fgets(line, 1024, file) != NULL) {
        // Check if this thread should read this line
        
        if(line_number % NUMBER_OF_READ_THREADS == thread_id) {
            
            for(int i = 0; i < 1024; i++) { 
                if(line[i] == '\n') line[i] = '\0'; 
            }
            printf("Read_%d\t\t\tRead_%d read the line %d which is '%s'\n", thread_id, thread_id, line_number, line);
            addNewLine(line, line_number);
            
        }
        
        line_number++;
    }
    fclose(file); // closing the file that opened
    pthread_exit(NULL); // terminating the thread to allow other thread to work
}

void* upper_thread(void* threadType) {
    upper_thread_data* data = (upper_thread_data*) threadType;
    int thread_id = data->thread_id;
    lines_data* tempLines = lines;
    while(tempLines != NULL) {
        if(tempLines->isLineUppered == 0) {
            tempLines->isLineUppered = 1;
            printf("Upper threadde mutex kilitlendi -> Thread id: %d\n", thread_id);
            pthread_mutex_lock(&mutex);
            printf("Upper_%d\t\t\tUpper_%d read index %d and converted '%s' to\n", thread_id, thread_id, tempLines->lineNumber, tempLines->lineString);
            for(int i = 0; i < 1024; i++) {
                tempLines->lineString[i] = toupper(tempLines->lineString[i]);
            }
            printf("\t\t\t'%s'\n", tempLines->lineString);
            pthread_mutex_unlock(&mutex);
            printf("Upper threadde mutex kilidi acildi -> Thread id: %d\n", thread_id);
        }
        tempLines = tempLines->next;
    }
    pthread_exit(NULL);
}

void* replace_thread(void* threadType) {
    upper_thread_data* data = (upper_thread_data*) threadType;
    int thread_id = data->thread_id;
    lines_data* tempLines = lines;
    while(tempLines != NULL) {
        if(tempLines->isLineReplaced == 0) {
            tempLines->isLineReplaced = 1;
            for(int i = 0; i < 1024; i++) {
                if(tempLines->lineString[i] == ' ') {
                    tempLines->lineString[i] = '_';
                }
            }
            pthread_mutex_lock(&mutex);
            printf("Replace_%d\t\tReplace_%d read index %d and converted '%s' to\n", thread_id, thread_id, tempLines->lineNumber, tempLines->lineString);
            printf("\t\t\t'%s'\n", tempLines->lineString);
            pthread_mutex_unlock(&mutex);
        }
        tempLines = tempLines->next;
    }
    pthread_exit(NULL);
}

void* write_thread(void* threadType) {
    upper_thread_data* data = (upper_thread_data*) threadType;
    int thread_id = data->thread_id;
    lines_data* tempLines = lines;

}

void printLines() {
    lines_data* tempLines = lines;
    while(tempLines != NULL) {
        printf("Line Number: %d\tLine -> %s\n", tempLines->lineNumber, tempLines->lineString);
        tempLines = tempLines->next;
        totalNumberOfLines--;
    }
}

int main(int argc, char* argv[]) {
    if (argc != 6) {
        printf("Usage: %s <filename>\n", argv[0]);
        exit(1);
    }

    pthread_mutex_init(&mutex, NULL);

    NUMBER_OF_READ_THREADS = atoi(argv[2]);
    NUMBER_OF_UPPER_THREADS = atoi(argv[3]);
    NUMBER_OF_REPLACE_THREADS = atoi(argv[4]);
    NUMBER_OF_WRITE_THREADS = atoi(argv[5]);
    printf("Number of read threads that is gonna be created: %d\n", NUMBER_OF_READ_THREADS);
    printf("Number of upper threads that is gonna be created: %d\n", NUMBER_OF_UPPER_THREADS);
    printf("Number of replace threads that is gonna be created: %d\n", NUMBER_OF_REPLACE_THREADS);
    printf("<Thread-type and ID>\t\t\t<Output>\n");
    // creating threads
    pthread_t readThreads[NUMBER_OF_READ_THREADS];
    read_thread_data readThreadData[NUMBER_OF_READ_THREADS];

    pthread_t upperThreads[NUMBER_OF_UPPER_THREADS];
    upper_thread_data upperThreadData[NUMBER_OF_UPPER_THREADS];

    pthread_t replaceThreads[NUMBER_OF_REPLACE_THREADS];
    upper_thread_data replaceThreadData[NUMBER_OF_REPLACE_THREADS];

    for(int i = 0; i < NUMBER_OF_READ_THREADS; i++) {
        readThreadData[i].thread_id = i;
        readThreadData[i].filename = argv[1];
        int result = pthread_create(&readThreads[i], NULL, read_thread, &readThreadData[i]);
        if(result != 0) {
            perror("Error creating read thread");
            exit(1);
        }
    }
    // waiting for read threads to be completed
    for(int i = 0; i < NUMBER_OF_READ_THREADS; i++) {
        int result = pthread_join(readThreads[i], NULL);
        if(result != 0) {
            perror("Error waiting for thread");
            exit(1);
        }
    }

    printf("\n**********************************\n");
    // creating upper threads
    lines_data* tempLines = lines;
    for(int i = 0; i < NUMBER_OF_UPPER_THREADS; i++) {
        if(tempLines != NULL) {
            upperThreadData[i].thread_id = i;
            tempLines = tempLines->next;
        }
        int result = pthread_create(&upperThreads[i], NULL, upper_thread, &upperThreadData[i]);
        if(result != 0) {
            perror("Error creating upper thread");
            exit(1);
        }
    }

    //creating replace threads
    lines_data* tempLines1 = lines;
    for(int i = 0; i < NUMBER_OF_REPLACE_THREADS; i++) {
        if(tempLines1 != NULL) {
            replaceThreadData[i].thread_id = i;
            tempLines1 = tempLines1->next;
        }
        int result = pthread_create(&replaceThreads[i], NULL, replace_thread, &replaceThreadData[i]);
        if(result != 0) {
            perror("Error creating upper thread");
            exit(1);
        }
    }

    // waiting for upper threads to be completed
    for(int i = 0; i < NUMBER_OF_UPPER_THREADS; i++) {
        int result = pthread_join(upperThreads[i], NULL);
        if(result != 0) {
            perror("Error waiting for thread");
            exit(1);
        }
    }
    // waiting for upper threads to be completed
    for(int i = 0; i < NUMBER_OF_REPLACE_THREADS; i++) {
        int result = pthread_join(replaceThreads[i], NULL);
        if(result != 0) {
            perror("Error waiting for thread");
            exit(1);
        }
    }
    printf("Total number of lines: %d\n", totalNumberOfLines);
    printLines();
    printf("Total number of lines: %d\n", totalNumberOfLines);
    
    pthread_mutex_destroy(&mutex);
    
    
    return 0;
}
