
cmake_minimum_required(VERSION 3.14)
project(dcc012-lab2-sort1)

option(CLASSROOM "Enable classroom build" OFF)
option(CPU_TIME  "Enable cputime build" ON)

set(INPUT_DIR "${PROJECT_SOURCE_DIR}/tests/input/")
set(EXPECTED_OUTPUT_DIR "${PROJECT_SOURCE_DIR}/tests/expected_output/")

configure_file(${PROJECT_SOURCE_DIR}/siga/config.h.in ${PROJECT_SOURCE_DIR}/siga/include/config.h) 
include_directories(${PROJECT_SOURCE_DIR}/siga/include)


enable_testing()
add_subdirectory(siga)
add_subdirectory(tests)

add_test(
    NAME Setup
    COMMAND cmake -E remove -f dataset.bin
    )

add_test(
  NAME  TestImportacao1000
  COMMAND $<TARGET_FILE:test1>
  )

add_test(
   NAME  TestMergeSort1000
   COMMAND $<TARGET_FILE:test2> 
   )

add_test(
    NAME  MergeSortCompare
    COMMAND cmake -E compare_files test2.csv ${PROJECT_SOURCE_DIR}/tests/expected_output/test2.csv
    )

add_test(
  NAME  TestQuickSort1000
  COMMAND COMMAND $<TARGET_FILE:test3> 
)

add_test(
    NAME  QuickSortCompare
    COMMAND cmake -E compare_files test2.csv ${PROJECT_SOURCE_DIR}/tests/expected_output/test3.csv
    )

add_test(
  NAME  Importe2000
  COMMAND COMMAND $<TARGET_FILE:test4> 
)

add_test(
  NAME  OrdenaCursoENome
  COMMAND COMMAND $<TARGET_FILE:test5> 
)

add_test(
    NAME  OrdenaCursoENomeCompare
    COMMAND cmake -E compare_files test5.csv ${PROJECT_SOURCE_DIR}/tests/expected_output/test5.csv
    )

add_test(
      NAME  Compara
      COMMAND COMMAND $<TARGET_FILE:test6> 
)
    