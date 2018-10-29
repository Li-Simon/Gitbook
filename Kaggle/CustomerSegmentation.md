## Customer Segmentation

###问题与技术路线
1. 要处理的问题是什么?
   1. 客户分割
2. 要实现什么结果？
   1. 把客户分割成不同的几个类别
3. 数据要怎么处理？
   1. 数据清洗\(去除错误的项目，比如购物数量小于0，无意义的项目，比如用户ID是nan项\)
4. 怎么实现我们的目的？
   1. 通过构造三个特征\(RFM, Rencency, Frequency, Mometary Value\)，再用K-means进行聚类
   2. Rencency:客户最近多长时间购物过
   3. Frequency:客户购物的频率
   4. Monetary value:客户一共花了多少钱
   
   
## Effective Cross Selling
###问题与技术路线
1. 要处理的问题是什么?
   2. 市场篮分析
2. 要实现什么结果？
   2. 寻找客户潜在的购买模式，来制定销售策略
3. 数据要怎么处理？
   1. 数据清洗\(去除错误的项目，比如购物数量小于0，无意义的项目，比如用户ID是nan项\)
4. 怎么实现我们的目的？
   1. 关联规则挖掘(Association Rule-Mining)
   2. FP Growth算法
