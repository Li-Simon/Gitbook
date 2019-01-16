# Lane Finding

上面我们已经介绍过了直线检测，现在我们主要讨论相对复杂的曲线检测。检测的步骤如下：  

* 通过棋盘图像计算相机参数与扭曲系数
* 对原始图像进行扭曲矫正
* 通过颜色变换，以及梯度等方法来得到一个基于阈值的二进制图像
* 应用perspective transform来得到一张矫正的二进制图(“birds-eye-view”)  
* 得到路道的像素并且找到路道的边界 
* 确定路道的曲率并且车辆相对于中心的位置  
* Wrap the detected lane boundaries back onto the original image
* Output visual display of the lane boundaries and numerical estimation of lane curvature and vehicle position  

####任务
1. 明白相机参数，扭曲系数的直观图像与怎么计算这些参数？
2. 怎么挑选颜色变换来得到鲁棒的图像？
3. 怎么进行perspective transform(透视变换)？ 
4. 除了基于Histogram的极值与卷积之外，还有什么其它方式来检测路道？  
5. 怎么计算路道的曲率以及怎么快速的代码实现？  
6. 对于崎岖，被遮挡的山道怎么有效的进行路道的识别？考虑特殊的情形，也就是可见度不高，不明显的路道怎么有效的确定路道？  
7. 如果你自己有一辆无人车，你怎么基于特定场景(工厂环境)设计鲁棒，计算量极小的算法来实现道路检测，自动驾驶？  
8. 明白无人驾驶在哪些方面无深度学习而不可？  



