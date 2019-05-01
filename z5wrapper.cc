//
// Created by Kevin Paul on 2019-04-24.
//
#include <string>
#include <vector>
#include <iostream>
#include "z5wrapper.h"

namespace z5 {
    extern "C" {

    void z5CreateGroup(char* path) {
        std::string path_s(path);
        bool asZarr = true;
        handle::Group cGroup(path_s);
        createGroup(cGroup, asZarr);
    } 
    void z5CreateFloatDataset(char *path, unsigned int ndim, size_t *shape, size_t *chunks, int cuseZlib, int level) {
        std::string path_s(path);
        std::vector<std::string> dtype({"float32"});
        std::vector<size_t> shape_v(shape, shape + ndim);
        std::vector<size_t> chunks_v(chunks, chunks + ndim);
        bool asZarr = true;
 
        DatasetMetadata floatMeta(types::Datatype::float32,shape_v,chunks_v,asZarr);
        if (cuseZlib) {
          floatMeta.compressor = types::zlib;
          floatMeta.compressionOptions["useZlib"] = true;
          floatMeta.compressionOptions["level"] = level;
        }
        handle::Dataset handle_(path_s);
        handle_.createDir();
        writeMetadata(handle_, floatMeta);

    }


    void z5WriteFloatSubarray(char *path, float *array, unsigned int ndim, size_t *shape, size_t *offset) {
        std::string path_s(path);
        auto ds =openDataset(path_s);
        size_t size = 1;
        std::vector<std::size_t> shape_v(shape,shape + ndim); 
        for (std::vector<size_t>::const_iterator i = shape_v.begin(); i != shape_v.end(); ++i)
            size=size*(*i);
        xt::xarray<float> adp_array=xt::adapt(array,size,xt::no_ownership(),shape_v);
        std::vector<size_t> offset_v(offset,offset + ndim);
        multiarray::writeSubarray<float>(ds,adp_array,offset_v.begin());
    }

    void z5ReadFloatSubarray(char *path, float *array, unsigned int ndim, size_t *shape, size_t *offset) {
        std::string path_s(path);
        auto ds = openDataset(path_s);
        using vec_type = std::vector<float>;
        size_t size = 1;
        std::vector<std::size_t> shape_v(shape,shape + ndim); 
        for (std::vector<size_t>::const_iterator i = shape_v.begin(); i != shape_v.end(); ++i)
            size*=(*i);
        using shape_type = std::vector<vec_type::size_type>;
        shape_type s(shape,shape+ndim);
        std::vector<size_t> offset_v(offset,offset + ndim);
        auto adp_array=xt::adapt(array,size,xt::no_ownership(),s);
        multiarray::readSubarray<float>(ds,adp_array,offset_v.begin()); 
    }
}

}
