#------------------------------------------------------------------------------
#
# CMake build system for different applications and tests
#
#------------------------------------------------------------------------------
#
# This file is licensed after LGPL v3
# Look at: https://www.gnu.org/licenses/lgpl-3.0.en.html for details
#
#------------------------------------------------------------------------------

set(APPS
  perm_app
  mmtuple_app
  hind_app
  gray_app
)

foreach(APP ${APPS})
  add_executable(${APP} ${APP}.c)
  target_link_libraries(${APP} comb)
endforeach()



