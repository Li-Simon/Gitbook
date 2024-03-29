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



#### 先验框匹配[^1]

在训练过程中，首先要确定训练图片中的ground truth（真实目标）与哪个先验框来进行匹配，与之匹配的先验框所对应的边界框将负责预测它。在Yolo中，ground truth的中心落在哪个单元格，该单元格中与其IOU最大的边界框负责预测它。但是在SSD中却完全不一样，SSD的先验框与ground truth的匹配原则主要有两点。首先，对于图片中每个ground truth，找到与其IOU最大的先验框，该先验框与其匹配，这样，可以保证每个ground truth一定与某个先验框匹配。通常称与ground truth匹配的先验框为正样本（其实应该是先验框对应的预测box，不过由于是一一对应的就这样称呼了），反之，若一个先验框没有与任何ground truth进行匹配，那么该先验框只能与背景匹配，就是负样本。一个图片中ground truth是非常少的， 而先验框却很多，如果仅按第一个原则匹配，很多先验框会是负样本，正负样本极其不平衡，所以需要第二个原则。第二个原则是：对于剩余的未匹配先验框，若某个ground truth的 IOU 大于某个阈值（一般是0.5），那么该先验框也与这个ground truth进行匹配。这意味着某个ground truth可能与多个先验框匹配，这是可以的。但是反过来却不可以，因为一个先验框只能匹配一个ground truth，如果多个ground truth与某个先验框 $$\text{IOU}$$ 大于阈值，那么先验框只与IOU最大的那个先验框进行匹配。第二个原则一定在第一个原则之后进行，仔细考虑一下这种情况，如果某个ground truth所对应最大 IOU 小于阈值，并且所匹配的先验框却与另外一个ground truth的 IOU 大于阈值，那么该先验框应该匹配谁，答案应该是前者，首先要确保某个ground truth一定有一个先验框与之匹配。但是，这种情况我觉得基本上是不存在的。由于先验框很多，某个ground truth的最大 IOU 肯定大于阈值，所以可能只实施第二个原则既可以了，这里的TensorFlow版本就是只实施了第二个原则，但是这里的Pytorch两个原则都实施了。图8为一个匹配示意图，其中绿色的GT是ground truth，红色为先验框，FP表示负样本，TP表示正样本。

![](/assets/SSD_Box_ground_truth.png)

尽管一个ground truth可以与多个先验框匹配，但是ground truth相对先验框还是太少了，所以负样本相对正样本会很多。为了保证正负样本尽量平衡，SSD采用了hard negative mining，就是对负样本进行抽样，抽样时按照置信度误差（预测背景的置信度越小，误差越大）进行降序排列，选取误差的较大的top-k作为训练的负样本，以保证正负样本比例接近1:3。

#### SSD网络结构

SSD采用VGG16作为基础模型，然后在VGG16的基础上新增了卷积层来获得更多的特征图以用于检测。SSD的网络结构如图5所示。上面是SSD模型，下面是Yolo模型，可以明显看到SSD利用了多尺度的特征图做检测。模型的输入图片大小是 $$300\times300$$ （还可以是 $$512\times512$$ ，其与前者网络结构没有差别，只是最后新增一个卷积层，本文不再讨论）。  
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

#### 数据扩增

采用数据扩增（Data Augmentation）可以提升SSD的性能，主要采用的技术有水平翻转（horizontal flip），随机裁剪加颜色扭曲（random crop & color distortion），随机采集块域（Randomly sample a patch）（获取小目标训练样本）

#### 预测过程

预测过程比较简单，对于每个预测框，首先根据类别置信度确定其类别（置信度最大者）与置信度值，并过滤掉属于背景的预测框。然后根据置信度阈值（如0.5）过滤掉阈值较低的预测框。对于留下的预测框进行解码，根据先验框得到其真实的位置参数（解码后一般还需要做clip，防止预测框位置超出图片）。解码之后，一般需要根据置信度进行降序排列，然后仅保留top-k（如400）个预测框。最后就是进行NMS算法，过滤掉那些重叠度较大的预测框。最后剩余的预测框就是检测结果了。

#### 结果

SSD与其它检测算法的对比结果（在VOC2007数据集）如表所示，基本可以看到，SSD与Faster R-CNN有同样的准确度，并且与Yolo具有同样较快地检测速度。

![](/assets/ssd_results.png)

[^1]: 目标检测|SSD原理与实现  https://zhuanlan.zhihu.com/p/33544892   

[^2]: 一文读懂目标检测：R-CNN、Fast R-CNN、Faster R-CNN、YOLO、SSD   https://blog.csdn.net/v_JULY_v/article/details/80170182