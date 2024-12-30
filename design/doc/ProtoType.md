https://www.jetbrains.com/help/clion/2021.3/markdown.html#preview

# 对象创建模式
通过“对象创建”模式绕开new，来避免对象创建（new）过程中所导致的紧耦合（依赖具体类），
从而支持对象创建的稳定。它是接口抽象之后的第一步工作。
## 典型模式
Factory Method
Abstract Factory
Prototype
Builder

### Prototype
这种方式的主要优势是在运行时不需要知道具体的类，只需一个实例对象即可
#### 根因
在软件系统中，经常面临着<font color=red>某些结构复杂的对象的创建工作</font>；由于需求的变化
，这些对象经常面临着剧烈的变化，但是他们却拥有比较稳定一致的接口。
#### 方法
使用原型实例指定创建对象的种类，然后通过拷贝这些原型来创建新的对象。
### 与工厂模式的区别
工厂模式使用createFactory方法创建具体的对象，原型使用实列对象clone一个新对象。
### 总结
Prototype模式同样用于隔离类对象的使用者和具体类型（易变类）之间的耦合关系，他同样要求这些
易变类拥有稳定的接口。
Protoype模式对于如何创建易变类的实体对象采用<font color=red>原型克隆</font>的方法来做,他使得我们
可以非常灵活的动态创建拥有某些稳定接口的新对象---<font color=red>所需工作仅仅是注册一个新类的对象（即原型），然后在
任何需要的地方clone</font>
Prototype模式中的clone方法可以利用某些框架中的序列化来实现深拷贝。
