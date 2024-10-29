cmake_minimum_required(VERSION 3.10)
project(InteriorPointSolver)

# Устанавливаем стандарт C++
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Добавляем исходные файлы
set(SRC_FILES
        src/Matrix.cpp
        src/InteriorPoint.cpp
)

# Определяем исполняемый файл для основной программы (если добавите main.cpp)
# add_executable(${PROJECT_NAME} ${SRC_FILES} src/main.cpp)

# Подключаем Google Test
enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# Добавляем исполняемый файл для тестов
add_executable(runTests tests/test_main.cpp ${SRC_FILES})

# Линкуем с GTest и pthread
target_link_libraries(runTests ${GTEST_LIBRARIES} pthread)
add_test(NAME runTests COMMAND runTests)
