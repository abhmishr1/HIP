/*
Copyright (c) 2015 - 2024 Advanced Micro Devices, Inc. All rights reserved.

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/

/**
 * @file hip_runtime_hooks.h
 *
 * @brief Defines the external hooks for HIP runtime.
 * This file can be compiled with a standard compiler.
 */

#ifndef HIP_INCLUDE_HIP_HIP_RUNTIME_HOOKS_H
#define HIP_INCLUDE_HIP_HIP_RUNTIME_HOOKS_H

#include <hip/hip_runtime_api.h>

#include <dlfcn.h>
#include <iostream>
#include <memory>

template <typename T>
decltype(auto) hipRuntimeHookFunc(const char * symbolName) {
    using U = std::shared_ptr<T>;

    static U func = [symbolName]() {
        T *ptr = nullptr;

        void* handle = dlopen("libhip_runtimehooks.so", RTLD_LAZY);

        auto close_handle = [handle](auto) {
            dlclose(handle);
        };

        if (!handle) {
            std::cout << "Could not find libhip_runtimehooks.so: " << dlerror() << std::endl;
            return std::shared_ptr<T>(ptr, close_handle);
        }
        ptr = (T*) dlsym(handle, symbolName);

        return std::shared_ptr<T>(ptr, close_handle);
    }();

    return func;
}

hipError_t hipLaunchKernel_sim(const uint8_t* kernelBin, size_t binSize,
                            void** kArgs, size_t kArgsSize, dim3 gridDim,
                            dim3 blockDim, size_t sharedMemBytes, hipStream_t stream) {

    auto func_sptr = hipRuntimeHookFunc<decltype(hipLaunchKernel_sim)>("hipLaunchKernel_sim").get();

    if (func_sptr == nullptr) {
        return hipErrorInvalidValue;
    }

    hipError_t hip_error = func_sptr(kernelBin, binSize, kArgs, kArgsSize,
                                    gridDim, blockDim, sharedMemBytes, stream);

    return hip_error;
}

#endif
