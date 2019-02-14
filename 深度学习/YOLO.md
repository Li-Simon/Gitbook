## YOLO
目标检测算法可以分为two stage与one stage两类算法：  
two stage就是先产生region proposal，再在region proposal上做分类与回归，典型的就是RCNN的算法，如：R-CNN, Fast R-CNN, Faster R-CNN, 它的优点是准确率高，但是速度慢。   
one stage算法仅仅使用一个CNN网络直接预测不同目标的类别与位置，典型的算法是YOLO，SSD。  
###YOLO的原理图
![](/assets/YOLO_Principle.png)



