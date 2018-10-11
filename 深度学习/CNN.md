#CNN
CNN主要是处理空间数据，比如图像数据。CNN主要包含LetNet-5,AlexNet,GoogLeNet,VGG,Residual Net,Dense Net。  
####CNN相对于全连接网络的好处
####CNN的卷积核与特征提取
####CNN的卷积核大小为啥是奇数?
不能保持对称性，比如原来图像长度宽是MxM，卷积核大小是nxn，则卷积作用后图像大小是(M-n+1)x(M-n+1)，如果n是偶数，则n-1是奇数，因此处理后的图像不再对称了。  
####CNN两层之间如何连接
####CNN的pooling的作用