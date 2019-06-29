# Tensorflor整体框架

### 总体结构[^1]

从底向上分为设备管理和通信层、数据操作层、图计算层、API接口层、应用层。  
![](/assets/tensorflow_framework.png)  
1. 底层设备通信层负责网络通信和设备管理。  
   1. 设备管理可以实现TF设备异构的特性，支持CPU、GPU、Mobile等不同设备。  
   2. 网络通信依赖gRPC通信协议实现不同设备间的数据传输和更新。  
2. 数据操作层是Tensor的OpKernels实现。这些OpKernels以Tensor为处理对象，依赖网络通信和设备内存分配，实现了各种Tensor操作或计算。Opkernels不仅包含MatMul等计算操作，还包含Queue等非计算操作  
3. 图计算层（Graph），包含本地计算流图和分布式计算流图的实现。Graph模块包含Graph的创建、编译、优化和执行等部分，Graph中每个节点都是OpKernels类型表示。  
4. API接口层。Tensor C API是对TF功能模块的接口封装，便于其他语言平台调用。  
5. 应用层。不同编程语言在应用层通过API接口层调用TF核心功能实现相关实验和应用。

#### 代码结构

以2018.09.23的master为基准:  
tensorflow/core  
![](/assets/tensorflow_code_code.png)

其中，tensorflow/core目录包含了TF核心模块代码：

public: API接口头文件目录，用于外部接口调用的API定义，主要是session.h。  
client: API接口实现文件目录。（目前已经没有这个目录了…）  
platform: OS系统相关接口文件，如file system, env等。  
protobuf: 均为.proto文件，用于数据传输时的结构序列化。（都是proto3的语法）  
common\_runtime: 公共运行库，包含session, executor, threadpool, rendezvous, memory管理, 设备分配算法等。  
distributed\_runtime: 分布式执行模块，如rpc session, rpc master, rpc worker, graph manager。  
framework: 包含基础功能模块，如log, memory, tensor  
graph: 计算流图相关操作，如construct, partition, optimize, execute等  
kernels: 核心Op，如matmul, conv2d, argmax, batch\_norm等  
lib: 公共基础库，如gif、gtl\(google模板库\)、hash、histogram、jpeg、png、wav等。  
ops: 基本ops运算\(xxx\_ops.cc\)，ops梯度运算（xxx\_grad.cc），io相关的       ops（io\_ops.cc），控制流和数据流\*操作（control\_flow\_ops.cc和data\_flow\_ops.cc）  
tensorflow/stream\_executor

tensorflow/stream\_executor目录是并行计算框架，由google stream executor团队开发。

tensorflow/contrib

tensorflow/contrib目录是contributor开发目录。

tensroflow/python

tensroflow/python目录是python API客户端脚本

##### third\_party

eigen3：eigen矩阵运算库，tf基础ops调用  
gpus: 封装了cuda/cudnn编程库



[^1]: tensorflow代码解析——概览  [https://daiwk.github.io/posts/platform-tensorflow-code-analysis-overview.html](https://daiwk.github.io/posts/platform-tensorflow-code-analysis-overview.html)  

[^2]: EasyTensorflow [https://www.easy-tensorflow.com/tf-tutorials/basics/graph-and-session](https://www.easy-tensorflow.com/tf-tutorials/basics/graph-and-session)

