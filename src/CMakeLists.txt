set(MASSCALC_SOURCE_FILES
    masscalc.cpp)

foreach(FILE ${MASSCALC_SOURCE_FILES})
    get_filename_component(PARENT_DIR "${FILE}" PATH)

    string(REPLACE "/" "\\" GROUP "${PARENT_DIR}")

    if("${FILE}" MATCHES ".*\\.cpp")
        set(GROUP "Source Files\\${GROUP}")
    elseif("${FILE}" MATCHES ".*\\.hpp")
        set(GROUP "Header Files\\${GROUP}")
    endif()

    source_group("${GROUP}" FILES "${FILE}")
endforeach()

add_library(masscalc-lib ${MASSCALC_SOURCE_FILES})

set_target_properties(
    masscalc-lib PROPERTIES

    CXX_EXTENSIONS OFF
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
)

# enable multi processor building if VS project
if(${CMAKE_GENERATOR} MATCHES "Visual Studio.*")
    target_compile_options(masscalc-lib PRIVATE "/MP")
endif()

# Replace variables in header file with CMake values
configure_file(
    ${PROJECT_SOURCE_DIR}/include/metadata/meta.hpp.in ${CMAKE_CURRENT_BINARY_DIR}/include/metadata/meta.hpp
)

target_include_directories(
    masscalc-lib

    PUBLIC
    ${PROJECT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_BINARY_DIR}/include/
)

if(CONAN_LIBS)
    target_link_libraries(
        masscalc-lib

        PUBLIC
        ${CONAN_LIBS}
    )
else()
    foreach(_LIB ${CONAN_LIBS_RELEASE})
        target_link_libraries(
            masscalc-lib
            optimized

            ${_LIB}
        )
    endforeach()
    foreach(_LIB ${CONAN_LIBS_DEBUG})
        target_link_libraries(
            masscalc-lib
            debug

            ${_LIB}
        )
    endforeach()
endif()
