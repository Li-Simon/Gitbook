# RNN

建模序列化数据的一种主流深度学习模型。

## 设计目的

捕获长距离输入之间的依赖。

###### 背景：

传统的前馈神经网络一般输入的都市一个定长的向量，无法处理变长的序列信息，即使通过一些方法把序列处理成定长的向量，模型也很难捕捉序列中的长距离依赖关系。RNN则通过将神经元串行起来处理序列化的数据。由于每个神经元能用它的内部变量保存之前输入的序列信息，因此整个序列被浓缩成抽象的表示，并可以据此进行分类或生成新的序列。近年来，得益于计算能力的大幅度提升和模型的改进，RNN在很多领域取得了突破性的进展--机器翻译，图像描述，推荐系统，智能聊天机器人，自动作词作曲等。

### 循环神经网络（RNN）

#### 最简单的RNN

![](/assets/RNN_Simple_1.png)

![](/assets/RNN_Simple_2.png)

循环神经网络中一些重要的设计模式包含如下几种：  
\(1\)每个时间步都有输出，并且隐藏单元之间有循环连接的循环网络，如下图所示。  
RNN的输入到隐藏的连接由权值矩阵U参数化，隐藏到隐藏的循环由权重矩阵W参数化，隐藏到输出层的连接由权重矩阵V参数化。$$L^{(t)}$$是损失函数。  
![](/assets/RNN_General.png)  
前向传播公式：假设激活函数是tanh，我们有如下的更新方程：  
  $$ \mathbf{a}^{(t)} = \mathbf{b} + \mathbf{W}\mathbf{h}^{(t-1)} + \mathbf{U}x^{(t)}$$  
  $$ \mathbf{h}^{(t)} = \tanh(\mathbf{a})$$  
  $$ \mathbf{o}^{(t)} = \mathbf{c} + \mathbf{V}\mathbf{h}^{(t)} $$  
  $$\mathbf{\hat y}^{(t)} = softmax(\mathbf{o}^{(t)})$$  
其中$$\mathbf{b},\mathbf{c}$$是偏置向量,$$\mathbf{U},\mathbf{V},\mathbf{W}$$是权重矩阵。  
这一循环网络将一个输入序列映射到相同长度的输出序列。与$$\mathbf{x}$$序列配对的$$\mathbf{y}$$的总的损失就是所有时间步的损失之和。例如，$${L}^{(t)}$$为给定的$$x^{(1)},x^{(2)},...,x^{(t)}$$后$$y^{(t)}$$的负对数似然，则：  
  $$L((x^{(1)},x^{(2)},...,x^{(\tau)}),(y^{(1)},y^{(2)},...,y^{(\tau)})) = \displaystyle \sum_{t} L^{(t)}$$  
  $$ = -\displaystyle \sum_{t} \log p_{model}(y^{(t)}|(x^{(1)},x^{(2)},...,x^{(t)})$$  
其中$$p_{model}(y^{(t)}|(x^{(1)},x^{(2)},...,x^{(t)})$$需要读取模型输出向量$$\mathbf{\hat y}^{(t)}$$对应于$$\mathbf{y}^{(t)}$$的项。  
应用于展开图且代价为$$O(\tau)$$的反向传播算法是通过时间反向传播\(back-propagation through time, BPTT\)。  
\(2\)每个时间步都产生一个输出，只有当前时刻的输出到下个时刻的隐藏单元之间有循环连接的循环网络。如下图所示：  
该图中，RNN被训练将特定输出值放入o中，并且o是被允许传播到未来的唯一信息。此处没有从h前向传播的直接连接。之前的h仅通过产生的预测间接地连接到当前。o通常缺乏过去的重要信息，除非它非常高维并且内容丰富。这使得该图中的RNN不那么强大，但是它更容易训练，因为每个时间步可以与其他时间步分离训练，允许训练期间更多的并行化。

![](/assets/RNN_DesignPattern_2.png)  
\(3\)隐藏单元之间存在循环连接，但读取整个序列后产生单个输出的循环网络，如下图所示：  
这样的网络可以用于概括序列并产生用于进一步处理的固定大小的表示。在结束处可能存在目标，或者通过更下游模块的反向传播来获得输出$$o^{(t)}$$上的梯度。  
![](/assets/RNN_DesignPattern_3.png)

## Clockwork RNNs

CW-RNNs，时钟频率驱动循环神经网络  
![](/assets/CW_RNN_LSTM_result.png)  
上图中，绿色实线是预测结果，蓝色散点是真实结果。每个模型都是对前半部分进行学习，然后预测后半部分。LSTMs模型类似滑动平均，但是CW-RNNs效果更好。其中三个模型的输入层、隐藏层、输出层的节点数都相同，并且只有一个隐藏层，权值都使用均值为0，标准差为0.1的高斯分布进行初始化，隐藏层的初始状态都为0，每一个模型都使用Nesterov-style  momentum SGD\(Stochastic Gradient Descent，随机梯度下降算法\)进行学习与优化

## LSTM

由于Vanilla RNN具有梯度消失问题，对长关系的依赖的建模能力不够强大，也就是很长时刻以前的输入，对现在的网络影响非常小，后向传播那些梯度也很难影响很早以前的输入，即会出现题都消失的问题。而LSTM通过构建一些门，让网络能记住那些非常重要的信息，而这个核心的结构就是cell state。比如遗忘门，来选择性清空过去的记忆和更新较新的信息。  
两种常见的LSTM结构。  
第一种是带遗忘门的Traditional LSTM。公式如下：  
  $$ f_t = \sigma_g(W_fx_t + U_fh_{t-1} + b_f)$$  
  $$ i_t = \sigma_g(W_ix_t + U_ih_{t-1} + b_i)$$  
  $$ o_t = \sigma_g(W_ox_t + U_oh_{t-1} + b_o)$$  
  $$ c_t = f_t*c_{t-1} + i_t*\sigma_c(W_cx_t + U_ch_{t-1} + b_c)$$  
  $$ h_t = o_t*\sigma_h(c_t)$$  
前三行是三个门，分别是遗忘门f,输入门i,输出门o,输入都是$$x_t,h_{t-1}$$,只是参数不同，然后要经过一个激活函数把值缩放到\[0,1\]之间，第四行$$c_t$$是cell state,由上一时刻的$$c_{t-1}$$和输入得到,两者相互独立。如果遗忘门$$f_t$$取0的话，那么上一时刻的状态就会全部被清空，然后只关注此时刻的输入。输入门$$i_t$$决定是否接收此时刻的输入，最后输出门$$o_t$$决定是否输出cell state。  
  $$\hat c = \sigma_c(W_cx_t + U_ch_{t-1} + b_c)$$  
因此有$$c_t = f_t*c_{t-1} + i_t*\hat c$$.  
这样一来cell state的更新来源就明显了，一部分是上时刻的自己，一部分是new memory content，而且两个来源是相互独立地由两个门控制的。遗忘门控制是否记住以前的那些特征，输入们决定是否接受当前的输入。后面可以看到GRU其实把这两个门合二为一了。  
第二种是带遗忘门的Peephole LSTM，公式如下：  
  $$ f_t = \sigma_g(W_fx_t + U_fc_{t-1} + b_f)$$  
  $$i_t = \sigma_g(W_ix_t + U_ic_{t-1} + b_i)$$  
  $$ o_t = \sigma_g(W_ox_t + U_oc_{t-1} + b_o)$$  
  $$c_t = f_t*c_{t-1} + i_t*\sigma_c(W_cx_t + b_c)$$  
  $$ h_t = o_t*\sigma_h(c_t)$$  
和上面的公式比较，发现只是把$$h_{t-1}$$换成了$$c_{t-1}$$，即三个门的输入都改成了\[$$x_t,c_{t-1}$$\],因为是从cell state里取得信息，所以叫窥视管\(peephole\)。  
把这两种结构结合起来，可以用如下图描述：  
![](/assets/LSTM_Structure.png)

图中连着门的那些虚线都市peephole。三个输入都是\[$$x_t,h_{t-1},c_{t-1}$$\]

## [GRU](https://blog.csdn.net/zhangxb35/article/details/70060295)

参考[循环神经网络\(RNN, Recurrent Neural Networks\)介绍](https://blog.csdn.net/heyongluoyao8/article/details/48636251)  
GRU这个结构2014年才出现，结构与LSTM类似，效果一样，但是精简一些，参数更少。公式如下：  
  $$ z_t = \sigma(W_zx_t + U_zh_{t-1})$$  
  $$ r_t = \sigma(W_rx_t + U_rh_{t-1})$$  
  $$ \hat h_t = \tanh(Wx_t + U(r_t*h_{t-1}))$$  
  $$h_t = (1-z_t)*h_{t-1} + z_t*\hat h_t$$  
四行的解释如下：  
  $$z_t$$是update gate，更新activation时的逻辑门。  
  $$r_t$$是reset gate，决定candidate activation时，是否要放弃以前的activate $$h_t$$  
  $$\hat h_t$$是candidate activation，接收\[$$x_t,h_{t-1}$$\]  
  $$h_t$$是activation，是GRU的隐层，接收\[$$h_{t-1},\hat h_{t}$$\].

![](/assets/GRU_LSTM_Structure.png)

从LSTM和GRU的公式里面可以看出，都会有门操作，决定是否保留上时刻的状态和是否接收此时刻的外部输入，LSTM是用遗忘门和输入门来做到的，GRU则是只用一个更新门\($$z_t$$\)。  
这种设计有两种解释，一种解释是说，网络是能很容易记住长依赖问题。即前面很久之前出现过一个重要的特征，如果遗忘门或者更新门选择不重写内部的memory，那么网络就会一直记住之前的重要特征，那么会对当前或者未来继续产生影响。另一点是，这种设计可以不同状态之间提供一条捷径，那么梯度回传的时候不会消失的太快，因此减缓了梯度消失带来的训练难问题。  
LSTM 和GRU的不同点。首先LSTM有一个输出门来控制memory content的曝光程度，而GRU则是直接输出。另外一点是要更新的new memory content的来源不同，$$\hat h_t$$会通过重置门控制从$$h_{t-1}$$中得到信息的力度，而$$\hat c_t$$则没有，而是直接输入$$h_{t-1}$$。

## Seq2Seq

## 注意力机制



