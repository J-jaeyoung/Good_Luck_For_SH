#include <stdio.h>
#include <stdlib.h>

int *get_next_process(int *prev_pointer, int size){
    int next_size;
    int *next_pointer;

    next_size = (size+1) / 2;
    int is_first = prev_pointer[0] < prev_pointer[size-1] ? 1 : 0;

    next_pointer = malloc(sizeof(int) * next_size);
    int PTR = 0;
    
    if(is_first){
        for(int i = size - 1; i >= 0; i -= 2){
            next_pointer[PTR++] = prev_pointer[i] + prev_pointer[i-1];
        }
    } else{
        for(int i = 0; i <= size - 1; i += 2){
            next_pointer[PTR++] = prev_pointer[i] + prev_pointer[i+1];
        }
    }
    return next_pointer;       
}

int main(){
    int N, size;
    int *candy_boxed;
    scanf("%d",&N);
    candy_boxed = malloc(sizeof(int) * N);
    
    for(int i = 0; i < N; i++){
        scanf("%d",candy_boxed + i);
    }
    size = N;
    while(size != 1){
        int* tmp = get_next_process(candy_boxed, size);
        free(candy_boxed);
        candy_boxed = tmp;
        size = (size+1) / 2;
        for(int i = 0; i < size; i++){
            printf("%d ", candy_boxed[i]);
        }
        printf("\n");
    }
}
