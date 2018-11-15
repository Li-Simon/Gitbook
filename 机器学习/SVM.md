* [ ] # SVM

## 线性可分二分类问题

一组数据$$(x_i, y_i), i=1,2...N, y_i \in {+1, -1}, x_i \in R^m$$  
SVM算法是为了求得一个分割超平面$$\mathbf{wx} + b = 0$$ 使得所有的样本点到超平面的几何距离都不小于$$\gamma$$,且这个$$\gamma$$是最大的。  
首先我们定义几何距离和函数距离：  
几何距离：  $$\gamma_i = y_i(\frac{\mathbf{wx_i}}{||\mathbf{w}||} + \frac{b}{||\mathbf{w}||})$$  
除以$$||w||$$是因为x,b同时乘以一个因子，超平面不变。  
![](/assets/SVM_Support_Vector.png)

函数间距：$$\gamma_i = y_i(\mathbf{wx_i} + b)$$  
我们要使: $$\gamma_i \ge \gamma$$. 对任何的样本点i都成立， 并求得$$\gamma$$的最大值。 故上面的问题可以用如下数学来刻画：  
$$\kern{4 em}\displaystyle \max_{\mathbf{w, b}} \gamma$$  
$$\kern{4 em} s.t. \kern{2 em}y_i(\frac{\mathbf{wx_i}}{||\mathbf{w}||} + \frac{b}{||\mathbf{w}||}) \ge \gamma$$  
转化为函数间隔：  
$$\kern{4 em}\displaystyle max_{\mathbf{w, b}} \gamma$$  
$$\kern{4 em} s.t. \kern{2 em}y_i(\mathbf{wx_i} + b) \ge ||w||\gamma = \hat \gamma$$  
为了简化计算， 我们取$$\hat \gamma = 1$$  
因此问题转化为：  
$$\kern{4 em}\displaystyle \max_{\mathbf{w, b}} \frac{1}{||w||}$$  
$$\kern{4 em} s.t. \kern{2 em}y_i(\mathbf{wx_i} + b) \ge 1, i = 1,2...,N$$  
转化为求极小问题：  
$$\kern{4 em}\displaystyle \min_{\mathbf{w, b}} \frac{1}{2}||w||^2$$  
$$\kern{4 em} s.t. \kern{2 em}y_i(\mathbf{wx_i} + b) \ge 1, i = 1,2...,N$$  
问题转化成带约束的优化问题（在这里是凸优化问题）。带等式的约束问题可以通过引入拉格朗日乘子求解，带不等式约束的问题可以引入KKT乘子求解。下面我们先来讨论下带约束的凸优化问题。





