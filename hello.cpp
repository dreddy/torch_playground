#include <torch/extension.h>

#include <iostream>

void print_world (void) {
    std::cout<< "Hello World" << std::endl;
}

torch::Tensor tensor_xor(torch::Tensor z, uint32_t magic) {
    torch::Tensor b = torch::autograd::Variable(z.clone()).detach();
    auto acsr = b.accessor<float,2>(); // Assuming a 2-D array

    for(int i=0; i<acsr.size(0); i++) {
        for(int j=0; j<acsr.size(1); j++) {
            uint32_t temp = *(int *)(&acsr[i][j]);
            temp ^= magic;
            acsr[i][j] = *(float*)(&temp);
        }
    }
    return b;
}

PYBIND11_MODULE(TORCH_EXTENSION_NAME, m) {
    m.def("print_world", &print_world, "Print hello");
    m.def("tensor_xor", &tensor_xor, "Xor tensor with a scalar");
}
