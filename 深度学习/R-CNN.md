## R-CNN

R-CNN（Region CNN，区域卷积神经网络）可以说是利用深度学习进行目标检测的开山之作，作者Ross Girshick多次在PASCAL VOC的目标检测竞赛中折桂，2010年更是带领团队获得了终身成就奖，如今就职于Facebook的人工智能实验室（FAIR）。  
R-CNN算法的流程如下：  

![](/assets/RCNN_flow.png)



1、输入图像
2、每张图像生成1K~2K个候选区域
3、对每个候选区域，使用深度网络提取特征（AlextNet、VGG等CNN都可以）
4、将特征送入每一类的SVM 分类器，判别是否属于该类
5、使用回归器精细修正候选框位置

