# 第二节

```
Linq 语句
q = from sl in m_cassette.slot_descs
     where sl.slot_seq == i
     orderby sl.recipe_seq ascending
     select sl;
```

```
C#委托

Action<int, string, string> dr = this.OnFinishedLoadingWaferInternal;
    this.Invoke(dr, new object[] { slot, waferID, lotID });

http://www.cnblogs.com/akwwl/p/3232679.html
Delegate至少0个参数，至多32个参数，可以无返回值，也可以指定返回值类型
Func可以接受0个至16个传入参数，必须具有返回值
Action可以接受0个至16个传入参数，无返回值
Predicate只能接受一个传入参数，返回值为bool类型
```



