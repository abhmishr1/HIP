#ifndef HIP_INCLUDE_HIP_HIP_PRESIL_HELPER_H
#define HIP_INCLUDE_HIP_HIP_PRESIL_HELPER_H

#include <hip/hip_runtime.h>
#include <dlfcn.h>
#include <string.h>
#include <filesystem>
#include <iostream>
#include <vector>

template <typename T>
decltype(auto) hipPresilHelperFunc(const char * symbolName) {

    static T *func = [symbolName]() {
        T *ptr = nullptr;

        void* handle = dlopen("libamdhip64.so", RTLD_LAZY);

        if (!handle) {
            std::cout << "Could not find libamdhip64.so: " << dlerror() << std::endl;
            return ptr;
        }
        ptr = (T*) dlsym(handle, symbolName);

        dlclose(handle);
        return ptr;
    }();

    return func;
}

hipError_t hipGetKernelData(const void* hostFunction, hipKernelInfo* kernelData, const char * archName) {

    auto func_ptr = hipPresilHelperFunc<decltype(hipGetKernelInfo)>("hipGetKernelInfo");

    if (func_ptr == nullptr) {
        return hipErrorInvalidValue;
    }

    hipError_t hip_error;
    hip_error = func_ptr(hostFunction, kernelData, archName);

    return hip_error;
}

hipError_t hipFreeKernelData(hipKernelInfo* kernelData) {

    auto func_ptr = hipPresilHelperFunc<decltype(hipFreeKernelInfo)>("hipFreeKernelInfo");

    if (func_ptr == nullptr) {
        return hipErrorInvalidValue;
    }

    hipError_t hip_error;
    hip_error = func_ptr(kernelData);

    return hip_error;
}

hipError_t hipGetKernelArgsMallocs(void** kArgsAddr, size_t kArgsSize, size_t deviceId, std::vector<void*> &mallocsVec) {

    auto get_func_ptr = hipPresilHelperFunc<decltype(hipGetKArgsMallocs)>("hipGetKArgsMallocs");
    auto free_func_ptr = hipPresilHelperFunc<decltype(hipFreeKArgsMallocs)>("hipFreeKArgsMallocs");

    if (get_func_ptr == nullptr || free_func_ptr == nullptr) {
        return hipErrorInvalidValue;
    }

    hipError_t          hip_error;
    hipKArgsMallocsList mallocsList;

    hip_error = get_func_ptr(kArgsAddr, kArgsSize, deviceId, &mallocsList);

    for (int i = 0; i< mallocsList.mallocs.size; i++) {
      mallocsVec.push_back(mallocsList.mallocs.data[i]);
    }

    hip_error = free_func_ptr(&mallocsList);

    return hip_error;
}

#endif