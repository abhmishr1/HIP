.. meta::
  :description: This chapter describes the HIP runtime API and the compilation workflow of the HIP compilers.
  :keywords: AMD, ROCm, HIP, CUDA, HIP runtime API

*******************************************************************************
Programming interface
*******************************************************************************

The programming interface document will focus on the C/C++ HIP runtime API and the usage of this API. The runtime API provides C and C++ functions for event, stream,  device and memory managements, etc. The HIP runtime on AMD platform uses the Common Language Runtimes (CLR), while on NVIDIA platform HIP runtime is only a thin layer over the CUDA runtime.

- **CLR**
  CLR contains source codes for AMD's compute languages runtimes: ``HIP`` and ``OpenCL™``. CLR includes the implementation of ``HIP`` language on the AMD platform `hipamd <https://github.com/ROCm/clr/tree/develop/hipamd>`_ and the Radeon Open Compute Common Language Runtime (rocclr), which is a virtual device interface, that HIP runtimes interact with different backends. (CLR also include the implementation of `OpenCL <https://github.com/ROCm/clr/tree/develop/opencl>`_)
- **CUDA runtime**
  CUDA runtime is built over the CUDA driver API (lower-level C API). For further information about the CUDA driver and runtime API, check the :doc:`hip:how-to/hip_porting_driver_api`. On non-AMD platform, HIP runtime determines, if CUDA is available and can be used. If available, HIP_PLATFORM is set to ``nvidia`` and underneath CUDA path is used.

HIP compilers
=============

The HIP runtime API and HIP C++ extensions are available with HIP compilers. On AMD platform ROCm currently provides two compiler interfaces: ``hipcc`` and ``amdclang++``. The ``hipcc`` command-line interface aims to provide a more familiar user interface to users who are experienced in CUDA but relatively new to the ROCm/HIP development environment. On the other hand, ``amdclang++`` provides a user interface identical to the clang++ compiler. (For further details, check `llvm <llvm-project-docs:index>`_). On NVIDIA platform HIP invoke the locally installed ``NVCC`` compiler.

For compiler options, check the `GPU compiler option page <https://rocm.docs.amd.com/en/docs-5.2.3/reference/rocmcc/rocmcc.html#amd-gpu-compilation>`_.

HIP compilation workflow
------------------------


For example of compiling from command line, check the :ref:` SAXPY tutorial compiling <compiling_on_the_command_line>`.

HIP versioning
===============

.. include:: algorithm-libraries-support-matrix-content.rst

Linux kernel driver support
---------------------------

.. include:: user-kernel-space-compat-matrix-content.rst


HIP runtime API
===============