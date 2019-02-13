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



