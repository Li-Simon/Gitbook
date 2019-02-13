## Residual NN

#### Residual NN提出来的背景：

随着网络变深，训练误差与测试误差得提高了。这是违反我们的训练的初衷的，因为即使我们把36层后面的网络变成恒等映射，效果也不会变差。  
![](/assets/RNN_HeKaiming_result1.png)  
存在这种随着网络层数增加，会出现如下两个问题：  
1.梯度消失或者爆炸，导致训练难以收敛。然而梯度消失/爆炸的问题，很大程度上可以通过标准的初始化和正则化层来基本解决，确保几十层的网络能够收敛（用SGD+反向传播）[^1]。  
2.随着深度增加，模型的训练误差与测试误差会迅速下滑，这样一种退化，并不是过拟合导致的，并且增加更多的层匹配深度模型，会导致更多的训练误差。这种现象在CIFAR-10和ImageNet中都有提及。    


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


[^1]: [译] Deep Residual Learning for Image Recognition (ResNet)  https://www.jianshu.com/p/f71ba99157c7
