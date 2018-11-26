## SVD

对于任何一个DxM的矩阵X可以做如下分解：  
$$\kern{8 em} X = UDV^T$$  
其中$$U^TU=I_D,VTV=I_N$$,D是对角矩阵。  
$$\kern{8 em} XX^T = UDV^TVDU^T=UD^2U^T$$  
$$\kern{8 em} X^TX = VDU^TUDV^T=VD^2V^T$$  
是矩阵的本征值分解。因此可以通过上面两式来求解U，V。主要用到的是矩阵本征值，本征矢求解技巧。

## PCA

我们可以通过SVD来实现PCA,具体就是只取X的SVD中的前M个其一分量。  
$$\kern{8 em} X = UDV^T \approx U_MD_MV_M^T$$  
其中$$U_M,D_M,V_M$$对于矩阵X的前M个奇异值分量。

