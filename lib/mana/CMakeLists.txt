cmake_minimum_required(VERSION 2.8.9)

set(LIB_MANA ${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${LIB_MANA}/include)
include_directories(${INCLUDEOS_ROOT}/mod/rapidjson/include)

include_directories(${INCLUDEOS_ROOT}/api/posix)
include_directories(${LIBCXX_INCLUDE_DIR})
include_directories(${NEWLIB_INCLUDE_DIR})
include_directories(${INCLUDEOS_ROOT}/src/include)
include_directories(${INCLUDEOS_ROOT}/api)
include_directories(${INCLUDEOS_ROOT}/mod/GSL/)
include_directories(${INCLUDEOS_ROOT}/mod)

set(MANA_OBJ
  src/connection.cpp
  src/request.cpp
  src/response.cpp
  src/server.cpp
  )

set(MANA_COMP
  src/components/dashboard/dashboard.cpp
  )

set(MANA_MWARE
  src/middleware/butler.cpp
  src/middleware/director.cpp
  src/middleware/parsley.cpp
  src/middleware/cookie_parser.cpp
  )

set(MANA_ATTR
  src/attributes/cookie_jar.cpp
  )

add_library(mana STATIC ${MANA_OBJ} ${MANA_COMP} ${MANA_MWARE} ${MANA_ATTR})

add_dependencies(mana PrecompiledLibraries)

install(TARGETS mana DESTINATION includeos/lib)
install(DIRECTORY include/mana DESTINATION includeos/include)
