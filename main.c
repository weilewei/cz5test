#include <stdlib.h>
#include <assert.h>
#include "z5wrapper.h"

int main() {

    size_t shape[] = {10, 10, 10};
    size_t chunks[] = {10, 10, 10};
    size_t offset[] = {0, 0, 0};
    float data[10][10][10];
    float rdata[10][10][10];
    unsigned int ndim = 3;
    for (int i = 0; i < shape[0]; i++){
        for (int j = 0; j < shape[1]; j++){
            for (int k = 0; k<shape[2]; k++){ 
                data[i][j][k]=rand()%1000+1;
            }    
        }
    }
    struct z5Dataset* ds = z5CreateFloatDataset("test_c.z5", ndim, shape, chunks);
    z5WriteFloatSubarray((void *)ds, data, ndim, shape, offset);
    z5ReadFloatSubarray((void *)ds, rdata, ndim, shape, offset); 
    for (int i = 0; i < shape[0]; i++){
        for (int j = 0; j < shape[1]; j++)
            for (int k = 0; k<shape[2]; k++) 
                assert(data[i][j][k] == rdata[i][j][k]); 
    }
    return 0;
}
