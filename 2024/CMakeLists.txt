set(CMAKE_CXX_STANDARD 17)

function(add_aoc_executables array)
  foreach (dir IN LISTS ${array})
    add_executable(${dir}_part1 ${dir}/part1.cpp)
    add_executable(${dir}_part2 ${dir}/part2.cpp)
  endforeach()
endfunction()

set(folders 01 02 03 04 05 06)
add_aoc_executables(folders)

