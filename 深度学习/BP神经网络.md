# 自己动手写神经网络

这里需要实现NN，CNN,RNN，区别在于是否加卷积。对于NN，要保证层数不说限制，每层的神经元不受限制，只处理一维输入,输出也就一维,也就是分类问题；CNN处理二维输入\(图像\)，设计卷积和卷积核，实现的例子就是LeNet-5。RNN就是实现最简单的RNN。三者通用的东西是什么？可以提出来，我们需要用到哪些模块？这个心里是要清楚的。

## DNN

首先讨论普通的DNN  
![](/assets/BP_CNN1.png)

$$n_l$$是层神经元数目；  
$$W^{(l)} \in R^{n_l \times n_{l-1}}$$是第l-1层到第l层的的权重矩阵。  
$$W^{(l)}_{ij}$$表示第l-1层的j神经元到l层的i神经元之间的权重。  
$$f()$$是激活函数。  
$$\mathbf{b^{(l)}}=[b^{(l)}_1,b^{(l)}_2,...,b^{(l)}_{n_l}] \in R^{n_l}$$表示第l-1层到第l层的的偏置。  
$$\mathbf{z^{(l)}}=[z^{(l)}_1,z^{(l)}_2,...,z^{(l)}_{n_l}]\in R^{n_l}$$表示第l层神经元的的状态。  
$$\mathbf{a^{(l)}}=[a^{(l)}_1,a^{(l)}_2,...,a^{(l)}_{n_l}]\in R^{n_l}$$表示第l层神经元的的激活值。

## 信息前向传播

因此我们根据下面的公式计算每层的神经元状态与输出值，计算从第2层到最后一层L。  
  $$\mathbf{z^{(l)}}=\mathbf{W^{(l)}a^{(l-1)} + b^{(l)}}$$  
  $$\mathbf{a^{(l)}}=f(\mathbf{z^{(l)}})$$  
对于第L层，最终输出$$\mathbf{a^{(L)}}$$。信息传播如下：  
  $$\mathbf{x = a^{(1)} \to z^{(2)}\to a^{(2)} \to ...\to a^{(L-1)} \to z^{(L)} \to a^{(L)} = y}$$

## 误差反向传播

训练数据为$$\mathbf{(x^{(1)},y^{(1)}),...,(x^{(N)},y^{(N)})}$$,即N个数据，假设输出是$$n_L$$维的，也就是：  
  $$\mathbf{y^{(i)}}=(y^{(i)}_1,y^{(i)}_2,...,y^{(i)}_{n_L})^T\in R^{n_L \times 1}$$  
对于第i个数据，假设误差是均方误差，$$\mathbf{o^{(i)}}$$是输出。  
  $$E_i = \frac{1}{2} (\mathbf{y^{(i)}-o^{(i)}})^2 = \frac{1}{2} \displaystyle \sum_{k=1}^{n_L}(y_k^{(i)}-o_k^{(i)})^2$$  
因此对总的N个数据。总的误差表示如下：  
  $$E =\frac{1}{N} \displaystyle \sum_{i=1}^{N}E_i$$

## 对输出层权重参数更新

$$\frac{\partial E}{\partial w_{ij}^{(n_L)}} = \frac{\partial E}{\partial z_{i}^{(n_L)}} \frac{\partial z_{i}^{(n_L)}}{\partial w_{ij}^{(n_L)}} = \delta_i^{(n_L)}a_j^{(n_L-1)}$$  
其中：  
  $$\delta_i^{(n_L)} = \frac{\partial E}{\partial z_{i}^{(n_L)}} = -(y_i - a_i^{(n_L)})f'(z_i^{(n_L)})$$  
因此：  
  $$\mathbf{\delta^{(n_L)} = -(y - a^{(n_L)})*f'(z^{(n_L)})}$$  
其中\*表示向量对应元素相乘。

## 对隐含层权重参数的更新

对于隐藏层有：  
  $$\frac{\partial E}{\partial w_{ij}^{(l)}} = \frac{\partial E}{\partial z_{i}^{(l)}} \frac{\partial z_{i}^{(l)}}{\partial w_{ij}^{(l)}} = \delta_i^{(l)}a_j^{(l-1)}$$

$$\delta_i^{(l)} = \frac{\partial E}{\partial z_{i}^{(l)}} =\displaystyle \sum_{j=1}^{n_{l+1}} \frac{\partial E}{\partial z_{j}^{(l+1)}} \frac{\partial z_{j}^{(l+1)}}{\partial z_{i}^{(l)}} =\displaystyle \sum_{j=1}^{n_{l+1}} \delta_j^{(l+1)} \frac{\partial z_{j}^{(l+1)}}{\partial z_{i}^{(l)}} $$  
  $$\frac{\partial z_{j}^{(l+1)}}{\partial z_{i}^{(l)}} = \frac{\partial z_{j}^{(l+1)}}{\partial a_{i}^{(l)}}\frac{\partial a_{i}^{(l)}}{\partial z_{i}^{(l)}} = w_{ji}^{(l+1)}f'(z_{i}^{(l)})$$  
因此有：  
  $$\delta_i^{(l)} = \displaystyle \sum_{j=1}^{n_{l+1}} \delta_j^{(l+1)} w_{ji}^{(l+1)}f'(z_{i}^{(l)}) = (\displaystyle \sum_{j=1}^{n_{l+1}} \delta_j^{(l+1)} w_{ji}^{(l+1)})f'(z_{i}^{(l)})$$  
因此写成矢量想成形式：  
  $$\mathbf{\delta^{(l)} = -((W^{(l+1)})^T\delta^{(l+1)})*f'(z^{(l)})}$$  
因此：  
  $$\frac{\partial E}{\partial w_{ij}^{(l)}} = (\displaystyle \sum_{j=1}^{n_{l+1}} \delta_j^{(l+1)} w_{ji}^{(l+1)})f'(z_{i}^{(l)})a_j^{(l-1)}$$

### 对输出层与隐含偏置求导数

$$\frac{\partial E}{\partial b_{i}^{(l)}} = \frac{\partial E}{\partial z_{i}^{(l)}} \frac{\partial z_{i}^{(l)}}{\partial b_{i}^{(l)}} = \delta_i^{(l)}$$

## BP四个核心公式

整理起来，BP算法有如下四个核心公式：  
  $$\delta_i^{(L)}= -(y_i - a_i^{(L)})f'(z_i^{(L)})$$  
  $$\delta_i^{(l)} = (\displaystyle \sum_{j=1}^{n_{l+1}} \delta_j^{(l+1)} w_{ji}^{(l+1)})f'(z_{i}^{(l)})$$  
  $$\frac{\partial E}{\partial b_{i}^{(l)}} = \delta_i^{(l)}$$  
  $$\frac{\partial E}{\partial w_{ij}^{(l)}} = \delta_i^{(l)}a_j^{(l-1)}$$

### 两个辅助公式

$$\mathbf{z^{(l)}}=\mathbf{W^{(l)}a^{(l-1)} + b^{(l)}}$$  
  $$\mathbf{a^{(l)}}=f(\mathbf{z^{(l)}})$$

## 参数更新

$$W^{(l)} = W^{(l)} - \frac{u}{N}\displaystyle \sum_{i=1}^{N} \frac{\partial E_i}{\partial W^{(l)}}$$  
  $$\mathbf{b^{(l)} = b^{(l)}} - \frac{u}{N}\displaystyle \sum_{i=1}^{N} \frac{\partial E_i}{\partial b^{(l)}}$$

### 代码实现

如下是一个输入两个变量，只含有4个神经元的隐含层以及一个输出变量的网络\(2,4,1\)。

```py
import numpy as np


class BP_network(object):
    def __init__(self):
        self.w2 = np.random.random((4, 2))
        self.w3 = np.random.random((1, 4))
        self.b2 = np.random.random((4, 1))
        self.b3 = np.random.random((1, 1))
        self.a1 = np.zeros((2, 1))
        self.z2 = np.zeros((4, 1))
        self.a2 = np.zeros((4, 1))
        self.z3 = np.zeros((1, 1))
        self.a3 = np.zeros((1, 1))
        self.delta3 = np.zeros((1, 1))
        self.delta2 = np.zeros((4, 1))
        self.batch_size = 100
        self.leak_rate = 0.01
        self.learn_rate = 0.1

    def grad(self, x):
        result = np.zeros(x.shape)
        for n in range(x.shape[0]):
            if x[n] > 0:
                result[n] = 1
            else:
                result[n] = self.leak_rate
        return result

    def activate_function(self, x):
        result = np.zeros(x.shape)
        for n in range(x.shape[0]):
            if x[n] > 0:
                result[n] = x[n]
            else:
                result[n] = self.leak_rate*x[n]
        del x
        return result

    def forward_prop(self,input_data):
        self.a1 = input_data
        self.z2 = np.dot(self.w2, self.a1) + self.b2
        self.a2 = self.activate_function(self.z2)

        self.z3 = np.dot(self.w3, self.a2) + self.b3
        self.a3 = self.activate_function(self.z3)
        return self.a3

    def back_prop(self, out_put, y_target):
        self.delta3 = -(y_target - out_put)*self.grad(self.z3)
        self.delta2 = np.multiply(np.dot(self.w3.T, self.delta3), self.grad(self.z2))
        self.w3 -= self.learn_rate*np.dot(self.delta3, self.a2.T)
        self.b3 -= self.learn_rate*self.delta3
        self.w2 -= self.learn_rate*np.dot(self.delta2, self.a1.T)
        self.b2 -= self.learn_rate*self.delta2

    def train(self, max_epoch, input_data, output_data):
        data_size = len(input_data)
        for epoch_n in range(max_epoch):
            n = np.random.randint(0, input_data.shape[0])
            x = input_data[n, :]
            x = np.reshape(x, (x.shape[0], 1))
            y = output_data[epoch_n%data_size, :]
            output = self.forward_prop(x)
            error = (output[0] - y[0])*(output[0] - y[0])
            print("Iter ", epoch_n, error, n)
            self.back_prop(output, y)


if __name__ == '__main__':
    bp = BP_network()
    # z = x + 2y
    input_data = np.array([[1, 1], [1, 0], [0, 1], [1, 0.5], [1.5, 0.5]])
    output_data = np.array([[3], [1], [2], [2], [2.5]])
    bp.train(100, input_data, output_data)
    result = bp.forward_prop(np.reshape([1, 1], (2, 1)))
    print("predict is ", result)
```

## CNN

现在我们讨论卷积神经网络的误差怎么反向传播，以及参数的梯度怎么计算。主要涉及到的概念就是卷积计算，pooling,步长，边界补齐。  
下图就是一个典型的CNN[^1]。    

![](/assets/CNN_fig.png)  
###卷积计算
假设I就是输入的图像，$$K \in R^{k_1 \times k_2}$$的卷积核，则卷积如下计算：  
&emsp;&emsp;$$\begin{align}
(I \ast K)_{ij} &= \sum_{m = 0}^{k_1 - 1} \sum_{n = 0}^{k_2 - 1} I(i-m, j-n)K(m,n) \\
&= \sum_{m = 0}^{k_1 - 1} \sum_{n = 0}^{k_2 - 1} I(i+m, j+n)K(-m,-n)
\end{align}$$
首先通过描述每一个网络：  


[^1]: https://www.jefkine.com/general/2016/09/05/backpropagation-in-convolutional-neural-networks/

