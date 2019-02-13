## Fast-RCNN

继2014年的R-CNN推出之后，Ross Girshick在2015年推出Fast R-CNN，构思精巧，流程更为紧凑，大幅提升了目标检测的速度。

#### Fast R-CNN主要解决R-CNN的一下问题

1， 训练，测试时速度慢  
R-CNN的一张图像内候选框之间存在大量重叠，提取特征操作冗余。而Fast R-CNN将整张图像归一化后直接送入深度网络，紧接着送入从这幅图像上提取出的候选区域。这些候选区域的前几层特征不需要再重复计算。  
2， 训练所需空间大  
R-CNN中独立的分类器和回归器需要大量特征作为训练样本。Fast R-CNN把类别判断和位置精调统一用深度网络实现，不再需要额外存储。

#### Fast R-CNN原理示意图

![](/assets/Fast_RCNN_Principle.png)

#### 在特征提取阶段

通过CNN（如AlexNet）中的conv、pooling、relu等操作都不需要固定大小尺寸的输入，因此，在原始图片上执行这些操作后，输入图片尺寸不同将会导致得到的feature map（特征图）尺寸也不同，这样就不能直接接到一个全连接层进行分类。

### SPP Net

SPP：Spatial Pyramid Pooling（空间金字塔池化）  
众所周知，CNN一般都含有卷积部分和全连接部分，其中，卷积层不需要固定尺寸的图像，而全连接层是需要固定大小的输入。  
所以当全连接层面对各种尺寸的输入数据时，就需要对输入数据进行crop（crop就是从一个大图扣出网络输入大小的patch，比如227×227），或warp（把一个边界框bounding box的内容resize成227×227）等一系列操作以统一图片的尺寸大小，比如224\_224（ImageNet）、32\_32\(LenNet\)、96\*96等。

![](/assets/SPP_Crop.png)

所以才如你在上文中看到的，在R-CNN中，“因为取出的区域大小各自不同，所以需要将每个Region Proposal缩放（warp）成统一的227x227的大小并输入到CNN”。

但warp/crop这种预处理，导致的问题要么被拉伸变形、要么物体不全，限制了识别精确度。没太明白？说句人话就是，一张16:9比例的图片你硬是要Resize成1:1的图片，你说图片失真不？

SPP Net的作者Kaiming He等人逆向思考，既然由于全连接FC层的存在，普通的CNN需要通过固定输入图片的大小来使得全连接层的输入固定。那借鉴卷积层可以适应任何尺寸，为何不能在卷积层的最后加入某种结构，使得后面全连接层得到的输入变成固定的呢？

这个“化腐朽为神奇”的结构就是spatial pyramid pooling layer。下图便是R-CNN和SPP Net检测流程的比较：

![](/assets/RCNN_SPP_Comp.png)  
它的特点有两个:  
1.结合空间金字塔方法实现CNNs的多尺度输入。  
SPP Net的第一个贡献就是在最后一个卷积层后，接入了金字塔池化层，保证传到下一层全连接层的输入固定。  
换句话说，在普通的CNN机构中，输入图像的尺寸往往是固定的（比如224\*224像素），输出则是一个固定维数的向量。SPP Net在普通的CNN结构中加入了ROI池化层（ROI Pooling），使得网络的输入图像可以是任意尺寸的，输出则不变，同样是一个固定维数的向量。

简言之，CNN原本只能固定输入、固定输出，CNN加上SSP之后，便能任意输入、固定输出。神奇吧？

ROI池化层一般跟在卷积层后面，此时网络的输入可以是任意尺度的，在SPP layer中每一个pooling的filter会根据输入调整大小，而SPP的输出则是固定维数的向量，然后给到全连接FC层。

![](/assets/SPP_Const_output.png)

2.只对原图提取一次卷积特征  
在R-CNN中，每个候选框先resize到统一大小，然后分别作为CNN的输入，这样是很低效的。  
而SPP Net根据这个缺点做了优化：只对原图进行一次卷积计算，便得到整张图的卷积特征feature map，然后找到每个候选框在feature map上的映射patch，将此patch作为每个候选框的卷积特征输入到SPP layer和之后的层，完成特征提取工作。

如此这般，R-CNN要对每个区域计算卷积，而SPPNet只需要计算一次卷积，从而节省了大量的计算时间，比R-CNN有一百倍左右的提速。

![](/assets/SPP_FC.png)

##### ROI Pooling

在Fast R-CNN中，作者提出了一个叫做ROI Pooling的网络层，这个网络层可以把不同大小的输入映射到一个固定尺度的特征向量。ROI Pooling层将每个候选区域均匀分成M×N块，对每块进行max pooling。将特征图上大小不一的候选区域转变为大小统一的数据，送入下一层。这样虽然输入的图片尺寸不同，得到的feature map（特征图）尺寸也不同，但是可以加入这个神奇的ROI Pooling层，对每个region都提取一个固定维度的特征表示，就可再通过正常的softmax进行类型识别。

![](/assets/Fast_RCNN_ROI_Pooling.png)

#### 2、在分类回归阶段

在R-CNN中，先生成候选框，然后再通过CNN提取特征，之后再用SVM分类，最后再做回归得到具体位置（bbox regression）。而在Fast R-CNN中，作者巧妙的把最后的bbox regression也放进了神经网络内部，与区域分类合并成为了一个multi-task模型，如下图所示：

![](/assets/FASTRCNN_bbox_regression.png)  
实验表明，这两个任务能够共享卷积特征，并且相互促进。  
Fast R-CNN很重要的一个贡献是成功地让人们看到了Region Proposal+CNN（候选区域+卷积神经网络）这一框架实时检测的希望，原来多类检测真的可以在保证准确率的同时提升处理速度。

#### 总结

Fast-RCNN的优势：  
1. 加入ROI Pooling层使得每个提名区域的输出大小一致  
2. 把分类任务与位置回归任务放在一个网络里面，同时训练，损失函数是分类损失函数加上回归损失函数。加快了训练过程。  
Fast R-CNN和R-CNN相比，训练时间从84小时减少到9.5小时，测试时间从47秒减少到0.32秒，并且在PASCAL VOC 2007上测试的准确率相差无几，约在66%-67%之间。

![](/assets/RCNN_FastRCNN_time_Compare.png)

