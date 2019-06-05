#include <stdlib.h>
#include <assert.h>
#include "z5wrapper.h"

void my_create_dataset(char* arrayName)
{
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
    //char* arrayName = "test_c.z5";
    int cusezlib = 1;
    int level = 1;
    z5CreateFloatDataset(arrayName, ndim, shape, chunks, cusezlib, level);
    z5WriteFloatSubarray(arrayName, data1, ndim, chunks, offset);
    z5ReadFloatSubarray(arrayName, rdata, ndim, chunks, offset);
    for (int i = 0; i < chunks[0]; i++){
        for (int j = 0; j < chunks[1]; j++)
            for (int k = 0; k<chunks[2]; k++)
                assert(data1[i][j][k] == rdata[i][j][k]);
        printf("data1 = %f\n",data1[i][0][0]);
    }
    z5WriteFloatSubarray(arrayName, data2, ndim, chunks, offset2);
    z5ReadFloatSubarray(arrayName, rdata, ndim, chunks, offset2);
    printf("after read float\n");
    for (int i = 0; i < chunks[0]; i++){
        for (int j = 0; j < chunks[1]; j++)
            for (int k = 0; k<chunks[2]; k++)
                assert(data2[i][j][k] == rdata[i][j][k]);
        printf("data2 = %f\n",data2[i][0][0]);
    }
    z5writeAttributesString(arrayName, "time", "noon");
    
    float floatval = 42.0;
    z5writeAttributesfloat(arrayName, "float", &floatval);
    
    double doubleval = 42.0;
    z5writeAttributesdouble(arrayName, "double", &doubleval);
    
    int intval = 42;
    z5writeAttributesint(arrayName, "int", &intval);
    
    long int longval = 42;
    z5writeAttributeslong(arrayName, "long", &longval);
   
    long long longlongval = 42;
    z5writeAttributeslonglong(arrayName, "longlong", &longlongval);
    
    unsigned long long ulonglongval = 42;
    z5writeAttributesulonglong(arrayName, "ulonglong", &ulonglongval);
    
    unsigned short ushortval = 42;
    z5writeAttributesushort(arrayName, "unshort", &ushortval);
   
    unsigned int uint = 42;
    z5writeAttributesuint(arrayName, "uint", &uint);

    unsigned short usint = 42;
    z5writeAttributesusint(arrayName, "usint", &usint);
 
    short shortint = 42;
    z5writeAttributesshort(arrayName, "short", &shortint);
 
    printf("after assert\n");
}

void test_create_file()
{
    // create a group
    char* fileName = "new_file";
    z5CreateFile(fileName);
    char* groupName1 = "new_file/group1";
    z5CreateGroup(groupName1);
    char* groupName2 = "new_file/group2";
    z5CreateGroup(groupName2);
    char* arrayName = "new_file/group1/array1";
    my_create_dataset(arrayName);
    
}


int main()
{
	test_create_file();
	return 0;
}
