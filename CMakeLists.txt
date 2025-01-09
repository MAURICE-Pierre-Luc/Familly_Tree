cmake_minimum_required(VERSION 3.25)
project(projetCIR1_groupe_5 C)

set(CMAKE_C_STANDARD 11)

add_executable(projetCIR1_groupe_5 main.c
        date_and_birth.c
        region.c
        population.c
        create_html.h
        create_html.c
        read_csv.c
        menu.c
)
