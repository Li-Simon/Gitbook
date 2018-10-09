# 深度学习在晶圆检测中的应用研究

要从这个项目中深挖出整个深度学习，也就是从这个项目中涉及到CNN，RNN,DNN.以及训练技巧以及ML。图像处理与信号处理。也就是要体现出深度与广度。三段经历代表深度学习，编程，最优化\(机器学习\)三大领域，要会发现亮点，也就是自己的特色。注意深度，附带是广度。  

## 项目
通过深度学习来提升光刻模型的性能。

### 背景
随着半导体工艺中，芯片中的尺寸越来越小，光学衍射效应越来越明显，单纯的几何光学（初中物理老师告诉你，光是直线传播的，这其实说的是，光是粒子，但光通过狭窄的缝隙会发生衍射效应，这时，光不是直线传播的了）以及不适用，要考虑光的衍射效应。光通过Musk就相当于一次傅里叶变化，从时域变到了频率域。再通过棱镜，又相当于一次傅里叶变换，从频率域变到时域。但棱镜的尺寸有限，因此只接收了低频波，因此，用图像处理的话来说，棱镜的作用就是一个低通滤波器。去掉了高频部分，因此投影到wafer（晶圆）上的图案不再菱角分明，而是在边界处会比较圆滑。

如果没有一些傅里叶光学的背景，你们听起来会比较费劲，但是如果你们有图像处理的背景的话，就记住把Musk上的图案刻蚀到晶圆上就是经历了两次傅里叶变换再加一个低通滤波器。

光通过单缝后，其频谱是连续的，但是经过周期性（结构）缝，其频谱就是离散的，如果为了节约棱镜的开支，就只能取很低的频谱。

光学建模是个逆问题（逆问题的例子，就是CT，通过收集到的信号来反推身体的内部结构）。（怎么把逆问题与深度学习，机器学习联系起来？），再通俗点，它实际上和机器学习，深度学习要处理的问题是一样的，就是求解一个模型，就是train一个model。正向过程就是你已经训练好了一个模型（取啥例子？），然后输入一张图，看它的分类是啥，这很容易，难得是，我有一堆分类好的图片，让你训练一个model。逆问题就是一个优化问题，因此就涉及到一些优化算法，这时候考点就来了？有哪些优化算法，总结下，有两种，线性搜索方法（linear search）以及 trust region。但是对于这个求逆问题而言，是很复杂的，直接离散的话，参数基本在10的15次方以上，总之，这个求逆问题是很难的，即使求出来，也不会很准。因此，我们有两个研究的方向。直接通过光学图像（也就是将要刻蚀在wafer上的电路板）来反求印刷这张图像的模板（Musk），其实这个光刻就像拍照片，拍的物体（比如风景）就是Musk,wafer就相当于胶卷，wafer上的图像就相当于风景在胶卷上的投缘。

第一个方向是，直接通过光学图像（也就是将要刻蚀在wafer上的电路板）来反求印刷这张图像的模板（Musk），我们的模型就是卷积网络，因为多层网络可以用来近似任何一个函数（通用近似定理 \(Universal approximation theorem，一译万能逼近定理\)」指的是：如果一个前馈神经网络具有线性输出层和至少一层隐藏层，只要给予网络足够数量的神经元，便可以实现以足够高精度来逼近任意一个在 Rn 的紧子集 \(Compact subset\) 上的连续函数。只要神经元足够多，再加一个激活函数），当然可以用来近似这个求逆过程。但是这条路风险很大，因此，我们有了第二条研究的路径，就是修正原有的物理模型，使得它更powerful，也就是说，我们任然需要建立物理model，来进行求逆过程，得到一个物理的model，只是，这个model不是足够强大，会有一些缺陷，因此，我们想通过一个CNN来修正这个model,来让我们的模型更有效。这就是大致的背景。背景讲清楚了，我们就该讲我们是怎么做的了。

搭建GPU环境，装显卡驱动（显卡驱动，蓝屏），cuda，cudnn，但是发现不能使用apt-get install东西，重装了很多次系统，装了不同的ubuntu系统，从12.04到16.04的五个不同版本，折腾了一周。（因此因为公司的IP保护，无线网卡解决问题）
我们一开始做了些尝试，用了CNN，VGG，遇到的问题（图像预处理，亚像素的偏离），数据集不够，因为真实数据都是机密（IP），不可以轻易拿到。自己去切割图像，通过有经验的人工来做分类。再通过翻转这些操作来增加数据集。此外，数据集也是很讲究的，你得保证同一数据集中的物理参数，焦距，偏振方向都是一致的，焦距不同，得到的图像模糊程度不同。
很长一段时间，我们都在用用记忆卷积，反卷积的深度神经网络，都市没有发现很好的效果。后来使用了pre-trained model,因为我们的数据量少（30000张图），但是经过CNN处理过的图像，并不比没有处理额图像好，这就尴尬了，因此，我们一直加深网络。

### 目的

### 工具

### 图像预处理

### 数据集

图像大小：48\*48,  
数据集：一共31400张图片，训练集90%,一共28260张图，测试集10%,一共3140张图  
batch size大小5.  
一个epcoh\(训练完28260张图\)的时间是600s,即10分钟左右。

```py
#batch_size =5
#learn_rate = 0.0001
net = tflearn.input_data(shape=[None, 48, 48, 1])
net = tflearn.conv_2d(net, 64, 1)
net = tflearn.residual_block(net, 2, 64)
net = tflearn.conv_2d(net, 64, 1)
net = tflearn.residual_block(net, 3, 64)
net = tflearn.conv_2d(net, 64, 1)
net = tflearn.residual_block(net, 2, 64)
net = tflearn.conv_2d(net, 64, 1)
net = tflearn.residual_block(net, 1, 64)
net = tflearn.conv_2d(net, 1, 1)
Training Step: 1000  | total loss: 6.56844 | time: 118.655s
| Adam | epoch: 001 | loss: 6.56844 - acc: 0.7033 | val_loss: 8.57394 - val_acc: 0.6723 -- iter: 05000/28260
--
Training Step: 2000  | total loss: 6.26063 | time: 234.816s
| Adam | epoch: 001 | loss: 6.26063 - acc: 0.6907 | val_loss: 8.11802 - val_acc: 0.6762 -- iter: 10000/28260
--
Training Step: 3000  | total loss: 5.61156 | time: 351.264s
| Adam | epoch: 001 | loss: 5.61156 - acc: 0.7085 | val_loss: 7.88475 - val_acc: 0.6794 -- iter: 15000/28260
--
Training Step: 4000  | total loss: 6.61628 | time: 469.786s
| Adam | epoch: 001 | loss: 6.61628 - acc: 0.7000 | val_loss: 9.18316 - val_acc: 0.6804 -- iter: 20000/28260
--
Training Step: 5000  | total loss: 5.81782 | time: 586.015s
| Adam | epoch: 001 | loss: 5.81782 - acc: 0.6987 | val_loss: 7.58499 - val_acc: 0.6852 -- iter: 25000/28260
--
Training Step: 6000  | total loss: 5.99239 | time: 50.356ss
| Adam | epoch: 002 | loss: 5.99239 - acc: 0.7008 | val_loss: 6.78956 - val_acc: 0.6852 -- iter: 01740/28260
```

### 网络选择

从一开始的VGG到

```py
#batch_size =5
#learn_rate = 0.0001
net = tflearn.input_data(shape=[None, 48, 48, 1])
net = tflearn.conv_2d(net, 64, 1)
net = tflearn.residual_block(net, 2, 64)
net = tflearn.residual_block(net, 1, 64)
net = tflearn.conv_2d(net, 64, 1)
net = tflearn.residual_block(net, 1, 64)
net = tflearn.residual_block(net, 2, 64)
net = tflearn.conv_2d(net, 1, 1)
Training Step: 1000  | total loss: 6.41052 | time: 88.615s
```

### 效果

通过我们的ResidualNN,我们能很大的降低我们模型得到的图像与实际拍摄到的图像之间的差别，也就是在Max2x2。\(RMS怎么定义忘记了？\)  
![](/assets/ResidualNN_result_figure.png)  
原因是，我们输入的图像已经很接近输出的图像，因此，我们只需要训练残差就可以了。

## 图像与信号处理

## Residual NN
#### Residual NN提出来的背景：

随着网络变深，训练误差与测试误差得提高了。这是违反我们的训练的初衷的，因为即使我们把26层后面的网络变成恒等映射，效果也不会变差。  
![](/assets/RNN_HeKaiming_result1.png)  
存在这种随着网络层数增加，会出现如下两个问题：  
1.梯度消失或者爆炸，导致训练难以收敛。这个问题可以通过norimalized initialization 和intermediate normalization layers解决。  
2.随着深度增加，模型的训练误差与测试误差会迅速下滑，这不是overfit造成的。这种现象在CIFAR-10和ImageNet中都有提及。

##### Residual-NN的实现
Residual Block的设计如下：
![](/assets/ResidualNNStructure.png) 
##### Residual NN模型效果：

![](/assets/ResiNN_HeKaiming_Result2.png)  
Resi-NN能解决以往随着模型加深训练与测试误差变大的现象。

#### 模型的改进（Simons）

是否可以通过逐渐加深网络来实现浅层的网络而具有强大的功能。具体步骤就是：  
1. 一个浅层的网络进行end-end的训练，训练到一定程度的时候，进行第二步  
2. 沿用第一步的权重，通过以Residual Block来微调网络，减小误差，优化方法是SGD，但是我们要保证，每增加一层网络，总的模型的效果会更好。  
3. 循环第二步，直到结果符合我们期望的为止\(误差到noise层\)  
理论上，这类似于机器学习中的Adaboost，是否可以分析它的误差会指数衰减？希望能像ML算法一样，能有数学理论来分析深度学习。通过理论指导，像搭积木一样来构建深度神经网络。

## 三大神经网络

### CNN

### RNN

#### LSTM

### DNN

## 自编码

## 强化学习



