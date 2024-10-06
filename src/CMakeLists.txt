set(CMAKE_INCLUDE_CURRENT_DIR_IN_INTERFACE ON)

#add_library (dateClass-objs OBJECT )
#set_target_properties(dateClass-objs PROPERTIES POSSITION_INDEPENDEND_CODE 1)

#set_target_properties(dateClass-objs PROPERTIES CXX_STANDARD 17 CXX_EXTENSIONS OFF CXX_STANDARD_REQUIRED ON)
# 98 11 14 17 20 23


#target_sources(dateClass-objs PRIVATE ) 

#add_library(dateClass-shared SHARED $<TARGET_OBJECTS:dateClass-objs>)
#add_library(dateClass-static STATIC $<TARGET_OBJECTS:dateClass-objs>)

#set_target_properties(dateClass-shared PROPERTIES OUTPUT_NAME "dateClassShared")
#set_target_properties(dateClass-static PROPERTIES OUTPUT_NAME "dateClassStatic")

#set_source_files_properties( TARGET_DIRECTORY dateClass-shared PROPERTIES LANGUAGE CXX)
#set_source_files_properties( TARGET_DIRECTORY dateClass-static PROPERTIES LANGUAGE CXX)


if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
  # target_include_directories(dateClass-objs PRIVATE linuxgcc.plt)

  # target_include_directories(dateClass-objs PRIVATE linuxclang.plt)
elseif(CMAKE_SYSTEM_NAME STREQUAL "Windows")
  message(STATUS "C++ loaded? ${CMAKE_CXX_COMPILER_LOADED}")
  if(CMAKE_CXX_COMPILER_LOADED)
    message(STATUS "ID: ${CMAKE_CXX_COMPILER_ID}")
    message(STATUS "Version: ${CMAKE_CXX_COMPILER_VERSION}")
    if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
      message("GNU C++")
      #target_include_directories(dateClass-objs PRIVATE wingcc.plt)
      #target_compile_options(dateClass-objs PRIVATE -pedantic -Wall -Wextra -Wconversion -Wsign-conversion -Wduplicated-cond -Wduplicated-branches -Wlogical-op -Wnon-virtual-dtor -Wnull-dereference -Wuseless-cast -Wshadow)
    elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
      message("CLang C++")
      #target_include_directories(dateClass-objs PRIVATE winclang.plt)
      #target_compile_options(dateClass-objs PRIVATE -Wall -Wno-c++17-extensions)
    elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
      message("MSVC C++")
      #target_include_directories(dateClass-objs PRIVATE winmsvc.plt)
      #target_compile_options(dateClass-objs PRIVATE /Wall /W4 /permissive-)
      #target_compile_definitions(dateClass-objs PRIVATE _CRT_SECURE_NO_WARNINGS)
    else()
      message(STATUS "Unknown cxx ompiler: ${CMAKE_CXX_COMPILER_ID}")
    endif()
  endif()
elseif(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
  # target_include_directories(dateClass-objs PRIVATE macgcc.plt)
  # target_include_directories(dateClass-objs PRIVATE macclang.plt)
elseif(CMAKE_SYSTEM_NAME STREQUAL "Amiga")
  # target_include_directories(dateClass-objs PRIVATE amigasas.plt)
  #other
else()
  message(STATUS "Unknown system: ${CMAKE_SYSTEM_NAME}")
endif()
