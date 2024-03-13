# --------------------------------
# Create the mockos static library
# --------------------------------
# https://gitlab.com/CLIUtils/modern-cmake/tree/master/examples/extended-project
file(GLOB headers "${mockos_SOURCE_DIR}/include/mockos/*.h")
file(GLOB sources "${mockos_SOURCE_DIR}/lib/mockos/*.cpp")

add_library(mockos ${headers} ${sources}
        EditDisplayParsingStrategy.cpp
        PermissionProxy.cpp
        PermissionCommand.cpp)
target_include_directories(mockos PUBLIC ${mockos_SOURCE_DIR}/include)
target_compile_features(mockos PUBLIC cxx_std_14)
