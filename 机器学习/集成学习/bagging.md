#Bagging
Bagging系列方法的原理图如下：  
![](/assets/Bagging.png)  
Bagging的本质思想是平均一个多noisy（variance大）但是近似无偏的模型，因此可以减少variance。树是bagging理想的候选者，因为他们能抓住数据中复杂的相互作用结构。 在大多数问题中，boosting相对于bagging有压倒性优势，成为更好的选择。  
Boosting通过弱学习者的时间演化，成员投一个带权重的票。  
Regression:&emsp;&emsp;$$ \hat f_{rf}^B(x) = \frac{1}{B}\displaystyle \sum_{b=1}^BT_b(x)$$  
因为从bagging中生成的树是id\(identically distributed\),B颗树的期望与单颗树的期望一样，如果输之间是IID\(independent identically distributed\),每颗树的variance是 $$\sigma^2$$,则B颗树的variance是$$\frac{\sigma^2}{B}$$,假设树之间的关联系数是$$c$$,则B颗树的variance是：  
&emsp;&emsp;$$ c\sigma^2 + \frac{1-c}{B}\sigma^2$$  
如果c=1，就回到iid情况，如果$$c \ne 0$$,则上面的第一项不会随着B增大而减小，只有第二项会随着B增大而减小，因此我们要尽量使得树之间的关联系数c趋于0. 这可以通过随机化来实现，对样本和对特征这两方面随机化。  
问题：怎么构造具有负关联系数的系统？
&emsp;&emsp;$$\hat f_{bag}(x) = \frac{1}{B}\displaystyle \sum_{b=1}^B \hat f^{*}(x)$$  
当B趋于无穷时，上述表达式就是bagging 估计的一个Monte Carlo估计。

#### Random Forest
随机森林的两个随机：  
1. 随机挑选一部分训练样本。  
2. 随机挑选一部分特征。  
这样保证每颗子树尽量是不相关的。因此误差也是不相关的，就可以通过多个模型平均来减小整个模型的误差。    
参数推荐：  
对于分类问题，默认m是$$\sqrt{p}$$,最小的节点数是1.  
对于回归问题，默认的m是p/3，最小的节点尺寸是5.  
OOB:out of box, bagging中有$$(1-\frac{1}{N})^N = 1/e$$的样本没有被选中，可以用来做验证，因此不需要交叉验证。当OOB误差稳定后，训练也就可以结束了。  
####Kernel random forest

