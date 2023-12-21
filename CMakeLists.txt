cmake_minimum_required(VERSION 2.8)
project(video_stream_server)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

find_package(Boost COMPONENTS
  thread
  system
  regex
  REQUIRED
  )

if (Boost_FOUND)
  message(STATUS "Boost headers at ${Boost_INCLUDE_DIRS}")
  message(STATUS "Boost libraries at ${Boost_LIBRARIES}")
endif()
add_subdirectory(json_spirit)

find_package(OpenCV REQUIRED)
include_directories(
  ${Boost_INCLUDE_DIRS}
  ${CMAKE_CURRENT_SOURCE_DIR}
  )

add_executable(video_server  server.cpp)
target_link_libraries(video_server
    ${OpenCV_LIBS}
    boost_thread boost_system boost_regex
)

add_executable(video_client  client.cpp)
target_link_libraries(video_client
    ${OpenCV_LIBS}
    boost_thread boost_system boost_regex
)

  
