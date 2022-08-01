cmake_minimum_required(VERSION 3.0.0)
project(adhan VERSION 0.1.0)

include(CTest)
include(CPack)
include(GNUInstallDirs)
include(CMakePackageConfigHelpers)
include(CheckLibraryExists)


option(BUILD_SHARED_LIBS "Build libadhan as a shared library" OFF)
option(ADHAN_WITH_TESTS "Build libadhan with tests" OFF)
option(ADHAN_WITH_CMAKE "Build libadhan with cmake files" ON)
option(ADHAN_WITH_PKGCONF "Build libadhan with pkgconf .pc files" ON)



add_library(adhan)

add_subdirectory(src)

set(PUBLIC_HEADERS 
  include/adhan.h
  include/adhan/astronomical.h
  include/adhan/calculation_method.h
  include/adhan/calculation_parameters.h
  include/adhan/calendrical_helper.h
  include/adhan/coordinates.h
  include/adhan/data_components.h
  include/adhan/double_utils.h
  include/adhan/high_latitude_rule.h
  include/adhan/madhab.h
  include/adhan/prayer_adjustments.h
  include/adhan/prayer.h
  include/adhan/prayer_times.h
  include/adhan/shadow.h
  include/adhan/solar_coordinates.h
  include/adhan/solar_time.h
)

CHECK_LIBRARY_EXISTS(m sin "" HAVE_LIB_M)                                                                                                
                                                                                                                                         
if (HAVE_LIB_M)                                                                                                                          
  set(EXTRA_LIBS ${EXTRA_LIBS} m)
  set(LIBM_FLAG "-lm")                                                                                                      
endif (HAVE_LIB_M)

set_target_properties(adhan PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(adhan PROPERTIES SOVERSION 1)

target_link_libraries(adhan PUBLIC ${EXTRA_LIBS})

target_include_directories(adhan PUBLIC 
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include/adhan
)

if (ADHAN_WITH_PKGCONF)
  configure_file(adhan.pc.in adhan.pc @ONLY)
  install(FILES ${CMAKE_BINARY_DIR}/adhan.pc
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/pkgconfig)
endif(ADHAN_WITH_PKGCONF)

if (ADHAN_WITH_TESTS)
  add_subdirectory(test)
endif(ADHAN_WITH_TESTS)


if (ADHAN_WITH_CMAKE)
  configure_package_config_file("cmake/adhanConfig.cmake.in"
    ${CMAKE_CURRENT_BINARY_DIR}/adhanConfig.cmake
    INSTALL_DESTINATION ${LIB_INSTALL_DIR}/adhan/cmake)
  write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/adhanConfigVersion.cmake
    COMPATIBILITY SameMajorVersion)

  install(TARGETS adhan EXPORT adhanTargets)

  install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/adhanConfig.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/adhanConfigVersion.cmake
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/adhan)
  install(EXPORT adhanTargets
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/adhan)
endif(ADHAN_WITH_CMAKE)

install(TARGETS adhan
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

enable_testing()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})

