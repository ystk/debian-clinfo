#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "output_common.h"

char const *device_type_to_string(cl_device_type t)
{
        switch(t)
        {
        case CL_DEVICE_TYPE_GPU:
                return "CL_DEVICE_TYPE_GPU";
        case CL_DEVICE_TYPE_CPU:
                return "CL_DEVICE_TYPE_CPU";
        default:
                return "(unknown)";
        }
}
