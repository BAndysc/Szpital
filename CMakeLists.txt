cmake_minimum_required(VERSION 2.8)
project(Szpital)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -Wall")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")

set(SOURCE_FILES hospital.c parse.h parse.c structure.c structure.h reference_string.c reference_string.h disease.c disease.h patient.c patient.h helpers.h  hospital_simulator.c hospital_simulator.h)
add_executable(Szpital ${SOURCE_FILES})
