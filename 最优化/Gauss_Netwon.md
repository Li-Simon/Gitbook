#高斯-牛顿法
对于函数$$f(x)$$的小邻域展开
$$\kern{4 em} f(x+h) \simeq l(h) \equiv f(x) + J(x)h$$
$$\kern{4 em} F(x+h) \simeq L(h) \equiv \frac{1}{2}l(h)^Tl(h)
=\frac{1}{2}f^{T}f + h^TJ^Tf + \frac{1}{2}h^TJ^TJh$$
我们需要选择步长$$h_{gn}$$来最小化$$L(h)$$
$$\kern{4 em} h_{gn} = argmin_h{L(h)}$$
$$\kern{4 em} (J^TJ)h_{gn} = -J^Tf$$
