## YOLO

目标检测算法可以分为two stage与one stage两类算法：  
two stage就是先产生region proposal，再在region proposal上做分类与回归，典型的就是RCNN的算法，如：R-CNN, Fast R-CNN, Faster R-CNN, 它的优点是准确率高，但是速度慢。  
one stage算法仅仅使用一个CNN网络直接预测不同目标的类别与位置，典型的算法是YOLO，SSD。 它的准确度要低一些，但是它的速度快。  
目标检测的一个实际应用场景就是无人驾驶，如果能够在无人车上装载一个有效的目标检测系统，那么无人车将和人一样有了眼睛，可以快速地检测出前面的行人与车辆，从而作出实时决策[^1]。

### YOLO的原理图

![](/assets/YOLO_Principle.png)   

#### 原理解析  

整体上，YOLO采用的是一个单独的CNN实现end-to-end的目标检测。通过输入一张448x448的图片到CNN，先经过GoogLeNet的前二十个卷积层，再通过一些卷积层与两个全连接层，最终输出的是7x7x30的张量。7x7表示49个区域，30=20+2x5，表示二十个类别的概率，2表示两个边界框，5表示每个边界框的四个坐标以及一个置信度。   
 
#### 网络设计   
Yolo采用卷积网络来提取特征，然后使用全连接层来得到预测值。网络结构参考GooLeNet模型，包含24个卷积层和2个全连接层，如图8所示。对于卷积层，主要使用1x1卷积来做channle reduction，然后紧跟3x3卷积。对于卷积层和全连接层，采用Leaky ReLU激活函数： max(x, 0.1x) 。但是最后一层却采用线性激活函数。    
![](/assets/YOLO_Net_Structure.png)   

##### 输出参数解析

每个单元格需要预测$$(B\times5+C)$$个值。如果将输入图片划分为 $$S\times S$$ 网格，那么最终预测值为$$ S\times S\times (B\times5+C)$$ 大小的张量。整个模型的预测值结构如下图所示。对于PASCAL VOC数据，其共有20个类别，如果使用 S=7,B=2 ，那么最终的预测结果就是$$ 7\times 7\times 30 $$大小的张量。在下面的网络结构中我们会详细讲述每个单元格的预测值的分布位置。

#### 损失函数

Yolo算法将目标检测看成回归问题，所以采用的是均方差损失函数。但是对不同的部分采用了不同的权重值。首先区分定位误差和分类误差。  
对于定位误差，即边界框坐标预测误差，采用较大的权重 $$\lambda_{coord}=5$$。  
然后其区分不包含目标的边界框与含有目标的边界框的置信度，对于前者，采用较小的权重值 $$\lambda_{noobj}=0.5 $$。其它权重值均设为1。  然后采用均方误差，其同等对待大小不同的边界框，但是实际上较小的边界框的坐标误差应该要比较大的边界框要更敏感。为了保证这一点，将网络的边界框的宽与高预测改为对其平方根的预测，即预测值变为 $$(x,y,\sqrt{w}, \sqrt{h})$$ 。  
最终的损失函数：  
![](/assets/YOLO_Cost_Function.png)

上面两行是坐标误差，中间两行是IOU误差，最下面一行是分类误差。  
其中第一项是边界框中心坐标的误差项， $$1^{obj}_{ij}$$指的是第 i 个单元格存在目标，且该单元格中的第  j 个边界框负责预测该目标。第二项是边界框的高与宽的误差项。第三项是包含目标的边界框的置信度误差项。第四项是不包含目标的边界框的置信度误差项。而最后一项是包含目标的单元格的分类误差项， $$1^{obj}_{i}$$ 指的是第 i 个单元格存在目标。这里特别说一下置信度的target值 $$C_i$$ ，如果是不存在目标，此时由于 Pr\(object\)=0，那么 $$C_i=0$$ 。如果存在目标， Pr\(object\)=1 ，此时需要确定 $$\text{IOU}^{truth}_{pred}$$ ，当然你希望最好的话，可以将IOU取1，这样 $$C_i=1$$ ，但是在YOLO实现中，使用了一个控制参数rescore（默认为1），当其为1时，IOU不是设置为1，而就是计算truth和pred之间的真实IOU。不过很多复现YOLO的项目还是取 $$C_i=1$$ ，这个差异应该不会太影响结果吧。

##### 输出参数解析

具体来说，Yolo的CNN网络将输入的图片分割成 $$S\times S$$ 网格，然后每个单元格负责去检测那些中心点落在该格子内的目标，如图6所示，可以看到狗这个目标的中心落在左下角一个单元格内，那么该单元格负责预测这个狗。每个单元格会预测 B 个边界框（bounding box）以及边界框的置信度（confidence score）。所谓置信度其实包含两个方面，一是这个边界框含有目标的可能性大小，二是这个边界框的准确度。前者记为 Pr\(object\) ，当该边界框是背景时（即不包含目标），此时 Pr\(object\)=0 。而当该边界框包含目标时， Pr\(object\)=1 。边界框的准确度可以用预测框与实际框（ground truth）的IOU（intersection over union，交并比）来表征，记为 $$\text{IOU}^{truth}_{pred}$$ 。因此置信度可以定义为 $$Pr(object)*\text{IOU}^{truth}_{pred}$$ 。很多人可能将Yolo的置信度看成边界框是否含有目标的概率，但是其实它是两个因子的乘积，预测框的准确度也反映在里面。边界框的大小与位置可以用4个值来表征： \(x, y,w,h\) ，其中 \(x,y\) 是边界框的中心坐标，而 w 和 h 是边界框的宽与高。还有一点要注意，中心坐标的预测值 \(x,y\) 是相对于每个单元格左上角坐标点的偏移值，并且单位是相对于单元格大小的，单元格的坐标定义如图6所示。而边界框的 w 和 h 预测值是相对于整个图片的宽与高的比例，这样理论上4个元素的大小应该在 \[0,1\] 范围。这样，每个边界框的预测值实际上包含5个元素： \(x,y,w,h,c\) ，其中前4个表征边界框的大小与位置，而最后一个值是置信度。

### 网络预测

在说明Yolo算法的预测过程之前，这里先介绍一下非极大值抑制算法（non maximum suppression, NMS），这个算法不单单是针对Yolo算法的，而是所有的检测算法中都会用到。NMS算法主要解决的是一个目标被多次检测的问题，如图11中人脸检测，可以看到人脸被多次检测，但是其实我们希望最后仅仅输出其中一个最好的预测框，比如对于美女，只想要红色那个检测结果。那么可以采用NMS算法来实现这样的效果：首先从所有的检测框中找到置信度最大的那个框，然后挨个计算其与剩余框的IOU，如果其值大于一定阈值（重合度过高），那么就将该框剔除；然后对剩余的检测框重复上述过程，直到处理完所有的检测框。Yolo预测过程也需要用到NMS算法。

![](/assets/YOLO_NMS.png)  
下面就来分析Yolo的预测过程，这里我们不考虑batch，认为只是预测一张输入图片。根据前面的分析，最终的网络输出是 $$7\times 7 \times 30 $$，但是我们可以将其分割成三个部分：类别概率部分为 \[7, 7, 20\] ，置信度部分为 \[7,7,2\] ，而边界框部分为 \[7,7,2,4\] （对于这部分不要忘记根据原始图片计算出其真实值）。然后将前两项相乘（矩阵 \[7, 7, 20\] 乘以 \[7,7,2\] 可以各补一个维度来完成 \[7,7,1,20\]x\[7,7,2,1\] ）可以得到类别置信度值为 \[7, 7,2,20\] ，这里总共预测了 7_7_2=98 个边界框。

所有的准备数据已经得到了，那么我们先说第一种策略来得到检测框的结果，我认为这是最正常与自然的处理。首先，对于每个预测框根据类别置信度选取置信度最大的那个类别作为其预测标签，经过这层处理我们得到各个预测框的预测类别及对应的置信度值，其大小都是 \[7,7,2\] 。一般情况下，会设置置信度阈值，就是将置信度小于该阈值的box过滤掉，所以经过这层处理，剩余的是置信度比较高的预测框。最后再对这些预测框使用NMS算法，最后留下来的就是检测结果。一个值得注意的点是NMS是对所有预测框一视同仁，还是区分每个类别，分别使用NMS。Ng在deeplearning.ai中讲应该区分每个类别分别使用NMS，但是看了很多实现，其实还是同等对待所有的框，我觉得可能是不同类别的目标出现在相同位置这种概率很低吧。

##小结
YOLO将目标检测任务转换成一个回归问题，大大加快了检测的速度，使得YOLO可以每秒处理45张图像。而且由于每个网络预测目标窗口时使用的是全图信息，使得false positive比例大幅降低（充分的上下文信息）。

但是YOLO也存在问题：没有了Region Proposal机制，只使用7*7的网格回归会使得目标不能非常精准的定位，这也导致了YOLO的检测精度并不是很高。

[^2]: 目标检测|YOLO原理与实现  https://zhuanlan.zhihu.com/p/32525231
[^3]: 一文读懂目标检测：R-CNN、Fast R-CNN、Faster R-CNN、YOLO、SSD   https://blog.csdn.net/v_JULY_v/article/details/80170182