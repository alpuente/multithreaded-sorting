#multithreaded-sorting
This program is a solution to the chapter 4 programming project 2 in the OS textbook. The program takes in a filename on the command line. The file should have
integer values, one per line, which the program reads into an int array.
The program then creates 2 threads, one to sort each half of the array.
Then the program creates a third thread which merges the 2 subarrays.
The parent thread then outputs the sorted master array.

To compile the program, use the command "gcc part1.c -pthread" 
To run the command, run the executable file with a data file name on the command line.
