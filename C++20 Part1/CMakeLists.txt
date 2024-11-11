add_executable (01_span                        "01_span.cpp")
add_executable (02_module                      "02_module.cpp" "my_module.ixx" "my_module.cpp")

target_compile_options(02_module PRIVATE /experimental:module)
