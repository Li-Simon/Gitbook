## ADMM（乘子的交替方向法）[^1]

在分布式计算中，为了减少通讯成本，就需要我们减少求解问题的迭代次数；要降低迭代次数，就必然要求在一个迭代内完成更复杂的计算。因此有了ADMM。  
考虑具有线性约束并且目标函数是两个分开函数之和形式的图最小化模型。  
  $$\min f_1(\mathbf{x^{(1)}})+f_1(\mathbf{x^{(2)}})$$  
  s.t. $$\mathbf{A_1x^{(1)} + A_2x^{(2)} = b}$$  
    $$\mathbf{x^{(1)} \in \Omega_1,x^{(2)} \in \Omega_2}$$  
其中$$A_i \in E^{m\times n_i}$$,{i=1,2},$$b \in E^m, \Omega_i \subset E^{n_i}(i=1,2)$$是闭凸集;且$$f_i:E^{n_i} \to E, i=1,2$$分别是$$\Omega_i$$上的凸函数。因此上面问题的增广拉格朗日函数是：  
  $$l_c(\mathbf{x^{(1)},x^{(2)},\lambda}) = f_1(\mathbf{x^{(1)}}) + f_2(\mathbf{x^{(2)}}) +\mathbf{\lambda^T}(\mathbf{A_1x^{(1)} + A_2x^{(2)} -b})+\frac{c}{2}|\mathbf{A_1x^{(1)} + A_2x^{(2)} -b}|^2$$  
我们假定上面的问题至少有一个最优解。  
相比于乘子方法，ADMM是以另外的规则\(近似\)最小化$$l_c(\mathbf{x^{(1)},x^{(2)},\lambda}) $$  
  $$\mathbf{x_{k+1}^{(1)}}:= \arg \min_{x^{(1)\in \Omega_1}}l_c(\mathbf{x^{(1)},x_k^{(2)},\lambda_k})$$  
  $$\mathbf{x_{k+1}^{(2)}}:= \arg \min_{x^{(2)\in \Omega_2}}l_c(\mathbf{x_{k+1}^{(1)},x^{(2)},\lambda_k})$$  
  $$\mathbf{\lambda_{k+1}}:= \mathbf{\lambda_{k}} + c(A_1x_{k+1}^{(1)} + A_2x_{k+1}^{(2)} -b)$$  
这种思想是每一个更小的最优化问题都能被更有效地解决或者某些情形有接近的形式。

## 例子

ADMM最典型的例子就是加L1或者L2正则化的优化问题；下面以L1正则化为例。

### 用ADMM求解Lasso问题

lasso的拉格朗日形式可以等价表示成：  
  $$\displaystyle \min_{\beta \in R^p,\theta \in R^p}[\frac{1}{2N}||\mathbf{y-X\beta}||^2_2 + \frac{1}{N}\lambda||\theta||_1],  \beta-\theta = 0$$  
相应的增广拉格朗日函数为：  
  $$\displaystyle \min_{\beta \in R^p,\theta \in R^p}[\frac{1}{2N}||\mathbf{y-X\beta}||^2_2 + \frac{1}{N}\lambda||\theta||_1+ \rho||\beta-\theta||_2^2]$$  
对于lasso，ADMM的更新公式为：  
  $$\beta^{t+1} = \mathbf{(X^TX+\rho I)}^{-1}(\mathbf{X^Ty}+\rho \theta^t - u^t)$$  
  $$\theta^{t+1} = S_{\lambda / \rho}(\beta^{t+1} + u^t/\rho)$$  
  $$u^{t+1} =u^t +  \rho(\beta^{t+1} - \theta^{t+1})$$  
对$$\beta$$进行岭回归，对$$\theta$$进行的更新是软阈值，对u采用线性更新。

[^1]: 《线性与非线性规划》David G. Luenberger

