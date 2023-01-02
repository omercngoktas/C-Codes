#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <semaphore.h>

#define NUM_THREADS 5

// Structure for passing data to threads
typedef struct thread_data {
    int thread_id;
    char** array;
    int size;
    char* filename;
} thread_data;

// Array to store lines read from the file
char** line_array;

// Semaphores for synchronizing threads
sem_t sem_upper;
sem_t sem_replace;
sem_t sem_write;

// Read Thread function
void* read_thread(void* thread_arg) {
    thread_data* data = (thread_data*) thread_arg;
    int thread_id = data->thread_id;
    char* filename = data->filename;

    // Open the file
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        exit(1);
    }

    // Read the file line by line
    char line[1024];
    int line_number = 0;
    while (fgets(line, 1024, file) != NULL) {
        // Check if this thread should read this line
        if (line_number % NUM_THREADS == thread_id) {
            printf("Thread %d: %s", thread_id, line);
        }
        line_number++;
    }

    // Close the file
    fclose(file);

    pthread_exit(NULL);
}

// Upper Thread function
void* upper_thread(void* thread_arg) {
    thread_data* data = (thread_data*) thread_arg;
    int thread_id = data->thread_id;
    char** array = data->array;
    int size = data->size;

    while (1) {
        // Wait for a new line to be available
        sem_wait(&sem_upper);

        // Process the array
        for (int i = 0; i < size; i++) {
            // Check if this thread should process this index
            if (i % NUM_THREADS == thread_id) {
                // Convert the string to uppercase
                int length = strlen(array[i]);
                for (int j = 0; j < length; j++) {
                    array[i][j] = toupper(array[i][j]);
                }
            }
        }

        // Signal the replace threads that a line has been modified
        sem_post(&sem_replace);
    }
}

void* replace_thread(void* thread_arg) {
    thread_data* data = (thread_data*) thread_arg;
    int thread_id = data->thread_id;
    char** array = data->array;
    int size = data->size;

    while (1) {
        // Wait for a line to be modified by the upper threads
        sem_wait(&sem_replace);

        // Find an unmodified index in the array
        int index = -1;
        for (int i = 0; i < size; i++) {
            if (i % NUM_THREADS == thread_id) {
                index = i;
                break;
            }
        }

        // If no unmodified index was found, continue to the next iteration
        if (index == -1) {
            continue;
        }

        // Replace all spaces in the string with underscores
        int length = strlen(array[index]);
        for (int i = 0; i < length; i++) {
            if (array[index][i] == ' ') {
                array[index][i] = '_';
            }
        }

        // Signal that the line has been modified
        sem_post(&sem_write);
    }

    pthread_exit(NULL);
}

// Write Thread function
void* write_thread(void* thread_arg) {
    thread_data* data = (thread_data*) thread_arg;
    int thread_id = data->thread_id;
    char** array = data->array;
    int size = data->size;
    char* filename = data->filename;

    while (1) {
        // Wait for a line to be modified by the replace threads
        sem_wait(&sem_write);

        // Open the file
        FILE* file = fopen(filename, "w");
        if (file == NULL) {
            perror("Error opening file");
            exit(1);
        }

        // Write the array to the file
        for (int i = 0; i < size; i++) {
            fprintf(file, "%s", array[i]);
        }

        // Close the file
        if (fclose(file) != 0) {
            perror("Error closing file");
            exit(1);
        }

        // Release the semaphore
        sem_post(&sem_write);
    }

    pthread_exit(NULL);
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        exit(1);
    }

    // Create the threads
    pthread_t threads[NUM_THREADS];
    thread_data data[NUM_THREADS];
    for (int i = 0; i < NUM_THREADS; i++) {
        data[i].thread_id = i;
        data[i].filename = argv[1];
        int result1 = pthread_create(&threads[i], NULL, upper_thread, &data[i]);
        printf("Result1 -> %d\n", result1);
        int result = pthread_create(&threads[i], NULL, read_thread, &data[i]);
        printf("Result -> %d\n", result);
        if (result != 0) {
            perror("Error creating thread");
            exit(1);
        }
    }

    // Wait for all threads to complete
    for (int i = 0; i < NUM_THREADS; i++) {
        int result = pthread_join(threads[i], NULL);
        if (result != 0) {
            perror("Error waiting for thread");
            exit(1);
        }
    }

    return 0;
}
