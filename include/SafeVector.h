#ifndef SAFEVECTOR_H
#define SAFEVECTOR_H

#include <mutex>

#include "myvector.h"

namespace SPL
{
    template <typename T>
    struct SafeVector
    {
        std::mutex safeVector_mutex;
        SPL::MyVector<T> safeVector;  
    };
}
#endif