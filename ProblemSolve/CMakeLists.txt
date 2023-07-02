cmake_minimum_required(VERSION 3.24)
project(ProblemSolve)

set(CMAKE_CXX_STANDARD 14)

add_executable(ProblemSolve
        coreConcept.cpp split/splitTest.cpp Permutation/makePermutation.cpp combination/combinationPS.cpp)
