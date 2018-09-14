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
$$\kern{4 em}Q(\theta, \theta^{(i)}) = E_z[\log P(Y,Z|\theta)|Y,\theta^{(i)}] = \displaystyle \sum_z P(Y,Z|\theta^{(i)})\log P(Y,Z|\theta)$$  
这里，$$P(Y,Z|\theta^{(i)})$$是在给定
观测数据Y和当前的参数估计$$\theta^{(i)}$$下隐变量数据Z的条件概率分布：  
(3)M步：求使$$Q(\theta, \theta^{(i)})$$极大化的$$\theta$$,确定第i+1次迭代的参数的估计值$$\theta^{(i+1)}$$:   
$$\kern{4 em} \theta^{(i+1)} = arg \max_\theta Q(\theta, \theta^{(i)})$$  
(4)重复第(2)(3)步，直到收敛。    
##高斯混合模型
##隐马尔科夫模型
