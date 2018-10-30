## Customer Segmentation

制定简单的方案花不了多少时间，尤其在具有理论基础的前提下。花时间的是怎么用代码去实现你的方案。只有在对语言\(这个工具\)非常熟悉的时候你才能快速的实现你的demo。

### 问题与技术路线

1. 要处理的问题是什么?
   1. 客户分割
2. 要实现什么结果？
   1. 把客户分割成不同的几个类别
3. 数据要怎么处理？
   1. 数据清洗\(去除错误的项目，比如购物数量小于0，无意义的项目，比如用户ID是nan项\)
   2. 以客户的ID作为标识，来对客户进行分类
4. 怎么实现我们的目的？
   1. 通过客户的三个特征\(RFM, Rencency, Frequency, Mometary Value\)，再用K-means进行聚类
   2. Rencency:客户最近多长时间购物过
   3. Frequency:客户购物的频率
   4. Monetary value:客户一共花了多少钱

groupby\("CustomerID"\).sum\(\).reset\_index\(\)的作用就是根据CustomerID进行聚类，再对同一CustomerID的amount进行求和。

```py
customer_monetary_val = cs_df[['CustomerID','amount']].groupby("CustomerID").sum().reset_index()
customer_history_df = customer_history_df.merge(customer_monetary_val, how='outer')
customer_freq = cs_df[['CustomerID','amount']].groupby("CustomerID").count().reset_index()
customer_freq.rename(columns={'amount':'frequency'},inplace=True)
customer_history_df = customer_history_df.merge(customer_freq, how='outer')

print cs_df.shape,'\n',customer_history_df.head(5)
(354345, 11) 
   CustomerID  recency    amount  frequency
0     12346.0    326.0  77183.60          1
1     12747.0      2.0   4196.01        103
2     12748.0      1.0  33719.73       4596
3     12749.0      4.0   4090.88        199
4     12820.0      3.0    942.34         59
```

对数化这是那个指标

```py
from sklearn import preprocessing
customer_history_df['recency_log'] = customer_history_df['recency'].apply(math.log)
customer_history_df['amount_log'] = customer_history_df['amount'].apply(math.log)
customer_history_df['frequency_log'] = customer_history_df['frequency'].apply(math.log)
feature_vector = ['recency_log','amount_log','frequency_log']
X_subset = customer_history_df[feature_vector].as_matrix()
scaler = preprocessing.StandardScaler().fit(X_subset)
X_scaled = scaler.transform(X_subset)
```

要注意，如下两种表达方式是一样的。

```py
recency_log_1 = customer_history_df['recency'].apply(math.log)
recency_log_2 = customer_history_df.recency.apply(math.log)
```

然后做直方图，也就是统计amount\_log在每个值区间的出现的概率。用n,bins，patchs接收返回的数据。

```py
X = customer_history_df.amount_log
n, bins, patchs = plt.hist(X,1000,facecolor='green',alpha = 0.75)
plt.xlabel('Log of Sales Amount')
plt.ylabel('Probality')
plt.title(r'Histogram of Log Transformed Customer Monetary Value')
plt.grid(True)
plt.show()
```

画RFM图，进行聚类。

```py
from mpl_toolkits.mplot3d import Axes3D

fig = plt.figure(figsize=(8,6))
ax = fig.add_subplot(111,projection='3d')

xs = customer_history_df.recency_log
ys = customer_history_df.frequency_log
zs = customer_history_df.amount_log
ax.scatter(xs,ys,zs,s=5)

ax.set_xlabel('Recency')
ax.set_ylabel('Frequency')
ax.set_zlabel('Monetary')
```

用KMeans来进行聚类

```py
from __future__ import print_function

from sklearn.datasets import make_blobs
from sklearn.cluster import KMeans
from sklearn.metrics import silhouette_samples, silhouette_score

import matplotlib.pyplot as plt
import matplotlib.cm as cm
import numpy as np

print(__doc__)

# Generating the sample data from make_blobs
# This particular setting has one distinct cluster and 3 clusters placed close
# together.

X =  X_scaled# For reproducibility
cluster_centers = dict()
#range_n_clusters = [2, 3, 4, 5, 6]
range_n_clusters = [3,5]

for n_clusters in range_n_clusters:
    # Create a subplot with 1 row and 2 columns
    fig, (ax1, ax2) = plt.subplots(1, 2)
    fig.set_size_inches(18, 7)

    # The 1st subplot is the silhouette plot
    # The silhouette coefficient can range from -1, 1 but in this example all
    # lie within [-0.1, 1]
    ax1.set_xlim([-0.1, 1])
    # The (n_clusters+1)*10 is for inserting blank space between silhouette
    # plots of individual clusters, to demarcate them clearly.
    ax1.set_ylim([0, len(X) + (n_clusters + 1) * 10])

    # Initialize the clusterer with n_clusters value and a random generator
    # seed of 10 for reproducibility.
    clusterer = KMeans(n_clusters=n_clusters, random_state=10)
    cluster_labels = clusterer.fit_predict(X)

    # The silhouette_score gives the average value for all the samples.
    # This gives a perspective into the density and separation of the formed
    # clusters
    silhouette_avg = silhouette_score(X, cluster_labels)
    print("For n_clusters =", n_clusters,
          "The average silhouette_score is :", silhouette_avg)

    # Compute the silhouette scores for each sample
    sample_silhouette_values = silhouette_samples(X, cluster_labels)

    y_lower = 10
    for i in range(n_clusters):
        # Aggregate the silhouette scores for samples belonging to
        # cluster i, and sort them
        ith_cluster_silhouette_values = \
            sample_silhouette_values[cluster_labels == i]

        ith_cluster_silhouette_values.sort()

        size_cluster_i = ith_cluster_silhouette_values.shape[0]
        y_upper = y_lower + size_cluster_i

        color = cm.nipy_spectral(float(i) / n_clusters)
        ax1.fill_betweenx(np.arange(y_lower, y_upper),
                          0, ith_cluster_silhouette_values,
                          facecolor=color, edgecolor=color, alpha=0.7)

        # Label the silhouette plots with their cluster numbers at the middle
        ax1.text(-0.05, y_lower + 0.5 * size_cluster_i, str(i))

        # Compute the new y_lower for next plot
        y_lower = y_upper + 10  # 10 for the 0 samples

    ax1.set_title("The silhouette plot for the various clusters.")
    ax1.set_xlabel("The silhouette coefficient values")
    ax1.set_ylabel("Cluster label")

    # The vertical line for average silhouette score of all the values
    ax1.axvline(x=silhouette_avg, color="red", linestyle="--")

    ax1.set_yticks([])  # Clear the yaxis labels / ticks
    ax1.set_xticks([-0.1, 0, 0.2, 0.4, 0.6, 0.8, 1])

    # 2nd Plot showing the actual clusters formed
    feature1 = 1
    feature2 = 2
    colors = cm.nipy_spectral(cluster_labels.astype(float) / n_clusters)
    ax2.scatter(X[:, feature1], X[:, feature2], marker='.', s=30, lw=0, alpha=0.7,
                c=colors, edgecolor='k')

    # Labeling the clusters
    centers = clusterer.cluster_centers_
    # Draw white circles at cluster centers
    ax2.scatter(centers[:, feature1], centers[:, feature2], marker='o',
                c="white", alpha=1, s=200, edgecolor='k')

    for i, c in enumerate(centers):
        ax2.scatter(c[feature1], c[feature2], marker='$%d$' % i, alpha=1,
                    s=50, edgecolor='k')

    ax2.set_title("The visualization of the clustered data.")
    ax2.set_xlabel("Feature space for the 1st feature")
    ax2.set_ylabel("Feature space for the 2nd feature")

    plt.suptitle(("Silhouette analysis for KMeans clustering on sample data "
                  "with n_clusters = %d" % n_clusters),
                 fontsize=14, fontweight='bold')

plt.show()
```
聚类图如下。  
![](/assets/Kmeans_CustomerSegmentation.png)


## Effective Cross Selling

### 问题与技术路线

1. 要处理的问题是什么?
   1. 市场篮分析
2. 要实现什么结果？
   1. 寻找客户潜在的购买模式，来制定销售策略
3. 数据要怎么处理？
   1. 数据清洗\(去除错误的项目，比如购物数量小于0，无意义的项目，比如用户ID是nan项\)
4. 怎么实现我们的目的？
   1. 关联规则挖掘\(Association Rule-Mining\)
   2. FP Growth算法



