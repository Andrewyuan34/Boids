#===================================================#
#           CMakeLists.txt -- thirdparty/glad/
#===================================================#
# Package GLAD as a static library for better modularity

# Define a list to store all C source files
FILE(GLOB TPR_GLAD_SRC  src/*.c )

# Create the target library
# This name will be used in the main CMakeLists.txt to link against this library
add_library(glad 
    STATIC
    ${TPR_GLAD_SRC}
)

# Specify header file paths:
#   PRIVATE - for library's own compilation
#   SYSTEM INTERFACE - for global include (callers don't need to specify include path)
target_include_directories(glad
    PRIVATE           include
    SYSTEM INTERFACE  include
)

# Compiler options
if(MSVC)
    target_compile_options(glad PRIVATE /wd4201)  # MSVC equivalent for language extension warnings
else()
    target_compile_options(glad PRIVATE -Wno-language-extension-token)
endif()

# Set library output name to glad.lib
set_target_properties(glad PROPERTIES PREFIX "")
set_target_properties(glad PROPERTIES OUTPUT_NAME "glad") 