#include <stdlib.h>
#include "z5wrapper.h"

int main() {

    size_t shape[] = {100, 100, 100};
    size_t chunks[] = {10, 10, 10};
    float data[100][100][100];
    unsigned int ndim = 3;
    for (int i = 0; i < shape[0];i++)
        for (int j = 0; j < shape[1]; j++)
            for (int k = 0; k<shape[2]; k++) 
                data[i][j][k]=rand()%1000+1;
    struct z5Dataset* ds = z5CreateFloatDataset("test_c.z5", ndim, shape, chunks);
    size_t offset[] = {5, 10, 15};
    z5WriteFloatSubarray((void *)ds, data, shape, offset);
    return 0;
}
