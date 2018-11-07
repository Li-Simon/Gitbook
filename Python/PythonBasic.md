# PyBasic

```py
dicFile = open('train_1.txt', 'r')#打开数据  
print '开始装载数据...'  
txtDict = {}#建立字典  
while True:  
    line = dicFile.readline()  
    if line == '':  
        break  
    index = line.find('\t')#以tab键为分割  
    key = line[:index]  
    value = line[index:]  
    txtDict[key] = value#加入字典  
dicFile.close()  
##查找字典  
srcFile = open('train1.txt', 'r')#要匹配的key  
destFile = open('match.txt', 'w')#符合字典的写入里面  
while True:  
    line = srcFile.readline()  
    if line == '':  
        break  
    index = line.find(' ')  
    key = line[:index]  
    if txtDict.has_key(key):      
        destFile.write(key)  
        destFile.write(txtDict[key])         
    else:  
        badFile.write(key)  
        badFile.write('\n')  
print '全部完成！'  
destFile.close()  
srcFile.close()
```

还需要保存一份Jupyter笔记，用于python代码的实验：

### 调用graphviz库来实现可视化

必须通过conda install python-graphviz安装graphviz

```py
import graphviz 
from sklearn import tree
from sklearn.datasets import load_iris
iris = load_iris()
clf = tree.DecisionTreeClassifier()
clf = clf.fit(iris.data, iris.target)
dot_data = tree.export_graphviz(clf, out_file=None) 
graph = graphviz.Source(dot_data) 
graph.render("iris") 
dot_data = tree.export_graphviz(clf, out_file=None, 
                         feature_names=iris.feature_names,  
                         class_names=iris.target_names,  
                         filled=True, rounded=True,  
                         special_characters=True)
graph = graphviz.Source(dot_data)  
graph
```

结果图：![](/assets/graphviz_iris.png)

