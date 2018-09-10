#include <assert.h>
#include <omp.h>
#include <vector>
#include <stdlib.h>

/*
    this project test opm section
*/
int main()
{
    //====================
    //  Default
    //====================
    {
        int max = omp_get_max_threads();
        std::vector<int> arr(static_cast< std::vector< int >::size_type >(max));

        #pragma omp parallel sections
        {
            #pragma omp section
            {
                for(int i=0 ; i<max/2 ; ++i)
                {
                    arr[i] = omp_get_thread_num();
                }
            }
            #pragma omp section
            {
                for(int i=max/2 ; i<max ; ++i)
                {
                    arr[i] = omp_get_thread_num();
                }
            }
        }

        for(int i=0 ; i<max/2 ; ++i)
        {
            assert(arr[static_cast< std::vector< int >::size_type >(i)] == arr[static_cast< std::vector< int >::size_type >(0)]);
        }
        for(int i=max/2 ; i<max ; ++i)
        {
            assert(arr[static_cast< std::vector< int >::size_type >(i)] == arr[static_cast< std::vector< int >::size_type >(max-1)]);
        }
    }
    //====================
    //  Reduction
    //====================
    {
        int max = omp_get_max_threads();
        int res = 0;

        #pragma omp parallel sections reduction(+:res)
        {
            #pragma omp section
            {
                for(int i=0 ; i<max/2 ; ++i)
                {
                    ++res;
                }
            }
            #pragma omp section
            {
                for(int i=max/2 ; i<max ; ++i)
                {
                    ++res;
                }
            }
        }

        assert(res == max);
    }

    return EXIT_SUCCESS;
}
