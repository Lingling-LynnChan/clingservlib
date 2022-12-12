# clingservlib
C语言面向对象库
## 最新版本 v0.1（正在开发中）
### 已经实现的功能
* 方法接口 `ObejctMethod`
* 常用对象装箱
* * `Int: int64_t`
* * `Flt: double`
* * `Str: string`
* 常用泛型数据结构（线程安全）
* * `List` : 基于数组实现
* * `HashMap` : 基于 `List` 实现
* * `Set` : 基于 `List` 提供抽象 `Set` 方法实现和嵌套于 `HashMap` 的 `Set` 实现
* 常用工具
* * 布尔变量的枚举实现 [clingservlib/lib/bool.h](https://github.com/Lingling-LynnChan/clingservlib/blob/main/clingservlib/lib/bool.h)
* * 互斥锁、读写锁和安全指针的封装 [clingservlib/lib/safe.h](https://github.com/Lingling-LynnChan/clingservlib/blob/main/clingservlib/lib/safe.h)
* * 内存管理的代理接口 [clingservlib/lib/proxy/alloc.h](https://github.com/Lingling-LynnChan/clingservlib/blob/main/clingservlib/lib/proxy/alloc.h)
* * 输入输出的代理接口 [clingservlib/lib/proxy/output.h](https://github.com/Lingling-LynnChan/clingservlib/blob/main/clingservlib/lib/proxy/output.h)
* 特色工具
* * `SafePtr` : 安全指针，用于包装堆空间的指针，可用于监控内存泄露，防止内存的非法访问与释放
### 计划实现的功能
* 实现链表 `LinkedList`
* 实现 `Tree` 并用于解决哈希冲突
* 实现专用的 `Set` 数据结构
* 未完待续 ... ...
