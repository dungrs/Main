#include <iostream>
#include <fstream>
#include <string>
#include <cstring>

using namespace std;

struct HangHoa {
    int MaHH;
    char TenHH[50];
    char NhaSX[50];
    int DonGia;
};

struct HoaDon {
    int MaHH;
    char MaKhach[6];
    int Soluong;
    int Ngaymua;
    int Thangmua;
    int Thanhtien;
};

void NhapHangHoa() {
    HangHoa h;
    cout << "Nhap MaHH: "; cin >> h.MaHH;
    cin.ignore();
    cout << "Nhap TenHH: "; cin.getline(h.TenHH, 50);
    cout << "Nhap NhaSX: "; cin.getline(h.NhaSX, 50);
    cout << "Nhap DonGia: "; cin >> h.DonGia;
    ofstream("HangHoa.bin", ios::binary | ios::app).write((char*)&h, sizeof(HangHoa));
    cout << "Hang hoa da duoc them vao file HangHoa.bin" << endl;
}

void NhapHoaDon() {
    HoaDon hd;
    cout << "Nhap MaHH: "; cin >> hd.MaHH;
    cout << "Nhap MaKhach: "; cin >> hd.MaKhach;
    cout << "Nhap Soluong: "; cin >> hd.Soluong;
    cout << "Nhap Ngaymua: "; cin >> hd.Ngaymua;
    cout << "Nhap Thangmua: "; cin >> hd.Thangmua;

    ifstream file("HangHoa.bin", ios::binary);
    HangHoa h;
    while (file.read((char*)&h, sizeof(HangHoa)))
        if (h.MaHH == hd.MaHH) { hd.Thanhtien = hd.Soluong * h.DonGia; break; }
    file.close();

    ofstream("HoaDon.bin", ios::binary | ios::app).write((char*)&hd, sizeof(HoaDon));
    cout << "Hoa don da duoc them vao file HoaDon.bin" << endl;
}

void TinhTongTien() {
    char MaKhach[6];
    cout << "Nhap MaKhach: "; cin >> MaKhach;

    ifstream hdFile("HoaDon.bin", ios::binary);
    HoaDon hd;
    HangHoa h;
    int stt = 1, tongTien = 0;

    ofstream khachFile((string(MaKhach) + ".txt").c_str());
    khachFile << "STT\tTenHH\t\t\tSoLuong\tDonGia\tThanhTien" << endl;
    cout << "STT\tTenHH\t\t\tSoLuong\tDonGia\tThanhTien" << endl;

    while (hdFile.read((char*)&hd, sizeof(HoaDon)))
        if (strcmp(hd.MaKhach, MaKhach) == 0) {
            ifstream hFile("HangHoa.bin", ios::binary);
            while (hFile.read((char*)&h, sizeof(HangHoa)))
                if (h.MaHH == hd.MaHH) {
                    cout << stt << "\t" << h.TenHH << "\t\t\t" << hd.Soluong << "\t" << h.DonGia << "\t" << hd.Thanhtien << endl;
                    khachFile << stt << "\t" << h.TenHH << "\t\t\t" << hd.Soluong << "\t" << h.DonGia << "\t" << hd.Thanhtien << endl;
                    tongTien += hd.Thanhtien;
                    break;
                }
            hFile.close();
            stt++;
        }
    khachFile << "Tong tien: " << tongTien << endl;
    cout << "Tong tien: " << tongTien << endl;
    hdFile.close();
    khachFile.close();
}

int main() {
    int luaChon;
    do {
        cout << "\nMENU:\n1. Nhap hang hoa\n2. Nhap hoa don\n3. Tinh tong tien cho mot khach hang\n0. Thoat\nLua chon cua ban: ";
        cin >> luaChon;
        switch (luaChon) {
            case 1: NhapHangHoa(); break;
            case 2: NhapHoaDon(); break;
            case 3: TinhTongTien(); break;
            case 0: cout << "Tam biet!"; break;
            default: cout << "Lua chon khong hop le!"; break;
        }
    } while (luaChon != 0);
    return 0;
}
