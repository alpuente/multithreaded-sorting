////////////////////////////////
// Amy Puente                 //
// CS 426 Assignment 2        //
// CH. 4 Project Solution     //
////////////////////////////////

/*
This program is a solution to the chapter 4 programming project 2 in the OS textbook. The program takes in a filename on the command line. The file should have
integer values, one per line, which the program reads into an int array.
The program then creates 2 threads, one to sort each half of the array.
Then the program creates a third thread which merges the 2 subarrays.
The parent thread then outputs the sorted master array.

To compile the program, use the command "gcc part1.c -pthread" 
To run the command, run the executable file with a data file name on the command line.

*/

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>

void *runner(void *param); /* threads call this function */
int array_length, file_length;
int *array_master;

FILE *freader;  
int *read_file(char *fname) {
    freader = fopen(fname, "rt"); // open file
    int bufsize = file_length;
    char line[80];
    int integer;
    int index = 0;
    int *input = malloc(bufsize*sizeof(int));


    while (fgets(line, 80, freader) != NULL) {
        sscanf(line, "%d", &integer); // read the integer value
        input[index] = integer;
        ++index;
        ++array_length;
    }
    
    fclose(freader); // close the file    
    
    return input;
}


int read_length(char *fname) {
    freader = fopen(fname,"rt"); // open file
//    int bufsize = 80;
    char line[80];
    int file_length = 0;
    
    while (fgets(line, 80, freader) != NULL) {
        file_length += 1;
    }

    return file_length;
}

void merge(int arr[], int left, int middle, int right) {
    
    int i, j, k;
    int half1 = middle - left + 1;
    int half2 = right - middle;

    int first[half1], second[half2]; // temp arrays

    for (i = 0; i < half1; i++) {
        first[i] = arr[left + i];
    }

    for (j = 0; j < half2; j++) {
        second[j] = arr[middle + 1 + j];
    }
    
    i = 0;
    j = 0;
    k = left;

    while (i < half1 && j < half2) {
        
        if (first[i] <= second[j]) {
            arr[k] = first[i];
            ++i;
        } else {
            arr[k] = second[j];
            j++;
        }

        k++;
    }

    while (i < half1) {
        arr[k] = first[i];
        i++;
        k++;
    }

    while (j < half2) {
        arr[k] = second[j];
        j++;
        k++;
    }
}

void merge_sort(int arr[], int l, int r) {
    if (l < r) {
        int middle = (l + (r-1))/ 2;
        merge_sort(arr, l, middle);
        merge_sort(arr, middle+1, r);
        merge(arr, l, middle, r);
    }
}


int main(int argc, char *argv[])
{
    //array_length = 0;
    pthread_t tid; /* the thread identifier */
    pthread_attr_t attr; /* set of thread attributes */
    
    pthread_t tid2; // second thread id
    pthread_attr_t attr2; // second thread attributes
   
    pthread_t tid3; // third thread id
    pthread_attr_t attr3;

    char *fname = argv[1];

    file_length = read_length(fname);
    

    array_master = read_file(fname);


    char *thread_no = "first";
    
    pthread_attr_init(&attr); /* get the default attributes */
    pthread_create(&tid,&attr,runner, thread_no); /* create the thread */
    
    
    char *thread2 = "second";
    pthread_attr_init(&attr2);
    pthread_create(&tid2,&attr2, runner, thread2);
    /* wait for the thread to exit */
    
    char *thread3 = "third";
    pthread_attr_init(&attr3);
    pthread_create(&tid3, &attr2, runner, thread3);

    pthread_join(tid, NULL);
    pthread_join(tid2, NULL);
    pthread_join(tid3, NULL); 
   // printf("got here\n");
    //merge(array_master, 0, (array_length/2), array_length-1);

    int j;
    for (j = 0; j < array_length; j++) {
        if (j == array_length-1) {
            printf("%d", array_master[j]);
        } else {
            printf("%d, ", array_master[j]);
        }
    } 
    
    pthread_exit(0);    
    
    return 0;
}


void *runner(void *param)
{
    int midpoint = array_length/2;
    if (strcmp(param, "first") == 0) {
        merge_sort(array_master, 0, midpoint);
    }

    if (strcmp(param, "second") == 0) {
        merge_sort(array_master, midpoint + 1, array_length - 1);
    }

    if (strcmp(param, "third") == 0) {
        merge(array_master, 0, (array_length/2), array_length-1);
    }

    pthread_exit(0);
}
