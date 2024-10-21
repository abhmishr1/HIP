#ifndef HIP_INCLUDE_HIP_HIP_KERNEL_PRESIL_API_H
#define HIP_INCLUDE_HIP_HIP_KERNEL_PRESIL_API_H

#include <hip/hip_runtime.h>
#include <dlfcn.h>
#include <string.h>
#include <filesystem>
#include <iostream>

template <typename T>
decltype(auto) hipKernelFunc(std::string symbolName)
{
	static T *func = [symbolName]()
    {
        T *ptr = nullptr;

        void* handle = dlopen("libamdhip64.so", RTLD_LAZY);

        if (!handle) {
            std::cout << "Could not find libamdhip64.so: " << dlerror() << std::endl;
            return ptr;
        }
        ptr = (T*) dlsym(handle, symbolName.c_str());

        dlclose(handle);
        return ptr;
	}();

	return func;
}

hipError_t hipGetKernelData(const void* hostFunction, hipKernelInfo* kernelData, const char * archName) {

    auto func_ptr = hipKernelFunc<decltype(hipGetKernelInfo)>(std::string("hipGetKernelInfo"));

    if (func_ptr == nullptr) {
        return hipErrorInvalidValue;
    }

    hipError_t hip_error;
    hip_error = func_ptr(hostFunction, kernelData, archName);

    return hip_error;
}

hipError_t hipFreeKernelData(hipKernelInfo* kernelData) {

    auto func_ptr = hipKernelFunc<decltype(hipFreeKernelInfo)>(std::string("hipFreeKernelInfo"));

    if (func_ptr == nullptr) {
        return hipErrorInvalidValue;
    }

    hipError_t hip_error;
    hip_error = func_ptr(kernelData);

    return hip_error;
}

#endif