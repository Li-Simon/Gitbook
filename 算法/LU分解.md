# LU分解

任何非奇异方阵都可以分解成上三角阵与下三角阵之积

$$\begin{bmatrix}a_{11}&a_{12}&\cdots&a_{1n}\\ a_{21}&a_{22}&\cdots&a_{2n}\\\cdots&\cdots&\cdots&\cdots\\a_{n1}&a_{n2}&\cdots&a_{nn}\end{bmatrix} = 
\begin{bmatrix}l_{11}&0&\cdots&0\\ l_{21}&l_{22}&\cdots&0\\\cdots&\cdots&\cdots&\cdots\\l_{n1}&l_{n2}&\cdots&l_{nn}\end{bmatrix}*
\begin{bmatrix}u_{11}&u_{12}&\cdots&u_{1n}\\ 0&u_{22}&\cdots&a_{2n}\\\cdots&\cdots&\cdots&\cdots\\0&0&\cdots&u_{nn}\end{bmatrix}$$  
对比两边矩阵的，可以求得：  
但是编程时，行列都是从0开始时，要注意转换。  
第1行：$$a_{1j} = u_{1j}, j = 1, 2,..,n. => u_{1j} = a_{1j}$$。  
第1列：$$a_{j1} = l_{j1}u_{11}, j = 1, 2,..,n. => l_{j1} = a_{j1}/u_{11}$$。  
...。  
第k行：$$a_{kj} = \sum_{i=1}^{i=k} l_{ki}u_{ij}, => u_{kj} = a_{kj} - \sum_{i=1}^{i=k-1} l_{ki}u_{ij}$$。  
第k列：$$a_{jk} = \sum_{i=1}^{i=k} l_{ji}u_{ik}, => u_{jk} = [a_{jk} - \sum_{i=1}^{i=k-1} l_{ji}u_{ik}]/u_{kk}$$。

因为前k-1行的$$u_{ij}$$都已知，前k-1列的$$l_{ij}$$都已知,因此可以求得第k行$$u_{ij}$$，第k列的$$l_{ij}$$。  
问题：得保证$$a_{11}$$非0，以及矩阵非奇异。

# 利用LU分解求线性方程组的解

求解线性方程组 Ax=b相当于求解LUx=b;  
设Y = UX; 因此LY = b;首先求解LY = b,  
$$\begin{bmatrix}l_{11}&0&\cdots&0\\ l_{21}&l_{22}&\cdots&0\\\cdots&\cdots&\cdots&\cdots\\l_{n1}&l_{n2}&\cdots&l_{nn}\end{bmatrix}\begin{bmatrix}y_{1}\\y_{2}\\\cdots&\\y_{n}\end{bmatrix}= 
\begin{bmatrix}b_{1}\\b_{2}\\\cdots&\\b_{n}\end{bmatrix}$$  
求解上面的方程：  
第1行：$$y_{1} = b_{1}$$。  
对于第k行：$$b_{k} = \sum_{i=1}^{i=k}l_{ki}y_{i} =>y_{k} = b_{k} - \sum_{i=1}^{i=k-1}l_{ki}y_{i}$$。  
求得Y之后，代入Y=UX求得X:  
$$\begin{bmatrix}u_{11}&u_{12}&\cdots&u_{1n}\\ 0&u_{22}&\cdots&u_{2n}\\\cdots&\cdots&\cdots&\cdots\\0&0&\cdots&u_{nn}\end{bmatrix}\begin{bmatrix}x_{1}\\x_{2}\\\cdots&\\x_{n}\end{bmatrix}= 
\begin{bmatrix}y_{1}\\y_{2}\\\cdots&\\y_{n}\end{bmatrix}$$  
对于上三角矩阵，我们从第n行开始求解  
对第n行：$$y_{n} = u_{nn}x_{n} => x_{n} = y_{n}/u_{nn}$$。  
...。  
对第k行：$$y_{k} = \sum_{i=k}^{i=n}u_{ki}x_{i} => x_{k} = [y_{n}-\sum_{i=k+1}^{i=n}u_{ki}x_{i}]/u_{kk}$$  
这样通过LU分解矩阵就求得了线性方程组的就X.

# 矩阵求逆

我们可以利用LU分解来求非奇异方阵的逆矩阵。  
**AB=I**  
$$\begin{bmatrix}a_{11}&a_{12}&\cdots&a_{1n}\\ a_{21}&a_{22}&\cdots&a_{2n}\\\cdots&\cdots&\cdots&\cdots\\a_{n1}&a_{n2}&\cdots&a_{nn}\end{bmatrix}*
\begin{bmatrix}b_{11}&b_{12}&\cdots&b_{1n}\\ b_{21}&b_{22}&\cdots&b_{2n}\\\cdots&\cdots&\cdots&\cdots\\b_{n1}&b_{n2}&\cdots&b_{nn}\end{bmatrix}=
\begin{bmatrix}1&0&\cdots&0\\ 0&1&\cdots&1\\\cdots&\cdots&\cdots&\cdots\\0&0&\cdots&u_{nn}\end{bmatrix}$$  
可以分解成求:  
$$\begin{bmatrix}a_{11}&a_{12}&\cdots&a_{1n}\\ a_{21}&a_{22}&\cdots&a_{2n}\\\cdots&\cdots&\cdots&\cdots\\a_{n1}&a_{n2}&\cdots&a_{nn}\end{bmatrix}*
\begin{bmatrix}b_{1k}\\b_{2k}\\\cdots\\b_{nk}\end{bmatrix}=
\begin{bmatrix}0\\0\\\cdots\\1\\\cdots\\0\end{bmatrix}$$  
右边的列，就只是第k行值非0；  
$$A*b_{k} = e_{k}$$,对所有的$$e_{k}$$求出$$b_{k}$$就可以得到A的逆矩阵$$A^{-1} = B$$  
实际求解中把A 换成LU来减少计算量。总的计算开销还是$$n^{3}$$。但是这样并不比直接的高斯消元法来的快。

算法实现如下。

```cpp
//LU
template<class T>
void CMatrix<T>::LU(CMatrix &mat, int N, CMatrix* L, CMatrix* U)
{
    for (int k = 0; k <N; k++)
    {
        for (int j = k; j<N;j++)
        {
            T U_k_j = mat.Get(k, j);
            T L_j_k = mat.Get(j, k);
            for (int i = 0; i <k; i++)
            {
                U_k_j -= L->Get(k, i)*U->Get(i, j);
            }
            U->Set(k, j, U_k_j);

            for (int i = 0; i < k; i++)
            {
                L_j_k -= L->Get(j, i)*U->Get(i, k);
            }
            L_j_k = L_j_k / U->Get(k, k);
            L->Set(j, k, L_j_k);

        }
    }
}

//solve linear algebra equations
CVector Solve(CMatrix<double>& mat, CVector& vec)
{
    CVector X(vec.Size());
    CVector Y(vec.Size());
    if (mat.Columns() != mat.Rows() && mat.Rows() != vec.Size())
    {
        printf("Dimension not match!");
        return X;
    }
    CMatrix<double> L(vec.Size(), vec.Size());
    CMatrix<double> U(vec.Size(), vec.Size());
    mat.LU(mat, vec.Size(), &L, &U);
    Y = SolveLow(L, vec);
    cout << "Y\n" << Y;
    X = SolveUpper(U, Y);
    cout << "X\n" << X;
    return X;
}

CVector SolveLow(CMatrix<double>& mat, CVector& vec)
{
    CVector vecRes(vec.Size());
    if (mat.Columns() != mat.Rows() && mat.Rows() != vec.Size())
    {
        printf("Dimension not match!");
        return vecRes;
    }

    for (int k = 0; k < vec.Size(); k++)
    {
        double mRes = 0;
        mRes = vec.Get(k);
        for (int i = 0; i < k; i++)
        {
            mRes -= mat.Get(k, i)*vecRes.Get(i);
        }
        vecRes.Set(k, mRes);
    }
    return vecRes;
}

CVector SolveUpper(CMatrix<double>& mat, CVector& vec)
{
    CVector vecRes(vec.Size());
    if (mat.Columns() != mat.Rows() && mat.Rows() != vec.Size())
    {
        printf("Dimension not match!");
        return vecRes;
    }

    for (int k = vec.Size() -1; k >=0 ; k--)
    {
        double mRes = 0;
        mRes = vec.Get(k);
        for (int i = k+1; i <vec.Size(); i++)
        {
            mRes -= mat.Get(k, i)*vecRes.Get(i);
        }
        mRes = mRes / mat.Get(k, k);
        vecRes.Set(k, mRes);
    }
    return vecRes;
}

//inverse matrix
template<class T>
CMatrix<T>  CMatrix<T>::Inv()
{
    CMatrix result = *this;
    CMatrix<double> L(mRows, mColumns);
    CMatrix<double> U(mRows, mColumns);
    CMatrix<double> InvMat(mRows, mColumns);
    LU(result,mRows, &L, &U);
    for (int col = 0; col < mColumns; col++)
    {
        CVector vec(mRows, col);
        CVector mSolution(mRows);
        mSolution = SolveLow(L, vec);
        mSolution = SolveUpper(U, mSolution);
        for (int row = 0; row<mRows; row++)
        {
            InvMat.Set(row, col, mSolution.Get(row));
        }
    }
    return InvMat;
}
```



