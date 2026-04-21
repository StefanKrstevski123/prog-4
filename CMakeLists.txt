cmake_minimum_required(VERSION 3.31)
project(prog_4)

set(CMAKE_CXX_STANDARD 20)

include_directories(push-relabel, string-matching)

add_executable(prog_4 prvo_polugodie/adjlist.cpp)
add_executable(matrix_run prvo_polugodie/matrica.cpp)
add_executable(djikstra_run prvo_polugodie/djikstra.cpp)
add_executable(bellmand prvo_polugodie/belmandford.cpp)
add_executable(gen prvo_polugodie/generator.cpp)
add_executable(matrixf prvo_polugodie/matrixfloyd.cpp)
add_executable(adjf prvo_polugodie/adjfloyd.cpp)
add_executable(max prvo_polugodie/uamaxflow.cpp)
add_executable(ford prvo_polugodie/fordful.cpp)
add_executable(augf prvo_polugodie/fordaug.cpp)
add_executable(edd prvo_polugodie/edmond.cpp)
add_executable(din prvo_polugodie/dininc.cpp)
add_executable(regexp prvo_polugodie/regex_primer.cpp)
add_executable(germa prvo_polugodie/GermanicStrings.cpp)
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

add_executable(trieen string-matching/trie_en.cpp)
add_executable(triemk string-matching/trie_mk.cpp)
add_executable(myint myinteger.cpp
        grahamjarvis.cpp)
add_executable(myint2 myinteger2.cpp)
add_executable(trnn linearna_algebra_trans/trnsfr.cpp)
add_executable(majmun majmunn/majmun_rotacija.cpp)
add_executable(trangll triangulejsh.cpp)
add_executable(grahhj grahamjarvis.cpp)