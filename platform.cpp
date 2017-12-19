#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "platform.h"

#include "device.h"

platform::platform(cl_platform_id id) throw() : id(id)
{
        return;
}

platform::platform(platform const &p) :
        id(p.id),
        profile(p.profile),
        version(p.version),
        name(p.name),
        vendor(p.vendor),
        extensions(p.extensions),
        devices(p.devices)
{
        return;
}

platform::~platform() throw()
{
        return;
}

void platform::load()
{
        query(name, CL_PLATFORM_NAME);
        query(vendor, CL_PLATFORM_VENDOR);
        query(profile, CL_PLATFORM_PROFILE);
        query(version, CL_PLATFORM_VERSION);
        query(extensions, CL_PLATFORM_EXTENSIONS);

        cl_uint num_device_ids;
        cl_int rc = clGetDeviceIDs(id, CL_DEVICE_TYPE_ALL, 0, 0, &num_device_ids);
        if(rc != CL_SUCCESS)
                throw rc;

        cl_device_id device_ids[num_device_ids];
        rc = clGetDeviceIDs(id, CL_DEVICE_TYPE_ALL, num_device_ids, device_ids, 0);
        if(rc != CL_SUCCESS)
                throw rc;

        for(cl_device_id const *i = device_ids; i != device_ids + num_device_ids; ++i)
                devices.insert(devices.end(), device(*i))->load();
}

void platform::query(std::string &value, cl_platform_info info)
{
        size_t length;
        cl_int rc = clGetPlatformInfo(id, info, 0, 0, &length);
        if(rc != CL_SUCCESS)
                throw rc;
        char buffer[length];
        rc = clGetPlatformInfo(id, info, length, buffer, 0);
        if(rc != CL_SUCCESS)
                throw rc;
        value = buffer;
}

