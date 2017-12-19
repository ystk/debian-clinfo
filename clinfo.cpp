/* 
 * Copyright (C) 2013 Simon Richter
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <CL/cl.h>
#include <CL/cl_ext.h>

#include <iostream>

#include "platform.h"

#include "output_amd_compat.h"

#include <list>

int main(int, char **)
{
        std::list<platform> platforms;

        try
        {
                cl_uint num_platform_ids;
                cl_int rc = clGetPlatformIDs(0, 0, &num_platform_ids);
                switch(rc)
                {
                case CL_SUCCESS:
                        break;

                case CL_PLATFORM_NOT_FOUND_KHR:
                        std::cerr << "I: ICD loader reports no usable platforms" << std::endl;
                        return 0;

                default:
                        throw rc;
                }

                cl_platform_id platform_ids[num_platform_ids];

                rc = clGetPlatformIDs(num_platform_ids, platform_ids, 0);
                if(rc != CL_SUCCESS)
                        throw rc;

                for(cl_platform_id const *i = platform_ids; i != platform_ids + num_platform_ids; ++i)
                        platforms.insert(platforms.end(), platform(*i))->load();


                output_amd_compat(platforms);

                return 0;
        }
        catch(cl_int e)
        {
                std::cerr << "E: " << e << std::endl;
                return 1;
        }
}
