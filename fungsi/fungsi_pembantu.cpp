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
    cout << "\nTekan [ENTER] untuk kembali..."; // menampilkan pesan untuk menekan enter
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // membersihkan buffer input agar tidak ada sisa input
    cin.get(); // menunggu input enter dari pengguna
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
    cout << string(26, '-') << "+"; // Kategori
    cout << string(36, '-') << "+"; // Deskripsi
    cout << string(30, '-') << "+"; // Nominal
    cout << "\n";
}

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
         << string(18, ' ') << "SMART MONEY TRACKER APP" << string(18, ' ') << RESET << "\n"; // menampilkan judul aplikasi
    cout << CYAN << "   ====================================================" << RESET << "\n\n"; // menampilkan garis pemisah
}

bool validasi_tanggal(const string& tanggal)
{
    // cek panjang tanggal harus 10 (YYYY-MM-DD)
    if (tanggal.length() == 10) { return true; } // jika panjang tanggal sesuai maka kembalikan true
    return false; // jika panjang tanggal tidak sesuai maka kembalikan false
}

long long validasi_input_angka(const string& perintah)
{
    long long nilai; // variabel untuk menyimpan input angka
    while (true) {
        cout << perintah; // menampilkan perintah input
        if (cin >> nilai) { return nilai; } // jika input adalah angka maka kembalikan nilai
        cout << BG_RED << WHITE << " [!] Input harus angka! " << RESET << "\n"; // jika input bukan angka maka cetak pesan error
        cin.clear(); // membersihkan flag error agar cin dapat digunakan kembali
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // membersihkan buffer input agar tidak ada sisa input
    }
}

int validasi_pilihan_menu(const string& perintah, const int min, const int max)
{
    int pilihan; // variabel untuk menyimpan input pilihan menu
    while (true) {
        cout << perintah; // menampilkan perintah input
        if (cin >> pilihan) { // jika pilihan adalah angka
            if (pilihan >= min && pilihan <= max) return pilihan; // jika pilihan ada dalam range maka kembalikan nilai
            cout << BG_RED << WHITE << " [!] Pilihan tidak ada. " << RESET << "\n"; // jika pilihan di luar range maka cetak pesan error
        }
        else { // jika pilihan bukan angka
            cout << BG_RED << WHITE << " [!] Input harus angka! " << RESET << "\n"; // jika pilihan bukan angka maka cetak pesan error
            cin.clear(); // membersihkan flag error agar cin dapat digunakan kembali
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // membersihkan buffer input agar tidak ada sisa input
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
        cout << BG_RED << WHITE << " [!] Tidak boleh kosong. " << RESET << "\n"; // jika input kosong maka cetak pesan error
    }
}

void swap_transaksi(Transaksi& a, Transaksi& b)
{
    Transaksi temp = a; // menyimpan nilai a ke variabel sementara
    a = b; // menukar nilai a dengan b
    b = temp; // menukar nilai b dengan variabel sementara
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