#include <iostream>
#include <vector>
using namespace std;


int chay(vector<int>& frame, int soframe, vector<int> page, int buocNow, vector<int>& time) {
	int i;
	int pageNow = page[buocNow];
	int idlelong = 0;
	int pageidle;
	//Check Page hit 
	for (i = 0; i < soframe; i++) {
		//check page co trong frame chua
		if (pageNow == frame[i]) {
			time[i] = buocNow;
			cout << " Page hit tai buoc: " << buocNow << " voi so page la " << pageNow << endl;
			return 0;
		}
	}
	// check frame trong
	for (i = 0; i < soframe; i++) {
		if (frame[i] == -1) {
			frame[i] = pageNow;
			time[i] = buocNow;
			cout << " Page fault tai buoc: " << buocNow << " voi so page la " << pageNow << " va thay the frame " << i << " trong" << endl;
			return 0;
		}
	}
	//thuat toan LRU
	// set thoi gian nho nhat
	int min = time[0];
	// tim ra page idle lau nhat va
	for (i = 0; i < soframe; i++) {
		if (time[i] < min) {
			min = time[i];
			pageidle = i;
		}
	}
	idlelong = frame[pageidle];
	frame[pageidle] = pageNow;
	time[pageidle] = buocNow;
	//thay the page idle bang page moi va cap nhat time cua page
	cout << " Page fault tai buoc: " << buocNow << " voi so page fault la " << pageNow << " va page bi thay la " << idlelong << endl;
	return 0;
}
int main() {
	int i, buocNow;
	int soframe, sopage;
	cout << "Nhap so frame: ";
	cin >> soframe;
	cout << "Nhap so chuoi trang ( cung la so buoc truy cap): ";
	cin >> sopage;
	//Khai bao vector  
	vector<int> frame(soframe, -1);
	vector<int> page(sopage, -1);
	vector<int> time(soframe, 0);
	//Check dieu kien frame,page va step
	if (soframe < 1) {
		cout << "So frame phai lon hon 0";
		return 0;
	}
	//Nhap va xuat chuoi trang
	for (i = 0; i < sopage; i++) {
		cout << "Nhap trang thu " << i << " : ";
		cin >> page[i];
	}
	cout << "\n Chuoi trang vua nhap la: ";
	for (i = 0;i < sopage;i++) {
		cout << page[i] << " ";
	}
	cout << endl;
	//Xu ly tung buoc 
	for (i = 0;i < sopage; i++) {
		buocNow = i;
		chay(frame, soframe, page, buocNow, time);
	}
}
