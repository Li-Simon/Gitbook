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
from sklearn.cluster import KMeans
from sklearn.metrics import silhouette_samples, silhouette_score
import matplotlib.cm as cm

X = X_scaled

cluster_centers = dict()

for n_clusters in range(3,6,2):
    fig, (ax1, ax2) = plt.subplots(1, 2)
    #ax2 = plt.subplot(111, projection='3d')
    fig.set_size_inches(18, 7)
    ax1.set_xlim([-0.1, 1])
    ax1.set_ylim([0, len(X) + (n_clusters + 1) * 10])

    clusterer = KMeans(n_clusters=n_clusters, random_state=10)
    cluster_labels = clusterer.fit_predict(X)

    silhouette_avg = silhouette_score(X, cluster_labels)
    cluster_centers.update({n_clusters :{
                                        'cluster_center':clusterer.cluster_centers_,
                                        'silhouette_score':silhouette_avg,
                                        'labels':cluster_labels}
                           })

    sample_silhouette_values = silhouette_samples(X, cluster_labels)
    y_lower = 10
    for i in range(n_clusters):
        ith_cluster_silhouette_values = \
            sample_silhouette_values[cluster_labels == i]

        ith_cluster_silhouette_values.sort()

        size_cluster_i = ith_cluster_silhouette_values.shape[0]
        y_upper = y_lower + size_cluster_i

        color = cm.nipy_spectral(float(i) / n_clusters)
        ax1.fill_betweenx(np.arange(y_lower, y_upper),
                          0, ith_cluster_silhouette_values,
                          facecolor=color, edgecolor=color, alpha=0.7)

        ax1.text(-0.05, y_lower + 0.5 * size_cluster_i, str(i))
        y_lower = y_upper + 10  # 10 for the 0 samples

    ax1.set_title("The silhouette plot for the various clusters.")
    ax1.set_xlabel("The silhouette coefficient values")
    ax1.set_ylabel("Cluster label")
    ax1.axvline(x=silhouette_avg, color="red", linestyle="--")
    ax1.set_yticks([])
    ax1.set_xticks([-0.1, 0, 0.2, 0.4, 0.6, 0.8, 1])
    colors = cm.nipy_spectral(cluster_labels.astype(float) / n_clusters)
    feature1 = 1
    feature2 = 2
    ax2.scatter(X[:, feature1], X[:, feature2], marker='.', s=30, lw=0, alpha=0.7,
                c=colors, edgecolor='k')

    centers = clusterer.cluster_centers_
    ax2.scatter(centers[:, feature1], centers[:, feature2], marker='o',
                c="white", alpha=1, s=200, edgecolor='k')
    for i, c in enumerate(centers):
        ax2.scatter(c[feature1], c[feature2], marker='$%d$' % i, alpha=1,
                    s=50, edgecolor='k')
    ax2.set_title("The visualization of the clustered data.")
    ax2.set_xlabel("Feature space for the 1st feature i.e. monetary value")
    ax2.set_ylabel("Feature space for the 2nd feature i.e. frequency")
    plt.suptitle(("Silhouette analysis for KMeans clustering on sample data "
                  "with n_clusters = %d" % n_clusters),
                 fontsize=14, fontweight='bold')
    #plt.show()
```

对于聚类要注意这个指标：silhouette score  
聚类图如下。  
![](/assets/Kmeans_customer_segmentation.png)  
然后对不同的特征画进行分析，画最小值，最大值，25%，中值，75%。  
traces是一个list，通过append来添加元素，把y,name,cls添加到traces里面。  
plotly的使用可以参看[官方教程](https://plot.ly/python/box/), plotly是一个完全开源的项目。  

np.percentile\(y0, cutoff\_quantile\)表示取从小到大，在cutoff\_quantile%处的值，cutoff_quantile为百分位值。  

```py
import plotly as py
import plotly.graph_objs as go
py.offline.init_notebook_mode()

x_data = ['Cluster 1','Cluster 2','Cluster 3','Cluster 4', 'Cluster 5']
cutoff_quantile = 100
field_to_plot = 'recency'

y0 = customer_history_df[customer_history_df['num_cluster5_labels']==0][field_to_plot].values
y0 = y0[y0<np.percentile(y0, cutoff_quantile)]
y1 = customer_history_df[customer_history_df['num_cluster5_labels']==1][field_to_plot].values
y1 = y1[y1<np.percentile(y1, cutoff_quantile)]
y2 = customer_history_df[customer_history_df['num_cluster5_labels']==2][field_to_plot].values
y2 = y2[y2<np.percentile(y2, cutoff_quantile)]
y3 = customer_history_df[customer_history_df['num_cluster5_labels']==3][field_to_plot].values
y3 = y3[y3<np.percentile(y3, cutoff_quantile)]
y4 = customer_history_df[customer_history_df['num_cluster5_labels']==4][field_to_plot].values
y4 = y4[y4<np.percentile(y4, cutoff_quantile)]
y_data = [y0,y1,y2,y3,y4]

colors = ['rgba(93, 164, 214, 0.5)', 'rgba(255, 144, 14, 0.5)', 'rgba(44, 160, 101, 0.5)', 'rgba(255, 65, 54, 0.5)', 'rgba(207, 114, 255, 0.5)', 'rgba(127, 96, 0, 0.5)']
traces = []

for xd, yd, cls in zip(x_data, y_data, colors):
        traces.append(go.Box(
            y=yd,
            name=xd,
            boxpoints=False,
            jitter=0.5,
            whiskerwidth=0.2,
            fillcolor=cls,
            marker=dict(
                size=2,
            ),
            line=dict(width=1),
        ))

layout = go.Layout(
    title='Difference in sales {} from cluster to cluster'.format(field_to_plot),
    yaxis=dict(
        autorange=True,
        showgrid=True,
        zeroline=True,
        dtick=50,
        gridcolor='black',
        gridwidth=0.1,
        zerolinecolor='rgb(255, 255, 255)',
        zerolinewidth=2,
    ),
    margin=dict(
        l=40,
        r=30,
        b=80,
        t=100,
    ),
    paper_bgcolor='white',
    plot_bgcolor='white',
    showlegend=False
)

fig = go.Figure(data=traces, layout=layout)
py.offline.iplot(fig)
```

## ![](/assets/ployly_Customer_Segmentation.png)

## 

## Effective Cross Selling

### 问题与技术路线

1. 要处理的问题是什么?
   1. 市场篮分析
2. 要实现什么结果？
   1. 寻找客户潜在的购买模式，来制定销售策略，增加销售量。
3. 数据要怎么处理？
   1. 数据清洗\(去除错误的项目，比如购物数量小于0，无意义的项目，比如用户ID是nan项\)
4. 怎么实现我们的目的？
   1. 关联规则挖掘\(Association Rule-Mining\)
   2. FP Growth算法
   
###concepts
Itemset：存在的物品组合，比如{A,B,C,...,X}  
Support:特定组合物品组合占所有交易的比列。  
n = number of transactions with beer and diaper;     
N = total transactions;  
&emsp;&emsp;$$supp(beer,diaper) = \frac{n}{N}$$  
Confidence：一种规则的置信度。  
for a rule which statrs{beer->diaper}    
&emsp;&emsp;$$confidence(beer,diaper) = \frac{supp(beer and diaper)}{supp(beer)}$$   
Lift:  the lift of rule {X->Y}  
&emsp;&emsp;$$lift(X->Y) = \frac{supp(X U Y)}{supp(X)*supp(Y)}$$   
Frequent itemset: Frequent itemsets are itemsets whose support is greater than a user defined support threshold.  
