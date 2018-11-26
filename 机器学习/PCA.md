机器学习一般面对的是一个高维的问题，样本稀疏。容易面临严重的维数灾难。处理维数灾难的一个重要方法就是降维。确切的来说，有两种情形：
1. 基于距离的聚类问题。对于M个数据，定义距离后，M个数据张成一个MxM的距离矩阵，而且是对称矩阵。  
2. 基于数据的低秩分解。对于M个数据，每个数据是N维，我们是对这个数据集张成的MxN维矩阵进行降维。  
这就可以用到我们在矩阵计算中的一些方法，比如主成分分析(PCA),实际上我们是通过SVD来是实现PCA的，就是取最大的K个奇异值与奇异向量来实现矩阵的低秩分解。 
下面我们主要考虑第一种情况，也就是处理聚类问题。    
## SVD
对于任何一个MxD的矩阵X可以做如下分解：  
$$\kern{8 em} X = UDV^T$$  
其中$$U^TU=I_D,VTV=I_N$$,D是MxD的对角矩阵。   
$$\kern{8 em} XX^T = UDV^TVD^TU^T=UDD^TU^T$$  
$$\kern{8 em} X^TX = VD^DU^TUDV^T=VD^TDV^T$$  
是矩阵的本征值分解。因此可以通过上面两式来求解U，V。主要用到的是矩阵本征值，本征矢求解技巧。这都在矩阵计算(第五章)那一章讨论的内容。 
对于我们的情况M=D, 因此  
$$\kern{4 em}D^T=D$$ 
令$$B = X^TX$$，对B做特征值分解，得到  
$$\kern{4 em}B = V\Lambda V^T$$，
假设$$\Lambda$$的矩阵元按如下方式排序：  
$$\lambda_1 \ge \lambda_2 \ge ... \ge \lambda_M$$
## PCA
我们可以通过SVD来实现PCA,具体就是只取X的SVD中的前M个其一分量。  
$$\kern{8 em} X = UDV^T \approx U_MD_MV_M^T$$  
其中$$U_M,D_M,V_M$$对于矩阵X的前M个奇异值分量。 
取前d个奇异向量。选择一个比例t，一般取t = 95%，使得。  
$$\kern{4 em}\frac{\displaystyle \sum_{i=1}^d \lambda_i}{\displaystyle \sum_{i=1}^M \lambda_i} \ge t$$  



