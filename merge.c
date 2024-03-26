#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CALCSIZE(x) (sizeof(x)/sizeof(x[0]))

void merge(int *orig, int origSize, int *left, int leftSize, int *right, int rightSize);
void mergeSort(int *array, int size);
void copy(int *original, int *newArr, int newSize, int startIndex);
void printArr(int *array, int size);

int main(void) {
  int array[] = {3, 2, 1, 5, 4};

  int size = CALCSIZE(array);

  printf("unsorted: \t");
  printArr(array, size);
  mergeSort(array, size);
  printf("sorted: \t");
  printArr(array, size);

  int stay = 1;
  while (stay) {
    int sizeOfArray;
    printf("enter size of array: ");
    fflush(stdout);
    scanf("%d", &sizeOfArray);

    int array[sizeOfArray];

    printf("enter array: ");
    for(int i = 0; i < sizeOfArray; i++) {
      printf("%d: ", i);
      fflush(stdout);
      scanf("%d", &array[i]);
    }

    mergeSort(array, sizeOfArray);
    printf("sorted: \t");
    printArr(array, sizeOfArray);

    printf("enter 0 to exit, 1 to continue: ");
    fflush(stdout);
    scanf("%d", &stay);
  }

  return 0;
}

void mergeSort(int *array, int size) {
  if(size == 1) return;
  int mid = size/2;
  int leftArr[mid];
  int rightArr[size - mid];
  copy(array, leftArr, mid, 0);
  copy(array, rightArr, size - mid, mid);
  // printArr(leftArr, mid);
  // printArr(rightArr, size - mid);

  mergeSort(leftArr, mid);
  mergeSort(rightArr, size - mid);

  merge(array, size, leftArr, mid, rightArr, size - mid);
}

void copy(int *original, int *newArr, int newSize, int startIndex){
  for(int i = 0; i < newSize; i++) {
    newArr[i] = original[i + startIndex];
  }
}

void merge(int *orig, int origSize, int *left, int leftSize, int *right, int rightSize){
  int origIndex = origSize - 1, leftIndex = leftSize - 1, rightIndex = rightSize - 1;
  for(int i = 0; i < origSize; i++) {
    if(leftIndex == -1){
        //printf("leftIndex negative\n");
        for(int j = 0; j <= rightIndex; j++) {
          orig[origIndex] = right[rightIndex - j];
          origIndex--;
        }

        break;
    }
    else if(rightIndex == -1){
      for(int j = 0; j <= leftIndex; j++) {
        orig[origIndex] = left[leftIndex - j];
        origIndex--;
      }

      break;
    }

    if(left[leftIndex] > right[rightIndex]) {
      orig[origIndex] = left[leftIndex];
      leftIndex--;
      //printf("left was bigger\n");
    }
    else if(left[leftIndex] < right[rightIndex]) {
      orig[origIndex] = right[rightIndex];
      rightIndex--;
    }
    else {
      orig[origIndex] = left[leftIndex];
      orig[origIndex - 1] = left[leftIndex];
      origIndex--;
    }
    origIndex--;
  }

  // printf("after merge: ");
  // printArr(orig, origSize);
  // printf("\n");
}

void printArr(int *array, int size) {
  printf("[");
  for(int i = 0; i < size - 1; i++) {
    printf("%d, ", array[i]);
  }
  printf("%d]\n", array[size - 1]);
}
