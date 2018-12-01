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



[^1]: 《线性与非线性规划》David G. Luenberger

