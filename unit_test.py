#!/usr/bin/env python3

import torch, hello_cpp
import time

for size in {512, 1024, 2048}:
    a = torch.rand(size,size)
    for i in {0,1,2,3,4}:
        tic=time.time()
        b=hello_cpp.tensor_xor(a, 0xdeadbeef)
        toc=time.time()
        print(f"Time for {size}x{size} iter {i}:: {toc-tic} secs ")
