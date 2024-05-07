#include <iostream>
#include <string>
#include <fstream>
#include <cstring>

using namespace std;

struct MatHang {
    int maHang;
    char tenHang[50];
    char donViTinh[10];
    int donGia;
};

struct PhieuBH {
    char maNB[6];
    int maHang;
    int soLuong;
    int ngayBan;
    int thangBan;
    int namBan;
    int thanhTien;
};

void themMatHang() {
    MatHang matHang;
    cout << "Nhap MaHang: ";
    cin >> matHang.maHang;
    cout << "Nhap TenHang: ";
    cin.ignore();
    cin.getline(matHang.tenHang, 50);
    cout << "Nhap Donvitinh: ";
    cin.getline(matHang.donViTinh, 10);
    cout << "Nhap DonGia: ";
    cin >> matHang.donGia;
    cin.ignore();

    ofstream file("MatHang.bin", ios::binary | ios::app);
    if (!file.is_open()) {
        cerr << "Loi! Khong the mo file MatHang.bin!\n";
        return;
    }

    file.write((char*)&matHang, sizeof(MatHang));
    file.close();
    cout << "Mat hang da duoc them vao file MatHang.bin!\n";
    cout << "_____________________________________________\n";
}

void themPhieuBH() {
    PhieuBH phieuBH;
    cout << "Nhap MaNB: ";
    cin.getline(phieuBH.maNB, 6);
    cout << "Nhap MaHang: ";
    cin >> phieuBH.maHang;
    cout << "Nhap Soluong: ";
    cin >> phieuBH.soLuong;
    cout << "Nhap Ngayban: ";
    cin >> phieuBH.ngayBan;
    cout << "Nhap Thangban: ";
    cin >> phieuBH.thangBan;
    cout << "Nhap Namban: ";
    cin >> phieuBH.namBan;

    // Tinh thanh tien
    ifstream matHangFile("MatHang.bin", ios::binary);
    if (!matHangFile.is_open()) {
        cerr << "Loi! Khong the mo file MatHang.bin!\n";
        return;
    }

    MatHang matHang;
    int thanhtien = 0;
    while (matHangFile.read((char*)&matHang, sizeof(MatHang))) {
        if (matHang.maHang == phieuBH.maHang) {
            thanhtien = phieuBH.soLuong * matHang.donGia;
            break;
        }
    }

    matHangFile.close();
    phieuBH.thanhTien = thanhtien;

    ofstream file("PhieuBH.bin", ios::binary | ios::app);
    if (!file.is_open()) {
        cerr << "Loi! Khong the mo file PhieuBH.bin!\n";
        return;
    }

    file.write((char*)&phieuBH, sizeof(PhieuBH));
    file.close();
    cout << "Phieu ban hang da duoc them vao file PhieuBH.bin!\n";
    cout << "_____________________________________________\n";
}

void danhSachMatHangTheoMaNB() {
    char maNB[6];
    cout << "Nhap MaNB: ";
    cin >> maNB;

    ifstream phieuBHFile("PhieuBH.bin", ios::binary);
    if (!phieuBHFile.is_open()) {
        cerr << "Loi! Khong the mo file PhieuBH.bin\n";
        return;
    }

    MatHang matHang;
    PhieuBH phieuBH;
    int stt = 1;
    int tongTien = 0;

    ofstream maNBFile((maNB + string(".txt")).c_str(), ios::app);
    if (!maNBFile.is_open()) {
        cerr << "Loi! Khong the tao file cho khach hang " << maNB << endl;
        return;
    }

    cout << "Danh sach mat hang ban cua MaNB " << maNB << ":\n";
    cout << "STT\tTenHang\t\tSo luong\tDon gia\t\tThanh tien\n";
    maNBFile << "Danh sach mat hang ban cua MaNB " << maNB << ":\n";
    maNBFile << "STT\tTenHang\t\tSo luong\tDon gia\t\tThanh tien\n";

    while (phieuBHFile.read((char*)&phieuBH, sizeof(PhieuBH))) {
        if (strcmp(phieuBH.maNB, maNB) == 0) {
            ifstream matHangFile("MatHang.bin", ios::binary);
            if (!matHangFile.is_open()) {
                cerr << "Loi! Khong the mo file MatHang.bin";
                phieuBHFile.close();
                return;
            }

            while (matHangFile.read((char*)&matHang, sizeof(MatHang))) {
                if (matHang.maHang == phieuBH.maHang) {
                    tongTien += phieuBH.thanhTien;
                    cout << stt << "\t" << matHang.tenHang << "\t\t" << phieuBH.soLuong << "\t\t" << matHang.donGia << "\t\t" << phieuBH.thanhTien << endl;
                    maNBFile << stt << "\t" << matHang.tenHang << "\t\t" << phieuBH.soLuong << "\t\t" << matHang.donGia << "\t\t" << phieuBH.thanhTien << endl;
                    break;
                }
            }
            stt++;
            matHangFile.close();
        }
    }

    cout << "Tong tien ban duoc: " << tongTien << endl;
    maNBFile << "Tong tien ban duoc: " << tongTien << endl;
    phieuBHFile.close();
    maNBFile.close();
}

int main() {
    int luaChon;

    do {
        // Hiển thị menu
        cout << "MENU:" << endl;
        cout << "1. Them mat hang" << endl;
        cout << "2. Them phieu ban hang" << endl;
        cout << "3. Xem danh sach mat hang theo MaNB" << endl;
        cout << "0. Thoat" << endl;
        cout << "Lua chon cua ban: ";
        cin >> luaChon;

        // Xử lý các tùy chọn từ menu
        switch (luaChon) {
            case 1:
                themMatHang();
                break;
            case 2:
                themPhieuBH();
                break;
            case 3:
                danhSachMatHangTheoMaNB();
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