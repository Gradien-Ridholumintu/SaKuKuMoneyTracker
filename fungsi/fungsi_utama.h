// Header file untuk deklarasi fungsi-fungsi utama, yaitu fungsi-fungsi yang menangani fitur utama aplikasi
#ifndef FUNGSI_UTAMA_H // mengecek apakah FUNGSI_UTAMA_H sudah didefinisikan
#define FUNGSI_UTAMA_H // mendefinisikan FUNGSI_UTAMA_H jika belum didefinisikan

// fungsi file I/O
void muat_data(); // fungsi untuk memuat data dari file CSV
void simpan_data(); // fungsi untuk menyimpan data ke dalam file CSV

// fungsi manajemen transaksi
void tambah_transaksi(); // fungsi untuk menambah transaksi baru
void kelola_riwayat(); // fungsi untuk mengelola riwayat transaksi

// fungsi laporan keuangan
void tampilkan_lapkeu(); // fungsi untuk menampilkan laporan keuangan
void tampilkan_skala_prioritas(); // fungsi untuk menampilkan skala prioritas pengeluaran

// fungsi pengaturan anggaran
void atur_budget(); // fungsi untuk mengatur anggaran bulanan
void cek_status_budget(); // fungsi untuk mengecek status anggaran bulanan

// fungsi edit dan hapus transaksi untuk kelola riwayat
void hapus_transaksi(int indeks); // fungsi untuk menghapus transaksi pada indeks tertentu
void edit_transaksi(int indeks); // fungsi untuk mengedit transaksi pada indeks tertentu

#endif