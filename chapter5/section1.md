# 第一节 Kriging插值

[https://xg1990.com/blog/archives/222](https://xg1990.com/blog/archives/222)  
学过空间插值的人都知道克里金插值，但是它的变种繁多、公式复杂，还有个半方差函数让人不知所云 本文讲简单介绍基本克里金插值的原理，及其推理过程，全文分为九个部分： 0.引言－从反距离插值说起 1.克里金插值的定义 2.假设条件 3.无偏约束条件 4.优化目标／代价函数 5.代价函数的最优解 6.半方差函数 7.普通克里金与简单克里金 8.小结  
假设条件:

1. 无偏约束条件 $$E(\hat{z_0} - z_0)$$
2. 优化目标/代价函数 $$J = Var((\hat{z_0} - z_0))$$取极小值
3. 空间关联

$$r_{ij} = \sigma^2 - C_{ij}$$
等价于$$r_{ij} = \frac{1}{2}E[(z_i-z_j)^2]$$
$$\begin{bmatrix}r_{11}&r_{12}&\cdots&r_{1n}&1\\ r_{21}&r_{22}&\cdots&r_{2n}&1\\\cdots&\cdots&\cdots&\cdots&\cdots\\r_{n1}&r_{n2}&\cdots&r_{nn}&1\\1&1&\cdots&1&0\end{bmatrix}\begin{bmatrix} \lambda_1\\ \lambda_2\\\cdots\\\lambda_n\\0\end{bmatrix}=\begin{bmatrix} r_{1o}\\ r_{2o}\\\cdots\\r_{no}\\1\end{bmatrix}$$








