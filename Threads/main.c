/*
    Fatih YELBOĞA - 270201028
    Berkay BAYRAK - 270201068

    NOTE: 
        - We have created the file named "sorted_numbers.csv". 
        - To prove that the program is working correctly, 
          we have printed each linked list in hashtable to the file, leaving "--------\n" between them.
        - Node values of each list will be added when the program is run.
        - When the program is run more than once, there is no problem because the file is overwritten.
*/

#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include <pthread.h>

// Structure for linked list node
typedef struct node {
    struct node* r_node;
    unsigned value;
} node;

// Structure for hash table
typedef struct hash_table {
    node** list;
    unsigned nof_element;
} hash_table;

// Structure to pass parameters to threads
typedef struct parameterPass {
    unsigned nof_threads;
    unsigned* numbers;
    unsigned start_index;
    unsigned end_index;
    hash_table* table;
} parameterPass;

// Function to count the number of elements in the CSV file
unsigned countNumOfElements(char* filename) {
    FILE* file = fopen(filename, "r");
    unsigned count = 0;
    char line[256];
    while (fgets(line, sizeof(line), file) != NULL) {
        count++;
    }
    fclose(file);
    return count - 1;
}

// Function to read numbers from the CSV file
unsigned* readNumbers(char* filename, unsigned num_element) {
    FILE* file = fopen(filename, "r");
    unsigned* numbers = malloc(num_element * sizeof(unsigned));
    unsigned i = 0;
    char line[256];
    unsigned first_line = 0;
    while (fgets(line, sizeof(line), file) != NULL) {
        if(first_line == 0){
            i++;
            first_line = 1;
            continue;
        } else {
            char* number_id = strtok(line, ",");
            char* number = strtok(NULL, ",");
            numbers[i] = atoi(number);
            i++;
        }
    }
    fclose(file);
    return numbers;
}

// Function to initialize the hash table
hash_table* initializeHashTable(unsigned numOfThread, unsigned numOfElements) {
    hash_table* table = malloc(sizeof(hash_table));
    table->list = malloc(numOfThread * (numOfThread + 1) / 2 * sizeof(node*));
    table->nof_element = numOfElements;
    for (unsigned i = 0; i < numOfThread * (numOfThread + 1) / 2; i++) {
        table->list[i] = NULL;
    }
    return table;
}

// Function to swap two nodes
void swap(node* a, node* b) {
    unsigned temp = a->value;
    a->value = b->value;
    b->value = temp;
}

// Bubble sort algorithm to sort a linked list
void* bubbleSort(void* start) {
    int swapped;
    node* ptr1;
    node* lptr = NULL;

    if (start == NULL)
        return NULL;

    do {
        swapped = 0;
        ptr1 = start;

        while (ptr1->r_node != lptr) {
            if (ptr1->value > ptr1->r_node->value) {
                swap(ptr1, ptr1->r_node);
                swapped = 1;
            }
            ptr1 = ptr1->r_node;
        }
        lptr = ptr1;
    } while (swapped);
}

// Mutex to lock or unlock
pthread_mutex_t mutex;

// Function to insert elements into the hash table
void* insertionFunction(void* parameters) {
    parameterPass* params = (parameterPass*)parameters;
    unsigned* numbers = params->numbers;
    unsigned numOfThreads = params->nof_threads;
    unsigned start_index = params->start_index;
    unsigned end_index = params->end_index;
    hash_table* table = params->table;
        
    
    for (unsigned i = start_index; i < end_index; i++) {
        node* newNode = malloc(sizeof(node));
        newNode->value = numbers[i];
        newNode->r_node = NULL;        
            
        pthread_mutex_lock(&mutex); // Acquire the lock

        unsigned mod = newNode->value % numOfThreads;

        if (table->list[mod] == NULL) {
            table->list[mod] = newNode;
        } else {
            node* current = table->list[mod];
            while (current->r_node != NULL) {
                current = current->r_node;
            }
            current->r_node = newNode;
        }        

        pthread_mutex_unlock(&mutex); // Release the lock
    }

    return NULL;
}

// Function to write node values into the file
void writeNodeValues(char* filename, hash_table* table, unsigned numOfLists){
    FILE* file = fopen(filename, "w");
    for(unsigned i = 0; i < numOfLists; i++){   
        node* current_node = table->list[i];
        while (current_node != NULL) {
            fprintf(file, "%d\n", current_node->value);
            current_node = current_node->r_node;
        }
        fprintf(file, "--------\n");
    }
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        printf("Usage: %s <numbers.csv> <numOfThreads>\n", argv[0]);
        return 1;
    }

    char* filename = argv[1];
    unsigned numOfThreads = atoi(argv[2]);

    // Count the number of elements in the CSV file
    unsigned numOfElements = countNumOfElements(filename);

    // Read the numbers from the CSV file
    unsigned* numbers = readNumbers(filename, numOfElements);

    // Initialize the hash table
    hash_table* table = initializeHashTable(numOfThreads, numOfElements);

    // Create an array of creation threads
    pthread_t creation_threads[numOfThreads];

    // Create parameterPass structures for each thread
    parameterPass params[numOfThreads];

    // Initialize the mutex
    pthread_mutex_init(&mutex, NULL);

    printf("------------------------------------------------------------\n");

    // Calculate the interval and offset for each thread
    unsigned interval = numOfElements / numOfThreads + 1;
    for (unsigned i = 0; i < numOfThreads; i++) {
        unsigned start_index = i * interval;
        unsigned end_index = start_index + interval;
        if (end_index > numOfElements) {
            end_index = numOfElements;
        }

        params[i].numbers = numbers;
        params[i].nof_threads = numOfThreads * (numOfThreads + 1) / 2;
        params[i].start_index = start_index;
        params[i].end_index = end_index;
        params[i].table = table;

        // Create threads to insert elements into the hash table
        pthread_create(&creation_threads[i], NULL, insertionFunction, &params[i]);
        printf("Thread %d has started the insertionFunction in the range of %d to %d\n", i+1, start_index, end_index);
    }

    printf("------------------------------------------------------------\n");

    // Wait for all threads to finish
    for (unsigned i = 0; i < numOfThreads; i++) {
        pthread_join(creation_threads[i], NULL);
        printf("Thread %d has finished execution the insertionFunction\n", i+1);
    }

    // Destroy the mutex
    pthread_mutex_destroy(&mutex);

    printf("------------------------------------------------------------\n");

    // Change the numOfThreads before sorting
    numOfThreads = numOfThreads * (numOfThreads + 1) / 2;

    // Create an array of sorting threads
    pthread_t sorting_threads[numOfThreads];

    // Create threads to sort elements into the hash table
    for (unsigned i = 0; i < numOfThreads; i++) {
        pthread_create(&sorting_threads[i], NULL, bubbleSort, table->list[i]);  
        printf("Thread %d has started the bubleSort\n", i+1);      
    }

    printf("------------------------------------------------------------\n");

    // Wait for all threads to finish
    for (unsigned i = 0; i < numOfThreads; i++) {
        pthread_join(sorting_threads[i], NULL);
        printf("Thread %d has finished execution the bubleSort\n", i+1);
    }

    // Write the values to the file
    writeNodeValues("sorted_numbers.csv", table, numOfThreads);

    // Cleanup: Free allocated memory
    free(numbers);
    for (unsigned i = 0; i < (numOfThreads + 1) / 2; i++) {
        node* current = table->list[i];
        while (current != NULL) {
            node* temp = current;
            current = current->r_node;
            free(temp);
        }
    }
    free(table->list);
    free(table);

    return 0;
}