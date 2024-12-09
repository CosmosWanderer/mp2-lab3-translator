# mp2-lab3-translator  
**Поташник Максим 3823Б1ФИ1**  

Лабораторная работа №3 включает:  
- парсер для математических выражений,  
- перевод в постфиксную форму,  
- вычисление выражений.  

Также реализована возможность:  
- заранее задавать константы,  
- добавлять и изменять переменные во время выполнения программы,  
- добавлять функции от одного и нескольких аргументов.  


## **translator.h**  
Основной класс, объединяющий в себе все остальные.  

Метод `execute` применяется к математическому выражению, записанному в виде строки. Возвращает одно из следующих:  
- полученное значение,  
- уведомление о добавлении/изменении переменной,  
- иные сообщения (например, уведомление о пустой строке).  

Если ввод некорректен, выбрасывается исключение в формате строки. Это позволяет определить, на каком этапе произошла ошибка.  

В сетах `func1`, `func2` хранятся списки функций, распознаваемых при парсинге. Для добавления функций следует использовать `functions.h` и метод `addFunctions`:  
```cpp
functions f;  
std::set<std::string> f1 = f.func1;  
std::set<std::string> f2 = f.func2;  
tr.addFunctions(f1, f2);  
```  

В мапах `variables`, `constants` хранятся переменные и константы.  
Добавление констант:  
```cpp
tr.constants.insert({ "Pi", "3.14159265359" });  
tr.constants.insert({ "e", "2.7182" });  
```  


## **lexiconalysis.h**  
Класс, отвечающий за лексический анализ выражений и разбиение их на лексемы.  

Метод `analyse` принимает:  
- выражение в виде строки,  
- мапы переменных и констант,  
- сеты функций `func1` и `func2`.  

Возвращает вектор пар-лексем:  
- первая часть пары — тип лексемы,  
- вторая часть — название лексемы.  

Если выражение некорректно, выбрасывается исключение.  

**Важно:** бинарные `+` и `-` не разделяются от унарных на этапе лексического анализа — это происходит при синтаксическом анализе.  


## **syntanalysis.h**  
Класс для синтаксического анализа выражений.  

Метод `analyse` принимает:  
- вектор пар-лексем,  
- мапы переменных и констант,  
- сеты функций `func1` и `func2`.  

Возвращает вектор пар-лексем, так как в процессе синтаксического анализа определяется тип операций (например, унарные).  

Если выражение некорректно, выбрасывается исключение.  


## **transformator.h**  
Класс, преобразующий вектор лексем в постфиксную форму.  
Принимает и возвращает вектор пар-лексем.  


## **calculator.h**  
Класс, вычисляющий значение выражения в постфиксной форме.  

Метод `calculate`:  
- принимает вектор лексем в постфиксной форме,  
- возвращает строку-значение.  

Если в процессе вычисления возникает ошибка (например, деление на ноль), выбрасывается исключение.  


## **functions.h**  
Класс для работы с функциями, участвующими в вычислениях.  

Функции делятся на два типа:  
- `func1` — функции от одного аргумента,  
- `func2` — функции от нескольких аргументов.  

`func1` получает выражение внутри скобок.  
`func2` получает несколько выражений, разделённых запятыми.  

Аргументы функций могут быть сложными выражениями, так как они упрощаются до одного значения в процессе обработки.  

Для вызова функций сторонние классы используют методы `solveFunc1` или `solveFunc2`:  
```cpp
std::string resValue = f.solveFunc1(S.top().second, token.second);  
```  

### **Добавление новых функций**  
Для добавления новой функции:  
1. Добавьте название функции в соответствующий сет.  
2. Реализуйте функцию в `.cpp`-файле.  
3. Добавьте вызов функции в соответствующий метод `solveFunc`.  
