/* Copyright 2014 Samsung Electronics Co., Ltd.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/**
 * Unit test for pool manager.
 */

#define JERRY_MEM_POOL_INTERNAL

#include "globals.h"
#include "jerry-libc.h"
#include "mem-allocator.h"
#include "mem-pool.h"
#include "mem-poolman.h"

extern void srand (unsigned int __seed);
extern int rand (void);
extern long int time (long int *__timer);

// Heap size is 8K
const size_t test_heap_size = 8 * 1024;

// Iterations count
const uint32_t test_iters = 16384;

// Subiterations count
const uint32_t test_max_sub_iters = 64;

int
main( int __unused argc,
      char __unused **argv)
{
    uint8_t heap[test_heap_size] __attribute__((aligned(MEM_ALIGNMENT)));

    mem_HeapInit( heap, sizeof (heap));
    mem_PoolsInit();

    srand((unsigned int) time(NULL));
    unsigned int seed = (unsigned int)rand();
    __printf("seed=%u\n", seed);
    srand(seed);

    for ( int i = 0; i < test_iters; i++ )
    {
        const size_t subiters = ( (size_t) rand() % test_max_sub_iters ) + 1;

        uint8_t * ptrs[subiters];
        mem_PoolChunkType_t types[subiters];

        for ( size_t j = 0; j < subiters; j++ )
        {
            mem_PoolChunkType_t type = (mem_PoolChunkType_t) (rand() % MEM_POOL_CHUNK_TYPE__COUNT);
            const uint32_t chunkSize = mem_GetChunkSize( type);

            types[j] = type;
            ptrs[j] = mem_PoolsAlloc( type);
            JERRY_ASSERT(ptrs[j] != NULL);

            if ( ptrs[j] != NULL )
            {
                __memset(ptrs[j], 0, chunkSize);
            }
        }

        // mem_HeapPrint( false);
        
        for ( size_t j = 0; j < subiters; j++ )
        {
            if ( ptrs[j] != NULL )
            {
                mem_PoolChunkType_t type = types[j];
		const uint32_t chunkSize = mem_GetChunkSize( type);

                for ( size_t k = 0; k < chunkSize; k++ )
                {
                    JERRY_ASSERT( ((uint8_t*) ptrs[j])[k] == 0 );
                }
                
                mem_PoolsFree( type, ptrs[j]);
            }
        }
    }

    return 0;
} /* main */