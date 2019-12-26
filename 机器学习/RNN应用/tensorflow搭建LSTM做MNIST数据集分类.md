### Tensorflow 搭建基础LSTM对MNIST数据集进行分类

2019-12-26

参考资料：https://www.kesci.com/home/project/5d01bf35e727f8002c4af15a




```python
import tensorflow as tf
from tensorflow.examples.tutorials.mnist import input_data

import ssl
ssl._create_default_https_context = ssl._create_unverified_context

mnist = input_data.read_data_sets('./data/mnist', one_hot=True)
```

    Extracting ./data/mnist/train-images-idx3-ubyte.gz
    Extracting ./data/mnist/train-labels-idx1-ubyte.gz
    Extracting ./data/mnist/t10k-images-idx3-ubyte.gz
    Extracting ./data/mnist/t10k-labels-idx1-ubyte.gz

```python
#输入一行，一行有28个数据
n_inputs = 28 

#一共28行
max_time = 28

#隐层单元设置为100个
lstm_size = 100 

#最后的标签共10个分类
n_classes = 10 

#每批次有50个样本
batch_size = 50 

#计算一共有多少个批次
n_batch = mnist.train.num_examples // batch_size 
```


```python
'''
#placeholder()函数是在神经网络构建graph的时候在模型中的占位，
#此时并没有把要输入的数据传入模型，它只会分配必要的内存。
#等建立session，在会话中，运行模型的时候通过feed_dict()函数向占位符传入数据
#这里建立了两个占位
'''

#维度为28*28
x = tf.placeholder(tf.float32,[None,784])
#标签有10个
y = tf.placeholder(tf.float32,[None,10])
```


```python
'''
#我们需要创建大量的权重和偏置量
#权重应用少量的噪声来打破对称性以及避免0梯度
#用一个较小的正数来初始化偏置项
'''

#权重
#tf.truncated_normal从截断的正态分布中输出随机值。 
#[lstm_size, n_classes]表示生成张量的维度，stddev是标准差，均值默认为0

weights = tf.Variable(tf.truncated_normal([lstm_size, n_classes], stddev=0.1))
#偏执量
#创建一个常数张量，shape代表张量的维度
biases = tf.Variable(tf.constant(0.1, shape=[n_classes]))
```


```python
'''
tf.nn.dynamic_rnn(
    cell,
    inputs,
    sequence_length=None,
    initial_state=None,
    dtype=None,
    parallel_iterations=None,
    swap_memory=False,
    time_major=False,
    scope=None
)
cell：RNNCell的一个实例.
inputs：RNN输入.

sequence_length：(可选)大小为[batch_size]的int32/int64的向量.
initial_state：(可选)RNN的初始状态.
如果cell.state_size是整数,则必须是具有适当类型和shape为[batch_size, cell.state_size]的Tensor.
如果cell.state_size是一个元组,则应该是张量元组,在cell.state_size中为s设置shape[batch_size, s].

dtype：(可选)初始状态和预期输出的数据类型.如果未提供initial_state或RNN状态具有异构dtype,则是必需的.

parallel_iterations：(默认值：32).并行运行的迭代次数.
time_major：inputs和outputsTensor的形状格式.
scope：用于创建子图的VariableScope；默认为“rnn”.
'''
```


```python
#定义一个RNN的模型
def RNN(X,weights,biases):
    #输入数据维度为[batch_size, max_time, n_inputs]
    #改变输入数据的形状
    inputs = tf.reshape(X,[-1,max_time,n_inputs])
    
    #定义LSTM基本CELL
    #lstm_size代表神经元数量，其余变量都设为默认值
    lstm_cell = tf.contrib.rnn.BasicLSTMCell(lstm_size, reuse=tf.AUTO_REUSE)

    
    outputs,final_state = tf.nn.dynamic_rnn(lstm_cell, inputs, dtype=tf.float32)
    
    #将输出的结果乘以权重，加上偏置量，再应用softmax函数
    results = tf.nn.softmax(tf.matmul(final_state[1],weights) + biases)
    
    
    return results

```


```python
# 计算RNN的返回结果
prediction = RNN(x, weights, biases)

# 定义损失函数
# logits代表神经网络的预测值
# labels代表真实标签
cross_entropy = tf.reduce_mean(tf.nn.softmax_cross_entropy_with_logits_v2(logits=prediction, labels=y))

# 使用AdamOptimizer为损失函数计算梯度
train_step = tf.train.AdamOptimizer(1e-4).minimize(cross_entropy)

# tf.equal（x, y）  判断x， y是否相等，相等返回true，不相等false
#tf.cast(x, dtype, name=None)  数据类型转换
#x  待转换的数据     dtype 目标数据类型   name=None  操作的名称
#tf.reduce_mean() 求均值
#tf.argmax(input,axis)根据axis取值的不同返回每行或者每列最大值的索引
#accuracy代表精度
#首先将输出层每个数据所对应最大概率那个值所对应的数据索引与标签值所对应的索引相比较
#如果两者一样，则返回1，如果两者不一致，则返回0，最终求出平均值作为精确度
correct_prediction = tf.equal(tf.argmax(y,1),tf.argmax(prediction,1))
accuracy = tf.reduce_mean(tf.cast(correct_prediction,tf.float32))

##初始化模型的参数，一般情况下，都需要加上这一句
init = tf.global_variables_initializer()
```

```python
with tf.Session() as sess:
    sess.run(init)
    for epoch in range(6):
        for batch in range(n_batch):
            batch_xs, batch_ys = mnist.train.next_batch(batch_size)
            sess.run(train_step, feed_dict = {x:batch_xs, y:batch_ys})
        acc = sess.run(accuracy, feed_dict = {x:mnist.test.images, y:mnist.test.labels})
        print("epoch {}: Acc = {}".format(epoch+1, acc))
```

输出结果

```
epoch 1: Acc = 0.7250999808311462
epoch 2: Acc = 0.8130999803543091
epoch 3: Acc = 0.8309000134468079
epoch 4: Acc = 0.8980000019073486
epoch 5: Acc = 0.9171000123023987
epoch 6: Acc = 0.9280999898910522
```

