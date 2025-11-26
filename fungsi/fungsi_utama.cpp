// Implementasi fungsi utama
#include "fungsi_utama.h"
#include "fungsi_pembantu.h"
#include <fstream> // untuk std::ifstream dan std::ofstream
#include <iomanip> // untuk std::setw dan std::left
#include <iostream> // untuk std::cout dan std::cin
#include <limits> // untuk std::numeric_limits
#include <sstream> // untuk std::stringstream

using namespace std;

// ASCII Art logo program
const string logo = CYAN "  $$$$$$\\            $$\\   $$\\          $$\\   $$\\          \n"
                         " $$  __$$\\           $$ | $$  |         $$ | $$  |         \n"
                         " $$ /  \\__| $$$$$$\\  $$ |$$  /$$\\   $$\\ $$ |$$  /$$\\   $$\\ \n"
                         " \\$$$$$$\\   \\____$$\\ $$$$$  / $$ |  $$ |$$$$$  / $$ |  $$ |\n"
                         "  \\____$$\\  $$$$$$$ |$$  $$<  $$ |  $$ |$$  $$<  $$ |  $$ |\n"
                         " $$\\   $$ |$$  __$$ |$$ |\\$$\\ $$ |  $$ |$$ |\\$$\\ $$ |  $$ |\n"
                         " \\$$$$$$  |\\$$$$$$$ |$$ | \\$$\\\\$$$$$$  |$$ | \\$$\\\\$$$$$$  |\n"
                         "  \\______/  \\_______|\\__|  \\__|\\______/ \\__|  \\__|\\______/ \n" RESET;

void cetak_logo()
{
    cout << logo << "\n"; // menampilkan logo ASCII art
    cout << BG_BLUE << WHITE << BOLD // mengatur warna latar belakang biru dengan teks putih tebal
         << string(18, ' ') << "SMART MONEY TRACKER APP" << string(18, ' ') << RESET << "\n";
    cout << CYAN << "   ====================================================" << RESET << "\n\n";
}

void muat_data(StatusProgram& program)
{
    program.jumlah_data = 0;
    program.budget_limit = 0;
    ifstream file(FILE_CSV); // membuka file CSV untuk dibaca
    if (!file.is_open()) {
        cout << RED << " [!] Gagal membuka file data_transaksi.csv. Memulai dengan data kosong. " << RESET
             << "\n"; // pesan error
        return;
    } // jika gagal membuka maka keluar dari fungsi

    string line; // variabel sementara untuk menyimpan baris dari file CSV
    if (getline(file, line)) { // membaca baris pertama dari file CSV (yang berisikan budget limit)
        program.budget_limit = atoll(line.c_str()); // mengonversi string ke long long dan menyimpannya
    }
    while (getline(file, line)
           && program.jumlah_data < MAX_DATA) { // membaca setiap baris file CSV hingga baris terakhir
                                                // selama belum mencapai batas maksimum jumlah data
        stringstream ss(line); // mengubah satu baris string menjadi input stream
        string nominal_str; // variabel sementara untuk menyimpan nominal dalam bentuk string
        Transaksi& trans = program.daftar_transaksi[program.jumlah_data]; // referensi ke transaksi saat ini

        getline(ss, trans.tipe, ';'); // membaca tipe transaksi dari stream ke transaksi saat ini
        getline(ss, trans.tanggal, ';'); // membaca tanggal transaksi dari stream ke transaksi saat ini
        getline(ss, trans.kategori, ';'); // membaca kategori transaksi dari stream ke transaksi saat ini
        getline(ss, trans.deskripsi, ';'); // membaca deskripsi transaksi dari stream ke transaksi saat ini
        getline(ss, nominal_str, ';'); // membaca nominal transaksi dari stream ke string sementara

        long long nilai = atoll(nominal_str.c_str()); // mengonversi string nominal ke long long
        if (nilai == 0 && nominal_str != "0") { // jika hasil konversi adalah 0 tapi string bukan "0" maka ada kesalahan
            continue; // lewati data ini
        }

        trans.nominal = nilai; // menyimpan nominal yang sudah dikonversi ke transaksi saat ini
        program.jumlah_data++; // menambah jumlah data transaksi yang valid agar loop terus berjalan mengisi array
                               // transaksi dengan indeks berikutnya
    }
    file.close(); // menutup file setelah selesai membaca
}

void simpan_data(StatusProgram& program)
{
    std::ofstream file(FILE_CSV); // membuka file CSV untuk ditulis
    if (!file.is_open()) {
        cout << RED << " [!] Gagal membuka file data_transaksi.csv untuk disimpan. " << RESET << "\n"; // pesan error
        return;
    } // jika gagal membuka maka keluar dari fungsi

    file << program.budget_limit << "\n"; // menulis budget limit pada baris pertama file CSV
    for (int i = 0; i < program.jumlah_data; i++) { // looping untuk setiap transaksi yang ada
        Transaksi& trans = program.daftar_transaksi[i]; // referensi ke transaksi saat ini
        // menulis data transaksi saat ini ke file CSV dengan format yang sesuai
        file << trans.tipe << ";" << trans.tanggal << ";" << trans.kategori << ";" << trans.deskripsi << ";" << trans.nominal << "\n";
    }
    file.close(); // menutup file setelah selesai menulis
    std::cout << BG_BLUE << WHITE << " >> Data tersimpan otomatis. " << RESET << "\n";
}

void tambah_transaksi(StatusProgram& program)
{
    bersihkan_terminal(); // membersihkan terminal sebelum menampilkan tampilan tambah transaksi
    if (program.jumlah_data >= MAX_DATA) { // memeriksa apakah jumlah data sudah mencapai batas maksimum
        std::cout << BG_RED << WHITE << " [ERROR] Penyimpanan penuh! " << RESET << "\n"; // pesan error
        enter_untuk_lanjut(); // menunggu input enter dari pengguna
        return; // keluar dari fungsi
    }

    Transaksi& baru = program.daftar_transaksi[program.jumlah_data]; // referensi ke transaksi baru yang akan ditambahkan
    int tipe_transaksi; // variabel untuk menyimpan pilihan tipe transaksi

    cetak_judul("TAMBAH TRANSAKSI BARU"); // mencetak "TAMBAH TRANSAKSI BARU" dengan format judul
    std::cout << "Pilih: " << GREEN << "[1] Pemasukan" << RESET << " / " << RED << "[2] Pengeluaran" << RESET << "\n";
    tipe_transaksi = validasi_pilihan_menu("Pilihan (1/2): ", 1, 2); // memvalidasi input pilihan tipe transaksi

    if (tipe_transaksi == 1) // jika pilihan adalah 1
        baru.tipe = "Pemasukan"; // set tipe transaksi menjadi "Pemasukan"
    else // jika pilihan adalah 2
        baru.tipe = "Pengeluaran"; // set tipe transaksi menjadi "Pengeluaran"

    if (std::cin.peek() == '\n') std::cin.ignore(); //

    std::cout << "\n--- Detail --- \n";
    do {
        std::cout << "Tanggal (YYYY-MM-DD) : ";
        std::getline(std::cin, baru.tanggal);
        if (!validasi_tanggal(baru.tanggal)) std::cout << RED << "   Format salah! Harus 10 karakter.\n" << RESET;
    }
    while (!validasi_tanggal(baru.tanggal));

    baru.kategori = validasi_input_teks("Kategori : ");
    baru.deskripsi = validasi_input_teks("Deskripsi: ");

    do {
        baru.nominal = validasi_input_angka("Nominal (Rp): ");
        if (baru.nominal <= 0) std::cout << RED << "   Harus lebih dari 0!\n" << RESET;
    }
    while (baru.nominal <= 0);

    program.jumlah_data++;
    std::cout << "\n" << BG_GREEN << BLACK << " [SUKSES] Data disimpan! " << RESET << "\n";
    enter_untuk_lanjut();
}

void hapus_transaksi(StatusProgram& program, int indeks)
{
    for (int i = indeks; i < program.jumlah_data - 1; i++) {
        program.daftar_transaksi[i] = program.daftar_transaksi[i + 1];
    }
    program.jumlah_data--;
    std::cout << "\n" << BG_GREEN << BLACK << " [v] Data dihapus. " << RESET << "\n";
}

void edit_transaksi(StatusProgram& program, int indeks)
{
    Transaksi& t = program.daftar_transaksi[indeks];
    std::string input_temp;

    std::cout << "\n" << BG_YELLOW << BLACK << " --- Edit Data (Enter = Lewati) --- " << RESET << "\n";

    if (std::cin.peek() == '\n') std::cin.ignore();

    std::cout << "Tanggal Lama: " << t.tanggal << "\nBaru >> ";
    std::getline(std::cin, input_temp);
    if (!input_temp.empty() && validasi_tanggal(input_temp)) t.tanggal = input_temp;

    std::cout << "Kategori Lama: " << t.kategori << "\nBaru >> ";
    std::getline(std::cin, input_temp);
    if (!input_temp.empty()) t.kategori = input_temp;

    std::cout << "Deskripsi Lama: " << t.deskripsi << "\nBaru >> ";
    std::getline(std::cin, input_temp);
    if (!input_temp.empty()) t.deskripsi = input_temp;

    std::cout << "Nominal Lama: " << t.nominal << "\nBaru (0 utk skip) >> ";
    std::string str_nominal;
    std::getline(std::cin, str_nominal);
    if (!str_nominal.empty()) {
        try {
            long long temp = std::stoll(str_nominal);
            if (temp > 0) t.nominal = temp;
        }
        catch (...) {
        }
    }
    std::cout << "\n" << BG_GREEN << BLACK << " [v] Data diperbarui. " << RESET << "\n";
}

void kelola_riwayat(StatusProgram& program)
{
    while (true) {
        bersihkan_terminal();
        cetak_judul("RIWAYAT TRANSAKSI");
        cetak_garis_tabel();

        sort_transaksi_tanggal(program.daftar_transaksi, program.jumlah_data);

        for (int i = 0; i < program.jumlah_data; i++) {
            Transaksi& t = program.daftar_transaksi[i];
            std::cout << "| " << std::left << std::setw(4) << (i + 1) << "| " << std::setw(12) << t.tanggal << "| "
                      << ((t.tipe == "Pemasukan") ? GREEN : RED) << std::setw(12) << t.tipe << RESET << "| "
                      << std::setw(15) << t.kategori << "| " << std::setw(25) << t.deskripsi << "| Rp " << std::right
                      << std::setw(15) << t.nominal << " |\n";
        }
        cetak_garis_tabel();

        std::cout << "\n[1] Edit  [2] Hapus  [0] Kembali\n";
        int opsi = validasi_pilihan_menu("Pilihan >> ", 0, 2);

        if (opsi == 0) break;

        if (opsi == 1 || opsi == 2) {
            int no = validasi_pilihan_menu("No Urut: ", 1, program.jumlah_data);
            if (opsi == 1)
                edit_transaksi(program, no - 1);
            else {
                char confirm;
                std::cout << "Yakin hapus? (y/n): ";
                std::cin >> confirm;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                if (confirm == 'y' || confirm == 'Y') hapus_transaksi(program, no - 1);
            }
            enter_untuk_lanjut();
        }
    }
}

// ==========================================
// LAPORAN SEDERHANA
// ==========================================
void tampilkan_lapkeu(StatusProgram& program)
{
    bersihkan_terminal();
    long long masuk = 0, keluar = 0;

    for (int i = 0; i < program.jumlah_data; i++) {
        if (program.daftar_transaksi[i].tipe == "Pemasukan")
            masuk += program.daftar_transaksi[i].nominal;
        else
            keluar += program.daftar_transaksi[i].nominal;
    }

    cetak_judul("LAPORAN KEUANGAN");
    std::cout << " Total Pemasukan   : " << GREEN << "Rp " << masuk << RESET << "\n";
    std::cout << " Total Pengeluaran : " << RED << "Rp " << keluar << RESET << "\n";
    std::cout << " -------------------------------\n";
    std::cout << " Sisa Saldo        : " << BOLD << "Rp " << (masuk - keluar) << RESET << "\n\n";

    std::cout << YELLOW << "[INFO] Gunakan Menu 4 (Skala Prioritas) untuk melihat detail pengeluaran terbesar.\n"
              << RESET;
    enter_untuk_lanjut();
}

void tampilkan_skala_prioritas(StatusProgram& program)
{
    bersihkan_terminal();

    Transaksi temp[MAX_DATA];
    int count = 0;
    for (int i = 0; i < program.jumlah_data; i++) {
        if (program.daftar_transaksi[i].tipe == "Pengeluaran") {
            temp[count] = program.daftar_transaksi[i];
            count++;
        }
    }

    sort_transaksi_nominal(temp, count);

    cetak_judul("SKALA PRIORITAS (TERBESAR)");
    cetak_garis_tabel();
    for (int i = 0; i < count; i++) {
        std::cout << "| " << std::left << std::setw(4) << (i + 1) << "| " << std::setw(12) << temp[i].tanggal << "| "
                  << RED << std::setw(12) << "Keluar" << RESET << "| " << std::setw(15) << temp[i].kategori << "| "
                  << std::setw(25) << temp[i].deskripsi << "| Rp " << std::right << std::setw(15) << temp[i].nominal
                  << " |\n";
    }
    cetak_garis_tabel();
    enter_untuk_lanjut();
}

void atur_budget(StatusProgram& program)
{
    bersihkan_terminal();
    cetak_judul("PENGATURAN ANGGARAN");
    std::cout << "Saat ini: Rp " << program.budget_limit << "\n\n";

    long long baru = validasi_input_angka("Target Baru (0 = Hapus): ");
    if (baru < 0)
        std::cout << "Tidak boleh negatif!\n";
    else {
        program.budget_limit = baru;
        std::cout << "\n" << BG_GREEN << BLACK << " [v] Disimpan. " << RESET << "\n";
    }
    enter_untuk_lanjut();
}

void cek_status_budget(StatusProgram& program)
{
    bersihkan_terminal();
    if (program.budget_limit == 0) {
        std::cout << "Anda belum mengatur budget.\n";
        enter_untuk_lanjut();
        return;
    }

    long long keluar = 0;
    for (int i = 0; i < program.jumlah_data; i++) {
        if (program.daftar_transaksi[i].tipe == "Pengeluaran") keluar += program.daftar_transaksi[i].nominal;
    }

    cetak_judul("STATUS ANGGARAN");
    std::cout << " Batas Anggaran : Rp " << program.budget_limit << "\n";
    std::cout << " Terpakai       : " << ((keluar > program.budget_limit) ? RED : GREEN) << "Rp " << keluar << RESET
              << "\n";

    long long sisa = program.budget_limit - keluar;
    std::cout << " Sisa Anggaran  : Rp " << sisa << "\n";

    if (sisa < 0) std::cout << "\n" << BG_RED << WHITE << " [!!!] OVER BUDGET! " << RESET << "\n";

    enter_untuk_lanjut();
}