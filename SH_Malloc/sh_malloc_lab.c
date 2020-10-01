#include <stdio.h>
#include <stdlib.h>
/*
    Mini Malloc for SH

    목표: malloc과 free를 사용하여 자신만의 malloc, free, calloc, realloc 구현해보기.
         sh_malloc, sh_calloc, sh_realloc 이후에 free를 사용했으면 더이상 메모리에 할당된 공간이 없어야 한다.
         예를 들어, sh_malloc 은 주소 100~200을 할당해줬는데, sh_free 가 주소 110~200만 해제해준다면 잘못 구현된 것.
         sh_malloc은 내부적으로 malloc을 사용한다.
         sh_free는 내부적으로 free를 사용한다.
         sh_calloc 과 sh_realloc 은 내부적으로 sh_malloc와 sh_free을 사용한다.
         
    여기서 말하는 모든 int는 0이상의 정수만 생각한다.
*/


// 정수 size 크기의 메모리 공간을 할당해주고,
// size만큼 사용할 수 있는 메모리의 주소를 반환해준다.
// size가 0이면 NULL을 반환한다.
// 사용법: sh_malloc(5)
void* sh_malloc(int size){
    void* memory ;
    if(size == 0) return NULL ;
    else
    {
        memory = (void*)malloc(size+4);
        ((int*)memory)[0] = size ;    // my : ((int*)memory)[size] = size ; return memory
        return (char*)memory+4 ;
    }
}

// 할당받은 메모리를 해제해준다.
// ptr은 sh_malloc, sh_calloc, sh_realloc 으로 할당받은 주소만 들어온다고 가정한다.
// sh_free 로 해제한 메모리 공간은 더이상 사용이 불가능하다.
// 사용법: sh_free(p)
void sh_free(void* ptr){
    free((int*)ptr-1);    // 보이드라 인트해야
}

// elementSize크기의 변수 elementCount 개를 저장할 수 있는 배열을 할당한 뒤, 배열의 모든 값을 0으로 초기화시킨다.
// 즉, elementSize * elementCount 크기의 0으로 초기화된 배열이 생성되는 것과 같다.
// 두 인자 중 하나가 0이면 NULL을 반환한다.
// 사용법: sh_calloc (100, sizeof(int))
void* sh_calloc(int elementCount, int elementSize){
    int* memory ;
    memory = (int*)sh_malloc(elementCount * elementSize);
    for(int i=0 ; i<elementCount ; i++) *(memory+i) = 0 ;
    return memory ;
}

// 실제 realloc 과 동작이 다르다.
// 할당받은 포인터 oldPtr을 받아서, newSize크기의 배열을 재할당하여 반환한다.
// 만약 기존 oldPtr에 할당받은 크기가 newSize보다 크다면, oldPtr을 그대로 반환한다.
// 만약 기존 oldPtr에 할당받은 크기보다 newSize가 크다면, oldPtr을 해제하고 새로운 newSize의 배열의 주소를 반환한다.
// newSize 가 0 인 경우는 oldPtr에 할당된 공간을 해제한다.
// 예를 들어, p = sh_malloc(100) 이후에 sh_realloc(p, 99)를 한다면 그대로 p를 반환해야만 한다. (실제 realloc은 이런 제한이 없음)
// 사용법: sh_realloc(p, 1000)
void* sh_realloc(void *oldPtr, int newSize){
    int oldSize = *((int*)oldPtr - 1);
    if(newSize == 0) sh_free(oldPtr);
    else if(oldSize <= newSize) return oldPtr ;
    else if(oldSize > newSize) 
    {
        void* newPtr = (int*)sh_malloc(newSize); // vod* newPtr로도 ㄱㄴ... 차피 이 함수가 void* 로 리턴해서 ㄴ상관 이리메라
        return newPtr ;                          // 위의 줄 생략하고 return sh_malloc(newSize) 가능 이리메라
    }
}

int main()
{
    int* a ;
    // a = (int*)malloc(5);
    a = (int*)sh_calloc(5,sizeof(int));
    for(int i=0 ; i<5 ; i++) printf("%d ", a[i]);
    printf("\n");

    a = (int*)sh_realloc(a, 6*sizeof(int));
    for(int i=0 ; i<6 ; i++) printf("%d ", a[i]);
    printf("\n");
}
