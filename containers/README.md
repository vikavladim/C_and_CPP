# vv_containers

Реализация библиотеки vv_containers.h.

vv_containers - это библиотека контейнеров, которая включает в себя реализацию следующих контейнеров:

* Основные контейнеры:
    - `list` (список)
    - `map` (словарь)
    - `queue` (очередь)
    - `set` (множество)
    - `stack` (стек)
    - `vector` (вектор)
* Дополнительные контейнеры:
    - `array` (массив)
    - `multiset` (мультимножество)

Библиотека также включает в себя реализацию методов `insert_many` для различных контейнеров, которые позволяют вставлять
несколько элементов в контейнер одновременно.

Библиотека реализована в виде заголовочных файлов `vv_containers.h` и `vv_containersplus.h`, которые включают в себя
другие заголовочные файлы с реализациями необходимых контейнеров. Для тестов написанной библиотеки предусмотрен Makefile
с целями `clean` и `test`.