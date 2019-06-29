# 特征工程

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

&emsp;&emsp;$$MIC:I(X,Y)=\sum_{y \in Y}\sum_{x \in X}p(x,y)\log(\frac{p(x,y)}{p(x)p(y)})$$  
对于线性与非线性关系的数据都实用。

##### 距离相关系数（Distance Correlation）

为了克服Pearson相关系数只对具有线性关系的变量起作用而引入。  
样本：$$(X_k,Y_k),k=1,2,...,n$$  
定义距离矩阵：  
&emsp;&emsp;$$ a_{j,k} = ||\mathbf{X_j} - \mathbf{X_k}||,j,k=1,2,...,n$$  
&emsp;&emsp;$$  b_{j,k} = ||\mathbf{Y_j} - \mathbf{Y_k}||,j,k=1,2,...,n$$  
$$||*||$$是欧氏距离。取所有的双中心距离。  
&emsp;&emsp;$$ \mathbf{A_{j,k}} := a_{j,k} - \hat a_{j.}- \hat a_{.k} + \hat a_{..}$$  
&emsp;&emsp;$$ \mathbf{B_{j,k}} := b_{j,k} - \hat b_{j.}- \hat b_{.k} + \hat b_{..}$$  
$$\hat a_{j.}$$是j-th row的平均，$$\hat a_{.k}$$是k-th column的平均，$$\hat a_{..}$$是全局平均。  
定义The squared sample distance covariance：  
&emsp;&emsp;$$  dCov^2_n(X,Y) := \frac{1}{n^2}\displaystyle \sum_{j=1}^n\displaystyle \sum_{k=1}^nA_{jk}B_{jk}$$  
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

机器学习的本质是数据加算法，算法就是数学函数，方程与优化。  
![](/assets/Machine_Learning_pipeline.png)

### Feature extraction and engineering

#### 标准的机器学习pipeline

特征提取，标度，选择的pipeline。  
![](/assets/FeatureEngineerPipeline.png)  
特征提取和特征工程是整个机器学习pipeline中最重要的步骤。  
特征工程就是通过特殊领域的知识与特殊的技能，把数据转化成特征。数据科学家把他们时间的80%花在特征工程上。花在模型搭建与评估上的时间相对的少，但是也是重要的。深度学习\(CNN,RNN,LSTM\)区别于机器学习是其拥有机器学习没有的特征自动提取功能。  
One-Hot编码在类别数据中工作的非常好，但是当类别很多时会造成灾难，此时需要Bin-Counting Scheme.， Feature Hashing Scheme.

#### 文本数据处理

Bag of Words Model.对次进行统计  
Bag of N-Grams Model，对N个连续的词进行统计，比如两个或三个，Bi-Grams, Tri-Grams. 在NLP中，Tri-Grams就已经足够了。  
词袋模型只考虑词的统计特性，但是有些词在所有文本中本身就具有高的频率，因此就有了TF-IDF model\(Term Frequency-Inverse Document Frequency\)  
&emsp;&emsp;$$  tfidf(w,D)=tf(w,D)*idf(w,D)=f(w,D)*\log(\frac{C}{df(w)})$$  
tf-idf\(w,D\)是词w在文本D中TF-IDF分数。tf\(w,D\)表示词w在文档D中的频率，idf\(w,D\)是词w的逆文档频率，C是该语料库中的文本数。TF-IDF模型可以用来做为文本关键词提取。以及文本相似性计算\(一般用余弦相似性\)，因此可以用来做聚类，适用于无监督学习。  
LDA\(Latent Dirichlet Allocation\)作用在TF-IDF矩阵上，分解成document-topic matrix与topic-term matrix。  

![](/assets/TFIDF-LDA.png)
利用LDA把tf-idf矩阵分解成两个主题T1,T2,可以看出0，1，4成一类，2，3，5成一类。  
####图像数据
Canny edge detection算法；from skimage.feature import canny。  
Object Detection:HOG(Histogram of Oriented gradients)  
from skimage.feature import hog

### Feature scaling

### Feature selection

###准确率与召回率
True Positive(TP)：实际是正例并且我们分类成正例的样本数。  
False Positive(FP)：实际是负例但是我们分类成正例的样本数。  
True Negative(FN):实际是负例并且我们分类成也是负例的样本数。  
False Negative(FN):实际是正例但是我们分类成也是负例的样本数。  
####Accuracy
&emsp;&emsp;$$Accuracy = \frac{TP+TN}{TP+FP+TN+FN}$$  
####Precision 
只针对于正样本或者误分为正样本的样本，在不均衡样本中比较有用，比如人群中癌症阳性的比列很小，因此如果预测人群众没有患癌则获得的accuracy很高，但是precision是0,.    
&emsp;&emsp;$$Precision = \frac{TP}{TP+FP}$$  
####Recall
&emsp;&emsp;$$Recall = \frac{TP}{Tp+FN}$$
####F1 Score
&emsp;&emsp;$$F1 Score = \frac{2*Precision*Recall}{Precision+Recall}$$   
###超参数finetune
两种方法：Grid 搜索与随机搜索。  






