# spbu pmpucpp PersonTest
Программа была зачтена, но существуют недочеты, которые стоит адресовать:

1)Не перегружен оператор ввода из istream для листа. (По формулировке задачи никак не применимо для указанного интерфейса, но АП упоминал, что это можно добавить)  
2)Фильтрованный ввод (защита от дурачка) не осуществлён в качестве функции, мейн засорён аналогичными блоками кода.  
3)Классы Person и PersonList стоит разбить на два файла .cpp и .h соответственно.  
