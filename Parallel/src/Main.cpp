#include <assert.h>
#include <omp.h>
#include <vector>

/*
    this project test opm parallel
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
