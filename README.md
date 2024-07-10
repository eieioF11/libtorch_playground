# libtorch_playground
libtorchの勉強用

## 環境構築
```bash
cd
git clone https://github.com/pytorch/pytorch
cd pytorch
git submodule update --init --recursive
python3 setup.py build
mkdir build_libtorch && cd build_libtorch
python3 ../tools/build_libtorch.py
```

## build
```bash
mkdir build
cd build
cmake ..
make
```
## run
```bash
cd build
./libtorch_ex
```

## mem
- https://pytorch.org/cppdocs/installing.html
- https://pytorch.org/docs/stable/cuda.html
