target_sources(adhan PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/astronomical.c
  ${CMAKE_CURRENT_LIST_DIR}/calculation_parameters.c
  ${CMAKE_CURRENT_LIST_DIR}/calendrical_helper.c
  ${CMAKE_CURRENT_LIST_DIR}/CMakeLists.txt
  ${CMAKE_CURRENT_LIST_DIR}/data_components.c
  ${CMAKE_CURRENT_LIST_DIR}/prayer_times.c
  ${CMAKE_CURRENT_LIST_DIR}/solar_coordinates.c
  ${CMAKE_CURRENT_LIST_DIR}/solar_time.c
) 

target_include_directories(adhan PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include/adhan)