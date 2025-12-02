# **💸SaKuKu Money Tracker💸**

### Dibuat Untuk Memenuhi Final Project Pemrograman 1 PRG 9 (Wahyono, S.Kom., Ph.D.).

#### Dibuat Oleh:

| **Nama**                       | **NIM**      |
| ------------------------------------ | ------------------ |
| **Gradien Ridholumintu**       | 25/555306/PA/23271 |
| **Nauval Andrian Antarest P.** | 25/555547/PA/23287 |
| **Mutiara Ameer Ricila**       | 25/555997/PA/23330 |
| **Muhamad Fathul Farhi**       | 25/560014/PA/23581 |
| **Almira Ahadia Agustin**      | 25/561232/PA/23660 |
| **Reyhana Fayyaz Sabila**      | 25/561315/PA/23644 |
| **Reffi Callista Hindargo**    | 25/558098/PA/23457 |
| **Chelsea Flavia Yuandhiza**   | 25/557728/PA/23436 |

## 📄Deskripsi Singkat Program

**SaKuKu** adalah program manajemen keuangan pribadi sederhana berbasis terminal yang ditulis menggunakan bahasa C++.  Program ini dirancang untuk membantu pengguna mencatat pemasukan dan pengeluaran, melakukan budgeting, serta menganalisis prioritas pengeluaran.

## 🔎Fitur Utama Program

Program ini memiliki fitur-fitur berikut:

1. **Tambah Transaksi**: mencatat pemasukan atau pengeluaran dengan detail (Tanggal, Kategori, Deskripsi, Nominal).
2. **Kelola Riwayat Transaksi**: melihat daftar transaksi serta fitur **Edit** dan **Hapus** data transaksi.
3. **Laporan Keuangan**: menampilkan ringkasan total pemasukan, total pengeluaran, dan sisa saldo.
4. **Skala Prioritas**: menganalisis pengeluaran dengan mengurutkannya dari nominal terbesar ke terkecil.
5. **Atur Anggaran**: menetapkan batas pengeluaran (*budget limit*) bulanan.
6. **Cek Status Anggaran**: memantau apakah pengeluaran saat ini masih aman atau sudah melebihi batas anggaran (*over budget*).
7. **Penyimpanan Otomatis**: Data disimpan secara permanen dalam file CSV (`data_transaksi.csv`) agar bisa di *load* kembali.

## 📂Struktur File dan Data

Aplikasi ini menggunakan file `data_transaksi.csv` sebagai *database* sederhana.

### Format CSV

File `data_transaksi.csv` menggunakan format pemisah titik koma (`;`).

* **Baris 1**: Menyimpan nilai **Budget Limit**.
* **Baris 2 dst**: Menyimpan data transaksi.

Contoh isi file:

```
4500000
Pemasukan;2025-11-28;Komisi;Freelance;2500000
Pengeluaran;2023-11-22;Konsumsi;Jajan dan Bahan Makan;400000
Pengeluaran;2023-11-21;Pendidikan;Bayar UKT;1000000
```

### Struktur Folder Proyek

```
SaKuKuMoneyTracker/
├── CMakeLists.txt           # Konfigurasi CMake
├── data_transaksi.csv       # File penyimpanan data (dibuat otomatis, bila tidak ada di main folder berarti ada di subfolder build)
├── main.cpp                 # Entry point program
└── fungsi/
    ├── definisi_global.h    # Struct dan variabel global
    ├── fungsi_utama.h       # Deklarasi fitur utama
    ├── fungsi_utama.cpp     # Implementasi fitur utama
    ├── fungsi_pembantu.h    # Deklarasi fungsi helper/UI
    └── fungsi_pembantu.cpp  # Implementasi fungsi helper/UI
```

## ⚙️Cara Kompilasi & Menjalankan

### A. Menggunakan Online Compiler

#### [!!] WARNING: menjalankan program menggunakan online compiler menghapus beberapa fungsionalitas program.

#### [!!] Tidak semua online compiler support fitur clear terminal, gunakan OnlineGDB untuk pengalaman terbaik.

1. Pergi ke laman [OnlineGDB](https://www.onlinegdb.com/)
2. Pilih bahasa pemrograman C++ 17 di pojok kanan atas (bila tampilan input error, ganti versi C++)
3. Pergi ke [docs berisikan kode khusus untuk online compiler](https://docs.google.com/document/d/1fcFmZDQYL3XQXLRSPtCZ3f6GlFmoqlLv/edit?usp=sharing&ouid=103891571868123742308&rtpof=true&sd=true)
4. Salin semua kode pada docs
5. Tempelkan kode pada OnlineGDB
6. Jalankan program dengan menekan opsi "RUN" di bagian atas

### B. Menggunakan GCC

#### [!!] Pastikan anda memiliki GCC jika ingin menggunakan opsi ini

1. Buka terminal pada folder yang ingin anda gunakan untuk menyimpan program
2. Clone repositori dengan menjalankan perintah berikut

```bash
git clone https://github.com/Gradien-Ridholumintu/SaKuKuMoneyTracker.git
cd SaKuKuMoneyTracker
```

3. Compile program dengan menjalankan perintah berikut

```bash
g++ main.cpp fungsi/fungsi_utama.cpp fungsi/fungsi_pembantu.cpp -o SaKuKu -std=c++20
```

4. Jalankan executable

### C. Menggunakan CMAKE

#### [!!] Pastikan anda memiliki CMAKE jika ingin menggunakan opsi ini

1. Buka terminal pada folder yang ingin anda gunakan untuk menyimpan program
2. Clone repositori dengan menjalankan perintah berikut

```bash
git clone https://github.com/Gradien-Ridholumintu/SaKuKuMoneyTracker.git
cd SaKuKuMoneyTracker
```

3. Build program dengan menjalankan perintah berikut

```bash
mkdir build
cd build
cmake ..
cmake --build .
```

4. Pergi ke build folder dengan menjalankan perintah berikut

```bash
cd build/Debug
```

5. Jalankan executable
