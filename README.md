## 海贼 Hython 语言设计与开发

### 项目描述

海贼 19-8 班 C++ 综合项目，设计一门自己的编程语言



### 1. Antlr 的基础使用

1. 增加除法表达式的支持（增加文本【源代码】中的关键字）
2. 增加取余表达式的支持（增加文本【源代码】中的关键字）
3. 修改解释器，对于每一行内容，都输出其表达式的值（修改解释器的功能）
4. 增加变量定义的语法结构
5. 增加作用域的功能`（基于船长的文法文件，完成解释器的程序部分）`



### 2.简单的流程控制

1. 整理工程目录，include/lib/bin/src/...
2. 整理 main.cpp 内容，分成头文件和原文件，main.cpp 尽量简单
3. print 子句
4. 增加条件表达式(==,<=, >=, && , ||)
5. if 结构的增加
6. for 结构的增加
7. while 结构的增加
8. do...while 结构的增加
9. 找 bug`非常关键，能够理解 bug，才能锻炼思维`



### 3.增加弱类型系统

1. 用责任链模式改写整体 ExprTreeEvaluator 类的功能
2. 设计并实现弱类型系统