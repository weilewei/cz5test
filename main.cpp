#include "xtensor/xarray.hpp"
#include "z5/dataset_factory.hxx"
#include "z5/multiarray/xtensor_access.hxx"
#include "z5/attributes.hxx"
#include "nlohmann/json.hpp"

int main() {
    // create a new zarr dataset
    std::vector<size_t> shape = {1000, 1000, 1000};
    std::vector<size_t> chunks = {100, 100, 100};
    bool asZarr = true;
    auto ds = z5::createDataset("test_cpp.z5", "float32", shape, chunks, asZarr);

    // write array to roi
    std::vector<size_t> offset1 = {50, 100, 150};
    std::vector<size_t> shape1 = {150, 200, 100};
    xt::xarray<float> array1(shape1, 42.);
    z5::multiarray::writeSubarray<float>(ds, array1, offset1.begin());

    // read array from roi (values that were not written before are filled with a fill-value)
    std::vector<size_t> offset2 = {100, 100, 100};
    std::vector<size_t> shape2 = {300, 200, 75};
    xt::xarray<float> array2(shape2);
    z5::multiarray::readSubarray<float>(ds, array2, offset2.begin());

    // read and write json attributes
    nlohmann::json attributesIn;
    attributesIn["bar"] = "foo";
    attributesIn["pi"] = 3.141593;
    z5::writeAttributes(ds->handle(), attributesIn);

    std::vector<std::string> keys = {"bar", "pi"};
    nlohmann::json attributesOut;
    z5::readAttributes(ds->handle(), keys, attributesOut);

    return 0;
}
