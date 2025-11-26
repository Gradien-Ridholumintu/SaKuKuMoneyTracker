// Implementasi fungsi pembantu
#include "fungsi_pembantu.h"
#include <cstdlib> // untuk system("cls") dan system("clear")
#include <iomanip> // untuk std::setw dan std::left
#include <iostream> // untuk std::cout dan std::cin
#include <limits> // untuk std::numeric_limits

using namespace std;

void bersihkan_terminal()
{
#ifdef _WIN32 // untuk Windows
    system("cls");
#else // untuk Unix/Linux/Mac
    system("clear");
#endif
}

void enter_untuk_lanjut()
{
    cout << "\nTekan [ENTER] untuk kembali...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // membersihkan buffer input
    cin.get(); // menunggu input enter
}

void cetak_judul(const string& judul)
{
    cout << "\n"
         << BG_BLUE << WHITE << BOLD // mengatur warna latar belakang biru dengan teks putih tebal
         << "   " << left << setw(40) << judul << "   " << RESET << "\n\n";
}

void cetak_garis_tabel()
{
    cout << "+";
    cout << string(4, '-') << "+"; // No
    cout << string(14, '-') << "+"; // Tanggal
    cout << string(13, '-') << "+"; // Tipe
    cout << string(16, '-') << "+"; // Kategori
    cout << string(26, '-') << "+"; // Deskripsi
    cout << string(20, '-') << "+"; // Nominal
    cout << "\n";
}

bool validasi_tanggal(const string& tanggal)
{
    // cek panjang harus 10 (YYYY-MM-DD)
    if (tanggal.length() == 10) { return true; }
    return false;
}

long long validasi_input_angka(const string& perintah)
{
    long long nilai;
    while (true) {
        std::cout << perintah; // menampilkan perintah input
        if (std::cin >> nilai) { return nilai; } // jika input adalah angka maka kembalikan nilai
        std::cout << BG_RED << WHITE << " [!] Input harus angka! " << RESET << "\n"; // pesan error
        std::cin.clear(); // membersihkan flag error
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // membersihkan buffer input
    }
}

int validasi_pilihan_menu(const string& perintah, const int min, const int max)
{
    int pilihan;
    while (true) {
        cout << perintah; // menampilkan perintah input
        if (cin >> pilihan) { // jika input adalah angka
            if (pilihan >= min && pilihan <= max) return pilihan; // jika pilihan ada dalam range maka kembalikan nilai
            cout << BG_RED << WHITE << " [!] Pilihan tidak ada. " << RESET << "\n"; // pesan error
        }
        else { // jika input bukan angka
            cout << BG_RED << WHITE << " [!] Input harus angka! " << RESET << "\n"; // pesan error
            cin.clear(); // membersihkan flag error
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // membersihkan buffer input
        }
    }
}

string validasi_input_teks(const string& perintah)
{
    string teks;
    while (true) {
        cout << perintah; // menampilkan perintah input
        getline(cin, teks); // membaca input teks beserta spasi
        if (!teks.empty()) return teks; // jika input tidak kosong maka kembalikan nilai
        cout << BG_RED << WHITE << " [!] Tidak boleh kosong. " << RESET << "\n"; // pesan error
    }
}

void swap_transaksi(Transaksi& a, Transaksi& b)
{
    Transaksi temp = a;
    a = b;
    b = temp;
}

void sort_transaksi_tanggal(Transaksi arr[], int size)
{
    // menggunakan bubble sort (descending)
    for (int i = 0; i < size - 1; i++) { // loop untuk setiap tanggal transaksi
        for (int j = 0; j < size - i - 1; j++) { // loop untuk membandingkan tanggal berdekatan
            if (arr[j].tanggal < arr[j + 1].tanggal) { swap_transaksi(arr[j], arr[j + 1]); } // tukar jika lebih kecil
        }
    }
}

void sort_transaksi_nominal(Transaksi arr[], int size)
{
    // menggunakan bubble sort (descending)
    for (int i = 0; i < size - 1; i++) { // loop untuk setiap nominal transaksi
        for (int j = 0; j < size - i - 1; j++) { // loop untuk membandingkan nominal berdekatan
            if (arr[j].nominal < arr[j + 1].nominal) { swap_transaksi(arr[j], arr[j + 1]); } // tukar jika lebih kecil
        }
    }
}