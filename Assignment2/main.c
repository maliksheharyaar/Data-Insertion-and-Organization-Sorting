/*
-------------------------------------------
Student: Malik Sheharyaar Talhat talhat@sheridan.desire2learn.com
StudentID: 991435266
-------------------------------------------
 */

/* 
 * File:   main.c
 * Author: Malik Sheharyaar Talhat talhat@sheridan.desire2learn.com
 *
 * Created on October 14, 2018, 6:44 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const unsigned int MAX_SIZE=100;
typedef unsigned int uint;

// This function will be used to swap "pointers".
void swap(char** ptr1, char** ptr2){
  char *temp = *ptr1;
  *ptr1 = *ptr2;
  *ptr2 = temp;
};

// Bubble sort function here.Referenced from https://www.geeksforgeeks.org/bubble-sort/
void bubbleSort(char** arr, uint size) {
    int i, j;
    for (i = 0; i < size - 1; i++) {
        // Last i elements are already in place 
        for (j = 0; j < size - i - 1; j++) {
            if (strlen(arr[j]) >= strlen(arr[j + 1])) {
                swap(&arr[j], &arr[j + 1]);
            }
        }
    }
};

// Read quotes from quotes.txt file file and add them to array. Adjust the size as well!
// Note: size should reflect the number of quotes in the array/quotes.txt file!
void read_in(char** arr, uint* size) {
    FILE *fp;
    char temp[*size][200];
    fp = fopen("quotes.txt", "r");
    if (fp == NULL) {
        printf("Error! The file trying to be read does not exist.");
        exit(1);
    } else {

        int i = 0; //Counter to increment array temp[]
        int j = 0; //Counter to increment array of pointers arr[].
        int quoteCounter = 0;
        char c; //Temporary variable to store characters from the file.
        //Open the file and count number of lines. Referenced from https://www.geeksforgeeks.org/c-program-count-number-lines-file/
        for (c = getc(fp); c != EOF; c = getc(fp)) {
            if (c == '\n') {
                quoteCounter++;
            }
        }
        fclose(fp);
        //Open the file again to read and store the data into an array
        FILE *fpointer;
        fpointer = fopen("quotes.txt", "r");

        for (i = 0; i < quoteCounter; i++) {
            if (i < MAX_SIZE) {
                fgets(temp[i], sizeof (temp[i]), fpointer);
                //Checks if a line consists of only 2 characters, such as '\n'
                if (strlen(temp[i]) > 2) {

                    arr[j] = (char*) calloc(1, strlen(temp[i]) + 1 * sizeof (char));
                    if (arr[j] == NULL || arr[j] == 0) {
                        printf("Cannot allocate memory of %d", strlen(temp[i]) + 1);
                        exit(1);
                    }
                    strcpy(arr[j], temp[i]);
                    j++;
                }

            } else {
                printf("The number of quotes is larger than the maximum readable size\n");
                break;
            }
        }
        //Adjust the size to the actual number of quotes
        *size = j;
        fclose(fpointer);
    }
};

// Print the quotes using array of pointers.
void print_out(char** arr, uint size) {
    int i = 0;
    while (i < size) {
        printf("%s", arr[i]);
        i++;
    }

};

// Save the sorted quotes in the output.txt file
void write_out(char** arr, uint size) {
    FILE *fpointer;
    fpointer = fopen("output.txt", "w");
    int i = 0;
    while (i < size) {
        fprintf(fpointer, "\n");
        fprintf(fpointer, arr[i]);
        i++;
    }
    fclose(fpointer);
};

// Free memory!
void free_memory(char** arr, uint size){
    int i = 0;
    while (i<size) {
        free(arr[i]);
        i++;
    }
   
};

int main() {

    // Create array of pointers. Each pointer should point to heap memory where
    // each quote is kept. I.e. arr[0] points to quote N1 saved on the heap.
    char *arr[MAX_SIZE];

    // Number of quotes in the file quotes.txt.Size is later adjusted according to number of quotes in file
    uint size=MAX_SIZE; 
    
    read_in(arr, &size);

    printf("--- Input:\n");
    print_out(arr, size);
    
    bubbleSort(arr, size);
    
    printf("--- Output:\n");    
    print_out(arr, size);
    write_out(arr, size);
    
    free_memory(arr, size);
    
    return (0);
}