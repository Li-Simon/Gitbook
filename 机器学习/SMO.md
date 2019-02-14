##SMO序列最小最优化算法
在SVM中，求解最终是在对偶空间里面，也就是拉格朗日乘子空间，要求解的就是如下的带约束的优化问题：  
 
&emsp;&emsp;$$\displaystyle \min_{\mathbf{\alpha}}\frac{1}{2}\displaystyle \sum_{i=1}^N\displaystyle \sum_{j=1}^N\alpha_i\alpha_jy_iy_j(\mathbf{x_ix_j}) - \displaystyle \sum_{i=1}^N \alpha_i$$   
&emsp;&emsp;s.t.  $$\sum_{i=1}^N \alpha_iy_i = 0$$   
&emsp;&emsp;&emsp;&emsp;$$\alpha_i \ge 0$$ ,i=1,2,...,N。    

