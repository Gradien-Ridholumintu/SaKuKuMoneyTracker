// SaKuKu: Prgoram Manajemen Keuangan Pribadi Sederhana Berbasis Terminal
// Dibuat untuk memenuhi Final Project Mata Kuliah Pemrograman 1 Kelas PRG 9 (Wahyono, S.Kom., Ph.D.)
/*
 * Dibuat oleh:
 *              Kelompok 2
 * Gradien Ridholumintu 25/555306/PA/23271
 * Nauval Andrian Antarest P. 25/555547/PA/23287
 * Mutiara Ameer Ricila 25/555997/PA/23330
 * Muhamad Fathul Farhi 25/560014/PA/23581
 * Almira Ahadia Agustin 25/561232/PA/23660
 * Reyhana Fayyaz Sabila 25/561315/PA/23644
 * Reffi Callista Hindargo 25/558098/PA/23457
 * Chelsea Flavia Yuandhiza 25/557728/PA/23436
 */
#include "fungsi/definisi_global.h" // menyertakan definisi global
#include "fungsi/fungsi_pembantu.h" // menyertakan fungsi pembantu
#include "fungsi/fungsi_utama.h" // menyertakan fungsi utama
#include <iostream> // untuk std::cout dan std::cin

// definisi variabel global
Transaksi daftar_transaksi[MAX_DATA]; // array of struct untuk menyimpan data transaksi
int jumlah_data{}; // variabel untuk menyimpan jumlah data transaksi
long long budget_limit{}; // variabel untuk menyimpan batas anggaran bulanan

int main()
{
    muat_data(); // memuat data dari file CSV saat program dijalankan

    int pilihan = 0; // variabel untuk menyimpan pilihan menu utama
    while (pilihan != 7) { // looping selama pilihan bukan 7 (Keluar & Simpan)
        bersihkan_terminal(); // membersihkan terminal sebelum menampilkan menu utama

        cetak_logo(); // menampilkan logo program

        std::cout << "  [1]  Tambah Transaksi\n"; // menampilkan pilihan 1 pada menu
        std::cout << "  [2]  Kelola Riwayat (Edit/Hapus)\n"; // menampilkan pilihan 2 pada menu
        std::cout << "  [3]  Laporan Keuangan\n"; // menampilkan pilihan 3 pada menu
        std::cout << "  [4]  Skala Prioritas\n"; // menampilkan pilihan 4 pada menu
        std::cout << "  [5]  Atur Anggaran\n"; // menampilkan pilihan 5 pada menu
        std::cout << "  [6]  Cek Status Anggaran\n"; // menampilkan pilihan 6 pada menu
        std::cout << "  [7]  Keluar & Simpan\n"; // menampilkan pilihan 7 pada menu
        std::cout << "=========================================\n"; // mencetak garis pemisah

        pilihan = validasi_pilihan_menu("Pilihan >> ", 1, 7); // memvalidasi input pilihan menu utama dari pengguna

        switch (pilihan) { // menangani pilihan menu utama
        case 1:
            tambah_transaksi();
            break; // jika pilihan adalah 1 maka panggil fungsi tambah_transaksi
        case 2:
            kelola_riwayat();
            break; // jika pilihan adalah 2 maka panggil fungsi kelola_riwayat
        case 3:
            tampilkan_lapkeu();
            break; // jika pilihan adalah 3 maka panggil fungsi tampilkan_lapkeu
        case 4:
            tampilkan_skala_prioritas();
            break; // jika pilihan adalah 4 maka panggil fungsi tampilkan_skala_prioritas
        case 5:
            atur_budget();
            break; // jika pilihan adalah 5 maka panggil fungsi atur_budget
        case 6:
            cek_status_budget();
            break; // jika pilihan adalah 6 maka panggil fungsi cek_status_budget
        case 7: // jika pilihan adalah 7 maka simpan data dan keluar dari program
            simpan_data();
            std::cout << GREEN << "\nTerima kasih! Data telah diamankan.\n" << RESET;
            return 0;
        }
    }
}