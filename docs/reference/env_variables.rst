.. meta::
    :description: HIP environment variables reference
    :keywords: AMD, HIP, environment variables, environment, reference

*************************************************************
HIP environment variables
*************************************************************

In this section, the reader can find all the important HIP environment variables. The full collection of the ROCm environment variables is on the :doc:`ROCm environment variables page<rocm:reference/env-variables>`.

GPU isolation variables
=======================

The GPU isolation environment variables in HIP are collected in the next table. For more information, check :doc:`GPU isolation page <rocm:conceptual/gpu-isolation>`.

.. list-table::
    :header-rows: 1
    :widths: 70,30

    * - **Environment variable**
      - **Usage**

    * - | ``ROCR_VISIBLE_DEVICES``
        | A list of device indices or UUIDs that will be exposed to applications.
      - Example: ``0,GPU-DEADBEEFDEADBEEF``

    * - | ``GPU_DEVICE_ORDINAL``
        | Devices indices exposed to OpenCL and HIP applications.
      - Example: ``0,2``

    * - | ``HIP_VISIBLE_DEVICES`` or ``CUDA_VISIBLE_DEVICES``
        | Device indices exposed to HIP applications.
      - Example: ``0,2``

Profiling variables
===================

The profiling environment variables in HIP are collected in the next table. For more information, check :doc:`setting the number of CUs page <rocm:how-to/setting-cus>`.

.. list-table::
    :header-rows: 1
    :widths: 70,30

    * - **Environment variable**
      - **Usage**

    * - | ``HSA_CU_MASK``
        | Sets the mask on a lower level of queue creation in the driver,
        | this mask will also be set for queues being profiled.
      - Example: ``1:0-8``

    * - | ``ROC_GLOBAL_CU_MASK``
        | Sets the mask on queues created by the HIP or the OpenCL runtimes,
        | this mask will also be set for queues being profiled.
      - Example: ``0xf``, enables only 4 CUs

    * - | ``HIP_FORCE_QUEUE_PROFILING``
        | Used to run the app as if it were run in rocprof. Forces command queue
        | profiling on by default.
      - | 0: Disable
        | 1: Enable

Debug variables
===============

The debugging environment variables in HIP are collected in the next table. For more information, check :ref:`debugging_with_hip`.

.. include:: ../how-to/debugging_env.rst

Memory management related variables
===================================

The memory management related environment variables in HIP are collected in the next table.

.. list-table::
    :header-rows: 1
    :widths: 35,14,51

    * - **Environment variable**
      - **Default value**
      - **Usage**

    * - | ``HIP_HIDDEN_FREE_MEM``
        | Amount of memory to hide from the free memory reported by hipMemGetInfo.
      - ``0``
      - | 0: Disable
        | Unit: megabyte (MB)

    * - | ``HIP_HOST_COHERENT``
        | Coherent memory in ``hipHostMalloc``.
      - ``0``
      - | 0: Memory is not coherent between host and GPU.
        | 1: Memory is coherent with host.
        | Environment variable has effect, if:
        | - One of the HostMalloc flags is set.
        | - ``hipHostMallocCoherent=0``
        | - ``hipHostMallocNonCoherent=0``
        | - ``hipHostMallocMapped=0``

    * - | ``HIP_INITIAL_DM_SIZE``
        | Set initial heap size for device malloc.
      - ``8388608``
      - | Unit: Byte
        | The default value corresponds to 8 MB.

    * - | ``HIP_MEM_POOL_SUPPORT``
        | Enables memory pool support in HIP.
      - ``0``
      - | 0: Disable
        | 1: Enable

    * - | ``HIP_MEM_POOL_USE_VM``
        | Enables memory pool support in HIP.
      - | ``0``: other OS
        | ``1``: Windows
      - | 0: Disable
        | 1: Enable

    * - | ``HIP_VMEM_MANAGE_SUPPORT``
        | Virtual Memory Management Support.
      - ``1``
      - | 0: Disable
        | 1: Enable

    * - | ``GPU_MAX_HEAP_SIZE``
        | Set maximum size of the GPU heap to % of board memory.
      - ``100``
      - | Unit: Percentage

    * - | ``GPU_MAX_REMOTE_MEM_SIZE``
        | Maximum size that allows device memory substitution with system.
      - ``2``
      - | Unit: kilobyte (KB)

    * - | ``GPU_NUM_MEM_DEPENDENCY``
        | Number of memory objects for dependency tracking.
      - ``256``
      -

    * - | ``GPU_STREAMOPS_CP_WAIT``
        | Force the stream memory operation to wait on CP.
      - ``0``
      - | 0: Disable
        | 1: Enable

    * - | ``HSA_LOCAL_MEMORY_ENABLE``
        | Enable HSA device local memory usage.
      - ``1``
      - | 0: Disable
        | 1: Enable

    * - | ``PAL_ALWAYS_RESIDENT``
        | Force memory resources to become resident at allocation time.
      - ``0``
      - | 0: Disable
        | 1: Enable

    * - | ``PAL_PREPINNED_MEMORY_SIZE``
        | Size of prepinned memory.
      - ``64``
      - | Unit: kilobyte (KB)

    * - | ``REMOTE_ALLOC``
        | Use remote memory for the global heap allocation.
      - ``0``
      - | 0: Disable
        | 1: Enable

HIP environment variable tips
==============================

This documentation set is open source. Consider adding your own tips to this section. They will be reviewed by the AMD ROCm documentation team before being committed to the documentation.

* The performance can be improved at `GROMACS <https://github.com/ROCM/Gromacs>`_ HIP backend, when the ``ROC_ACTIVE_WAIT_TIMEOUT=0`` and ``ROC_USE_FGS_KERNARG=0`` environment variables are set.
* Unsupported AMD GPUs can act like supported GPUs, if the ``HSA_OVERRIDE_GFX_VERSION`` environment variable is set.
* ``ROC_GLOBAL_CU_MASK`` and ``HSA_CU_MASK`` can be used to see how a kernel scale with different CU numbers. If a kernel compute bounded, it shows linear scale with increasing CU numbers.
* ``AMD_LOG_LEVEL=3``, ``AMD_SERIALIZE_KERNEL=3`` and ``AMD_SERIALIZE_COPY=3`` can help to debug (without debugger) and see which kernel fails.
