#ifndef HIP_INCLUDE_HIP_HIP_PRESIL_HELPER_H
#define HIP_INCLUDE_HIP_HIP_PRESIL_HELPER_H

#include <hip/hip_runtime.h>
#include <dlfcn.h>
#include <string.h>
#include <filesystem>
#include <iostream>
#include <vector>

struct hipKernelData {
    std::vector<uint8_t> kernelBin;
    std::vector<uint8_t> kArgsSizes;
    std::vector<uint8_t> kArgsOffsets;
    std::vector<uint8_t> kArgsAccQuals;
    std::vector<bool>    kArgsHidden;
    size_t               kArgSegSize;

    void free() {
        kernelBin.clear();
        kArgsSizes.clear();
        kArgsOffsets.clear();
        kArgsAccQuals.clear();
        kArgsHidden.clear();
    }
};

enum AccQualType {
    READ_ONLY = hipArgReadOnly,
    WRITE_ONLY = hipArgWriteOnly,
    READ_WRITE = hipArgReadWrite
};

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

hipError_t hipGetKernelData(const void* hostFunction, const char * archName, hipKernelData &kernelData) {

    auto get_func_ptr = hipPresilHelperFunc<decltype(hipGetKernelInfo)>("hipGetKernelInfo");
    auto free_func_ptr = hipPresilHelperFunc<decltype(hipFreeKernelInfo)>("hipFreeKernelInfo");

    if (get_func_ptr == nullptr || free_func_ptr == nullptr) {
        return hipErrorInvalidValue;
    }

    hipError_t    hip_error;
    hipKernelInfo kernelInfo;

    hip_error = get_func_ptr(hostFunction, &kernelInfo, archName);

    for (int i = 0; i < kernelInfo.binary.size; i++) {
        kernelData.kernelBin.push_back(kernelInfo.binary.data[i]);
    }

    for (int i = 0; i < kernelInfo.kernArgsSizes.size; i++) {
        kernelData.kArgsSizes.push_back(kernelInfo.kernArgsSizes.data[i]);
        kernelData.kArgsOffsets.push_back(kernelInfo.kernArgsOffsets.data[i]);
        if (kernelInfo.kernArgsHidden.data[i]) {
            kernelData.kArgsHidden.push_back(true);
        } else {
            kernelData.kArgsHidden.push_back(false);
        }
    }

    for (int i = 0; i < kernelInfo.kernArgsAccQualifiers.size; i++) {
        kernelData.kArgsAccQuals.push_back(kernelInfo.kernArgsAccQualifiers.data[i]);
    }

    kernelData.kArgSegSize = kernelInfo.kernArgSegSize;

    hip_error = free_func_ptr(&kernelInfo);

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