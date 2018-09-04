# FM(Factorization Machines),FFM
##FM
$$\kern{2 em}$$一般的线性模型为：
$$\kern{4 em} y = w_0 + \displaystyle \sum_{i=1}^nw_ix_i$$
一般模型中，各个特征是独立考虑的，没有考虑特征之间的相互关系。 如果考虑特征$$x_i,x_j$$之间的相互关系，模型修改如下：  
$$\kern{4 em} y = w_0 + \displaystyle \sum_{i=1}^nw_ix_i + \displaystyle \sum_{i=1}^n\displaystyle \sum_{j=i+1}^nw_{ij}x_ix_j$$  
$$\kern{2 em}$$如果系统的特征比较多的话，计算复杂度会大大提升。为了降低时间复杂度， 我们引入了辅助向量lantent vector   
$$\kern{4 em}\mathbf{V_i} = [v_{i1},v_{i2},...,v_{ik}]^T$$,模型修改如下：  
$$\kern{4 em} y = w_0 + \displaystyle \sum_{i=1}^nw_ix_i + \displaystyle \sum_{i=1}^n\displaystyle \sum_{j=i+1}^n(V_i,V_j)x_ix_j$$  
以上就是FM模型。k是超参数，一般娶30或者40。时间复杂度是$$O(kn^2)$$,可通过如下方式化简。  
$$\kern{4 em}  \displaystyle \sum_{i=1}^n\displaystyle \sum_{j=i+1}^n(V_i,V_j)x_ix_j$$  
$$\kern{4 em}  =\frac{1}{2}\displaystyle \sum_{i=1}^n\displaystyle \sum_{j=1}^n(V_i,V_j)x_ix_j - \frac{1}{2}\displaystyle \sum_{i=1}^n(V_i,V_i)x_ix_i$$  
$$\kern{4 em}  =\frac{1}{2}\displaystyle \sum_{f=1}^n(\displaystyle \sum_{i=1}^nv_{if}x_i)^2 - \displaystyle \sum_{i=1}^nv_{if}^2x_i^2)$$    
通过对每个特征引入lantent vector$$\mathbf{V_i}$$,并对公式进行化简，可以把时间复杂度降为$$O(kn)$$.


