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

groupby\("CustomerID"\).sum\(\).reset\_index\(\)的作用就是根据CustomerID进行聚类，再对同一CustomerID的amount进行求和。

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
然后做直方图，也就是统计amount_log在每个值区间的出现的概率。  
```py
X = customer_history_df.amount_log
n, bins, patchs = plt.hist(X,1000,facecolor='green',alpha = 0.75)
plt.xlabel('Log of Sales Amount')
plt.ylabel('Probality')
plt.title(r'Histogram of Log Transformed Customer Monetary Value')
plt.grid(True)
plt.show()
```

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



