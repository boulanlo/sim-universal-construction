#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <stdint.h>

#include <config.h>
#include <primitives.h>
#include <fastrand.h>
#include <threadtools.h>
#include <clhhash.h>
#include <barrier.h>
#include <bench_args.h>
#include <math.h>

#define N_BUCKETS        64
#define LOAD_FACTOR      1
#define INITIAL_CAPACITY (LOAD_FACTOR * N_BUCKETS)

#define RANDOM_RANGE (INITIAL_CAPACITY * log(INITIAL_CAPACITY))

CLHHash object_struct CACHE_ALIGN;
CLHHashThreadState *th_state;

int main(int argc, char *argv[]) {
    CLHHashStructInit(&object_struct, N_BUCKETS, 16);

    th_state = synchGetAlignedMemory(CACHE_LINE_SIZE, sizeof(CLHHashThreadState));
    CLHHashThreadStateInit(&object_struct, th_state, N_BUCKETS, 0);

    CLHHashInsert(&object_struct, th_state, 1, 1, 0);
    CLHHashDelete(&object_struct, th_state, 1, 0);

    int search = CLHHashSearch(&object_struct, th_state, 1, 0);

    fprintf(stderr, "search: %d", search);

    return 0;
}
