# 第三节 需要做的事情

20180508

* [ ] 怎么把自己用gitbook创作的书同步到网上，这样就可以方便查看了，最好能设置只能个人看。
* [ ] C\# Lamda表达式还是需要多看一些，自己写一些应用，用于Linq。
* [ ] Gitbook上怎么索引一个程序，这样就不要占用太多空间了。

```
using RS7.DataProcessing.Utility;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace RS7.DataProcessing.Numerics
{
    public class Matrix
    {
        public Matrix(int rows, int cols)
        {
            if (rows <= 0 || cols <= 0)
            {
                throw new ArgumentOutOfRangeException("At least one of the arguments are out of range!");
            }

            mRows    = rows;
            mColumns = cols;

            mData    = new double[rows * cols];
        }

        public Matrix(double[] data, int stride, bool copy = true)
        {
            if (stride <= 0)
            {
                throw new ArgumentException("Failed to construct Matrix: Invalid stride!");
            }

            mLength  = data.Length;
            mRows    = mLength / stride;
            mColumns = stride;

            if (copy)
            {
                mData = new double[mLength];
                Array.Copy(data, mData, mLength);
            }
            else
            {
                mData = data;
            }
        }

        private int      mRows;
        private int      mColumns;
        private int      mLength;
        private double[] mData;

        public int Rows
        {
            get { return mRows; }
        }

        public int Columns
        {
            get { return mColumns; }
        }

        public int Length
        {
            get { return mLength; }
        }

        public double[] Data
        {
            get { return mData; }
        }

        public double this[int row, int col]
        {
            get { return mData[row * mColumns + col]; }
            set { mData[row * mColumns + col] = value; }
        }

        public static Matrix IdentityMatrix(int rank)
        {
            Matrix result = new Matrix(rank, rank);

            for (int i = 0; i < rank; i++)
            {
                result[i, i] = 1;
            }

            return result;
        }

        public Matrix Submatrix(int i, int j, int m, int n)
        {
            Matrix A = new Matrix(m, n);

            for (int xi = 0; xi < m; xi++)
            {
                for (int xj = 0; xj < n; xj++)
                {
                    A[xi, xj] = this[xi + i, xj + j];
                }
            }

            return A;
        }

        public Vector Column(int column)
        {
            Vector c = new Vector(Rows);

            for (int i = 0; i < Rows; i++)
            {
                c[i] = this[i, column];
            }

            return c;
        }

        public Vector Row(int row)
        {
            Vector c = new Vector(Columns);

            for (int i = 0; i < Columns; i++)
            {
                c[i] = this[row, i];
            }

            return c;
        }

        public static Matrix operator +(Matrix a, Matrix b)
        {
            if (a.Rows != b.Rows || a.Columns != b.Columns)
            {
                throw new ArgumentException("The rows and columns of the two matrices are incompatible for this operation.");
            }

            Matrix result = new Matrix(a.Rows, a.Columns);

            for (int i = 0; i < result.Rows; i++)
            {
                for (int j = 0; j < result.Columns; j++)
                {
                    result[i, j] = a[i, j] + b[i, j];
                }
            }

            return result;
        }

        public static Matrix operator -(Matrix a, Matrix b)
        {
            if (a.Rows != b.Rows || a.Columns != b.Columns)
            {
                throw new ArgumentException("The rows and columns of the two matrices are incompatible for this operation.");
            }

            Matrix result = new Matrix(a.Rows, a.Columns);

            for (int i = 0; i < result.Rows; i++)
            {
                for (int j = 0; j < result.Columns; j++)
                {
                    result[i, j] = a[i, j] - b[i, j];
                }
            }

            return result;
        }

        public static Matrix operator *(Matrix a, double v)
        {
            Matrix result = new Matrix(a.Rows, a.Columns);

            for (int i = 0; i < result.Rows; i++)
            {
                for (int j = 0; j < result.Columns; j++)
                {
                    result[i, j] = a[i, j] * v;
                }
            }

            return result;
        }

        public static Matrix operator *(double v, Matrix a)
        {
            Matrix result = new Matrix(a.Rows, a.Columns);

            for (int i = 0; i < result.Rows; i++)
            {
                for (int j = 0; j < result.Columns; j++)
                {
                    result[i, j] = a[i, j] * v;
                }
            }

            return result;
        }

        public static Matrix operator *(Matrix a, Matrix b)
        {
            if (a.Columns != b.Rows)
            {
                throw new ArgumentException("The rows and columns of the two matrices are incompatible for this operation.");
            }

            Matrix result = new Matrix(a.Rows, b.Columns);

            for (int i = 0; i < a.Rows; i++)
            {
                for (int j = 0; j < b.Columns; j++)
                {
                    for (int k = 0; k < a.Columns; k++)
                    {
                        result[i, j] += a[i, k] * b[k, j];
                    }
                }
            }

            return result;
        }

        public static Vector operator *(Matrix a, Vector b)
        {
            if (a.Columns != b.Length)
            {
                throw new ArgumentException("The columns of the matrix and the length of the vector are incompatible for this operation.");
            }

            Vector result = new Vector(a.Rows);

            for (int i = 0; i < a.Rows; i++)
            {
                for (int j = 0; j < a.Columns; j++)
                {
                    result[i] += a[i, j] * b[j];
                }
            }

            return result;
        }

        public static Matrix operator -(Matrix a)
        {
            return a * -1.0;
        }

        public void SwapRow(int row1, int row2)
        {
            double a;

            for (int i = 0; i < Columns; i++)
            {
                a             = this[row1, i];
                this[row1, i] = this[row2, i];
                this[row2, i] = a;
            }
        }

        public void SwapColumn(int col1, int col2)
        {
            double a;

            for (int i = 0; i < Rows; i++)
            {
                a             = this[i, col1];
                this[i, col1] = this[i, col2];
                this[i, col2] = a;
            }
        }

        public double Norm()
        {
            double r = 0;

            for (int i = 0; i < Rows; i++)
            {
                for (int j = 0; j < Columns; j++)
                {
                    r += this[i, j] * this[i, j];
                }
            }

            return Math.Sqrt(r);
        }
        
        public Matrix Trans()
        {
            Matrix result = new Matrix(Columns, Rows);

            for(int i = 0; i < Rows; i++)
            {
                for(int j = 0; j < Columns; j++)
                {
                    result[j, i] = this[i, j];
                }
            }

            return result;
        }

        public Matrix Clone()
        {
            Matrix result = new Matrix(Rows, Columns);

            for (int i = 0; i < Rows; i++)
            {
                for (int j = 0; j < Columns; j++)
                {
                    result[i, j] = this[i, j];
                }
            }

            return result;
        }

        public Matrix Diagonal()
        {
            if (Rows != Columns)
            {
                throw new InvalidOperationException("The rows and columns of the matrix are incompatible for this operation.");
            }

            Matrix m = new Matrix(Rows, Columns);

            for (int i = 0; i < Rows; i++)
            {
                m[i, i] = this[i, i];
            }

            return m;
        }

        public double DiagonalMax()
        {
            if (Rows != Columns)
            {
                throw new InvalidOperationException("The rows and columns of the matrix are incompatible for this operation.");
            }

            double var = this[0, 0];

            for (int i = 1; i < Rows; i++)
            {
                if (var < this[i, i])
                {
                    var = this[i, i];
                }
            }

            return var;
        }

        public Matrix Centered()
        {
            Matrix m = new Matrix(Rows, Columns);

            for (int col = 0; col < Columns; col++)
            {
                double mean = 0;

                for (int row = 0; row < Rows; row++)
                {
                    mean += this[row, col];
                }

                mean /= Rows;

                for (int row = 0; row < Rows; row++)
                {
                    m[row, col] = this[row, col] - mean;
                }
            }

            return m;
        }

        public Matrix Standardized()
        {
            Matrix m = new Matrix(Rows, Columns);

            for (int col = 0; col < Columns; col++)
            {
                double mean = 0;

                for (int row = 0; row < Rows; row++)
                {
                    mean += this[row, col];
                }

                mean /= Rows;

                double mse = 0;

                for (int row = 0; row < Rows; row++)
                {
                    mse += Math.Pow(this[row, col] - mean, 2);
                }

                double dev = Math.Sqrt(mse / Rows);

                for (int row = 0; row < Rows; row++)
                {
                    m[row, col] = dev != 0 ? (this[row, col] - mean) / dev : 0;
                }
            }

            return m;
        }

        public override string ToString()
        {
            StringBuilder builder = new StringBuilder();

            for (int i = 0; i < Rows; i++)
            {
                for (int j = 0; j < Columns; j++)
                {
                    builder.Append(this[i, j]);
                    builder.Append("\t");
                }
                builder.Append("\n");
            }

            return builder.ToString();
        }

        public string ToCompactString()
        {
            StringBuilder builder = new StringBuilder();

            for (int i = 0; i < Rows; i++)
            {
                for (int j = 0; j < Columns - 1; j++)
                {
                    builder.Append(this[i, j]);
                    builder.Append(",");
                }

                builder.Append(this[i, Columns - 1]);
                builder.Append(";");
            }

            return builder.ToString();
        }

        public static Matrix FromCompactString(string text)
        {
            if (string.IsNullOrEmpty(text))
            {
                return null;
            }

            string[] sections = text.Split(new char[] { ';' }, StringSplitOptions.RemoveEmptyEntries);

            if (sections == null || sections.Length == 0)
            {
                return null;
            }
            
            int rows = sections.Length;
            int cols = sections[0].Split(new char[] { ',' }, StringSplitOptions.RemoveEmptyEntries).Length;

            Matrix m = new Matrix(rows, cols);

            try
            {
                for (int i = 0; i < rows; i++)
                {
                    var segments = sections[i].Split(new char[] { ',' }, StringSplitOptions.RemoveEmptyEntries);

                    if (segments == null || segments.Length != cols)
                    {
                        return null;
                    }

                    for (int j = 0; j < cols; j++)
                    {
                        m[i, j] = Convert.ToDouble(segments[j]);
                    }
                }
            }
            catch (Exception ex)
            {
                Logger.Warn (ex.Message);
                Logger.Trace(ex.StackTrace);

                return null;
            }

            return m;
        }


    }
}

```



