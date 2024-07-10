cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
project(libtorch_ex)

add_compile_options(-O3)
add_compile_options(-pg)

set(Caffe2_DIR "$ENV{HOME}/pytorch/torch/share/cmake/Caffe2")
set(Torch_DIR "$ENV{HOME}/pytorch/torch/share/cmake/Torch")
find_package(Torch REQUIRED)
find_package(Eigen3 REQUIRED)
find_package(Python3 COMPONENTS Interpreter Development)
find_package(pybind11 REQUIRED)
find_package(matplotlibcpp17)



add_executable(${PROJECT_NAME} src/main.cpp)
target_include_directories(${PROJECT_NAME} PRIVATE ./include)
target_link_libraries(${PROJECT_NAME} ${TORCH_LIBRARIES} Eigen3::Eigen ${Python3_LIBRARIES} pybind11::embed matplotlibcpp17::matplotlibcpp17)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)
