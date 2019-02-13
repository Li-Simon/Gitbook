## VGG

相对于以前的网络而言，VGG与GoogLeNet的网络变得更深了。VGGNet在整个网络中使用3x3的小感受野，以步长1进行逐像素卷积，因此两个3x3卷积相当于一个5x5,三个3x3卷积核相当于一个7x7的卷积核，这样大大减小了模型的参数个数。  使用了小尺寸的卷积核，增加了网络深度并不会带来明显的参数膨胀，却能在更深的网络中获得更高的精度。  
####VGG结构
![](/assets/VGG_structure.png)
VGG16包含16层，VGG19包含19层。一系列的VGG在最后三层的全连接层上完全一样，整体结构上都包含5组卷积层，卷积层之后跟一个MaxPool。所不同的是5组卷积层中包含的级联的卷积层越来越多。   
#### VGG11-VGG19
 
![](/assets/VGG_11_19.png)

#### 图像大小变化

![](/assets/VGG_Structure.png)

### 原理

1, VGG16相比AlexNet的一个改进是采用连续的几个3x3的卷积核代替AlexNet中的较大卷积核（11x11，7x7，5x5）。         
比如用2个3x3代替一个5x5   
![](/assets/VGG_small_kernel_replace_large.png)     





