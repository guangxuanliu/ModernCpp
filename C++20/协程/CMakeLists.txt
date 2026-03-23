set(SRC
    main.cpp
)

add_executable(Coroutines ${SRC})

add_executable(another another.cpp)

add_executable(IntReader IntReader.cpp)

add_executable(Fibonacci Fibonacci.cpp)

add_executable(Awaiter Awaiter.cpp)
add_executable(Task Task.cpp)