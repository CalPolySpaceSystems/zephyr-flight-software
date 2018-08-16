include($ENV{ZEPHYR_BASE}/cmake/app/boilerplate.cmake NO_POLICY_SCOPE)
project(NONE)

target_sources(app PRIVATE src/main.c)


# The external static library that we are linking with does not know
# how to build for this platform so we export all the flags used in
# this zephyr build to the external build system.
#
# Other external build systems may be self-contained enough that they
# do not need any build information from zephyr. Or they may be
# incompatible with certain zephyr options and need them to be
# filtered out.
zephyr_get_include_directories_for_lang_as_string(       C includes)
zephyr_get_system_include_directories_for_lang_as_string(C system_includes)
zephyr_get_compile_definitions_for_lang_as_string(       C definitions)
zephyr_get_compile_options_for_lang_as_string(           C options)

set(external_project_cflags
  "${includes} ${definitions} ${options} ${system_includes}"
  )

include(ExternalProject)

# Add an external project to be able download and build the third
# party library. In this case downloading is not necessary as it has
# been committed to the repository.
set(ms56xx_src_dir   ${CMAKE_CURRENT_SOURCE_DIR}/ms56xx)
set(ms56xx_build_dir ${CMAKE_CURRENT_BINARY_DIR}/ms56xx)

set(ms56xx_LIB_DIR     ${ms56xx_build_dir}/lib)
set(ms56xx_INCLUDE_DIR ${ms56xx_src_dir}/include)

ExternalProject_Add(
  ms56xx_project                 # Name for custom target
  PREFIX     ${ms56xx_build_dir} # Root dir for entire project
  SOURCE_DIR ${ms56xx_src_dir}
  BINARY_DIR ${ms56xx_src_dir} # This particular build system is invoked from the root
  CONFIGURE_COMMAND ""    # Skip configuring the project, e.g. with autoconf
  BUILD_COMMAND
  make
  PREFIX=${ms56xx_build_dir}
  CC=${CMAKE_C_COMPILER}
  CFLAGS=${external_project_cflags}
  INSTALL_COMMAND ""      # This particular build system has no install command
  BUILD_BYPRODUCTS ${ms56xx_LIB_DIR}/libms56xx.a
  )

# Create a wrapper CMake library that our app can link with
add_library(ms56xx_lib STATIC IMPORTED GLOBAL)
add_dependencies(
  ms56xx_lib
  ms56xx_project
  )
set_target_properties(ms56xx_lib PROPERTIES IMPORTED_LOCATION             ${ms56xx_LIB_DIR}/libms56xx.a)
set_target_properties(ms56xx_lib PROPERTIES INTERFACE_INCLUDE_DIRECTORIES ${ms56xx_INCLUDE_DIR})

target_link_libraries(app ms56xx_lib)
