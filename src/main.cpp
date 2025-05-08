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

namespace Neuralnetworks {
  struct LinearImpl : torch::nn::Module {
    LinearImpl(int in, int out) {
      weight = register_parameter("W", torch::randn({in, out}));
      bias   = register_parameter("b", torch::randn(out));
    };

    torch::Tensor forward(const torch::Tensor& input);
    torch::Tensor weight, bias;
  };
  TORCH_MODULE(Linear);

  class DenseNetImpl : public torch::nn::Module {
  public:
    DenseNetImpl(const std::vector<int>& units) {
      size_t numlayers = units.size() - 1;
      this->numlayers  = numlayers;
      for (int i = 0; i < numlayers; i++) {
        auto n_in         = units.at(i);
        auto n_out        = units.at(i + 1);
        Linear layer_temp = Linear(n_in, n_out);
        this->linears_.push_back(layer_temp);

        register_module("linear_" + std::to_string(i), this->linears_[i]);
      }
    };
    torch::Tensor forward(const torch::Tensor& input);

  private:
    std::vector<Linear> linears_;
    size_t numlayers;
  };
  TORCH_MODULE(DenseNet);
} // namespace Neuralnetworks

torch::Tensor Neuralnetworks::LinearImpl::forward(const torch::Tensor& input) {
  return at::add(matmul(input, this->weight), this->bias); //+ this->bias;
}

torch::Tensor Neuralnetworks::DenseNetImpl::forward(const torch::Tensor& input) {
  torch::Tensor x = input.clone();
  for (int i = 0; i < this->numlayers - 1; i++) {
    x = torch::tanh(this->linears_.at(i)->forward(x));
  }
  x = this->linears_.at(this->numlayers - 1)->forward(x);

  return at::sum(x, 0);
}

int main() {
  std::cout << "cuda is available:" << torch::cuda::is_available() << std::endl;
  std::cout << "cuda device count:" << torch::cuda::device_count() << std::endl;
  std::cout << std::endl;
  torch::Tensor x = torch::full({3, 3}, 1.5, torch::TensorOptions().dtype(torch::kFloat));
  std::cout << x << std::endl;

  torch::Tensor tensor = torch::rand({3});
  std::cout << tensor << std::endl;

  std::vector<int> layers{3, 10, 1};
  auto model = Neuralnetworks::DenseNet(layers);
  auto y     = model->forward(tensor);
  std::cout << y << std::endl;
  y.backward();
  for (auto& param : model->named_parameters()) {
    std::cout << "value" << std::endl;
    std::cout << param.value() << std::endl;
    std::cout << "gradient " << std::endl;
    std::cout << param.value().grad() << std::endl;
  }
  return 0;
}

// int main()
// {
//   std::cout << "cuda is available:" << torch::cuda::is_available() << std::endl;
//   std::cout << "cuda device count:" << torch::cuda::device_count() << std::endl;
//   std::cout << std::endl;
//   torch::Tensor x = torch::full({3, 3}, 1.5, torch::TensorOptions().dtype(torch::kFloat));
//   std::cout << x << std::endl;
//   return 0;
// }
