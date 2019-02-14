## YOLO
目标检测算法可以分为two stage与one stage两类算法：  
two stage就是先产生region proposal，再在region proposal上做分类与回归，典型的就是RCNN的算法，如：R-CNN, Fast R-CNN, Faster R-CNN, 它的优点是准确率高，但是速度慢。   
one stage算法仅仅使用一个CNN网络直接预测不同目标的类别与位置，典型的算法是YOLO，SSD。 它的准确度要低一些，但是它的速度快。   
目标检测的一个实际应用场景就是无人驾驶，如果能够在无人车上装载一个有效的目标检测系统，那么无人车将和人一样有了眼睛，可以快速地检测出前面的行人与车辆，从而作出实时决策。    
###YOLO的原理图
![](/assets/YOLO_Principle.png)  

####原理解析




