#include <iostream>
#include <iomanip>
#include <string>
#include <algorithm>
#include <queue>
#include <stack>

using namespace std;

struct Menu {
    string nama;
    int harga;
};


Menu* searchMenu(Menu* menus, int jumlahMenu, const string& namaMenu) {
    for (int i = 0; i < jumlahMenu; ++i) {
        if (menus[i].nama == namaMenu) {
            return &menus[i];
        }
    }
    return nullptr;
}


void sortMenu(Menu* menus, int jumlahMenu) {
    auto compareMenu = [](const Menu& a, const Menu& b) {
        return a.nama < b.nama;
    };

    sort(menus, menus + jumlahMenu, compareMenu);
}


void showMenu(Menu* menus, int jumlahMenu) {
    cout << "==== Daftar Menu ====" << endl;
    for (int i = 0; i < jumlahMenu; ++i) {
        cout << i + 1 << ". " << menus[i].nama << " - Rp" << menus[i].harga << endl;
    }
}


void showOrders(stack<Menu*>& itemStack, queue<Menu*>& itemQueue) {
    if (!itemStack.empty()) {
        cout << "Daftar Pesanan (dari stack):" << endl;
        stack<Menu*> tempStack = itemStack;
        while (!tempStack.empty()) {
            Menu* pesanan = tempStack.top();
            tempStack.pop();
            cout << "- " << pesanan->nama << " (" << pesanan->harga << ")\n";
        }

        cout << "\nDaftar Pesanan (dari queue):" << endl;
        queue<Menu*> tempQueue = itemQueue;
        while (!tempQueue.empty()) {
            Menu* pesanan = tempQueue.front();
            tempQueue.pop();
            cout << "- " << pesanan->nama << " (" << pesanan->harga << ")\n";
        }
    } else {
        cout << "Stack pesanan kosong." << endl;
    }
}

int main() {
    const int MAX_MENU = 10;
    Menu menuList[MAX_MENU] = {
        {"Ayam Penyet", 15000},
        {"Tahu Goreng", 5000},
        {"Tempe Penyet", 6000},
        {"Nasi Putih", 3000},
        {"Sambal Pedas", 2000},
        {"Es Teh Manis", 4000},
        {"Jus Alpukat", 8000},
        {"Kerupuk Udang", 2500},
        {"Lalapan", 7000},
        {"Air Mineral", 2000}
    };

    int jumlahMenu = 10;
    stack<Menu*> itemStack;
    queue<Menu*> itemQueue;
    int totalPembayaran = 0;

    char pilihan;
    do {
        cout << "==== Selamat Datang Di  Warung Ayam Penyet ====" << endl;
        cout << "0. Keluar" << endl;
        cout << "1. Lihat Menu" << endl;
        cout << "2. Pesan Menu" << endl;
        cout << "3. Tambah Pesanan" << endl;
        cout << "4. Tampilkan Pesanan" << endl;
        cout << "5. Hapus Pesanan" << endl;
        cout << "6. Total Pembayaran" << endl;
        cout << "7. Bayar" << endl;
        cout << "8. Proses Pesanan" << endl;
        cout << "Pilihan Anda: ";
        cin >> pilihan;

        switch (pilihan) {
            case '0':
                cout << "Terima kasih telah telah memesan ." << endl;
                break;
            case '1':
                showMenu(menuList, jumlahMenu);
                break;
           case '2': {
    cout << "==== Pilihan Pesan Menu ====" << endl;
    cout << "Sebelum menambah pesanan, pilih salah satu opsi pesanan:\n";
    for (int i = 0; i < jumlahMenu; ++i) {
        cout << i + 1 << ". " << menuList[i].nama << endl;
    }

    cout << "Masukkan nama menu yang ingin dipesan: ";
    string namaPesanan;
    cin.ignore();
    getline(cin, namaPesanan);

    Menu* pesanan = searchMenu(menuList, jumlahMenu, namaPesanan);
    if (pesanan != nullptr) {
        itemStack.push(pesanan);
        itemQueue.push(pesanan);
        totalPembayaran += pesanan->harga;
        cout << "Pesanan " << pesanan->nama << " ditambahkan ke dalam stack dan queue." << endl;
    } else {
        cout << "Menu tidak ditemukan." << endl;
    }
    break;
}


            case '3': {
                cout << "==== Tambah Pesanan ====" << endl;
                string namaPesanan;
                cout << "Masukkan nama menu: ";
                cin.ignore();
                getline(cin, namaPesanan);

                Menu* pesanan = searchMenu(menuList, jumlahMenu, namaPesanan);
                if (pesanan != nullptr) {
                    itemStack.push(pesanan);
                    itemQueue.push(pesanan);
                    totalPembayaran += pesanan->harga;
                    cout << "Pesanan ditambahkan ke dalam stack dan queue." << endl;
                } else {
                    cout << "Menu tidak ditemukan." << endl;
                }
                break;
            }
            case '4':
                showOrders(itemStack, itemQueue);
                break;
            case '5': {
                if (!itemStack.empty()) {
                    Menu* pesananDihapus = itemStack.top();
                    itemStack.pop();
                    itemQueue = {}; 
                    totalPembayaran -= pesananDihapus->harga;
                    cout << "Pesanan " << pesananDihapus->nama << " dihapus." << endl;
                } else {
                    cout << "Stack pesanan kosong." << endl;
                }
                break;
            }
            case '6':
                cout << "Total Pembayaran: Rp" << totalPembayaran << endl;
                break;
            case '7': {
                int pembayaran;
                cout << "Masukkan jumlah pembayaran: Rp";
                cin >> pembayaran;

                if (pembayaran >= totalPembayaran) {
                    int kembalian = pembayaran - totalPembayaran;
                    cout << "Pembayaran berhasil. Kembalian: Rp" << kembalian << endl;
                    totalPembayaran = 0;
                } else {
                    cout << "Pembayaran kurang. Silakan masukkan jumlah yang cukup." << endl;
                }
                break;
            }
            case '8': {
                if (!itemQueue.empty()) {
                    Menu* pesananDiproses = itemQueue.front();
                    itemQueue.pop();
                    totalPembayaran -= pesananDiproses->harga;
                    cout << "Pesanan " << pesananDiproses->nama << " diproses." << endl;
                } else {
                    cout << "Queue pesanan kosong." << endl;
                }
                break;
            }
            default:
                cout << "Pilihan tidak valid. Silakan coba lagi." << endl;
        }

        cout << endl;

        cin.ignore();  
    } while (pilihan != '0');

return 0;
}
