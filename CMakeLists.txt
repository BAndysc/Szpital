cmake_minimum_required(VERSION 2.8)
project(Szpital)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -Wall")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")

set(SOURCE_FILES src/hospital.c src/parse.h src/parse.c src/structure.c src/structure.h src/reference_string.c src/reference_string.h src/disease.c
        src/disease.h src/patient.c src/patient.h src/helpers.h  src/hospital_simulator.c src/hospital_simulator.h)
add_executable(Szpital ${SOURCE_FILES})
