// Implementasi fungsi utama
#include "fungsi_utama.h"
#include "fungsi_pembantu.h"
#include <fstream> // untuk std::ifstream dan std::ofstream
#include <iomanip> // untuk std::setw dan std::left
#include <iostream> // untuk std::cout dan std::cin
#include <limits> // untuk std::numeric_limits
#include <sstream> // untuk std::stringstream

using namespace std;

void muat_data()
{
    jumlah_data = 0; // inisialisasi jumlah data transaksi menjadi 0
    budget_limit = 0; // inisialisasi budget limit menjadi 0
    ifstream file(FILE_CSV); // membuka file CSV untuk dibaca
    if (!file.is_open()) {
        cout << RED << " [!] Gagal membuka file data_transaksi.csv. Memulai dengan data kosong. " << RESET
             << "\n"; // jika gagal membuka file CSV maka tampilkan pesan error
        return; // keluar dari fungsi
    }

    string line; // variabel sementara untuk menyimpan baris dari file CSV
    if (getline(file, line)) { // membaca baris pertama dari file CSV (yang berisikan budget limit)
        budget_limit = atoll(line.c_str()); // mengonversi string budget limit ke long long dan menyimpannya
    }
    while (getline(file, line) && jumlah_data < MAX_DATA) { // membaca setiap baris file CSV dari baris kedua hingga baris terakhir
                                                            // selama belum mencapai batas maksimum jumlah data
        stringstream ss(line); // mengubah satu baris string menjadi input stream
        string nominal_str; // variabel sementara untuk menyimpan nominal dalam bentuk string
        Transaksi& trans = daftar_transaksi[jumlah_data]; // referensi ke transaksi saat ini

        getline(ss, trans.tipe, ';'); // membaca tipe transaksi dari stream ke transaksi saat ini
        getline(ss, trans.tanggal, ';'); // membaca tanggal transaksi dari stream ke transaksi saat ini
        getline(ss, trans.kategori, ';'); // membaca kategori transaksi dari stream ke transaksi saat ini
        getline(ss, trans.deskripsi, ';'); // membaca deskripsi transaksi dari stream ke transaksi saat ini
        getline(ss, nominal_str, ';'); // membaca nominal transaksi dari stream ke string sementara

        long long nilai = atoll(nominal_str.c_str()); // mengonversi string nominal ke long long dan menyimpannya ke variabel sementara
        if (nilai == 0 && nominal_str != "0") { // jika hasil konversi adalah 0 tapi string bukan "0" maka ada kesalahan
            continue; // lewati data ini
        }

        trans.nominal = nilai; // menyimpan nominal yang sudah dikonversi ke transaksi saat ini
        jumlah_data++; // menambah jumlah data transaksi yang valid agar loop terus berjalan mengisi array
                       // transaksi dengan indeks berikutnya
    }
    file.close(); // menutup file setelah selesai membaca
}

void simpan_data()
{
    ofstream file(FILE_CSV); // membuka file CSV untuk ditulis
    if (!file.is_open()) {
        cout << RED << " [!] Gagal membuka file data_transaksi.csv untuk disimpan. " << RESET
             << "\n"; // // jika gagal membuka file CSV maka tampilkan pesan error
        return; // keluar dari fungsi
    }

    file << budget_limit << "\n"; // menulis budget limit pada baris pertama file CSV
    // untuk baris-baris berikutnya dilakukan:
    for (int i = 0; i < jumlah_data; i++) { // looping untuk setiap transaksi yang ada
        Transaksi& trans = daftar_transaksi[i]; // referensi ke transaksi saat ini
        // menulis data transaksi saat ini ke file CSV dengan format yang sesuai
        file << trans.tipe << ";" << trans.tanggal << ";" << trans.kategori << ";" << trans.deskripsi << ";" << trans.nominal << "\n";
    }
    file.close(); // menutup file setelah selesai menulis
    cout << BG_BLUE << WHITE << " >> Data tersimpan otomatis. " << RESET << "\n"; // menampilkan pesan sukses penyimpanan data
}

void tambah_transaksi()
{
    bersihkan_terminal(); // membersihkan terminal sebelum menampilkan tampilan tambah transaksi
    if (jumlah_data >= MAX_DATA) { // memeriksa apakah jumlah data sudah mencapai batas maksimum
        cout << BG_RED << WHITE << " [ERROR] Penyimpanan penuh! " << RESET << "\n"; // jika data sudah penuh maka tampilkan pesan error
        enter_untuk_lanjut(); // menunggu input enter dari pengguna
        return; // keluar dari fungsi
    }

    Transaksi& baru = daftar_transaksi[jumlah_data]; // referensi ke transaksi baru yang akan ditambahkan

    cetak_judul("TAMBAH TRANSAKSI BARU"); // mencetak "TAMBAH TRANSAKSI BARU" dengan format judul
    // menampilkan pilihan tipe transaksi
    cout << "Pilih: " << GREEN << "[1] Pemasukan" << RESET << " / " << RED << "[2] Pengeluaran" << RESET << "\n";
    int tipe_transaksi = validasi_pilihan_menu("Pilihan (1/2): ", 1, 2); // memvalidasi input pilihan tipe transaksi

    if (tipe_transaksi == 1) // jika pilihan adalah 1
    {
        baru.tipe = "Pemasukan";
    } // set tipe transaksi menjadi "Pemasukan"
    else // jika pilihan adalah 2
    {
        baru.tipe = "Pengeluaran";
    } // set tipe transaksi menjadi "Pengeluaran"

    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // membersihkan buffer input agar tidak ada sisa input

    cout << "\n----- Detail ----- \n"; // menampilkan header detail transaksi
    do {
        cout << "Tanggal (YYYY-MM-DD) : "; // menampilkan contoh format tanggal
        getline(cin, baru.tanggal); // membaca input tanggal dari pengguna ke struct
        if (!validasi_tanggal(baru.tanggal)) {
            cout << RED << "   Format salah! Harus 10 karakter.\n" << RESET;
        } // jika format tanggal salah maka tampilkan pesan error
    }
    while (!validasi_tanggal(baru.tanggal)); // ulangi selama input tanggal belum valid

    baru.kategori = validasi_input_teks("Kategori : "); // memvalidasi dan membaca input kategori dari pengguna ke struct
    baru.deskripsi = validasi_input_teks("Deskripsi: "); // memvalidasi dan membaca input deskripsi dari pengguna ke struct

    do {
        baru.nominal = validasi_input_angka("Nominal (Rp): "); // memvalidasi dan membaca input nominal dari pengguna ke struct
        if (baru.nominal <= 0) {
            cout << RED << "   Harus lebih dari 0!\n" << RESET;
        } // jika input nominal kurang dari atau sama dengan 0 maka tampilkan pesan error
    }
    while (baru.nominal <= 0); // ulangi selama input nominal kurang dari atau sama dengan 0

    jumlah_data++; // menambah jumlah data transaksi setelah berhasil menambahkan transaksi baru
    cout << "\n" << BG_GREEN << BLACK << " [SUKSES] Data disimpan! " << RESET << "\n"; // menampilkan pesan sukses penambahan data
    enter_untuk_lanjut(); // menunggu input enter dari pengguna
}

void hapus_transaksi(int indeks)
{
    for (int i = indeks; i < jumlah_data - 1; i++) { // looping dari indeks yang akan dihapus hingga indeks terakhir
        daftar_transaksi[i] = daftar_transaksi[i + 1]; // menggeser setiap data transaksi di sebelah kanan indeks yang akan dihapus sebanyak
                                                       // satu langkah ke kiri
    }
    jumlah_data--; // mengurangi jumlah data transaksi setelah penghapusan
    cout << "\n" << BG_GREEN << BLACK << " [v] Data dihapus. " << RESET << "\n"; // menampilkan pesan sukses penghapusan data
}

void edit_transaksi(int indeks)
{
    Transaksi& edit = daftar_transaksi[indeks]; // referensi ke transaksi yang akan diedit
    string input_temp; // variabel sementara untuk menyimpan input pengguna

    cout << "\n" << BG_YELLOW << BLACK << " --- Edit Data (Enter = Lewati) --- " << RESET << "\n"; // menampilkan header edit data

    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // membersihkan buffer input agar tidak ada sisa input

    cout << "Tanggal Lama: " << edit.tanggal << "\nBaru >> "; // menampilkan tanggal lama dan meminta input tanggal baru
    getline(cin, input_temp); // membaca input tanggal baru dari pengguna ke variabel sementara
    if (!input_temp.empty() && validasi_tanggal(input_temp)) {
        edit.tanggal = input_temp;
    } // jika input tidak kosong dan valid maka update tanggal pada struct

    cout << "Kategori Lama: " << edit.kategori << "\nBaru >> "; // menampilkan kategori lama dan meminta input kategori baru
    getline(cin, input_temp); // membaca input kategori baru dari pengguna ke variabel sementara
    if (!input_temp.empty()) { edit.kategori = input_temp; } // jika input tidak kosong maka update kategori pada struct

    cout << "Deskripsi Lama: " << edit.deskripsi << "\nBaru >> "; // menampilkan deskripsi lama dan meminta input deskripsi baru
    getline(cin, input_temp); // membaca input deskripsi baru dari pengguna ke variabel sementara
    if (!input_temp.empty()) { edit.deskripsi = input_temp; } // jika input tidak kosong maka update deskripsi pada struct

    cout << "Nominal Lama: " << edit.nominal << "\nBaru (0 utk skip) >> "; // menampilkan nominal lama dan meminta input nominal baru
    string nominal_str; // variabel sementara untuk menyimpan input nominal baru
    getline(cin, nominal_str); // membaca input nominal baru dari pengguna ke variabel sementara
    if (!nominal_str.empty()) { // jika input tidak kosong
        long long temp = atoll(nominal_str.c_str()); // mengonversi string ke long long dan menyimpannya ke variabel sementara
        if (temp > 0) { edit.nominal = temp; } // jika hasil konversi lebih dari 0 maka update nominal pada struct
    }
    cout << "\n" << BG_GREEN << BLACK << " [v] Data diperbarui. " << RESET << "\n"; // menampilkan pesan sukses pembaruan data
}

void kelola_riwayat()
{
    while (true) {
        bersihkan_terminal(); // membersihkan terminal sebelum menampilkan riwayat transaksi
        cetak_judul("RIWAYAT TRANSAKSI"); // mencetak "RIWAYAT TRANSAKSI" dengan format judul
        cetak_garis_tabel(); // mencetak garis tabel (atas)

        sort_transaksi_tanggal(daftar_transaksi,
                               jumlah_data); // mengurutkan data transaksi berdasarkan tanggal dari yang terbaru hingga ke yang terlama

        for (int i = 0; i < jumlah_data; i++) { // looping untuk setiap data transaksi yang ada
            Transaksi& trans = daftar_transaksi[i]; // referensi ke transaksi saat ini
            cout << "| " << left << setw(3) << (i + 1) << "| " << setw(13) << trans.tanggal << "| "
                 << ((trans.tipe == "Pemasukan") ? GREEN : RED) << setw(12) << trans.tipe << RESET << "| " << setw(25) << trans.kategori
                 << "| " << setw(35) << trans.deskripsi << "| Rp " << right << setw(25) << trans.nominal
                 << " |\n"; // mencetak data transaksi saat ini dengan format tabel
        }
        cetak_garis_tabel(); // mencetak garis tabel (bawah)

        cout << "\n[1] Edit  [2] Hapus  [0] Kembali\n"; // menampilkan pilihan untuk mengedit, menghapus, atau kembali
        int pilihan = validasi_pilihan_menu("Pilihan >> ", 0,
                                            2); // memvalidasi input pilihan dari pengguna dan menyimpannya ke variabel pilihan

        if (pilihan == 0) { break; } // jika pilihan adalah 0 maka keluar dari loop dan kembali ke menu utama
        if (pilihan == 1 || pilihan == 2) { // jika pilihan adalah 1 atau 2
            // meminta pengguna untuk memasukkan nomor urut transaksi yang akan diedit atau dihapus
            int nomor = validasi_pilihan_menu("No Urut: ", 1,
                                              jumlah_data); // memvalidasi input nomor urut dari pengguna dan menyimpannya ke variabel nomor
            if (pilihan == 1) {
                edit_transaksi(nomor - 1);
            } // jika pilihan adalah 1 maka panggil fungsi edit_transaksi dengan indeks nomor - 1
            else { // jika pilihan adalah 2
                char confirm; // variabel untuk menyimpan konfirmasi penghapusan
                cout << "Yakin hapus? (y/n): "; // meminta konfirmasi penghapusan dari pengguna
                cin >> confirm; // membaca input konfirmasi dari pengguna
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // membersihkan buffer input agar tidak ada sisa input
                if (confirm == 'y' || confirm == 'Y') {
                    hapus_transaksi(nomor - 1);
                } // jika konfirmasi adalah 'y' atau 'Y' maka panggil fungsi hapus_transaksi dengan indeks nomor - 1
            }
            enter_untuk_lanjut(); // menunggu input enter dari pengguna
        }
    }
}

void tampilkan_lapkeu()
{
    bersihkan_terminal(); // membersihkan terminal sebelum menampilkan laporan keuangan
    long long pemasukan = 0, pengeluaran = 0; // variabel untuk menyimpan total pemasukan dan pengeluaran

    for (int i = 0; i < jumlah_data; i++) { // looping untuk setiap data transaksi yang ada
        if (daftar_transaksi[i].tipe == "Pemasukan") // jika tipe transaksi adalah "Pemasukan"
        {
            pemasukan += daftar_transaksi[i].nominal;
        } // tambahkan nominal transaksi ke total pemasukan
        else // jika tipe transaksi adalah "Pengeluaran
        {
            pengeluaran += daftar_transaksi[i].nominal;
        } // tambahkan nominal transaksi ke total pengeluaran
    }

    cetak_judul("LAPORAN KEUANGAN"); // mencetak "LAPORAN KEUANGAN" dengan format judul
    cout << " Total Pemasukan   : " << GREEN << "Rp " << pemasukan << RESET << "\n"; // menampilkan total pemasukan dengan warna hijau
    cout << " Total Pengeluaran : " << RED << "Rp " << pengeluaran << RESET << "\n"; // menampilkan total pengeluaran dengan warna merah
    cout << " -------------------------------\n"; // mencetak garis pemisah
    cout << " Sisa Saldo        : " << BOLD << "Rp " << (pemasukan - pengeluaran) << RESET
         << "\n\n"; // menampilkan sisa saldo dengan format tebal

    cout << YELLOW << "[?] Gunakan Menu 4 (Skala Prioritas) untuk melihat detail pengeluaran terbesar.\n"
         << RESET; // menampilkan informasi tambahan dengan warna kuning
    enter_untuk_lanjut(); // menunggu input enter dari pengguna
}

void tampilkan_skala_prioritas()
{
    bersihkan_terminal(); // membersihkan terminal sebelum menampilkan skala prioritas

    Transaksi temp[MAX_DATA]; // array sementara untuk menyimpan transaksi pengeluaran agar tidak mengubah data asli
    int count = 0; // variabel untuk menghitung jumlah transaksi pengeluaran
    for (int i = 0; i < jumlah_data; i++) { // looping untuk setiap data transaksi yang ada
        if (daftar_transaksi[i].tipe == "Pengeluaran") { // jika tipe transaksi adalah "Pengeluaran"
            temp[count] = daftar_transaksi[i]; // salin data transaksi ke array sementara
            count++; // tambahkan jumlah transaksi pengeluaran
        }
    }

    sort_transaksi_nominal(temp, count); // mengurutkan array sementara berdasarkan nominal dari yang terbesar hingga ke yang terkecil

    cetak_judul("SKALA PRIORITAS (TERBESAR)"); // mencetak "SKALA PRIORITAS (TERBESAR)" dengan format judul
    cetak_garis_tabel(); // mencetak garis tabel (atas)
    for (int i = 0; i < count; i++) { // looping untuk setiap data transaksi pengeluaran yang ada di array sementara
        cout << "| " << left << setw(3) << (i + 1) << "| " << setw(13) << temp[i].tanggal << "| " << RED << setw(12) << "Pengeluaran"
             << RESET << "| " << setw(25) << temp[i].kategori << "| " << setw(35) << temp[i].deskripsi << "| Rp " << right << setw(25)
             << temp[i].nominal << " |\n"; // mencetak data transaksi pengeluaran saat ini dengan format tabel
    }
    cetak_garis_tabel(); // mencetak garis tabel (bawah)
    enter_untuk_lanjut(); // menunggu input enter dari pengguna
}

void atur_budget()
{
    bersihkan_terminal(); // membersihkan terminal sebelum menampilkan pengaturan anggaran
    cetak_judul("PENGATURAN ANGGARAN"); // mencetak "PENGATURAN ANGGARAN" dengan format judul
    cout << "Saat ini: Rp " << budget_limit << "\n\n"; // menampilkan anggaran (budget limit) saat ini

    long long budget_limit_baru
            = validasi_input_angka("Target Baru (0 = Hapus): "); // memvalidasi dan membaca input anggaran baru dari pengguna
    if (budget_limit_baru < 0) {
        cout << RED << "Tidak boleh negatif!" << RESET << "\n";
    } // jika input anggaran baru kurang dari 0 maka tampilkan pesan error
    else { // jika input anggaran baru valid
        budget_limit = budget_limit_baru; // update anggaran (budget limit) dengan nilai baru
        cout << "\n" << BG_GREEN << BLACK << " [v] Disimpan. " << RESET << "\n"; // menampilkan pesan sukses penyimpanan anggaran
    }
    enter_untuk_lanjut(); // menunggu input enter dari pengguna
}

void cek_status_budget()
{
    bersihkan_terminal(); // membersihkan terminal sebelum menampilkan status anggaran
    if (budget_limit == 0) { // jika anggaran (budget limit) belum diatur
        cout << YELLOW << "Anda belum mengatur budget." << RESET << "\n"; // menampilkan pesan informasi dengan warna kuning
        enter_untuk_lanjut(); // menunggu input enter dari pengguna
        return; // keluar dari fungsi
    }

    long long pengeluaran = 0; // variabel untuk menyimpan total pengeluaran
    for (int i = 0; i < jumlah_data; i++) { // looping untuk setiap data transaksi yang ada
        // menambahkan nominal transaksi ke total pengeluaran jika tipe transaksi adalah "Pengeluaran"
        if (daftar_transaksi[i].tipe == "Pengeluaran") { pengeluaran += daftar_transaksi[i].nominal; }
    }

    cetak_judul("STATUS ANGGARAN"); // mencetak "STATUS ANGGARAN" dengan format judul
    cout << " Batas Anggaran : Rp " << budget_limit << "\n"; // menampilkan batas anggaran (budget limit)
    cout << " Terpakai       : " << ((pengeluaran > budget_limit) ? RED : GREEN) << "Rp " << pengeluaran << RESET
         << "\n"; // menampilkan total pengeluaran dengan warna merah jika melebihi anggaran atau hijau jika masih dalam anggaran

    long long sisa = budget_limit - pengeluaran; // menghitung sisa anggaran
    cout << " Sisa Anggaran  : Rp " << sisa << "\n"; // menampilkan sisa anggaran

    // menampilkan peringatan jika sisa anggaran kurang dari 0 (pengeluaran melebihi anggaran)
    if (sisa < 0) { cout << "\n" << BG_RED << WHITE << " [!!!] MELEBIHI BATAS ANGGARAN! " << RESET << "\n"; }

    enter_untuk_lanjut(); // menunggu input enter dari pengguna
}