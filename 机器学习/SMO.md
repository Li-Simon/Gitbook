##SMO序列最小最优化算法
当你明白其原理的时候，该算法实现起来也不是很难的。  
在SVM中，求解最终是在对偶空间里面，也就是拉格朗日乘子空间，要求解的就是如下的带约束的优化问题：  
 
&emsp;&emsp;$$\displaystyle \min_{\mathbf{\alpha}}\frac{1}{2}\displaystyle \sum_{i=1}^N\displaystyle \sum_{j=1}^N\alpha_i\alpha_jy_iy_j(\mathbf{x_ix_j}) - \displaystyle \sum_{i=1}^N \alpha_i$$   
&emsp;&emsp;s.t.  $$\sum_{i=1}^N \alpha_iy_i = 0$$   
&emsp;&emsp;&emsp;&emsp;$$0 \le \alpha_i \le C$$ ,i=1,2,...,N。   
每个$$\alpha_i$$对应一个样本点$$x_i$$，只不过只有支持向量对应的$$\alpha_i$$不为0。  
SMO是一种启发式算法，基本思路就是，如果所有变量都满足KKT条件，则得到了最优化问题的解。因为KKT条件是最优化问题的充分必要条件。否则就选择两个变量而固定其它所有变量，针对这两个变量构建一个二次规划问题，这个二次规划问题的解会更接近于原始优化问题的解，因为它使原始问题的目标函数变低了。重要的是，两个变量的二次规划问题有解析解，这大大的加快了算法的求解速度。
####两个变量的选取
子问题有两个变量，选取的标准是，第一个变量是违反KKT条件最严重的点，第二个变量根据第一个变量与约束条件而自动的确定。  
如此，SMO算法不断的把原始问题分解为子问题并对子问题求解，最终达到求解原始问题的目的。  
#####第一个变量的选取
查找违反KKT条件最严重的点，如下是KKT条件：  
&emsp;&emsp;$$\alpha_i = 0$$等价于$$y_ig(x_i) \ge 1$$   
&emsp;&emsp;$$0 \lt \alpha_i \lt  C$$等价于$$y_ig(x_i) = 1$$  
&emsp;&emsp;$$\alpha_i =  C$$等价于$$y_ig(x_i) \le 1$$  
其中： $$g(x_i) = \displaystyle \sum_{j=1}^N\alpha_jy_jK(\mathbf{x_i,x_j}) + b$$ 
分两步查找，首先查找满足$$0 \lt \alpha_i \lt  C$$的$$\alpha$$,因为这是支持向量对应的点，如果都符合KKT条件，则再遍历所有的$$\alpha$$,检查是否符合KKT条件。  
#####第二个变量的选取
找到$$\alpha_1$$之后，我们希望第二个变量$$\alpha_2$$具有足够大的变化。  
###两个变量的二次规划问题
假设我们要优化的就是$$\alpha_1, \alpha_2$$，而其它的$$\alpha$$都是常量，则我们要优化的是如下的两个变量的二次规划问题。  
&emsp;&emsp;$$\displaystyle \min_{\mathbf{\alpha_1,\alpha_2}}W(\alpha_1,\alpha_2) = \frac{1}{2}K_{11}\alpha_1^2 + \frac{1}{2}K_{22}\alpha_2^2 + y_1y_2K_{12}\alpha_1\alpha_2 -(\alpha_1 + \alpha_2)$$
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;$$ + y_1\alpha_1\displaystyle \sum_{j=3}^N\alpha_iy_iK_{i1}+ y_2\alpha_2\displaystyle \sum_{j=3}^N\alpha_iy_iK_{i2}$$   
&emsp;&emsp;s.t.  $$\alpha_1y_1 + \alpha_2y_2 = -\displaystyle \sum_{i=3}^N\alpha_iy_i = \xi$$   
&emsp;&emsp;&emsp;&emsp;$$0 \le \alpha_i \le C, i = 1,2$$   
其中$$K_{ij} = K(x_1,x_j),i,j=1,2,..,N$$,  $$\xi$$是常数。   

###二次规划问题的解
上面优化问题的未剪辑的解是：  
$$\alpha_2^{\text{new,nuc}} = \alpha_2^{\text{old}} + \frac{y_2(E_1 - E_2)}{\eta}$$  
其中:$$\eta = K_{11} + K_{22} - 2K_{12}$$  
$$E_i = g(x_i) - y_i = (\displaystyle \sum_{j=1}^N\alpha_jy_jK(\mathbf{x_i,x_j}) + b) - y_i$$, i=1,2  
经过剪辑之后，$$\alpha_2$$的解是：  
&emsp;&emsp;$$\alpha_2^{\text{new}} = H$$, if $$\alpha_2^{\text{new,nuc}} > H$$   
&emsp;&emsp;$$\alpha_2^{\text{new}} = \alpha_2^{\text{new,nuc}}$$, if $$L < \alpha_2^{\text{new,nuc}} < H$$   
&emsp;&emsp;$$\alpha_2^{\text{new}} = L$$, if $$\alpha_2^{\text{new,nuc}} < L$$   
由$$\alpha_2^{\text{new}}$$求得$$\alpha_1^{\text{new}}$$是：  
&emsp;&emsp;$$\alpha_1^{\text{new}} = \alpha_1^{\text{old}} + y_1y_2(\alpha_2^{\text{old}} - \alpha_2^{\text{new}})$$   
其中：  
当$$y_1 \ne y_2$$时，$$L = max(0,\alpha_2^{\text{old}} -\alpha_1^{\text{old}}),H = min(C,C + \alpha_2^{\text{old}} -\alpha_1^{\text{old}})$$   
当$$y_1 = y_2$$时，$$L = max(0,\alpha_2^{\text{old}} +\alpha_1^{\text{old}}-C),H = min(C,\alpha_2^{\text{old}} +\alpha_1^{\text{old}})$$   






 


    
 

