# Алгоритм Эрли проверки принадлежности слова контекстно-свободной грамматике

### Покрытие тестами

Информацию о покрытии тестами см. в директории `coverage-info` (файл `index.html` можно открыть, например, с помощью браузера).

Для получения информации о покрытии тестами в качестве примера использовалась [статья на Medium](https://medium.com/@naveen.maltesh/generating-code-coverage-report-using-gnu-gcov-lcov-ee54a4de3f11).

Во флаги сборки проекта в `Clion` были добавлены
```cmake
SET(GCC_COVERAGE_COMPILE_FLAGS "-fprofile-arcs -ftest-coverage")
SET(GCC_COVERAGE_LINK_FLAGS    "--coverage")

SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")
SET(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} ${GCC_COVERAGE_LINK_FLAGS}")
```

После сборки проекта в директории `/cmake-build-debug/CMakeFiles/unit_tests.dir` появились данные о покрытии тестами.

Далее для сборки данных использовалась утилита `lcov`, а для генерации html-страниц - утилита `genhtml`:
```bash
lcov --capture --directory . --output-file main_coverage.info
genhtml main_coverage.info --output-directory coverage-info
cp -r coverage-info ../../../
```
