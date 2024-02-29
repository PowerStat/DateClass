
add_executable(dateClassTest JulianDayTest.cpp JulianMonthTest.cpp JulianYearTest.cpp JulianWeekTest.cpp JulianDateTest.cpp DaysTest.cpp MonthsTest.cpp YearsTest.cpp WeeksTest.cpp DurationTest.cpp JDTest.cpp MJDTest.cpp ScaligerYearTest.cpp WeekdaysTest.cpp CalendarSystemsTest.cpp)
# 
target_link_libraries(dateClassTest gtest_main) # dateClass-static

target_include_directories(dateClassTest PRIVATE ../src) # Find a better way

# TARGET_DIRECTORY dateClassTest

# ---------- TODO Clang-tidy ----------
#find_program(CLANG-TIDY_PATH clang-tidy REQUIRED)
#set_target_properties(dateClassTest PROPERTIES CXX_CLANG_TIDY "${CLANG-TIDY_PATH};-checks=bugprone-*,cert-*,clang-analyzer-*,cppcoreguidelines-*,hicpp-*,misc-*,modernize-*,performance-*,portability-*,readability-*,-cppcoreguidelines-avoid-const-or-ref-data-members,-readability-const-return-type,-cppcoreguidelines-avoid-magic-numbers,-readability-magic-numbers,-readability-identifier-length;--warnings-as-errors=*;-header-filter=.*/src/.*")


include(GoogleTest)
gtest_discover_tests(dateClassTest)


# -fno-inline -fno-inline-small-functions -fno-default-inline
# -fprofile-instr-generate -fcoverage-mcdc
# -show-mcdc-summary


# "C:\Program Files\LLVM\bin\llvm-profdata" merge -sparse default.profraw -o default.profdata
# "C:\Program Files\LLVM\bin\llvm-cov" show dateClassTest.exe -instr-profile=default.profdata
# -show-mcdc -show-line-counts -ignore-filename-regex=Test.cpp


# -fsanitize=undefined
# -fsanitize=memory -fsanitize=thread -fsanitize=address

if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
  #
elseif(CMAKE_SYSTEM_NAME STREQUAL "Windows")
  message(STATUS "C++ loaded? ${CMAKE_CXX_COMPILER_LOADED}")
  if(CMAKE_CXX_COMPILER_LOADED)
    message(STATUS "ID: ${CMAKE_CXX_COMPILER_ID}")
    message(STATUS "Version: ${CMAKE_CXX_COMPILER_VERSION}")
    if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
      message("GNU C++")
      #target_compile_options(dateClassTest PRIVATE -pedantic -Wall -Wextra -Wconversion -Wsign-conversion -Wduplicated-cond -Wduplicated-branches -Wlogical-op -Wnon-virtual-dtor -Wnull-dereference -Wuseless-cast -Wshadow)
    elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
      message("CLang C++")
      target_compile_options(dateClassTest PRIVATE -Wall -Wno-c++17-extensions -fprofile-instr-generate -fcoverage-mapping -fno-inline-functions)
    elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
      message("MSVC C++")
      #target_compile_options(dateClassTest PRIVATE /Wall /W4 /permissive-)
      #target_compile_definitions(dateClassTest PRIVATE _CRT_SECURE_NO_WARNINGS)
    else()
      message(STATUS "Unknown cxx ompiler: ${CMAKE_CXX_COMPILER_ID}")
    endif()
  endif()
elseif(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
  #
elseif(CMAKE_SYSTEM_NAME STREQUAL "Amiga")
  #
else()
  message(STATUS "Unknown system: ${CMAKE_SYSTEM_NAME}")
endif()
