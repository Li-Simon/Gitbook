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
从D中随机选取k个样本点作为中心，($$\mathbf{u_1,u_2,...,u_k}$$)  
repeat:
$$\kern 2 em$$令$$C_i = 0, (1 \le i \le k)$$
$$\kern 2 em$$for j=1,2,...,m,do
$$\kern 4 em$$ 样本点$$\mathbf{x_j}$$到与各均值$$\mathbf{u_i}$$的距离
$$\kern 4 em$$ $$d_{ij} = ||\mathbf{x_j}-\mathbf{u_i}||_2$$    
$$\kern 4 em$$根据距离确定样本点j所属于的类:$$\lambda_j = \arg \min d_{ji}$$ 
$$\kern 4 em$$将$$\mathbf{x_j}$$划入所属的类$$C_{\lambda_j} =C_{\lambda_j}U(\mathbf{u_i})$$
$$\kern 4 em$$






















