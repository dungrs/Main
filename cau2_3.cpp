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
    Sach s;
    cout << "Nhap MaSach: "; cin >> s.MaSach;
    cin.ignore();
    cout << "Nhap TenSach: "; cin.getline(s.TenSach, 50);
    cout << "Nhap NhaXB: "; cin.getline(s.NhaXB, 50);
    cout << "Nhap GiaBia: "; cin >> s.GiaBia;

    ofstream("Sach.bin", ios::binary | ios::app).write((char*)&s, sizeof(Sach));
    cout << "Sach da duoc them vao file Sach.bin" << endl;
}

void NhapMuon() {
    Muon m;
    cout << "Nhap MaSach: "; cin >> m.MaSach;
    cout << "Nhap MaBanDoc: "; cin >> m.MaBanDoc;
    cout << "Nhap NgayMuon: "; cin >> m.NgayMuon;
    cout << "Nhap ThangMuon: "; cin >> m.ThangMuon;

    ifstream sachFile("Sach.bin", ios::binary);
    Sach s;
    while (sachFile.read((char*)&s, sizeof(Sach)))
        if (s.MaSach == m.MaSach) { m.TienCoc = 0.4 * s.GiaBia; break; }
    sachFile.close();

    ofstream("Muon.bin", ios::binary | ios::app).write((char*)&m, sizeof(Muon));
    cout << "Thong tin muon sach da duoc them vao file Muon.bin" << endl;
}

void TinhTienCoc() {
    char MaBanDoc[6]; 
    cout << "Nhap MaBanDoc: "; cin >> MaBanDoc;

    ifstream muonFile("Muon.bin", ios::binary);
    Muon m;
    Sach s;
    float tongTienCoc = 0;
    int stt = 1;

    ofstream khachHangFile((string(MaBanDoc) + ".txt").c_str(), ios::app);
    cout << "STT\tTenSach\t\tNgayMuon\tThangMuon\tTienCoc\t\tGiaBia\n";
    khachHangFile << "STT\tTenSach\t\tNgayMuon\tThangMuon\tTienCoc\t\tGiaBia\n";

    while (muonFile.read((char*)&m, sizeof(Muon))) {
        if (strcmp(m.MaBanDoc, MaBanDoc) == 0) {
            ifstream sachFile("Sach.bin", ios::binary);
            while (sachFile.read((char*)&s, sizeof(Sach))) {
                if (s.MaSach == m.MaSach) {
                    cout << stt << "\t" << s.TenSach << "\t\t" << m.NgayMuon << "\t\t" << m.ThangMuon << "\t\t" << m.TienCoc << "\t\t" << s.GiaBia << endl;
                    khachHangFile << stt << "\t" << s.TenSach << "\t\t" << m.NgayMuon << "\t\t" << m.ThangMuon << "\t\t" << m.TienCoc << "\t\t" << s.GiaBia << endl;
                    tongTienCoc += m.TienCoc;
                    break;
                }
            }
            sachFile.close();
            stt++;
        }
    }

    cout << "Tong tien coc: " << tongTienCoc << endl;
    khachHangFile << "Tong tien coc: " << tongTienCoc << endl;
    muonFile.close();
    khachHangFile.close();
}

int main() {
    int luaChon;
    do {
        cout << "MENU:\n1. Nhap sach\n2. Nhap thong tin muon sach\n3. Tinh tien coc\n0. Thoat\nLua chon cua ban: ";
        cin >> luaChon;

        switch (luaChon) {
            case 1: NhapSach(); break;
            case 2: NhapMuon(); break;
            case 3: TinhTienCoc(); break;
            case 0: cout << "Tam biet!\n"; break;
            default: cout << "Lua chon khong hop le!\n"; break;
        }
    } while (luaChon != 0)
    return 0;
}
