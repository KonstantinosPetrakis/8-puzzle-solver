cmake_minimum_required(VERSION 3.17)
project(PROJECT_AI)

set(CMAKE_CXX_STANDARD 14)

add_executable(PROJECT_AI main.cpp Puzzle.cpp Puzzle.h Search.cpp Search.h DFS.cpp DFS.h BFS.cpp BFS.h BestFS.cpp Search.h AStar.cpp AStar.h BestFS.h API.cpp API.h)