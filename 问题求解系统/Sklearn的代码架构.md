# Sklearn的代码架构

### [API Reference](http://scikit-learn.org/stable/modules/classes.html)

1. #### [`sklearn.base`](http://scikit-learn.org/stable/modules/classes.html#module-sklearn.base): Base classes and utility functions
2. #### [`sklearn.calibration`](http://scikit-learn.org/stable/modules/classes.html#module-sklearn.calibration): Probability Calibration
3. #### [`sklearn.cluster`](http://scikit-learn.org/stable/modules/classes.html#module-sklearn.cluster): Clustering
4. #### [`sklearn.compose`](http://scikit-learn.org/stable/modules/classes.html#module-sklearn.compose): Composite Estimators
5. #### [`sklearn.covariance`](http://scikit-learn.org/stable/modules/classes.html#module-sklearn.covariance): Covariance Estimators
6. #### [`sklearn.cross_decomposition`](http://scikit-learn.org/stable/modules/classes.html#module-sklearn.cross_decomposition): Cross decomposition
7. #### [`sklearn.datasets`](http://scikit-learn.org/stable/modules/classes.html#module-sklearn.datasets): Datasets
8. #### [`sklearn.decomposition`](http://scikit-learn.org/stable/modules/classes.html#module-sklearn.decomposition): Matrix Decomposition
9. #### [`sklearn.discriminant_analysis`](http://scikit-learn.org/stable/modules/classes.html#module-sklearn.discriminant_analysis): Discriminant Analysis
10. #### [`sklearn.dummy`](http://scikit-learn.org/stable/modules/classes.html#module-sklearn.dummy): Dummy estimators
11. #### [`sklearn.ensemble`](http://scikit-learn.org/stable/modules/classes.html#module-sklearn.ensemble): Ensemble Methods
12. #### [`sklearn.exceptions`](http://scikit-learn.org/stable/modules/classes.html#module-sklearn.exceptions): Exceptions and warnings
13. #### [`sklearn.feature_extraction`](http://scikit-learn.org/stable/modules/classes.html#module-sklearn.feature_extraction): Feature Extraction
14. #### [`sklearn.feature_selection`](http://scikit-learn.org/stable/modules/classes.html#module-sklearn.feature_selection): Feature Selection
15. #### [`sklearn.gaussian_process`](http://scikit-learn.org/stable/modules/classes.html#module-sklearn.gaussian_process): Gaussian Processes
16. #### [`sklearn.isotonic`](http://scikit-learn.org/stable/modules/classes.html#module-sklearn.isotonic): Isotonic regression
17. #### [`sklearn.impute`](http://scikit-learn.org/stable/modules/classes.html#module-sklearn.impute): Impute
18. #### [`sklearn.kernel_approximation`](http://scikit-learn.org/stable/modules/classes.html#module-sklearn.kernel_approximation)Kernel Approximation
19. #### [`sklearn.kernel_ridge`](http://scikit-learn.org/stable/modules/classes.html#module-sklearn.kernel_ridge)Kernel Ridge Regression
20. #### [`sklearn.linear_model`](http://scikit-learn.org/stable/modules/classes.html#module-sklearn.linear_model): Generalized Linear Models
21. #### [`sklearn.manifold`](http://scikit-learn.org/stable/modules/classes.html#module-sklearn.manifold): Manifold Learning
22. #### [`sklearn.metrics`](http://scikit-learn.org/stable/modules/classes.html#module-sklearn.metrics): Metrics
23. #### [`sklearn.mixture`](http://scikit-learn.org/stable/modules/classes.html#module-sklearn.mixture): Gaussian Mixture Models
24. #### [`sklearn.model_selection`](http://scikit-learn.org/stable/modules/classes.html#module-sklearn.model_selection): Model Selection
25. #### [`sklearn.multiclass`](http://scikit-learn.org/stable/modules/classes.html#module-sklearn.multiclass): Multiclass and multilabel classification
26. #### [`sklearn.multioutput`](http://scikit-learn.org/stable/modules/classes.html#module-sklearn.multioutput): Multioutput regression and classification
27. #### [`sklearn.naive_bayes`](http://scikit-learn.org/stable/modules/classes.html#module-sklearn.naive_bayes): Naive Bayes
28. #### [`sklearn.neighbors`](http://scikit-learn.org/stable/modules/classes.html#module-sklearn.neighbors): Nearest Neighbors
29. #### [`sklearn.neural_network`](http://scikit-learn.org/stable/modules/classes.html#module-sklearn.neural_network): Neural network models
30. #### [`sklearn.pipeline`](http://scikit-learn.org/stable/modules/classes.html#module-sklearn.pipeline): Pipeline
31. #### [`sklearn.preprocessing`](http://scikit-learn.org/stable/modules/classes.html#module-sklearn.preprocessing): Preprocessing and Normalization
32. #### [`sklearn.random_projection`](http://scikit-learn.org/stable/modules/classes.html#module-sklearn.random_projection): Random projection
33. #### [`sklearn.semi_supervised`](http://scikit-learn.org/stable/modules/classes.html#module-sklearn.semi_supervised)Semi-Supervised Learning
34. #### [`sklearn.svm`](http://scikit-learn.org/stable/modules/classes.html#module-sklearn.svm): Support Vector Machines
35. #### [`sklearn.tree`](http://scikit-learn.org/stable/modules/classes.html#module-sklearn.tree): Decision Trees
36. #### [`sklearn.utils`](http://scikit-learn.org/stable/modules/classes.html#module-sklearn.utils): Utilities

### python类的继承

```py
class Person(object):
    pass

class Child(Person):                 # Child 继承 Person
    pass

May = Child()
Peter = Person()    

print(isinstance(May,Child))         # True
print(isinstance(May,Person))        # True
print(isinstance(Peter,Child))       # False
print(isinstance(Peter,Person))      # True
print(issubclass(Child,Person))      # True
```

class Child\(Person\)表示Child继承于Person，任何类最终都可以追溯到根类object，这与Java,C\#是一样的。

#### 多态
定义：允许不同类的对象对同一消息做出响应。即同一消息可以根据发送对象的不同而采用多种不同的行为方式。(发送消息就是函数调用)    
实现多态的技术称为:动态绑定，是指在执行期间判断所引用对象的实际类型，根据其实际的类型调用其相应的方法。    
多态的作用：消除类型之间的耦合关系。  
子类覆盖父类的函数实现，也就是子类重新实现父类的函数。不同的子类对相同的父类函数可以有不同的实现，因此多态就是"一个接口，多种实现"。  
多态就是指程序中定义的引用变量所指向的具体类型和通过该引用变量发出的方法调用在编译时并不确定，而是在程序运行期间才确定，即一个引用变量到底会指向哪个类的实例对象，该引用变量发出的方法调用到底是哪个类中实现的方法，必须在由程序运行期间才能确定。  

#### 多态的好处
继承和堕胎本质的目的是为了代码重用和解耦。而重用和解耦是为了减少开发时间和减少错误。最终达到降低成本的目的。  
多态体现的就是“对扩展开放，对修改封闭”。封闭就是子类不能直接修改父类的其它函数，扩展开放也就是子类可以重写父类的函数。    
1. 可替换性(substitutability)。多态对已经存在代码具有可替换性。  
2. 可扩充性(extensibility)。多态对代码具有可扩充性，增加新的子类不影响已经存在类的多态性，继承性，以及其他特性的运行和操作。实际上新加子类更容易获得多态功能。例如，在实现圆锥，半圆锥以及半球体的多态基础上，很容易增加球体类的多态性。  
3. 接口性(interface-ability)。多态是超类通过方法签名，向子类提供了一个共同接口，由子类来完善或者覆盖它而实现的。  
4. 灵活性(flexibility)。它在应用中体现了灵活多样的操作，提高了使用效率。  
5.简化性(simplicity)。多态简化对应用软件的编写和修改过程，尤其在处理大量对象和操作时，这个特点尤为突出和重要。  
1. 提高了代码的维护性\(继承保证\)  
2. 提高了代码的扩展性\(由多态保证\)  
   



