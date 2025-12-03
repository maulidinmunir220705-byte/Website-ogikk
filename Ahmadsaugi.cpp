#include <iostream>
#include <vector>
#include <string>
#include <iomanip> // Untuk format output

using namespace std;

// Struct untuk menyimpan data transaksi
struct Transaksi {
    string jenis; // "Deposit" atau "Withdraw"
    double jumlah;
    double saldoSetelah; // Saldo setelah transaksi
};

// Class untuk akun ATM
class AkunATM {
private:
    string pin; // PIN untuk login
    double saldo;
    vector<Transaksi> riwayat;

public:
    // Konstruktor: Inisialisasi dengan PIN default dan saldo awal
    AkunATM(string p = "111111", double s = 10000000.0) : pin(p), saldo(s) {}

    // Fungsi login: Cek PIN
    bool login(string inputPin) {
        return inputPin == pin;
    }

    // Fungsi cek saldo
    void cekSaldo() {
        cout << "Saldo Anda saat ini: Rp " << fixed << setprecision(2) << saldo << endl;
    }

    // Fungsi setor tunai
    void setorTunai(double jumlah) {
        if (jumlah > 0) {
            saldo += jumlah;
            riwayat.push_back({"Deposit", jumlah, saldo});
            cout << "Setor tunai berhasil! Saldo baru: Rp " << fixed << setprecision(2) << saldo << endl;
        } else {
            cout << "Jumlah setor harus lebih dari 0." << endl;
        }
    }

    // Fungsi tarik tunai
    void tarikTunai(double jumlah) {
        if (jumlah > 0 && jumlah <= saldo) {
            saldo -= jumlah;
            riwayat.push_back({"Withdraw", jumlah, saldo});
            cout << "Tarik tunai berhasil! Saldo baru: Rp " << fixed << setprecision(2) << saldo << endl;
        } else if (jumlah > saldo) {
            cout << "Saldo tidak cukup." << endl;
        } else {
            cout << "Jumlah tarik harus lebih dari 0." << endl;
        }
    }

    // Fungsi lihat riwayat transaksi
    void lihatRiwayat() {
        if (riwayat.empty()) {
            cout << "Belum ada transaksi." << endl;
        } else {
            cout << "Riwayat Transaksi:" << endl;
            cout << "--------------------------------------------------" << endl;
            for (size_t i = 0; i < riwayat.size(); ++i) {
                cout << i + 1 << ". " << riwayat[i].jenis << " Rp " << fixed << setprecision(2) << riwayat[i].jumlah
                     << " | Saldo setelah: Rp " << riwayat[i].saldoSetelah << endl;
            }
            cout << "--------------------------------------------------" << endl;
        }
    }
};

int main() {
    AkunATM akun; // Buat akun dengan PIN default "1234" dan saldo Rp 1.000.000
    string inputPin;
    bool loggedIn = false;

    cout << "=== Simulasi ATM ===" << endl;

    // Loop login
    while (!loggedIn) {
        cout << "Masukkan PIN: ";
        cin >> inputPin;
        if (akun.login(inputPin)) {
            loggedIn = true;
            cout << "Login berhasil! Selamat datang." << endl;
        } else {
            cout << "PIN salah. Coba lagi." << endl;
        }
    }

    // Menu utama setelah login
    int pilihan;
    while (true) {
        cout << "\n=== Menu ATM ===" << endl;
        cout << "1. Cek Saldo" << endl;
        cout << "2. Setor Tunai" << endl;
        cout << "3. Tarik Tunai" << endl;
        cout << "4. Riwayat Transaksi" << endl;
        cout << "5. Keluar" << endl;
        cout << "Pilih opsi (1-5): ";
        cin >> pilihan;

        switch (pilihan) {
            case 1:
                akun.cekSaldo();
                break;
            case 2: {
                double jumlah;
                cout << "Masukkan jumlah setor: Rp ";
                cin >> jumlah;
                akun.setorTunai(jumlah);
                break;
            }
            case 3: {
                double jumlah;
                cout << "Masukkan jumlah tarik: Rp ";
                cin >> jumlah;
                akun.tarikTunai(jumlah);
                break;
            }
            case 4:
                akun.lihatRiwayat();
                break;
            case 5:
                cout << "Terima kasih telah menggunakan ATM. Sampai jumpa!" << endl;
                return 0;
            default:
                cout << "Pilihan tidak valid. Coba lagi." << endl;
        }
    }

    return 0;
}

