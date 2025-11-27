// Header file untuk mendeklarasikan variabel global, mendefinisikan konstanta global, dan mendefinisikan struktur data
#ifndef DEFINISI_GLOBAL_H // mengecek apakah DEFINISI_GLOBAL_H sudah didefinisikan
#define DEFINISI_GLOBAL_H // mendefinisikan DEFINISI_GLOBAL_H jika belum didefinisikan

#include <string>

using namespace std;

// konstanta global
const int MAX_DATA = 1000; // maksimum data yang dapat disimpan pada array
const string FILE_CSV = "data_transaksi.csv"; // nama file untuk menyimpan data transaksi

// ANSI Escape Codes untuk mewarnai output di terminal
#define RESET     "\x1B[0m"
#define BOLD      "\x1B[1m"
#define HITAM     "\x1B[30m"
#define MERAH     "\x1B[31m"
#define HIJAU     "\x1B[32m"
#define KUNING    "\x1B[33m"
#define CYAN      "\x1B[36m"
#define PUTIH     "\x1B[37m"
#define BG_MERAH  "\x1B[41m"
#define BG_HIJAU  "\x1B[42m"
#define BG_KUNING "\x1B[43m"
#define BG_BIRU   "\x1B[44m"

// struct untuk menyimpan informasi transaksi
struct Transaksi {
    string tipe;
    string tanggal;
    string kategori;
    string deskripsi;
    long long nominal;
};

// deklarasi variabel global menggunakan extern agar tidak terjadi duplikasi
extern Transaksi daftar_transaksi[MAX_DATA]; // array of struct untuk menyimpan data transaksi
extern int jumlah_data; // variabel untuk menyimpan jumlah data transaksi
extern long long budget_limit; // variabel untuk menyimpan batas anggaran bulanan

#endif