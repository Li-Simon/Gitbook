# 常用的python数据处理函数

## pandas

### 处理结构化数据\(Data Retrieval\)DataFrame

#### List of Dictionaries to DataFrame

```py
In[27]: import pandas as pd
In[28]: d = [{'city':'Delhi',"data":1000},
...: {'city':'Bangalore',"data":2000},
...: {'city':'Mumbai',"data":1000}]
In[29]: pd.DataFrame(d)
Out[29]:
city data
0 Delhi 1000
1 Bangalore 2000
2 Mumbai 1000
In[30]: df = pd.DataFrame(d)
In[31]: df
Out[31]:
city data
0 Delhi 1000
1 Bangalore 2000
2 Mumbai 1000
```

#### CSV Files to DataFrame

```python
import pandas as pd
In [2]: city_data = pd.read_csv(filepath_or_buffer='simplemaps-worldcities-basic.csv')
In [3]: city_data.head(n=10)
Out[3]:
city city_ascii lat lng pop country \
0 Qal eh-ye Now Qal eh-ye 34.983000 63.133300 2997 Afghanistan
1 Chaghcharan Chaghcharan 34.516701 65.250001 15000 Afghanistan
2 Lashkar Gah Lashkar Gah 31.582998 64.360000 201546 Afghanistan
3 Zaranj Zaranj 31.112001 61.886998 49851 Afghanistan
4 Tarin Kowt Tarin Kowt 32.633298 65.866699 10000 Afghanistan
5 Zareh Sharan Zareh Sharan 32.850000 68.416705 13737 Afghanistan
6 Asadabad Asadabad 34.866000 71.150005 48400 Afghanistan
7 Taloqan Taloqan 36.729999 69.540004 64256 Afghanistan
8 Mahmud-E Eraqi Mahmud-E Eraqi 35.016696 69.333301 7407 Afghanistan
9 Mehtar Lam Mehtar Lam 34.650000 70.166701 17345 Afghanistan
```

#### Database to DataFrame

可以从数据库中读取数据  
server = 'xxxxxxxx' \# Address of the database server  
user = 'xxxxxx' \# the username for the database server  
password = 'xxxxx' \# Password for the above user  
database = 'xxxxx' \# Database in which the table is present  
conn = pymssql.connect\(server=server, user=user, password=password, database=database\)  
query = "select \* from some\_table"  
df = pd.read\_sql\(query, conn\)

### Data Access

#### Head and Tail

head提供dataframe前面几行数据，tail提供dataframe倒数几行数据。

```py
In [11]: city_data.tail()
Out[11]:
city city_ascii lat lng pop country \
7317 Mutare Mutare -18.970019 32.650038 216785.0 Zimbabwe
7318 Kadoma Kadoma -18.330006 29.909947 56400.0 Zimbabwe
7319 Chitungwiza Chitungwiza -18.000001 31.100003 331071.0 Zimbabwe
7320 Harare Harare -17.817790 31.044709 1557406.5 Zimbabwe
7321 Bulawayo Bulawayo -20.169998 28.580002 697096.0 Zimbabwe
```

#### Slicing and Dicing

数据切片，提取特定标签的数据。

```py
In [12]: series_es = city_data.lat//提取lat标签的数据
In [13]: type(series_es)
Out[13]: pandas.core.series.Series
In [14]: series_es[1:10:2]
Out[14]:
1 34.516701
3 31.112001
5 32.850000
7 36.729999
9 34.650000
Name: lat, dtype: float64
In [15]: series_es[:7]
Out[15]:
0 34.983000
1 34.516701
2 31.582998
3 31.112001
4 32.633298
5 32.850000
6 34.866000
Name: lat, dtype: float64
In [23]: series_es[:-7315]
Out[23]:
0 34.983000
1 34.516701
2 31.582998
3 31.112001
4 32.633298
5 32.850000
6 34.866000
Name: lat, dtype: float64
```

##### iloc

提取多少行\(数据样本数目\)，多少列\(标签数目\)。比如提取前4个标签的前5行数据。

```py
In [28]: city_data.iloc[:5,:4]
Out[28]:
city city_ascii lat lng
0 Qal eh-ye Now Qal eh-ye 34.983000 63.133300
1 Chaghcharan Chaghcharan 34.516701 65.250001
2 Lashkar Gah Lashkar Gah 31.582998 64.360000
3 Zaranj Zaranj 31.112001 61.886998
4 Tarin Kowt Tarin Kowt 32.633298 65.866699
```

##### 带判断的搜索

select cities that have population of more than 10 million and select columns that start with the letter l:

```py
In [56]: city_data[city_data['pop'] >
10000000][city_data.columns[pd.Series(city_data.columns).str.
startswith('l')]]
Out[53]:
lat lng
360 -34.602502 -58.397531
1171 -23.558680 -46.625020
2068 31.216452 121.436505
3098 28.669993 77.230004
3110 19.016990 72.856989
3492 35.685017 139.751407
4074 19.442442 -99.130988
4513 24.869992 66.990009
5394 55.752164 37.615523
6124 41.104996 29.010002
7071 40.749979 -73.980017
```

### Data Operations

Using the values attribute of the output dataframe, we can treat it in the same way as a numpy array.利用值属性，我们可以为dataframe填充数据，做缺失值处理。

```py
In [55]: df = pd.DataFrame(np.random.randn(8, 3),
...: columns=['A', 'B', 'C'])
In [56]: df
Out[56]:
A B C
0 -0.271131 0.084627 -1.707637
1 1.895796 0.590270 -0.505681
2 -0.628760 -1.623905 1.143701
3 0.005082 1.316706 -0.792742
4 0.135748 -0.274006 1.989651
5 1.068555 0.669145 0.128079
6 -0.783522 0.167165 -0.426007
7 0.498378 -0.950698 2.342104
In [58]: nparray = df.values
In [59]: type(nparray)
Out[59]: numpy.ndarray
```

##### Missing Data and the fillna Function

填补缺失值。

```py
In [65]: df.iloc[4,2] = NA
In [66]: df
Out[66]:
A B C
0 -0.271131 0.084627 -1.707637
1 1.895796 0.590270 -0.505681
2 -0.628760 -1.623905 1.143701
3 0.005082 1.316706 -0.792742
4 0.135748 -0.274006 NaN
5 1.068555 0.669145 0.128079
6 -0.783522 0.167165 -0.426007
7 0.498378 -0.950698 2.342104
In [70]: df.fillna (0)
Out[70]:
A B C
0 -0.271131 0.084627 -1.707637
1 1.895796 0.590270 -0.505681
2 -0.628760 -1.623905 1.143701
3 0.005082 1.316706 -0.792742
4 0.135748 -0.274006 0.000000
5 1.068555 0.669145 0.128079
6 -0.783522 0.167165 -0.426007
7 0.498378 -0.950698 2.342104
```

##### Descriptive Statistics Functions 统计属性

```py
In [76]: columns_numeric = ['lat','lng','pop']
In [78]: city_data[columns_numeric].mean()
Out[78]:
lat 20.662876
lng 10.711914
pop 265463.071633
dtype: float64

In [79]: city_data[columns_numeric].sum()
Out[79]:
lat 1.512936e+05
lng 7.843263e+04
pop 1.943721e+09
dtype: float64

In [80]: city_data[columns_numeric].count()
Out[80]:
lat 7322
lng 7322
pop 7322
dtype: int64

In [81]: city_data[columns_numeric].median()
Out[81]:
lat 26.792730
lng 18.617509
pop 61322.750000
dtype: float64

In [83]: city_data[columns_numeric].quantile(0.8)
Out[83]:
lat 46.852480
lng 89.900018
pop 269210.000000
dtype: float64

In [85]: city_data[columns_numeric].sum(axis = 1)
Out[85]:
0 3.095116e+03
1 1.509977e+04
2 2.016419e+05
3 4.994400e+04
4 1.009850e+04
```

Describe用来出数据的所有统计属性。  
Pandas also provides us with another very handy function called describe. This function will calculate the most important statistics for numerical data in one go so that we don’t have to use individual functions.

```py
In [86]: city_data[columns_numeric].describe()
Out[86]:
lat lng pop
count 7322.000000 7322.000000 7.322000e+03
mean 20.662876 10.711914 2.654631e+05
std 29.134818 79.044615 8.287622e+05
min -89.982894 -179.589979 -9.900000e+01
25% -0.324710 -64.788472 1.734425e+04
50% 26.792730 18.617509 6.132275e+04
75% 43.575448 73.103628 2.001726e+05
max 82.483323 179.383304 2.200630e+07
```

### Concatenating Dataframes

由于我们需要处理的数据通常有多个，因此我们需要合并这些数据。pandas提供了很多函数来支持数据的合并。

#### Concatenating Using the concat method

合并两组，每组随机选择3个样本。

```py
In [25]: city_data1 = city_data.sample(3)
In [26]: city_data2 = city_data.sample(3)
In [29]: city_data_combine = pd.concat([city_data1,city_data2])
In [30]: city_data_combine
Out[30]:
city city_ascii lat lng pop \
4255 Groningen Groningen 53.220407 6.580001 198941.0
5171 Tambov Tambov 52.730023 41.430019 296207.5
4204 Karibib Karibib -21.939003 15.852996 6898.0
4800 Focsani Focsani 45.696551 27.186547 92636.5
1183 Pleven Pleven 43.423769 24.613371 110445.5
7005 Indianapolis Indianapolis 39.749988 -86.170048 1104641.5

country iso2 iso3 province
4255 Netherlands NL NLD Groningen
5171 Russia RU RUS Tambov
4204 Namibia NaN NAM Erongo
4800 Romania RO ROU Vrancea
1183 Bulgaria BG BGR Pleven
7005 United States of America US USA Indiana
Another
```

另外一个场景是，我们对同一个数据集的不同columns进行合并，也就是对标签进行合并。index就是样本标号。

```py
In [32]: df1 = pd.DataFrame({'col1': ['col10', 'col11', 'col12', 'col13'],
...: 'col2': ['col20', 'col21', 'col22', 'col23'],
...: 'col3': ['col30', 'col31', 'col32', 'col33'],
...: 'col4': ['col40', 'col41', 'col42', 'col43']},
...: index=[0, 1, 2, 3])

In [33]: df1
Out[33]:
col1 col2 col3 col4
0 col10 col20 col30 col40
1 col11 col21 col31 col41
2 col12 col22 col32 col42
3 col13 col23 col33 col43
In [34]: df4 = pd.DataFrame({'col2': ['col22', 'col23', 'col26', 'col27'],
...: 'Col4': ['Col42', 'Col43', 'Col46', 'Col47'],
...: 'col6': ['col62', 'col63', 'col66', 'col67']},
...: index=[2, 3, 6, 7])
In [37]: pd.concat([df1,df4], axis=1)
Out[37]:
col1 col2 col3 col4 Col4 col2 col6
0 col10 col20 col30 col40 NaN NaN NaN
1 col11 col21 col31 col41 NaN NaN NaN
2 col12 col22 col32 col42 Col42 col22 col62
3 col13 col23 col33 col43 Col43 col23 col63
6 NaN NaN NaN NaN Col46 col26 col66
7 NaN NaN NaN NaN Col47 col27 col67
```

#### Database Style Concatenations Using the merge Command

The most familiar way to concatenate data \(for those acquainted with relational databases\) is using the join operation provided by the databases. Pandas provides a database friendly set of join operations for dataframes. These operations are optimized for high performance and are often the preferred method for joining disparate dataframes.  
 Joining by columns: This is the most natural way of joining two dataframes. In this method, we have two dataframes sharing a common column and we can join the two dataframes using that column. The pandas library has a full range of join operations \(inner, outer, left, right, etc.\) and we will demonstrate the use of inner join in this sub-section. You can easily figure out how to do the rest of join operations by checking out the pandas documentation.

For this example, we will break our original cities data into two different dataframes, one having the city information and the other having the country information. Then, we can join them using one of the shared common columns.

###### Lasso输出系数

```py
    def train(self):
        x_train, y_train, x_test, y_test = self.load_data()
        lasso = Lasso(random_state=0)
        alphas = np.logspace(-4, -0.5, 30)
        estimator = GridSearchCV(lasso, dict(alpha=alphas))
        estimator.fit(x_train, y_train)
        lasso.fit(x_train, y_train)//必须先对lasso使用fit，才可以使用coef_
        print "coef_ = ", lasso.coef_
        return estimator
```



