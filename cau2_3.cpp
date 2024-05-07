#include <iostream>
#include <string>
#include <fstream>
#include <cstring>

using namespace std;

struct Sach {
    int MaSach;
    char TenSach[50];
    char NhaXB[50];
    float GiaBia;
};

struct Muon {
    int MaSach;
    char MaBanDoc[6];
    int NgayMuon;
    int ThangMuon;
    float TienCoc;
};

void NhapSach() {
    Sach sach;
    cout << "Nhap MaSach: ";
    cin >> sach.MaSach;
    cout << "Nhap TenSach: ";
    cin.ignore();
    cin.getline(sach.TenSach, 50);
    cout << "Nhap NhaXB: ";
    cin.getline(sach.NhaXB, 50);
    cout << "Nhap GiaBia: ";
    cin >> sach.GiaBia;
    
    ofstream file("Sach.bin", ios::binary | ios::app);
    if (!file.is_open()) {
        cerr << "Loi! Khong the mo file Sach.bin!" << endl;
        return;
    }

    file.write((char*)&sach, sizeof(Sach));
    file.close();
    cout << "Sach da duoc them vao file Sach.bin" << endl;
    cout << "_____________________________________________" << endl;
}

void NhapMuon() {
    Muon muon;
    cout << "Nhap MaSach: ";
    cin >> muon.MaSach;
    cout << "Nhap MaBanDoc: ";
    cin >> muon.MaBanDoc;
    cout << "Nhap NgayMuon: ";
    cin >> muon.NgayMuon;
    cout << "Nhap ThangMuon: ";
    cin >> muon.ThangMuon;

    // Tinh tien coc
    ifstream sachFile("Sach.bin", ios::binary);
    if (!sachFile.is_open()) {
        cerr << "Loi! Khong the mo file Sach.bin" << endl;
        return;
    }

    Sach sach;
    float tienCoc = 0;
    
    while (sachFile.read((char*)&sach, sizeof(Sach))) {
        if (sach.MaSach == muon.MaSach) {
            tienCoc = 0.4 * sach.GiaBia;
        }
    }

    sachFile.close();
    muon.TienCoc = tienCoc;
    
    ofstream file("Muon.bin", ios::binary | ios::app);
    if (!file.is_open()) {
        cerr << "Loi! Khong the mo file Muon.bin" << endl;
        return;
    }

    file.write((char*)&muon, sizeof(Muon));
    file.close();
    cout << "Thong tin muon sach da duoc them vao file Muon.bin" << endl;
    cout << "_____________________________________________" << endl;
}

void TinhTienCoc() {
    char MaBanDoc[6]; 
    cout << "Nhap MaBanDoc: ";
    cin >> MaBanDoc;

    ifstream muonFile("Muon.bin", ios::binary);
    if (!muonFile.is_open()) {
        cerr << "Loi! Khong the mo file Muon.bin" << endl;
        return;
    }

    Muon muon;
    Sach sach;
    float tongTienCoc = 0;
    int stt = 1;

    ofstream khachHangFile((MaBanDoc + string(".txt")).c_str(), ios::app);
    if (!khachHangFile.is_open()) {
        cerr << "Loi! Khong the tao file cho khach hang " << MaBanDoc << endl;
        return;
    }

    cout << "STT\tTenSach\t\tNgayMuon\tThangMuon\tTienCoc\t\tGiaBia" << endl;
    khachHangFile << "STT\tTenSach\t\tNgayMuon\tThangMuon\tTienCoc\t\tGiaBia" << endl;
    while (muonFile.read((char*)&muon, sizeof(Muon))) {
        if (strcmp(muon.MaBanDoc, MaBanDoc) == 0) {
            ifstream sachFile("Sach.bin", ios::binary);
            if (!sachFile.is_open()) {
                cerr << "Loi! Khong the mo file Sach.bin" << endl;
                return;
            }

            while (sachFile.read((char*)&sach, sizeof(Sach))) {
                if (sach.MaSach == muon.MaSach) {
                    cout << stt << "\t" << sach.TenSach << "\t\t" << muon.NgayMuon << "\t\t" << muon.ThangMuon << "\t\t" << muon.TienCoc << "\t\t" << sach.GiaBia << endl;
                    khachHangFile << stt << "\t" << sach.TenSach << "\t\t" << muon.NgayMuon << "\t\t" << muon.ThangMuon << "\t\t" << muon.TienCoc << "\t\t" << sach.GiaBia << endl;
                    tongTienCoc += muon.TienCoc;
                    break;
                }
            }
            sachFile.close();
            stt++;
        }
    }

    cout << "Tong tien coc: " << tongTienCoc << endl;
    khachHangFile << "Tong tien coc: " << tongTienCoc << endl;

    khachHangFile.close();
    muonFile.close();
}

int main() {
    int luaChon;

    do {
        // Hiển thị menu
        cout << "MENU:" << endl;
        cout << "1. Nhap sach" << endl;
        cout << "2. Nhap thong tin muon sach" << endl;
        cout << "3. Tinh tien coc" << endl;
        cout << "0. Thoat" << endl;
        cout << "Lua chon cua ban: ";
        cin >> luaChon;

        // Xử lý các tùy chọn từ menu
        switch (luaChon) {
            case 1:
                NhapSach();
                break;
            case 2:
                NhapMuon();
                break;
            case 3:
                TinhTienCoc();
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
