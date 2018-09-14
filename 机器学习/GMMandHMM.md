# 高斯混合模型与隐马尔科夫模型


####三硬币模型
三枚硬币A，B, C正面出现的正面的概率是$$\pi,p,q$$.进行如下实验： 先掷硬币A，正面选硬币B，反面选硬币C；然后掷选出的硬币，掷硬币的结果出现正面记作1，反面记作0.独立地重复n次实验，得到一个观察序列如下：  
1,1,0,1,0,0,1,0,1,1  
三硬币模型可以写作：  
$$\kern{4 em} P(y|\theta) = \sum_zP(y,z|\theta) = \sum_zP(z|\theta)P(y|z,\theta)$$  
$$\kern{7 em}  = \pi p^y(1-p)^{1-y} + (1-\pi)q^y(1-q)^{1-y}$$  
$$\Theta = (\pi, p, q)$$是模型参数，随机变量y的数据可以观察，随机变量z的数据不可以观察。  
####最大似然函数
寻找一组模型参数，使得在该参数下，观测序列出现的概率极大。  
将可观察数据表示为$$Y=(Y_1,Y_2,...,Y_n)^T$$，为观测数据表示为$$\kern{4 em} Z=(Z_1,Z_2,..,Z_n)^T$$.则观察数据的似然函数是：  
$$\kern{4 em} P(Y|\theta) = \sum _ZP(Z|\theta)P(Y|Z,\theta)$$  
$$\kern{7 em}  = \displaystyle \prod _{j=1}^n[\pi p^y(1-p)^{1-y} + (1-\pi)q^y(1-q)^{1-y}]$$  
考虑求模型参数 $$\Theta = (\pi, p, q)$$的极大似然估计， 即：  
$$\kern{4 em} \hat \theta = arg \max_\theta log(P(Y|\theta))$$  
只能通过迭代来求解模型参数。EM算法就是该问题的一种方法。  
##EM算法
E步： 计算模型参数$$\pi^{(i)},p^{(i)},q^{(i)}$$下观测数据$$y_j$$来自掷硬币B的概率是(无论是正面还是方面，都可以用下面公式进行计算)：  
$$\kern{4 em}u^{(i+1)} = \frac{\pi^{(i)}(p^{(i)})^{y_j}(1-p^{(i)})^{1-y_j})}{\pi^{(i)}(p^{(i)})^{y_j}(1-p^{(i)})^{1-y_j}) + (1-\pi^{(i)})(q^{(i)})^{y_j}(1-q^{(i)})^{1-y_j})}$$  
M步：计算模型参数的新估计值：  
之所以抛硬币B是因为抛硬币A出现了正面，因此$$\pi$$(抛A出现正面的几率如下计算)  
$$\kern{4 em}\pi^{(i+1)} = \frac{1}{n}\displaystyle \sum _{j=1}^nu^{(i+1)} $$  
在抛硬币B的前提下，根据抛B得到正面的频率得到P(B正面出现的概率)
$$\kern{4 em}p^{(i+1)} = \frac{\displaystyle \sum _{j=1}^nu^{(i+1)}y_j}{\displaystyle \sum _{j=1}^nu^{(i+1)} }$$  
在抛硬币C的前提下(1-来自抛B的概率)，根据抛C得到正面的频率得到P(C正面出现的概率)
$$\kern{4 em}p^{(i+1)} = \frac{\displaystyle \sum _{j=1}^n(1 - u^{(i+1)})y_j}{\displaystyle \sum _{j=1}^n(1 - u^{(i+1)})}$$  
##（EM算法）
输入：观察变量数据Y，隐变量数据Z，联合分布$$P(Y,Z|\theta)$$,条件分布$$P(Z|Y,\theta)$$;  
输出： 模型参数$$\theta$$.  
(1)选择参数的初始值$$\theta^{(0)}$$,开始迭代；  
(2)E步：记$$\theta^{(i)}$$为第i次迭代参数$$\theta$$的估计值，在第i+1次迭代的E步，计算：  
$$\kern{4 em}Q(\theta, \theta^{(i)}) = E_z[\log P(Y,Z|\theta)|Y,\theta^{(i)}] = \displaystyle \sum_z P(Z|Y,\theta^{(i)})\log P(Y,Z|\theta)$$  
这里，$$P(Y,Z|\theta^{(i)})$$是在给定
观测数据Y和当前的参数估计$$\theta^{(i)}$$下隐变量数据Z的条件概率分布：  
(3)M步（求导令其等于0得极大）：求使$$Q(\theta, \theta^{(i)})$$极大化的$$\theta$$,确定第i+1次迭代的参数的估计值$$\theta^{(i+1)}$$:   
$$\kern{4 em} \theta^{(i+1)} = arg \max_\theta Q(\theta, \theta^{(i)})$$  
(4)重复第(2)(3)步，直到收敛。    
#####Q函数
完全数据的对数似然函数$$\log P(Y,Z|\theta)$$关于给定观测数据Y和当前参数$$\theta$$下对未观察数据Z的条件概率分布$$\log P(Z|Y,\theta^{(i)})$$的期望成为Q函数，即：  
$$\kern{4 em}Q(\theta, \theta^{(i)}) = E_z[\log P(Y,Z|\theta)|Y,\theta^{(i)}]$$
##高斯混合模型
高斯混合模型是指的具有如下形式的概率分布模型：  
$$\kern{4 em}P(y|\theta) = \displaystyle \sum _{k=1}^K \alpha_k\phi(y|\theta_k)$$  
其中$$\alpha_k$$是系数$$\alpha_k \ge 0, \displaystyle \sum _{k=1}^K \alpha_k = 1$$;$$\phi(y|\theta_k)$$是高斯分布函数，$$\theta_k = (u_k,\sigma^2_k)$$,  
$$\kern{4 em}P(y|\theta) = \frac{1}{\sqrt{2\pi}\sigma_k}exp(-\frac{(y-u_k)^2}{2\sigma_k^2})$$  
称为第k个分模型。  
###高斯混合模型参数股记得EM算法
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

##隐马尔科夫模型
###定义
马尔科夫模型是关于时序的概率模型，描述由一个隐藏的马尔科夫链生成不可观测的状态随机序列，再由各个状态生成一个观测而产生观测随机序列的过程。隐藏的马尔科夫链随机生成的状态的序列成为状态序列（state sequence）;每个状态生成一个观测，而由次产生的观测的随机序列成为观测序列（observation sequence）.序列的每一个位置又可以看成一个时刻。  
马尔科夫模型由初始概率分布，状态转移概率分布以及观测概率分布确定。  
