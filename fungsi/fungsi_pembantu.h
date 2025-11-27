// Header file untuk deklarasi fungsi-fungsi pembantu, yaitu fungsi-fungsi umum yang mendukung fungsi utama
#ifndef FUNGSI_PEMBANTU_H // mengecek apakah FUNGSI_PEMBANTU_H sudah didefinisikan
#define FUNGSI_PEMBANTU_H // mendefinisikan FUNGSI_PEMBANTU_H jika belum didefinisikan

#include "definisi_global.h" // menyertakan definisi global

// fungsi tampilan pengguna dan utilitas
void bersihkan_terminal(); // fungsi untuk membersihkan output pada terminal
void enter_untuk_lanjut(); // fungsi untuk menunggu input enter dari pengguna
void cetak_garis_tabel(); // fungsi untuk mencetak garis tabel
void cetak_baris_tabel(int nomor, const Transaksi& trans);
void cetak_judul(const std::string& judul); // fungsi untuk mencetak judul dengan format tertentu
void cetak_logo(); // fungsi untuk mencetak logo program

// fungsi validasi input
bool validasi_tanggal(const std::string& tanggal); // fungsi untuk memvalidasi format tanggal YYYY-MM-DD
long long validasi_input_angka(const std::string& perintah); // fungsi untuk memvalidasi input angka dari pengguna
int validasi_pilihan_menu(const std::string& perintah, int min,
                          int max); // fungsi untuk memvalidasi pilihan menu dari pengguna
std::string validasi_input_teks(const std::string& perintah); // fungsi untuk memvalidasi input teks dari pengguna

// fungsi pengurutan transaksi
void sort_transaksi_tanggal(Transaksi arr[],
                            int size); // fungsi untuk mengurutkan transaksi berdasarkan tanggal (terbaru ke terlama)
void sort_transaksi_nominal(Transaksi arr[],
                            int size); // fungsi untuk mengurutkan transaksi berdasarkan nominal (terbesar ke terkecil)
void swap_transaksi(Transaksi& a, Transaksi& b); // fungsi untuk menukar dua transaksi

#endif