if (MSVC)
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /NODEFAULTLIB:LIBCMTD")
else (MSVC)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fpermissive")
endif (MSVC)
enable_language(CXX)
enable_testing()

#set(gtest_disable_pthreads on) #needed in MinGW
if (MINGW)
  set(gtest_disable_pthreads on)
endif (MINGW)

message(STATUS "Fetching GoogleTest Library, please wait...")
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY      https://github.com/google/googletest.git
  GIT_TAG             main
)

FetchContent_GetProperties(googletest)
if(NOT googletest_POPULATED)
  FetchContent_Populate(googletest)
  set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
  add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()
message(STATUS "Done fetching and seting up GoogleTest!")


set(test_SRCS
        test.cpp
        astronomical_test.cpp
        double_utils_test.cpp
        calculation_method_test.cpp
        calculation_parameters_test.cpp
        prayer_times_test.cpp)

add_executable(adhantest ${test_SRCS})
add_dependencies(adhantest adhan)
target_link_libraries(adhantest
        gtest
        gmock
        adhan
        ${EXTRA_LIBS})

add_test(
  NAME adhantest
  COMMAND $<TARGET_FILE:adhantest>
  )
