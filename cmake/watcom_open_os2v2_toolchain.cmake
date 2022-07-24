include_guard()

set(OS2 1)

set(CMAKE_SYSTEM_NAME "Generic")

set(CMAKE_BUILD_TYPE RelWithDebInfo)

set(CMAKE_C_COMPILER "wcl386")
set(CMAKE_CXX_COMPILER "wcl386")
set(CMAKE_ASM_COMPILER "wasm")

if(CMAKE_VERBOSE_MAKEFILE)
  set(CMAKE_WCL_QUIET)
  set(CMAKE_WLINK_QUIET)
  set(CMAKE_LIB_QUIET)
else()
  set(CMAKE_WCL_QUIET "-zq")
  set(CMAKE_WLINK_QUIET "op q")
  set(CMAKE_LIB_QUIET "-q")
endif()

foreach(lang C CXX ASM)
  set(CMAKE_EXECUTABLE_SUFFIX_${lang} ".exe")
  set(CMAKE_${lang}_LINK_LIBRARY_SUFFIX ".lib")
  set(CMAKE_STATIC_LIBRARY_PREFIX_${lang} "")
  set(CMAKE_STATIC_LIBRARY_SUFFIX_${lang} ".lib")
  set(CMAKE_SHARED_LIBRARY_PREFIX_${lang} "")
  set(CMAKE_SHARED_LIBRARY_SUFFIX_${lang} ".dll")
  set(CMAKE_IMPORT_LIBRARY_PREFIX_${lang} "")
  set(CMAKE_IMPORT_LIBRARY_SUFFIX_${lang} ".lib")
endforeach()

set(CMAKE_DL_LIBS "")
set(CMAKE_FIND_LIBRARY_PREFIXES "")
set(CMAKE_FIND_LIBRARY_SUFFIXES ".lib")

set(CMAKE_LIBRARY_PATH_FLAG "libpath ")
set(CMAKE_LINK_LIBRARY_FLAG "library ")
set(CMAKE_LINK_LIBRARY_FILE_FLAG "library ")

set(CMAKE_C_COMPILE_OPTIONS_DLL "")
set(CMAKE_SHARED_LIBRARY_C_FLAGS "")

foreach(type EXE SHARED MODULE)
  set(CMAKE_${type}_LINKER_FLAGS_INIT " system os2v2 opt map, noext")
  set(CMAKE_${type}_LINKER_FLAGS_DEBUG_INIT " debug all")
  set(CMAKE_${type}_LINKER_FLAGS_RELWITHDEBINFO_INIT " debug all")
endforeach()

set(CMAKE_C_FLAGS_INIT " -w3 -bt=os2")
set(CMAKE_C_FLAGS_DEBUG_INIT " -d2")
set(CMAKE_C_FLAGS_MINSIZEREL_INIT " -s -os -d0 -dNDEBUG")
set(CMAKE_C_FLAGS_RELEASE_INIT " -s -ot -d0 -dNDEBUG")
set(CMAKE_C_FLAGS_RELWITHDEBINFO_INIT " -s -ot -d1 -dNDEBUG")

foreach(type CREATE_SHARED_LIBRARY CREATE_SHARED_MODULE LINK_EXECUTABLE)
  set(CMAKE_C_${type}_USE_WATCOM_QUOTE 1)
endforeach()

set(CMAKE_C_CREATE_IMPORT_LIBRARY
  "wlib ${CMAKE_LIB_QUIET} -c -n -b <TARGET_IMPLIB> +<TARGET_QUOTED>")

set(CMAKE_C_LINK_EXECUTABLE
  "wlink ${CMAKE_WLINK_QUIET} name <TARGET> <LINK_FLAGS> file {<OBJECTS>} <LINK_LIBRARIES>")

# compile a C file into an object file
set(CMAKE_C_COMPILE_OBJECT
    "<CMAKE_C_COMPILER> ${CMAKE_WCL_QUIET} -d+ <DEFINES> <INCLUDES> <FLAGS> -fo=\"<OBJECT>\" -c -cc \"<SOURCE>\"")

# preprocess a C source file
set(CMAKE_C_CREATE_PREPROCESSED_SOURCE
    "<CMAKE_C_COMPILER> ${CMAKE_WCL_QUIET} -d+ <DEFINES> <INCLUDES> <FLAGS> -fo=\"<PREPROCESSED_SOURCE>\" -pl -cc \"<SOURCE>\"")

string(REPLACE " option implib=<TARGET_IMPLIB>" ""
  CMAKE_CXX_CREATE_SHARED_MODULE "${CMAKE_CXX_CREATE_SHARED_LIBRARY}")

# create a C shared library
set(CMAKE_C_CREATE_SHARED_LIBRARY ${CMAKE_CXX_CREATE_SHARED_LIBRARY})

# create a C shared module
set(CMAKE_C_CREATE_SHARED_MODULE ${CMAKE_CXX_CREATE_SHARED_MODULE})

# create a C static library
set(CMAKE_C_CREATE_STATIC_LIBRARY "wlib ${CMAKE_LIB_QUIET} -c -n -b <TARGET_QUOTED> <LINK_FLAGS> <OBJECTS> ")

message(STATUS "Configured for OS/2 (32-bit)")
set(WATCOM_OS2V2 TRUE)
