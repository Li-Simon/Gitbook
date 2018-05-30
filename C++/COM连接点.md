# COM连接点

[COM连接点 - 最简单的例子](https://blog.csdn.net/zj510/article/details/39056097)

```cpp
 AtlAdvise(spCar, sinkptr, __uuidof(_IMyCarEvents), &cookies);
 sinkptr指向了一个CComObject<CSink>
 CComObject<CSink>* sinkptr = nullptr;  
 CComObject<CSink>::CreateInstance(&sinkptr);
```

换句话说，一旦将sink对象成功挂载到了COM对象，那么sink对象的生命周期就由对应的COM\(spCar\)对象来管理。

一旦挂载成功，sink对象就托管给对应的COM对象了，如果对应的COM对象析构了，那么所有它管理的sink对象也就释放了。


#COM Interop(互操作)



