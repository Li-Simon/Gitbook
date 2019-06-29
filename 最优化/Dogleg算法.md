#Dogleg算法
Powell’s Dog Leg Method是一种信赖域方法  
在Gauss-Netwon迭代中  
&emsp;&emsp;$$ J(x)h \simeq  -f(x)$$  
最陡的方向由下面公式给出：  
&emsp;&emsp;$$ h_{sd} = -g = -J(x)^Tf(x)$$  
但是这只是给出了方向，而没有给出步长。  
考虑线性模型  
&emsp;&emsp;$$f(x + \alpha h_{sd}) \simeq f(x) + \alpha J(x)h_{sd}$$  
&emsp;&emsp;$$ F(x + \alpha h_{sd}) \simeq  \frac{1}{2}||f(x) + \alpha J(x)h_{sd}||^{2} 
= F(x) + \alpha h_{sd}^TJ(x)^{T}f(x) + \frac{1}{2}\alpha ^2 ||J(x)h_{sd}||^{2}$$  
当$$\alpha$$取如下值得时候，以上函数取最小值  
&emsp;&emsp;$$ \alpha = - \frac{h_{sd}^TJ(x)^Tf(x)}{||J(x)h_{sd}||^{2}} = \frac{||g||^2}{||J(x)h_{sd}||^{2}}$$  
现在有两个步长的选择 $$a = \alpha h_{sd}$$ 以及 $$b = h_{gn}$$,Powell建议在信赖域半径是$$\Delta$$的时候，步长可以如下选择  
If $$||h_{gn}|| \leq \Delta, h_{dl} = h_{gn}$$  
&emsp;&emsp;Elseif: $$||\alpha h_{sd}|| \geq \Delta, h_{dl} = (\Delta / ||h_{sd}||)h_{sd}$$  
else:  
&emsp;&emsp;$$ h_{dl} = \alpha h_{sd} + \beta(h_{gn} - \alpha h_{sd})$$  
选择$$\beta$$ 使得$$||h_{dl}|| = \Delta$$  
在L-M算法中我们定义了增益因子，  
&emsp;&emsp;$$ \rho = (F(x) - F(x+h_{dl})/(L(0) - L(h_{dl})))$$  
其中L是线性模型  
&emsp;&emsp;$$ L(h) = \frac{1}{2}||f(x) + J(x)h||^2$$  
在L-M我们通过$$\rho$$来控制阻尼因子，在dog-leg算法中，我们通过它来控制步长  
Dog Leg Method:    
$$k:=0;x=x_0;\Delta := \Delta_0; g:=J(x)^Tf(x)$$     
found:= $$(||f(x)||_{\infty} \le \epsilon_3)$$or$$||g||_{\infty}\le \epsilon_1$$     
while(not found) and $$k < k_{max}$$     
&emsp; &emsp;k:=k+1,计算$$\alpha$$    
&emsp;&emsp;$$h_{sd}:=-\alpha g$$; solve $$J(x)h_{gn} \simeq -f(x)$$     
&emsp;&emsp;  计算 $$h_{dl}$$    
&emsp;&emsp; if $$||h_{dl}|| \le \epsilon(||x||+\epsilon_2)$$     
&emsp; &emsp;&emsp;&emsp; found := true     
&emsp; &emsp;else:    
&emsp; &emsp;&emsp;&emsp; $$x_{new}:=x+h_{dl}$$      
&emsp;&emsp; $$\rho := (F(x)-F(x+h_{dl})/(L(0)-L(h_{dl})))$$      
&emsp;&emsp;if $$\rho \ge 0$$     
&emsp;&emsp;&emsp;&emsp;$$x:=x_{new};g:=J(x)^Tf(x)$$     
&emsp;&emsp;&emsp;&emsp;found:= $$(||f(x)||_{\infty} \le \epsilon_3)$$or$$||g||_{\infty}\le \epsilon_1$$    
&emsp;&emsp;if $$\rho \ge 0.75$$      
&emsp;&emsp;&emsp;&emsp;$$\Delta:= \max(\Delta, 3*||h_{dl}||)$$    
&emsp;&emsp;else if $$\rho \le 0.25$$     
&emsp;&emsp;&emsp;&emsp;$$\Delta:= \Delta /2$$      
&emsp;&emsp;found:= $$\Delta \le \epsilon_2(||x||+\epsilon)$$     

```py
    def Dogleg_Solver(self):
        init_para = np.ones((2, 1))
        epsilon_1 = 1e-15
        epsilon_2 = 1e-15
        epsilon_3 = 1e-15
        alpha = 1
        cost_history = np.zeros((self.training_steps, 3))
        Jaco = self.Jacobian(init_para)  //get Jacobian
        Hassian = np.dot(Jaco.transpose(), Jaco) 
        resi = self.residual(init_para)
        m_g = np.dot(Jaco.transpose(), resi)
        cost_old = np.dot(resi.transpose(), resi)


        epoch = -1
        train_stop = -1
        delta = 0.01
        while epoch < self.training_steps - 1 and train_stop < 0:
            epoch += 1
            print "Epoch: ", epoch
            go_next_epoch = -1

            while go_next_epoch < 0:
                square_g = np.linalg.norm(m_g)
                square_Jg = np.linalg.norm(np.dot(Jaco, m_g))
                alpha = pow(square_g, 2) / pow(square_Jg, 2)

                h_sd = -alpha * m_g
                h_gn = np.dot(np.linalg.inv(Hassian), -m_g)
                norm_para = np.linalg.norm(init_para)

                ##calculate h_dl
                if np.linalg.norm(h_gn) <= delta:
                    h_dl = h_gn
                    hdl_type = 0
                elif np.linalg.norm(h_sd) >= delta:
                    h_dl = (delta / np.linalg.norm(h_sd)) * h_sd
                    hdl_type = 1
                else:
                    beta = self._get_h_dl(h_sd, h_gn, delta)
                    h_dl = h_sd + beta * (h_gn - h_sd)
                    hdl_type = 2

                    # #epsilon_2*norm_para:
                if np.linalg.norm(h_dl) < epsilon_2 * (norm_para + epsilon_2):
                    train_stop = 1
                    break
                else:
                    para_0 = init_para + h_dl
                    #cost_old = pow(np.linalg.norm(resi), 2)
                    resi_new = self.residual(para_0)
                    cost_new = np.dot(resi_new.transpose(), resi_new)
                    #pow(np.linalg.norm(resi_new), 2)
                    #h_sub = h_sd - 0.5 * np.dot(Hassian, h_dl)
                    #frac = np.dot(h_dl.transpose(), h_sub)
                    if hdl_type == 0:
                        frac = cost_new
                    elif hdl_type == 1:
                        frac = delta/(2*alpha)*(2*np.linalg.norm(alpha*m_g) - delta)
                    else:
                        frac = 0.5*alpha*pow(beta, 2)*pow(np.linalg.norm(alpha*m_g), 2)
                        frac += beta*(2 - beta)*cost_new
                    rou = (cost_old - cost_new) /frac
                    if rou > 0:
                        go_next_epoch = 1
                        init_para = para_0
                        Jaco = self.Jacobian(init_para)
                        Hassian = np.dot(Jaco.transpose(), Jaco)
                        resi = self.residual(init_para)
                        m_g = np.dot(Jaco.transpose(), resi)

                        cost_history[epoch, 0] = cost_new
                        cost_history[epoch, 1] = delta
                        cost_history[epoch, 2] = np.linalg.norm(m_g)
                        print para_0.transpose(), cost_new, delta

                        if (np.abs(m_g)).max() < epsilon_1 or (np.abs(resi_new)).max() < epsilon_3:
                            train_stop = 1
                            break
                    if rou > 0.75:
                        delta = max(delta, 3 * np.linalg.norm(h_dl))
                    elif rou < 0.25:
                        delta /= 2.0
                        if delta < epsilon_2:
                            break
                    cost_old = cost_new
        return cost_history, init_para
```
