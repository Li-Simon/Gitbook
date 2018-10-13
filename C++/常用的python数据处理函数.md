# 常用的python数据处理函数

## pandas

### 处理结构化数据(Data Retrieval)DataFrame
####List of Dictionaries to DataFrame
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

###Data Access
####Head and Tail



