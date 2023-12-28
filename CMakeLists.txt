cmake_minimum_required(VERSION 3.24)
project(ProjetoAedLp12023 C)

set(CMAKE_C_STANDARD 17)

add_executable(ProjetoAedLp12023 main.c libs_src/lib_stats.c libs_src/lib_stats.h libs_src/lib_util.c libs_src/lib_util.h estruturas.c estruturas.h funcoes.c funcoes.h)
