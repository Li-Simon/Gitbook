# 线性搜索与Armijo准则

符号约定：  
$$\kern{4 em} g_k: \nabla f(x_k)$$,即目标函数关于k次迭代值$$x_k$$的导数  
$$\kern{4 em} G_k: G(x_k) = \nabla ^2f(x_k)$$,即Hassian矩阵  
$$\kern{4 em} d_k: $$第k次迭代的步长因子，在最速下降算法中，有$$d_k = -g_k$$  
$$\kern{4 em} \alpha_k$$:第k次迭代的步长因子，有$$x_{k+1} = x_k + \alpha_k d_k$$  
在精确线性搜索中，步长因子$$\alpha _k$$由下面的因子确定：  
$$\kern{4 em} \alpha _k = arg min _{\alpha} f(x_k + \alpha d_k)$$  
而对于非精确线性搜索，选取的$$\alpha _k$$只要使得目标函数f得到可接受的下降量，即：  
$$\kern{4 em} \Delta f(x_k) = f(x_k) - f(x_k + \alpha _k d_k)$$  
Armijo 准则用于非精确线性搜索中步长因子$$\alpha$$的确定，内容如下：  
Armijo 准则：  
已知当前位置$$x_k$$和优化方向$$d_k$$，参数$$\beta \in (0,1), \delta \in (0,0.5)$$.令步长因子$$\kern{4 em} \alpha _k = \beta ^{m_k}$$,其中$$m_k$$为满足下列不等式的最小非负整数m:  
$$\kern{4 em} f(x_k + \beta ^m d_k) \leq f(x_k) + \delta \beta ^m g_k^Td_k$$  
由此确定下一个位置$$x_{k+1} = x_k + \alpha _k d_k$$  
对于梯度上升，上面的方程变成：  
$$\kern{4 em} f(x_k - \beta ^m d_k) \geq f(x_k) - \delta \beta ^m g_k^Td_k$$  
由此确定下一个位置$$x_{k+1} = x_k - \alpha _k d_k$$

# Qusi-Netwon methods

# BFGS

我们知道，在牛顿法中，我们需要求解二阶导数矩阵--Hassian阵，当变量很多时，求解Hassian阵势比较费时间的，Qusi-Netwon法主要是在构造Hassian阵上下功夫，它是通过构造一个近似的Hassian阵，或者Hassian阵的逆，而不是解析求解或者利用差分法来求解这个Hassian阵。构造的Hassian阵通过迭代而改变。  
比较出名的Qusi-Netwon方法有BFGS\(以Charles George Broyden, Roger Fletcher, Donald Goldfarb and David Shanno命名\)  
在牛顿法中，k步搜寻步长与方向是$$p_k$$，满足下面方程  
$$\kern{4 em} B_kp_k = -\nabla f(x_k)$$  
$$\kern{4 em} B_k$$就是近似的Hassian 阵。下面我们讨论$$B_k$$如何变化，  
我们要求$$B_k$$的更新满足quasi-Netwon条件  
$$\kern{4 em} B_{k+1}(x_{k+1} - x_k) = \nabla f(x_{K+1} - \nabla f(x_{K})$$  
这个条件就是简单的求$$f(x)$$的二阶导数。  
令：  
$$\kern{4 em} y_k = \nabla f(x_{k+1}) - \nabla f(x_{k})$$， $$s_k = x_{k+1} - x_k$$, 因此$$\kern{4 em} B_{k+1}$$满足$$B_{k+1}s_k = y_k$$  
这就是割线方程（the secant equation）, The curvature condition $$s_k^Ty_k > 0$$需要满足。  
k步的Hassian阵以如下方式更新，  
$$\kern{4 em} B_{k+1} = B_k + U_k + V_k$$  
为了保持$$B_{k+1}$$的正定性以及对称性。$$B_{k+1}$$可以取如下形式：  
$$\kern{4 em} B_{k+1} = B_k + \alpha uu^T + \beta vv^T$$  
选择$$u = y_k$$,$$v=B_ks_k$$,为了满足割线方程（the secant condition），我们得到：  
$$\kern{4 em} \alpha = \frac{1}{y_k^Ts_k}$$  
$$\kern{4 em} \beta = \frac{1}{s_k^TB_ks_k}$$  
最终我们得到Hassian阵的更新方程：  
$$\kern{4 em} B_{k+1} = B_{k} + \frac{y_ky_k^T}{y_k^Ts_k} - \frac{B_ks_ks_k^TB_k^T}{s_k^TB_ks_k}$$

利用 Sherman–Morrison formula，  
$$\kern{4 em} (A + uv^T)^{-1} = A^{-1} - \frac{A^{-1}uv^TA^{-1}}{1+v^TA^{-1}u}$$  
其中A是可逆方阵，$$1+v^TA^{-1}u \neq 0$$  
可以方便的得到$$B_{k+1}$$的逆。  
$$\kern{4 em} B_{k+1}^{-1} = (I - \frac{s_ky_k^T}{y_k^Ts_k})B_k^{-1}(1-\frac{y_ks_k^T}{y_k^Ts_k}) + \frac{s_ks_k^T}{y_k^Ts_k}$$  
$$\kern{4 em} B_{k+1}^{-1} = B_{k}^{-1} + \frac{(s_k^Ty_k + y_k^TB_k^{-1}y_k)(s_ks_k^T)}{(s_k^Ty_k)^2} - \frac{B_k^{-1}y_ks_k^T + s_ky_k^TB_k^{-1}}{s_k^Ty_k}$$

# DFP

[参考](https://blog.csdn.net/golden1314521/article/details/46225289\#2线搜索技术和armijo准则)
DFP的矫正公式如下：  
$$\kern{4 em} H_{k+1} = H_{k} + \frac{H_ky_ky_k^TH_k}{y_k^TH_ky_k} +\frac{s_ks_k^T}{s_k^Ty_k}$$  
当采用精确线搜索时，矩阵序列$$H_k$$的正定新条件$$s^T_ky_k>0$$可以被满足。但对于Armijo搜索准则来说，不能满足这一条件，需要做如下修正：  
$$\kern{4 em} H_{k+1} = H_{k}  \quad s_{k}^Ty_{k} \leq 0 $$  
$$\kern{4 em} H_{k+1} = H_{k} + \frac{H_{k}y_{k}y{_k}^TH_{k}}{y\_k^TH\_ky\_k} \quad s_{k}^Ty_{k}>0$$

#Broyden族算法
之前BFGS和DFP矫正都是由$$y_k$$和$$B_ks_k$$(或者$$s_k$$和$$H_ky_k$$组成的秩2矩阵。而Droyden族算法采用了BFGS和DFP校正公式的凸组合，如下：
$$\kern{4 em} H_{k+1}^{\phi} = \phi _{k}H_{k+1}^{BFGS} + (1-\phi _{k})H_{k+1}^{DFP}
= H_k - \frac{H_ky_ky_k^TH_k}{y_k^TH_ky_k} +\frac{s_ks_k^T}{s_k^Ty_k} + \phi _{k} v_{k}v_{k}^T$$
其中$$\phi _{k} \in [0,1]$$，$$v_k$$由下式定义：
$$\kern{4 em} v_{k} = \sqrt{y_{k}^TH_ky_k}(\frac{s_k}{y_k^Ts_k} - \frac{H_ky_k}{y_k^TH_ky_k})$$

