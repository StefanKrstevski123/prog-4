cmake_minimum_required(VERSION 3.31)
project(prog_4)

set(CMAKE_CXX_STANDARD 20)

include_directories(push-relabel, string-matching)

add_executable(prog_4 adjlist.cpp)
add_executable(matrix_run  matrica.cpp)
add_executable(djikstra_run djikstra.cpp)
add_executable(bellmand belmandford.cpp)
add_executable(gen generator.cpp)
add_executable(matrixf matrixfloyd.cpp)
add_executable(adjf adjfloyd.cpp)
add_executable(max uamaxflow.cpp)
add_executable(ford fordful.cpp)
add_executable(augf fordaug.cpp)
add_executable(edd edmond.cpp)
add_executable(din   dininc.cpp)
add_executable(regexp regex_primer.cpp)
add_executable(germa GermanicStrings.cpp)
add_executable(relabel
        "push-relabel/push_relabel1.cpp"
)

add_executable(gud
        "string-matching/Good Substrings.cpp"
)

add_executable(long
        "string-matching/Longest Duplicate Substring.cpp"
)

add_executable(palindro
        "string-matching/Palindromic Characteristics.cpp"
)

add_executable(spojjj
        "string-matching/SPOJ - Pattern Find.cpp"
)

add_executable(rabin-karp
        "string-matching/Rabin-Karp.cpp"
)