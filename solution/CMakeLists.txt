project(assignment-3-image-rotation)
file(GLOB_RECURSE sources CONFIGURE_DEPENDS
    src/*.c
    src/*.h
    include/*.h
)

add_executable(image-transformer ${sources} src/
        src/include/)
target_include_directories(image-transformer PRIVATE src include)
