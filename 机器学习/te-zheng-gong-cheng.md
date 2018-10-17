# 特征工程

## 特征工程是什么

有这么一句话在业界广泛流传：数据和特征决定了机器学习的上限，而模型和算法只是逼近这个上限而已。那特征工程到底是什么呢？顾名思义，其本质是一项工程活动，目的是最大限度地从原始数据中提取特征以供算法和模型使用。通过总结和归纳，人们认为特征工程包括以下方面：

## 特征选择方式

参考知乎上[这篇文章](https://www.zhihu.com/question/28641663)  
特征选择与特征提取是特征工程中的两大核心问题。特征选择是指选择获得相应模型和算法最好性能的特征集，工程上常用的方法如下：  
1. 计算每一个特征与相应变量的相关性。一般是算皮尔逊系数和互信息系数。皮尔逊系数只能衡量线性相关性，互信息系数能够很好地度量各种相关性，但是计算相对复杂，很多toolkit里面包含了这个工具（如sklearn的MINI）,得到相关性之后就可以排序选择特征了。  
2. 构建单个特征的模型，通过模型的准确性为特征排序，借此来选择特征。  
3. 通过L1正则项来选择特征，L1正则方法具有稀疏解的特性，因此天然具备特征选择的特性。  
4. 训练能够对特征打分的预选模型：RF和LR等都对模型的特征打分，通过打分获得相关性后再训练最终模型。  
5. 通过特征组合后再来选择特征：如对用户ID和用户特征的组合来获得较大的特征集再来选择特征，这种做法在推荐系统和广告系统中比较常见，这也是所谓亿级甚至十亿集特征的主要来源，原因是用户数据比较稀疏，特征组合能同时兼顾全局模型和个性化模型。  
6. 通过深度学习来进行特征选择/目前这种手段

总体而言，有两种方法：  
基于方差的方法（PCA），基于相关性方法。  
1. 相关性：一般用皮尔逊相关系数来定义。  
2. 方差法：去掉值变化不大的特征，因为可以把这些特征看成常数值，他们对分类或者回归结果影响不大。

### 特征选择

1. Filter方法：自变量与目标变量之间的关联
   1. Pearson相关系数
   2. 卡方检测
   3. 信息增益，互信息\(MIC\)
2. Wrapper方法：通过目标函数来决定是否加入一个变量
   1. 迭代：产生特征子集，评价
   2. 完全搜索
   3. 启发式搜索
   4. 随机搜索（GA，SA）​
3. Embedded方法:学习器自身自动选择特征
   1. 正则化L1，L2
   2. 决策树（熵-信息增益，基尼系数）
   3. 深度学习​

#### Filter

##### Pearson相关系数

Pearson相关系数\(取值在\[-1,1\]之间，大于0是正相关，小于0是负相关，等于0就没有相关性。只对具有线性相关性的变量有效，不能处理具有非线性关系的两组变量\)

##### 互信息\(MIC\)

$$\kern{4 em}MIC:I(X,Y)=\sum_{y \in Y}\sum_{x \in X}p(x,y)\log(\frac{p(x,y)}{p(x)p(y)})$$  
对于线性与非线性关系的数据都实用。

##### 距离相关系数（Distance Correlation）

为了克服Pearson相关系数只对具有线性关系的变量起作用而引入。  
样本：$$(X_k,Y_k),k=1,2,...,n$$  
定义距离矩阵：  
$$\kern{4 em} a_{j,k} = ||\mathbf{X_j} - \mathbf{X_k}||,\kern{2 em}j,k=1,2,...,n$$  
$$\kern{4 em} b_{j,k} = ||\mathbf{Y_j} - \mathbf{Y_k}||,\kern{2 em}j,k=1,2,...,n$$  
$$||*||$$是欧氏距离。取所有的双中心距离。  
$$\kern{4 em}\mathbf{A_{j,k}} := a_{j,k} - \hat a_{j.}- \hat a_{.k} + \hat a_{..}$$  
$$\kern{4 em}\mathbf{B_{j,k}} := b_{j,k} - \hat b_{j.}- \hat b_{.k} + \hat b_{..}$$  
$$\hat a_{j.}$$是j-th row的平均，$$\hat a_{.k}$$是k-th column的平均，$$\hat a_{..}$$是全局平均。  
定义The squared sample distance covariance：  
$$\kern{4 em} dCov^2_n(X,Y) := \frac{1}{n^2}\displaystyle \sum_{j=1}^n\displaystyle \sum_{k=1}^nA_{jk}B_{jk}$$  
虽然MIC与距离相关系数能处理具有线性与非线性关系的变量之间的相关性，但是Pearson还是不可替代的，第一，Pearson系数计算速度快；第二，相对于其它两种取值在\[0,1\],Pearson取值\[-1,1\],正负表关系的正负，绝对值表示强度。前提就是两个变量是线性相关的。

### 特征工程小结

* 特征工程：利用数据领域的相关知识来创建能够使机器学习算法达到最佳性能的特征的过程。
* 特征构建：是原始数据中人工的构建新的特征。
* 特征提取：自动地构建新的特征，将原始特征转换为一组具有明显物理意义或者统计意义或核的特征。  
* 特征选择：从特征集合中挑选一组最具统计意义的特征子集，从而达到降维的效果。  
  重要性排名：特征构建&gt;特征提取&gt;特征选择

## ML框架[^1]

[参考](http://blog.kaggle.com/2016/07/21/approaching-almost-any-machine-learning-problem-abhishek-thakur/)  
![](/assets/ML_Framework.png)

## 特征工程

![](/assets/FeatureProject.png)

## 模型的超参数调节

![](/assets/ML_hyperparameter_selection.png)

## NLP 特征工程

![](/assets/NLP_Feature_Project.png)  
特征工程可以参考[这篇文章](机器学习算法工程师速查表大全)

```
http://blog.kaggle.com/2016/07/21/approaching-almost-any-machine-learning-problem-abhishek-thakur/
```

## Feature extraction and engineering

机器学习的本质是数据加算法，算法就是数学函数，方程与优化。
###标准的机器学习pipeline  

![](/assets/Machine_Learning_pipeline.png)

## Feature scaling

## Feature selection



