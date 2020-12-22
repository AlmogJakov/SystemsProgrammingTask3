#include <stdio.h>
#define arrlen 50

/* The method gets a pointer and moves the
following n characters to the right */
int shift_element(int* arr, int i) {
    int *dest = (int*)arr;
    for (; i>0; i--) {
        *(dest+i) = *(dest+i-1);
    }
    return 0;
}

/* The method performs insertion sort by double-looping
and moving each number to the appropriate position */
int insertion_sort(int* arr , int len) {
    int temp = *(arr);
    int *pointer = (int*)arr;
    for (int i = 1; i<len; i++){
        temp = *(arr+i);
        for (int j = 0; j<i; j++){
            pointer = arr+j;
            if (temp<*pointer) {
                shift_element(pointer,i-j);
                *pointer = temp;
                break;
            }
        }
    }
    return 0;
}

int main() {
    int arr[arrlen];
    int *pointer = (int*)arr;
    for (int i = 0; i < arrlen; i++) {scanf(" %d", pointer+i);}
    /* call insertion sort method */
    insertion_sort(pointer,arrlen);
    /* print the sorted array */
    for (int i = 0; i < arrlen-1; i++) {printf("%d,", *(pointer++));}
    printf("%d\n", *pointer);
    return 0;
}