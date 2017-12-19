#ifndef clinfo_platform_h_
#define clinfo_platform_h_ 1

#include <list>
#include <string>

#include <CL/cl.h>

struct device;

struct platform
{
        platform(cl_platform_id) throw();
        platform(platform const &);
        ~platform() throw();

        void load();

        cl_platform_id const id;

        std::string profile;
        std::string version;
        std::string name;
        std::string vendor;
        std::string extensions;

        std::list<device> devices;

private:
        void query(std::string &, cl_device_info);
};

#endif
