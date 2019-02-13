## Faster-RCNN

###### Faster R-CNN更快更强

继2014年推出R-CNN，2015年推出Fast R-CNN之后，目标检测界的领军人物Ross Girshick团队在2015年又推出一力作：Faster R-CNN，使简单网络目标检测速度达到17fps，在PASCAL VOC上准确率为59.9%，复杂网络达到5fps，准确率78.8%。  
在Fast R-CNN还存在着瓶颈问题：Selective Search（选择性搜索）。要找出所有的候选框，这个也非常耗时。那我们有没有一个更加高效的方法来求出这些候选框呢？  
在Faster R-CNN中加入一个提取边缘的神经网络，也就说找候选框的工作也交给神经网络来做了。
######这样，目标检测的四个基本步骤（候选区域生成，特征提取，分类，位置精修）终于被统一到一个深度网络框架之内。  
如下图所示：  

![](/assets/RCNN_Fast_Faster_RCNN_compare.png)

