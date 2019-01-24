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
具体步骤如下：  
Finding chessboard corners \(for an 8x6 board\):

```py
ret, corners = cv2.findChessboardCorners(gray, (8,6), None)
```

Drawing detected corners on an image:

```py
img = cv2.drawChessboardCorners(img, (8,6), corners, ret)
```

Camera calibration, given object points, image points, and the**shape of the grayscale image**:

```py
ret, mtx, dist, rvecs, tvecs = cv2.calibrateCamera(objpoints, imgpoints, gray.shape[::-1], None, None)
```

Undistorting a test image:

```py
dst = cv2.undistort(img, mtx, dist, None, mtx)
```

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

![](/assets/warpPerspective.png)

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

实验发现，对于目标检测而言，对S通道进行阈值分割能得到更Robust的结果，特殊情况例外，比如R,G,B单色的目标物体。

```py
thresh = (90, 255)
binary = np.zeros_like(S)
binary[(S > thresh[0]) & (S <= thresh[1])] = 1
```

![](/assets/HLS_S_channel.png)

### Gradient Thresholds

我们可以通过soble算子来求不同方向的梯度，可以用来检测方向以及通过阈值来进行分割。  
强度阈值：  
$$abssobel_x = (sobel_x^2)^{1/2}$$  
$$abssobel_y = (sobel_y^2)^{1/2}$$  
$$abssobel_{xy} = (sobel_x^2 + sobel_y^2)^{1/2}$$  
角度阈值：  $$\arctan(sobel_y/sobel_x)$$

#### Sobel Operator

![](/assets/Sobel_X_Y.png)

```py
gray = cv2.cvtColor(im, cv2.COLOR_RGB2GRAY)
sobelx = cv2.Sobel(gray, cv2.CV_64F, 1, 0)
sobely = cv2.Sobel(gray, cv2.CV_64F, 0, 1)
abs_sobelx = np.absolute(sobelx)
scaled_sobel = np.uint8(255*abs_sobelx/np.max(abs_sobelx))
```

```py
gray = cv2.cvtColor(img, cv2.COLOR_RGB2GRAY)
sobelx = cv2.Sobel(gray, cv2.CV_64F, 1, 0, ksize=sobel_kernel)
sobely = cv2.Sobel(gray, cv2.CV_64F, 0, 1, ksize=sobel_kernel)
# Calculate the gradient magnitude
gradmag = np.sqrt(sobelx**2 + sobely**2)
# Rescale to 8 bit
scale_factor = np.max(gradmag)/255 
gradmag = (gradmag/scale_factor).astype(np.uint8) 
binary_output = np.zeros_like(gradmag)
binary_output[(gradmag >= mag_thresh[0]) & (gradmag <= mag_thresh[1])] = 1
```

## Advanced Topic for Finding Lines

### Histogram Peaks

![](/assets/Histogram_raw_image.png)

```py
import numpy as np
import matplotlib.pyplot as plt

histogram = np.sum(img[img.shape[0]//2:,:], axis=0)
plt.plot(histogram)
```

![](/assets/Histogram_CV_line.png)

### Sliding Window

如果我们把图像切分成小的window,通过上面的Histogram Peaks找到每个小window的peak，也就是对于的路线最可能过的点，做一条曲线来拟合这些点，这条曲线就是lane line。如下图中的黄线。 下图中的绿色小窗口的宽度就是margin宽度，我们认为lane line位于margin区域内。

![](/assets/sliding_window_cv_sd.png)

```py
import numpy as np
import matplotlib.image as mpimg
import matplotlib.pyplot as plt
import cv2

# Load our image
binary_warped = mpimg.imread('warped_example.jpg')


def find_lane_pixels(binary_warped):
    # Take a histogram of the bottom half of the image
    histogram = np.sum(binary_warped[binary_warped.shape[0] // 2:, :], axis=0)
    # Create an output image to draw on and visualize the result
    out_img = np.dstack((binary_warped, binary_warped, binary_warped))
    # Find the peak of the left and right halves of the histogram
    # These will be the starting point for the left and right lines
    midpoint = np.int(histogram.shape[0] // 2)
    leftx_base = np.argmax(histogram[:midpoint])
    rightx_base = np.argmax(histogram[midpoint:]) + midpoint

    # HYPERPARAMETERS
    # Choose the number of sliding windows
    nwindows = 9
    # Set the width of the windows +/- margin
    margin = 100
    # Set minimum number of pixels found to recenter window
    minpix = 50

    # Set height of windows - based on nwindows above and image shape
    window_height = np.int(binary_warped.shape[0] // nwindows)
    # Identify the x and y positions of all nonzero pixels in the image
    nonzero = binary_warped.nonzero()
    nonzeroy = np.array(nonzero[0])
    nonzerox = np.array(nonzero[1])
    # Current positions to be updated later for each window in nwindows
    leftx_current = leftx_base
    rightx_current = rightx_base

    # Create empty lists to receive left and right lane pixel indices
    left_lane_inds = []
    right_lane_inds = []

    lefty = []
    righty = []

    # Step through the windows one by one
    for window in range(nwindows):
        # Identify window boundaries in x and y (and right and left)
        win_y_low = binary_warped.shape[0] - (window + 1) * window_height
        win_y_high = binary_warped.shape[0] - window * window_height
        ### TO-DO: Find the four below boundaries of the window ###
        win_xleft_low = leftx_current - margin   # Update this
        win_xleft_high = leftx_current + margin # Update this
        win_xright_low = rightx_current - margin # Update this
        win_xright_high = rightx_current + margin  # Update this

        # Draw the windows on the visualization image
        cv2.rectangle(out_img, (win_xleft_low, win_y_low),
                      (win_xleft_high, win_y_high), (0, 255, 0), 2)
        cv2.rectangle(out_img, (win_xright_low, win_y_low),
                      (win_xright_high, win_y_high), (0, 255, 0), 2)

        ### TO-DO: Identify the nonzero pixels in x and y within the window ###
        good_left_inds = None
        good_right_inds = None

        histogram2 = np.sum(binary_warped[win_y_low:win_y_high, :], axis=0)

        good_left_inds = ((nonzeroy >= win_y_low) & (nonzeroy < win_y_high) &
                          (nonzerox >= win_xleft_low) & (nonzerox < win_xleft_high)).nonzero()[0]

        good_right_inds = ((nonzeroy >= win_y_low) & (nonzeroy < win_y_high) &
                          (nonzerox >= win_xright_low) & (nonzerox < win_xright_high)).nonzero()[0]

        if len(good_left_inds) > minpix:
            leftx_current = np.int(np.mean(nonzerox[good_left_inds]))
        if len(good_right_inds) > minpix:
            rightx_current = np.int(np.mean(nonzerox[good_right_inds]))

        # Append these indices to the lists
        left_lane_inds.append(good_left_inds)
        right_lane_inds.append(good_right_inds)

        ### TO-DO: If you found > minpix pixels, recenter next window ###
        ### (`right` or `leftx_current`) on their mean position ###
        pass  # Remove this when you add your function

    # Concatenate the arrays of indices (previously was a list of lists of pixels)
    try:
        left_lane_inds = np.concatenate(left_lane_inds)
        right_lane_inds = np.concatenate(right_lane_inds)
    except ValueError:
        # Avoids an error if the above is not implemented fully
        pass

    # Extract left and right line pixel positions
    leftx = nonzerox[left_lane_inds]
    lefty = nonzeroy[left_lane_inds]
    #leftx = left_lane_inds
    #rightx = right_lane_inds
    rightx = nonzerox[right_lane_inds]
    righty = nonzeroy[right_lane_inds]

    return leftx, lefty, rightx, righty, out_img


def fit_polynomial(binary_warped):
    # Find our lane pixels first
    leftx, lefty, rightx, righty, out_img = find_lane_pixels(binary_warped)

    ### TO-DO: Fit a second order polynomial to each using `np.polyfit` ###
    left_fit = np.polyfit(lefty, leftx, 2)
    right_fit = np.polyfit(righty, rightx, 2)

    # Generate x and y values for plotting
    ploty = np.linspace(0, binary_warped.shape[0] - 1, binary_warped.shape[0])
    try:
        left_fitx = left_fit[0] * ploty ** 2 + left_fit[1] * ploty + left_fit[2]
        right_fitx = right_fit[0] * ploty ** 2 + right_fit[1] * ploty + right_fit[2]
    except TypeError:
        # Avoids an error if `left` and `right_fit` are still none or incorrect
        print('The function failed to fit a line!')
        left_fitx = 1 * ploty ** 2 + 1 * ploty
        right_fitx = 1 * ploty ** 2 + 1 * ploty

    ## Visualization ##
    # Colors in the left and right lane regions
    out_img[lefty, leftx] = [255, 0, 0]
    out_img[righty, rightx] = [0, 0, 255]

    # Plots the left and right polynomials on the lane lines
    plt.plot(left_fitx, ploty, color='yellow')
    plt.plot(right_fitx, ploty, color='yellow')

    return out_img


out_img = fit_polynomial(binary_warped)

plt.imshow(out_img)
plt.show()
```

### Search from Prior

这是基于先验\(前面的位置与方向的方法\)，具体就是，根据以前的运动曲线，比如在小范围内可以拟合成二次曲线，再基于当前的位置，我们就可以确定下一时刻大致的运动范围，因此我们不需要检验所有与前进方向垂直的区域，只需要检验Margin区域来得到下一位置的Lane line的位置。  
通过一步步的迭代，更新拟合曲线的参数与位置，就可以得到整条Lane Line。

![](/assets/Lane_line_search_from_prior.png)   

####可行区域填充
得到Lane Lines之后，我们使用dstack是二进制图像变成三维图像，再用彩色填充道路之间的区域。  
再用getPerspectiveTransform得到一个逆矩阵，从而把bird view变成原始空间的图像。  
再叠加原始的图像，得到对道路进行填充的图像。   
src不必要太精确，只需是包含原始道路区域的梯形，而dst坐标是特定矩形的四个顶点。 当然，求src的精确方法是，通过卷积，来求得道路的终点。           

```cpp
Minv = cv2.getPerspectiveTransform(dst, src)
    
warp_zero = np.zeros_like(combined_binary).astype(np.uint8)
color_warp = np.dstack((warp_zero, warp_zero, warp_zero))
pts_left = np.array([np.flipud(np.transpose(np.vstack([left_fitx, lefty])))])
pts_right = np.array([np.transpose(np.vstack([right_fitx, righty]))])
pts = np.hstack((pts_left, pts_right))
cv2.polylines(color_warp, np.int_([pts]), isClosed=False, color=(0,0,255), thickness = 40)
cv2.fillPoly(color_warp, np.int_([pts]), (0,255, 0))
newwarp = cv2.warpPerspective(color_warp, Minv, (combined_binary.shape[1], combined_binary.shape[0]))
result = cv2.addWeighted(mpimg.imread(image), 1, newwarp, 0.5, 0)
```



### Convolution Methods

我们也可以利用卷积来寻找Lane Line的位置，具体步骤就是。  
对一个小的窗口，比如高度为80，长度L就是图像x轴长度的一个窗口区域， 对这个窗口区域做Histogram，得到一个大小为L的一维数组， 一个卷积核对这个数组做卷积，位于我们感兴趣的Margin区域内的Peak位置，就是Lane Line上的点。把这些点连起来就可以得到整条Lane Line。

![](/assets/Lane_Line_Finding_Conv.png)

## Measuring Curvature

对于曲线：  
   $$x = f(y) = Ay^2 + By + C$$  
曲线$$x = f(y)$$的曲率半径定义为：  
   $$R_{curve} = \frac{(1+(\frac{dy}{dx})^2)^{3/2}}{|\frac{d^2x}{dy^2}|}$$  
对于我们的例子有：  
   $$f'(y) = \frac{dy}{dx} = 2Ay + B$$  
   $$f''(y) = \frac{d^2x}{dy^2} = 2A$$  
因此，\(y,x\)点的曲率半径为：  
   $$R_{curve} = \frac{(1+ (2Ay + B)^2)^{3/2}}{|2A|}$$

## 无标度化

当然，我们还可以进行无标度化，来得到一个不带单位的方程，具体就是对x,y除以一个单位因子，这个因子就是每个pixel对应的物理长度。  
![](/assets/Lane_Line_Curvature_1.png)


在实际中，我们需要确保两条线之间的距离在一定的区间，必须要有这个约束。  

