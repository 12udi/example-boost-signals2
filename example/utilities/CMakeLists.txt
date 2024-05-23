# static lib

set(TARGET_NAME Utilities)

string(TOLOWER ${TARGET_NAME} LOWERCASE_TARGET_NAME)

set(TARGET_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/example/${LOWERCASE_TARGET_NAME}/include)
set(TARGET_SRC_DIR ${PROJECT_SOURCE_DIR}/example/${LOWERCASE_TARGET_NAME}/src)

set(CMAKE_AUTOMOC OFF)
set(CMAKE_AUTORCC OFF)

set(PUBLIC_HEADERS
    ${TARGET_INCLUDE_DIR}/${LOWERCASE_TARGET_NAME}/Receiver.h
)

set(SOURCES
    ${TARGET_SRC_DIR}/Receiver.cpp
)

# target
add_library(${TARGET_NAME} SHARED
    ${PUBLIC_HEADERS} 
    ${SOURCES}
)

target_compile_options(${TARGET_NAME} PRIVATE
  $<$<CXX_COMPILER_ID:MSVC>:/W4 /WX>
  $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -Wpedantic -Werror>
)

target_include_directories(${TARGET_NAME}
    PUBLIC ${TARGET_INCLUDE_DIR}
)

# linker
target_link_libraries(${TARGET_NAME}
    PRIVATE Boost::signals2
)

# public includes
set_target_properties(${TARGET_NAME}
    PROPERTIES PUBLIC_HEADER ${PUBLIC_HEADERS}
)

# folder structure
set_target_properties(${TARGET_NAME}
    PROPERTIES FOLDER ${EXAMPLE_INSTALL_SUFFIX}
)

install(TARGETS ${TARGET_NAME}
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION ${EXAMPLE_INSTALL_DIR}
    PUBLIC_HEADER DESTINATION include/${LOWERCASE_TARGET_NAME}
)
