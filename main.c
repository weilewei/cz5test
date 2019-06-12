#include <stdlib.h>
#include <assert.h>
#include "z5wrapper.h"

int main() {

    size_t shape[] = {20, 20, 20};
    size_t chunks[] = {10, 10, 10};
    size_t offset[] = {0, 0, 0};
    size_t offset2[] = {10, 10, 10};
    float data1[10][10][10];
    float data2[10][10][10];
    float rdata[10][10][10];
    long long int idata1[10][10][10];
    long long int idata2[10][10][10];
    long long int irdata[10][10][10];
    unsigned int ndim = 3;
    for (int i = 0; i < chunks[0]; i++){
        for (int j = 0; j < chunks[1]; j++){
            for (int k = 0; k<chunks[2]; k++){ 
                data1[i][j][k]=rand()%1000+1;
                idata1[i][j][k]=rand()%1000+1;
            }    
        }
    }
    for (int i = 0; i < chunks[0]; i++){
        for (int j = 0; j < chunks[1]; j++){
            for (int k = 0; k<chunks[2]; k++){ 
                data2[i][j][k]=rand()%1000+1;
                idata2[i][j][k]=rand()%1000+1;
            }    
        }
    }
    char* arrayName = "test_c.z5";
    int cusezlib = 1;
    int level = 1;
    z5CreateFloat32Dataset(arrayName, ndim, shape, chunks, cusezlib, level);
    z5WriteFloat32Subarray(arrayName, data1, ndim, chunks, offset);
    z5ReadFloat32Subarray(arrayName, rdata, ndim, chunks, offset);
    for (int i = 0; i < chunks[0]; i++){
        for (int j = 0; j < chunks[1]; j++)
            for (int k = 0; k<chunks[2]; k++) 
                assert(data1[i][j][k] == rdata[i][j][k]); 
        printf("data1 = %f\n",data1[i][0][0]);
    }
    z5WriteFloat32Subarray("test_c.z5", data2, ndim, chunks, offset2);
    z5ReadFloat32Subarray("test_c.z5", rdata, ndim, chunks, offset2);
    printf("after read float\n");
    for (int i = 0; i < chunks[0]; i++){
        for (int j = 0; j < chunks[1]; j++)
            for (int k = 0; k<chunks[2]; k++) 
                assert(data2[i][j][k] == rdata[i][j][k]); 
        printf("data2 = %f\n",data2[i][0][0]);
    }
    printf("after assert\n");

    char* iarrayName = "test_c_int64.z5";
    z5CreateInt64Dataset(iarrayName, ndim, shape, chunks, cusezlib, level);
    z5WriteInt64Subarray(iarrayName, idata1, ndim, chunks, offset);
    z5ReadInt64Subarray(iarrayName, irdata, ndim, chunks, offset); 
    for (int i = 0; i < chunks[0]; i++){
        for (int j = 0; j < chunks[1]; j++)
            for (int k = 0; k<chunks[2]; k++) 
                assert(idata1[i][j][k] == irdata[i][j][k]); 
        printf("idata1 = %lu\n",idata1[i][0][0]);
    }
    z5WriteInt64Subarray(iarrayName, idata2, ndim, chunks, offset2);
    z5ReadInt64Subarray(iarrayName, irdata, ndim, chunks, offset2); 
    printf("after read float\n");
    for (int i = 0; i < chunks[0]; i++){
        for (int j = 0; j < chunks[1]; j++)
            for (int k = 0; k<chunks[2]; k++) 
                assert(idata2[i][j][k] == irdata[i][j][k]); 
        printf("idata2 = %lu\n",idata2[i][0][0]);
    }
    printf("after assert\n");
    size_t chunkSize0=z5GetFileSize("test_c_int64.z5/0.0.0");
    size_t chunkSize1=z5GetFileSize("test_c_int64.z5/1.1.1");
    printf("size = %lu, %lu\n",chunkSize0,chunkSize1);
    z5Delete("test_c_int64.z5");
    return 0;
}
