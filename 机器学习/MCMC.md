# 马尔科夫链蒙特卡洛方法
[参考这篇文章](https://blog.csdn.net/google19890102/article/details/51755242)
##基本思想
对于一个给定的概率分布P(X)，若要得到其样本，通过上述的马尔科夫链的概念，我们可以构造一个转移矩阵P的马尔科夫链，使得该MC的平稳分布是P(X),这样，无论初始状态是何值，比如是$$x_0$$,那么随着马尔科夫过程的转移，得到了一系列的状态值，如:$$x_0,x_1,...,x_n,x_{n+1},...$$,如果这个马尔科夫过程在第n步已经收敛，那么分布P(X)的样本就是$$x_n,x_{n+1},...$$。  
##细致平衡条件
假设一个各态便利的马尔科夫过程，其转移矩阵是P,分布是$$\pi(x)$$,若满足：  
&emsp;&emsp;$$ \pi(i)P_{i,j} = \pi(j)P_{j,i}$$  
则$$\pi(x)$$是马尔科夫链的平稳分布，上式称为细致平衡条件。  
##Metropolos采样算法
###Metropolos采样算法的基本原理
假设需要从目标概率密度$$p(\theta)$$中进行采样，同时，$$\theta$$满足$$-\infty < \theta < \infty $$.Metropolis采样算法根据马尔科夫链去生成一个序列：  
$$\theta^{(1)} \to \theta^{(2)} \to ...\theta^{(t)} \to$$  
其中，$$\theta^{(t)}$$表示的是马尔科夫链在第t时刻的状态。  
在Metropolis采样算法过程中，首先初始化状态值$$\theta^{(1)}$$，然后利用一个已知的分布$$q(\theta|\theta^{(t-1)})$$生成一个新的候选状态$$\theta^{(*)}$$,随后根据一定的概率选择接受这个新值还是拒绝这个新值，在Metropolos采样中，概率为：  
&emsp;&emsp;$$\alpha = \min(1, \frac{p(\theta^{(*)})}{p(\theta^{(t-1)})})$$  
这样的过程一直持续到采样过程的收敛，当收敛以后，样本$$\theta^{(t)}$$即为目标分布$$P(\theta)$$中的样本。  
###Metropolos采样算法的流程
基于以上的分析，可以总结出如下的Metropolis采样算法的流程  
初始化时间t=1  
设置u的值，并初始化初始状态$$\theta^{(t)} = u$$  
重复以下的过程：  
&emsp;&emsp;令t=t+1
&emsp;&emsp;从已知分布$$q(\theta|\theta^{(t-1)})$$中生成一个候选状态$$\theta^{(*)}$$  
&emsp;&emsp;计算接受的概率：$$\alpha = \min(1, \frac{p(\theta^{(*)})}{p(\theta^{(t-1)})})$$   
&emsp;&emsp;从均匀分布Uniform(0,1)生成一个随机值a.
&emsp;&emsp;如果$$a < \alpha$$,则接受新生成的值：$$\theta^{(t)} = \theta^{(*)}$$;否则$$\theta^{(t)} = \theta^{(t-1)}$$
 直到t=T.
 ###Metropolos采样算法的解释
 
要证明Metropolis采样算法的正确性，最重要的是要证明构造的马尔科夫过程满足细致平衡条件，即：  
&emsp;&emsp;$$ \pi(i)P_{i,j} = \pi(j)P_{j,i}$$   
对于上面的过程，分布为$$p(\theta)$$,从状态i转移到状态j的转移概率为：  
&emsp;&emsp;$$ P_{i,j} = \alpha_{i,j}Q_{i,j}$$  
其中，$$Q_{i,j}$$为上述已知分分布，且是对称的分布$$Q_{i,j} = Q_{j,i}$$。 即:  
&emsp;&emsp;$$q(\theta = \theta^{(t)}|\theta^{(t-1)}) = q(\theta = \theta^{(t-1)}|\theta^{(t)})$$
接下来，我们需要证明Metropolis采样算法中构造的马尔科夫链满足细致平衡条件：  
&emsp;&emsp;$$p(\theta^{(i)}P_{i,j} = p(\theta^{(i)}\alpha_{i,j}Q_{i,j}$$    
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;$$=p(\theta^{(i)}\min(1, \frac{p(\theta^{(j)})}{p(\theta^{(i)})})Q_{i,j}$$  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;$$ =\min(p(\theta^{(i)}Q_{i,j}, p(\theta^{(j)}Q_{i,j})$$  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;$$=p(\theta^{(j)}\min(\frac{p(\theta^{(i)})}{p(\theta^{(j)})},1)Q_{j,i}$$  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;$$ =p(\theta^{(i)}\alpha_{i,j}Q_{i,j}$$  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;$$ =p(\theta^{(j)}P_{j,i}$$  
因此，通过上面方法构造出来的马尔科夫链满足细致平衡条件。  
##MCMC的使用场景
[MCMC——Metropolis-Hasting算法](https://www.cnblogs.com/xbinworld/p/4266146.html)  
[MCMC——Gibbs Sampling算法](https://www.cnblogs.com/xbinworld/p/4266146.html)


#统计推断
贝叶斯方法把参数视为随机变量，这些随机变量具有先验分布，表示这些随机变量在人们心目中的取值。我们可以从贝叶斯的角度，来对正则化进行解释。 
##L1正则化 
当我们认为模型的拟合的残差符合高斯分布，而模型的参数$$\beta_i$$服从独立同分布的拉普拉斯分布，也就是：   
&emsp;&emsp;$$ \mathbf{y}|\beta,\lambda,\sigma \sim N( \mathbf{X}^T\beta,\sigma^2I_{N\times N})$$  
&emsp;&emsp;$$\beta_i |\lambda,\sigma  \sim \displaystyle \prod_{j=1}^p \frac{\lambda}{2\sigma}\exp(-\frac{\lambda}{\sigma}|\beta_j|)$$  
很容易证明，$$\beta |\mathbf{y}, \lambda,\sigma$$的负对数后验概率密度为：  
&emsp;&emsp;$$ \frac{1}{2\sigma^2}||\mathbf{y} - \mathbf{X}\beta||_2^2 + \frac{\lambda}{\sigma}||\beta||_1$$  






