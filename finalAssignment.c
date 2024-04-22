#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void printMenu(){
    printf("Select an algorithm:\n");
    printf("1. Insertion Sort\n");
    printf("2. Bubble Sort\n");
    printf("3. Quick Sort\n");
    printf("4. Sequential Search\n");
    printf("5. Binary Search\n");
    printf("0. Exit\n");
}

void printDataMenu(){
    printf("\nSelect data size:\n");
    printf("1. 5000\n");
    printf("2. 16000\n");
    printf("3. 64000\n");
}

void printMenuChoice(int *menu){
    printf("Enter your choice:");
    scanf("%d", menu);
}

void generateData(int size, int data[]){
    srand(time(NULL));
    for(int i = 0; i < size; i++){
        data[i] = rand() % 1000; 
    }
}

void insertionSort(int data[], int size){
    for(int i = 1; i < size; i++){
        int key = data[i];
        int j = i - 1;
        while(j >= 0 && data[j] > key){
            data[j + 1] = data[j];
            j--;
        }
        data[j + 1] = key;
    }
}

void bubbleSort(int data[], int size){
    for(int i = 0; i < size - 1; i++){
        for(int j = 0; j < size - i - 1; j++){
            if(data[j] > data[j + 1]){
                int temp = data[j];
                data[j] = data[j + 1];
                data[j + 1] = temp;
            }
        }
    }
}

void swap(int* a, int* b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition(int arr[], int low, int high){
    int pivot = arr[low];
    int tempLow = low;
    int tempHigh = high;
    while(tempLow < tempHigh){
        while(arr[tempLow] <= pivot && tempLow <= high -1){
            tempLow++;
        }
        while(arr[tempHigh] > pivot && tempHigh >= low + 1){
        tempHigh--;
        }
        if(tempLow < tempHigh) swap(&arr[tempLow], &arr[tempHigh]);
    }
    swap(&arr[low], &arr[tempHigh]);
    return tempHigh;
}

void quickSort(int arr[], int low, int high){
    if(low < high){
        int partitionIndex = partition(arr, low, high);
        quickSort(arr, low, partitionIndex-1);
        quickSort(arr, partitionIndex+1, high);
    }
}

int sequentialSearch(int data[], int size, int target){
    for(int i = 0; i < size; i++){
        if(data[i] == target){
            return i;
        }
    }
    return -1;
}

int binarySearch(int data[], int size, int target){
    int low = 0, high = size - 1;
    while(low <= high){
        int mid = (low + high) / 2;
        if(data[mid] == target){
            return mid;
        } 
        else if(data[mid] < target){
            low = mid + 1;
        } 
        else{
            high = mid - 1;
        }
    }
    return -1; 
}

void timeSpent(clock_t begin, clock_t end){
    double time_spent;
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC; 
    printf("Time spent = %.2f seconds\n", time_spent) ;
}

int main(){
    int algorithmChoice = -1, dataChoice, size;
    clock_t begin, end;
    double time_spent;

    while(algorithmChoice != 0){
        printMenu();
        printMenuChoice(&algorithmChoice);
        if(algorithmChoice!=0){
            printDataMenu();
            printMenuChoice(&dataChoice);
            switch(dataChoice) {
                case 1:
                    size = 5000;
                    break;
                case 2:
                    size = 16000;
                    break;
                case 3:
                    size = 64000;
                    break;
            }
            int data[size];
            generateData(size, data);
            switch(algorithmChoice){
                case 1:
                printf("\nSorting data using Insertion Sort:\n");
                begin = clock();
                insertionSort(data, size);
                end = clock();
                timeSpent(begin, end);
                break;
                
                case 2:
                printf("\nSorting data using Bubble Sort:\n");
                begin = clock();
                bubbleSort(data, size);
                end = clock();
                timeSpent(begin, end);
                break;

                case 3:
                printf("\nSorting data using Quick Sort:\n");
                begin = clock();
                quickSort(data, 0, size - 1);
                end = clock();
                timeSpent(begin, end);
                break;

                case 4:
                printf("\nPerforming Sequential Search:\n");
                int target = data[rand() % size];
                printf("Target number = %d\n", target);
                begin = clock();
                int index = sequentialSearch(data, size, target);
                end = clock();
                if (index != -1){
                    printf("Target number %d found at %d\n", target, index);
                }
                timeSpent(begin, end);
                break;

                case 5:
                printf("\nPerforming Binary Search:\n");
                target = data[rand() % size];
                printf("Target number = %d\n", target);
                insertionSort(data, size);
                begin = clock();
                index = binarySearch(data, size, target);
                end = clock();
                if(index != -1){
                    printf("Target number %d found at %d\n", target, index);
                }
                timeSpent(begin, end);
                break;
            }
        }
    }
    return 0;
}