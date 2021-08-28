//
// Created by Gautam Sharma on 7/31/21.
//

#ifndef NNFTW_UTILITY_H
#define NNFTW_UTILITY_H
#include <vector>
#include <map>

namespace NNFTW {
    enum operation {
        ADD = 0,
        SUBTRACT = 1
    };


    struct shape {
        size_t first_dimension;
        size_t second_dimension;

        bool operator==(const shape &rhs) const;

        bool operator!=(const shape &rhs) const;

    };
}

#endif //NNFTW_UTILITY_H
