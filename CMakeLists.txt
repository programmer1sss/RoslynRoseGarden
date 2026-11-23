cmake_minimum_required(VERSION 3.16)
project(RoslynRoseGarden LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# ── Опції ──
option(ENABLE_SANITIZERS "Build with ASan and UBSan" OFF)

# ── Спільні попередження ──
set(PROJECT_WARNINGS -Wall -Wextra -Wpedantic)

# ── Допоміжна функція для санітайзерів ──
function(apply_warnings_and_sanitizers target)
    if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
        target_compile_options(${target} PRIVATE ${PROJECT_WARNINGS} -g)
        if(ENABLE_SANITIZERS)
            target_compile_options(${target} PRIVATE
                -fsanitize=address,undefined
                -fno-omit-frame-pointer -g
            )
            target_link_options(${target} PRIVATE
                -fsanitize=address,undefined
            )
        endif()
    endif()
endfunction()

# ── Спільні файли предметної області (без main.cpp) ──
set(NURSERY_SOURCES
    src/Money.cpp
    src/PlantingMaterial.cpp
    src/FruitSeedling.cpp
    src/OrnamentalShrub.cpp
    src/Nursery.cpp
    src/NurseryOrder.cpp
    src/DiamondExperiment.cpp
)

# ════════════════════════════════════════════════════════════════
#  ГОЛОВНА ПРОГРАМА
# ════════════════════════════════════════════════════════════════

add_executable(nursery_demo
    src/main.cpp
    ${NURSERY_SOURCES}
)
target_compile_features(nursery_demo PRIVATE cxx_std_17)
target_include_directories(nursery_demo PRIVATE src)
apply_warnings_and_sanitizers(nursery_demo)

# ════════════════════════════════════════════════════════════════
#  ТЕСТИ (GoogleTest)
# ════════════════════════════════════════════════════════════════
enable_testing()

include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG        v1.14.0
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Тести для наскрізного проєкту (Розсадник)
add_executable(test_nursery
    tests/tests.cpp
    ${NURSERY_SOURCES}
)
target_compile_features(test_nursery PRIVATE cxx_std_17)
target_include_directories(test_nursery PRIVATE src)
target_link_libraries(test_nursery PRIVATE GTest::gtest_main)
apply_warnings_and_sanitizers(test_nursery)

include(GoogleTest)
gtest_discover_tests(test_nursery)