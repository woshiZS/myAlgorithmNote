#include<stdlib.h>
#include<stdio.h>

typedef long long word_t;

typedef struct block{
    word_t header;
    union {
        struct {
            struct block* pre;
            struct block* next;
        }p;
        char payload[0];
    }u;
}block_t;

int main(){
    printf("Before start is okay.\n");
    block_t blk_0;
    block_t blk_1;
    block_t blk_2;
    blk_1.header=20;
    blk_1.u.p.pre=&(blk_0);
    blk_1.u.p.next=&(blk_2);

    printf("Stage 1(before output) is okay.\n");

    printf("header = %ld\n",blk_1.header);
    printf("forward = %p\n",blk_1.u.p.pre);
    printf("backward = %p\n",blk_1.u.p.next);
    printf("payload = %d\n",blk_1.u.payload[0]);
    printf("------------------------------------------------------\n");

    blk_1.u.payload[0]=123;
    printf("header = %ld\n",blk_1.header);
    printf("forward = %p\n",blk_1.u.p.pre);
    printf("backward = %p\n",blk_1.u.p.next);
    printf("payload = %d\n",blk_1.u.payload[0]);
    printf("------------------------------------------------------\n");

    return 0;
}