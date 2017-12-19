#
#   Copyright (C) 2012 Simon Richter
#
#   This program is free software: you can redistribute it and/or modify
#   it under the terms of the GNU General Public License as published by
#   the Free Software Foundation, either version 3 of the License, or
#   (at your option) any later version.
#
#   This program is distributed in the hope that it will be useful,
#   but WITHOUT ANY WARRANTY; without even the implied warranty of
#   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#   GNU General Public License for more details.
#
#   You should have received a copy of the GNU General Public License
#   along with this program.  If not, see <http://www.gnu.org/licenses/>.

# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.67])
AC_INIT([clinfo], [0.0.20130513], [Simon.Richter@hogyros.de])
AM_INIT_AUTOMAKE([1.10 foreign])

AC_CONFIG_SRCDIR([clinfo.cpp])

# Checks for programs.
AC_PROG_CXX

# Checks for libraries.
AC_CHECK_LIB([OpenCL], [clGetPlatformIDs])

# Checks for header files.

# Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_SIZE_T

# Checks for library functions.

AC_CONFIG_FILES([Makefile])
AC_CONFIG_HEADERS([config.h])
AC_OUTPUT
