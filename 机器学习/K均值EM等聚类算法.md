# K均值EM等聚类算法
K-means是一种无监督的学习方法，通过定义距离与分类的数目K，样本归属于哪个类，取决于该样本距离K个类中心的距离，选择距离最小的类作为归属。随机选择K个起始点，通过迭代，最终收敛。其迭代过程就是求如下函数极小的过程。  
$$\kern{4 em} E = \displaystyle \sum_{i=1}^K \displaystyle \sum_{x \in C_i} ||\mathbf{x - u_i}||^2$$  
$$\kern{4 em} \mathbf{u_i} = \frac{1}{|C_i|}\displaystyle \sum_{x \in C_i} \mathbf{x}$$  
###问题
一个主要的问题就是怎么选取类的数目K。
###改进方案
k-means对初始值的设置很敏感，所以有了k-means++、intelligent k-means、genetic k-means。   
k-means对噪声和离群值非常敏感，所以有了k-medoids和k-medians。   
k-means只用于numerical类型数据，不适用于categorical类型数据，所以k-modes。   
k-means不能解决非凸（non-convex）数据，所以有了kernel k-means

###算法流程
输入：样本集D=($$\mathbf{x_1,x_2,...,x_m}$$),聚类数目k.





