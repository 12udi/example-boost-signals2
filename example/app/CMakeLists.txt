# executable

set(TARGET_NAME App)

string(TOLOWER ${TARGET_NAME} LOWERCASE_TARGET_NAME)

set(TARGET_SRC_DIR ${PROJECT_SOURCE_DIR}/example/${LOWERCASE_TARGET_NAME}/src)

set(CMAKE_AUTOMOC OFF)
set(CMAKE_AUTORCC OFF)

set(SOURCES
    ${TARGET_SRC_DIR}/main.cpp
)

add_executable(${TARGET_NAME}
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
    PRIVATE fmt::fmt
)
target_link_libraries(${TARGET_NAME}
    PRIVATE Utilities
)

# folder structure
set_target_properties(${TARGET_NAME}
    PROPERTIES FOLDER ${EXAMPLE_INSTALL_SUFFIX}
)

install(TARGETS ${TARGET_NAME}
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION ${EXAMPLE_INSTALL_DIR}
)
