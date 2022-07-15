
# MathFunctions/CMakeLists.txt
# add a MathFunctions lib
# static lib
add_library(MathFunctions mysqrt.cpp)

# CMAKE_CURRENT_SOURCE_DIR 表示 MathFunctions 库所在目录
target_include_directories(MathFunctions
          INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
          )
