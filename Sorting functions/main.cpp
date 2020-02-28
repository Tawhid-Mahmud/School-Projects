#include <iostream>
#include "SortingTests.hpp"

using namespace std;

int main() {
    
    const size_t SMALL_ARRAY_SIZE = 100;
    const size_t MEDIUM_ARRAY_SIZE = 1000;
    const size_t LARGE_ARRAY_SIZE = 10000;
    const size_t HUGE_ARRAY_SIZE = 100000;
    
    int values[SMALL_ARRAY_SIZE];
    int value[LARGE_ARRAY_SIZE];
    generateAscendingArray(values, SMALL_ARRAY_SIZE);
        cout << "Elapsed time for merge sort averaged over 10 runs on array of size " << SMALL_ARRAY_SIZE << " is: " << mergeSortTest(value, LARGE_ARRAY_SIZE)<< " microseconds" << endl;
    
//    //*** FIRST TEST RANDOM VALUES ON SMALL_ARRAY_SIZE ***/
//
//    generateRandomArray(values, SMALL_ARRAY_SIZE);
//    cout << "Elapsed time for selection sort averaged over 10 runs on array of size " << SMALL_ARRAY_SIZE << " is: " << sortTest(&selectionSort, values, LARGE_ARRAY_SIZE)<< " microseconds" << endl;
//
//    generateRandomArray(values, SMALL_ARRAY_SIZE);
//    cout << "Elapsed time for insertion sort averaged over 10 runs on array of size " << SMALL_ARRAY_SIZE << " is: " << sortTest(&insertionSort, values, SMALL_ARRAY_SIZE)<< " microseconds" << endl;
//
//    generateRandomArray(values, SMALL_ARRAY_SIZE);
//    cout << "Elapsed time for merge sort averaged over 10 runs on array of size " << SMALL_ARRAY_SIZE << " is: " << mergeSortTest(values, LARGE_ARRAY_SIZE)<< " microseconds" << endl;
//
//    //*** SECOND TEST SORTED VALUES ON SMALL_ARRAY_SIZE ***/
//
//    generateAscendingArray(values, SMALL_ARRAY_SIZE);
//    cout << "Elapsed time for selection sort averaged over 10 runs on array of size " << SMALL_ARRAY_SIZE << " is: " << sortTest(&selectionSort, values, LARGE_ARRAY_SIZE)<< " microseconds" << endl;
//
//    generateAscendingArray(values, SMALL_ARRAY_SIZE);
//    cout << "Elapsed time for insertion sort averaged over 10 runs on array of size " << SMALL_ARRAY_SIZE << " is: " << sortTest(&insertionSort, values, SMALL_ARRAY_SIZE)<< " microseconds" << endl;
//
//    generateAscendingArray(values, SMALL_ARRAY_SIZE);
//    cout << "Elapsed time for merge sort averaged over 10 runs on array of size " << SMALL_ARRAY_SIZE << " is: " << mergeSortTest(values, LARGE_ARRAY_SIZE)<< " microseconds" << endl;
//
//
//    // YOU SHOULD GET THE IDEA! DO THIS FOR ALL ARRAY-TYPES AND FOR ALL ARRAY-SIZES.
//    //  RUN THESE TESTS ONE AT A TIME ESPECIALLY FOR LARGER ARRAY SIZES
//    //  OBSERVE AND COMPARE THE REPORTED TIMES AND MAKE SURE THEY MAKE SENSE
//
    return 0;
}
