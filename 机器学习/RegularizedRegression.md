# 线性系统的Regularized Regression

这里讨论的还是线性系统，也就是预测函数：  
&emsp;&emsp;$$f(\mathbf{x}) = \beta_0 + \displaystyle \sum_{j=1}^px_{j}\beta_j$$  
然后通过最小二乘求解数据的模型。通过加正则项来约束模型的复杂度或者参数范围。对于非线性模型，只是把模型$$f(\mathbf{x})$$换成你想要的非线性函数即可，比如N元M次多项式，选最简单的就是N元二次方程，这是最简单的非线性模型。  
物理学中有一些很有意思的非线性回归模型，比如光的衍射成像，光通过特定结构的衍射，反射成像，求解这些模型，第一步是建model,也就是通过求解Maxwell方程，得到非线性方程组，第二步就是通过实验数据来求解模型中的参数，这些参数有两类，一类书几何参数，也就是设计到要处理问题的几何结构；第二类是物理参数，主要是描述系统材料属性的参数，比如折射率，反射率，光的波长等。  
一个典型的非线性回归例子就是深度学习，神经网络就是一个高度非线性的函数，非线性是由激活函数决定的，也就是激活函数是非线性函数。 通过这个非线性函数，可以把输入的数据映射到输出的数据空间；高度的非线性是神经网络具有强大的非线性拟合能力的根本。神经网络的表达能力由下面的定理给出。

#### 万能近似定理

万能近似定理（universal approximation theorem）\(Hornik et al., 1989;Cybenko, 1989\) 表明，一个前馈神经网络如果具有线性输出层和至少一层具有任何一种‘‘挤压’’ 性质的激活函数（例如logistic sigmoid激活函数）的隐藏层，只要给予网络足够数量的隐藏单元，它可以以任意的精度来近似任何从一个有限维空间到另一个有限维空间的Borel 可测函数。 

正则化的目的是减少test误差而不是training误差，这是要明白的。  

## Ridge回归，Shrink与SVD

&emsp;&emsp;$$\hat \beta ^{ridge} =  \arg min_{\beta}{\displaystyle \sum_{i=1}^N(y_i -\beta_0-\displaystyle \sum_{j=1}^px_{ij}\beta_j)^2 + \lambda \displaystyle \sum_{j=1}^p\beta_j^2}$$  
等价于:  
&emsp;&emsp;$$\hat \beta ^{ridge} =  \arg min_{\beta}{\displaystyle \sum_{i=1}^N(y_i -\beta_0-\displaystyle \sum_{j=1}^px_{ij}\beta_j)^2} $$  
&emsp;&emsp;s.t. &emsp; $$ \displaystyle \sum_{j=1}^p\beta_j^2 \le t$$.  
上面的问题也等价于假定，$$y_i,\beta_i$$服从如下分布：  
&emsp;&emsp;$$ y_i \in N(\beta_0 + x_i^T\beta,\sigma^2)$$  
&emsp;&emsp;$$\beta_i \in N(0,\tau^2)$$  
其中：$$\lambda = \sigma^2/\tau^2$$  
因此RRS\(Root sum square\)可以写成如下形式：  
&emsp;&emsp;$$RRS(\lambda) =(\mathbf{y} - \mathbf{X\beta})^T(\mathbf{y} - \mathbf{X\beta}) + \lambda \beta^T\beta $$  
通过对$$\beta$$求导并令其为0，可以得到：  
&emsp;&emsp;$$ \hat \beta ^{ridge} = (\mathbf{X}^T\mathbf{X} + \lambda I)^{-1}\mathbf{X}^T\mathbf{y}$$  
为了建立起L2与SVD之间的联系， 我们对X进行SVD分解：  
&emsp;&emsp;$$\mathbf{X} = \mathbf{UDV^T}$$  
我们重写没有正则化的最小二乘拟合：  
&emsp;&emsp;$$ \mathbf{X}\beta^{ls} = (\mathbf{X}^T\mathbf{X} )^{-1}\mathbf{X}^T\mathbf{y} =\mathbf{UU^T}\mathbf{y} $$  
对于L2正则化的最小二乘法：  
&emsp;&emsp; $$\mathbf{X}\beta^{ls} = (\mathbf{X}^T\mathbf{X} + \lambda I)^{-1}\mathbf{X}^T\mathbf{y} =\mathbf{UD}(\mathbf{D^2+\lambda I})^{-1}\mathbf{DU^T}\mathbf{y} $$  
 &emsp;&emsp;&emsp;&emsp;&emsp;$$ = \displaystyle \sum_{j=1}^p \mathbf{u_j}\frac{d_j^2}{d_j^2 + \lambda}\mathbf{u_j}^T\mathbf{y}$$  
 从上面的分式$$\frac{d_j^2}{d_j^2 + \lambda}$$可以知道，对于$$d_j \ll \lambda$$,则相应的方向会收缩到0。可以认为L2就是对数据进行了SVD分解后，只保留了$$d_j \gt \lambda$$的分量。

## Lasso\(L1\)回归

&emsp;&emsp;$$ \hat \beta ^{ridge} =  \arg min_{\beta}{\displaystyle \sum_{i=1}^N(y_i -\beta_0-\displaystyle \sum_{j=1}^px_{ij}\beta_j)^2 + \lambda \displaystyle \sum_{j=1}^p|\beta_j|}$$  
等价于:  
&emsp;&emsp;$$\hat \beta ^{ridge} =  \arg min_{\beta}{\displaystyle \sum_{i=1}^N(y_i -\beta_0-\displaystyle \sum_{j=1}^px_{ij}\beta_j)^2} $$  
&emsp;&emsp;$$ subject to:  \displaystyle \sum_{j=1}^p|\beta_j| \le t$$.  
L1更容易产生稀疏性,因为椭圆与菱形更易在菱形顶点相交，而与圆形不容易在坐标轴上相切。  
![](/assets/L1_L2_regulation.png)

### L1稀疏性的数学解析

一个数学上更严格的解析。。  
上面的问题也等价于假定，$$y_i,\beta_i$$服从如下分布：  
&emsp;&emsp;$$ y_i \in N(\beta_0 + x_i^T\beta,\sigma^2)$$  
&emsp;&emsp;$$ \beta_i \in (1/2\tau)exp(-|\beta|/\tau)$$  
其中： $$\tau = 1/\lambda$$  
因此$$\beta_i$$更容易分布在0的附件，也就是能级排斥（量子混沌里面的概念，L1是可积系统，L2是GOE）  
最小二乘一般通过Cholesky分解（$$p^3+Np^2/2$$）或者QR分解\($$NP^2$$\)来实现，前者一般更快，但是没有后者稳定。

