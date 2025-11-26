#include <iostream>
#include "fungsi/definisi_global.h"
#include "fungsi/fungsi_pembantu.h"
#include "fungsi/fungsi_utama.h"

int main() {
    StatusProgram app_state;
    muat_data(app_state);

    int pilihan = 0;
    while (pilihan != 7) {
        bersihkan_terminal();

        // Menampilkan Logo ASCII Art
        cetak_logo();

        std::cout << "  [1]  Tambah Transaksi\n";
        std::cout << "  [2]  Kelola Riwayat (Edit/Hapus)\n";
        std::cout << "  [3]  Laporan Keuangan\n";
        std::cout << "  [4]  Skala Prioritas\n";
        std::cout << "  [5]  Atur Anggaran\n";
        std::cout << "  [6]  Cek Status Anggaran\n";
        std::cout << "  [7]  Keluar & Simpan\n";
        std::cout << "=========================================\n";

        pilihan = validasi_pilihan_menu("Pilihan >> ", 1, 7);

        switch (pilihan) {
        case 1: tambah_transaksi(app_state); break;
        case 2: kelola_riwayat(app_state); break;
        case 3: tampilkan_lapkeu(app_state); break;
        case 4: tampilkan_skala_prioritas(app_state); break;
        case 5: atur_budget(app_state); break;
        case 6: cek_status_budget(app_state); break;
        case 7:
            simpan_data(app_state);
            std::cout << GREEN << "\nTerima kasih! Data telah diamankan.\n" << RESET;
            return 0;
        }
    }
    return 0;
}