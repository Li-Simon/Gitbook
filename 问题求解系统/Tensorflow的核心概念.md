#Tensorflow的核心概念
tf的核心是围绕Graph, Variable, Session展开的，简而言之，就是Tensor沿着Graph传递闭包完成Flow的过程。

### Graph

TensorFlow is a way of representing computation without actually performing it until asked. The first step to learn Tensorflow is to understand its main key feature, the "computational graph" approach. Basically, all Tensorflow codes contain two important parts:  
1. 构建Graph,它表示计算的数据流  
2. 运行一个Session，它执行graph中的操作

我们以下面一个例子来理解tf来基于graph进行计算的[^2]：

```py
import tensorflow as tf
x = 2
y = 3
add_op = tf.add(x, y, name='Add')
mul_op = tf.multiply(x, y, name='Multiply')
pow_op = tf.pow(add_op, mul_op, name='Power')
useless_op = tf.multiply(x, add_op, name='Useless')

with tf.Session() as sess:
    pow_out, useless_out = sess.run([pow_op, useless_op])
```

![](/assets/tf_graph_ex1.png)\#\#\#

#### ReLU Graph

![](/assets/Graph_ReLU.png)

### Session
To compute anything, a graph must be launched in a session. Technically, session places the graph ops on hardware such as CPUs or GPUs and provides methods to execute them. In our example, to run the graph and get the value for c the following code will create a session and execute the graph by running 'c':  

```py
import tensorflow as tf
a = 2
b = 3
c = tf.add(a, b, name='Add')
print(c)  
Tensor("Add:0", shape=(), dtype=int32)  
```


```py
with tf.Session() as sess:
    print(sess.run(c))
5
```






### Tensor

Matrix表示二维线性映射，Tensor表示多维线性映射。TF中Tensor的维数描述为阶，数值是0阶，向量是1阶，矩阵是2阶，以此类推，可以表示n阶高维数据。  
Tensor定义和运算主要是调用Eigen矩阵计算库完成的。

Tensor的定义在tensorflow/core/framework/tensor.h中。

#### Constant

As the name speaks for itself, **Constants  **are used as constants. They create a node that takes value and it does not change. You can simply create a constant tensor using  **tf.constant, **It accepts the five arguments:

```py
tf.constant(value, dtype=None, shape=None, name='Const', verify_shape=False)
n [3]:
# create graph
a = tf.constant(2)
b = tf.constant(3)
c = a + b
# launch the graph in a session
with tf.Session() as sess:
    print(sess.run(c))
```

#### VARIABLE

##### Create Variables {#2.1.-Create-Variables}

create a variable, we should use **tf.Variable **as:

```py
# Create a variable.
w = tf.Variable(<initial-value>, name=<optional-name>)
#Some examples of creating scalar and matrix variables are as follows:
s = tf.Variable(2, name="scalar") 
m = tf.Variable([[1, 2], [3, 4]], name="matrix") 
W = tf.Variable(tf.zeros([784,10]))
```

##### Initialize Variables {#2.2.-Initialize-Variables}

TensorFlow recommends to use the wraper **tf.get\_variable** instead as it accepts the name, shape, etc as its arguments with many more as follows:

```py
tf.get_variable(name,
                shape=None,
                dtype=None,
                initializer=None,
                regularizer=None,
                trainable=True,
                collections=None,
                caching_device=None,
                partitioner=None,
                validate_shape=True,
                use_resource=None,
                custom_getter=None,
                constraint=None)
```

变量必须被初始化才能被使用：

```py
# create graph
a = tf.get_variable(name="A", initializer=tf.constant(2))
b = tf.get_variable(name="B", initializer=tf.constant(3))
c = tf.add(a, b, name="Add")
# add an Op to initialize global variables
init_op = tf.global_variables_initializer()
# without this line, we will get "FailedPreconditionError: Attempting to use uninitialized value"

# launch the graph in a session
with tf.Session() as sess:
    # run the variable initializer operation
    sess.run(init_op)
    # now let's evaluate their value
    print(sess.run(a))
    print(sess.run(b))
    print(sess.run(c))
```

###### Example in neural network

```py
# create graph
weights = tf.get_variable(name="W", shape=[2,3], initializer=tf.truncated_normal_initializer(stddev=0.01))
biases = tf.get_variable(name="b", shape=[3], initializer=tf.zeros_initializer())

# add an Op to initialize global variables
init_op = tf.global_variables_initializer()

# launch the graph in a session
with tf.Session() as sess:
    # run the variable initializer
    sess.run(init_op)
    # now we can run our operations
    W, b = sess.run([weights, biases])
    print('weights = {}'.format(W))
    print('biases = {}'.format(b))

weights = [[-0.00376599 -0.00506956  0.00082394]
 [ 0.0016487   0.00981423 -0.00226094]]
biases = [0. 0. 0.]
```

#### Placeholder

Placeholder比variable更基本，它是一个变量我们将要指定的数据。Placehos是一些在执行时被喂进的数据。  
Placeholders are more basic than a variable. It is simply a variable that we asign data in a future time. Placeholders are nodes whose value is fed in at execution time. If we have inputs to our network that depend on some external data and we don't want our graph to depend on any real value while developing the graph, placeholders are the datatype we need. In fact, we can build the graph without any data. Therefore, placeholders don't need any initial value; only a datatype \(such as float32\) and a tensor shape so the graph still knows what to compute with even though it doesn't have any stored values yet.  
Some examples of creating placeholders are as follows:

```py
a = tf.constant([5, 5, 5], tf.float32, name='A')
b = tf.placeholder(tf.float32, shape=[3], name='B')
c = tf.add(a, b, name="Add")

with tf.Session() as sess:
    # create a dictionary:
    d = {b: [1, 2, 3]}
    # feed it to the placeholder
    print(sess.run(c, feed_dict=d))
```

[^1]: tensorflow代码解析——概览  [https://daiwk.github.io/posts/platform-tensorflow-code-analysis-overview.html](https://daiwk.github.io/posts/platform-tensorflow-code-analysis-overview.html)  

[^2]: EasyTensorflow [https://www.easy-tensorflow.com/tf-tutorials/basics/graph-and-session](https://www.easy-tensorflow.com/tf-tutorials/basics/graph-and-session)

