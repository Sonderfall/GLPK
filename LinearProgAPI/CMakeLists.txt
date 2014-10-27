cmake_minimum_required (VERSION 2.8)

file (GLOB COMMONS src/tools/tools.cpp src/linprog/variable/variable.cpp src/linprog/constraint/constraint.cpp src/linprog/linear-problem/linear-problem.cpp src/main/main.cpp)

add_executable (LinearProgAPI ${COMMONS})

target_link_libraries (LinearProgAPI glpk)
