#include <vector>
#include <assert.h>

/*
    this project test opm parallel for
*/
int main()
{
    int max = 10;
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
