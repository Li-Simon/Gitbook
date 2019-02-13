## LSTM

由于Vanilla RNN具有梯度消失问题，对长关系的依赖的建模能力不够强大，也就是很长时刻以前的输入，对现在的网络影响非常小，后向传播那些梯度也很难影响很早以前的输入，即会出现题都消失的问题。而LSTM通过构建一些门，让网络能记住那些非常重要的信息，而这个核心的结构就是cell state。比如遗忘门，来选择性清空过去的记忆和更新较新的信息。  
两种常见的LSTM结构。  
第一种是带遗忘门的Traditional LSTM。  

![](/assets/LSTM_1.png)   
公式如下：  
  $$ f_t = \sigma_g(W_fx_t + U_fh_{t-1} + b_f)$$  
  $$ i_t = \sigma_g(W_ix_t + U_ih_{t-1} + b_i)$$  
  $$ o_t = \sigma_g(W_ox_t + U_oh_{t-1} + b_o)$$  
  $$ c_t = f_t*c_{t-1} + i_t*\sigma_c(W_cx_t + U_ch_{t-1} + b_c)$$  
  $$ h_t = o_t*\sigma_h(c_t)$$    
"*"表示向量中对应元素相乘。$$c_t$$是cell中t时刻保存的信息，$$h_t$$表示t时刻的输出。$$f_t,i_t, o_t, c_t, h_t$$都是向量。  
前三行是三个门，分别是遗忘门f,输入门i,输出门o,输入都是$$x_t,h_{t-1}$$,只是参数不同，然后要经过一个激活函数把值缩放到\[0,1\]之间。  
第四行 $$c_t$$是cell state,由上一时刻的$$c_{t-1}$$和输入得到,两者相互独立。如果遗忘门$$f_t$$取0的话，也就是调节参数$$W_f, U_f$$使得对于任意的输入$$x_t$$与上一次的输出$$h_{t-1}$$都有$$f_t$$趋于0向量，那么上一时刻的状态就会全部被清空，然后只关注此时刻的输入，这与传统的RNN相似，只是多了一个$$\sigma_h$$操作。输入门$$i_t$$决定是否接收此时刻的输入。  最后输出门$$o_t$$决定是否输出cell state。  
$$\hat c = \sigma_c(W_cx_t + U_ch_{t-1} + b_c)$$
因此有$$c_t = f_t*c_{t-1} + i_t *\hat c$$.  
这样一来cell state的更新来源就明显了，一部分是上时刻的自己，一部分是new memory content，而且两个来源是相互独立地由两个门控制的。遗忘门控制是否记住以前的那些特征，输入们决定是否接受当前的输入。后面可以看到GRU其实把这两个门合二为一了。

#### 总结

加入输入门与遗忘门，就是为了控制上一时刻与当前时刻的内容在cell state $$c_t$$中的比列，$$f_t, i_t$$的值介于\[0,1\],当取0的时候，就表示对应的内容不添加在cell state中。 因此，当前cell state的内容由上一时刻cell state中的内容以及这一时刻的输入决定[^2]。  

### Peephole LSTM

第二种是带遗忘门的Peephole LSTM，公式如下：  
  $$f_t = \sigma_g(W_fx_t + U_fc_{t-1} + b_f)$$  
  $$i_t = \sigma_g(W_ix_t + U_ic_{t-1} + b_i)$$  
  $$o_t = \sigma_g(W_ox_t + U_oc_{t-1} + b_o)$$  
  $$c_t = f_t*c_{t-1} + i_t*\sigma_c(W_cx_t + b_c)$$  
  $$h_t = o_t*\sigma_h(c_t)$$  
和上面的公式比较，发现只是把$$h_{t-1}$$换成了$$c_{t-1}$$，即三个门的输入都改成了\[$$x_t,c_{t-1}$$\],因为是从cell state里取得信息，所以叫窥视管\(peephole\)。  
把这两种结构结合起来，可以用如下图描述：  
![](/assets/LSTM_Structure.png)

图中连着门的那些虚线都市peephole。三个输入都是$$x_t,h_{t-1},c_{t-1}$$

