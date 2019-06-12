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
    double ddata[10][10][10];
    double rddata[10][10][10];
    long long int idata1[10][10][10];
    long long int idata2[10][10][10];
    long long int irdata[10][10][10];
    int8_t i8data[10][10][10];
    int8_t ri8data[10][10][10];
    int16_t i16data[10][10][10];
    int16_t ri16data[10][10][10];
    int32_t i32data[10][10][10];
    int32_t ri32data[10][10][10];
    int64_t i64data[10][10][10];
    int64_t ri64data[10][10][10];
    uint8_t ui8data[10][10][10];
    uint8_t rui8data[10][10][10];
    uint16_t ui16data[10][10][10];
    uint16_t rui16data[10][10][10];
    uint32_t ui32data[10][10][10];
    uint32_t rui32data[10][10][10];
    uint64_t ui64data[10][10][10];
    uint64_t rui64data[10][10][10];
    unsigned int ndim = 3;
    for (int i = 0; i < chunks[0]; i++){
        for (int j = 0; j < chunks[1]; j++){
            for (int k = 0; k<chunks[2]; k++){
                data1[i][j][k]=rand()%1000+1;
                idata1[i][j][k]=rand()%1000+1;
                data2[i][j][k]=rand()%1000+1;
                idata2[i][j][k]=rand()%1000+1;
                i8data[i][j][k]=rand()%1000+1;
                i16data[i][j][k]=rand()%1000+1;
                i32data[i][j][k]=rand()%1000+1;
                i64data[i][j][k]=rand()%1000+1;
                ui8data[i][j][k]=rand()%1000+1;
                ui16data[i][j][k]=rand()%1000+1;
                ui32data[i][j][k]=rand()%1000+1;
                ui64data[i][j][k]=rand()%1000+1;
            }
        }
    }
    int cusezlib = 1;
    int level = 1;
    z5CreateFloat32Dataset(arrayName, ndim, shape, chunks, cusezlib, level);
    z5WriteFloat32Subarray(arrayName, data1, ndim, chunks, offset);
    z5ReadFloat32Subarray(arrayName, rdata, ndim, chunks, offset);
    for (int i = 0; i < chunks[0]; i++){
        for (int j = 0; j < chunks[1]; j++)
            for (int k = 0; k<chunks[2]; k++)
                assert(data1[i][j][k] == rdata[i][j][k]);
    }
    z5WriteFloat32Subarray(arrayName, data2, ndim, chunks, offset2);
    z5ReadFloat32Subarray(arrayName, rdata, ndim, chunks, offset2);
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

    // testing read all attributes
    z5readAttributes(arrayName);
    
    // testing read attributes by providing keys
    char *keysinput[2] = {"uint", "double"};
    z5readAttributesWithKeys(arrayName, keysinput, 2); 
    
    printf("after assert\n");

    printf("testing different array types\n");


    char* float64arrayName = "new_file/group1/float64variables";
    z5CreateFloat64Dataset(float64arrayName, ndim, shape, chunks, cusezlib, level);
    printf("===successfully creat Float64Dataset===\n");
    z5WriteFloat64Subarray(float64arrayName, ddata, ndim, chunks, offset);
    printf("===successfully write Float64Dataset===\n");
    z5ReadFloat64Subarray(float64arrayName, rddata, ndim, chunks, offset);
    for (int i = 0; i < chunks[0]; i++){
        for (int j = 0; j < chunks[1]; j++)
            for (int k = 0; k<chunks[2]; k++)
                assert(ddata[i][j][k] == rddata[i][j][k]);
    }
    printf("===successfully read Float64Dataset===\n");


    char* int8arrayName = "new_file/group1/int8variables";
    z5CreateInt8Dataset(int8arrayName, ndim, shape, chunks, cusezlib, level);
    printf("===successfully creat Int8Dataset===\n");
    z5WriteInt8Subarray(int8arrayName, i8data, ndim, chunks, offset);
    printf("===successfully write Int8Dataset===\n");
    z5ReadInt8Subarray(int8arrayName, ri8data, ndim, chunks, offset);
    for (int i = 0; i < chunks[0]; i++){
        for (int j = 0; j < chunks[1]; j++)
            for (int k = 0; k<chunks[2]; k++)
                assert(i8data[i][j][k] == ri8data[i][j][k]);
    }
    printf("===successfully read Int8Dataset===\n");

    char* int16arrayName = "new_file/group1/int16variables";
    z5CreateInt16Dataset(int16arrayName, ndim, shape, chunks, cusezlib, level);
    printf("===successfully creat Int16Dataset===\n");
    z5WriteInt16Subarray(int16arrayName, i16data, ndim, chunks, offset);
    printf("===successfully write Int16Dataset===\n");
    z5ReadInt16Subarray(int16arrayName, ri16data, ndim, chunks, offset);
    for (int i = 0; i < chunks[0]; i++){
        for (int j = 0; j < chunks[1]; j++)
            for (int k = 0; k<chunks[2]; k++)
                assert(i16data[i][j][k] == ri16data[i][j][k]);
    }
    printf("===successfully read Int16Dataset===\n");

    char* int32arrayName = "new_file/group1/int32variables";
    z5CreateInt32Dataset(int32arrayName, ndim, shape, chunks, cusezlib, level);
    printf("===successfully creat Int32Dataset===\n");
    z5WriteInt32Subarray(int32arrayName, i32data, ndim, chunks, offset);
    printf("===successfully write Int32Dataset===\n");
    z5ReadInt32Subarray(int32arrayName, ri32data, ndim, chunks, offset);
    for (int i = 0; i < chunks[0]; i++){
        for (int j = 0; j < chunks[1]; j++)
            for (int k = 0; k<chunks[2]; k++)
                assert(i32data[i][j][k] == ri32data[i][j][k]);
    }
    printf("===successfully read Int32Dataset===\n");

    char* uint8arrayName = "new_file/group1/uint8variables";
    z5CreateUInt8Dataset(uint8arrayName, ndim, shape, chunks, cusezlib, level);
    printf("===successfully creat UInt8Dataset===\n");
    z5WriteUInt8Subarray(uint8arrayName, ui8data, ndim, chunks, offset);
    printf("===successfully write UInt8Dataset===\n");
    z5ReadUInt8Subarray(uint8arrayName, rui8data, ndim, chunks, offset);
    for (int i = 0; i < chunks[0]; i++){
        for (int j = 0; j < chunks[1]; j++)
            for (int k = 0; k<chunks[2]; k++)
                assert(ui8data[i][j][k] == rui8data[i][j][k]);
    }
    printf("===successfully read UInt8Dataset===\n");

    char* uint16arrayName = "new_file/group1/uint16variables";
    z5CreateUInt16Dataset(uint16arrayName, ndim, shape, chunks, cusezlib, level);
    printf("===successfully creat UInt16Dataset===\n");
    z5WriteUInt16Subarray(uint16arrayName, ui16data, ndim, chunks, offset);
    printf("===successfully write UInt16Dataset===\n");
    z5ReadUInt16Subarray(uint16arrayName, rui16data, ndim, chunks, offset);
    for (int i = 0; i < chunks[0]; i++){
        for (int j = 0; j < chunks[1]; j++)
            for (int k = 0; k<chunks[2]; k++)
                assert(ui16data[i][j][k] == rui16data[i][j][k]);
    }
    printf("===successfully read UInt16Dataset===\n");

    char* uint32arrayName = "new_file/group1/uint32variables";
    z5CreateUInt32Dataset(uint32arrayName, ndim, shape, chunks, cusezlib, level);
    printf("===successfully creat UInt32Dataset===\n");
    z5WriteUInt32Subarray(uint32arrayName, ui32data, ndim, chunks, offset);
    printf("===successfully write UInt32Dataset===\n");
    z5ReadUInt32Subarray(uint32arrayName, rui32data, ndim, chunks, offset);
    for (int i = 0; i < chunks[0]; i++){
        for (int j = 0; j < chunks[1]; j++)
            for (int k = 0; k<chunks[2]; k++)
                assert(ui32data[i][j][k] == rui32data[i][j][k]);
    }
    printf("===successfully read UInt32Dataset===\n");

    char* uint64arrayName = "new_file/group1/uint64variables";
    z5CreateUInt64Dataset(uint64arrayName, ndim, shape, chunks, cusezlib, level);
    printf("===successfully creat UInt64Dataset===\n");
    z5WriteUInt64Subarray(uint64arrayName, ui64data, ndim, chunks, offset);
    printf("===successfully write UInt64Dataset===\n");
    z5ReadUInt64Subarray(uint64arrayName, rui64data, ndim, chunks, offset);
    for (int i = 0; i < chunks[0]; i++){
        for (int j = 0; j < chunks[1]; j++)
            for (int k = 0; k<chunks[2]; k++)
                assert(ui64data[i][j][k] == rui64data[i][j][k]);
    }
    printf("===successfully read UInt64Dataset===\n");

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
