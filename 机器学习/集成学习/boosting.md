#Boosting
Boosting系列方法的原理图如下：

![](/assets/Boosting.png)

#### AdaBoost

Boosting系列算法的代表就是AdaBoost。  
算法如下：  
输入：训练数据集 $$T = ((x_1, y_1),(x_2, y_2)...(x_N, y_N))$$,其中$$x_i \in X \subseteq R^{n}, y \in (-1, +1)$$  
输出： 最终的分类器G\(x\)  
\(1\)初始化训练数据集的权重分布  
&emsp;&emsp;$$D_1 = (w_{11},...,w_{1i},...,w_{1N})$$,  
&emsp;&emsp;$$w_{1i} = \frac{1}{N}, i =1, 2,...,N$$  
\(2\)对m=1,2,...,M  
使用具有权值分布$$D_{m}$$的训练数据集进行训练，得到基分类器  
&emsp;&emsp;$$G_m(x): \chi \in (-1, +1)$$  
\(b\)计算$$G_m(x)G_m(x)$$在训练集上的分类误差率：  
&emsp;&emsp;$$e_m = P(G_m(x_i) \ne y_i) = \displaystyle\sum_{i=1}^N w_{mi}I(G_m(x_i) \ne y_i)$$  
\(c\)计算$$G_m(x)$$的系数  
&emsp;&emsp;$$\alpha _m = \frac{1}{2}\log \frac{1-e_m}{e_m}$$  
这里用的是自然对数。  
\(d\)更新训练数据集的权值分布：  
&emsp;&emsp;$$D_1 = (w_{m+1,1},...,w_{m+1,i},...,w_{m+1,N})$$,  
&emsp;&emsp;$$w_{m+1,i} = \frac{w_{mi}}{Z_m}exp(-\alpha _m y_i G_m(x_i)), i =1, 2,...,N$$  
这里，$$Z_m$$是归一化因子：  
&emsp;&emsp;$$Z_m =\displaystyle\sum_{i=1}^N w_{mi}exp(-\alpha _m y_i G_m(x_i))$$  
它使$$D_{m+1}$$成为一个概率分布。  
\(3\)构建基本分类器的线性组合：  
&emsp;&emsp;$$ f(x) = \displaystyle\sum_{i=1}^N \alpha _m G_m(x)$$  
得到最终分类器  
&emsp;&emsp;$$ G(x) = sign(f(x)) = sign(\displaystyle\sum_{i=1}^N \alpha _m G_m(x))$$  
由$$\alpha _m$$的定义可以知道，第m个分类器的误差率越小，则$$\alpha _m$$的值越大，因此第m个分类器在总的分类器中占的比重越大。因此，AdaBoost会加大那些准确率很高的分类器的权重。  
同时，在第m+1个分类器求解时，对于上一轮被分错的样本的权值会变大。  
不改变所给的训练数据，而不断的改变训练数据权值的分布，使得训练数据在基本分类器的学习中起不同的作用，这是AdaBoost的一个特点。  
关键的两点：  
1. 加大上一轮分错的样本的权重。  
2. 加大分类错误率低的基分类器的权重。  
可以参考《统计机器学习》8.1节的例子来加深理解。

##### AdaBoost算法的训练误差分析

定理：**\(AdaBoost的训练误差界\)**  
AdaBoost 算法最终分类器的训练误差界为：  
&emsp;&emsp;$$\frac{1}{N}\displaystyle\sum_{i=1}^N I(G_m(x_i) \ne y_i) \le \frac{1}{N} \displaystyle\sum_{i=1}^N exp(-y_if(x_i)) = \displaystyle \prod_{m} Z_m$$

定理**\(二分类问题AdaBoost的训练误差界\)**  
&emsp;&emsp;$$ \displaystyle \prod_{m} Z\_m = \displaystyle \prod_{m=1}^{M}[2\sqrt{e_m(1-e_m)}] =   
\displaystyle \prod_{m=1}^{M}\sqrt{1 - 4\gamma _m^2} \le exp(-2\displaystyle \sum_{m=1}^{M}\gamma \_m^2)$$  
其中： $$\gamma _m = \frac{1}{2} - e_m$$

#### 梯度提升

提升树是以分类树或者回归树为基本分类器的提升方法，提升树被认为是统计学习中性能最好的方法之一。  
  提升树实际采用加法模型\(即基函数的线性组合\)与前向分步算法。 以决策树为基函数的提升方法称为提升树。 对分类问题决策树是二叉分类树，对回归问题决策树是二叉回归树。  
  决策树桩\(decsion stump\)：可以看成是一个根节点直接连接两个叶节点的简单决策树。  提升树模型可以表示为决策树的加法模型。  
  &emsp;&emsp;$$ f_M(x) = \displaystyle \sum_{m=1}^{M}T(x;\Theta_m)$$  
  其中：$$T(x, \Theta_m)$$表示决策树；$$\Theta_m$$为决策树的参数；M为树的个数。

梯度提升算法：  
提升树算法采用前向分步算法。首先缺点初始提升树$$f_0(x)=0$$,第m步的模型是:  
&emsp;&emsp;$$f_m(x) = f_{m-1}(x) + T(x;\Theta_m)$$  
其中，$$f_{m-1}(x)$$为当前模型，通过经验风险极小化来确定下一刻决策树的参数$$\Theta_m$$  
&emsp;&emsp;$$ \hat \Theta_m = arg min_{\Theta_m} \sum_{i=1}^NL(y_i,f_{m-1}(x_i)+T(x_i;\Theta_m))$$.  
对于一个训练数据集 $$T=((x_1,y_1),(x_2,y_2),...,(x_N,y_N)),x_i \in \chi \in R^N$$, $$\chi$$为输入控件， $$y_i \in R$$,为输出空间。如果将输入空间$$\chi$$划分为J个互不相交的区域$$R_1,R_2,...,R_J$$，并且在每个区域上确定输出的常量$$c_j$$，那么树可以表示为：  
&emsp;&emsp;$$T(x;\theta)= \displaystyle \sum_{j=1}^J c_j I(x\in R_j)$$.  
其中，参数$$\Theta = ((R_1,c_1),(R_2,c_2),...,(R_J,c_J))$$表示树的区域划分和各区域上的常数。J是回归树的复杂度，即叶节点个数。  
回归问题提升树使用以下前向分步算法：  
&emsp;&emsp;$$f_0(x) = 0$$  
&emsp;&emsp;$$f_m(x) = f_{m-1}(x) + T(x;\Theta_m), m=1,2,...,M$$  
&emsp;&emsp;$$f_m(x) = \displaystyle \sum_{m=1}^M T(x;\Theta_m) $$  
在前向分步算法的第m步，给定当前模型$$f_{m-1}(x)$$，需求解：  
&emsp;&emsp;$$\hat \Theta_m = arg min_{\Theta_m} \sum_{i=1}^NL(y_i,f_{m-1}(x_i)+T(x_i;\Theta_m))$$.  
得到$$\hat \Theta_m$$，即第m颗树的参数。  
采用平方误差损失函数时：  
&emsp;&emsp;$$  L(y,f(x)) = (y-f(x))^2$$  
其损失变成：  
&emsp;&emsp;$$ L(y,f_{m-1}(x) + T(x;\Theta_m)) = (y-f_{m-1}(x) - T(x;\Theta_m))^2 = [r - T(x;\Theta_m)]^2$$  
这里，  
 &emsp;&emsp;$$ r = y-f_{m-1}(x)$$  
  是当前模型拟合数据的残差。所以，对回归问题的提升树算法来说，只需要简单地拟合当前模型的残差，也就是下一步只是拟合前面一步的残差，类似于Resi-Net。

##### GBDT

当损失函数是平方损失和指数损失函数时，每一步优化是很简单的，但是对于一般损失函数而言，往往每一步优化并不容易。针对这一问题，Freidman提出了梯度梯度提升\(gradient boosting\)算法,这是利用最速下降法的近似方法，其关键是利用损失函数的负梯度在当前模型残差的近似值。而在平方损失中，拟合的是残差，在这里拟合的是模型上一步的梯度。   
&emsp;&emsp;$$ -[\frac{\partial L(y, f(x_i))}{\partial f(x_i)}]_{f(x)=f_{m-1}(x)}$$  
作为回归问题提升算法中的残差的近似值，拟合一个回归树。  
梯度提升树算法  
输入： 训练数据集 $$T=((x_1,y_1),(x_2,y_2),...,(x_N,y_N)),x_i \in \chi \in R^N$$, $$\chi$$为输入， $$y_i \in R$$，损失函数为$$L(y,f(x))$$:  
输出： 回归树$$\hat f(x)$$.  
\(1\)初始化  
&emsp;&emsp;$$f_0(x) = arg min_{c} \displaystyle\sum_{i=1}^NL(y_i,c)$$.  
\(2\)对m=1,2,...,M  
\(a\)对i=1,2,...,N，计算  
&emsp;&emsp;$$ r_{mi} = -[\frac{\partial L(y, f(x_i))}{\partial f(x_i)}]_{f(x)=f_{m-1}(x)}$$  
（b）对$$r_{mi}$$拟合一个回归树，得到第m课树叶节点区域$$R_{my},j=1,2,..,J$$  
\(c\)对j=1,2,..,J, 计算  
&emsp;&emsp;$$c_{mj} = arg min_{c} \displaystyle \sum_{x_i \in R_{mj}}L(y_i,f_{m-1}(x_i)+c)$$.  
\(d\)更新$$f_m(x) = f_{m-1}(x) + \displaystyle \sum_{j=1}^Jc_{mj}I(x \in R_{mj}), m=1,2,...,M$$  
\(3\)得到回归树  
&emsp;&emsp;$$\hat f(x) = f_M(x) = \displaystyle \sum_{m=1}^M\displaystyle \sum_{j=1}^Jc_{mj}I(x \in R_{mj})$$

函数空间的数值优化：

#### XGBoost[^1]

模型复杂度惩罚是XGBoost相对于MART的提升。  
&emsp;&emsp;$$= \displaystyle \sum_{m=1}^M[\gamma T_m + \frac{1}{2}\lambda ||w_m||^2_2 + \alpha ||w_m||_1 ]$$  
MART includes row subsampling, while XGBoost includes both row and column  
subsampling

###### Newton boosting

Input: Data set D, A loss function L, A base learner $$L_\Phi$$, the number of iterations M. The learning rate $$\eta$$  
1. Initialize $$\hat f^{(0)}(x) = \hat f_{(0)}(x) = \hat \theta_0 = arg min_\theta \displaystyle \sum_{i=1}^n L(y_i, \theta)$$;  
2. for m = 1,2,...,M do  
3. $$\hat g_m(x_i) = [\frac{\partial L(y, f(x_i))}{\partial f(x_i)}]_{f(x)=f^{(m-1)}(x)}$$  
4. $$\hat h_m(x_i) = [\frac{\partial^2 L(y, f(x_i))}{\partial f(x_i)^2}]_{f(x)=f^{(m-1)}(x)}$$  
5. $$\hat \phi_m = arg min_{\phi \in \Phi} \displaystyle \sum_{i=1}^n \frac{1}{2}\hat h_m(x_i)[(-\frac{\hat g_m(x_i)}{\hat h_m(x_i)}) - \phi(x_i)]^2$$  
6. $$\hat f_m(x) = \eta \hat\phi_m(x)$$;  
7. $$\hat f^m(x) = \hat f^{(m-1)}(x) + \hat f_m(x)$$;  
8. end  
Output: $$\hat f(x) = \hat g^{(M)}(x) = \displaystyle \sum_{m=1}^M\hat f_m(x)$$

对于没有惩罚项的Netwon tree boosting\(NTB\),每一次迭代都市最小化如下损失函数：  
&emsp;&emsp;$$J_m(\phi_m) = \displaystyle \sum_{i=1}^nL(y_i, \hat f^{(m-1)(x_i)}+\phi_m(x_i))$$  
对于梯度提升算法，基函数是如下的树：  
&emsp;&emsp;$$ \phi_m(x) = \displaystyle \sum_{j=1}^Tw_{jm}I(x \in R_{jm})$$  
这里的T是第m颗树叶子节点的个数，$$w_jm$$是第m颗树中第j个叶子节点的权重。  
对上式进行二阶泰勒展开,并忽略掉常数项可以得到：  
&emsp;&emsp;$$J_m(\phi_m) = \displaystyle \sum_{i=1}^n[\hat g_m(x_i)\phi_m(x_i) +\frac{1}{2}\hat h_m(x_i)\phi_m(x_i)^2]$$  
代入：  
&emsp;&emsp;$$\phi_m(x) = \displaystyle \sum_{j=1}^Tw_{jm}I(x \in R_{jm})$$  
&emsp;&emsp;$$J_m(\phi_m) = \displaystyle \sum_{i=1}^n[\hat g_m(x_i)\displaystyle \sum_{j=1}^Tw_{jm}I(x \in R_{jm}) +\frac{1}{2}\hat h_m(x_i)(\displaystyle \sum_{j=1}^Tw_{jm}I(x \in R_{jm}))^2]$$  
由于每个样本点只能属于一个叶子节点，因此：  
&emsp;&emsp;$$I(x \in R_{jm})I(x \in R_{im}) = \delta_{ij}$$  
因此上面可以简化成：  
&emsp;&emsp;$$J_m(\phi_m) = \displaystyle \sum_{i=1}^n[\hat g_m(x_i)\displaystyle \sum_{j=1}^Tw_{jm}I(x \in R_{jm}) +\frac{1}{2}\hat h_m(x_i)\displaystyle \sum_{j=1}^Tw_{jm}^2I(x \in R_{jm})]$$  
&emsp;&emsp;$$ = \displaystyle \sum_{j=1}^T\displaystyle \sum_{i\in I_{jm}}[\hat g_m(x_i)w_{jm} + \frac{1}{2}\hat h_m(x_i)w_{jm}^2]$$  
定义：  
&emsp;&emsp;$$ G_{jm} = \displaystyle  \sum_{i \in I_{jm}} \hat g_m(x_i)$$  
&emsp;&emsp;$$ H_{jm} = \displaystyle  \sum_{i \in I_{jm}} \hat h_m(x_i)$$  
因此，可以把cost function写成：  
&emsp;&emsp;$$J_m(\phi_m) = \displaystyle \sum_{j=1}^T[G_{jm}w_{jm} + \frac{1}{2}H_{jm}w_{jm}^2]$$  
&emsp;&emsp;&emsp;&emsp;$$ \ge -\displaystyle \sum_{j=1}^T\frac{1}{2}\frac{G_{jm}^2}{H_{jm}}$$  
成立条件是：  
&emsp;&emsp;$$w_{jm} = -\frac{G_{jm}}{H_{jm}}, j=1,2...,T$$  
为了寻找最佳分裂点j，也就是最大化如下的Gain:  
&emsp;&emsp;$$Gain = \frac{1}{2}[\frac{G_{L}^2}{H_{L}} + \frac{G_{R}^2}{H_{R}} - \frac{G_{jm}^2}{H_{jm}}]$$  
总结起来：Newton tree boosting算法如下：  
Input: Data set D, A loss function L, A base learner $$L_\Phi$$, the number of iterations M. The learning rate $$\eta$$  
1. Initialize $$\hat f^{(0)}(x) = \hat f_{(0)}(x) = \hat \theta_0 = arg min_\theta \displaystyle \sum_{i=1}^n L(y_i, \theta)$$;  
2. for m = 1,2,...,M do  
3. $$\hat g_m(x_i) = [\frac{\partial L(y, f(x_i))}{\partial f(x_i)}]_{f(x)=f^{(m-1)}(x)}$$  
4. $$\hat h_m(x_i) = [\frac{\partial^2 L(y, f(x_i))}{\partial f(x_i)^2}]_{f(x)=f^{(m-1)}(x)}$$  
5. Determin the structure $$\hat R_{jm}, j=1,...,T$$ by selecting splits which maximize  
&emsp;&emsp;$$ Gain = \frac{1}{2}[\frac{G_{L}^2}{H_{L}} + \frac{G_{R}^2}{H_{R}} - \frac{G_{jm}^2}{H_{jm}}]$$  
6. Determine the leaf weights $$w_{jm}, j=1,...,T$$   for the learnt structure by  
&emsp;&emsp;$$\hat w_{jm} = -\frac{G_{jm}}{H_{jm}}, j=1,2...,T$$  
7. $$\hat f_m(x) = \eta \displaystyle \sum_{j=1}^T \hat w_{jm}I(x \in \hat R_{jm})$$;  
8. $$\hat f^m(x) = \hat f^{(m-1)}(x) + \hat f_m(x)$$;  
9. end  
Output: $$\hat f(x) = \hat g^{(M)}(x) = \displaystyle \sum_{m=1}^M\hat f_m(x)$$


