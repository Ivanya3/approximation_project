# README.md для проекта "Аппроксимация линий"

```markdown
# Approximation Project

Приложение для аппроксимации линий методом наименьших квадратов с визуальным интерфейсом.

## 📋 Описание

Проект представляет собой графическое приложение на Qt, позволяющее:

- Рисовать линии от руки и аппроксимировать их полиномом
- Импортировать точки из CSV-файлов
- Выбирать распределение точек (равномерное, случайное, Чебышева)
- Настраивать степень полинома (от 3 до 20)
- Анализировать качество аппроксимации (максимальная ошибка, RMSE)
- Редактировать точки в таблице и видеть все коэффициенты полинома
- Панорамировать и масштабировать график

## 🛠 Технологии

| Технология | Версия | Назначение |
|------------|--------|------------|
| C++ | 17 | Язык программирования |
| Qt | 6.x / 5.x | GUI фреймворк |
| CMake | 3.16+ | Система сборки |
| Google Test | 1.17.0 | Юнит-тестирование |

## 📁 Структура проекта

```
approximation_project/
├── CMakeLists.txt          # Главный файл сборки
├── main.cpp                # Точка входа
├── mainwindow.cpp/h        # Главное окно
├── mainwindow.ui           # UI главного окна
├── graf.cpp/h              # Виджет графика
├── statswindow.cpp/h       # Окно статистики
├── StatsWindow.ui          # UI окна статистики
├── slidervv.cpp/h          # Кастомный слайдер
├── csvimporter.cpp/h       # Импорт CSV
├── resources.qrc           # Ресурсы (шрифты)
├── fonts/                  # Шрифты Montserrat
└── tests/                  # Юнит-тесты
    ├── CMakeLists.txt
    ├── main.cpp
    ├── math_utils.h
    └── test_least_squares.cpp
```

## ⚙️ Сборка проекта

### Требования

- **CMake** версии 3.16 или выше
- **Qt6** или **Qt5** (Widgets, Core)
- **Компилятор** с поддержкой C++17 (GCC, Clang, MSVC)
- **Google Test** (для сборки тестов)

### Установка зависимостей

#### macOS
```bash
# Установка CMake
brew install cmake

# Установка Qt6
brew install qt@6

# Установка Google Test (для тестов)
brew install googletest
```

#### Ubuntu/Debian
```bash
# Установка CMake и Qt6
sudo apt update
sudo apt install cmake qt6-base-dev libgtest-dev

# Сборка Google Test
cd /usr/src/gtest
sudo cmake .
sudo make
sudo cp lib/*.a /usr/lib
```

#### Windows (с использованием MSYS2)
```bash
# Установка пакетов
pacman -S mingw-w64-x86_64-cmake
pacman -S mingw-w64-x86_64-qt6
pacman -S mingw-w64-x86_64-gtest
```

### Сборка из терминала

```bash
# Клонирование репозитория
git clone https://gitflic.ru/project/musya-eto-ty/approximation_project.git
cd approximation_project

# Создание папки для сборки
mkdir build && cd build

# Конфигурация CMake (для Qt6)
cmake -DCMAKE_PREFIX_PATH="/opt/homebrew/opt/qt@6" -DCMAKE_BUILD_TYPE=Release ..

# Сборка
make -j4

# Запуск
./test5.app/Contents/MacOS/test5  # macOS
./test5                            # Linux
./Release/test5.exe                # Windows
```

### Сборка в Qt Creator

1. Откройте **Qt Creator**
2. **File → Open File or Project**
3. Выберите `CMakeLists.txt` из корня проекта
4. Выберите комплект (Kit) с Qt
5. Нажмите **Configure Project**
6. Нажмите **Build → Rebuild All** (`Cmd+Shift+B`)

### Опции CMake

| Опция | Значение по умолчанию | Описание |
|-------|----------------------|----------|
| `CMAKE_BUILD_TYPE` | `Debug` | Тип сборки (`Debug`, `Release`, `RelWithDebInfo`) |
| `CMAKE_PREFIX_PATH` | - | Путь к установке Qt |
| `BUILD_TESTING` | `ON` | Сборка юнит-тестов |

Пример с опциями:
```bash
cmake -DCMAKE_BUILD_TYPE=Release -DBUILD_TESTING=ON ..
```

## 🧪 Запуск тестов

### В терминале
```bash
cd build/tests
./test_runner
```

### В Qt Creator
1. Выберите в выпадающем списке `test_runner`
2. Нажмите зелёную кнопку ▶
3. Или **Build → Run CMake Tests**

## 📦 Компиляция в Docker (опционально)

```bash
# Запуск Docker контейнера с Qt6
docker run -it --rm -v $(pwd):/project qt6:latest bash

# Внутри контейнера
cd /project
mkdir build && cd build
cmake ..
make
```

## 🚀 Запуск приложения

### Из Qt Creator
Выберите `test5` в выпадающем списке и нажмите ▶

### Из терминала (macOS)
```bash
./build/test5.app/Contents/MacOS/test5
```

### Из терминала (Linux)
```bash
./build/test5
```

### Из терминала (Windows)
```cmd
.\build\Release\test5.exe
```

## 📖 Использование

### Главное окно
1. **Нарисуйте линию** — зажмите левую кнопку мыши на поле графика
2. **Настройте параметры** — выберите распределение точек, плотность, степень полинома
3. **Вычислите полином** — нажмите кнопку «Построить»
4. **Очистите график** — кнопка «Очистить»

### Импорт CSV
- Формат: `X,Y` (разделители: запятая, точка с запятой, пробел)
- Пустые строки игнорируются
- Строки с `#` или `//` игнорируются

### Режим «Рука»
- Нажмите кнопку «Рука» в боковой панели
- Зажмите левую кнопку мыши для панорамирования
- Колесико мыши — масштабирование

## 📊 Результаты тестов

Всего реализовано **13 юнит-тестов**:

| Категория | Количество тестов | Что проверяют |
|-----------|-------------------|---------------|
| LeastSquaresTest | 7 | Линейная, квадратичная, константа, недостаток точек, пустые массивы |
| RMSETest | 4 | Perfect match, постоянная ошибка, разные значения, пустой вектор |
| EdgeCasesTest | 2 | Отрицательные значения, большие числа |

## 👥 Автор

**Автор проекта:** Ваня, Весна


## 🙏 Благодарности

- Преподавателям за ценные замечания