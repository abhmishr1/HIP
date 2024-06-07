.. meta::
    :description: HIP environment variables reference
    :keywords: AMD, HIP, environment variables, environment, reference

*************************************************************
HIP environment variables
*************************************************************

In this section the reader can find all the important HIP environment variables. The full collection of the ROCm environment variables is on the :doc:`ROCm environment variables page<rocm:reference/env-variables>`

GPU isolation
=============

The GPU isolation environment variables in HIP is collected in the next table  For more information, check :doc:`GPU isolation page <rocm:conceptual/gpu-isolation>`

.. list-table::
    :header-rows: 1

    * - **Environment variable**
      - **Example value**

    * - | ``ROCR_VISIBLE_DEVICES``
        | A list of device indices or UUIDs that will be exposed to applications.
      - ``0,GPU-DEADBEEFDEADBEEF``

    * - | ``GPU_DEVICE_ORDINAL``
        | Devices indices exposed to OpenCL and HIP applications.
      - ``0,2``

    * - | ``HIP_VISIBLE_DEVICES`` or ``CUDA_VISIBLE_DEVICES``
        | Device indices exposed to HIP applications.
      - ``0,2``

Profiling environment variables
===============================

The profiling environment variables in HIP is collected in the next table. For more information, check :doc:`setting the number of CUs page <rocm:conceptual/settings-cu>`

.. list-table::
    :header-rows: 1

    * - **Environment variable**
      - **Example value**

    * - | ``HSA_CU_MASK``
        | Sets the mask on a lower level of queue creation in the driver, 
        | this mask will also be set for queues being profiled.
      - ``1:0-8``

    * - | ``ROC_GLOBAL_CU_MASK``
        | Sets the mask on queues created by the HIP or the OpenCL runtimes, 
        | this mask will also be set for queues being profiled.
      -

    * - | ``ROCR_VISIBLE_DEVICES``
        | A list of device indices or UUIDs that will be exposed to applications.
      - ``0,GPU-DEADBEEFDEADBEEF``

    * - | ``HIP_FORCE_QUEUE_PROFILING``
        | Used to run the app as if it were run in rocprof. Forces command queue
        | profiling on by default.
      - ON, OFF

Debug environment variables
===========================

The debugging environment variables in HIP is collected in the next table. For more information, check :ref:`debugging_with_hip`

.. include:: ../how-to/debugging_env.rst

Memory management related environment variables
===============================================

The memory management related environment variables in HIP is collected in the 
next table.

.. list-table::
    :widths: 70,15,15
    :header-rows: 1

    * - Environment variable
      - Variable type
      - Default value

    * - | ``HIP_HIDDEN_FREE_MEM``
        | Reserve free mem reporting in Mb, 0 = Disable
      - ``uint``
      - 0

    * - | ``HIP_HOST_COHERENT``
        | Coherent memory in ``hipHostMalloc``
      - ``uint``
      - 0

    * - | ``HIP_INITIAL_DM_SIZE``
        | Set initial heap size for device malloc. The default value corresponds to 8 MiB
      - ``size_t``
      - 8388608

    * - | ``HIP_MEM_POOL_SUPPORT``
        | Enables memory pool support in HIP
      - ``bool``
      - ``false``

    * - | ``HIP_MEM_POOL_USE_VM``
        | Enables memory pool support in HIP
      - ``bool``
      - | ``true`` on Windows,
        | ``false`` on other OS

    * - | ``HIP_VMEM_MANAGE_SUPPORT``
        | Virtual Memory Management Support
      - ``bool``
      - ``true``

    * - | ``GPU_MAX_HEAP_SIZE``
        | Set maximum size of the GPU heap to % of board memory
      - ``uint``
      - 100

    * - | ``GPU_MAX_REMOTE_MEM_SIZE``
        | Maximum size , in Ki that allows device memory substitution with system
      - ``uint``
      - 2

    * - | ``GPU_NUM_MEM_DEPENDENCY``
        | Number of memory objects for dependency tracking
      - ``size_t``
      - 256

    * - | ``GPU_STREAMOPS_CP_WAIT``
        | Force the stream wait memory operation to wait on CP.
      - ``bool``
      - ``false``

    * - | ``HSA_LOCAL_MEMORY_ENABLE``
        | Enable HSA device local memory usage
      - ``bool``
      - ``true``

    * - | ``PAL_ALWAYS_RESIDENT``
        | Force memory resources to become resident at allocation time
      - ``bool``
      - ``false``

    * - | ``PAL_PREPINNED_MEMORY_SIZE``
        | Size in KBytes of prepinned memory
      - ``size_t``
      - 64

    * - | ``REMOTE_ALLOC``
        | Use remote memory for the global heap allocation
      - ``bool``
      - ``false``

HIP environment variables tips
==============================

Please feel free to open PR with your environment variable tips. We will check and add to this section.

* The performance can be improved at Gromacs HIP backend, when the
``ROC_ACTIVE_WAIT_TIMEOUT=0`` and ``ROC_USE_FGS_KERNARG=0`` environment
  variables are set.
* ``HSA_OVERRIDE_GFX_VERSION`` can be used for unsupported GPUs looks like
  supported GPUS. `HSA_OVERRIDE_GFX_VERSION example. <https://github.com/ROCm/ROCm/issues/2216>`_
* ``ROC_GLOBAL_CU_MASK`` and ``ROCR_VISIBLE_DEVICES`` can be used to see how a
  kernel scale with different CU numbers. If a kernel compute bounded, it shows
  linear scale with increasing CU numbers.
* ``AMD_LOG_LEVEL=3``, ``AMD_SERIALIZE_KERNEL=3`` and ``AMD_SERIALIZE_COPY=3``
  can help to debug (without debugger) and see which kernel fails.
