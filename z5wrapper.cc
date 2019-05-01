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
        std::vector<size_t> shape_v(shape, shape + ndim);
        std::vector<size_t> chunks_v(chunks, chunks + ndim);
        bool asZarr = true;
        return createDataset(path_s, "float32", shape_v, chunks_v, asZarr).release();
    }

    void z5WriteFloatSubarray(void *ds, float *array, unsigned int ndim, size_t *shape, size_t *offset) {
        size_t size = 1;
        std::vector<std::size_t> shape_v(shape,shape + ndim); 
        for (std::vector<size_t>::const_iterator i = shape_v.begin(); i != shape_v.end(); ++i)
            size=size*(*i);
        std::unique_ptr<Dataset> unq_ds((Dataset*)ds);
        xt::xarray<float> adp_array=xt::adapt(array,size,xt::no_ownership(),shape_v);
        std::vector<size_t> offset_v(offset,offset + ndim);
        multiarray::writeSubarray<float>(unq_ds,adp_array,offset_v.begin());
        unq_ds.release();
    }

    void z5ReadFloatSubarray(void *ds, float *array, unsigned int ndim, size_t *shape, size_t *offset) {
        using vec_type = std::vector<float>;
        size_t size = 1;
        std::vector<std::size_t> shape_v(shape,shape + ndim); 
        for (std::vector<size_t>::const_iterator i = shape_v.begin(); i != shape_v.end(); ++i)
            size*=(*i);
        std::unique_ptr<Dataset> unq_ds((Dataset*)ds);
        using shape_type = std::vector<vec_type::size_type>;
        shape_type s(shape,shape+ndim);
        std::vector<size_t> offset_v(offset,offset + ndim);
        auto adp_array=xt::adapt(array,size,xt::no_ownership(),s);
        multiarray::readSubarray<float>(unq_ds,adp_array,offset_v.begin()); 
        unq_ds.release();
    }
}

}
