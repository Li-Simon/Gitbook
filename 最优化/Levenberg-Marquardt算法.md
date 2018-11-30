#L-M算法
方法用于求解非线性最小二乘问题，结合了梯度下降法和高斯-牛顿法。因此我们先简单介绍梯度下降法与Gauss-Netwon法。  
##[梯度下降法](https://en.wikipedia.org/wiki/Gradient_descent)  
把损失函数展开到一阶。  
&emsp;&emsp;$$f(x + \alpha \mathbf{d} ) = f(x_0) + \alpha f'(x_0) \mathbf{d} + O({\alpha}^2)$$  
&emsp;&emsp;$$x_{t+1} = x_t -\alpha f'(x_t)$$,
##牛顿法
[牛顿法](https://en.wikipedia.org/wiki/Newton's\_method\_in\_optimization)
把cost function进行展开到二阶：  
&emsp;&emsp;$$f(x_{t+1}) = f(x_t) + g(x_{t+1} - x_t)  + \frac{1}{2} (x_{t+1} -x_t)^TH(x_{t+1} -x_t)$$  
求导，$$\frac{\partial f}{\partial x_t} = g + H(x_{t+1} -x_t)$$,让导数为0就有  
&emsp;&emsp;$$x_{t+1} = x_t - H^{-1}g$$  
要是H是正定的，上面的就是凸函数，也就一定有了最小值。可惜H不一定是正定的，这就引导出了下面的方法

##[高斯-牛顿法](https://en.wikipedia.org/wiki/Gauss–Newton_algorithm)  
cost function可以表示成残差的形式：  
&emsp;&emsp;$$L(x) = \sum_{i=1}^{m}r_i(x)^2$$  
根据牛顿法：  
&emsp;&emsp;$$x_{t+1} = x_t - H^{-1}g$$,  
梯度表示为：  
&emsp;&emsp;$$g_j=2 \sum _i r_i \frac{\partial r_i}{\partial x_j}$$  
对方程\(4.9\)求二阶导，我们可以得到Hessian矩阵：  
&emsp;&emsp;$$H_{jk} = 2\sum _i (\frac{\partial r_i}{\partial x_j}\frac{\partial r_i}{\partial x_k} + r_i\frac{\partial ^2 r_i}{\partial x_j \partial x_k})$$,  
当残差$$r_i$$很小的时候,我们就可以去掉最后一项，因此  
&emsp;&emsp;$$H_{jk} \approx  2 \sum _i J_{ij}J_{ik} \quad With \quad J_{ij} = \frac{\partial r_i}{\partial x_j}$$  
这样Hessian就是半正定了。  
因此参数迭代公式\(4.10\)可以写成：  
&emsp;&emsp;$$x_{t+1} = x_t - (J^TJ)^{-1}J^Tr$$,  
##[Levenberg-Marquardt](https://en.wikipedia.org/wiki/Levenberg–Marquardt_algorithm)  
方法用于求解非线性最小二乘问题，结合了梯度下降法和高斯-牛顿法。  
其主要改变是在Hessian阵中加入对角线项,加这一样可以保证Hassian阵是正定的。当然，这是一种L2正则化方式。  
&emsp;&emsp;$$x_{t+1} = x_t - (H + \lambda I_n)^{-1}g$$,  
&emsp;&emsp;$$x_{t+1} = x_t - (J^TJ + \lambda I_n)^{-1}J^Tr$$  
L-M算法的不足点。  
当$$\lambda$$很大时，$$J^TJ + \lambda I_n$$根本没用，Marquardt为了让梯度小的方向移动的快一些，来防止小梯度方向的收敛，把中间的单位矩阵换成了$$diag(J^TJ)$$,因此迭代变成：  
&emsp;&emsp;$$x_{t+1} = x_t - (J^TJ + \lambda diag(J^TJ))^{-1}J^Tr$$

阻尼项（damping parameter）$$\lambda$$的选择，Marquardt 推荐一个初始值$$\lambda_0$$与因子$$v > 1$$，开始时，$$\lambda = \lambda_0$$,然后计算cost functions,第二次计算$$\lambda = \lambda_0/v$$,如果两者cost function都比初始点高，然后我们就增大阻尼项，通过乘以v,直到我们发现当$$\lambda = \lambda_0v^k$$时，cost function下降。  
如果使用$$\lambda = \lambda_0/v$$使得cost fucntion下降，然后我们就把$$\lambda_0/v$$作为新的$$\lambda$$  
当$$\lambda = 0$$时，就是高斯-牛顿法，当$$\lambda$$趋于无穷时，就是梯度下降法。如果使用$$\lambda/v$$没有是损失函数下降，使用$$\lambda$$导致损失函数下降，那么我们就继续使用$$\lambda$$做为阻尼项。

# 归一化的残差

如果我们假设数据中每一点的贡献是等权重，因此，我们有必要对每一项残差加一个权重，来归一化每一项残差。因此公式\(4-9\)可以变成，  
cost function可以表示成残差的形式：  
&emsp;&emsp;$$L(x) = \sum_{i=1}^{m}\lambda_i r_i(x)^2 = \sum_{i=1}^{m}\frac{1}{y_i^2} (y_i - f_i(x_i))^2 $$   
此时，Jacobia变成  
&emsp;&emsp;$$H_{jk} \approx  2 \sum _i J_{ij}J_{ik} \quad With \quad J_{ij} = y_i \frac{\partial r_i}{\partial x_j}$$  
&emsp;&emsp;$$J_S = \Sigma J,  \Sigma_{ij} = \frac{1}{y_i}\delta_{ij} $$

# L2正则化与Levenberg-Marquardt算法

我们在cost fucntion加上L2正则项  
&emsp;&emsp;$$L(\beta) = \sum_{i=1}^{m}[y_i - f(x_i,\beta)]^2 + \lambda||\beta||^2$$  
可以表示成：  
&emsp;&emsp;$$L(\beta) = L(\beta_0) + (\beta - \beta_0)^T\nabla_\beta L(\beta_0) + \frac{1}{2}(\beta - \beta_0)^TH(\beta - \beta_0)+ \lambda||\beta||^2+O(\beta^3)$$  
求一阶导数：  
&emsp;&emsp;$$L(\beta) = L(\beta_0) + (\beta - \beta_0)^Tg + \frac{1}{2}(\beta - \beta_0)^TH(\beta - \beta_0)+ \frac{1}{2}\lambda||\beta||^2+O(\beta^3)$$  
令其为0：  
&emsp;&emsp;$$\frac{\partial L(\beta)}{\partial \beta} = g + H(\beta - \beta_0) + \lambda\beta = 0$$  
就得到：  
&emsp;&emsp;$$\beta = (H + \lambda I_n)^{-1}H\beta_0 - (H + \lambda I_n)^{-1}g$$,
算法流程如下：  
$$k:=0;x=x_0;v:=2;A:=J(x)^TJ(x); g:=J(x)^Tf(x);u:=\tau*\max(a_{ii})$$      
found:= $$(||g||_{\infty} \le \epsilon_1)$$   
while(not found) and $$k < k_{max}$$    
&emsp; &emsp;k:=k+1,计算$$h_{lm}$$根据$$(A+uI)h_{lm} = -g$$     
&emsp;&emsp; if $$||h_{lm}||\le  \epsilon(||x||+\epsilon_2)$$     
&emsp; &emsp;&emsp;&emsp; found := true    
&emsp;&emsp; else:    
&emsp; &emsp;&emsp;&emsp; $$x_{new}:=x+h_{lm}$$     
&emsp;&emsp; $$\rho := (F(x)-F(x+h_{lm})/(L(0)-L(h_{lm})))$$     
&emsp;&emsp;if $$\rho \ge 0$$    
&emsp;&emsp;&emsp;&emsp;$$x:=x_{new};g:=J(x)^Tf(x)$$    
&emsp;&emsp;&emsp;&emsp;$$A:=J^T(x)J(x);g:=J^T(x)f(x)$$   
&emsp;&emsp;&emsp;&emsp;found:= $$(||g||_{\infty} \le \epsilon_1)$$   
&emsp;&emsp;&emsp;&emsp;u:= $$u*\max(1/2,1-(2\rho-1)^3);v:=2$$     
&emsp;&emsp;else:     
&emsp;&emsp;&emsp;&emsp;$$u:= u*v; v = 2*v$$    

```py
    def LM_Solver(self):
        init_p = 0.5 * np.ones((2, 1))
        init_p[0, 0] = 2.0
        init_p[1, 0] = 1.0
        epsilon_1 = 1e-15
        epsilon_2 = 1e-15
        epsilon_3 = 1e-15
        alpha = 1
        cost_history = np.zeros((self.training_steps, 3))
        Jaco = self.Jacobian(init_p)
        Hassian = np.dot(Jaco.transpose(), Jaco)
        resi = self.residual(init_p)
        m_g = np.dot(Jaco.transpose(), resi)
        cost_old = np.dot(resi.transpose(), resi)
        epoch = -1
        train_stop = -1
        miu = Hassian.max()
        lamda_v = 2

        matrix_I = np.identity(Hassian.shape[0])
        while epoch < self.training_steps - 1 and train_stop < 0:
            epoch += 1
            print "Epoch: ", epoch
            go_next_epoch = -1

            while go_next_epoch < 0:
                sigma_p = np.dot(np.linalg.inv(Hassian + miu*matrix_I), m_g)
                square_g = np.linalg.norm(sigma_p)
                if square_g <= epsilon_2*np.linalg.norm(init_p):
                    train_stop = 1
                    break
                else:
                    new_p = init_p + sigma_p
                    resi_new = self.residual(new_p)
                    cost_new = np.dot(resi_new.transpose(), resi_new)
                    frac = np.dot(sigma_p.transpose(),  miu* sigma_p + m_g)
                    rou = (cost_old - cost_new) / frac
                    if rou > 0:
                        go_next_epoch = 1
                        init_p = new_p
                        Jaco = self.Jacobian(init_p)
                        Hassian = np.dot(Jaco.transpose(), Jaco)
                        resi = self.residual(init_p)
                        m_g = np.dot(Jaco.transpose(), resi)
                        if (np.abs(m_g)).max < epsilon_1:
                            train_stop = 1
                            break
                        miu *= max(1.0 / 3.0, 1 - pow(2 * rou - 1, 3))
                        lamda_v = 2
                        print init_p.transpose(), miu, cost_new
                        cost_history[epoch, 0] = cost_new
                        cost_history[epoch, 1] = miu
                        cost_history[epoch, 2] = np.linalg.norm(m_g)
                        cost_old = cost_new
                    else:
                        miu *= lamda_v
                        # lamda_miu *= 0
                        lamda_v *= 2
        return cost_history, init_p
```



