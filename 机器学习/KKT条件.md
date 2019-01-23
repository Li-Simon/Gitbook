# Karush-Kuhn-Tucker(KKT)条件
1. 先讨论一般带约束优化问题的数据描述  
2. 然后引入其作用约束与不起作用约束的定义  
3. 再引入正则点的定义  
4. 接下来引入KKT条件
5.针对局部极小问题， 我们考虑优化函数的二阶导数问题。  
一般形式的优化问题:  

&emsp;&emsp;$$minimize f(\mathbf{x})$$  
&emsp;&emsp;s.t. &emsp;$$ \mathbf h(\mathbf{x}) = \mathbf{0}$$   
&emsp;&emsp;s.t. &emsp;$$ \mathbf g(\mathbf{x}) \le \mathbf{0}$$  
其中： $$f: R^n->R, \mathbf{h}: R^n->R^m, m \le n; \mathbf{g}: R^n->R^p;$$  
针对这一问题，引入如下定义：  
定义21.1. 对于一个不等式约束$$g_i(x) \le 0$$，如果在$$x^*$$处，$$g_i(x^*) = 0$$,那么称该不等式约束是$$x^*$$处的起作用约束。如果：$$g_i(x^*) \lt 0$$,那么称该不等式约束是$$x^*$$处的不起作用约束。  
定义21.2. 设$$\mathbf{x^*}$$满足$$\mathbf{h(\mathbf{x^*})} = \mathbf{0}$$,  $$\mathbf{g(\mathbf{x^*})} \le \mathbf{0}$$，设$$J(\mathbf{x^*})$$为起作用不等式约束下标集，  
&emsp;&emsp;$$ J(\mathbf {x^*}) = (j: g_j(\mathbf{x^*})=0)$$  
如果：  $$\bigtriangledown h_i(\mathbf{x^*})$$,$$\bigtriangledown g_j(\mathbf{x^*}), i \le i \le m, j \in J(\mathbf x^*)$$  
是线性无关的， 则称$$\mathbf{x^*}$$是一个正则点。   
KKT条件：某个点是局部技校点所满足的一阶必要条件。  
定理： KKT条件， 设$$f, \mathbf{g}, \mathbf{h} \in C^1$$,设$$\mathbf{x^*}$$是问题$$\mathbf{h} = 0, \mathbf{g} \le 0$$的一个正则点和局部极小点， 那么必然存在$$\lambda ^* \in R^m$$ 和$$u^* \in R^p$$使得以下条件成立：  
&emsp;&emsp;$$\mathbf{u^*} \ge \mathbf{0}$$  
&emsp;&emsp;$$Df(\mathbf{x^*}) + \mathbf{\lambda^*}Dh(\mathbf{x^*}) + \mathbf{u^*}Dg(\mathbf{x^*})  = \mathbf{0^T}$$   
&emsp;&emsp;$$\mathbf{u^{*T}}\mathbf{g(x*)} = 0$$   
$$\mathbf{\lambda^*}$$为拉格朗日乘子向量，$$\mathbf{u^*}$$是iKKT乘子向量，其元素分别成为拉格朗日乘子，KKT乘子。  
####充分条件
上面讲了局部极小的必要条件，这里我们讨论局部极小的充分条件。 然后我们就利用KKT条件去求不等式约束问题。  
二阶充分必要条件;  
定义如下矩阵：  
&emsp;&emsp;$$L(\mathbf{x},\mathbf{\lambda},\mathbf{u}) = F(\mathbf{x}) + \mathbf{\lambda}\mathbf{H}(\mathbf{x})+ \mathbf{u}\mathbf{G}(\mathbf{x})$$  
&emsp;&emsp;$$F(\mathbf{x})$$是f在$$\mathbf{x}$$处的Hassian矩阵；  
&emsp;&emsp;$$\mathbf{\lambda}\mathbf{H}(\mathbf{x}) = \lambda _1H_1(\mathbf{x}) + ... + \lambda _mH_m(\mathbf{x})$$  
&emsp;&emsp;$$\mathbf{u}\mathbf{G}(\mathbf{x}) = u_1G_1(\mathbf{x}) + ... + u_pG_p(\mathbf{x})$$  
其中$$G_k(\mathbf{x})$$是$$g_k$$处的Hassian矩阵。  
起作用约束所定义曲面的切线空间：
&emsp;&emsp;$$T(\mathbf{x^*}) = (y \in R^n: Dh(x^*)y)=0,Dg_j(x^*)y)=0, j \in J(x^*) $$.  
定理： 二阶必要条件：
如果$$\mathbf{x^*}$$是上面讨论的优化问题的极小点，那么存在$$\mathbf{\lambda^*} \in R^m, \mathbf{u^*} \in R^p$$使得：  
&emsp;&emsp;1. $$\mathbf{u^*} \ge 0$$,      
&emsp;&emsp;2. $$Df(\mathbf{x^*}) + \mathbf{\lambda^*}Dh(\mathbf{x^*}) + \mathbf{u^*}Dg(\mathbf{x^*})  = \mathbf{0^T}$$  
&emsp;&emsp;3. $$\mathbf{u^{*T}}\mathbf{g(x*)} = 0$$   
&emsp;&emsp;4.对所有$$\mathbf{y} \in T(\mathbf{x^*}, \mathbf{u^*}), \mathbf{y} \ne 0$$，都有$$\mathbf{y^T}L(\mathbf{x},\mathbf{\lambda},\mathbf{u})\mathbf{y} > 0$$  
定理： 二阶充分条件：  
假设$$f, \mathbf{g}, \mathbf{h} \in C^2, \mathbf{x^*} \in R^n$$是一个可行点， 存在向量$$\mathbf{\lambda^*} \in R^m, \mathbf{u^*} \in R^p$$使得：   
&emsp;&emsp;1. $$\mathbf{u^*} \ge 0$$,   
&emsp;&emsp;2. $$Df(\mathbf{x^*}) + \mathbf{\lambda^*}Dh(\mathbf{x^*}) + \mathbf{u^*}Dg(\mathbf{x^*})  = \mathbf{0^T}$$    
&emsp;&emsp;3. $$\mathbf{u^{*T}}\mathbf{g(x*)} = 0$$     
&emsp;&emsp;4.对所有$$\mathbf{y} \in T(\mathbf{x^*}, \mathbf{u^*}), \mathbf{y} \ne 0$$，都有&emsp;&emsp;$$\mathbf{y^T}L(\mathbf{x},\mathbf{\lambda},\mathbf{u})\mathbf{y} > 0$$   
那么$$\mathbf{x^*}$$是优化问题   
&emsp;&emsp;s.t. &emsp;&emsp;$$\mathbf h(\mathbf{x}) = \mathbf{0}$$   
&emsp;&emsp;s.t. &emsp;&emsp;$$\mathbf g(\mathbf{x}) \le \mathbf{0}$$  
的严格局部极小点，  
&emsp;&emsp;$$T(\mathbf{x^*}) = (y \in R^n: Dh(x^*)y)=0,Dg_j(x^*)y)=0, j \in J(x^*) $$.  
其中： $$J(\mathbf {x^*,\mathbf {u^*}}) = (j: g_j(\mathbf{x^*})=0),\mathbf {u^*} > 0$$ 
##学习的对偶算法
对于求极小问题：  
&emsp;&emsp;$$\displaystyle \min_{\mathbf{w, b}} \frac{1}{2}||w||^2$$  
&emsp;&emsp;s.t.&emsp;&emsp;$$y_i(\mathbf{wx_i} + b) \ge 1, i = 1,2...,N$$  

引入拉格朗日函数，对每个不等式约束引入拉格朗日乘子$$\alpha_i \ge 0, i=1,2,3...,N$$：  
&emsp;&emsp;$$L(w,b,\alpha) = \frac{1}{2}||w||^2 - \displaystyle \sum_{i=1}^N \alpha_iy_i(\mathbf{wx_i} + b) + \displaystyle \sum_{i=1}^N \alpha_i$$   
其中$$\mathbf{\alpha} = (\alpha_1,\alpha_2,...,\alpha_N)^T$$为拉格朗日乘子向量。   
根据拉格朗日对偶性，原始问题的对偶问题是极大极小问题：  
 &emsp;&emsp;$$ \displaystyle \max_{\mathbf{\alpha}}\displaystyle \min_{\mathbf{w,b}}L(\mathbf{w,b,\alpha})$$   
 现对w,b求极小，再对$$\alpha$$求极大。  
 (1)求$$\displaystyle \min_{\mathbf{w,b}}L(\mathbf{w,b,\alpha})$$。对w,b求导并令其为0，得到:  
 &emsp;&emsp;$$\frac{\partial L(w,b,\alpha)}{\partial \mathbf{w}} = \mathbf{w} - \displaystyle \sum_{i=1}^N \alpha_iy_i(\mathbf{x_i}) = 0$$  
 &emsp;&emsp;$$\frac{\partial L(w,b,\alpha)}{\partial \mathbf{b}} = \displaystyle \sum_{i=1}^N \alpha_iy_i = 0$$  
把上面两个式子代入拉格朗日函数，可以得到原始函数的对偶函数，对偶函数只是拉格朗日乘子的函数：  
&emsp;&emsp;$$\displaystyle \min_{\mathbf{w,b}}L(\mathbf{w,b,\alpha}) = -\frac{1}{2}\displaystyle \sum_{i=1}^N\displaystyle \sum_{j=1}^N\alpha_i\alpha_jy_iy_j(\mathbf{x_ix_j}) + \displaystyle \sum_{i=1}^N \alpha_i$$  
(2)求$$\displaystyle \min_{\mathbf{w,b}}L(\mathbf{w,b,\alpha})$$对$$\alpha$$的极大即是对偶问题。  
&emsp;&emsp;$$\displaystyle \max_{\mathbf{\alpha}}-\frac{1}{2}\displaystyle \sum_{i=1}^N\displaystyle \sum_{j=1}^N\alpha_i\alpha_jy_iy_j(\mathbf{x_ix_j}) + \displaystyle \sum_{i=1}^N \alpha_i$$   
&emsp;&emsp;s.t. &emsp;&emsp;$$\sum_{i=1}^N \alpha_iy_i = 0$$   
&emsp;&emsp;&emsp;&emsp;$$\alpha_i \ge 0$$ ,i=1,2,...,N。    
由于原始问题满足KKT条件，所以存在$$w^*,\alpha^*$$使得$$w^*$$是原始问题的解，$$\alpha^*$$是对偶问题的解。  
####定理：由对偶问题求原始问题  
假设$$\mathbf{\alpha^*} = (\alpha_1^*,\alpha_2^*,...,\alpha_N^*)^T$$是对偶问题的解，则存在一个指标j使得$$\alpha_j >0$$，使得原问题的解$$\mathbf{w^*},b$$可由下面方程给出：  
&emsp;&emsp;$$ \mathbf{w^*} = \displaystyle \sum_{i=1}^N \alpha_i^*y_i(\mathbf{x_i})$$  
&emsp;&emsp;$$ b^* = y_j - \displaystyle \sum_{i=1}^N \alpha_i^*y_i(\mathbf{x_i*x_j})$$  
由此得到分离超平面：  
&emsp;&emsp;$$\mathbf{w^*x + b^*} = 0$$    
分类决策函数:  
&emsp;&emsp;$$f(x) = sign(\mathbf{w^*x + b^*}) $$  
&emsp;&emsp;&emsp;&emsp;$$= sign(\displaystyle \sum_{i=1}^N \alpha_i^*y_i\mathbf{x_ix_j} + b^*) $$    

### 线性不可分与软间隔最大化

&emsp;&emsp;$$\displaystyle \min_{\mathbf{w, b}} \frac{1}{2}||w||^2 + C\displaystyle \sum_{i=1}^N \xi_i $$    
&emsp;&emsp;s.t. &emsp;$$y_i(\mathbf{wx_i} + b) \ge 1 - \xi_i$$, i = 1,2...,N    
&emsp;&emsp;$$\xi_i \ge 0, i = 1,2...,N$$  

通过构造拉格朗日函数求对偶函数。原问题的解是$$(w^*,\xi^*,b^*)$$,对偶问题的解是$$\mathbf{\alpha}$$。  

实际上与线性可分的求法是一致的,只是对应的$$\xi$$会多出一个拉格朗日乘子，在求解对偶问题的最优化时，多了一个约束。$$\mathbf{w^*}$$是唯一的，b不唯一。  






