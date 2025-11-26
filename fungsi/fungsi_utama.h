// Header file untuk deklarasi fungsi-fungsi utama
#ifndef FUNGSI_UTAMA_H // mengecek apakah FUNGSI_UTAMA_H sudah didefinisikan
#define FUNGSI_UTAMA_H // mendefinisikan FUNGSI_UTAMA_H jika belum didefinisikan

#include "definisi_global.h"

// fungsi tampilan ASCII art
void cetak_logo(); // fungsi untuk mencetak logo program

// fungsi file I/O
void muat_data(StatusProgram& program); // fungsi untuk memuat data dari file CSV ke dalam struct StatusProgram
void simpan_data(StatusProgram& program); // fungsi untuk menyimpan data dari struct StatusProgram ke dalam file CSV

// fungsi manajemen transaksi
void tambah_transaksi(StatusProgram& program); // fungsi untuk menambah transaksi baru
void kelola_riwayat(StatusProgram& program); // fungsi untuk mengelola riwayat transaksi

// fungsi laporan keuangan
void tampilkan_lapkeu(StatusProgram& program); // fungsi untuk menampilkan laporan keuangan
void tampilkan_skala_prioritas(StatusProgram& program); // fungsi untuk menampilkan skala prioritas pengeluaran

// fungsi pengaturan anggaran
void atur_budget(StatusProgram& program); // fungsi untuk mengatur anggaran bulanan
void cek_status_budget(StatusProgram& program); // fungsi untuk mengecek status anggaran bulanan

// fungsi edit dan hapus transaksi untuk kelola riwayat
void hapus_transaksi(StatusProgram& program, int indeks); // fungsi untuk menghapus transaksi pada indeks tertentu
void edit_transaksi(StatusProgram& program, int indeks); // fungsi untuk mengedit transaksi pada indeks tertentu

#endif