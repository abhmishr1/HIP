.. meta::
  :description: This chapter describes the HIP programming model, the contract
                between the programmer and the compiler/runtime executing the
                code.
  :keywords: AMD, ROCm, HIP, CUDA, C++ language extensions

*******************************************************************************
Programming interface
*******************************************************************************

HIP defines a model for mapping single instruction, multiple threads (SIMT) programs 
onto various architectures, primarily GPUs. While the model may be expressed 
in most imperative languages, (for example Python via PyHIP) this document will focus on 
the original C/C++ API of HIP.

HIP compilers
=============

AMD platform compilers
----------------------

ROCm currently provides two compiler interfaces for compiling HIP programs:

* ``/opt/rocm/bin/hipcc``
* ``/opt/rocm/bin/amdclang++``

Both leverage the same LLVM compiler technology with the AMD GCN GPU support; however, they offer a slightly different user experience. The `hipcc` command-line interface aims to provide a more familiar user interface to users who are experienced in CUDA but relatively new to the ROCm/HIP development environment. On the other hand, `amdclang++` provides a user interface identical to the clang++ compiler. It is more suitable for experienced developers who want to directly interact with the clang compiler and gain full control of their application’s build process.

The major differences between `hipcc` and `amdclang++` are listed below:

.. list-table::
    :header-rows: 1

    * - 
      - ``hipcc``
      - ``amdclang++``

    * - Compiling HIP source files  .
      - Treats all source files as HIP language source files.
      - Enables the HIP language support for files with the ``.hip`` extension or through the ``-x hip`` compiler option

    * - Detecting GPU architecture.
      - Auto-detects the GPUs available on the system and generates code for those devices when no GPU architecture is specified.
      - Has AMD GCN gfx803 as the default GPU architecture. The ``--offload-arch`` compiler option may be used to target other GPU architectures.

    * - Finding a HIP installation.
      - Finds the HIP installation based on its own location and its knowledge about the ROCm directory structure.
      - First looks for HIP under the same parent directory as its own LLVM directory and then falls back on ``/opt/rocm``. Users can use the ``--rocm-path`` option to instruct the compiler to use HIP from the specified ROCm installation.

    * - Linking to the HIP runtime library.
      - Is configured to automatically link to the HIP runtime from the detected HIP installation.
      - Requires the ``--hip-link`` flag to be specified to link to the HIP runtime. Alternatively, users can use the ``-l<dir> -lamdhip64`` option to link to a HIP runtime library.

    * - Device function inlining.
      - Inlines all GPU device functions, which provide greater performance and compatibility for codes that contain file scoped or device function scoped ``__shared__`` variables. However, it may increase compile time.
      - Relies on inlining heuristics to control inlining. Users experiencing performance or compilation issues with code using file scoped or device function scoped ``__shared__`` variables could try ``-mllvm -amdgpu-early-inline-all=true -mllvm -amdgpu-function-calls=false`` to work around the issue. There are plans to address these issues with future compiler improvements.

    * - Source code location.
      - `HIPCC <https://github.com/ROCm/HIPCC>`_
      - `amdclang++ <https://github.com/ROCm/llvm-project>`_

For compiler options check the `GPU compiler option page <https://rocm.docs.amd.com/en/docs-5.2.3/reference/rocmcc/rocmcc.html#amd-gpu-compilation>`_.

NVIDIA platform compilers
-------------------------

HIP versioning
===============

.. include:: algorithm-libraries-support-matrix-content.rst

Linux kernel driver support
---------------------------

.. include:: user-kernel-space-compat-matrix-content.rst