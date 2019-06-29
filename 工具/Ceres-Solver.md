#Ceres-Solver
Ceres-Solver是Google 2010年开源的一款非线性优化库。它主要能解决两类问题：  
1. 带约束的非线性最小二乘问题  
2. 一般的无约束优化问题  
底层实现引用了Eigen与Lapack, Ceres是求解非线性优化问题的首选，可以应用到SLAM中去。有现成的参考文档http://ceres-solver.org/features.html。   
如果我们需要基于Ceres-Slover来开发求解一个非线性优化问题，我们怎么把它封装成dll再发布？  
其它的非线性优化库还有g2o。  