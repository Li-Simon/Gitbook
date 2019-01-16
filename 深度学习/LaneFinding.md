# Lane Finding

上面我们已经介绍过了直线检测，现在我们主要讨论相对复杂的曲线检测。检测的步骤如下：

* 通过棋盘图像计算相机参数与扭曲系数
* 对原始图像进行扭曲矫正
* 通过颜色变换，以及梯度等方法来得到一个基于阈值的二进制图像
* 应用perspective transform来得到一张矫正的二进制图\(“birds-eye-view”\)  
* 得到路道的像素并且找到路道的边界 
* 确定路道的曲率并且车辆相对于中心的位置  
* Wrap the detected lane boundaries back onto the original image
* Output visual display of the lane boundaries and numerical estimation of lane curvature and vehicle position  

## 任务

1. 明白相机参数，扭曲系数的直观图像与怎么计算这些参数？
2. 怎么挑选颜色变换来得到鲁棒的图像？
3. 怎么进行perspective transform\(透视变换\)？ 
4. 除了基于Histogram的极值与卷积之外，还有什么其它方式来检测路道？  
5. 怎么计算路道的曲率以及怎么快速的代码实现？  
6. 对于崎岖，被遮挡的山道怎么有效的进行路道的识别？考虑特殊的情形，也就是可见度不高，不明显的路道怎么有效的确定路道？  
7. 如果你自己有一辆无人车，你怎么基于特定场景\(工厂环境\)设计鲁棒，计算量极小的算法来实现道路检测，自动驾驶？  
8. 明白无人驾驶在哪些方面无深度学习而不可？  

## Camera Calibration

由于相机棱镜的不完美，导致了图形的径向扭曲，由于相机位置不正，导致了图像的切向扭曲，因为我们有必要对现实扭曲的图像进行矫正来得到完美的图像。  
To ensure that the geometrical shape of objects is represented consistently, no matter where they appear in an image.  
![](/assets/Distortion.png)  
\($$x_c,y_c$$\)是扭曲中心，r是原始图像中一点到扭曲中心的距离。

### radial distortion

径向扭曲，具有旋转不变性，因此对x,y的修正是一样的。通过一些高阶的修正来还原模型，我们需要求得这些修正的系数。  
$$x_{distored} = x_{ideal}(1 + k_1 r^2 + k_2 r^4 + k_3 r^6)$$  
$$y_{distored} = y_{ideal}(1 + k_1 r^2 + k_2 r^4 + k_3 r^6)$$

### tangential distortion

$$x_{corrected} = x + [2p_1 xy + p_2(r^2 + 2x^2)]$$  
$$y_{corrected} = y + [2p_2 xy +  p_1(r^2 + 2y^2)]$$

### Calibrating Camera

To computer the transformation between 3D object points in the world and 2D image points  
我们一般使用棋盘模型来的得到这些扭曲系数\($$k_1,k_2,k_3,p_1,p_2$$\)  
ret, mtx, dist, rvecs, tvecs = cv2.calibrateCamera\(objpoints, imgpoints, img\_size,None,None\), 其中mtx is camera matrix, mtx, dist is distortion coefficients. 具体而言，imgpoints是真实的扭曲的图像中的点的3D坐标，objpoints是没有扭曲的棋盘坐标，是2D的，通过这两者之间，可以建立i一个映射关系，返回ret, mtx, dist, rvecs, tvecs这些参数。  
其中imgpoints可以通过OpenCV的函数来搜索到扭曲图像中的角点，ret, corners = cv2.findChessboardCorners\(gray, \(8,6\), None\)。  
再用dst = cv2.undistort\(img, mtx, dist, None, mtx\)就可以恢复图像了。

## Perspective Transform

To transform an image such that we are effectively viewing objects from adifferent angle or direction.

```py
offset = 100 # offset for dst points
# Grab the image shape
img_size = (gray.shape[1], gray.shape[0])

# For source points I'm grabbing the outer four detected corners
src = np.float32([corners[0], corners[nx-1], corners[-1], corners[-nx]])
# For destination points, I'm arbitrarily choosing some points to be
# a nice fit for displaying our warped result 
# again, not exact, but close enough for our purposes
dst = np.float32([[offset, offset], [img_size[0]-offset, offset], [img_size[0]-offset, img_size[1]-offset], 
                                     [offset, img_size[1]-offset]])
# Given src and dst points, calculate the perspective transform matrix
M = cv2.getPerspectiveTransform(src, dst)
# Warp the image using OpenCV warpPerspective()
warped = cv2.warpPerspective(undist, M, img_size)
```

注意dst中对应于src中的四点可以任意，getPerspectiveTransform中注意参数顺序。

## Color transformation, HSV and HLS

彩色图像可以用RGB来表示，也可以用HSV空间\(hue色相, saturation饱和度, and value明度\), 或者HLS空间\(hue色相, lightness亮度, and saturation饱和度\)来表示。

![](/assets/HSV_HLS.png)

HSL（a~d）和HSV（e~h）。上半部分（a、e）：两者的3D模型截面。下半部分：将模型中三个参数的其中之一固定为常量，其它两个参数的图像。\(图像引用自维基百科中文版\)  
由OpenCV的cv2.imread\(\)可以得到RGB图像，再由

```py
hls = cv2.cvtColor(image, cv2.COLOR_RGB2HLS)
H = hls[:,:,0]
L = hls[:,:,1]
S = hls[:,:,2]
```

可以把RGB转换成HLS图像。

### HLS and Color Thresholds

```py
thresh = (90, 255)
binary = np.zeros_like(S)
binary[(S > thresh[0]) & (S <= thresh[1])] = 1
```



