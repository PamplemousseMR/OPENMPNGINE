#include <vector>
#include <assert.h>
#include <omp.h>

/*
    this project test opm parallel for
*/
int main()
{
    //====================
    //  Default
    //====================
    {
        int max = omp_get_max_threads();
        std::vector<int> arr(static_cast< std::vector< int >::size_type >(max));

        #pragma omp parallel for
        for(int i=0 ; i<max; ++i)
        {
            arr[static_cast< std::vector< int >::size_type >(i)] = i;
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
        int max = omp_get_max_threads();
        int res = 0;

        #pragma omp parallel for reduction(+:res)
        for(int i=0 ; i<max ; ++i)
        {
            res += 1;
        }

        assert(res == max);
    }

    return EXIT_SUCCESS;
}
