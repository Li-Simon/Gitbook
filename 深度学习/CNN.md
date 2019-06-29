# CNN

CNN主要是处理空间数据，比如图像数据。CNN主要包含LetNet-5,AlexNet,GoogLeNet,VGG,Residual Net,Dense Net。  
CNN核心：局部感受野，权值共享，时间或空间亚采样这三种思想来保证某种程度的平移，尺度，形变不变性。  
介绍每种模型的时候，要说明这种模型的优点，最好能阐述为啥会有这种优点。

## CNN基础知识

这里，我们将讨论CNN中用到的基础知识，比如：卷积，stride, paddle, pooling, 激活函数，误差反向传播，局部感知，权值共享。

#### [如何理解CNN中的卷积？](https://blog.csdn.net/cheneykl/article/details/79740810)

#### CNN相对于全连接网络的好处

减少模型参数数量，减少计算时间。

#### CNN的卷积核与特征提取

[CNN中卷积核数目以及参数数据的计算](https://blog.csdn.net/yanzi6969/article/details/78019683)。根据的是相邻两层feature maps个数，以及每个map的大小来计算出所用卷积核的数目。

#### CNN的卷积核大小为啥是奇数?

不能保持对称性，比如原来图像长度宽是MxM，卷积核大小是nxn，则卷积作用后图像大小是\(M-n+1\)x\(M-n+1\)，如果n是偶数，则n-1是奇数，因此处理后的图像不再对称了。  
在这里，我们将要计算模型中，两层之间的参数数目。

#### [如何计算CNN两层之间参数数目](https://blog.csdn.net/yanzi6969/article/details/78019683)

![](/assets/LeNet-5.png)  
C1层是卷积层，单通道下用了6个卷积核，这样就得到了6个feature map，其中每个卷积核的大小为5\*5，用每个卷积核与原始的输入图像进行卷积，这样feature map的大小为\(32-5+1\)×\(32-5+1\)= 28×28，所需要的参数的个数为\(5×5+1\)×6= 156\(其中5×5为卷积模板参数，1为偏置参数\)，连接数为\(5×5+1\)×28×28×6=122304\(其中28×28为卷积后图像的大小\)。

S2层为 pooling 层，也可以说是池化或者特征映射的过程，拥有6个 feature map，每个feature map的大小为14\*14，每个feature map的隐单元与上一层C1相对应的feature map的 2×2 单元相连接，这里没有重叠。计算过程是：2×2 单元里的值相加然后再乘以训练参数w，再加上一个偏置参数b\(每一个feature map共享相同w和b\)，然后取sigmoid 值，作为对应的该单元的值。所以S2层中每 feature map 的长宽都是上一层C1的一半。S2层需要2×6=12个参数，连接数为\(4+1\)×14×14×6 = 5880。注：这里池化的过程与ufldl教程中略有不同。下面为卷积操作与池化的示意图：

![](/assets/Conv_Pooling.png)

计算CNN相邻两层之间参数数目，假设上层有大小是NxMxM，其中n是通道数目，MxM是图像大小。如果连接下一层的卷积核大小是nxn，我们可以对上一层的a个通道做卷积，则每次操作需要a个卷积核，再加上一个偏置，则需要axnxn+1个参数，假设下一层有K个通道，则两层之间所有的参数数目是K\(axnxn+1\)。这里a可以取不同值，也可以是不同值的组合，比如在LeNet-5中，S2到C3之间就存在不同通道的组合，C3的前6个特征图以S2中3个相邻的特征图子集为输入\(1-&gt;2-&gt;3-&gt;4-&gt;5-&gt;6-&gt;1\)。接下来6个特征图以S2中4个相邻特征图子集为输入。然后的3个以不相邻的4个特征图子集为输入。最后一个将S2中所有特征图为输入。这样C3层有6\(3\*25+1\)+6\*\(4\*25+1\)+3\*\(4\_25+1）+\(25\*6+1\)=1516个可训练参数和10\*10\*1516=151600个连接。

#### CNN怎么实现误差反向传播

#### CNN的pooling的作用

降维与信息提取。

### 下采样与上采样的误差怎么传递与反向？

[卷积神经网络\(CNN\)反向传播算法](https://www.cnblogs.com/pinard/p/6494810.html)  
[CNN中一些特殊环节的反向传播](https://blog.csdn.net/qq_21190081/article/details/72871704)

CNN网络中另外一个不可导的环节就是Pooling池化操作，因为Pooling操作使得feature map的尺寸变化，假如做2×22×22 \times 2的池化，假设那么第l+1l+1l+1层的feature map有16个梯度，那么第lll层就会有64个梯度，这使得梯度无法对位的进行传播下去。其实解决这个问题的思想也很简单，就是把1个像素的梯度传递给4个像素，但是**需要保证传递的loss（或者梯度）总和不变**。根据这条原则，mean pooling和max pooling的反向传播也是不同的。

#### 1、mean pooling {#1mean-pooling}

mean pooling的前向传播就是把一个patch中的值求取平均来做pooling，那么反向传播的过程也就是把某个元素的梯度等分为n份分配给前一层，这样就保证池化前后的梯度（残差）之和保持不变，还是比较理解的，  
 mean pooling比较容易让人理解错的地方就是会简单的认为直接把梯度复制N遍之后直接反向传播回去，但是这样会造成loss之和变为原来的N倍，网络是会产生梯度爆炸的。

#### 2、max pooling {#2max-pooling}

max pooling也要满足梯度之和不变的原则，max pooling的前向传播是把patch中最大的值传递给后一层，而其他像素的值直接被舍弃掉。那么反向传播也就是把梯度直接传给前一层某一个像素，而其他像素不接受梯度，也就是为0。所以max pooling操作和mean pooling操作不同点在于需要记录下池化操作时到底哪个像素的值是最大，也就是max id，这个可以看caffe源码的pooling\_layer.cpp，下面是caffe框架max pooling部分的源码

```cpp
// If max pooling, we will initialize the vector index part.
if (this->layer_param_.pooling_param().pool() == PoolingParameter_PoolMethod_MAX && top.size() == 1)
{
    max_idx_.Reshape(bottom[0]->num(), channels_, pooled_height_,pooled_width_);
  }
```

源码中有一个max\_idx\_的变量，这个变量就是记录最大值所在位置的，因为在反向传播中要用到，那么假设前向传播和反向传播的过程就如下图所示

#### ImageNet top5 error record history

![](/assets/ImageNetTop5History.png)  
网络层数随历史的变化。  
![](/assets/ImageNetTop5Layers.png)

## AlexNet

![](/assets/AlexNet structure.png)  
AlexNet的优点，  
1. 使用ReLU作为激活函数，消除了sigmoid,tanh造成的梯度消失问题。同时也减小了激活函数的计算量。  
2. 百万数据和多GPU训练减小了计算时间。  
3. 局部相应归一化\(LRN,Local Response Normalization\)  
4. 重叠池化，也就是pooling的尺寸小于步长。  
5. 通过数据增强\(裁剪，平移，尺度变换，水平翻转，加随机光照\)与Dropout降低过拟合

## VGG

相对于以前的网络而言，VGG与GoogLeNet的网络变得更深了。VGGNet在整个网络中使用3x3的小感受野，以步长1进行逐像素卷积，因此两个3x3卷积相当于一个5x5,三个3x3卷积核相当于一个7x7的卷积核，这样大大减小了模型的参数个数。  使用了小尺寸的卷积核，增加了网络深度并不会带来明显的参数膨胀，却能在更深的网络中获得更高的精度。  
![](/assets/VGG_structure.png)

## GoogLeNet

特点：  
1. 不使用全连接层，而是用平均池化代替全连接层，减小模型的参数数量,这种想法来自于NIN。  
2. 采用一种高效的机器视觉深度神经网络结构，称为"Inception",这种模块化结构方便增加与修改，现在inception版本到了V6/V7。GoogLeNet中采用了9个inception模块。  
3. 为了避免梯度小时，网络额外增加了2个辅助的softmax用于向前传导梯度。

GoogLeNet中的Inception  
![](/assets/GoogLeNetInception.png)  
GoogLeNet的参数 :可以看出里面用7x7的平均池代替了全连接。  
后续改进的版本：  
1. Inception-v2在之前的版本中主要加入了batch Normalization；另外也借鉴VGGNet的思想，用两个3x3的卷积代替5x5的卷积，不仅降低了训练参数，也提升了速度。  
2. Inception-3在v2的基础上进一步分解大的卷积，比如把nxn的卷积拆分成两个一维卷积：1xn,nx1。  
3. Inception-V4借鉴了ResNet可以构建更深层网络的思想，设计了一个更深更优化的模型。  
![](/assets/GoogLeNetParameters.png)

## Residual NN

#### Residual NN提出来的背景：

随着网络变深，训练误差与测试误差得提高了。这是违反我们的训练的初衷的，因为即使我们把26层后面的网络变成恒等映射，效果也不会变差。  
![](/assets/RNN_HeKaiming_result1.png)  
存在这种随着网络层数增加，会出现如下两个问题：  
1.梯度消失或者爆炸，导致训练难以收敛。这个问题可以通过norimalized initialization 和intermediate normalization layers解决。  
2.随着深度增加，模型的训练误差与测试误差会迅速下滑，这不是overfit造成的。这种现象在CIFAR-10和ImageNet中都有提及。

##### Residual-NN的实现

[参考He Kaiming的这篇文章](https://arxiv.org/pdf/1603.05027v2.pdf)  
Residual Block的设计如下：  
![](/assets/ResidualNNStructure.png)  
对于每一个Residual Units：  
&emsp;&emsp;$$ y_l = h(x_l) + F(x_l,W_l)$$  
&emsp;&emsp;$$ x_{l+1}= f(y_l)$$  
其中函数h一般取恒等映射$$h(x_l) = x_l$$，实验发现f取恒等映射能实现最快的误差下降与最低的训练误差；f是激活函数，取ReLU。F的残差函数。

一个推荐的网络结构：  
![](/assets/Residual_Proposed_structure.png)  
如果激活函数f取恒等映射$$y_l = f(y_l)$$，则有:  
&emsp;&emsp;$$ x_{l+1}= x_l + F(x_l,W_l)$$  
&emsp;&emsp;$$x_{L}= x_l + \displaystyle \sum_{i=l}^{L-1}F(x_i,W_i)$$  
因此对于误差反向传播：  
&emsp;&emsp;$$\frac{\partial \epsilon}{\partial x_l} = \frac{\partial \epsilon}{\partial x_L}\frac{\partial x_L}{\partial x_l} = \frac{\partial \epsilon}{\partial x_L}(1+\frac{\partial }{\partial x_l}\displaystyle \sum_{i=l}^{L-1}F(x_i,W_i))$$  
因为$$\frac{\partial }{\partial x_l}\displaystyle \sum_{i=l}^{L-1}F(x_i,W_i)$$不会常等于-1,因此梯度不会消失，即使当权重非常小的时候。  
因此信号对于正向与反向传播，可以直接的从一个单元传到另外一个单元。条件就是skip connection 函数h,激活函数f是恒等映射。函数h是恒等映射时保证梯度不消失或者爆炸的关键。   
他们使用的mini-batch是128，用了2GPUs,权重衰减是0.0001，动量是0.9，权重初始化了。详细的可以看上面给的论文链接。权重每30个epoch变成原来的十分之一。

##### Residual NN模型效果：

![](/assets/ResiNN_HeKaiming_Result2.png)  
Resi-NN能解决以往随着模型加深训练与测试误差变大的现象。与其它网络的结果比较。  
![](/assets/ResiNN_ResultsCompare.png)

#### 模型的改进（Simons）

是否可以通过逐渐加深网络来实现浅层的网络而具有强大的功能。具体步骤就是：  
1. 一个浅层的网络进行end-end的训练，训练到一定程度的时候，进行第二步  
2. 沿用第一步的权重，通过以Residual Block来微调网络，减小误差，优化方法是SGD，但是我们要保证，每增加一层网络，总的模型的效果会更好。  
3. 循环第二步，直到结果符合我们期望的为止\(误差到noise层\)  
理论上，这类似于机器学习中的Adaboost，是否可以分析它的误差会指数衰减？希望能像ML算法一样，能有数学理论来分析深度学习。通过理论指导，像搭积木一样来构建深度神经网络。  
这种方式与现在的逐层训练有啥区别吗？  

## Dense Net

DenseNet的示意图，主要表现实任意两层间可以有short connection。  
在ResNets中，只在相邻两层有skip connection.在激活函数是恒等函数的前提下，有：  
  $$x_l = H_l(x_{l-1}) + x_{l-1}$$  
对于Dense Net,l层可以与0，1，...,l-1中任意多层相连。因此有：  
  $$x_l = H_l(x_0,x_1,...,x_{l-1})$$  
DenseNet的一个优点是网络更窄，参数更少，大一部分原因是得益于这种dense block的设计，后面有提到在dense block中每个卷积层的输出feature map数量都很小\(小于100\)，而不像其他网络一样动不动就是几百上千的宽度。同样这种连接方式使得特征和梯度的传递更加有效，网络也更容易训练。前面提到过梯度消失问题是网络深度越深的时候越容易出现，原因就是输入信息和梯度信息在很多层之间传递导致的，而现在这种dense connection相当于每一层都直接连接input和loss,因此就可以减轻梯度消失现象，这样更深网络不是问题。  
Dense net主要通过建立不同层之间的直接连续，充分利用了feature，进一步减轻了梯度消失问题，加深了网络深度，而且训练效果非常好。另外利用bottlenech layer,translation layer以及较小的growth rate使得网络变窄，参数减小，有效抑制了过拟合，同时减小了计算量。  
![](/assets/DenseNet-Structure.png)  
Dense Blocks之间通过pooling与convolution来改变图像尺寸。

![](/assets/DenseBlocksWithPooling.png)

    

## 问题集

1. 为什么1x1的卷积核可以用来降维？  

   1、降维（ dimension reductionality ）。比如，一张500 _ 500且厚度depth为100 的图片在20个filter上做1_1的卷积，那么结果的大小为500_500_20。
   2、加入非线性。卷积层之后经过激励层，1\*1的卷积在前一层的学习表示上添加了非线性激励（ non-linear activation ），提升网络的表达能力。  

[参考](https://zhuanlan.zhihu.com/p/32486381)

