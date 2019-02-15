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

### ![](/assets/backprop_four.png)

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

### 卷积计算

假设I就是输入的图像，$$K \in R^{k_1 \times k_2}$$的卷积核，则卷积如下计算：  
  $$(I \ast K)_{ij} = \sum_{m = 0}^{k_1 - 1} \sum_{n = 0}^{k_2 - 1} I(i-m, j-n)K(m,n)$$  
       $$= \sum_{m = 0}^{k_1 - 1} \sum_{n = 0}^{k_2 - 1} I(i+m, j+n)K(-m,-n)$$  
卷积和Cross-correlation是一样的，当$$K(-m,-n) == K(m,n)$$;  
首先通过数学来描述每一层网络：  
对于图像，我们输入是一个高H，长W和通道C=3的张量，比如图像  
$$I \in \mathbb{R}^{H \times W \times C}$$;对于D个Filters，我们有$$K \in \mathbb{R}^{k_1 \times k_2 \times C \times D}$$,以及偏置$$b \in \mathbb{R}^{D}$$。  
因此通过卷积操作之后的输出是：  
  $$(I \ast K)_{ij} = \sum_{m = 0}^{k_1 - 1} \sum_{n = 0}^{k_2 - 1} \sum_{c = 1}^{C} K_{m,n,c}\cdot I_{i+m, j+n, c} + b$$  
对于灰度图C=1：  
  $$(I \ast K)_{ij} = \sum_{m = 0}^{k_1 - 1} \sum_{n = 0}^{k_2 - 1} K_{m,n} \cdot I_{i+m, j+n} + b$$

### 记号

为了方便我们的计算，我们约定使用如下计算：  
1. l表示低l层，l=1是第一层，l=L是最后一层  
2. 输入的维度是$$H\times W$$，用i,j表示其迭代子  
3. 卷积核w的维度是$$k_1\times k_2$$， m,n是他们的迭代子  
4. $$w_{m,n}^{l}$$是连接第l层神经元与第l-1层之间的权值矩阵，也就是卷积核。  
5. $$b^l$$是第l层的偏置  
6. l层的输入$$x_{i,j}^l$$与第l-1层的输出$$O_{i,j}^{l-1}$$之间关系是：  
  $$x_{i,j}^l = \sum_{m}\sum_{n} w_{m,n}^l o_{i + m,j + n}^{l-1} + b^l$$  
7. $$O_{i,j}^{l-1}$$是l层的输出：  
  $$O_{i,j}^{l-1} = f(x_{i,j}^l)$$  
8. $$f(\cdot)$$是激活函数

#### l层的输入输出

$$x_{i,j}^l = \text{rot}_{180^\circ} \left\{ w_{m,n}^l \right\} \ast o_{i,j}^{l-1} + b_{i,j}^l $$  
  $$  x_{i,j}^l = \sum_{m} \sum_{n} w_{m,n}^l o_{i+m,j+n}^{l-1} + b_{i,j}^l $$  
  $$ o_{i,j}^l = f(x_{i,j}^l) $$

### 误差

神经网络的输出值是$$y_p$$,相应的目标值是$$t_p$$。因此误差是：  
  $$E =  \frac{1}{2}\sum_{p} \left(t_p - y_p \right)^2 $$

### 误差反向

我们所有要计算的参数就是每层卷积核与偏置。  
我们需要通过改变卷积核中的一个矩阵元$$w_{m'n'}$$来观察最终的误差怎么改变，再反过来调节卷积核个的元素大小，最终使得网络输出值与相应的目标值之间的误差极小。  
总的来说，CNN与普通的DNN的求法思想是一样的，CNN特别之处不是对整张图求和。而只是对卷积范围内的区域求和。  
![](/assets/CNN_Conv.png)  
$$H\times W$$的图像经过$$k_1\times k_2$$的卷积核作用之后，得到的图像大小是$$(H-k_1+1) \times (W-k_2 + 1)$$。因此相应的梯度可以由链式法则表示：  
  $$\frac{\partial E}{\partial w_{m^{\prime},n^{\prime}}^l} = \sum_{i=0}^{H-k_1} \sum_{j=0}^{W-k_2} \frac{\partial E}{\partial x_{i,j}^{l}} \frac{\partial x_{i,j}^{l}}{\partial w_{m^{\prime},n^{\prime}}^l}$$  
     $$= \sum_{i=0}^{H-k_1} \sum_{j=0}^{W-k_2} \delta^{l}_{i,j} \frac{\partial x_{i,j}^{l}}{\partial w_{m^{\prime},n^{\prime}}^l}$$  
因为：  
  $$  x_{i,j}^l = \sum_{m} \sum_{n} w_{m,n}^l o_{i+m,j+n}^{l-1} + b_{i,j}^l $$  
代入上式得到：  
  $$\frac{\partial x_{i,j}^{l}}{\partial w_{m^{\prime},n^{\prime}}^l} = \frac{\partial}{\partial w_{m^{\prime},n^{\prime}}^l}\left( \sum_{m} \sum_{n} w_{m,n}^{l}o_{i+m, j+n}^{l-1} + b^l \right) $$  
得到：  
  $$\frac{\partial x_{i,j}^{l}}{\partial w_{m^{\prime},n^{\prime}}^l} = \frac{\partial}{\partial w_{m',n'}^l}\left( w_{0,0}^{l} o_{ i + 0, j + 0}^{l-1} + ... + w_{m',n'}^{l} o_{ i + m^{\prime}, j + n^{\prime}}^{l-1} + ... + b^l\right) $$  
      $$= \frac{\partial}{\partial w_{m^{\prime},n^{\prime}}^l}\left( w_{m^{\prime},n^{\prime}}^{l} o_{ i + m^{\prime}, j + n^{\prime}}^{l-1}\right)$$  
      $$=  o_{i+m^{\prime},j+n^{\prime}}^{l-1} $$  
最终得到误差对卷积核的梯度是：  
  $$\frac{\partial E}{\partial w_{m',n'}^l} = \sum_{i=0}^{H-k_1} \sum_{j=0}^{W-k_2} \delta^{l}_{i,j} o_{ i + m^{\prime}, j + n^{\prime}}^{l-1}$$  
      $$= \text{rot}_{180^\circ} \left\{ \delta^{l}_{i,j} \right\} \ast  o_{m^{\prime},n^{\prime}}^{l-1}$$  
现在我们需要来计算$$\delta^{l}_{i,j}$$:

#### 误差对每输入的导数

$$\delta^{l}_{i,j} = \frac{\partial E}{\partial x_{i,j}^{l}}$$  
可以由链式法则来求，并建立起$$\delta^{l}_{i,j}$$与$$\delta^{l+1}_{i,j}$$之间的关系：  
  $$\frac{\partial E}{\partial x_{i',j'}^{l}} = \sum_{i,j \in Q} \frac{\partial E}{\partial x_{Q}^{l+1}}\frac{\partial x_{Q}^{l+1}}{\partial x_{i',j'}^l}$$  
     $$= \sum_{i,j \in Q} \delta^{l+1}_{Q} \frac{\partial x_{Q}^{l+1}}{\partial x_{i',j'}^l}$$  
只有有限区域Q中的$$\delta^{l+1}_{i,j}$$对$$\delta^{l}_{i,j}$$有影响，Q的大小就是卷积核的大小。  
  $$\frac{\partial E}{\partial x_{i',j'}^{l}} = \sum_{m = 0}^{k_1 -1} \sum_{n = 0}^{k_2 -1} \frac{\partial E}{\partial x_{i'-m, j'-n}^{l+1}}\frac{\partial x_{i'-m, j'-n}^{l+1}}{\partial x_{i',j'}^l} $$  
     $$= \sum_{m = 0}^{k_1 -1} \sum_{n = 0}^{k_2 -1} \delta^{l+1}_{i'-m, j'-n} \frac{\partial x_{i'-m, j'-n}^{l+1}}{\partial x_{i',j'}^l} $$  
再求下面的导数：

#### 相邻两层输入之间的导数

$$\frac{\partial x_{i'-m,j'-n}^{l+1}}{\partial x_{i',j'}^l} = \frac{\partial}{\partial x_{i',j'}^l} \left( \sum_{m'} \sum_{n'} w_{m', n'}^{l+1} o_{i' - m + m',j' - n + n'}^{l} + b^{l+1} \right)$$  
       $$= \frac{\partial}{\partial x_{i',j'}^l}\left( \sum_{m'} \sum_{n'} w_{m',n'}^{l+1}f\left(x_{i' - m + m',j' - n + n'}^{l}\right) + b^{l+1} \right)$$  
得到：  
  $$\frac{\partial x_{i^{\prime} - m,j^{\prime} - n}^{l+1}}{\partial x_{i',j'}^l} = \frac{\partial}{\partial x_{i',j'}^l}\left( w_{m',n'}^{l+1} f\left(x_{ 0 - m + m', 0 - n + n'}^{l}\right) + ... + w_{m,n}^{l+1} f\left(x_{i',j'}^{l}\right) + ... + b^{l+1}\right)$$  
       $$= \frac{\partial}{\partial x_{i',j'}^l}\left( w_{m,n}^{l+1} f\left(x_{i',j'}^{l} \right) \right)$$  
       $$= w_{m,n}^{l+1} \frac{\partial}{\partial x_{i',j'}^l} \left( f\left(x_{i',j'}^{l} \right) \right)$$  
       $$= w_{m,n}^{l+1} f'\left(x_{i',j'}^{l}\right)$$  
最终得到误差对输入的导数：  
  $$\frac{\partial E}{\partial x_{i',j'}^{l}} = \sum_{m = 0}^{k_1 - 1} \sum_{n = 0}^{k_2 - 1} \delta^{l+1}_{i^{\prime} - m,j^{\prime} - n} w_{m,n}^{l+1} f'\left(x_{i',j'}^{l}\right)$$  
     $$= \text{rot}_{180^\circ} \left\{ \sum_{m = 0}^{k_1 - 1} \sum_{n = 0}^{k_2 - 1} \delta^{l+1}_{i^{\prime} + m,j^{\prime} + n} w_{m,n}^{l+1} \right\} f'\left(x_{i',j'}^{l}\right)$$  
     $$= \delta^{l+1}_{i',j'} \ast \text{rot}_{180^\circ} \left\{ w_{m,n}^{l+1} \right\} f'\left(x_{i',j'}^{l} \right)$$

## 贝叶斯网络\(信念网络\)

主要是基于波尔兹曼分布或者说波尔兹曼机的模型，也是一种MRF模型， 能量模型。

