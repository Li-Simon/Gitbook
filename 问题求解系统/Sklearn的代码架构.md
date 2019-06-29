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





