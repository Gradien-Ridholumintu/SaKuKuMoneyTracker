// Header file untuk mendefinisikan variabel global, konstanta, dan struktur data
#ifndef DEFINISI_GLOBAL_H // mengecek apakah DEFINISI_GLOBAL_H sudah didefinisikan
#define DEFINISI_GLOBAL_H // mendefinisikan DEFINISI_GLOBAL_H jika belum didefinisikan

#include <string>

using namespace std;

const int MAX_DATA = 1000; // maksimum data yang dapat disimpan pada array
const string FILE_CSV = "data_transaksi.csv"; // nama file untuk menyimpan data transaksi

// ANSI Escape Codes untuk mewarnai output di terminal
#define RESET     "\x1B[0m"
#define BOLD      "\x1B[1m"
#define BLACK     "\x1B[30m"
#define RED       "\x1B[31m"
#define GREEN     "\x1B[32m"
#define YELLOW    "\x1B[33m"
#define CYAN      "\x1B[36m"
#define WHITE     "\x1B[37m"
#define BG_RED    "\x1B[41m"
#define BG_GREEN  "\x1B[42m"
#define BG_YELLOW "\x1B[43m"
#define BG_BLUE   "\x1B[44m"
#define BG_CYAN   "\x1B[46m"
#define BG_WHITE  "\x1B[47m"

// struct untuk menyimpan informasi transaksi
struct Transaksi {
    string tipe;
    string tanggal;
    string kategori;
    string deskripsi;
    long long nominal;
};

// struct untuk menyimpan status program secara keseluruhan
struct StatusProgram {
    Transaksi daftar_transaksi[MAX_DATA];
    int jumlah_data{};
    long long budget_limit{};
};

#endif