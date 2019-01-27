#Tensorflow


####pooling layers
#####Advantages:   
Decrease the size of the output and prevent overfitting. Preventing overfitting is a consequence of reducing the output size, which in turn, reduces the number of parameters in future layers.

Recently, pooling layers have fallen out of favor. Some reasons are:    
1. Recent datasets are so big and complex we're more concerned about underfitting.   
2. Dropout is a much better regularizer.   
3. Pooling results in a loss of information. Think about the max pooling operation as an example.   
4. We only keep the largest of n numbers, thereby disregarding n-1 numbers completely.   