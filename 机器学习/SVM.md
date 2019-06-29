# SVM

## 线性可分二分类问题

一组数据$$(x_i, y_i), i=1,2...N, y_i \in {+1, -1}, x_i \in R^m$$  
SVM算法是为了求得一个分割超平面$$\mathbf{wx} + b = 0$$ 使得所有的样本点到超平面的几何距离都不小于$$\gamma$$,且这个$$\gamma$$是最大的。  
首先我们定义几何距离和函数距离：  
几何距离：  $$\gamma_i = y_i(\frac{\mathbf{wx_i}}{||\mathbf{w}||} + \frac{b}{||\mathbf{w}||})$$  
除以$$||w||$$是因为x,b同时乘以一个因子，超平面不变。  
![](/assets/SVM_Support_Vector.png)

函数间距：$$\gamma_i = y_i(\mathbf{wx_i} + b)$$  
我们要使: $$\gamma_i \ge \gamma$$. 对任何的样本点i都成立， 并求得$$\gamma$$的最大值。 故上面的问题可以用如下数学来刻画：  
&emsp;&emsp;$$\displaystyle \max_{\mathbf{w, b}} \gamma$$  
&emsp;&emsp;s.t.&emsp;$$ y_i(\frac{\mathbf{wx_i}}{||\mathbf{w}||} + \frac{b}{||\mathbf{w}||}) \ge \gamma$$  
转化为函数间隔：  
&emsp;&emsp;$$\displaystyle max_{\mathbf{w, b}} \gamma$$  
&emsp;&emsp;s.t.&emsp;$$y_i(\mathbf{wx_i} + b) \ge ||w||\gamma = \hat \gamma$$  
为了简化计算， 我们取$$\hat \gamma = 1$$  
因此问题转化为：  
&emsp;&emsp;s.t.&emsp;$$\displaystyle \max_{\mathbf{w, b}} \frac{1}{||w||}$$  
&emsp;&emsp;s.t.&emsp;$$ y_i(\mathbf{wx_i} + b) \ge 1, i = 1,2...,N$$  
转化为求极小问题：  
&emsp;&emsp;$$\displaystyle \min_{\mathbf{w, b}} \frac{1}{2}||w||^2$$  
&emsp;&emsp;s.t.&emsp;$$y_i(\mathbf{wx_i} + b) \ge 1, i = 1,2...,N$$  
问题转化成带约束的优化问题（在这里是凸优化问题）。带等式的约束问题可以通过引入拉格朗日乘子求解，带不等式约束的问题可以引入KKT乘子求解。下面一节我们讨论带约束的凸优化问题。

### 线性不可分与软间隔最大化

&emsp;&emsp;$$\displaystyle \min_{\mathbf{w, b}} \frac{1}{2}||w||^2 + C\displaystyle \sum_{i=1}^N \xi_i $$  
&emsp;&emsp;s.t.&emsp;$$y_i(\mathbf{wx_i} + b) \ge 1 - \xi_i$$, i = 1,2...,N  
&emsp;&emsp;$$ \xi_i \ge 0, i = 1,2...,N$$

通过构造拉格朗日函数求对偶函数。原问题的解是$$(w^*,\xi^*,b^*)$$,对偶问题的解是$$\mathbf{\alpha^*}$$。

参考文献：

1. July · pluskid， 支持向量机通俗导论： [https://raw.githubusercontent.com/liuzheng712/Intro2SVM/master/Intro2SVM.pdf](https://raw.githubusercontent.com/liuzheng712/Intro2SVM/master/Intro2SVM.pdf)



