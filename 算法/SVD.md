# SVD

利用LU分解，我们可以求满秩的线性方程组的解。对于mxn（m&gt;n）阶矩阵，对于超定方程（方程数目大于未知数的个数），因为一般没有解满足$$Ax=b$$,这就是最小二乘法发挥作用的地方。  
这个问题的解就是使得： $$||Ax-b||_{2}^{2}$$值极小的解，通过求导（把x-&gt;x+e，求梯度等于0的x）,可以得到解为：$$x = (X^{T}A)^{-1}A^{T}b$$

# QR分解

定理：设A是mxn阶矩阵，m&gt;=n,假设A为满秩的，则存在一个唯一的正交矩阵$$Q (Q^{T}Q=I)$$和唯一的具有正对角元$$r_{ij}>0$$的nxn阶上三角阵$$R$$使得 $$A=QR$$.

**Gram-Schmidt正交化**

Gram-Schmidt正交化的基本想法，是利用投影原理在已有基的基础上构造一个新的正交基。

$$((\beta ))_{1}$$

[http://elsenaju.eu/Calculator/QR-decomposition.htm](http://elsenaju.eu/Calculator/QR-decomposition.htm)

[https://rosettacode.org/wiki/QR\_decomposition](https://rosettacode.org/wiki/QR_decomposition)

[https://www.wikiwand.com/en/QR\_decomposition\#/Example\_2](https://www.wikiwand.com/en/QR_decomposition#/Example_2)

[https://www.wikiwand.com/en/Householder\_transformation](https://www.wikiwand.com/en/Householder_transformation)

C\#有开源的免费的代数库mathnet.numerics,功能也比较多，推荐通过Nuget来安装这个库

# Nuget 安装dll

Tools--&gt;Nuget Package Manager--&gt;Manager Nuget packages for solution..--&gt;Browse

[https://numerics.mathdotnet.com/api/MathNet.Numerics.LinearAlgebra/Matrix\`1.htm\#QR](https://numerics.mathdotnet.com/api/MathNet.Numerics.LinearAlgebra/Matrix`1.htm#QR)

[https://numerics.mathdotnet.com/matrix.html](https://numerics.mathdotnet.com/matrix.html)

![](/assets/import5-SVD-1.png)

研究这个

![](/assets/import5-SVD-2.png)

