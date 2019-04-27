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

    int z5WriteFloatSubarray(void *ds, float *array, unsigned int ndim, size_t *shape, size_t *offset) {
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

    int z5ReadFloatSubarray(void *ds, float *array, unsigned int ndim, size_t *shape, size_t *offset) {
        size_t size = 1;
        std::vector<std::size_t> shape_v(shape,shape + ndim); 
        for (std::vector<size_t>::const_iterator i = shape_v.begin(); i != shape_v.end(); ++i)
            size=size*(*i);
        std::cout<<"size = "<<size<<"ndim = "<<ndim<<std::endl;
        std::unique_ptr<Dataset> unq_ds((Dataset*)ds);
        std::vector<size_t> offset_v(offset,offset + ndim);
        float* array1= new float[size];
        xt::xarray<float> adp_array=xt::adapt(array1,size,xt::no_ownership(),shape_v);
        //xt::xarray<float> adp_array=xt::adapt(array1,shape_v);
        multiarray::readSubarray<float>(unq_ds,adp_array,offset_v.begin()); 
        std::cout<< adp_array(0,0,0) <<" " <<adp_array(1,0,0)<<" "<<adp_array(2,0,0)<<std::endl;
        std::cout<< array1[0]<<" " <<array1[1]<<" "<<array1[2]<<std::endl;

    }
}

}
