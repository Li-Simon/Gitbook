#拟牛顿法

###拟牛顿法的历史
拟牛顿法是求解非线性优化问题最有效的方法之一，于20世纪50年代由美国Argonne国家实验室的物理学家W.C.Davidon所提出来。Davidon设计的这种算法在当时看来是非线性优化领域最具创造性的发明之一。不久R. Fletcher和M. J. D. Powell证实了这种新的算法远比其他方法快速和可靠，使得非线性优化这门学科在一夜之间突飞猛进。

拟牛顿法的本质思想是改善牛顿法每次需要求解复杂的Hessian矩阵的逆矩阵的缺陷，它使用正定矩阵来近似Hessian矩阵的逆，从而简化了运算的复杂度。拟牛顿法和最速下降法一样只要求每一步迭代时知道目标函数的梯度。通过测量梯度的变化，构造一个目标函数的模型使之足以产生超线性收敛性。这类方法大大优于最速下降法，尤其对于困难的问题。另外，因为拟牛顿法不需要二阶导数的信息，所以有时比牛顿法更为有效。如今，优化软件中包含了大量的拟牛顿算法用来解决无约束，约束，和大规模的优化问题。  
　　具体步骤：  
　　拟牛顿法的基本思想如下。首先构造目标函数在当前迭代$$x_k$$的二次模型：  
&emsp;&emsp;$$ m_k(p) = f(x_k) + \bigtriangledown f(x_k)^Tp + \frac{p^TB_{k}p}{2}$$  
&emsp;&emsp;$$p_k = - B^{-1}_{k}\bigtriangledown f(x_k)$$  
这里$$B_k$$是一个对称正定矩阵，于是我们取这个二次模型的最优解作为搜索方向，并且得到新的迭代点：  
&emsp;&emsp;$$ x_{k+1} = x_{k} + \alpha_kp_k$$  
其中我们要求步长$$\alpha_k$$满足Wolfe条件。这样的迭代与牛顿法类似，区别就在于用近似的Hesse矩阵$$B_k$$ 代替真实的Hesse矩阵。所以拟牛顿法最关键的地方就是每一步迭代中矩阵Bk 的更新。现在假设得到一个新的迭代$$x_k+1$$，并得到一个新的二次模型：

这个公式被称为割线方程。常用的拟牛顿法有DFP算法和BFGS算法。  
[最优化方法：牛顿迭代法和拟牛顿迭代法](https://blog.csdn.net/pipisorry/article/details/24574293)


## Qusi-Netwon methods

### BFGS

我们知道，在牛顿法中，我们需要求解二阶导数矩阵--Hassian阵，当变量很多时，求解Hassian阵势比较费时间的，Qusi-Netwon法主要是在构造Hassian阵上下功夫，它是通过构造一个近似的Hassian阵，或者Hassian阵的逆，而不是解析求解或者利用差分法来求解这个Hassian阵。构造的Hassian阵通过迭代而改变。  
比较出名的Qusi-Netwon方法有BFGS\(以Charles George Broyden, Roger Fletcher, Donald Goldfarb and David Shanno命名\)  
在牛顿法中，k步搜寻步长与方向是$$p_k$$，满足下面方程  
&emsp;&emsp;$$ B_kp_k = -\nabla f(x_k)$$  
&emsp;&emsp;$$ B_k$$就是近似的Hassian 阵。下面我们讨论$$B_k$$如何变化，  
我们要求$$B_k$$的更新满足quasi-Netwon条件  
&emsp;&emsp;$$ B_{k+1}(x_{k+1} - x_k) = \nabla f(x_{K+1}) - \nabla f(x_{K})$$  
这个条件就是简单的求$$f(x)$$的二阶导数。  
令：  
&emsp;&emsp;$$ y_k = \nabla f(x_{k+1}) - \nabla f(x_{k})$$， $$s_k = x_{k+1} - x_k$$, 因此&emsp;&emsp;$$B_{k+1}$$满足$$B_{k+1}s_k = y_k$$  
这就是割线方程（the secant equation）, The curvature condition $$s_k^Ty_k > 0$$需要满足。  
k步的Hassian阵以如下方式更新，  
&emsp;&emsp;$$ B_{k+1} = B_k + U_k + V_k$$  
为了保持$$B_{k+1}$$的正定性以及对称性。$$B_{k+1}$$可以取如下形式：  
&emsp;&emsp;$$ B_{k+1} = B_k + \alpha uu^T + \beta vv^T$$  
选择$$u = y_k$$,$$v=B_ks_k$$,为了满足割线方程（the secant condition），我们得到：  
&emsp;&emsp;$$ \alpha = \frac{1}{y_k^Ts_k}$$  
&emsp;&emsp;$$ \beta = \frac{1}{s_k^TB_ks_k}$$  
最终我们得到Hassian阵的更新方程：  
&emsp;&emsp;$$ B_{k+1} = B_{k} + \frac{y_ky_k^T}{y_k^Ts_k} - \frac{B_ks_ks_k^TB_k^T}{s_k^TB_ks_k}$$

利用 Sherman–Morrison formula，  
&emsp;&emsp;$$ (A + uv^T)^{-1} = A^{-1} - \frac{A^{-1}uv^TA^{-1}}{1+v^TA^{-1}u}$$  
其中A是可逆方阵，$$1+v^TA^{-1}u \neq 0$$  
可以方便的得到$$B_{k+1}$$的逆。  
&emsp;&emsp;$$ B_{k+1}^{-1} = (I - \frac{s_ky_k^T}{y_k^Ts_k})B_k^{-1}(1-\frac{y_ks_k^T}{y_k^Ts_k}) + \frac{s_ks_k^T}{y_k^Ts_k}$$  
&emsp;&emsp;$$B_{k+1}^{-1} = B_{k}^{-1} + \frac{(s_k^Ty_k + y_k^TB_k^{-1}y_k)(s_ks_k^T)}{(s_k^Ty_k)^2} - \frac{B_k^{-1}y_ks_k^T + s_ky_k^TB_k^{-1}}{s_k^Ty_k}$$

# DFP

[参考](https://blog.csdn.net/golden1314521/article/details/46225289\#2线搜索技术和armijo准则)
DFP的矫正公式如下：  
&emsp;&emsp;$$ H_{k+1} = H_{k} + \frac{H_ky_ky_k^TH_k}{y_k^TH_ky_k} +\frac{s_ks_k^T}{s_k^Ty_k}$$  
当采用精确线搜索时，矩阵序列$$H_k$$的正定新条件$$s^T_ky_k>0$$可以被满足。但对于Armijo搜索准则来说，不能满足这一条件，需要做如下修正：  
&emsp;&emsp;$$ H_{k+1} = H_{k}  \quad s_{k}^Ty_{k} \leq 0 $$  
&emsp;&emsp;$$H_{k+1} = H_{k} + \frac{H_{k}y_{k}y{_k}^TH_{k}}{y\_k^TH\_ky\_k} \quad s_{k}^Ty_{k}>0$$

#Broyden族算法
之前BFGS和DFP矫正都是由$$y_k$$和$$B_ks_k$$(或者$$s_k$$和$$H_ky_k$$组成的秩2矩阵。而Droyden族算法采用了BFGS和DFP校正公式的凸组合，如下：   
&emsp;&emsp;$$ H_{k+1}^{\phi} = \phi _{k}H_{k+1}^{BFGS} + (1-\phi _{k})H_{k+1}^{DFP}$$   
&emsp;&emsp;&emsp;&emsp;$$= H_k - \frac{H_ky_ky_k^TH_k}{y_k^TH_ky_k} +\frac{s_ks_k^T}{s_k^Ty_k} + \phi _{k} v_{k}v_{k}^T$$      
其中$$\phi _{k} \in [0,1]$$，$$v_k$$由下式定义：      
&emsp;&emsp;$$ v_{k} = \sqrt{y_{k}^TH_ky_k}(\frac{s_k}{y_k^Ts_k} - \frac{H_ky_k}{y_k^TH_ky_k})$$

