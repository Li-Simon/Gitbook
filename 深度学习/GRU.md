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
$$\hat h_t$$是candidate activation，接收$$x_t,h_{t-1}$$   
$$h_t$$是activation，是GRU的隐层，接收$$h_{t-1},\hat h_{t}$$       
GRU相对于LSTM，它取消了输出门。由更新门与重置门共同控制怎么从上一刻的的隐藏状态到当前的隐藏状态$$h_t$$。        
其中$$r_t$$ 用来控制需要 保留多少之前的记忆，比如如果$$r_t$$ 为0，那么 $$\tilde{h}_t$$只包含当前词的信息。
$$z_t$$控制需要从前一时刻的隐藏层 $$h_{t-1}$$ 中遗忘多少信息，需要加入多少当前时刻的隐藏层信息$$\tilde{h}_t$$,最后得到 $$h_t$$。  
如果reset门取1而update门取1，则退化到RNN。      

![](/assets/GRU_LSTM_Structure.png)  
现在看这图，就清晰很多，i,o,f都是门向量，作用就是控制流过这些门的流量，使得通过向量各个分量的通过门之后，其分量的值变为原来的x倍，$$x \in [0,1]$$是门的系数。就连输出也有一个输出门向量来控制。
 
