#------------------------------------------------------------------------------
#
# CMake build system for combinatorial library
#
#------------------------------------------------------------------------------
#
# This file is licensed after LGPL v3
# Look at: https://www.gnu.org/licenses/lgpl-3.0.en.html for details
#
#------------------------------------------------------------------------------

set(SOURCES
  perms.c
  mmtuple.c
  mmtuple-loopless.c
  hind.c
  gray-codes.c
  gray-rho.c
)

add_library(comb ${SOURCES})
target_include_directories(comb PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})