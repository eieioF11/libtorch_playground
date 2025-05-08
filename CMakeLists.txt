cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
project(libtorch_ex)

add_compile_options(-O3)
add_compile_options(-pg)

if (NOT PYTHON_EXECUTABLE)
    set(PYTHON_EXECUTABLE "python3")
endif()

# Pytorchのライブラリのcmake_prefix_pathを取得
execute_process(COMMAND ${PYTHON_EXECUTABLE} -c "import torch; print(torch.utils.cmake_prefix_path, end='')" OUTPUT_VARIABLE pytorch_path)
list(APPEND CMAKE_PREFIX_PATH "${pytorch_path}") # CMAKE_PREFIX_PATHに追加

# libtorch find
find_package(Torch REQUIRED)
find_package(Eigen3 REQUIRED)
find_package(Python3 COMPONENTS Interpreter Development)
find_package(pybind11 REQUIRED)
find_package(matplotlibcpp17)



add_executable(${PROJECT_NAME} src/main.cpp)
target_include_directories(${PROJECT_NAME} PRIVATE ./include)
target_link_libraries(${PROJECT_NAME} ${TORCH_LIBRARIES} Eigen3::Eigen ${Python3_LIBRARIES} pybind11::embed matplotlibcpp17::matplotlibcpp17)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)
