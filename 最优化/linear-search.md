#Linear Search Methods
## 线性搜索与Armijo准则

符号约定：  
&emsp;&emsp;$$ g_k: \nabla f(x_k)$$,即目标函数关于k次迭代值$$x_k$$的导数  
&emsp;&emsp;$$ G_k: G(x_k) = \nabla ^2f(x_k)$$,即Hassian矩阵  
&emsp;&emsp;$$ d_k: $$第k次迭代的优化方向，在最速下降算法中，有$$d_k = -g_k$$  
&emsp;&emsp;$$ \alpha_k$$:第k次迭代的步长因子，有$$x_{k+1} = x_k + \alpha_k d_k$$  
在精确线性搜索中，步长因子$$\alpha _k$$由下面的因子确定：  
&emsp;&emsp;$$ \alpha _k = arg min _{\alpha} f(x_k + \alpha d_k)$$  
而对于非精确线性搜索，选取的$$\alpha _k$$只要使得目标函数f得到可接受的下降量，即：  
&emsp;&emsp;$$ \Delta f(x_k) = f(x_k) - f(x_k + \alpha _k d_k)$$  
Armijo 准则用于非精确线性搜索中步长因子$$\alpha$$的确定，内容如下：  
Armijo 准则：  
已知当前位置$$x_k$$和优化方向$$d_k$$，参数$$\beta \in (0,1), \delta \in (0,0.5)$$.令步长因子&emsp;&emsp;$$ \alpha _k = \beta ^{m_k}$$,其中$$m_k$$为满足下列不等式的最小非负整数m:  
&emsp;&emsp;$$ f(x_k + \beta ^m d_k) \leq f(x_k) + \delta \beta ^m g_k^Td_k$$  
由此确定下一个位置$$x_{k+1} = x_k + \alpha _k d_k$$  
对于梯度上升，上面的方程变成：  
&emsp;&emsp;$$ f(x_k - \beta ^m d_k) \geq f(x_k) - \delta \beta ^m g_k^Td_k$$  
由此确定下一个位置$$x_{k+1} = x_k - \alpha _k d_k$$
##最速下降法
the steepest descent algorithm proceeds as follows: at each step, starting from the point $$x^{(k)}$$,we conduct a line search in the direction $$-\nabla f(x^{(k)})$$, until a minimizer, $$x^{(k+1)}$$, is found.  
&emsp;&emsp;$$\alpha _{k} = arg min_{\alpha \ge 0} f(x_{(k)} - \alpha  \nabla f(x^{(k)})) $$  
Proposition 8.1： if $$x^{(k)}$$ is the steepest descent sequence for f: $$R^n$$-&gt;R， then for each k the vector $$x^{(k+1)} - x^{(k)}$$ is orthogonal to the vector $$x^{(k+2)} - x^{(k+1)}$$  
Proposition 8.2：if $$x^{(k)}$$ is the steepest descent sequence for f: $$R^n$$-&gt;R and if $$\nabla f(x^{(k)}) \ne 0$$, then     
&emsp;&emsp;$$ f(x^{(k+1)}) < f(x^{(k)})$$  
Stopping criterion：  
&emsp;&emsp;$$ \frac{|f(x^{(k+1)}) - f(x^{(k)})|}{||f(x^{(k)})||} < \epsilon $$  
Example: Quadratic function of the form:  
&emsp;&emsp;$$ f(x) = \frac{1}{2}x^T\mathrm{Q}x - b^Tx $$  
Gradient:$$g^{(k)} = \nabla f(x^{(k)}) = Qx - b$$  
so   
&emsp;&emsp;$$ x^{(k+1)} = x^{(k)} - \alpha _{k}g^{(k)}$$  
where:  
&emsp;&emsp;$$ \alpha _{k} = arg min_{\alpha \ge 0} f(x_{(k)} - \alpha  g^{(k)})  $$  
&emsp;&emsp;&emsp;&emsp;$$= arg min_{\alpha \ge 0} (\frac{1}{2}(x^{k} - \alpha  g^{(k)})^TQ(x^{k} - \alpha  g^{(k)}) - (x^{k} - \alpha  g^{(k)})^Tb) $$  
Hence:  
&emsp;&emsp;$$ \alpha _{k} = \frac{g^{(k)T}g^{(k)}}{g^{(k)T}Qg^{(k)}}$$

Covergence properties:  
Define:   
&emsp;&emsp;$$ V(x) = f(x) + \frac{1}{2}x^{*T}Qx^{*} = \frac{1}{2}(x-x^*)^TQ(x-x^*)$$  
With:$$x^* = Q^{-1}b$$  
Lemma 8.1 The iterative algorithm   
&emsp;&emsp;$$ x^{(k+1)} = x^{(k)} - \alpha _{k}g^{(k)}$$  
with $$g^{(k)} = Qx^{(k)} - b$$ satisfies   
&emsp;&emsp;$$ V(x^{(k+1)}) = (1 - \gamma _{k})V(x^{(k)})$$,  
where, if $$g^{(k)} = 0$$ then $$\gamma _{k} = 1$$, and if $$g^{(k)} \ne 0$$ then:  
&emsp;&emsp;$$ \gamma _{k} = \alpha _{k}\frac{g^{(k)T}Qg^{(k)}}{g^{(k)T}Q^{-1}g^{(k)}}(2\frac{g^{(k)T}g^{(k)}}{g^{(k)T}Qg^{(k)}} - \alpha _{k})$$  
Submit $$\alpha _{k}$$ into $$\gamma _{k}$$, then  
&emsp;&emsp;$$\gamma _{k} = \frac{(g^{(k)T}g^{(k)})^2}{(g^{(k)T}Qg^{(k)})(g^{(k)T}Q^{-1}g^{(k)})}$$

Theorem 8.1 Let $$x^{(k)}$$ be the sequence resulting from a gradient algorithm  $$x^{(k+1)} = x^{(k)} - \alpha _{k}g^{(k)}$$. Let $$\gamma _{k}$$ be as defined in Lemma 8.1, and suppose that $$\gamma _{k} > 0$$ for all k, then $$x^{(k)}$$ converges to $$x^{*}$$ for any initial condition $$x^{(0)}$$ if and only if:  
&emsp;&emsp;$$ \sum _{x=0}^{\infty } \gamma _{k} = \infty $$

Theorem 8.2 In the steepest descent algorithm, we have   
&emsp;&emsp;$$ x^{(k)}$$ -&gt;$$x^{*}$$ for any $$x^{(0)}$$

Theorem 8.3 For the fixed step size gradient algorithm, $$x^{(k)}$$ -&gt;$$x^{*}$$ for any $$x^{(0)}$$

if and only if $$0 < \alpha < \frac{2}{\lambda _{max}(Q)}$$

Convergence Rate:  
Theorem 8.4 In the method of steepest descent applied to the quadratic function, at every step k, we have :  
&emsp;&emsp;$$V(x^{(k+1)}) \le (\frac{\lambda _{max}(Q) - \lambda _{min}(Q) }{\lambda _{max}(Q) })V(x^{(k)})$$.  
Let:  
&emsp;&emsp;$$ r = \frac{\lambda _{max}(Q)}{\lambda _{min}(Q)} = ||Q||||Q^{-1}||$$ the so-called condition number of Q.  
Then, it follows from Theorem 8.4 that $$V(x^{(k+1)}) \le (1 - \frac{1}{r})V(x^{(k)})$$. We refer to $$1 - \frac{1}{r}$$ as the convergence ratio. If r = 1, then $$\lambda _{max}(Q) = \lambda _{min}(Q) $$, corresonding to circular contours of f.  You can using the convergence ratio r to judge the speed of convergence.  
Definition 8.1 Given a sequence $$x^{(k)}$$ thst converges to $$x^*$$, that is, $$lim _{k ->\infty}||x^{(k)} - x^{*}|| = 0$$, we say that the order of convergence is o, where $$p \in R$$, 
if $$0 \lt lim_{k -> \infty} \frac{x^{(k+1)} - x^{*}}{||x^{(k)} - x^{*}||^p} < \infty$$,   
if for all $$p > 0$$, $$lim_{k -> \infty} \frac{x^{(k+1)} - x^{*}}{||x^{(k)} - x^{*}||^p} =0$$,   

  then we say that the order of convergence is $$\infty$$.  
Lemma 8.3. In the steepest descent algorithm, if $$g^(k) \ne 0$$ for all k, then $$\gamma _{k} = 1 $$ if and only if $$g^(k)$$ is an eigenvector of Q.

Theorem 8.6 Let $$x^{(k)}$$ be the sequence resulting from a gradient algorithm applied to a function f. Then, the order of convergence of $$x^{(k)}$$ is 1 in the worst case, that is, ehere exist a function f and an initial $$x^{(0)}$$ such that the order of convergence of $$x^{(k)}$$ is equal 1.

# Newtow's Method

&emsp;&emsp;$$ f(x) = f(x^{(x)}) + (x - x^{(k)})^Tg^{(k)} + \frac{1}{2}(x - x^{(k)})^TF(x^{(k)})(x - x^{(k)})$$  
 Theorem 9.1 Suppose that $$f \in C^3$$, and $$x^* \in R^n$$ is a point such that $$\nabla f(x^*) = 0$$ and $$F(x^*)$$ is invertible. Then, for all $$x^{(0)}$$ sufficiently close to $$x^*$$, Netwon's method is weel defined for all k, and converges to $$x^*$$ with order of convergence at least 2.

At stated in the aboved theorem, Newton's methods has superies convergence properties if the starting point is near the solution. However, the method is not guaranteed to converge to the soulution if we start away from it\(in fact, it may not even be well defined because the Hessian may be singular\). In particular, the method may not be a descent method; that is, it is possible that $$f(x^{(k+1)}) > f(x^{(k)})$$. Fortunately, it is possible to modify the algorithm such that descent property holds. To see this, we need the following result.  
 Theorem 9.2 Let $$x^{(k)}$$ be the sequence generated by Newton's method for minimizing a given objective function f\(x\). If the Hessian $$F(x^{(k)}) > 0$$ and $$g^{(k)} = \nabla f(x^{(k)}) \ne 0$$, then the direction   
&emsp;&emsp;$$d^{(k)} = -F(x^{(k)})^{-1}g^{(k)} = x^{(k+1)} - x^{(k)}$$ from $$x^{(k)}$$ to $$x^{(k+1)}$$ is a descent direction for f in the sense that there exists an $$\alpha > 0$$ such that for all $$a \in (a, \alpha)$$,  
  $$f(x^{(k)} = \alpha d^{(k)}) < f(x^{(k)})$$.

The above theorem motivates the following modification of Newton's method:  
&emsp;&emsp;$$ x^{(k+1)} =x^{(k)} - \alpha _k F(x^{(k)})^{-1}g^{(k)}$$ where  
&emsp;&emsp;$$\alpha _k = arg min _{\alpha \gt 0} f(x^{(k) - \alpha _{k} F(x^{(k)})^{-1}g^{(k)}})$$

A drawback of Newton's method is that evaluation of $$F(x^{(k)})$$ for large n can be computationally expensive. Furthermore, we have to solve the set of n linear equations $$F(x^{(k)})d^{(k)} = -g^{(k)}$$. In the Chapters 10 and 11, we discuss methods that alleviate this difficulty.

Levenberg-Marquardt Modification:  
If the Hessian matrix $$F(x^{(k)})$$ is not positive definite, then the search direction $$d^{(k)} = -F(x^{(k)})^{-1}g^{(k)}$$ may not point in a descent direction. A simple technique to ensure that the search direction is a descent direction is to introduce the so-called Levenberg-Marquardt Modification to Newton's algorithm:  
&emsp;&emsp;$$x^{(k+1)} =x^{(k)} - \alpha _k F(x^{(k)} + u_kI)^{-1}g^{(k)}$$  
where $$u_k \ge 0$$

# Newton's methods for nonlinear least-squares

Consider the following problem:  
&emsp;&emsp;$$minimize \sum _{i=1}^{m} (r_i(x))^2 $$  
where $$r_i: R^n -> R, i=1,...,m$$, are given functions. This particular problem is called a nonlinear least-squares problem  
&emsp;&emsp;$$F_{jk} = 2\sum _i (\frac{\partial r_i}{\partial x_j}\frac{\partial r_i}{\partial x_k} + r_i\frac{\partial ^2 r_i}{\partial x_j \partial x_k})$$,   
Let $$s(x) = r_{i}(x)\frac{\partial ^2 r_i}{\partial x_j \partial x_k}(x)$$  
So the Hessian matrix as   
&emsp;&emsp;$$ F(x) = 2(J(x)^TJ(x) + S(x))$$.  
Therefore, Newton's method applied to the nonlinear least-squares problems is given by  
&emsp;&emsp;$$x^{(k+1)} = x^{(k)} - (J(x)^TJ(x) + S(x))^{-1}J(x)^Tr(x)$$.   
In some case, s\(x\) can ne ignored because its components are negligibly small. In this case, the above Newtons's algorithm reduces to what is commonly called the Gauss-Newtons method:  
&emsp;&emsp;$$x^{(k+1)} = x^{(k)} - (J(x)^TJ(x))^{-1}J(x)^Tr(x)$$.  
A potential problem with the Gauss-Newton method is that the matri $$J(x)^TJ(x)$$ may not be positive definite. As described before, this problem can be overcome using a Levenberg-Marquardt modification:  
&emsp;&emsp;$$ x^{(k+1)} = x^{(k)} - (J(x)^TJ(x) + u_k I)^{-1}J(x)^Tr(x)$$.

# Conjugate Direction Methods

The conjugate direction methods typically perrform better than the method of steepest descent, but not as weel as Newton's method. As we saw from the method of steepest descent and Newton's method, the crucial factor in the efficiency of an iterative search method is the direction of the search at each iteration.

Definition 10.1 Let Q be a real symmetric nxn matrix. The directions $$d^{(0)},d^{(1)},d^{(2)},...,d^{(m)}$$ are Q-conjugate if, for all $$i \ne j$$, we have $$d{(i)T}Qd^{(j)} = 0$$.

Lemma 10.1 Let Q be as symmetric positive definite nxn matrix. If the diretions $$d^{(0)},d^{(1)},d^{(2)},...,d^{(m)} \in R^n, k \le n-1$$, are nonzero and Q-conjugate, then they are linearly independent.

Basic conjugate Direction Algorithm. Given a start $$x^{(0)}$$, and Q-conjugate direction &emsp;&emsp;$$d^{(0)},d^{(1)},d^{(2)},...,d^{(m)}, for k \ge 0$$,  
&emsp;&emsp;$$g^{(k)} = \nabla f(x^{(k)}) = Qx^{(k)} - b$$,  
&emsp;&emsp;$$ \alpha _k = -\frac{g^{(k)T}d^{(k)}}{d^{(k)T}Qd^{(k)}}$$  
&emsp;&emsp;$$x^{(k+1)} = x^{(k)} + \alpha _k d^{(k)}$$

Theorem 10.1 For any starting point $$x^{(0)}$$, the basic conjugate direction algorithm converges to the unique $$x^{*}$$ \(that solves Qx = b\) in n steps; that is, $$x^{(n)} = x^{*}$$  

Lemma 10.2 In the conjugate direction algorithm,   
$$g^{(k+1)T}d^{(i)} = 0$$. For all k, $$0 \le k \le n-1$$, and $$0 \le i \le k$$.  

The conjugate gradient algorithm is summarized below.  
1. Set k := 0; select the initial point $$x^{(0)}$$  
2. &emsp;&emsp;$$ g^{(0)} = \nabla f(x^{(0)})$$. If $$g^{(0)} = 0$$, stop, else set $$d^{(0)} = -g^{(0)}$$.   
3. &emsp;&emsp;$$\alpha _{k} = -\frac{g^{(k)T}d^{(k)}}{d^{(k)T}Qd^{(k)}}$$  
4. &emsp;&emsp;$$ x^{(k+1)} = x^{(k)} + \alpha _k d^{(k)}$$  
5. &emsp;&emsp;$$ g^{(k+1)} = \nabla f(x^{k+1})$$. If $$g^{(k+1)} = 0$$,stop.  
6. &emsp;&emsp;$$\beta _{k} = -\frac{g^{(k+1)T}Qd^{(k)}}{d^{(k)T}Qd^{(k)}}$$   
7. &emsp;&emsp;$$ d^{(k+1)} = -g^{(k+1)} + \beta _k d^{(k)}$$  
8. Set k:= k+1; go to step 3.  

Proposition 10.1 In the conjugate gradient algorithm, the directions $$d^{(0)},d^{(1)},d^{(2)},...,d^{(n-1)}$$ 
 are Q-conjugate.

