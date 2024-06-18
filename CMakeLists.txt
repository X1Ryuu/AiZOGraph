cmake_minimum_required(VERSION 3.28)
project(AiZOGraph)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_LIBRARIES "-static-libgcc -static-libstdc++ -lwsock32 -lws2_32 ${CMAKE_CXX_STANDARD_LIBRARIES}")

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-Bstatic,--whole-archive -lwinpthread -Wl,--no-whole-archive")
add_executable(AiZOGraph main.cpp
        Matrix/GraphIncidence.cpp
        Matrix/GraphIncidence.h
        Utils/utils.cpp
        Utils/utils.h
        List/GraphList.cpp
        List/GraphList.h
        Algorithms/Prim/Prim.cpp
        Algorithms/Prim/Prim.h
        Algorithms/Kruskal/Kruskal.cpp
        Algorithms/Kruskal/Kruskal.h
        Algorithms/Dijkstra/Dijkstra.cpp
        Algorithms/Dijkstra/Dijkstra.h
        Algorithms/Bellman/Bellman.cpp
        Algorithms/Bellman/Bellman.h)