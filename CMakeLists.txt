cmake_minimum_required(VERSION 3.10)  # Минимальная версия CMake
project(Rethink LANGUAGES C CXX)      # Проект с поддержкой C и C++

# Установка стандарта C++
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Настройка GLEW
add_definitions(-DGLEW_STATIC)  # Определение GLEW_STATIC для статической линковки
set(GLEW_BUILD_SHARED OFF CACHE BOOL "Build GLEW as a static library" FORCE)  # Принудительная сборка GLEW как статической библиотеки

# Добавление поддиректорий для GLFW и GLEW
add_subdirectory(thirdparty/glfw)
add_subdirectory(thirdparty/glew)

# Настройки для Windows
if(WIN32)
    target_compile_definitions(glfw PRIVATE  # Добавление специфичных для Windows определений для GLFW
        _WIN32
        WIN32
        _WINDOWS
    )
endif()

# Поиск OpenGL
find_package(OpenGL REQUIRED)

file(GLOB_RECURSE SOURCES "src/*.cpp" "src/*.hpp")
file(COPY ${CMAKE_SOURCE_DIR}/textures DESTINATION ${CMAKE_BINARY_DIR})

# Сборка GLEW как статической библиотеки
add_library(glew_static STATIC IMPORTED)  # Импорт GLEW как статической библиотеки
set_target_properties(glew_static PROPERTIES
    IMPORTED_LOCATION_DEBUG "${CMAKE_SOURCE_DIR}/thirdparty/glew/lib/Debug/x64/glew32sd.lib"  # Путь к библиотеке для Debug
    IMPORTED_LOCATION_RELEASE "${CMAKE_SOURCE_DIR}/thirdparty/glew/lib/Release/x64/glew32s.lib"  # Путь к библиотеке для Release
    INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_SOURCE_DIR}/thirdparty/glew/include"  # Директория с заголовочными файлами для GLEW
)

# Сборка основного проекта
# Явное перечисление исходных файлов
set(SOURCES
    src/main.cpp
    src/Window.cpp
    src/Engine.cpp
    src/Logger/Logger.cpp
    src/font/Font.cpp
    src/Transform.cpp
    src/Shader.cpp
    Game/Camera.cpp
    thirdparty/stb/stb_image.cpp
)

add_executable(Rethink ${SOURCES}  "Game/Texture.cpp")  # Создание исполняемого файла Rethink

# Установка директорий для включения заголовочных файлов
target_include_directories(Rethink PRIVATE
    ${CMAKE_SOURCE_DIR}  # Корневая директория
    ${CMAKE_SOURCE_DIR}/thirdparty/glfw/include  # Директория с заголовочными файлами GLFW
    ${CMAKE_SOURCE_DIR}/src                      # Директория с исходными файлами
    ${CMAKE_SOURCE_DIR}/thirdparty/glm  # Директория с заголовочными файлами GLM
    ${CMAKE_SOURCE_DIR}/thirdparty/stb  # Директория с заголовочными файлами STB
    ${CMAKE_SOURCE_DIR}/thirdparty/glew/include  # Директория с заголовочными файлами GLEW
)

# Включение экспериментальных функций GLM
add_definitions(-DGLM_ENABLE_EXPERIMENTAL)  # Включение экспериментальных функций GLM

# Статическая сборка для GLEW
target_compile_definitions(Rethink PRIVATE GLEW_STATIC)  # Определение GLEW_STATIC для цели Rethink
target_compile_definitions(Rethink PRIVATE TEXTURE_PATH="${CMAKE_SOURCE_DIR}/textures/sand.png")

# Линковка библиотек
target_link_libraries(Rethink PRIVATE 
    ${OPENGL_LIBRARIES}  # Линковка OpenGL
    glew_static  # Линковка статической библиотеки GLEW
    glfw  # Линковка GLFW
)