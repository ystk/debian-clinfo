#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "output_amd_compat.h"

#include "output_common.h"

#include "device.h"

#include <iostream>
#include <algorithm>

void output_amd_compat_platform_summary(platform const &p);
void output_amd_compat_platform_details(platform const &p);
void output_amd_compat_device(device const &);
void output_amd_compat_fp_config(cl_device_fp_config);

void output_amd_compat_platform_summary(platform const &p)
{
        std::cout << "  Platform Profile:\t\t\t\t " << p.profile << std::endl;
        std::cout << "  Platform Version:\t\t\t\t " << p.version << std::endl;
        std::cout << "  Platform Name:\t\t\t\t " << p.name << std::endl;
        std::cout << "  Platform Vendor:\t\t\t\t " << p.vendor << std::endl;
        std::cout << "  Platform Extensions:\t\t\t\t " << p.extensions << std::endl;
}

void output_amd_compat_platform_details(platform const &p)
{
        std::cout << "  Platform Name:\t\t\t\t " << p.name << std::endl;
        std::cout << "Number of devices:\t\t\t\t " << p.devices.size() << std::endl;
        std::for_each(p.devices.begin(), p.devices.end(), &output_amd_compat_device);
}

void output_amd_compat_device(device const &d)
{
        std::cout << "  Device Type:\t\t\t\t\t " << device_type_to_string(d.type) << std::endl;
        std::cout << "  Device ID:\t\t\t\t\t " << d.vendor_id << std::endl;
        //std::cout << "  Board name:\t\t\t\t\t " << d.name << std::endl;
        std::cout << "  Max compute units:\t\t\t\t " << d.max_compute_units << std::endl;
        cl_uint max_work_item_dimensions = d.max_work_item_sizes.size();
        std::cout << "  Max work items dimensions:\t\t\t " << max_work_item_dimensions << std::endl;
        for(cl_uint i = 0; i < max_work_item_dimensions; ++i)
                std::cout << "    Max work items[" << i << "]:\t\t\t\t " << d.max_work_item_sizes[i] << std::endl;
        std::cout << "  Max work group size:\t\t\t\t " << d.max_work_group_size << std::endl;
        std::cout << "  Preferred vector width char:\t\t\t " << d.preferred_vector_width_char << std::endl;
        std::cout << "  Preferred vector width short:\t\t\t " << d.preferred_vector_width_short << std::endl;
        std::cout << "  Preferred vector width int:\t\t\t " << d.preferred_vector_width_int << std::endl;
        std::cout << "  Preferred vector width long:\t\t\t " << d.preferred_vector_width_long << std::endl;
        std::cout << "  Preferred vector width float:\t\t\t " << d.preferred_vector_width_float << std::endl;
        std::cout << "  Preferred vector width double:\t\t " << d.preferred_vector_width_double << std::endl;
        std::cout << "  Native vector width char:\t\t\t " << d.native_vector_width_char << std::endl;
        std::cout << "  Native vector width short:\t\t\t " << d.native_vector_width_short << std::endl;
        std::cout << "  Native vector width int:\t\t\t " << d.native_vector_width_int << std::endl;
        std::cout << "  Native vector width long:\t\t\t " << d.native_vector_width_long << std::endl;
        std::cout << "  Native vector width float:\t\t\t " << d.native_vector_width_float << std::endl;
        std::cout << "  Native vector width double:\t\t\t " << d.native_vector_width_double << std::endl;
        std::cout << "  Max clock frequency:\t\t\t\t " << d.max_clock_frequency << "Mhz" << std::endl;
        std::cout << "  Address bits:\t\t\t\t\t " << d.address_bits << std::endl;
        std::cout << "  Max memory allocation:\t\t\t " << d.max_mem_alloc_size << std::endl;
        std::cout << "  Image support:\t\t\t\t " << (d.image_support != CL_FALSE ? "Yes":"No") << std::endl;
        std::cout << "  Max number of images read arguments:\t\t " << d.max_read_image_args << std::endl;
        std::cout << "  Max number of images write arguments:\t\t " << d.max_write_image_args << std::endl;
        std::cout << "  Max image 2D width:\t\t\t\t " << d.image2d_max_width << std::endl;
        std::cout << "  Max image 2D height:\t\t\t\t " << d.image2d_max_height << std::endl;
        std::cout << "  Max image 3D width:\t\t\t\t " << d.image3d_max_width << std::endl;
        std::cout << "  Max image 3D height:\t\t\t\t " << d.image3d_max_height << std::endl;
        std::cout << "  Max image 3D depth:\t\t\t\t " << d.image3d_max_depth << std::endl;
        std::cout << "  Max samplers within kernel:\t\t\t " << d.max_samplers << std::endl;
        std::cout << "  Max size of kernel argument:\t\t\t " << d.max_parameter_size << std::endl;
        std::cout << "  Alignment (bits) of base address:\t\t " << d.mem_base_addr_align << std::endl;
        std::cout << "  Minimum alignment (bytes) for any datatype:\t " << d.min_data_type_align_size << std::endl;
        std::cout << "  Single precision floating point capability" << std::endl;
        output_amd_compat_fp_config(d.single_fp_config);
        std::cout << "  Cache type:\t\t\t\t\t ";
        switch(d.global_mem_cache_type)
        {
        case CL_NONE:             std::cout << "None";       break;
        case CL_READ_ONLY_CACHE:  std::cout << "Read Only";  break;
        case CL_READ_WRITE_CACHE: std::cout << "Read/Write"; break;
        }
        std::cout << std::endl;
        std::cout << "  Cache line size:\t\t\t\t " << d.global_mem_cacheline_size << std::endl;
        std::cout << "  Cache size:\t\t\t\t\t " << d.global_mem_cache_size << std::endl;
        std::cout << "  Global memory size:\t\t\t\t " << d.global_mem_size << std::endl;
        std::cout << "  Constant buffer size:\t\t\t\t " << d.max_constant_buffer_size << std::endl;
        std::cout << "  Max number of constant args:\t\t\t " << d.max_constant_args << std::endl;
        std::cout << "  Local memory type:\t\t\t\t ";
        switch(d.local_mem_type)
        {
        case CL_LOCAL:  std::cout << "Local";  break;
        case CL_GLOBAL: std::cout << "Global"; break;
        }
        std::cout << std::endl;
        std::cout << "  Local memory size:\t\t\t\t " << d.local_mem_size << std::endl;
        std::cout << "  Error correction support:\t\t\t " << d.error_correction_support << std::endl;
        std::cout << "  Unified memory for Host and Device:\t\t " << d.host_unified_memory << std::endl;
        std::cout << "  Profiling timer resolution:\t\t\t " << d.profiling_timer_resolution << std::endl;
        std::cout << "  Device endianess:\t\t\t\t " << (d.endian_little ? "Little" : "Big") << std::endl;
        std::cout << "  Available:\t\t\t\t\t " << (d.available ? "Yes":"No") << std::endl;
        std::cout << "  Compiler available:\t\t\t\t " << (d.compiler_available ? "Yes":"No") << std::endl;
        std::cout << "  Execution capabilities:\t\t\t\t " << std::endl;
        std::cout << "    Execute OpenCL kernels:\t\t\t " << ((d.execution_capabilities & CL_EXEC_KERNEL) ? "Yes" : "No") << std::endl;
        std::cout << "    Execute native function:\t\t\t " << ((d.execution_capabilities & CL_EXEC_NATIVE_KERNEL) ? "Yes" : "No") << std::endl;
        std::cout << "  Queue properties:\t\t\t\t " << std::endl;
        std::cout << "    Out-of-Order:\t\t\t\t " << ((d.queue_properties & CL_QUEUE_OUT_OF_ORDER_EXEC_MODE_ENABLE) ? "Yes":"No") << std::endl;
        std::cout << "    Profiling :\t\t\t\t\t " << ((d.queue_properties & CL_QUEUE_PROFILING_ENABLE) ? "Yes":"No") << std::endl;
        std::cout << "  Platform ID:\t\t\t\t\t " << d.platform << std::endl;
        std::cout << "  Name:\t\t\t\t\t\t " << d.name << std::endl;
        std::cout << "  Vendor:\t\t\t\t\t " << d.vendor << std::endl;
        std::cout << "  Device OpenCL C version:\t\t\t " << d.opencl_c_version << std::endl;
        std::cout << "  Driver version:\t\t\t\t " << d.driver_version << std::endl;
        std::cout << "  Profile:\t\t\t\t\t " << d.profile << std::endl;
        std::cout << "  Version:\t\t\t\t\t " << d.version << std::endl;
        std::cout << "  Extensions:\t\t\t\t\t " << d.extensions << std::endl;
        std::cout << std::endl;
        std::cout << std::endl;

}

void output_amd_compat_fp_config(cl_device_fp_config config)
{
        std::cout << "    Denorms:\t\t\t\t\t " << ((config & CL_FP_DENORM) ? "Yes":"No") << std::endl;
        std::cout << "    Quiet NaNs:\t\t\t\t\t " << ((config & CL_FP_INF_NAN) ? "Yes":"No") << std::endl;
        std::cout << "    Round to nearest even:\t\t\t " << ((config & CL_FP_ROUND_TO_NEAREST) ? "Yes":"No") << std::endl;
        std::cout << "    Round to zero:\t\t\t\t " << ((config & CL_FP_ROUND_TO_ZERO) ? "Yes":"No") << std::endl;
        std::cout << "    Round to +ve and infinity:\t\t\t " << ((config & CL_FP_ROUND_TO_INF) ? "Yes":"No") << std::endl;
        std::cout << "    IEEE754-2008 fused multiply-add:\t\t " << ((config & CL_FP_FMA) ? "Yes":"No") << std::endl;
}

void output_amd_compat(std::list<platform> const &platforms)
{
        std::cout << "Number of platforms:\t\t\t\t " << platforms.size() << std::endl;
        std::for_each(platforms.begin(), platforms.end(), &output_amd_compat_platform_summary);
        std::cout << std::endl << std::endl;
        std::for_each(platforms.begin(), platforms.end(), &output_amd_compat_platform_details);
}
