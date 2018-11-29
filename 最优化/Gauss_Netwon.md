#高斯-牛顿法
非线性回归中，损失函数可以表示成残差的形式：  
&emsp;&emsp;$$L(x) = \sum_{i=1}^{m}r_i(x)^2$$  
根据牛顿法：  
&emsp;&emsp;$$x_{t+1} = x_t - H^{-1}g$$,  
梯度表示为：  
&emsp;&emsp;$$g_j=2 \sum _i r_i \frac{\partial r_i}{\partial x_j}$$  
对损失函数求二阶导，我们可以得到Hessian矩阵：  
&emsp;&emsp;$$H_{jk} = 2\sum _i (\frac{\partial r_i}{\partial x_j}\frac{\partial r_i}{\partial x_k} + r_i\frac{\partial ^2 r_i}{\partial x_j \partial x_k})$$,  
当残差$$r_i$$很小的时候,我们就可以去掉最后一项，因此  
&emsp;&emsp;$$H_{jk} \approx  2 \sum _i J_{ij}J_{ik} \quad With \quad J_{ij} = \frac{\partial r_i}{\partial x_j}$$  
这样Hessian就是半正定了。  
因此参数迭代公式可以写成：  
&emsp;&emsp;$$x_{t+1} = x_t - (J^TJ)^{-1}J^Tr$$,  
##另外一种解释
对于函数$$f(x)$$的小邻域展开  
&emsp;&emsp;$$f(x+h) \simeq l(h) \equiv f(x) + J(x)h$$    
&emsp;&emsp;$$ F(x+h) \simeq L(h) \equiv \frac{1}  {2}l(h)^Tl(h)  
=\frac{1}{2}f^{T}f + h^TJ^Tf + \frac{1}{2}h^TJ^TJh$$   
我们需要选择步长$$h_{gn}$$来最小化$$L(h)$$   
&emsp;&emsp;$$h_{gn} = argmin_h{L(h)}$$   
&emsp;&emsp;$$(J^TJ)h_{gn} = -J^Tf$$   
