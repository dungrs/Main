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
    HangHoa hanghoa;
    cout << "Nhap MaHH: ";
    cin >> hanghoa.MaHH;
    cout << "Nhap TenHH: ";
    cin.ignore();
    cin.getline(hanghoa.TenHH, 50);
    cout << "Nhap NhaSX: ";
    cin.getline(hanghoa.NhaSX, 50);
    cout << "Nhap DonGia: ";
    cin >> hanghoa.DonGia;

    ofstream file("HangHoa.bin", ios::binary | ios::app);
    if (!file.is_open()) {
        cerr << "Loi! Khong the mo file HangHoa.bin" << endl;
        return;
    }
    file.write((char*)&hanghoa, sizeof(HangHoa));
    file.close();
    cout << "Hang hoa da duoc them vao file HangHoa.bin" << endl;
    cout << "_____________________________________________" << endl;
}

void NhapHoaDon() {
    HoaDon hoadon;
    cout << "Nhap MaHH: ";
    cin >> hoadon.MaHH;
    cout << "Nhap MaKhach: ";
    cin >> hoadon.MaKhach;
    cout << "Nhap Soluong: ";
    cin >> hoadon.Soluong;
    cout << "Nhap Ngaymua: ";
    cin >> hoadon.Ngaymua;
    cout << "Nhap Thangmua: ";
    cin >> hoadon.Thangmua;

    ifstream hanghoaFile("HangHoa.bin", ios::binary);
    if (!hanghoaFile.is_open()) {
        cerr << "Loi! Khong the mo file HangHoa.bin" << endl;
        return;
    }
    HangHoa hanghoa;
    int thanhtien = 0;
    while (hanghoaFile.read((char*)&hanghoa, sizeof(HangHoa))) {
        if (hanghoa.MaHH == hoadon.MaHH) {
            thanhtien = hoadon.Soluong * hanghoa.DonGia;
            break;
        }
    }
    hanghoaFile.close();

    hoadon.Thanhtien = thanhtien;

    ofstream file("HoaDon.bin", ios::binary | ios::app);
    if (!file.is_open()) {
        cerr << "Loi! Khong the mo file HoaDon.bin" << endl;
        return;
    }
    file.write((char*)&hoadon, sizeof(HoaDon));
    file.close();
    cout << "Hoa don da duoc them vao file HoaDon.bin" << endl;
    cout << "_____________________________________________" << endl;
}

void TinhTongTien() {
    char MaKhach[6];
    cout << "Nhap MaKhach: ";
    cin >> MaKhach;

    ifstream hoadonFile("HoaDon.bin", ios::binary);
    if (!hoadonFile.is_open()) {
        cerr << "Loi! Khong the mo file HoaDon.bin" << endl;
        return;
    }
    HoaDon hoadon;
    HangHoa hanghoa;
    int stt = 1;
    int tongTien = 0;

    // đoạn này hơi khó hiểu, sẽ giải thích sau!
    ofstream khachHangFile((MaKhach + string(".txt")).c_str(), ios::app);
    if (!khachHangFile.is_open()) {
        cerr << "Loi! Khong the tao file cho khach hang " << MaKhach << endl;
        return;
    }

    khachHangFile << "STT\tTenHH\t\t\tSoLuong\tDonGia\tThanhTien" << endl;
    cout << "STT\tTenHH\t\t\tSoLuong\tDonGia\tThanhTien" << endl;
    while (hoadonFile.read((char*)&hoadon, sizeof(HoaDon))) {
        // Hàm strcmp đươc sử dụng để so sánh 2 chuỗi kí tự
        // Giá trị âm nếu chuỗi thứ nhất (str1) nhỏ hơn chuỗi thứ hai (str2).
        // Giá trị dương nếu chuỗi thứ nhất (str1) lớn hơn chuỗi thứ hai (str2).
        // Giá trị 0 nếu hai chuỗi bằng nhau.
        if (strcmp(hoadon.MaKhach, MaKhach) == 0) {
            ifstream hanghoaFile("HangHoa.bin", ios::binary);
            if (!hanghoaFile.is_open()) {
                cerr << "Loi! Khong the mo file HangHoa.bin" << endl;
                return;
            }
            
            while (hanghoaFile.read((char*)&hanghoa, sizeof(HangHoa))) {
                if (hanghoa.MaHH == hoadon.MaHH) {
                    cout << stt << "\t" << hanghoa.TenHH << "\t\t\t" << hoadon.Soluong << "\t" << hanghoa.DonGia << "\t" << hoadon.Thanhtien << endl;
                    khachHangFile << stt << "\t" << hanghoa.TenHH << "\t\t\t" << hoadon.Soluong << "\t" << hanghoa.DonGia << "\t" << hoadon.Thanhtien << endl;
                    tongTien += hoadon.Thanhtien;
                    break;
                }
            }
            hanghoaFile.close();
            stt++;
        }
    }
    khachHangFile << "Tong tien: " << tongTien << endl;
    cout << "Tong tien: " << tongTien << endl;
    
    khachHangFile.close();
    hoadonFile.close();
}


int main() {
    int luaChon;

    do {
        // Hiển thị menu
        cout << "\nMENU:" << endl;
        cout << "1. Nhap hang hoa" << endl;
        cout << "2. Nhap hoa don" << endl;
        cout << "3. Tinh tong tien cho mot khach hang" << endl;
        cout << "0. Thoat" << endl;
        cout << "Lua chon cua ban: ";
        cin >> luaChon;

        // Xử lý các tùy chọn từ menu
        switch (luaChon) {
            case 1:
                NhapHangHoa();
                break;
            case 2:
                NhapHoaDon();
                break;
            case 3:
                TinhTongTien();
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
