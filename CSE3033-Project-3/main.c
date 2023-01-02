#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_THREADS 2

// Structure for passing data to threads
typedef struct thread_data {
    int thread_id;
    char* filename;
} thread_data;

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
        int result = pthread_create(&threads[i], NULL, read_thread, &data[i]);
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
