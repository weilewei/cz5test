//
// Created by Kevin Paul on 2019-04-24.
//
#include <string>
#include <vector>
#include "z5wrapper.h"

namespace z5 {
    extern "C" {

    Dataset *z5CreateFloatDataset(char *path, unsigned int ndim, size_t *shape, size_t *chunks) {
        std::string path_s(path);
        std::vector<size_t> shape_v(shape, shape + ndim);
        std::vector<size_t> chunks_v(chunks, chunks + ndim);
        bool asZarr = true;
        return createDataset(path_s, "float32", shape_v, chunks_v, asZarr).get();
    }

    int z5WriteFloatSubarray(void *ds, float *array, size_t *offset) {

    }

    int z5ReadFloatSubarray(void *ds, float *array, size_t *offset) {

    }

    }
}
