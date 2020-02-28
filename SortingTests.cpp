//
//  SortingTests.cpp
//  Project 5
//
//  Created by Tawhid Mahmud on 11/8/18.
//  Copyright © 2018 Tawhid Mahmud. All rights reserved.
//

#include "SortingTests.hpp"
#include <stdlib.h>
#include <chrono>

using namespace std::chrono;

using namespace std;





/**
 @post Sorts an array in ascending order using the selection sort algorithm.
 @param a the array to sort
 @param size the number of elements in a
 */


void selectionSort(int a[], size_t size) {
    int i, j, minIndex, tmp;
    for (i = 0; i < size - 1; i++) {
        minIndex = i;
        for (j = i + 1; j < size; j++)
            if (a[j] < a[minIndex])
                minIndex = j;
        if (minIndex != i) {
            tmp = a[i];
            a[i] = a[minIndex];
            a[minIndex] = tmp;
        }
    }
}

/**
 @post Sorts an array in ascending order using insertion sort.
 @param a the array to sort
 @param size of the array
 */

void insertionSort(int a[], size_t size) {
    int i, j, tmp;
    for (i = 1; i < size; i++) {
        j = i;
        while (j > 0 && a[j - 1] > a[j]) {
            tmp = a[j];
            a[j] = a[j - 1];
            a[j - 1] = tmp;
            j--;
        }
    }
}


// friend function for merge sort
void merge(int arr[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 =  r - m;
    
    /* create temp arrays */
    int *L = new int [n1];
    int *R = new int[n2];
    
    /* Copy data to temp arrays L[] and R[] */
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1+ j];
    
    /* Merge the temp arrays back into arr[l..r]*/
    i = 0; // Initial index of first subarray
    j = 0; // Initial index of second subarray
    k = l; // Initial index of merged subarray
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    
    /* Copy the remaining elements of L[], if there
     are any */
    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }
    
    /* Copy the remaining elements of R[], if there
     are any */
    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}

/**
 @post Sorts the elements in a range of a array.
 @param a the array with the elements to sort
 @param from the first position in the range to sort
 @param to the last position in the range to sort (included)
 */

void mergeSort(int a[], int l, int r)
{
    if (l < r)
    {
        // Same as (l+r)/2, but avoids overflow for
        // large l and h
        int m = l+(r-l)/2;
        
        // Sort first and second halves
        mergeSort(a, l, m);
        mergeSort(a, m+1, r);
        
        merge(a, l, m, r);
    }
}
//void mergeSort(int a[], int from, int to)
//{
//    if (to > from)
//    {
//        int middle = (from + to)/2;
//
//        mergeSort(a, from, middle); // first half of the merge sort
//        mergeSort(a, middle+1, to); //second half
//        merge(a, from, to, middle);
//        //merge2(a, from, to);
//    }
//
//}



/*********************************************************************/
/****************** ARRAY POPULATING FUNCTIONS ***********************/
/*********************************************************************/


/**
 @post Populates values with randomly generated numbers in range size
 @param values the array to populate
 @param size of the array to be populated
 */
void generateRandomArray(int values[], size_t size)
{
    for (int i = 0; i < size; ++i) {
        values[i] = rand() % size + 1;
    }
}



/**
 @post Populates values with integers in ascending order
 @param values the array to populate
 @param size of the array to be populated
 */
void generateAscendingArray(int values[], size_t size)
{
    for(int i=0; i< size; i++)
    {
        values[i]=i;
        cout << values[i] << " ";
    }
}


/**
 @post Populates values with integers in descending order
 @param values the array to populate
 @param size of the array to be populated
 */
void generateDescendingArray(int values[], size_t size)
{
    for (int i = size; i >=0; i--)
    {
        values[i] = size;
        size--;
        cout << values[i] << " ";
    }
}

/**
 @post Populates values with integers in ascending order except for the last 10 that are randomly generated
 @param values the array to populate
 @param size of the array to be populated
 */
void generateLastTenRandomArray(int values[], size_t size)
{
    int num = size - 10;
    for (int i=0; i < size; i++)
    {
        if (i <= num -1)
        {
            values[i] = i;
        }
        else
        {
            values[i] = rand() % size +1;
        }
    }
}



/**
 @post Populates values with integers in randomly generated in range size/10
 @param values the array to populate
 @param size of the array to be populated
 */void generateFewRandomArray(int values[], size_t size)
{
    int start;
    start = rand() % (size/10);
    cout << endl;
    
    for (int i=0; i < size; i++)
    {
        values[i] = start;
        start = rand() % (size/10);
        
    }

}

/*****************************************************************/
/****************** RUNTIME TEST FUNCTIONS ***********************/
/*****************************************************************/


/**
 @post Sorts values in ascending order and averages its runtime over 10 runs
 @param sortingFunction the function used to sort the array
 @param values the array to sort
 @param size of the array to sort
 @return the average runtime in microseconds
 */
double sortTest(void (*sortingFunction)(int a[], size_t size), int values[], size_t size)
{
    double runtime_sum = 0;
    
    
    //int count =0;
    for(int i =0; i< 10; i++)
    {
        int *temp = new int[size];   //dynamic array
        for(int i =0; i< size; i++)
        {
            temp[i] = values[i];
        }
        
        auto start_time = high_resolution_clock().now();
        sortingFunction(temp, size);
        auto end_time = high_resolution_clock().now();
        
        duration<float, std::micro> runt_time = duration_cast<microseconds>(end_time - start_time);
        runtime_sum += runt_time.count();
    
        delete[] temp;
    }
    
    double average = runtime_sum/10;
    cout << average << " microseconds" << endl;
    return average;
}


/**
 @post Sorts values in ascending order using mergeSort and averages its runtime over 10 runs
 @param values the array to sort
 @param size of the array to sort
 @return the average runtime in microseconds
 */
double mergeSortTest(int values[], size_t size)
{
    double runtime_sum = 0;

    
    for(int i =0; i< 10; i++)
    {
        int *temp = new int[size];   //dynamic array
        for(int j =0; j< size; j++)
        {
            temp[j] = values[j];
        }
        auto start_time = high_resolution_clock().now();
        mergeSort(temp, 0, size-1);
        auto end_time = high_resolution_clock().now();
        
        duration<float, std::micro> runt_time = duration_cast<microseconds>(end_time - start_time);
        runtime_sum += runt_time.count();
        
        delete[] temp;
    }
    
    double average = runtime_sum/10;
    
    return average;
}




