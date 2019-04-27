//
// Created by Kevin Paul on 2019-04-24.
//
#ifndef CZ5TEST_Z5WRAPPER_H
#define CZ5TEST_Z5WRAPPER_H

#include <stddef.h>
#ifdef __cplusplus
#include "z5/multiarray/xtensor_access.hxx"
    extern "C" {
#endif
         typedef struct xarray cxarray;
#ifdef __cplusplus
    }
#endif

#ifdef __cplusplus
#include "z5/dataset_factory.hxx"
#endif

#ifdef __cplusplus
namespace z5 {
    extern "C" {
#endif

        typedef struct Dataset Dataset;

        Dataset *z5CreateFloatDataset(char *path, unsigned int ndim, size_t *shape, size_t *chunks);

        int z5WriteFloatSubarray(void *ds, float *array, unsigned int ndim, size_t *shape, size_t *offset);

        int z5ReadFloatSubarray(void *ds, float *array,  unsigned int ndim, size_t *shape,size_t *offset);

#ifdef __cplusplus
    }
}
#endif
#endif //CZ5TEST_Z5WRAPPER_H
