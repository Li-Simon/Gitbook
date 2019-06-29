# FM(Factorization Machines),FFM
##FM
&emsp;&emsp;一般的线性模型为：  
&emsp;&emsp;$$ y = w_0 + \displaystyle \sum_{i=1}^nw_ix_i$$
一般模型中，各个特征是独立考虑的，没有考虑特征之间的相互关系。 如果考虑特征$$x_i,x_j$$之间的相互关系，模型修改如下：  
&emsp;&emsp;$$ y = w_0 + \displaystyle \sum_{i=1}^nw_ix_i + \displaystyle \sum_{i=1}^n\displaystyle \sum_{j=i+1}^nw_{ij}x_ix_j$$  
如果系统的特征比较多的话，计算复杂度会大大提升。为了降低时间复杂度， 我们引入了辅助向量lantent vector   
&emsp;&emsp;$$\mathbf{V_i} = [v_{i1},v_{i2},...,v_{ik}]^T$$  
,辅助变量是描述变量之间的相关性。 模型修改如下：  
&emsp;&emsp;$$y = w_0 + \displaystyle \sum_{i=1}^nw_ix_i + \displaystyle \sum_{i=1}^n\displaystyle \sum_{j=i+1}^n(V_i,V_j)x_ix_j$$  
以上就是FM模型。k是超参数，一般娶30或者40。时间复杂度是$$O(kn^2)$$,可通过如下方式化简。  
&emsp;&emsp;$$ \displaystyle \sum_{i=1}^n\displaystyle \sum_{j=i+1}^n(V_i,V_j)x_ix_j$$  
&emsp;&emsp;$$ =\frac{1}{2}\displaystyle \sum_{i=1}^n\displaystyle \sum_{j=1}^n(V_i,V_j)x_ix_j - \frac{1}{2}\displaystyle \sum_{i=1}^n(V_i,V_i)x_ix_i$$  
&emsp;&emsp;$$  =\frac{1}{2}\displaystyle \sum_{f=1}^n(\displaystyle \sum_{i=1}^nv_{if}x_i)^2 - \displaystyle \sum_{i=1}^nv_{if}^2x_i^2)$$    
通过对每个特征引入lantent vector$$\mathbf{V_i}$$,并对公式进行化简，可以把时间复杂度降为$$O(kn)$$.  
##隐语义模型
LFM(Latent factor model):通过隐含特征（Latent Factor）联系用户兴趣和物品.   
LFM通过如下公式计算用户u对物品i的兴趣：  
&emsp;&emsp;$$Preference(u,i)=r_{ui}=p_u^Tq_i = \displaystyle \sum _{k=1}^K p_{u,k}q_{i,k}$$  
公式中$$p_{u,k}$$和$$q_{i,k}$$是模型的参数，其中$$p_{u,k}$$度量了用户u的兴趣和第k个隐类的关系。而$$q_{i,k}$$都凉了第k个隐类和物品i之间的关系。  
$$p_{u,k},q_{i,k}$$通过如下方式求解：  
&emsp;&emsp;$$C=\displaystyle \sum _{(u,i) \in K}(r_{ui} - \hat r_{ui})^2 = \displaystyle \sum _{(u,i) \in K}(r_{ui} - \displaystyle \sum _{k=1}^K p_{u,k}q_{i,k})^2 + \lambda ||p_u||^2 + \lambda ||q_i||^2$$  
[SVD++](https://blog.csdn.net/zhongkejingwang/article/details/43083603)
##指标
1. 准确率
2. 召回率
3. 覆盖率
4. 多样性

##非负矩阵分解
$$N*p$$数据矩阵$$\mathbf{X}$$近似表示为：  
&emsp;&emsp;$$\mathbf{X} \approx \mathbf{WH}$$  
其中:$$\mathbf{W} \in R^{N \times r}, \mathbf{H} \in R^{r \times p},r \le max(N,p)$$,我们假定&emsp;&emsp;$$x_{ij},w_{ik},h_{kj} \ge 0$$.  
矩阵$$\mathbf{W},\mathbf{H}$$通过最大化下面似然函数确定：  
&emsp;&emsp;$$ L(\mathbf{W},\mathbf{H}) = \displaystyle \sum _{i=1}^N\displaystyle \sum _{j=1}^p[x_{ij}\log(\mathbf{W}\mathbf{H})_{ij}-(\mathbf{W}\mathbf{H})_{ij}]$$  
这个从一个$$x_{ij}$$满足均值为$$(\mathbf{W}\mathbf{H})_{ij}$$的泊松分布的模型的似然函数。  
通过梯度下降法可以求解。 



