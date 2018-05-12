# 第一节 Kriging插值

[https://xg1990.com/blog/archives/222](https://xg1990.com/blog/archives/222)  
空间插值问题，就是在已知空间上若干离散点 $$(x_i,y_i)$$的某一属性\(如气温，海拔\)的观测值$$z_i = z(x_i,y_i)$$的条件下，估计空间上任意一点$$(x,y)$$的属性值的问题。  
直观来讲，根据地理学第一定律，

All attribute values on a geographic surface are related to each other, but closer values are more strongly related than are more distant ones.  
大意就是，地理属性有空间相关性，相近的事物会更相似。由此人们发明了反距离插值，对于空间上任意一点$$(x,y)$$ 的属性$$z = z ( x , y )$$ ，  
定义反距离插值公式估计量 $$\hat{z} = \sum^{n}_{i=0}{\frac{1}{d^\alpha}z_i}$$  
其中$$α$$通常取1或者2。

即，用空间上所有已知点的数据加权求和来估计未知点的值，权重取决于距离的倒数（或者倒数的平方）。

那么，距离近的点，权重就大；距离远的点，权重就小。 反距离插值可以有效的基于地理学第一定律估计属性值空间分布，但仍然存在很多问题：  
$$α$$的值不确定 用倒数函数来描述空间关联程度不够准确

因此更加准确的克里金插值方法被提出来了

克里金插值公式$$\hat{z_o} = \sum^{n}_{i=0}{\lambda_iz_i}$$  
其中$$\hat{z_0}$$是点$$(x_o,y_o)$$处的估计值， 即：$$z_o=z(x_o,y_o)$$  
假设条件:  
1. 无偏约束条件 $$E(\hat{z_0} - z_0) = 0$$  
2. 优化目标/代价函数 $$J = Var((\hat{z_0} - z_0))$$取极小值  
3. 半方差函数$$r_{ij}$$与空间距离$$d_{ij}$$存在关联,并且这个关联可以通过这这两组数拟合出来，因此可以用距离$$d_{ij}$$来求得$$r_{ij}$$

半方差函数$$r_{ij} = \sigma^2 - C_{ij}$$;   等价于$$r_{ij} = \frac{1}{2}E[(z_i-z_j)^2]$$  
求得$$r_{ij}$$之后，我们就可以求得$$\lambda_i$$  

