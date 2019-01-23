#Factorization Machines(FM)
这一节讨论点击率预测原发，常用的CTR预估算法有FM, FFM, DeepFM。  
要明白FM与SVD之间的联系。  
原理就是，每个特征x可以用隐变量来表示，一般隐变量维数为30-40，也就是说，每一个特征可以在一个30-40维的低维空间来表示。因此，可以与Krylov子空间，SVD联系起来。都是需求超大特征空间的低维表示或者低秩分解。  
##FM

一般的线性模型为：  
&emsp;&emsp;$$ y = w_0 + \displaystyle \sum_{i=1}^nw_ix_i$$
一般模型中，各个特征是独立考虑的，没有考虑特征之间的相互关系。 如果考虑特征$$x_i,x_j$$之间的相互关系，模型修改如下：  
&emsp;&emsp;$$ y = w_0 + \displaystyle \sum_{i=1}^nw_ix_i + \displaystyle \sum_{i=1}^n\displaystyle \sum_{j=i+1}^nw_{ij}x_ix_j$$  
如果系统的特征比较多的话，计算复杂度会大大提升。为了降低时间复杂度， 我们引入了辅助向量lantent vector   
&emsp;&emsp;$$\mathbf{V_i} = [v_{i1},v_{i2},...,v_{ik}]^T$$  
&emsp;&emsp;$$ w_i = \displaystyle \sum_{f=1}^kv_{i,f}$$  
&emsp;&emsp;$$ w_{i_1,...,i_{o^*}} = \displaystyle \sum_{f=1}^{k_{o^*}}\prod_{j=1}^{o^*}v_{i_j,f}$$  
,辅助变量是描述变量之间的相关性。 模型修改如下：  
&emsp;&emsp;$$y = w_0 + \displaystyle \sum_{i=1}^nw_ix_i + \displaystyle \sum_{i=1}^n\displaystyle \sum_{j=i+1}^n(V_i,V_j)x_ix_j$$  
以上就是FM模型。k是超参数，一般娶30或者40。时间复杂度是$$O(kn^2)$$,可通过如下方式化简。  
&emsp;&emsp;$$ \displaystyle \sum_{i=1}^n\displaystyle \sum_{j=i+1}^n(V_i,V_j)x_ix_j$$  
&emsp;&emsp;$$ =\frac{1}{2}\displaystyle \sum_{i=1}^n\displaystyle \sum_{j=1}^n(V_i,V_j)x_ix_j - \frac{1}{2}\displaystyle \sum_{i=1}^n(V_i,V_i)x_ix_i$$  
&emsp;&emsp;$$  =\frac{1}{2}\displaystyle \sum_{f=1}^k(\displaystyle \sum_{i=1}^nv_{if}x_i)^2 - \displaystyle \sum_{i=1}^nv_{if}^2x_i^2)$$    
通过对每个特征引入lantent vector$$\mathbf{V_i}$$,并对公式进行化简，可以把时间复杂度降为$$O(kn)$$.    
##Field-aware Factorization Machines(FFM)


