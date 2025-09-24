# CUDA C Programming

## 参考资料
- 一个不错的博客网站：https://godweiyang.com/2021/01/25/cuda-reading/
    - CUDA编程入门极简教程: https://zhuanlan.zhihu.com/p/34587739 ✔
    - 《CUDA C Programming Guide》《CUDA C 编程指南》导读：https://zhuanlan.zhihu.com/p/53773183
    - CUDA编程入门系列：https://zhuanlan.zhihu.com/p/97044592
    - 谭升的博客: https://face2ai.com/program-blog/#GPU%E7%BC%96%E7%A8%8B%EF%BC%88CUDA%EF%BC%89
    - CUDA C Programming code: https://github.com/kriegalex/wrox-pro-cuda-c
    - How CUDA Programming Works | GTC 2022
        - [English](https://www.youtube.com/watch?v=n6M8R8-PlnE&ab_channel=DantheMan)
        - [Chinese](https://www.bilibili.com/video/BV1gF41127vp?vd_source=6d46640a443a49f050af078d1f65143e)
- 代码风格采用Google开源项目风指南-C++风格指南：https://zh-google-styleguide.readthedocs.io/en/latest/google-cpp-styleguide/contents.html 


## 项目环境
- Ubuntu 20.04 LTS (Host) / Ubuntu 18.04 LTS (Server) 
- Visual Studio Code, Remote-SSH, C/C++, Nsight Visual Studio Code Edition
- CUDA-11.3, cuDNN 8.9

``` bash
(base) houjinliang@3080server:~/cuda-11.3$ nsys --version
NVIDIA Nsight Systems version 2021.1.3.14-b695ea9
(base) houjinliang@3080server:~/cuda-11.3$ ncu --version
NVIDIA (R) Nsight Compute Command Line Profiler
Copyright (c) 2018-2021 NVIDIA Corporation
Version 2021.1.1.0 (build 29918364) (public-release)
```

## VSCode NVCC Configure

- 使用VSCode configuration
```bash
(base) houjinliang@3080server:~/MyDevProject/NPUCppCode/CUDACProgramming/.vscode$ ll
总用量 24
drwxrwxr-x 2 houjinliang houjinliang 4096 5月   5  2024 ./
drwxrwxr-x 4 houjinliang houjinliang 4096 2月  19 15:47 ../
-rw-rw-r-- 1 houjinliang houjinliang  453 5月   4  2024 c_cpp_properties.json
-rw-rw-r-- 1 houjinliang houjinliang  267 5月   4  2024 launch.json
-rw-rw-r-- 1 houjinliang houjinliang  541 5月  15  2024 settings.json
-rw-rw-r-- 1 houjinliang houjinliang  228 5月   4  2024 tasks.json
```
配置好了之后，可以在VSC下直接对“.cu”文件编译并进入DeBUG。

> 在Visual Studio Code（VSCode）编辑器中，`.vscode`目录用于存储特定于项目的配置文件。以下是对提到的四个文件的解释：

`c_cpp_properties.json`:这个文件是C/C++扩展的一部分，用于配置C/C++项目的 IntelliSense。IntelliSense 是VSCode中用于代码补全、参数信息、快速信息和成员列表的功能。它包含了诸如包含路径、定义、编译器路径和 IntelliSense 模式等配置，这些配置有助于VSCode正确解析和索引C/C++代码。

`launch.json`:这个文件用于配置VSCode的调试器。它定义了调试会话的属性，例如调试器类型（例如 GDB、LLDB、Python、Node.js 等）、程序启动命令、工作目录、环境变量、调试设置和断点等。用户可以通过修改这个文件来定制调试行为，例如设置程序启动参数、选择调试器、指定要调试的程序等。

`settings.json`:这个文件包含了项目特定的VSCode设置。在这里设置的配置会覆盖用户和工作区级别的设置。它可以包含各种各样的设置，比如编辑器行为、代码格式化选项、插件配置、文件关联等。

`tasks.json`:这个文件用于配置和管理VSCode中的任务。任务可以是任何外部工具，如编译器、构建脚本、命令行工具等。在这个文件中，你可以定义任务、它们的命令、参数、问题匹配器（用于捕获输出中的错误和警告）以及任务执行时的其他选项。

这些文件共同为C/C++项目提供了一个完整的开发环境配置，允许开发者自定义编辑、调试和构建过程。通过在.vscode目录下配置这些文件，开发者可以在不同的机器或不同的开发环境中轻松重现相同的开发体验。

- 直接在命令行使用nvcc
若是不借助VScode的配置，直接使用命令行的nvcc直接对“.cu”进行编译
``` bash
# 不进入调试（下面两个命令一样，仅仅是参数顺序不同）
nvcc cpt1_hello_from_gpu.cu -o main 
nvcc -o main cpt1_hello_from_gpu.cu
./main 

# 进入调试
nvcc -g -G -o main  cpt1_hello_from_gpu.cu
gdb ./main 
```

# CUDA 基础 - 谭升的博客 NOTE

## NVIDIA GPU Compute Capability
https://developer.nvidia.com/cuda-gpus#compute

GeForce RTX 3080	8.6
GeForce RTX 3090	8.6
GeForce RTX 4090	8.9

## Kernel核函数编写有以下限制
- 只能访问设备内存
- 必须有void返回类型
- 不支持可变数量的参数
- 不支持静态变量
- 显示异步行为

## 不再支持的nvprof命令

目前主流的 CUDA 驱动不再支持nvprof命令!

``` bash
(base) houjinliang@3080server:~/MyProject/NPUCppCode/CUDACProgramming$ nvprof ./main 
======== Warning: nvprof is not supported on devices with compute capability 8.0 and higher.
                  Use NVIDIA Nsight Systems for GPU tracing and CPU sampling and NVIDIA Nsight Compute for GPU profiling.
                  Refer https://developer.nvidia.com/tools-overview for more details.
```

> [CUDA编程性能分析工具-metrics参数含义 | 知乎](https://zhuanlan.zhihu.com/p/666242337)
> nsys 和 ncu 工具都有可视化版本，这里只讨论命令行版本。
> nsys是系统层面的分析工具，可以分析主机与设备端的信息。ncu则是用于分析核函数的工具。两者均有图形界面版本和命令行版本。

- 目前主流的 CUDA 驱动不再支持nvprof命令，但我们仍可以在 NVIDIA Nsight Systems 中使用，在终端输入 `nsys nvprof ./*.o`就可以看到CUDA 程序执行的具体内容。
```bash
nsys profile --stats=true ./main
```

- 另外，`nvprof --metrics` 命令的功能被转换到了 `ncu --metrics` 命令中。

## 性能分析工具 nsys and ncu

Nsight Systems *(nsys)*：/mnt/houjinliang/cuda-11.3/nsight-systems-2021.1.3
Nsight Compute *(ncu)* ：/mnt/houjinliang/cuda-11.3/nsight-compute-2021.1.1

Nsight Systems 是一个系统级性能分析工具，它允许开发者捕获和分析应用程序的整体行为，包括 CPU 和 GPU 的活动。
Nsight Compute 是一个用于 CUDA 核心分析和优化的命令行工具。它专注于 GPU 内部的执行细节，提供深入的分析来帮助开发者优化 CUDA 核函数和内存操作。

[【NsightSystem】Nsight System命令大全](https://blog.csdn.net/qq_37794738/article/details/137379665)

``` markdown
Nsight System

nsys profile：启动Nsight Systems的性能分析模式

-o 或 --output：指定输出文件的名称。例如，-o my_profile 会生成 my_profile.qdrep 和 my_profile.sqlite 文件。
–stat：启用或禁用统计信息的收集。接受的值为 true 或 false。

–capture-range：指定性能数据收集的范围。常见的值包括 cudaProfilerApi（基于 CUDA Profiler API 标记的区域）、nvtx（基于 NVTX 范围的区域）等。
–trace：控制哪些类型的事件应被追踪。例如，cuda、nvtx、osrt（操作系统运行时）等。
–sample：启用或禁用CPU采样。接受的值为 cpu 或 none。
–force-overwrite：如果输出文件已存在，强制覆盖。
–delay：分析开始前的延迟时间（以秒为单位）。
–duration：分析的持续时间（以秒为单位）。
–stop-on-exit：当应用退出时自动停止分析。
–kill：分析结束后杀死应用进程。
–pause：开始时暂停数据收集，直到显式恢复。
–cudabacktrace：当CUDA应用出现错误时，收集backtrace。
–cpuctxsw：追踪CPU上下文切换。
–gpu-metrics：指定要收集的GPU性能指标。
–export：在分析结束后自动导出报告，支持的格式包括 sqlite、qdrep、csv 等。
–launch：启动并分析一个应用程序。
```

### ncu 权限问题

- 普通用户使用ncu是没有权限的
``` bash
(base) houjinliang@3080server:~/MyDevProject/NPUCppCode/CUDACProgramming$ ncu ./main
==PROF== Connected to process 51302 (/mnt/houjinliang/MyDevProject/NPUCppCode/CUDACProgramming/main)
==ERROR== Error: ERR_NVGPUCTRPERM - The user does not have permission to access NVIDIA GPU Performance Counters on the target device 0. For instructions on enabling permissions and to get more information see https://developer.nvidia.com/ERR_NVGPUCTRPERM
GPU Execution configuration <<<(256, 256), (32, 32)>>>  time: 0.001107
==PROF== Disconnected from process 51302
==WARNING== No kernels were profiled.
==WARNING== Profiling kernels launched by child processes requires the --target-processes all option.
```

- 使用root用户把此普通用户加入到sudoers中
> [Linux学习-给普通用户加sudo权限 | CSDN](https://summit.csdn.net/?spm=1001.2101.3001.8293)
``` bash
# 执行这个命令会使用nano打开/etc/sudoers
visudo

# 在“root ALL=(ALL) ALL”这一行下面，再加入一行：
# xxxxxxx ALL=(ALL) ALL

# Ctrl + X退出Nano，退出的时候选择保存。
```

- xxxxxxx用户加入到sudoers中之后，无法使用sudo ncu
``` bash
(base) houjinliang@3080server:~/MyDevProject/NPUCppCode/CUDACProgramming$ sudo ncu ./main 
sudo: ncu：找不到命令
```

当你尝试使用 sudo 来运行 ncu 命令时，你遇到了 "找不到命令" 的错误，这是因为 sudo 默认不会使用普通用户的 PATH 环境变量。相反，sudo 使用的是根用户（root）的环境变量，这通常不包括普通用户的本地安装路径（如 ~/.local/bin）。
以下是一些原因和解决方案：

**原因:** 
- 环境变量PATH不同：普通用户和根用户的环境变量PATH通常是不同的。如果 ncu 安装在普通用户的路径下，那么在 sudo 下可能找不到它。
- 安全考虑：sudo 设计为最小化环境变量的使用，以防止恶意软件利用环境变量来执行未经授权的命令。

**解决方案:**
- (目前的使用方法)使用完整路径：如你已发现，使用 ncu 的完整路径可以解决这个问题，因为这样不依赖于环境变量。
``` bash
sudo /mnt/houjinliang/cuda-11.3/nsight-compute-2021.1.1/ncu ./main
```

- 修改sudoers文件：如果你经常需要以 sudo 方式运行特定路径下的命令，你可以修改 /etc/sudoers 文件来包含普通用户的 PATH。但是，这通常不被推荐，因为它可能会引入安全风险。
要安全地修改 sudoers 文件，使用 visudo 命令：
sudo visudo
然后在文件中添加以下行：
Defaults    secure_path = "/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/mnt/houjinliang/cuda-11.3/nsight-compute-2021.1.1"
请确保将 ncu 的路径添加到 secure_path 变量中。

- 创建符号链接：如果合适，你可以在根用户可访问的目录下创建一个指向 ncu 的符号链接，但这也需要管理员权限，并且可能不被系统管理员所接受。
sudo ln -s /mnt/houjinliang/cuda-11.3/nsight-compute-2021.1.1/ncu /usr/local/bin/ncu
然后你就可以直接使用 sudo ncu ./main。

请记住，任何对系统配置的更改都应该谨慎进行，并且最好理解其含义和潜在影响。如果你不确定如何操作，最好咨询系统管理员或查阅官方文档。


## 动态并行
``` bash
(base) houjinliang@3080server:~/MyDevProject/NPUCppCode/CUDACProgramming$ nvcc -o main  ts_nestedhelloworld.cu 
ts_nestedhelloworld.cu(16): error: kernel launch from __device__ or __global__ functions requires separate compilation mode

1 error detected in the compilation of "ts_nestedhelloworld.cu".
(base) houjinliang@3080server:~/MyDevProject/NPUCppCode/CUDACProgramming$ nvcc -o main  ts_nestedhelloworld.cu -lcudadevrt --relocatable-device-code true
```

`-lcudadevrt --relocatable-device-code true`这两个指令是动态并行需要的一个库。

## CUDA的优化从哪儿入手

一条大路（内存读取总线）连接了工厂生产车间（GPU）和材料仓库（全局内存），生产车间又有很多的工作小组（SM），材料仓库有很多小库房（内存分块），工作小组同时生产相同的产品互不干扰（并行），我们有车从材料仓库开往工厂车间，什么时候发车，运输什么由工作小组远程电话指挥（内存请求），发车前，从材料仓库装货的时候，还要听从仓库管理员的分配，因为可能同一间库房可能只允许一个车来拿材料（内存块访问阻塞），然后这些车单向的开往工厂，这时候就是交通问题了，如果我们的路是单向（从仓库到工厂）8车道，每秒钟能通过16辆车，那么我们把这个指标称为带宽。当然我们还有一条路是将成品运输到成品仓库，这也是一条路，与原料库互不干扰，和材料仓库到工厂的路一样，也有宽度，也是单向的，如果这条路堵住，和仓库到工厂的路堵住一样，此时工厂要停工等待。
最理想的状态是，路上全是车，并且全都高速行驶，工厂里的所有工人都在满负荷工作，没有等待，这就是优化的最终目标，如果这个目标达到了，还想进一步提高效率，那么你就只能优化你的工艺了（算法）

内存延迟是影响核函数的一大关键，内存延迟，也就是从你发起内存请求到数据进入SM的寄存器的整个时间。
内存带宽，也就是SM访问内存的速度，它以单位时间内传输的字节数进行测量。

## DRAM 加载和存储的吞吐量
``` bash
sudo ~/cuda-11.3/nsight-compute-2021.1.1/ncu --metrics dram__bytes_read.sum.per_second,dram__bytes_write.sum.per_second  ./main
```



## GPU的内存
- 按照物理上的位置
    - 板载内存（显卡的PCB板上的GDDR SDRAM）
    - 片上内存(显卡核心Die内部的Memory)

> DDR=Double Data Rate双倍速率同步动态随机存储器。严格的说DDR应该叫DDR SDRAM，人们习惯称为DDR，其中，SDRAM 是Synchronous Dynamic Random Access Memory的缩写，即同步动态随机存取存储器。而DDR SDRAM是Double Data Rate SDRAM的缩写，是双倍速率同步动态随机存储器的意思。
> GDDR是Graphics Double Data Rate的缩写，为显存的一种，GDDR是为了设计高端显卡而特别设计的高性能DDR存储器规格，其有专属的工作频率、时钟频率、电压，因此与市面上标准的DDR存储器有所差异，与普通DDR内存不同且不能共用。一般它比主内存中使用的普通DDR存储器时钟频率更高，发热量更小，所以更适合搭配高端显示芯片。

全局内存是较大的板载内存，延迟高，共享内存是片上的较小的内存，延迟低，带宽高。前面我我们讲过工厂的例子，全局内存就是原料工厂，要用车来运输原料，共享内存是工厂内存临时存放原料的房间，取原料路程短速度快。

共享内存是一种可编程的缓存，共享内存通常的用途有：
- 块内线程通信的通道
- 用于全局内存数据的可编程管理的缓存
- 告诉暂存存储器，用于转换数据来优化全局内存访问模式

![](https://murphyimg.oss-cn-beijing.aliyuncs.com/img/202503151220951.png)


## 存储体宽度

GeForce RTX 3080	8.6 
Total amout of shared memory per block:      49152 bytes(48.000000 kbytes)

## DeviceProp
https://docs.nvidia.com/cuda/cuda-runtime-api/structcudaDeviceProp.html


---

# CUDA_C_编程权威指南 BOOKNOTE

- 《CUDA C 编程权威指南》[美] 马克斯·格罗斯曼（Max Grossmen）& [美] 泰·麦克切尔（Ty McKercher） 机械工业出版社  2017年出版
    - 第1章　基于CUDA的异构并行计算
    - 第2章　CUDA编程模型
    - 第3章　CUDA执行模型
    - 第4章　全局内存
    - 第5章　共享内存和常量内存
    - 第6章　流和并发
    - 第7章　调整指令级原语
    - 第8章　GPU加速库和OpenACC
- 

## 第1章　基于CUDA的异构并行计算
- 第一章概述了CUDA编程的一些基础知识，如串行编程和并行编程、CPU与GPU的异构计算、来自GPU的hello world!
- 第一章的习题没什么大问题
 - 程序结束时： 在程序即将结束时调用 cudaDeviceReset() 可以确保释放所有CUDA资源，以避免内存泄漏或其他资源泄漏。
 - 如果程序结束时没有调用 cudaDeviceReset()，程序就没有输出“hello world from gpu”了。这是为什么？❓️

## 第2章　CUDA编程模型
- 这一章的重点内容在*CUDA的两级线性层次结构——grid和block*。⭐️
- ⭐️组织线程是CUDA编程的重点之一，但看完了这一章感觉有点儿稀里糊涂的，没有搞懂到底是怎么组织线程，怎么找到最佳执行配置！
- 线程和块索引映射到矩阵坐标上，矩阵坐标映射到全局内存中的索引/存储单元上的两个公式，很重要！⭐️
``` c
    unsigned int ix = threadIdx.x + blockIdx.x * blockDim.x;
    unsigned int iy = threadIdx.y + blockIdx.y * blockDim.y;
    unsigned int idx = iy * knx + ix;
```
- 二维网格与二维块，二维网格与一维块，一维网格与二维块，一维网格与一维块
- 第二章的习题。。。额。。不太会做啊！😭

## 第3章　CUDA执行模型第2章　CUDA编程模型

- CUDA编程模型中两个主要的抽象概念：内存层次结构和线程层次结构。

- CUDA采用单指令多线程（SIMT）架构来管理和执行线程，每32个线程为一组，被称为线程束（warp）。线程束是SM中基本的执行单元。

- 在同一个线程束中的线程执行不同的指令，被称为线程束分化。线程束分化会导致性能明显地下降。

- 带宽与吞吐量，都是用来度量性能的指标。
    - 带宽通常是理论峰值。
    - 吞吐量是指已达到的值。
    - 带宽通常是用来描述单位时间内最大可能的数据传输量。
    - 吞吐量是用来描述单位时间内任何形式的信息或操作的执行速度，例如，每个周期内完成多少个指令。

- CUDA编程是与硬件紧密相关的，我所用的GPU是RTX 3080
    - GA102 白皮书: https://www.nvidia.com/content/PDF/nvidia-ampere-ga-102-gpu-architecture-whitepaper-v2.pdf
    - RTX 3080 规格说明：https://www.bilibili.com/video/BV1oV41127q5/?spm_id_from=333.337.search-card.all.click&vd_source=6d46640a443a49f050af078d1f65143e
    - RTX 3080 GPU采用的是安培架构，核心代号GA102，但RTX 3080并没有用到完整的GA102,而是在完整的GA102的基础上阉割掉了一个GPC，所以可用SM之后68组。
    - 所使用的设备的信息可用下面两个程序查看：`cpt2_check_device_infor.cu`, `cpt3_simple_divice_query.cu`

- 网格与线程块的配置准则
    - 保持每个块中线程数量是线程束大小（32）的倍数
    - 避免块太小：每个块至少要有125或256个线程
    - 根据内核资源的需求调整块大小
    - 块的数量要远远多于SM的数量，从而在设备中可以显示有足够的并行
    - 通过实验得到最佳执行配置和资源使用情况

- 并行性的表现
    - 一个内核的可实现占用率被定义为：每周期内活跃线程束的平均数量与一个SM支持的线程束最大数量的比值。更高的占用率并不一定意味着有更高的性能。
    - 更高的加载吞吐量并不意味之更高的性能。
    - 一个块的最内层维数（block.x）应该是线程束大小的倍数。线程块最内层维度的大小对性能起着关键的作用！

- CUDA编程的性能指标
    - 在大部分情况下，一个单独的指标不能产生最佳的性能。
    - 与总体性能最直接相关的指标或事件取决于内核代码的本质。
    - 在相关的指标与事件之间寻求一个好的平衡。
    - 从不同角度查看内核以寻找相关指标之间的平衡。
    - 网格/块启发式算法为性能调节提供了一个很好的起点。

- 避免分支分化
    - 在向量中执行满足**交换律和结合律**的运算，被称为**规约问题**。
    - 并行规约问题。
    