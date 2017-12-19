#ifndef clinfo_device_h_
#define clinfo_device_h_ 1

#include <CL/cl.h>
#include <CL/cl_ext.h>

#include <string>
#include <vector>

struct device
{
        device(cl_device_id);

        void load();

        cl_device_id const id;

        cl_device_id parent_device;

        std::string name;
        cl_platform_id platform;
        cl_device_type type;
        cl_uint vendor_id;
        std::string vendor;
        std::string profile;
        std::string version;
        std::string opencl_c_version;
        std::string driver_version;

        std::string built_in_kernels;

        // Availability
        cl_bool available;

        // Extensions
        std::string extensions;

        // General info
        cl_uint max_clock_frequency;
        cl_uint max_compute_units;
        cl_uint address_bits;
        cl_bool endian_little;
        cl_bool error_correction_support;
        cl_device_exec_capabilities execution_capabilities;
        cl_command_queue_properties queue_properties;

        std::vector<size_t> max_work_item_sizes;

        size_t max_parameter_size;
        cl_uint max_constant_args;
        cl_ulong max_constant_buffer_size;
        size_t max_work_group_size;
        size_t printf_buffer_size;

        cl_ulong profiling_timer_resolution;

        // Partitioning
        cl_uint partition_max_sub_devices;
        cl_device_partition_property partition_properties;
        cl_device_affinity_domain partition_affinity_domain;
        cl_uint partition_type;

        // Tools
        cl_bool compiler_available;
        cl_bool linker_available;

        // Floating Point
        cl_device_fp_config half_fp_config;
        cl_device_fp_config single_fp_config;
        cl_device_fp_config double_fp_config;

        // Vector
        cl_uint native_vector_width_char, preferred_vector_width_char;
        cl_uint native_vector_width_short, preferred_vector_width_short;
        cl_uint native_vector_width_int, preferred_vector_width_int;
        cl_uint native_vector_width_long, preferred_vector_width_long;
        cl_uint native_vector_width_half, preferred_vector_width_half;
        cl_uint native_vector_width_float, preferred_vector_width_float;
        cl_uint native_vector_width_double, preferred_vector_width_double;

        // Memory
        cl_bool host_unified_memory;
        cl_ulong global_mem_size;
        cl_ulong local_mem_size;
        cl_device_local_mem_type local_mem_type;
        cl_ulong max_mem_alloc_size;
        cl_uint min_data_type_align_size;
        cl_uint mem_base_addr_align;

        // Cache
        cl_device_mem_cache_type global_mem_cache_type;
        cl_ulong global_mem_cache_size;
        cl_uint global_mem_cacheline_size;

        // Images
        cl_bool image_support;
        size_t image2d_max_width, image2d_max_height;
        size_t image3d_max_width, image3d_max_height, image3d_max_depth;
        cl_uint max_read_image_args, max_write_image_args;
        cl_uint max_samplers;
        cl_uint image_max_array_size;
        cl_uint image_max_buffer_size;

        // Interop
        cl_uint preferred_interop_user_sync;

private:
        template<typename T> void query(T &, cl_device_info);
        void query(std::string &, cl_device_info);
        template<typename T, typename L> void query(std::vector<T> &, L, cl_device_info);
};

#endif
