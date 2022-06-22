#------------------------------------------------------------------------------
#
# CMake build system for paving and combinatorial examples
#
#------------------------------------------------------------------------------
#
# This file is licensed after LGPL v3
# Look at: https://www.gnu.org/licenses/lgpl-3.0.en.html for details
#
#------------------------------------------------------------------------------

cmake_minimum_required(VERSION 3.15)
project(pavings)
enable_testing()

# library for combinatorial algrothims
add_subdirectory(comb)

# applications
add_subdirectory(apps)

install()