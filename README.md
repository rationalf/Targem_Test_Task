
Реализация собственного класса динамической строки `String` без использования
STL-контейнеров, `std::string` и умных указателей. Память управляется напрямую
через функции стандартной библиотеки C (`malloc`/`realloc`/`free`).

## Состав

| Файл             | Назначение                                                        |
|------------------|-------------------------------------------------------------------|
| `String.h`       | Объявление класса `String` и внешних операторов                   |
| `String.cpp`     | Реализация класса                                                 |
| `main.cpp`       | Пример-программа: сортировка строк из командной строки            |
| `CMakeLists.txt` | Сборочный скрипт                                                  |

## Сборка

### Через CMake

```sh
cmake -S . -B build
cmake --build build
```

Исполняемый файл `string_sort` (или `string_sort.exe` на Windows) появится в каталоге `build`.

### Напрямую компилятором

```sh
g++ -std=c++11 -Wall -Wextra String.cpp main.cpp -o string_sort
```

## Запуск примера

Программа принимает список строк аргументами командной строки и печатает их
в порядке, **обратном лексикографическому, без учёта регистра** (ASCII).

```sh
./string_sort banana Apple cherry apple
```

Вывод:

```
cherry
banana
Apple
apple
```

### Конструкторы и присваивание
- `String()` — пустая строка.
- `String(const char* s)` — из C-строки (поддерживает `nullptr`).
- `String(const String&)` — копирование.
- `String(String&&) noexcept` — перемещение.
- `operator=` — для `String`, для `String&&` и для `const char*`.

### Конкатенация
- `operator+=(const String&)`, `operator+=(const char*)` — дописать на месте.
- `operator+` — `String + String`, `String + const char*`, `const char* + String`.

### Доступ и информация
- `operator[](size_t)` — доступ к символу (бросает `std::out_of_range` при выходе за границы).
- `c_str()` — указатель на нуль-терминированный буфер.
- `size()` / `length()` — длина строки.
- `empty()` — пустая ли строка.

### Сравнение
- `compare(const String&)`, `compare(const char*)` — как `strcmp`.
- Операторы `==`, `!=`, `<`, `>`, `<=`, `>=`.

