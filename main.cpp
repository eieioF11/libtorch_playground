// std
#include <algorithm>
#include <chrono>
#include <cmath>
#include <functional>
#include <iostream>
#include <limits>
#include <map>
#include <memory>
#include <optional>
#include <random>
#include <stdio.h>
#include <unistd.h>
#include <vector>
// matplotlibcpp17
#include <matplotlibcpp17/pyplot.h>
// Eigen
#include <Eigen/Dense>
// Torch
#include <torch/torch.h>



int main()
{
  torch::Tensor x = torch::full({3, 3}, 1.5, torch::TensorOptions().dtype(torch::kFloat));
  std::cout << x << std::endl;
  return 0;
}
