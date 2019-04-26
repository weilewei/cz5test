//
// Created by Kevin Paul on 2019-04-24.
//
#include <string>
#include <vector>
#include <iostream>
#include "z5wrapper.h"

namespace z5 {
    extern "C" {

    Dataset *z5CreateFloatDataset(char *path, unsigned int ndim, size_t *shape, size_t *chunks) {
        std::string path_s(path);
        size_t ndim1 = sizeof(shape)/sizeof(*shape);
        std::vector<size_t> shape_v(shape, shape + ndim1);
        std::vector<size_t> chunks_v(chunks, chunks + ndim1);
        bool asZarr = true;
        return createDataset(path_s, "float32", shape_v, chunks_v, asZarr).release();
    }

    int z5WriteFloatSubarray(void *ds, float *array, size_t *shape, size_t *offset) {
        size_t ndim1 = sizeof(shape)/sizeof(*shape);
        size_t size = shape[0] * shape[1] * shape[2]; 
        printf("ndim1 = %d,size = %d,shape[0]=%d\n",ndim1,size,shape[0]);
        std::vector<std::size_t> shape_v(shape,shape + ndim1); 
        std::unique_ptr<Dataset> unq_ds((Dataset*)ds);
        xt::xarray<float> adp_array=xt::adapt(array,size,xt::no_ownership(),shape_v);
        std::vector<size_t> offset_v(offset,offset + ndim1);
        multiarray::writeSubarray<float>(unq_ds,adp_array,offset_v.begin());
    }

    int z5ReadFloatSubarray(void *ds, float *array, size_t *offset) {

    }

    }
}
