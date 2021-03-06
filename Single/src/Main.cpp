#include <assert.h>
#include <omp.h>
#include <vector>
#include <stdlib.h>
/*
    this project test opm single
                     [       omp parallel single      ]v
    Thread 0: -------[--------------------------------]*------
    Thread 1:        [-----------< single >-----------]*
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
            #pragma omp single
            {
                arr[0] = max;
            }
        }

        assert(arr[0] == max);
        for(int i=1 ; i<max; ++i)
        {
            assert(arr[static_cast< std::vector< int >::size_type >(i)] == i);
        }
    }
    //====================
    //  Nowait
    //====================
    {
        int res;
        int max = omp_get_max_threads();
        std::vector<int> arr(static_cast< std::vector< int >::size_type >(max));

        #pragma omp parallel
        {
            #pragma omp single nowait
            {
                res = max;
            }
            arr[omp_get_thread_num()] = omp_get_thread_num();
        }

        assert(res == max);
        for(int i=0 ; i<max; ++i)
        {
            assert(arr[static_cast< std::vector< int >::size_type >(i)] == i);
        }
    }

    return EXIT_SUCCESS;
}
