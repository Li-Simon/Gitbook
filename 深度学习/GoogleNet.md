## GoogleNet

特点：  
1. 不使用全连接层，而是用平均池化代替全连接层，减小模型的参数数量,这种想法来自于NIN。  
2. 采用一种高效的机器视觉深度神经网络结构，称为"Inception",这种模块化结构方便增加与修改，现在inception版本到了V6/V7。GoogLeNet中采用了9个inception模块。  
3. 为了避免梯度小时，网络额外增加了2个辅助的softmax用于向前传导梯度。

### Inception v1模型[^1]

![](/assets/GoogLeNetInception.png)  
1. Inception V1:它将1x1，3x3，5x5的conv和3x3的pooling，堆叠在一起，一方面增加了网络的width，另一方面增加了网络对尺度的适应性；  
2. inception先通过一个1\*1的低channel的卷积核，来对后面的大的卷积核起降维作用，进而控制参数量。  
GoogLeNet的参数 :可以看出里面用7x7的平均池代替了全连接。

### Inception v2模型

一方面了加入了BN层，减少了Internal Covariate Shift（内部neuron的数据分布发生变化），使每一层的输出都规范化到一个N\(0, 1\)的高斯；  
　　另外一方面学习VGG用2个3x3的conv替代inception模块中的5x5，既降低了参数数量，也加速计算；  

![](/assets/Inception_v2.png)



使用3×3的已经很小了，那么更小的2×2呢？2×2虽然能使得参数进一步降低，但是不如另一种方式更加有效，那就是Asymmetric方式，即使用1×3和3×1两种来代替3×3的卷积核。这种结构在前几层效果不太好，但对特征图大小为12~20的中间层效果明显。

### Inception v3模型

v3一个最重要的改进是分解（Factorization），将7x7分解成两个一维的卷积（1x7,7x1），3x3也是一样（1x3,3x1），这样的好处，既可以加速计算（多余的计算能力可以用来加深网络），又可以将1个conv拆成2个conv，使得网络深度进一步增加，增加了网络的非线性，还有值得注意的地方是网络输入从224x224变为了299x299，更加精细设计了35x35/17x17/8x8的模块。

### Inception v4模型

v4研究了Inception模块结合Residual Connection能不能有改进？发现ResNet的结构可以极大地加速训练，同时性能也有提升，得到一个Inception-ResNet v2网络，同时还设计了一个更深更优化的Inception v4模型，能达到与Inception-ResNet v2相媲美的性能。

#### 后续改进的版本总结：

1. Inception-v2在之前的版本中主要加入了batch Normalization；另外也借鉴VGGNet的思想，用两个3x3的卷积代替5x5的卷积，不仅降低了训练参数，也提升了速度。  
2. Inception-3在v2的基础上进一步分解大的卷积，比如把nxn的卷积拆分成两个一维卷积：1xn,nx1。  
3. Inception-V4借鉴了ResNet可以构建更深层网络的思想，设计了一个更深更优化的模型。  

![](/assets/GoogLeNetParameters.png)

### GoogleNet structure

![](/assets/GoogleNet_structure.png)

### Auxiliary Classifiers[^2]

需要注意的是，为了避免梯度消失，网络额外增加了2个辅助的softmax用于向前传导梯度。文章中说这两个辅助的分类器的loss应该加一个衰减系数，实际测试的时候，这两个额外的softmax会被去掉。  
在GoogLeNet中，使用了多余的在底层的分类器，直觉上可以认为这样做可以使底层能够在梯度下降中学的比较充分，但在实践中发现两条：   
1. 多余的分类器在训练开始的时候并不能起到作用，在训练快结束的时候，使用它可以有所提升最底层的那个多余的分类器去掉以后也不会有损失。  
2. 以为多余的分类器起到的是梯度传播下去的重要作用，但通过实验认为实际上起到的是regularizer的作用，因为在多余的分类器前添加dropout或者batch normalization后效果更佳。

### 1\*1的卷积核与Inception[^3]

[^1]: 深入浅出——网络模型中Inception的作用与结构全解析深入浅出——网络模型中Inception的作用与结构全解析  [https://blog.csdn.net/u010402786/article/details/52433324](https://blog.csdn.net/u010402786/article/details/52433324)

[^2]:  Inception in CNN  [https://blog.csdn.net/stdcoutzyx/article/details/51052847](https://blog.csdn.net/stdcoutzyx/article/details/51052847)   

[^3]:  1\*1的卷积核与Inception  [https://blog.csdn.net/a1154761720/article/details/53411365](https://blog.csdn.net/a1154761720/article/details/53411365)

