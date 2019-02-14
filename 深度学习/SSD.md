## SSD

SSD: Single Shot MultiBox Detector  
YOLO使用整图特征在7\*7的粗糙网格内回归对目标的定位并不是很精准。那是不是可以结合Region Proposal的思想实现精准一些的定位？SSD结合YOLO的回归思想以及Faster R-CNN的anchor机制做到了这点。

#### 步骤

SSD仅需要一张输入图像和训练所需要的每个目标的 groud truth，而输出为位置偏移量、置信度和分类概率。首先通过对输入图像的一系列卷积操作生成不同大小尺寸的特征图，比如上图中的 8x8 和 4x4 大小特征图。然后对这些每个特征图执行 3x3 的卷积核来评估此前生成的默认边界框，这种默认边界框可理解为先验框，类似于此前 Faster R-CNN 的 anchor boxes。对这些边界框同时执行预测，主要预测两个量：边界框的偏移量和目标物体的分类概率值，最后使用非极大值抑制来选取高于阈值的边界框。  
所以，SSD 的分步步骤如下：  
1. 对输入图像执行一系列卷积生成不同大小的特征图  
2. 对每个特征图都执行3x3卷积来评估默认边界框  
3. 对每个边界框预测偏移量和分类概率  
4. 执行NMS非极大值抑制

#### SSD网络结构

![](/assets/SSD_Net_Structure.png)

#### 损失函数

训练样本确定了，然后就是损失函数了。损失函数定义为位置误差（locatization loss， loc）与置信度误差（confidence loss, conf）的加权和[^1]：

$$L(x,c,l,g) = \frac{1}{N}(L_{conf}(x,c) + \alpha L_{loc}(x,c,g))$$  
权重系数$$\alpha$$ 通过交叉验证设置为1。  
其中 N 是先验框的正样本数量。这里 $$x^p_{ij}\in \{ 1,0 \} $$为一个指示参数，当 $$x^p_{ij}= 1 $$时表示第 i 个先验框与第 j 个ground truth匹配，并且ground truth的类别为 p 。 c 为类别置信度预测值。 l 为先验框的所对应边界框的位置预测值，而 g 是ground truth的位置参数。对于位置误差，其采用Smooth L1 loss，定义如下：

![](/assets/ssd_cost_loc.png)

![](/assets/ssd_cost_smo.png)  
对于置信度偏差采用softmax:   

![](/assets/SSD_cost_conf.png)  


[^1]:  目标检测|SSD原理与实现  https://zhuanlan.zhihu.com/p/33544892
