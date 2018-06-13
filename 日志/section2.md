# 第二节 问题项目：

基础线性代数库

1. 2D插值
   1. 基于拟合公式，而拟合公式就是1D插值
   2. 第一个，实现克里金插值
2. 版本的迭代问题，每次也不求代码很完善，一次次测试与迭代，在过程中追求完美。
   1. 每个版本要说明改进的地方，为啥要改
   2. [https://github.com/lbbc1117/Nacho](https://github.com/lbbc1117/Nacho)
   3. 矩阵求逆需要记下一些notes或者文档。
      1. 这些只是一些练习，真实的可能会调用一些现成的库。目的是练练C++，也是为以后工作备用
   4. SVD 求解论文
      1. [http://people.duke.edu/~hpgavin/SystemID/References/Golub+Reinsch-NM-1970.pdf](http://people.duke.edu/~hpgavin/SystemID/References/Golub+Reinsch-NM-1970.pdf)
   5. **Armadillo **C++ library for linear algebra scientific computing  [http://arma.sourceforge.net/](http://arma.sourceforge.net/)
      1. [https://github.com/conradsnicta/armadillo-code/](https://github.com/conradsnicta/armadillo-code/)
      2. [https://en.wikipedia.org/wiki/Comparison\_of\_linear\_algebra\_libraries](https://en.wikipedia.org/wiki/Comparison_of_linear_algebra_libraries)
   6. 适合自己的才是最好的，
      1. 做一个自己实用的线性代数库，尽可能能供多的人去继承，去开发。
      2. 要有自己的开发文档。
   7. eigen： [https://github.com/Li-Simon/eigen-git-mirror](https://github.com/Li-Simon/eigen-git-mirror)
      1. 功能比**Armadillo 强大**
3. 因此，自己可以基于Eigen编写一个最优化算法的库，可以添加到Eigen中间去。仿照Eigen的风，可以作为自己的最优化，机器学习库函数，是否要保留一些核心功能作为护城河？保持文档（理论文档与使用文档）与代码配套
4. 要熟练使用的库
   1. OpenCV：暂时想不到可以用到什么地方
   2. Eigen：编写一个最优化算法库
   3. Tensorflow：有tensorflow lite可以为移动设备提供服务。
   
20180613
使用Eigen编写具有正则项的高次拟合函数，多项式，Sin函数，目的是引进正则项。
   



