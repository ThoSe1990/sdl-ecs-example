

set(target lua_cpp)

set(LUA_SRC
    ${CMAKE_CURRENT_SOURCE_DIR}/lapi.c
    ${CMAKE_CURRENT_SOURCE_DIR}/lcode.c
    ${CMAKE_CURRENT_SOURCE_DIR}/lctype.c
    ${CMAKE_CURRENT_SOURCE_DIR}/ldebug.c
    ${CMAKE_CURRENT_SOURCE_DIR}/ldo.c
    ${CMAKE_CURRENT_SOURCE_DIR}/ldump.c
    ${CMAKE_CURRENT_SOURCE_DIR}/lfunc.c
    ${CMAKE_CURRENT_SOURCE_DIR}/lgc.c
    ${CMAKE_CURRENT_SOURCE_DIR}/llex.c
    ${CMAKE_CURRENT_SOURCE_DIR}/lmem.c
    ${CMAKE_CURRENT_SOURCE_DIR}/lobject.c
    ${CMAKE_CURRENT_SOURCE_DIR}/lopcodes.c
    ${CMAKE_CURRENT_SOURCE_DIR}/lparser.c
    ${CMAKE_CURRENT_SOURCE_DIR}/lstate.c
    ${CMAKE_CURRENT_SOURCE_DIR}/lstring.c
    ${CMAKE_CURRENT_SOURCE_DIR}/ltable.c
    ${CMAKE_CURRENT_SOURCE_DIR}/ltm.c
    ${CMAKE_CURRENT_SOURCE_DIR}/lundump.c
    ${CMAKE_CURRENT_SOURCE_DIR}/lvm.c
    ${CMAKE_CURRENT_SOURCE_DIR}/lzio.c
    ${CMAKE_CURRENT_SOURCE_DIR}/lauxlib.c
    ${CMAKE_CURRENT_SOURCE_DIR}/lbaselib.c
    ${CMAKE_CURRENT_SOURCE_DIR}/lcorolib.c
    ${CMAKE_CURRENT_SOURCE_DIR}/ldblib.c
    ${CMAKE_CURRENT_SOURCE_DIR}/liolib.c
    ${CMAKE_CURRENT_SOURCE_DIR}/lmathlib.c
    ${CMAKE_CURRENT_SOURCE_DIR}/loadlib.c
    ${CMAKE_CURRENT_SOURCE_DIR}/loslib.c
    ${CMAKE_CURRENT_SOURCE_DIR}/lstrlib.c
    ${CMAKE_CURRENT_SOURCE_DIR}/ltablib.c
    ${CMAKE_CURRENT_SOURCE_DIR}/lutf8lib.c
    ${CMAKE_CURRENT_SOURCE_DIR}/linit.c
)

set_source_files_properties(${LUA_SRC} PROPERTIES LANGUAGE CXX )
add_library(${target} STATIC ${LUA_SRC})
target_include_directories(${target} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

