cmake_minimum_required(VERSION 4.0)
project(SaKuKuMoneyTracker)

set(CMAKE_CXX_STANDARD 20)

add_executable(SaKuKu
        main.cpp
        fungsi/fungsi_utama.cpp
        fungsi/fungsi_pembantu.cpp
        fungsi/definisi_global.h
        fungsi/fungsi_pembantu.h
        fungsi/fungsi_utama.h
)
