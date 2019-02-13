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

#### 后续改进的版本：

1. Inception-v2在之前的版本中主要加入了batch Normalization；另外也借鉴VGGNet的思想，用两个3x3的卷积代替5x5的卷积，不仅降低了训练参数，也提升了速度。  
2. Inception-3在v2的基础上进一步分解大的卷积，比如把nxn的卷积拆分成两个一维卷积：1xn,nx1。  
3. Inception-V4借鉴了ResNet可以构建更深层网络的思想，设计了一个更深更优化的模型。  

![](/assets/GoogLeNetParameters.png)

### GoogleNet structure

![](/assets/GoogleNet_structure.png)


[^1]: 深入浅出——网络模型中Inception的作用与结构全解析深入浅出——网络模型中Inception的作用与结构全解析  https://blog.csdn.net/u010402786/article/details/52433324

