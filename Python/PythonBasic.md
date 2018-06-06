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





