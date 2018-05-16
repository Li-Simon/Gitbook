# COM连接点

[COM连接点 - 最简单的例子](https://blog.csdn.net/zj510/article/details/39056097)

```cpp
 AtlAdvise(spCar, sinkptr, __uuidof(_IMyCarEvents), &cookies);
```

**换句话说，一旦将sink对象成功挂载到了COM对象，那么sink对象的生命周期就由对应的COM\(spCar\)对象来管理。**

