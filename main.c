#include "z5wrapper.h"

int main() {

    size_t shape[] = {1000, 1000, 1000};
    size_t chunks[] = {100, 100, 100};
    struct z5Dataset* ds = z5CreateFloatDataset("test_c.z5", 3, shape, chunks);

    return 0;
}
