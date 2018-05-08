# 第二节  C\#基本知识

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

```
 Mutex的使用
 // Summary:
        //     Initializes a new instance of the System.Threading.Mutex class with a Boolean
        //     value that indicates whether the calling thread should have initial ownership
        //     of the mutex, a string that is the name of the mutex, and a Boolean value that,
        //     when the method returns, indicates whether the calling thread was granted initial
        //     ownership of the mutex.
        //
        // Parameters:
        //   initiallyOwned:
        //     true to give the calling thread initial ownership of the named system mutex if
        //     the named system mutex is created as a result of this call; otherwise, false.
        //
        //   name:
        //     The name of the System.Threading.Mutex. If the value is null, the System.Threading.Mutex
        //     is unnamed.
        //
        //   createdNew:
        //     When this method returns, contains a Boolean that is true if a local mutex was
        //     created (that is, if name is null or an empty string) or if the specified named
        //     system mutex was created; false if the specified named system mutex already existed.
        //     This parameter is passed uninitialized.
        //
        // Exceptions:
        //   T:System.UnauthorizedAccessException:
        //     The named mutex exists and has access control security, but the user does not
        //     have System.Security.AccessControl.MutexRights.FullControl.
        //
        //   T:System.IO.IOException:
        //     A Win32 error occurred.
        //
        //   T:System.Threading.WaitHandleCannotBeOpenedException:
        //     The named mutex cannot be created, perhaps because a wait handle of a different
        //     type has the same name.
        //
        //   T:System.ArgumentException:
        //     name is longer than 260 characters.
        [ReliabilityContract(Consistency.WillNotCorruptState, Cer.MayFail)]
        [SecurityCritical]
        public Mutex(bool initiallyOwned, string name, out bool createdNew);
        var mutex = new Mutex(false, RS7.IF.CommonFunction.CommonString.MutexName, out createdNew);
```

```
as 的用法
IModuleCommonInterface iMagnet = MagnetSystem.GetInstance as IModuleCommonInterface;
```

```
Event 
public static event EventHandler<NexusWaferLocationEventArgs> WaferLocationEvent
        {
            add { m_waferLocationEvent += value; }
            remove { m_waferLocationEvent -= value; }
        }
```



