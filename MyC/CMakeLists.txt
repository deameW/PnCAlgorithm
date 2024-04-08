cmake_minimum_required(VERSION 3.27)
project(MyC)

set(CMAKE_CXX_STANDARD 17)

add_executable(MyC
        path_planning/Dijstra/Djkstra.cpp
        path_planning/Dijstra/Djkstra.h
        path_planning/Astar/Astar.cpp
        path_planning/Astar/Astar.h
        some_test/Test.cpp
        some_test/Test.h
        heuristic_search/genetic_algorithm/genetic.cpp
        heuristic_search/genetic_algorithm/genetic.h
)
