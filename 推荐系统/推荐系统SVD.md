# SVD在推荐系统的应用

假设我们现在有评分矩阵$$V \in \mathbb{R}^{n \times m}$$,SVD实际上就是去找到两个矩阵：$$U \in \mathbb{R}^{f \times n}$$，$$M \in \mathbb{R}^{f \times m}$$，其中矩阵U表示 User 和 feature 之间的联系，矩阵V表示 Item 和 feature 之间的联系。  
大家这时候肯定会想，我们的评分矩阵里面一般会有很多缺失值，那要怎么去得到 U 和 M 呢？实际上，这两个矩阵是通过学习的方式得到的，而不是直接做矩阵分解。我们定义如下的损失函数：  
  $$E = \frac{1}{2}\sum_{i=1}^{n}\sum_{j=1}^{m}I_{ij}(V_{ij} - p(U_i,M_j))^2+\frac{k_u}{2}\sum_{i=1}^{n}\lVert U_i \rVert^2 + \frac{k_m}{2}\sum_{j=1}^{m}\lVert M_j \rVert^2$$  
其中 $$p(U_i,M_j)$$ 表示我们对用户 i 对 物品 j 的评分预测：  
  $$p(U_i,M_j) = U_i^TM_j$$

梯度下降：  
  $$-\frac{\partial E}{\partial U_i} = \sum_{j=1}^{M}I_{ij}((V_{ij}-p(U_i,M_j))M_j) - k_uU_i $$  
  $$-\frac{\partial E}{\partial M_j} = \sum_{i=1}^{n}I_{ij}((V_{ij}-p(U_i,M_j))U_i) - k_mM_j $$

实际上，用户的评分与用户的习惯，以及该物品的总体评分水平有关，因此可以加上用户的均值与物品的均值。  
  $$\hat{r}_{ui} = \mu + b_i + b_u + \mathbf{q}_i^T\mathbf{p}_u $$  
μ： 训练集中所有记录的评分的全局平均数。在不同网站中，因为网站定位和销售的物品不同，网站的整体评分分布也会显示出一些差异。比如有些网站中的用户就是喜欢打高分，而另一些网站的用户就是喜欢打低分。而全局平均数可以表示网站本身对用户评分的影响。  
$$b_u$$： 用户偏置（user bias）项。这一项表示了用户的评分习惯中和物品没有关系的那种因素。比如有些用户就是比较苛刻，对什么东西要求都很高，那么他的评分就会偏低，而有些用户比较宽容，对什么东西都觉得不错，那么他的评分就会偏高。  
$$b_i$$： 物品偏置（item bias）项。这一项表示了物品接受的评分中和用户没有什么关系的因素。比如有些物品本身质量就很高，因此获得的评分相对都比较高，而有些物品本身质量很差，因此获得的评分相对都会比较低。  
这个时候我们的损失函数变为：  
  $$E = \sum_{(u,i)\in \mathcal{k}}(r_{ui}-\mu - b_i - b_u - \mathbf{q}_i^T\mathbf{p}_u) + \lambda (\lVert p_u \rVert_2) + \lVert q_i \rVert_2 + b_u^2 + b_i^2) $$

## SVD与神经网络实现

SVD实现维数约化，以及SVD与神经网络的实现。SVD与非线性维数约化，SVD与离群点检测。

### 非负矩阵分解

![](/assets/NMF.png)

###张量分解
Tucker分解可以用于张量分解，不止是有矩阵分解，还有张量分解，那么本征值怎么推广到张量？张量分解有什么用?  



[^1] [SVD在推荐系统中的应用](http://charleshm.github.io/2016/03/SVD-Recommendation-System/)

