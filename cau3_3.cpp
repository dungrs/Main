#include <iostream>
#include <string>
#include <fstream>
#include <cstring>

using namespace std;

struct Kho {
    int maKho;
    char tenKho[50];
    char diaChi[100];
};

struct VatTu {
    int maKho;
    char maVT[6];
    int soLuong;
    char donViTinh[20];
    int donGia;
    long thanhTien;
};

void nhapKho() {
    Kho kho;
    cout << "Nhap Makho: ";
    cin >> kho.maKho;
    cout << "Nhap Tenkho: ";
    cin.ignore();
    cin.getline(kho.tenKho, 50);
    cout << "Nhap Diachi: ";
    cin.getline(kho.diaChi, 100);

    ofstream file("Kho.bin", ios::binary | ios::app);
    if (!file.is_open()) {
        cerr << "Loi! Khong the mo file Kho.bin!" << endl;
        return;
    }
    file.write((char*)&kho, sizeof(Kho));
    file.close();
    cout << "Kho da duoc them vao file Kho.bin!" << endl;
    cout << "__________________________________" << endl;
}

void nhapVatTu() {
    VatTu vattu;
    cout << "Nhap Makho: ";
    cin >> vattu.maKho;
    cout << "Nhap MaVT: ";
    cin >> vattu.maVT;
    cout << "Nhap Soluong: ";
    cin >> vattu.soLuong;
    cout << "Nhap Donvitinh: ";
    cin.ignore();
    cin.getline(vattu.donViTinh, 20);
    cout << "Nhap Dongia: ";
    cin >> vattu.donGia;

    vattu.thanhTien = (long) vattu.soLuong * vattu.donGia;

    ofstream file("VatTu.bin", ios::binary | ios::app);
    if (!file.is_open()) {
        cerr << "Loi! Khong the mo file VatTu.bin!" << endl;
        return;
    }
    file.write((char*)&vattu, sizeof(VatTu));
    file.close();
    cout << "Vat tu da duoc them vao file VatTu.bin" << endl;
    cout << "_____________________________________________" << endl;
}

void ghiVatTuTheoMaVT() {
    char maVT[6];
    cout << "Nhap VatTu: ";
    cin >> maVT;
    
    ifstream vattuFile("VatTu.bin", ios::binary);
    if (!vattuFile.is_open()) {
        cerr << "Loi! Khong the mo file VatTu.bin!" << endl;
        return;
    }

    VatTu vattu;
    Kho kho;
    int stt = 1;
    int tongSoluong = 0;

    ofstream maVTFile((maVT + string(".txt")).c_str(), ios::app);
    if (!maVTFile.is_open()) {
        cerr << "Loi! Khong the tao file cho khach hang " <<  maVT << endl;
        return;
    }

    cout << "Danh sach cac kho chua vat tu MaVT " << maVT << ":\n";
    cout << "STT\tTenkho\t\tDiachi\t\tSoluong\t\tDongia\t\tThanhtien\n";
    maVTFile << "Danh sach cac kho chua vat tu MaVT " << maVT << ":\n";
    maVTFile << "STT\tTenkho\t\tDiachi\t\tSoluong\t\tDongia\t\tThanhtien\n";

    while (vattuFile.read((char*)&vattu, sizeof(VatTu))) {
        if (strcmp(vattu.maVT, maVT) == 0) {
            ifstream khoFile("Kho.bin", ios::binary);
            if (!khoFile.is_open()) {
                cerr << "Loi! Khong the mo file Kho.bin!" << endl;
                return;
            }

            while (khoFile.read((char*)&kho, sizeof(Kho))) {
                if (kho.maKho == vattu.maKho) {
                    cout << stt << "\t" << kho.tenKho << "\t\t" << kho.diaChi << "\t\t" << vattu.soLuong << "\t\t" << vattu.donGia << "\t\t" << vattu.thanhTien << endl;
                    maVTFile << stt << "\t" << kho.tenKho << "\t\t" << kho.diaChi << "\t\t" << vattu.soLuong << "\t\t" << vattu.donGia << "\t\t" << vattu.thanhTien << endl;
                    tongSoluong += vattu.soLuong;
                    break;
                }
            }
            khoFile.close();
            stt++;
        }
    }
    cout << "Tong so luong vat tu: " << tongSoluong << endl;
    maVTFile << "Tong so luong vat tu: " << tongSoluong << endl;
    maVTFile.close();
    vattuFile.close();
}

int main() {
    int luaChon;

    do {
        // Hiển thị menu
        cout << "\nMENU:" << endl;
        cout << "1. Nhap thong tin kho" << endl;
        cout << "2. Nhap thong tin vat tu" << endl;
        cout << "3. Ghi thong tin vat tu theo ma vat tu" << endl;
        cout << "0. Thoat" << endl;
        cout << "Lua chon cua ban: ";
        cin >> luaChon;

        // Xử lý các tùy chọn từ menu
        switch (luaChon) {
            case 1:
                nhapKho();
                break;
            case 2:
                nhapVatTu();
                break;
            case 3:
                ghiVatTuTheoMaVT();
                break;
            case 0:
                cout << "Tam biet!";
                break;
            default:
                cout << "Lua chon khong hop le!";
                break;
        }
    } while (luaChon != 0);

    return 0;
}


