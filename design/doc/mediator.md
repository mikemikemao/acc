https://www.jetbrains.com/help/clion/2021.3/markdown.html#preview

# 接口隔离模式
在组件构建过程中，某些接口之间直接的依赖常常带来很多问题，甚至无法实现，采用添加一层间接（稳定）接口，
来隔离本来相互紧密关联的接口是一种常见的解决方案
## 典型模式
facade
proxy
adapter
mediator

### 中介者模式

#### 根因
多个对象相互关联的情况，对象之间常常会维持一种复杂的引用关系，如果遇到一些需求的更改，这种直接的引用关系将面临不断的变化。
在这种情况下，可以使用一种”中介对象“来管理对象间的关联关系，避免相互交互的对象之间的紧耦合引用关系，从而更好地抵御变化。
#### 方法
用一个中介对象来封装(封装变化)一系列的对象交互。中介者使各对象不需要显式的相互引用(编译时依赖->运行时依赖)， 从而使其耦合松散(管理变化)，并且可以独立地改变它们之间的交互

### 总结
将多个对象间发杂的关联关系解耦
Facade模式是解耦系统间(单向)的对象关联关系；Mediator模式是解耦系统内各个对象之间(双向)的关联关系。