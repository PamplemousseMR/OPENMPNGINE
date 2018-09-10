#include <assert.h>
#include <omp.h>
#include <vector>
#include <stdlib.h>

/*
    this project test opm parallel
                     [          omp parallel          ]v
    Thread 0: -------[--------------------------------]*------
    Thread 1:        [--------------------------------]*
    Thread 2:        [--------------------------------]*
    ...                                                *
    Thread N-1:      [--------------------------------]*
*/
int main()
{
    //====================
    //  Default
    //====================
    {
        int max = omp_get_max_threads();
        std::vector<int> arr(static_cast< std::vector< int >::size_type >(max));

        #pragma omp parallel
        {
            arr[omp_get_thread_num()] = omp_get_thread_num();
        }

        for(int i=0 ; i<max; ++i)
        {
            assert(arr[static_cast< std::vector< int >::size_type >(i)] == i);
        }
    }
    //====================
    //  If
    //====================
    {
        int max = omp_get_max_threads();
        std::vector<int> arr(static_cast< std::vector< int >::size_type >(max));

        #pragma omp parallel if(true)
        {
            arr[omp_get_thread_num()] = omp_get_thread_num();
        }

        #pragma omp parallel if(false)
        {
            arr[0] = max;
        }

        assert(arr[0] == max);
        for(int i=1 ; i<max; ++i)
        {
            assert(arr[static_cast< std::vector< int >::size_type >(i)] == i);
        }
    }
    //====================
    //  Num threads
    //====================
    {
        int max = 16;
        std::vector<int> arr(static_cast< std::vector< int >::size_type >(max));

        #pragma omp parallel num_threads(max)
        {
            arr[omp_get_thread_num()] = omp_get_thread_num();
        }

        for(int i=0 ; i<max; ++i)
        {
            assert(arr[static_cast< std::vector< int >::size_type >(i)] == i);
        }
    }
    //====================
    //  Private
    //====================
    {
        int max = omp_get_max_threads();
        int threadnum = 0;
        std::vector<int> arr(static_cast< std::vector< int >::size_type >(max));

        #pragma omp parallel private(threadnum)
        {
            threadnum = omp_get_thread_num();
            arr[omp_get_thread_num()] = threadnum;
        }

        assert(threadnum == 0);
        for(int i=0 ; i<max; ++i)
        {
            assert(arr[static_cast< std::vector< int >::size_type >(i)] == i);
        }
    }
    //====================
    //  First private
    //====================
    {
        int max = omp_get_max_threads();
        int threadnum = max;
        std::vector<int> arr(static_cast< std::vector< int >::size_type >(max));

        #pragma omp parallel firstprivate(threadnum)
        {
            arr[omp_get_thread_num()] = threadnum;
            threadnum = omp_get_thread_num();
        }

        assert(threadnum == max);
        for(int i=0 ; i<max; ++i)
        {
            assert(arr[static_cast< std::vector< int >::size_type >(i)] == max);
        }
    }
    //====================
    //  Reduction
    //====================
    {
        int res = 0;

        #pragma omp parallel reduction(+:res)
        {
            res += omp_get_thread_num();
        }

        int max = omp_get_max_threads()-1;
        int expected = 0;
        while(max)
        {
            expected += max--;
        }

        assert(expected == res);
    }

    return EXIT_SUCCESS;
}
