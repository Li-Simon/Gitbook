# Levenberg-Marquardt算法

[Levenberg-Marquardt](https://en.wikipedia.org/wiki/Levenberg–Marquardt_algorithm)  
方法用于求解非线性最小二乘问题，结合了梯度下降法和高斯-牛顿法。  
其主要改变是在Hessian阵中加入对角线项,加这一样可以保证Hassian阵是正定的。当然，这是一种L2正则化方式。  
$$x_{t+1} = x_t - (H + \lambda I_n)^{-1}g$$,  
$$x_{t+1} = x_t - (J^TJ + \lambda I_n)^{-1}J^Tr$$  
L-M算法的不足点。  
当$$\lambda$$很大时，$$J^TJ + \lambda I_n$$根本没用，Marquardt为了让梯度小的方向移动的快一些，来防止小梯度方向的收敛，把中间的单位矩阵换成了$$diag(J^TJ)$$,因此迭代变成：  
$$x_{t+1} = x_t - (J^TJ + \lambda diag(J^TJ))^{-1}J^Tr$$

阻尼项（damping parameter）$$\lambda$$的选择，Marquardt 推荐一个初始值$$\lambda_0$$与因子$$v > 1$$，开始时，$$\lambda = \lambda_0$$,然后计算cost functions,第二次计算$$\lambda = \lambda_0/v$$,如果两者cost function都比初始点高，然后我们就增大阻尼项，通过乘以v,直到我们发现当$$\lambda = \lambda_0v^k$$时，cost function下降。  
如果使用$$\lambda = \lambda_0/v$$使得cost fucntion下降，然后我们就把$$\lambda_0/v$$作为新的$$\lambda$$  
当$$\lambda = 0$$时，就是高斯-牛顿法，当$$\lambda$$趋于无穷时，就是梯度下降法。如果使用$$\lambda/v$$没有是损失函数下降，使用$$\lambda$$导致损失函数下降，那么我们就继续使用$$\lambda$$做为阻尼项。

  
![](/assets/L_M_Algo.gif)

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



