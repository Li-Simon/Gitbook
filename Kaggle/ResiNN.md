# 深度学习在晶圆检测中的应用研究

要从这个项目中深挖出整个深度学习，也就是从这个项目中涉及到CNN，RNN,DNN.以及训练技巧以及ML。图像处理与信号处理。也就是要体现出深度与广度。三段经历代表深度学习，编程，最优化\(机器学习\)三大领域，要会发现亮点，也就是自己的特色。

## 项目

### 背景

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
####模型的改进（Simons）
是否可以通过逐渐加深网络来实现浅层的网络而具有强大的功能。具体步骤就是：  
1. 一个浅层的网络进行end-end的训练，训练到一定程度的时候，进行第二步
2. 沿用第一步的权重，通过以Residual Block来微调网络，减小误差，优化方法是SGD，但是我们要保证，每增加一层网络，总的模型的效果会更好。  
3. 循环第二步，直到结果符合我们期望的为止(误差到noise层)  
理论上，这类似于机器学习中的Adaboost，是否可以分析它的误差会指数衰减？希望能像ML算法一样，能有数学理论来分析深度学习。通过理论指导，像搭积木一样来构建深度神经网络。
## 三大神经网络

### CNN

### RNN

#### LSTM

### DNN

## 自编码

## 强化学习



 