# 高斯混合模型与隐马尔科夫模型

HMM类似于量子力学中的路径积分

#### 三硬币模型

三枚硬币A，B, C正面出现的正面的概率是$$\pi,p,q$$.进行如下实验： 先掷硬币A，正面选硬币B，反面选硬币C；然后掷选出的硬币，掷硬币的结果出现正面记作1，反面记作0.独立地重复n次实验，得到一个观察序列如下：  
1,1,0,1,0,0,1,0,1,1  
三硬币模型可以写作：  
$$\kern{4 em} P(y|\theta) = \sum_zP(y,z|\theta) = \sum_zP(z|\theta)P(y|z,\theta)$$  
$$\kern{7 em}  = \pi p^y(1-p)^{1-y} + (1-\pi)q^y(1-q)^{1-y}$$  
$$\Theta = (\pi, p, q)$$是模型参数，随机变量y的数据可以观察，随机变量z的数据不可以观察。

#### 最大似然函数

寻找一组模型参数，使得在该参数下，观测序列出现的概率极大。  
将可观察数据表示为$$Y=(Y_1,Y_2,...,Y_n)^T$$，为观测数据表示为$$\kern{4 em} Z=(Z_1,Z_2,..,Z_n)^T$$.则观察数据的似然函数是：  
$$\kern{4 em} P(Y|\theta) = \sum _ZP(Z|\theta)P(Y|Z,\theta)$$  
$$\kern{7 em}  = \displaystyle \prod _{j=1}^n[\pi p^y(1-p)^{1-y} + (1-\pi)q^y(1-q)^{1-y}]$$  
考虑求模型参数 $$\Theta = (\pi, p, q)$$的极大似然估计， 即：  
$$\kern{4 em} \hat \theta = arg \max_\theta log(P(Y|\theta))$$  
只能通过迭代来求解模型参数。EM算法就是该问题的一种方法。

## EM算法

E步： 计算模型参数$$\pi^{(i)},p^{(i)},q^{(i)}$$下观测数据$$y_j$$来自掷硬币B的概率是\(无论是正面还是方面，都可以用下面公式进行计算\)：  
$$\kern{4 em}u^{(i+1)} = \frac{\pi^{(i)}(p^{(i)})^{y_j}(1-p^{(i)})^{1-y_j})}{\pi^{(i)}(p^{(i)})^{y_j}(1-p^{(i)})^{1-y_j}) + (1-\pi^{(i)})(q^{(i)})^{y_j}(1-q^{(i)})^{1-y_j})}$$  
M步：计算模型参数的新估计值：  
之所以抛硬币B是因为抛硬币A出现了正面，因此$$\pi$$\(抛A出现正面的几率如下计算\)  
$$\kern{4 em}\pi^{(i+1)} = \frac{1}{n}\displaystyle \sum _{j=1}^nu^{(i+1)} $$  
在抛硬币B的前提下，根据抛B得到正面的频率得到P\(B正面出现的概率\)  
$$\kern{4 em}p^{(i+1)} = \frac{\displaystyle \sum _{j=1}^nu^{(i+1)}y_j}{\displaystyle \sum _{j=1}^nu^{(i+1)} }$$  
在抛硬币C的前提下\(1-来自抛B的概率\)，根据抛C得到正面的频率得到P\(C正面出现的概率\)  
$$\kern{4 em}p^{(i+1)} = \frac{\displaystyle \sum _{j=1}^n(1 - u^{(i+1)})y_j}{\displaystyle \sum _{j=1}^n(1 - u^{(i+1)})}$$

## （EM算法）

输入：观察变量数据Y，隐变量数据Z，联合分布$$P(Y,Z|\theta)$$,条件分布$$P(Z|Y,\theta)$$;  
输出： 模型参数$$\theta$$.  
\(1\)选择参数的初始值$$\theta^{(0)}$$,开始迭代；  
\(2\)E步：记$$\theta^{(i)}$$为第i次迭代参数$$\theta$$的估计值，在第i+1次迭代的E步，计算：  
$$\kern{4 em}Q(\theta, \theta^{(i)}) = E_z[\log P(Y,Z|\theta)|Y,\theta^{(i)}] = \displaystyle \sum_z P(Z|Y,\theta^{(i)})\log P(Y,Z|\theta)$$  
这里，$$P(Y,Z|\theta^{(i)})$$是在给定  
观测数据Y和当前的参数估计$$\theta^{(i)}$$下隐变量数据Z的条件概率分布：  
\(3\)M步（求导令其等于0得极大）：求使$$Q(\theta, \theta^{(i)})$$极大化的$$\theta$$,确定第i+1次迭代的参数的估计值$$\theta^{(i+1)}$$:  
$$\kern{4 em} \theta^{(i+1)} = arg \max_\theta Q(\theta, \theta^{(i)})$$  
\(4\)重复第\(2\)\(3\)步，直到收敛。

##### Q函数

完全数据的对数似然函数$$\log P(Y,Z|\theta)$$关于给定观测数据Y和当前参数$$\theta$$下对未观察数据Z的条件概率分布$$\log P(Z|Y,\theta^{(i)})$$的期望成为Q函数，即：  
$$\kern{4 em}Q(\theta, \theta^{(i)}) = E_z[\log P(Y,Z|\theta)|Y,\theta^{(i)}]$$

## 高斯混合模型

高斯混合模型是指的具有如下形式的概率分布模型：  
$$\kern{4 em}P(y|\theta) = \displaystyle \sum _{k=1}^K \alpha_k\phi(y|\theta_k)$$  
其中$$\alpha_k$$是系数$$\alpha_k \ge 0, \displaystyle \sum _{k=1}^K \alpha_k = 1$$;$$\phi(y|\theta_k)$$是高斯分布函数，$$\theta_k = (u_k,\sigma^2_k)$$,  
$$\kern{4 em}P(y|\theta) = \frac{1}{\sqrt{2\pi}\sigma_k}exp(-\frac{(y-u_k)^2}{2\sigma_k^2})$$  
称为第k个分模型。

### 高斯混合模型参数股记得EM算法

可以用EM算法来求解GMM的参数$$\alpha_k,u_k,\sigma_k$$.  
$$\gamma_{jk} = 1$$表示第j个观测来自第k个分模型，$$\gamma_{jk} = 0$$表示第j个观测不是来自第k个分模型。  
有了观察数据$$y_j$$以及未观测数据$$\gamma_{jk}$$,则完全数据是：  
$$\kern{4 em} (y_j,\gamma_{j1},\gamma_{j2},...,\gamma_{jK}),j=1,2,...,K$$  
似然函数为：  
$$\kern{4 em}P(y,\gamma|\theta) = \displaystyle \prod _{j=1}^NP(y_j,\gamma_{j1},\gamma_{j2},...,\gamma_{jK}|\theta)$$  
$$\kern{8 em} = \displaystyle \prod _{k=1}^K\displaystyle \prod _{j=1}^N[\alpha_k\phi(y_j|\theta_k)]^{\gamma_{jk}}$$  
$$\kern{8 em} = \displaystyle \prod _{k=1}^K\alpha_k^{n_k}\displaystyle \prod _{j=1}^N[\phi(y_j|\theta_k)]^{\gamma_{jk}}$$  
$$\kern{8 em} = \displaystyle \prod _{k=1}^K\alpha_k^{n_k}\displaystyle \prod _{j=1}^N[\frac{1}{\sqrt{2\pi}\sigma_k}\exp(-\frac{(y-u_k)^2}{2\sigma_k^2})]^{\gamma_{jk}}$$  
式中$$\displaystyle \sum _{j=1}^N\gamma_{jk} = n_k,\displaystyle \sum _{k=1}^Kn_k = N$$。  
转化为完全数据的对数似然函数。

## 隐马尔科夫模型

### 定义

马尔科夫模型是关于时序的概率模型，描述由一个隐藏的马尔科夫链生成不可观测的状态随机序列，再由各个状态生成一个观测而产生观测随机序列的过程。隐藏的马尔科夫链随机生成的状态的序列成为状态序列（state sequence）;每个状态生成一个观测，而由次产生的观测的随机序列成为观测序列（observation sequence）.序列的每一个位置又可以看成一个时刻。  
马尔科夫模型由初始概率分布，状态转移概率分布以及观测概率分布确定。  
设Q是所有可能的状态集合，V是所有可能的观测的集合。  
$$\kern{8 em} Q = (q_1,q_2,...,q_N), V =(v_1,v_2,...,v_M)$$  
其中N是可能的状态数，M是可能的观测数。  
I是长度为T的状态序列，O是对应的观测序列。  
$$\kern{8 em} I = (i_1,i_2,...,i_T), O =(o_1,o_2,...,o_T)$$  
A是状态转移矩阵：  
$$\kern{8 em} A = [a_{ij}]_{NxN}$$  
其中：  
$$\kern{8 em} a_{ij} = P(i_{t+1}=q_j|i_t = q_i), i =1,2,...,N,j=1,2,..,N$$  
是在t时刻处于$$q_i$$的条件下在时刻t+1转移到$$q_j$$的概率。  
B是观察概率矩阵：  
$$\kern{8 em} A = [b_{j}(k)]_{NxM}$$  
其中：  
$$b_j(k) =P(o_t=v_k|i_t=q_j),k=1,2,..,M;j=1,2,...,N$$  
是在时刻t处于状态$$q_j$$的条件下生成观测$$v_k$$的概率。  
$$\pi$$是初始状态概率向量：  
$$\kern{8 em} \pi = (\pi_i)$$  
其中：  
$$\kern{8 em} \pi_i = P(i_1 = q_i), i=1,2,...,N$$  
是在时刻t=1处于状态$$q_i$$的概率。  
马尔科夫模型$$\lambda$$可以用三元符号来表示：  
$$\kern{8 em} \lambda = (A,B,\pi)$$  
A,B,$$\pi$$称为马尔科夫模型的三要素。

### 马尔科夫模型的两个假设：

\(1\)齐次马尔科夫假设。任一时刻只与前一时刻有关系  
$$\kern{4 em} P(i_t|i_{t-1},o_{t-1},...,i_{1},o_{1}) = P(i_t|i_{t-1}), t=1,2,...,T$$  
\(2\)观测独立性假设：任一时刻的观测只依赖于该时刻的马尔科夫链的状态，而与其他观测以及状态没有关系。  
 $$\kern{4 em} P(o_t|i_{T},o_{T},...,i_{t+1},o_{t+1},i_{t},i_{t-1},o_{t-1},i_{1},o_{1}) = P(o_t|i_{t})$$

### HMM的三个问题

1. 概率计算问题:给定模型$$\lambda = (A,B,\pi)$$,和观测序列$$O=o_1,o_2,...,o_T$$,计算在模型$$\lambda$$下观测序列$$O$$出现的概率$$P(O|\lambda)$$。  
2. 学习问题：已知观测序列$$O=o_1,o_2,...,o_T$$,估计模型$$\lambda = (A,B,\pi)$$,使得$$P(O|\lambda)$$最大。即用极大似然法的方法估计参数。   
3. 预测问题（也称为解码（decoding）问题）：已知观测序列$$O=o_1,o_2,...,o_T$$和模型$$\lambda = (A,B,\pi)$$,求给定观测序列条件概率$$P(I|O)$$最大的序列$$I=(i_1,i_2,...,i_T)$$,即给定观测序列，求最有可能的对应的状态序列。  

### 概率计算问题

#### 直接计算方法：

问题：给定模型$$\lambda = (A,B,\pi)$$,和观测序列$$O=o_1,o_2,...,o_T$$,计算在模型$$\lambda$$下观测序列$$O$$出现的概率$$P(O|\lambda)$$。  
对于状态序列$$I=(i_1,i_2,...,i_T)$$的概率是：$$P(I|\lambda)=\pi_{i_1}a_{i_1i_2}a_{i_2i_3}...a_{i_{T-1}i_T}$$,  
对于上面这种状态序列，产生观测序列$$O=o_1,o_2,...,o_T$$的概率是：  
$$P(O|I,\lambda) = b_{i_1}(o_1)b_{i_2}(o_2)...b_{i_T}(o_T)$$,  
因此I和O的联合概率是：  
$$P(O,I|\lambda) = P(O|I,\lambda)P(I|\lambda)=b_{i_1}(o_1)b_{i_2}(o_2)...b_{i_T}(o_T)\pi_{i_1}a_{i_1i_2}a_{i_2i_3}...a_{i_{T-1}i_T}$$  
对所有可能的I求和，得到：  
$$\kern{4 em} P(O|\lambda)=\sum_IP(O,I|\lambda)$$  
直接计算，时间复杂度是$$O(TN^T)$$.  
为了降低计算的时间复杂度，引入了前向算法。

### 前向算法

给定模型$$\lambda$$，定义到时刻t部分观测序列为$$O=o_1,o_2,...,o_T$$且状态为$$q_i$$的概率为前向概率。记作：  
$$\kern{4 em} \alpha_t(i) = P(o_1,o_2,...,o_t,i_t=q_i|\lambda)$$  
有了前向概率就可以通过递归的方法来计算任何一个观测序列的概率。就如下图所示：  ![](/assets/HMM_Forward_Algo.png)  
上面就是状态数目为5，时间T=4的图。一个问题是，前向算法是否可以转化为矩阵求解问题？  
$$\kern{4 em} \alpha_t = (\alpha_t(1),\alpha_t(2),...,\alpha_t(N))^T$$  
初始状态是$$\pi$$,转移矩阵是A，因此时刻t的概率分布是一个NxM的矩阵，也就是N个状态，每个状态有M个分立值，计算如下：问题是怎么降低运算复杂度？$$N^T$$的复杂度是$$O(N^{2.373}\log T)$$
![](/assets/HMM_FW_Formula.png)
###后向概率
$$\kern{4 em} \beta_t(i) = P(o_{t+1},o_{t+2},...,o_T|i_t=q_i,\lambda)$$  
定义$$\kern{4 em} \beta_T(i) = 1, i=1,2,...,N$$  
对$$t=T-1,T-2,...,1$$有：  
$$\kern{4 em} \beta_t(i) = \displaystyle \sum_{j=1}^Na_{ij}b_j(o_{t+1})\beta_{t+1}(j), i=1,2,...,N$$  
$$\kern{4 em} \beta_t = A^{T-t}\displaystyle \prod_{j=t+1}^TxB[o_j], t=T-1,T-2,...,1$$  
$$\kern{4 em} \beta_t= (\beta_t(1),\beta_t(2),...,\beta_t(N))^T$$  
###一些概率与期望值
1. 给定模型$$\lambda$$以及观测O，在时刻t处于状态$$q_i$$的概率为：  
$$\kern{4 em} \gamma_t(i)= P(i_t=q_i|O,\lambda) = \frac{P(i_t=q_i,O|\lambda)}{P(O|\lambda)}$$  

因为$$\kern{4 em} \alpha_t(i)\beta_t(i) =P(i_t=q_i,O|\lambda)$$  
所以： $$\kern{4 em} \gamma_t(i)=\frac{\alpha_t(i)\beta_t(i)}{\displaystyle \sum_{i=1}^N\alpha_t(i)\beta_t(i)}$$   
2.给定模型$$\lambda$$以及观测O，在时刻t处于状态$$q_i$$且在t+1时刻处以$$q_j$$的概率为：  
$$\kern{4 em} \xi_t(i,j)= P(i_t=q_i,i_{t+1}=g_j|O,\lambda) $$  
$$\kern{4 em} \xi_t(i,j) = \frac{P(i_t=q_i,i_{t+1}=g_j,O|\lambda)}{P(O|\lambda)}= \frac{P(i_t=q_i,i_{t+1}=g_j,O|\lambda)}{\displaystyle \sum_{i=1}^N\displaystyle \sum_{j=1}^NP(i_t=q_i,i_{t+1}=g_j,O|\lambda)}$$  
而：  
$$\kern{4 em} P(i_t=q_i,i_{t+1}=g_j,O|\lambda) = \alpha_t(i)a_{ij}b_j(o_{t+1})\beta_{t+1}(j)$$  
所以：  
$$\kern{4 em} \xi_t(i,j) = \frac{\alpha_t(i)a_{ij}b_j(o_{t+1})\beta_{t+1}(j)}{\displaystyle \sum_{i=1}^N\displaystyle \sum_{j=1}^N\alpha_t(i)a_{ij}b_j(o_{t+1})\beta_{t+1}(j)}$$   
3. 将$$\gamma_t(i),\xi_t(i,j)$$对不同时刻t求和，可以得到一些有用的期望：  
(1)在观测O下状态i出现的期望值：  
$$\kern{8 em} \displaystyle \sum_{i=1}^T\gamma_t(i)$$  
(2)在观测O下由状态i转移的期望值：  
$$\kern{8 em} \displaystyle \sum_{i=1}^{T-1}\gamma_t(i)$$  
(3)在观测O下由状态i转移到状态j的期望值：  
$$\kern{8 em} \displaystyle \sum_{i=1}^{T-1}\xi_t(i,j)$$  
#学习算法
##监督学习方法
我们有观测序列和对应的状态序列$$[(O_1,I_1),(O_2,I_2),...,(O_S,I_S)]$$  
怎么可以通过统计方法来得到转移矩阵A，观测概率B，以及初始状态概率$$\pi$$  
$$\kern{4 em} \hat a_{ij} = \frac{A_{ij}}{\displaystyle \sum_{j=1}^NA_{ij}}, i=1,2,..,N;j=1,2,...,N$$   
$$\kern{4 em} \hat b_j(k) = \frac{B_{jk}}{\displaystyle \sum_{k=1}^MB_{jk}},j=1,2,..,N;k=1,2,...,M$$  
初始状态概率$$\pi_i$$的估计值$$\hat\pi_i$$为S个样本中初始状态为$$q_i$$的频率。  
人工标注的成本很高，因此就会利用非监督学习的方法。  
##Baum-Welch算法
假设给定训练数据只包含S个长度为T的观察序列$$(O_1,O_2,...,O_s)$$而没有对应的状态序列，目标是学习HMM模型$$\lambda = (A,B,\pi)$$的参数。我们将观测序列数据堪称观察数据O,状态序列数据看作不可观测的隐数据I,那么隐马尔科夫模型事实上是一个含有隐变量的概率模型：  
$$\kern{8 em} P(O|\lambda) =\displaystyle \sum_{I}P(O|I,\lambda)P(I|\lambda) $$  
他的参数学习可以由EM算法来实现。  
1. 确定完全数据的对数似然函数   
所有观测数据写成$$O=(o_1,o_2,...,o_T)$$,所有隐数据写成$$I=(i_1,i_2,...,i_T)$$,完成数据是$$(O,I)=(o_1,o_2,...,o_T,i_1,i_2,...,i_T)$$.完全数据的对数似然函数是$$\log P(O,I|\lambda)$$  
2. EM算法的E步，求Q函数$$Q(\lambda,\hat\lambda)$$  
$$\kern{4 em}Q(\lambda,\hat\lambda) = E_I[\log P(O,I|\lambda)|O,\hat \lambda]$$  
$$\kern{4 em}Q(\lambda,\hat\lambda) = \displaystyle \sum_{I}\log P(O,I|\lambda)P(O,I|\hat\lambda)$$   
其中,$$\hat \lambda$$是隐马尔科夫模型参数的当前估计值，$$\lambda$$是要极大化的马尔科夫模型参数。  
$$\kern{4 em} P(O,I|\lambda) =\pi_{i_1}b_{i_1}(o_1)b_{i_2}(o_2)...b_{i_T}(o_T)\pi_{i_1}a_{i_1i_2}a_{i_2i_3}...a_{i_{T-1}i_T}$$  
于是函数$$Q(\lambda,\hat\lambda)$$可以写成：  
$$\kern{4 em}Q(\lambda,\hat\lambda) = \displaystyle \sum_{I}\log \pi_{i_1}P(O,I|\hat\lambda) + \displaystyle \sum_{I}(\displaystyle \sum_{t=1}^{T-1}\log a_{i_ti_{t+1}})P(O,I|\hat \lambda) + \displaystyle \sum_{I}(\displaystyle \sum_{t=1}^{T-1}\log b_{i_t}(o_t))P(O,I|\hat \lambda)$$  
式中求和都是对所有训练数据的序列总长度T进行的。  
3. EM算法的M步：极大化Q函数$$Q(\lambda,\hat\lambda)$$求模型参数A,B,$$\lambda$$。极大化，满足梯度为0，也就对A，B,$$\lambda$$中的元素分别求导令其为0。  
在$$Q(\lambda,\hat\lambda)$$中的三项中，分别只包含了$$\pi,a_{ij},b_j(k)$$,因此求解起来比较方便。此外，我们还可以利用概率和为1的限定条件，也就是利用拉格朗日乘子来进行计算。 
对$$Q(\lambda,\hat\lambda)$$的第一项，我们求$$\lambda$$:  
$$\kern{8 em}\displaystyle \sum_{I}\log \pi_{i_1}P(O,I|\hat\lambda) = \displaystyle \sum_{i=1}^N\log \pi_{i}P(O,i_1 = i|\hat\lambda)$$  
因为$$\pi_i$$满足约束条件$$\displaystyle \sum_{i=1}^N\pi_{i}=1$$,利用拉格朗日乘子，写出拉格朗日函数：   
$$\kern{8 em}\displaystyle \sum_{i=1}^N\log \pi_{i}P(O,i_1 = i|\hat\lambda) + \gamma(\displaystyle \sum_{i=1}^N\pi_{i}-1)$$  
对其求偏导并令其为0：  
$$\kern{8 em} \frac{\partial}{\partial \pi_i}[\displaystyle \sum_{i=1}^N\log \pi_{i}P(O,i_1 = i|\hat\lambda) + \gamma(\displaystyle \sum_{i=1}^N\pi_{i}-1)] = 0$$  
得到：  
$$\kern{8 em} P(O,i_1 = i|\hat\lambda) + \gamma \pi_i = 0$$  
对i求和得到$$\gamma$$:  
$$\kern{8 em} \gamma = -P(O|\hat\lambda) $$  
代入上上式，得到：  
$$\kern{8 em} \pi_i = \frac{P(O,i_1 = i|\hat\lambda) }{P(O|\hat\lambda)}$$    
对$$Q(\lambda,\hat\lambda)$$的第二项，我们求$$a_{ij}$$:  
$$\kern{4 em} \displaystyle \sum_{I}(\displaystyle \sum_{t=1}^{T-1}\log a_{i_ti_{t+1}})P(O,I|\hat \lambda) = \displaystyle \sum_{i=1}^{N}\displaystyle \sum_{j=1}^{T-N}\displaystyle \sum_{t=1}^{T-1}\log a_{ij}P(O,i_t=i,i_{t+1}=j|\hat \lambda)$$  
利用约束条件$$\displaystyle \sum_{i=1}^{N}a_{ij} = 1$$，利用拉格朗日乘子可以得到：  
$$\kern{8 em} a_{ij}= \frac{\sum_{t=1}^{T-1}P(O,i_t=i,i_{t+1}=j|\hat \lambda) }{\sum_{t=1}^{T-1}P(O,i_t=i|\hat \lambda)}$$    
对$$Q(\lambda,\hat\lambda)$$的第三项，我们求$$b_j(k)$$:  
$$\kern{4 em}\displaystyle \sum_{I}(\displaystyle \sum_{t=1}^{T-1}\log b_{i_t}(o_t))P(O,I|\hat \lambda) = \displaystyle \sum_{j=1}^{N}\displaystyle \sum_{t=1}^{T}\log b_{j}(o_t))P(O,i_t=j|\hat \lambda)$$  
利用$$\displaystyle \sum_{k=1}^{M}b_j(k)=1$$. 注意只有在$$o_t = v_k$$时，$$b_j(o_t)$$对$$b_j(k)$$的偏导数才不为0，以$$I(o_t=v_k)$$表示，求得：  
$$\kern{4 em} b_j(k) = \frac{\displaystyle \sum_{t=1}^{T}P(O,i_t=j|\hat \lambda)I(o_t=v_k)}{\displaystyle \sum_{t=1}^{T}P(O,i_t=j|\hat \lambda)}$$   
$$\hat \lambda$$是当前$$(A,B,\pi)$$的估计值，因此可以通过迭代，得到  $$(A,B,\pi)$$的收敛解。  

###Baum-Welch算法
输入：观测数据$$O=(o_1,o_2,...,o_T)$$;  
输出：隐马尔科夫模型的参数  
(1)初始化  
对n=0,选取$$a_{ij}^{(0)},b_j(k)^{(0)},\pi_i^{(0)}$$得到模型$$\lambda^{(0)} = (A^{(0)},B^{(0)},\pi^{(0)})$$  
(2).递推对n=1,2,..,  
$$\kern{8 em} a_{ij}= \frac{\sum_{t=1}^{T-1}\xi_t(i,j)}{\sum_{t=1}^{T-1}\xi_t(i)}$$   
$$\kern{8 em} b_j(k) = \frac{\displaystyle \sum_{t=1,o_t=v_k}^{T}\gamma_t(j)}{\displaystyle \sum_{t=1}^{T}\gamma_t(j)}$$      
$$\kern{8 em} \pi_i = \gamma_1(i)$$    
右端的值按照观测$$O=(o_1,o_2,...,o_T)$$和模型$$\lambda^{(n)} = (A^{(n)},B^{(n)},\pi^{(n)})$$,以及式中$$\xi_t(i,j)$$按照中“一些概率与期望值”中定义进行计算。  
(3)终止，得到模型参数$$\lambda^{(n+1)} = (A^{(n+1)},B^{(n+1)},\pi^{(n+1)})$$
##预测算法
前面已经讨论了给定观测序列$$O=(o_1,o_2,...,o_T)$$的概率计算问题以及通过观测序列学习模型参数问题，还余下HMM三个问题中的给定观测下隐变量的预测问题。  
前面，我们在“一些概率与期望值”中通过前向概率和后向概率，得到了当前模型参数以及观察序列下，某一时刻隐变量的取值概率$$\xi_t(i)$$。  
$$\kern{4 em} \gamma_t(i)=\frac{\alpha_t(i)\beta_t(i)}{\displaystyle \sum_{i=1}^N\alpha_t(i)\beta_t(i)}$$  
计算每一时刻t最可能出现的状态i,然后得到最有可能出现的序列。这就是近似算法.
###近似算法
$$\kern{8 em} i_t^{*} = arg \displaystyle \max_{1\le i\le N}[\gamma_t(i)], t = 1,2,..,T$$  
从而得到状态序列$$I^* = (i_1^*,i_2^*,..,i_T^*)$$  
近似算法简单，但是会预测出一些实际上不发生的状态，比如转移矩阵等于0的两个相邻状态。  



