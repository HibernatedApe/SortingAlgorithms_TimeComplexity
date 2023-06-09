#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include <string.h>

/* PROJECT IN DESIGN AND ANALYSIS OF ALGORITHMS: SOURCE CODE 
AUTHORS
- Jan Wilhelm T. Sy
- Chris John Borigas
- Russel Pispis
- Jovic Francis B. Rayco
*/

// ------------------------------ FUNCTION DECLARATIONS -----------------------------
unsigned long int randomNumberGenerator(unsigned long int min, unsigned long int max);
void auxArrInsertion(unsigned long int auxArr[], unsigned long int numArr[], int arrLength);

void selectionSort(unsigned long int auxArr[], int arrLength);
void bubbleSort(unsigned long int auxArr[], int maxRange);
void insertionSort(unsigned long int auxArr[], int arrLength);

void callMergeSort(unsigned long int auxArr[], int arrLength);
void merge(unsigned long int auxArr[], int start, int mid, int end);
void mergeSort(unsigned long int auxArr[], int start, int end);

void heapSort(unsigned long int auxArr[], int n);
void maxHeapify(unsigned long int auxArr[], int i, int n);
void buildMaxHeap(unsigned long int auxArr[], int n);

void callQuickSort(unsigned long int auxArr[], int arrLength);
void quickSort(unsigned long int auxArr[], int left, int right);
int partition(unsigned long int auxArr[], int left, int right);
int medianOfThree(unsigned long int auxArr[], int left, int right);

void swap(unsigned long int *a, unsigned long int *b);
void print(unsigned long int auxArr[], int arrLength);

void runSortingAlgorithm(unsigned long int numArr[], int arrLength, int option);

// ------------------------------------- MAIN METHOD ---------------------------------
int main()
{
    // Variable declarations
    int arrLength;
    int option;
    unsigned long int xNum;

    FILE *file;
    // File Handling for creating outputfile
    if (fopen("sortingFile.txt","r") == NULL)
    {
        // Create new file if expected file does not exist
        file = fopen("sortingFile.txt", "w");
    }
    else
    {
        do
        {   // Give the user the option to replace or just append to existing file
            printf("Replace File? [1->Yes | 0->No]\n");
            scanf("%d", &option);
        } 
        while(option != 1 && option != 0);
        if (option == 1)
        {
            file = fopen("sortingFile.txt", "w");
        }
        else
        {
            file = fopen("sortingFile.txt", "a");
        }
    }

    while (1) {

        // ASK FOR ARRAY LENGTH
        // Label for goto operation
        arrayLength:            
        printf("---------------------------------------\n");
        printf("Enter Array Length: ");
        scanf("%d", &arrLength);

        // Input Error Handling
        if (arrLength <= 0 || arrLength > INT_MAX) {
            printf("!! Invalid Array Length !!\n\n");
            // If Invalid Input, goto arrayLength: label
            goto arrayLength;
        }

        // Initialize array with malloc
        unsigned long int *numArr = malloc(arrLength * sizeof(unsigned long int));

        // Label for goto operation
        valueGenerator:
        printf("---------------------------------------\n");
        printf("[1] Random Values\n");
        printf("[2] Sorted in an Increasing Order\n");
        printf("[3] Exit\n\n");

        // Get user choice for choice 1 and 2.
        printf("Enter Choice [1/2/3]: ");
        scanf("%d", &option);

        if (option == 1)   {      // a) Values are randomly generated.

            // Set rand() seed as current time.
            srand(time(NULL));

            // Add random numbers into the array.
            for (int i = 0; i < arrLength; i++) {
                numArr[i] = randomNumberGenerator(0, ULONG_MAX);
            }

            // Run the sorting algorithm
            runSortingAlgorithm(numArr, arrLength, 1);

        } else if (option == 2)  {  // b) Values are sorted using the formula: N+X, N+2X, N+kX

            printf("Enter 'X' Number: ");
            do{
                scanf("%lu", &xNum);
            } while (xNum < 1);
            printf("\n");

            // Increasing numbers using formula: N+X, N+2X, N+NX, X >= 1
            for (int i = 0; i < arrLength; i++) {
                 numArr[i] = arrLength + ((i+1) * xNum);
            }

            // Run the sorting algorithm
            runSortingAlgorithm(numArr, arrLength, 2);

        } else if (option == 3) {
            break;

        } else {
            // Input Error Handling
            printf("Invalid Choice \n");
            goto valueGenerator;
        }
    }
    fclose(file);
}

// Function for running the sorting algorithms and writing to file.
void runSortingAlgorithm(unsigned long int numArr[], int arrLength, int option)
{
    // Initialize auxilliary array and file variables
    unsigned long int *auxArr = malloc(arrLength * sizeof(unsigned long int));

    FILE *file;
    file = fopen("sortingFile.txt", "a");

    if(file == NULL){
        printf("FILE NOT FOUND!");
        exit(1);
    }

    // Writing to file
    fprintf(file,"------------------------------------------------------------------------------------------------\n");
    if(option == 1){
        fprintf(file,"\t     U N S O R T E D   A R R A Y   |   Case: %d", arrLength);
    }else{
        fprintf(file,"\t     S O R T E D   A R R A Y       |   Case: %d\n", arrLength);
    }

    fprintf(file,"\n------------------------------------------------------------------------------------------------\n");

    fprintf(file,"ORIGINAL ARRAY: ");
    auxArrInsertion(auxArr, numArr, arrLength);
    fclose(file);

    print(auxArr, arrLength);

    // Run all sorting algorithms
    for(int i = 0; i < 6; i++){
        file = fopen("sortingFile.txt", "a");

        clock_t start, end;
        double cpu_time_used;

        auxArrInsertion(auxArr, numArr, arrLength);

        switch (i) {
            case 0:
                fprintf(file,"\n\n[ SELECTION SORT ]\n");
                start = clock();                    // CLOCK START
                selectionSort(auxArr, arrLength);   // Implementing SELECTION SORT
                end = clock();                      // CLOCK END
                printf("Selection Sort Done Processing! \n");
                break;
            case 1:
                fprintf(file,"\n\n[ BUBBLE SORT ]\n");
                start = clock();                    // CLOCK START
                bubbleSort(auxArr, arrLength);      // Implementing SELECTION SORT
                end = clock();                      // CLOCK END
                printf("Bubble Sort Done Processing! \n");
                break;
            case 2:
                fprintf(file,"\n\n[ INSERTION SORT ]\n");
                start = clock();                    // CLOCK START
                insertionSort(auxArr, arrLength);   // Implementing SELECTION SORT
                end = clock();                      // CLOCK END
                printf("Insertion Sort Done Processing! \n");
                break;
            case 3:
                fprintf(file,"\n\n[ MERGE SORT ]\n");
                start = clock();                    // CLOCK START
                callMergeSort(auxArr, arrLength);   // Implementing SELECTION SORT
                end = clock();                      // CLOCK END
                printf("Merge Sort Done Processing! \n");
                break;
            case 4:
                fprintf(file,"\n\n[ QUICK SORT ]\n");
                start = clock();                    // CLOCK START
                callQuickSort(auxArr, arrLength);   // Implementing SELECTION SORT
                end = clock();                      // CLOCK END
                printf("Quick Sort Done Processing! \n");
                break;
            case 5:
                fprintf(file,"\n\n[ HEAP SORT ]\n");
                start = clock();                    // CLOCK START
                heapSort(auxArr, arrLength);        // Implementing SELECTION SORT
                end = clock();                      // CLOCK END
                printf("Heap Sort Done Processing! \n");
                break;
            default:
                break;
        }

        cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
        fprintf(file,"T(N): %lf\n", cpu_time_used);
        printf("T(N): %lf\n", cpu_time_used);

        fclose(file);
        print(auxArr, arrLength);
    }

    // Closing operations
    file = fopen("sortingFile.txt", "a");

    fprintf(file,"\n\n------------------------------------------------------------------------------------------------\n\n");

    fclose(file);
}
// ------------------------------------- HELPER METHODS ---------------------------------

// Copying elements from original array to an auxillary array
void auxArrInsertion(unsigned long int auxArr[], unsigned long int numArr[], int arrLength)
{
    for(int i = 0; i < arrLength; i++){
        auxArr[i] = numArr[i];
    }
}

// Random number generator
unsigned long int randomNumberGenerator(unsigned long int min, unsigned long int max)
{
    // NOTE: min is assumed to be 0. If The min parameter is more than 0, using the maxrange of unsigned long integer as max will result in error.
    return min + rand() % (max - min);
}

// ------------------------------------- SORTING ALGORITHMS ---------------------------------

// ITERATIVES - IMPLEMENTED BY RUSSEL PISPIS
// ---------------------------------------- SELECTION SORT -----------------------------------
void selectionSort(unsigned long int auxArr[], int arrLength) 
{
    unsigned long int min;
    int index;
    int i;
    int j;
    unsigned long int temp;

    for(i = 0; i < arrLength; i++) {

        // Setting the min as the i'th element.
        min = auxArr[i];
        index = i;

        for(j = i; j < arrLength; j++) {

            // Changing the value of min if another lowest value is found.
            if(auxArr[j] < min) {
                min = auxArr[j];
                index = j;
            }

        }

        // If the index of the min value is different, swap.
        if(index != i) {
            temp = auxArr[i];
            auxArr[i] = min;
            auxArr[index] = temp;
        }

    }

}

// ----------------------------------------- BUBBLE SORT ------------------------------------
void bubbleSort(unsigned long int auxArr[], int maxRange)
{
    int i = 0;
    int j = 0;
    int checker = 0;

    // Swapping adjacent elements based on comparison result
    for(i = 0; i < maxRange - 1; i++) {
        for(j = 0; j < maxRange - i - 1; j++) {

            if(auxArr[j] > auxArr[j + 1]) {
                swap(&auxArr[j], &auxArr[j+1]);

                checker++;
            }

        }
        // To check if array is already sorted
        if(checker == 0) {break;}

    }
}

// --------------------------------------- INSERTION SORT -----------------------------------
void insertionSort(unsigned long int auxArr[], int arrLength)
{
    int i = 1;
    unsigned long int key = 0;
    int j = 0;

    // Main Loop
    while(i <= arrLength-1)
    {
        key = auxArr[i];
        j = i - 1;

        // Find correct place for the key
        while(j >= 0 && auxArr[j] > key)
        {
            auxArr[j + 1] = auxArr[j];
            j--;
        }
        auxArr[j+1] = key;
        i++;
    }
}

// MERGESORT METHODS - IMPLEMENTED BY JAN WILHELM SY
// ----------------------------------------- MERGE SORT -------------------------------------
void callMergeSort(unsigned long int auxArr[], int arrLength)
{
    // Call main mergesort algorithm
    mergeSort(auxArr, 0, arrLength - 1);
}

void mergeSort(unsigned long int auxArr[], int start, int end)
{
    if(start < end)
    {
        // Calculate middle element
        int mid = (start + end)/2;
        // Recursive calls
        mergeSort(auxArr, start, mid);
        mergeSort(auxArr, mid+1, end);
        // Call Merge function
        merge(auxArr, start, mid, end);
    }
}

void merge(unsigned long int auxArr[], int start, int mid, int end)
{
    int leftLength = mid - start + 1;
    int rightLength = end - mid;

    // Initialized auxillary arrays
    unsigned long int * left = malloc(leftLength*sizeof(unsigned long int));
    unsigned long int * right = malloc(rightLength*sizeof(unsigned long int));
    int i;

    // Place elements
    for(i = 0; i < leftLength; i++)
    {
        left[i] = auxArr[start + i];
    }
    for(i = 0; i < rightLength; i++)
    {
        right[i] = auxArr[mid + 1 + i];
    }

    // Place auxillary array elements to auxArr
    for(int x = 0, y = 0, i = start; i <= end; i++)
    {
        if(x < leftLength && (y >= rightLength || left[x] <= right[y]))
        {
            auxArr[i] = left[x];
            x++;
        }
        else
        {
            auxArr[i] = right[y];
            y++;
        }
    }

    // Free Array Memory
    free(left);
    free(right);
}

// HEAPSORT METHODS - IMPLEMENTED BY JOVIC FRANCIS B. RAYCO
// ------------------------------------------ HEAP SORT -------------------------------------
void heapSort(unsigned long int auxArr[], int n)
{
    // Call buildMaxHeap to convert the auxArr into a maxHeap
    buildMaxHeap(auxArr, n-1);

    int i = n-1;
    // Swap the root and last child values of the heap, then heapify
    while (i>0)
    {
        swap(&auxArr[0], &auxArr[i]);
        maxHeapify(auxArr, 0, i-1);
        i--;
    }
}

void maxHeapify(unsigned long int auxArr[], int i, int n)
{
    int l = 2*i + 1; // left of i
    int r = 2*i + 2; // right of i
    int largest = 0;

    // Comparison of parent value to child values
    if (l <= n && auxArr[l] > auxArr[i])
    {
        largest = l;
    }
    else
    {
        largest = i;
    }
    if (r <= n && auxArr[r] > auxArr[largest])
    {
        largest = r;
    }
    // Swapping when largest node is not the parent node, and heapifying (recursive)
    if (largest != i)
    {
        swap(&auxArr[largest], &auxArr[i]);
        maxHeapify(auxArr, largest, n);
    }
}

void buildMaxHeap(unsigned long int auxArr[], int n)
{
    // maxHeapify the floor(n/2) elements
    int internalCount = (n/2);
    while (internalCount >= 0)
    {
        maxHeapify(auxArr, internalCount, n);
        internalCount--;
    }
}

// QUICK SORT METHODS - IMPLEMENTED BY CHRIS JOHN BORIGAS
// ----------------------------------------- QUICK SORT -------------------------------------
void callQuickSort(unsigned long int auxArr[], int arrLength)
{
    // Call main quicksort function
    quickSort(auxArr, 0, arrLength - 1);

}

void quickSort(unsigned long int auxArr[], int left, int right)
{
    if (left < right)
    {
        // Partition and get the pivotIndex
        int pivotIndex = partition(auxArr, left, right);
        // Recursive Calls
        // First recursive call includes pivotIndex: Pivot is not excluded in the swapping.
        quickSort(auxArr, left, pivotIndex);
        quickSort(auxArr, pivotIndex + 1, right);
    }
}

int partition(unsigned long int auxArr[], int left, int right)
{
    // Find Index of Median of Three
    int pivotIndex = medianOfThree(auxArr, left, right);
    // Assign pivot
    unsigned long int pivot = auxArr[pivotIndex];
    // Places arrays out of bounds for the do while iterations
    int i = left - 1;
    int j = right + 1;

    // Will repeat until i >= j after the two do while loops
    while (1)
    {
        // Do while method ensures that an infinite loop is avoided
        // Strict > and < is used as pivot is not excluded in the swapping.
        do
        {
            i++;
        } while (auxArr[i] < pivot);
        do
        {
            j--;
        } while (auxArr[j] > pivot);

        // Return the index j as the pivot index for the recursive calls
        if (i >= j)
        {
            return j;
        }

        swap(&auxArr[i], &auxArr[j]);
    }
}

int medianOfThree(unsigned long int auxArr[], int left, int right)
{
    // Set mid as the middle index
    int mid = (left + right) / 2;

    if (auxArr[left] > auxArr[right] && auxArr[left] < auxArr[mid])
    {
        // Returns index of left when left is median of three
        return left;
    }
    else if (auxArr[right] > auxArr[left] && auxArr[right] < auxArr[mid])
    {
        // Returns index of right when right is median of three
        return right;
    }
    else
    {
        // Returns index of mid when mid is median of three
        return mid;
    }
}

// ------------------------------------- SORTING ALGORITHMS HELPER METHODS ---------------------------------
// MAIN SWAP METHOD - Only not used in selection sort's swapping due to different swapping implementation.
void swap(unsigned long int*a, unsigned long int*b)
{
    unsigned long int temp = *a;
    *a = *b;
    *b = temp;
}

// ARRAY PRINTING METHOD
void print(unsigned long int auxArr[], int arrLength)
{
    FILE *file;
    file = fopen("sortingFile.txt", "a");

    for (int i = 0; i < arrLength; ++i) 
    {
        fprintf(file, "%lu ", auxArr[i]);
    }
    fprintf(file, "\n");
    fclose(file);
}
