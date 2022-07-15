cmake_minimum_required(VERSION 3.15)

# set the project name and version
project(Tutorial VERSION 1.0)

# add configure to pass version to cpp file
configure_file(TutorialConfig.h.in TutorialConfig.h)

set(SRC_LIST tutorial.cpp)

# use std variable CMAKE_CXX_STANDARD to specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

option(USE_MYMATH "Use tutorial provided math implementation" ON)
option(USE_MPI "Use MPI" ON)

if(USE_MYMATH)
  message(STATUS "=========USE_MYMATH=========")

  # in cpp file, ifdef USE_MYMATH can be used! 
  add_definitions(-DUSE_MYMATH)

  # add the MathFunctions library
  #  命令指定库所在子目录，该子目录下应包含 CMakeLists.txt 文件和代码文件。
  add_subdirectory(MathFunctions)

  list(APPEND EXTRA_LIBS MathFunctions)
  # list(APPEND EXTRA_INCLUDES ${PROJECT_SOURCE_DIR}/MathFunctions)
endif()

if(USE_MPI)
  find_package(MPI)
  if(MPI_CXX_FOUND)
    message(STATUS "MPI support found")
    message(STATUS "MPI compile flags: " ${MPI_CXX_COMPILE_FLAGS})
    message(STATUS "MPI include path: " ${MPI_CXX_INCLUDE_PATH})
    message(STATUS "MPI LINK flags path: " ${MPI_CXX_LINK_FLAGS})
    message(STATUS "MPI libraries: " ${MPI_CXX_LIBRARIES})
    
    add_definitions(-DMPI_INCLUDE=\"${MPI_CXX_INCLUDE_PATH}\")
    add_definitions(-DMPI_LIBRARY=\"${MPI_CXX_LIBRARIES}\")

    include_directories(SYSTEM ${MPI_CXX_INCLUDE_PATH})
    list(APPEND Caffe2_DEPENDENCY_LIBS ${MPI_CXX_LIBRARIES})
    find_program(OMPI_INFO
      NAMES ompi_info
      HINTS ${MPI_CXX_LIBRARIES}/../bin)
    if(OMPI_INFO)
      execute_process(COMMAND ${OMPI_INFO}
                      OUTPUT_VARIABLE _output)
      if(_output MATCHES "smcuda")
        message(STATUS "Found OpenMPI with CUDA support built.")
      else()
        message(WARNING "OpenMPI found, but it is not built with CUDA support.")
      endif()
    endif()
  else()
    message(WARNING "Not compiling with MPI. Suppress this warning with -DUSE_MPI=OFF")
  endif()
endif()


# CMake 中的 target 有可执行文件和库文件，分别使用 add_executable 和 add_library 命令生成，
# 除了指定生成的可执行文件名/库文件名，还需要指定相关的源文件。

# add the executable
add_executable(${PROJECT_NAME} ${SRC_LIST})

# 可执行文件要使用库文件，需要能够找到库文件和对应的头文件，
# 可以分别通过 target_link_libraries 和 target_include_directories 来指定。

target_link_libraries(${PROJECT_NAME} PUBLIC ${EXTRA_LIBS})

# add the binary tree to the search path for include files
# so that we will find TutorialConfig.h
# PROJECT_BINARY_DIR 表示当前工程的二进制路径, 将该目录添加到搜索头文件的路径列表中
target_include_directories(${PROJECT_NAME} PUBLIC
                           ${PROJECT_BINARY_DIR}
                           # ${EXTRA_INCLUDES}
                           )
