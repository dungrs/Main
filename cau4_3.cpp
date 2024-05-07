#include <iostream>
#include <fstream>
#include <string>
#include <cstring>

using namespace std;

struct HSCB {
    char maCB[6];
    char tenCB[50];
    char boPhan[10];
};

struct TamUng {
    char maCB[6];
    int maCT;
    int ngayTU;
    int thangTU;
    int namTU;
    int soTien;
};

void nhapHSCB() {
    HSCB hscb;
    cout << "Nhap MaCB: ";
    cin >> hscb.maCB;
    cout << "Nhap TenCB: ";
    cin.ignore();
    cin.getline(hscb.tenCB, 50);
    cout << "Nhap Bophan: ";
    cin.getline(hscb.boPhan, 10);

    ofstream file("HSCB.bin", ios::binary | ios::app);
    if (!file.is_open()) {
        cerr << "Loi! Khong the mo file HSCB.bin!\n";
        return;
    }

    file.write((char*)&hscb, sizeof(HSCB));
    file.close();
    cout << "HSCB da duoc them vao file HSCB.bin!\n";
    cout << "___________________________________\n";
}

void nhapTamUng() {
    TamUng tamUng;
    cout << "Nhap MaCB: ";
    cin >> tamUng.maCB;
    cout << "Nhap MaCT: ";
    cin >> tamUng.maCT;
    cout << "Nhap NgayTU: ";
    cin >> tamUng.ngayTU;
    cout << "Nhap ThangTU: ";
    cin >> tamUng.thangTU;
    cout << "Nhap NamTU: ";
    cin >> tamUng.namTU;
    cout << "Nhap Sotien: ";
    cin >> tamUng.soTien;
    cin.ignore();

    ofstream file("TamUng.bin", ios::binary | ios::app);
    if (!file.is_open()) {
        cerr << "Loi! Khong the mo file TamUng.bin!\n";
        return;
    }

    file.write((char*)&tamUng, sizeof(TamUng));
    file.close();
    cout << "Chung tu tam ung da duoc them vao file TamUng.bin!\n";
    cout << "_________________________________________________!\n";
}

void ghiChungTuTheoMaCB() {
    char maCB[6];
    cout << "Nhap MaCB: ";
    cin >> maCB;

    ifstream tamUngFile("TamUng.bin", ios::binary);
    if (!tamUngFile.is_open()) {
        cerr << "Loi! Khong the mo file TamUng.bin!\n";
        return;
    }

    TamUng tamUng;
    HSCB hscb;
    int stt = 1;
    int tongTien = 0;

    ofstream maCBFile((maCB + string(".txt")).c_str(), ios::app);
    if (!maCBFile.is_open()) {
        cerr << "Loi! Khong the tao file cho khach hang " << maCB << endl;
        return;
    }

    cout << "Danh sach chung tu tam ung cua MaCB " << maCB << ":\n";
    cout << "STT\tTenCB\t\tNgayTU\t\tThangTU\t\tNamTU\t\tSotien\n";
    maCBFile << "Danh sach chung tu tam ung cua MaCB " << maCB << ":\n";
    maCBFile << "STT\tTenCB\t\tNgayTU\t\tThangTU\t\tNamTU\t\tSotien\n";

    while (tamUngFile.read((char*)&tamUng, sizeof(TamUng))) {
        if (strcmp(tamUng.maCB, maCB) == 0) {
            ifstream hscbFile("HSCB.bin", ios::binary);
            if (!hscbFile.is_open()) {
                cerr << "Loi! Khong the mo file HSCB.bin\n";
                tamUngFile.close();
                return;
            }

            while (hscbFile.read((char*)&hscb, sizeof(HSCB))) {
                if (strcmp(hscb.maCB, maCB) == 0) {
                    cout << stt << "\t" << hscb.tenCB << "\t\t" << tamUng.ngayTU << "\t\t" << tamUng.thangTU << "\t\t" << tamUng.namTU << "\t\t" << tamUng.soTien << endl;
                    maCBFile << stt << "\t" << hscb.tenCB << "\t\t" << tamUng.ngayTU << "\t\t" << tamUng.thangTU << "\t\t" << tamUng.namTU << "\t\t" << tamUng.soTien << endl;
                    break;
                }
            }

            hscbFile.close();

            tongTien += tamUng.soTien;
            stt++;
        }
    }
    cout << "Tong tien tam ung: " << tongTien << endl;
    maCBFile << "Tong tien tam ung: " << tongTien << endl;
    maCBFile.close();
    tamUngFile.close();
}



int main() {
    int luaChon;

    do {
        // Hiển thị menu
        cout << "\nMENU:" << endl;
        cout << "1. Nhap thong tin nhan vien" << endl;
        cout << "2. Nhap chung tu tam ung" << endl;
        cout << "3. Ghi chung tu theo ma nhan vien" << endl;
        cout << "0. Thoat" << endl;
        cout << "Lua chon cua ban: ";
        cin >> luaChon;

        // Xử lý các tùy chọn từ menu
        switch (luaChon) {
            case 1:
                nhapHSCB();
                break;
            case 2:
                nhapTamUng();
                break;
            case 3:
                ghiChungTuTheoMaCB();
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

