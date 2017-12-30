#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef u_int8_t byte;

void swap_int(int *a, int *b);
void allocateArray_int(int **arrPtr, byte arrLen);
void getArrElemVals(int **arrPtr, int len);
void copyValue_int(int **dest, int **org, byte from, byte to);
void bubbleSort(int **arrPtr, byte arrLen);
void mergeSort(int **arrPtr, byte arrLen);
void printArrElems(int *arr, byte arrLen);


/*/ The Main Program /*/
int main() {

    // Variables
    auto int *arr;
    byte arrLen;

    // Get Array with It's Length
    printf( "Please enter a length for array (even): " );
    scanf("%i", &arrLen);

    // Exit If The Length is Greater than 255
    if(arrLen > 255) exit(0);
    // if(arrLen % 2 != 0) exit(0);

    // Allocated Array and Point to It
    allocateArray_int(&arr, arrLen);

    // Get Value of Elements from User
    getArrElemVals(&arr, arrLen);

    // Sort The Array Using Merge Sort Algorithm
    mergeSort(&arr, arrLen);

    // Print Array Elements
    printArrElems(arr, arrLen);

    free(arr);
    return 0;
}

/*/ Swap Values /*/
void swap_int(int *a, int *b){

    auto int tmp = *a;
    *a = *b;
    *b = tmp;

}

/*/ Point to Allocated Array /*/
void allocateArray_int(int **arrPtr, byte arrLen){

    *arrPtr = calloc( (size_t) arrLen, sizeof(int) );

    if (*arrPtr == NULL) {
        printf("\nArray Allocation FAILED !!!\n");
        abort();
    }

}

/*/ Get Value of Array Elements from User Input /*/
void getArrElemVals(int **arrPtr, int len){

    for( register byte i = 0; i < len; i++ ){

        printf("Value of Index %i: ", i);
        scanf( "%i", (*arrPtr + i) );

    }

}

/*/ Copy Arr /*/
void copyValue_int(int **dest, int **org, byte from, byte to){

    for (register byte i = 0, j = from; j < to; i++, j++)
        *(*dest + i) = *(*org + j);

}

/*/ Append Arr /*/
void appendValue_int(int **dest, int *org, byte orgLen){

    memcpy(*dest, org, orgLen * sizeof(int));
    return;

}

/*/ Sort Array Using Bubble Sort Algorithm /*///e.g. {12, 6, 9, 11, 7, 10, 2, 5, 3, 1, 4, 8}
void bubbleSort(int **arrPtr, byte arrLen) {

    // Main-Gauging
    for (register byte i = arrLen - 1; i > 0; i--) {

        // Sub-Gauging
        for (register byte j = 0; j < i; j++) {

            // Swap
            // if :: This Element is Greater Than The Next One
            if (*(*arrPtr + j) > *(*arrPtr + j + 1)) {

                swap_int(*arrPtr + j, *arrPtr + j + 1);

            }

        }

    }

}

/*/ Sort Array Using Merge Sort Algorithm /*/
//e.g. {12, 6, 9, 11, 7, 10, 2, 5, 3, 1, 4, 8}
//e.g. {4, 3, 2, 1}
void mergeSort(int **arrPtr, byte arrLen){

    if (arrLen < 2) return;

    // Define Left & Right Arrays
    byte leftLen = (byte) ceil(arrLen / 2.0);
    byte rightLen = (byte) floor(arrLen / 2.0);
    auto int *leftArr ; allocateArray_int(&leftArr, leftLen);
    auto int *rightArr; allocateArray_int(&rightArr, rightLen);

    // Copy Left & Right Values in Them
    copyValue_int(&leftArr, arrPtr, 0, leftLen);
    copyValue_int(&rightArr, arrPtr, leftLen, arrLen);

    // Sort The Left And Right
    mergeSort(&leftArr, leftLen);
    mergeSort(&rightArr, rightLen);

    /////////////////////////
    // Merge Them Together //
    /////////////////////////
    register byte k = 0; // Main Array Index
    register byte i = 0; // Left Array Index
    register byte j = 0; // Right Array Index
    // After Using Them We Need a SubArray
    auto int *subArr;
    register byte subArrLen = 0;

    // Loop
    // if :: left indexes are not finished
    // and if :: right indexes are not finished
    while (i < leftLen && j < rightLen) {

        // if :: right element is greater than the left one
        if(*(leftArr + i) < *(rightArr + j)) {

            *(*arrPtr + k) = *(leftArr + i);
            i++;

        // else if :: left element is greater than the right one or they are equivalent
        } else {

            *(*arrPtr + k) = *(rightArr + j);
            j++;

        }
        k++;

    }

    ////////////////////////////////////////////////
    // Let's use the sub array (( if necessary )) //
    ////////////////////////////////////////////////

    // if :: left indexes are finished
    if (i == leftLen && j != rightLen) {

        // Make Left Array Free (( we don't need it more ))
        free(leftArr);

        // Calculate The Length of Sub Array
        subArrLen = rightLen - j;

        // Keep Right Array Remained Elements
        allocateArray_int(&subArr, subArrLen);

        // Copy Values on Sub Array
        copyValue_int(&subArr, &rightArr, j, rightLen);

        // Bubble Sort on Them
        bubbleSort(&subArr, subArrLen);

        // Skip The Next If Statement
        goto subArrayIsReady;

    }

    // if :: right indexes are finished
    if (j == rightLen && i != leftLen) {

        // Make Right Array Free (( we don't need it more ))
        free(rightArr);

        // Calculate The Length of Sub Array
        subArrLen = leftLen - i;

        // Keep Right Array Remained Elements
        allocateArray_int(&subArr, subArrLen);

        // Copy Values on Sub Array
        copyValue_int(&subArr, &leftArr, i, leftLen);

        // Merge Sort on Them
        bubbleSort(&subArr, subArrLen);

    }

    subArrayIsReady:

    // Append The Sorted Sub Array to The Main Array (( if it has any element ))
    if (subArrLen > 0) {

        register byte l = 0; // The Sub Array Index
        while (k < arrLen) {

            *(*arrPtr + k) = *(subArr + l);
            l++;
            k++;

        }

    }

}

/*/ Show Array Elements /*/
void printArrElems(int *arr, byte arrLen){

    for (register byte i = 0; i < arrLen; i++)
        printf("%i, ", *(arr + i));

    printf("\b\b\n");

}