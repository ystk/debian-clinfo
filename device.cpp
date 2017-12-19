#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "device.h"

device::device(cl_device_id id) : id(id)
{
        return;
}

template<typename T>
void device::query(T &value, cl_device_info info)
{
        size_t length;
        cl_int rc = clGetDeviceInfo(id, info, sizeof value, &value, &length);
        if(rc != CL_SUCCESS)
                throw rc;
        if(length != sizeof value)
                throw length;
}

void device::query(std::string &value, cl_device_info info)
{
        size_t length;
        cl_int rc = clGetDeviceInfo(id, info, 0, 0, &length);
        if(rc != CL_SUCCESS)
                throw rc;
        char buffer[length];
        rc = clGetDeviceInfo(id, info, length, buffer, 0);
        if(rc != CL_SUCCESS)
                throw rc;
        value = buffer;
}

template<typename T, typename L>
void device::query(std::vector<T> &value, L count, cl_device_info info)
{
        value.resize(count);
        size_t length;
        cl_int rc = clGetDeviceInfo(id, info, sizeof(T) * count, value.data(), &length);
        if(rc != CL_SUCCESS)
                throw rc;
        if(length != sizeof(T) * count)
                throw length;
}

void device::load()
{
        query(address_bits, CL_DEVICE_ADDRESS_BITS);
        query(available, CL_DEVICE_AVAILABLE);
        query(built_in_kernels, CL_DEVICE_BUILT_IN_KERNELS);
        query(compiler_available, CL_DEVICE_COMPILER_AVAILABLE);
        try
        {
                query(double_fp_config, CL_DEVICE_DOUBLE_FP_CONFIG);
        }
        catch(cl_int)
        {
                double_fp_config = 0;
        }
        query(driver_version, CL_DRIVER_VERSION);
        query(endian_little, CL_DEVICE_ENDIAN_LITTLE);
        query(error_correction_support, CL_DEVICE_ERROR_CORRECTION_SUPPORT);
        query(execution_capabilities, CL_DEVICE_EXECUTION_CAPABILITIES);
        query(extensions, CL_DEVICE_EXTENSIONS);
        query(global_mem_cacheline_size, CL_DEVICE_GLOBAL_MEM_CACHELINE_SIZE);
        query(global_mem_cache_size, CL_DEVICE_GLOBAL_MEM_CACHE_SIZE);
        query(global_mem_cache_type, CL_DEVICE_GLOBAL_MEM_CACHE_TYPE);
        query(global_mem_size, CL_DEVICE_GLOBAL_MEM_SIZE);
        try
        {
                query(half_fp_config, CL_DEVICE_HALF_FP_CONFIG);
        }
        catch(cl_int)
        {
                half_fp_config = 0;
        }
        query(host_unified_memory, CL_DEVICE_HOST_UNIFIED_MEMORY);

        query(image_support, CL_DEVICE_IMAGE_SUPPORT);
        if(image_support)
        {
                query(image2d_max_height, CL_DEVICE_IMAGE2D_MAX_HEIGHT);
                query(image2d_max_width, CL_DEVICE_IMAGE2D_MAX_WIDTH);
                query(image3d_max_depth, CL_DEVICE_IMAGE3D_MAX_DEPTH);
                query(image3d_max_height, CL_DEVICE_IMAGE3D_MAX_HEIGHT);
                query(image3d_max_width, CL_DEVICE_IMAGE3D_MAX_WIDTH);
                //query(image_max_array_size, CL_DEVICE_IMAGE_MAX_ARRAY_SIZE);
                //query(image_max_buffer_size, CL_DEVICE_IMAGE_MAX_BUFFER_SIZE);
        }

        try
        {
                query(linker_available, CL_DEVICE_LINKER_AVAILABLE);
        }
        catch(cl_int)
        {
                linker_available = CL_FALSE;
        }
        query(local_mem_size, CL_DEVICE_LOCAL_MEM_SIZE);
        query(local_mem_type, CL_DEVICE_LOCAL_MEM_TYPE);
        query(max_clock_frequency, CL_DEVICE_MAX_CLOCK_FREQUENCY);
        query(max_compute_units, CL_DEVICE_MAX_COMPUTE_UNITS);
        query(max_constant_args, CL_DEVICE_MAX_CONSTANT_ARGS);
        query(max_constant_buffer_size, CL_DEVICE_MAX_CONSTANT_BUFFER_SIZE);
        query(max_mem_alloc_size, CL_DEVICE_MAX_MEM_ALLOC_SIZE);
        query(max_parameter_size, CL_DEVICE_MAX_PARAMETER_SIZE);
        query(max_read_image_args, CL_DEVICE_MAX_READ_IMAGE_ARGS);
        query(max_samplers, CL_DEVICE_MAX_SAMPLERS);
        query(max_work_group_size, CL_DEVICE_MAX_WORK_GROUP_SIZE);

        {
                cl_uint max_work_item_dimensions;
                query(max_work_item_dimensions, CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS);
                query(max_work_item_sizes, max_work_item_dimensions, CL_DEVICE_MAX_WORK_ITEM_SIZES);
        }

        query(max_write_image_args, CL_DEVICE_MAX_WRITE_IMAGE_ARGS);
        query(mem_base_addr_align, CL_DEVICE_MEM_BASE_ADDR_ALIGN);
        query(min_data_type_align_size, CL_DEVICE_MIN_DATA_TYPE_ALIGN_SIZE);
        query(name, CL_DEVICE_NAME);
        query(native_vector_width_char, CL_DEVICE_NATIVE_VECTOR_WIDTH_CHAR);
        query(native_vector_width_double, CL_DEVICE_NATIVE_VECTOR_WIDTH_DOUBLE);
        query(native_vector_width_float, CL_DEVICE_NATIVE_VECTOR_WIDTH_FLOAT);
        query(native_vector_width_half, CL_DEVICE_NATIVE_VECTOR_WIDTH_HALF);
        query(native_vector_width_int, CL_DEVICE_NATIVE_VECTOR_WIDTH_INT);
        query(native_vector_width_long, CL_DEVICE_NATIVE_VECTOR_WIDTH_LONG);
        query(native_vector_width_short, CL_DEVICE_NATIVE_VECTOR_WIDTH_SHORT);
        query(opencl_c_version, CL_DEVICE_OPENCL_C_VERSION);
        try
        {
                query(parent_device, CL_DEVICE_PARENT_DEVICE);
        }
        catch(cl_int)
        {
                parent_device = 0;
        }
        try
        {
                query(partition_affinity_domain, CL_DEVICE_PARTITION_AFFINITY_DOMAIN);
                query(partition_max_sub_devices, CL_DEVICE_PARTITION_MAX_SUB_DEVICES);
                query(partition_properties, CL_DEVICE_PARTITION_PROPERTIES);
                query(partition_type, CL_DEVICE_PARTITION_TYPE);
        }
        catch(cl_int)
        {
        }
        query(platform, CL_DEVICE_PLATFORM);
        try
        {
                query(preferred_interop_user_sync, CL_DEVICE_PREFERRED_INTEROP_USER_SYNC);
                query(printf_buffer_size, CL_DEVICE_PRINTF_BUFFER_SIZE);
        }
        catch(cl_int)
        {
        }
        query(preferred_vector_width_char, CL_DEVICE_PREFERRED_VECTOR_WIDTH_CHAR);
        query(preferred_vector_width_double, CL_DEVICE_PREFERRED_VECTOR_WIDTH_DOUBLE);
        query(preferred_vector_width_float, CL_DEVICE_PREFERRED_VECTOR_WIDTH_FLOAT);
        query(preferred_vector_width_half, CL_DEVICE_PREFERRED_VECTOR_WIDTH_HALF);
        query(preferred_vector_width_int, CL_DEVICE_PREFERRED_VECTOR_WIDTH_INT);
        query(preferred_vector_width_long, CL_DEVICE_PREFERRED_VECTOR_WIDTH_LONG);
        query(preferred_vector_width_short, CL_DEVICE_PREFERRED_VECTOR_WIDTH_SHORT);
        query(profile, CL_DEVICE_PROFILE);
        query(queue_properties, CL_DEVICE_QUEUE_PROPERTIES);
        if(queue_properties & CL_QUEUE_PROFILING_ENABLE)
        {
                query(profiling_timer_resolution, CL_DEVICE_PROFILING_TIMER_RESOLUTION);
        }
        query(single_fp_config, CL_DEVICE_SINGLE_FP_CONFIG);
        query(type, CL_DEVICE_TYPE);
        query(vendor_id, CL_DEVICE_VENDOR_ID);
        query(vendor, CL_DEVICE_VENDOR);
        query(version, CL_DEVICE_VERSION);
}
