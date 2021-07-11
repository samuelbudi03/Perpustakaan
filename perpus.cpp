#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;
typedef struct{
	string nama, namapenerbit, namapenulis;
	int tahun,kodebuku;
}buku;
ifstream inFile;
ofstream outFile;
buku ListBuku[100];
void panjang(int& count);
void input_data();
void output_data(int panjang);
void get_data(int panjang);
void pinjambuku();
void hapusbuku();
void pengembalian();
void sort();
void sortp();
void sortbykode(int panjang);
void sortbynama(int panjang);
void sortbypenerbit(int panjang);
void sortbypenulis(int panjang);
void sortbytahun(int panjang);

main(){
char pilihan,kembali;
system("cls");
cout<<"========================\n";
cout<<" Menu Utama Perpustakan\n";
cout<<"========================\n\n";
cout<<"1. Peminjaman\n";
cout<<"2. Pengembalian Buku\n";
cout<<"3. Input Buku\n";
cout<<"4. Hapus Buku dari Daftar\n";
cout<<"5. Informasi Peminjam Buku\n";
cout<<"6. Daftar Buku Tersedia\n";
cout<<"0. Keluar\n\n";
cout<<"Silahkan masukkan angka pada menu tersebut : ";cin>>pilihan;
system("cls");
switch (pilihan)//input menu yang diinginkan berdasarkan angka pada pilihan
	{
		case '1' :
			pinjambuku();
			//memanggil fungsi pinjam
			break;
		case '2' :
			pengembalian();
			//memanggil fungsi pengembalian
			break;
		case '3' :
			input_data();
			//memanggil fungsi input buku
			break;
		case '4' :
			hapusbuku();
			//memanggil fungsi hapus buku
			break;
		case '5' :
			sortp();
			//memanggil fungsi informasi peminjam buku
			break;
		case '6' :
			sort();
		    //memanggil fungsi informasi buku
		    break;
		case '0' :
			exit(0); //keluar dari program
			break;
		default :
			cout<<"\n Salah memasukkan angka.\n		";
			system("PAUSE");
			main();
	}
		cout<<"\nIngin kembali ke menu awal?(Y/N)";cin>>kembali;
		if(kembali=='Y'||kembali=='y') {system("cls");main();}
		else {exit(1);}
}
void input_data(){
	int banyak,pilih;
	string nama_file;
	cout<< endl;
	menu:
	cout<< "Ingin menambah buku atau menyusun ulang buku/membuat file baru?\n1.Tambah\n2.Susun Ulang/File baru\n";
	cout<<"Masukkan pilihan: ";cin>>pilih;
	if (pilih==1){
		cout <<"Masukkan Nama File  : "; cin >> nama_file;
		cout <<"Masukan banyak data : "; cin>> banyak;
		outFile.open(nama_file, ios::app);}
	else if (pilih==2){
		cout <<"Masukkan Nama File  : "; cin >> nama_file;
		cout <<"Masukan banyak data : "; cin>> banyak;
		outFile.open(nama_file, ios::out);}
	else{
		cout<<"\n Salah memasukkan angka.\n	";
		system("PAUSE");
		goto menu;}

	cout<< "Data Buku : \n";
	for (int a = 0; a < banyak; a++){
			cout<< "Kode Buku    : "; cin>>ListBuku[a].kodebuku;
			cout<< "Judul Buku   : "; cin.ignore(); getline(cin,ListBuku[a].nama);
			cout<< "Penerbit     : "; getline(cin,ListBuku[a].namapenerbit);
			cout<< "Penulis      : "; getline(cin,ListBuku[a].namapenulis);
			cout<< "Tahun Terbit : "; cin>> ListBuku[a].tahun;
			outFile <<ListBuku[a].kodebuku<<"\n"<<ListBuku[a].nama<<"\n" << ListBuku[a].namapenerbit<<"\n" << ListBuku[a].namapenulis<<"\n" << ListBuku[a].tahun<<endl;
		}
	outFile.close();		
}
void output_data(int panjang){
	cout<<"==========================================================================\n";
    cout<<" Kode     Nama                  Penerbit          Penulis           Tahun \n";
    cout<<"==========================================================================\n";
    for (int i = 0; i < panjang ; i++){
        cout <<left<<setw(10)<<ListBuku[i].kodebuku <<setw(22)<< ListBuku[i].nama <<setw(18)<< ListBuku[i].namapenerbit <<setw(18)<< ListBuku[i].namapenulis <<setw(5)<< ListBuku[i].tahun<<endl;
	}
    cout<<"==========================================================================\n";
}
void get_data(int panjang){
	inFile.clear();
	inFile.seekg(0);
    for (int i = 0; i < panjang; i++)
	{
        inFile >> ListBuku[i].kodebuku; inFile.ignore();
        getline(inFile, ListBuku[i].nama);
        getline(inFile, ListBuku[i].namapenerbit);
        getline(inFile,ListBuku[i].namapenulis);
		inFile >> ListBuku[i].tahun;
    }
}
void panjang(int& count){
	string line;
	while (getline(inFile, line)){
		count++;}
	count=count/5;
}
void pinjambuku(){
	ofstream pinjam;
	int kode, count=0;
	string nama,line; 
	bool found;
	cout<<"=================\n";
	cout<<"   Pinjam Buku \n";
	cout<<"=================\n";
	menu:
	cout<<"Masukkan nama file tempat buku ingin dipinjam: ";cin>>nama;
	inFile.open(nama.c_str(),ios::in);

	if (!inFile){
    cout << "Tidak ada file dengan nama tersebut di dalam direktori" << endl;
    system("PAUSE");
	inFile.close();
    goto menu;
    }

	panjang(count);
	get_data(count);
	output_data(count);
	inFile.close();

	pinjam.open("tmp.txt",ios::out);
	outFile.open("pinjam.txt",ios::app);
	cout<<"Buku yang ingin dipinjam. Masukkan kode buku: ";cin>>kode;
    for (int i = 0; i < count ; i++){
        if (kode == ListBuku[i].kodebuku){
            found = true;
				outFile<<ListBuku[i].kodebuku<<endl;
				outFile<<ListBuku[i].nama<<endl;
				outFile<<ListBuku[i].namapenerbit<<endl;
				outFile<<ListBuku[i].namapenulis <<endl;
				outFile<<ListBuku[i].tahun<<endl;
            }
		else{
			pinjam<<ListBuku[i].kodebuku<<endl;
			pinjam<<ListBuku[i].nama<<endl;
			pinjam<<ListBuku[i].namapenerbit<<endl;
			pinjam<<ListBuku[i].namapenulis <<endl;
			pinjam<<ListBuku[i].tahun<<endl;
			}
        }
    cout<<"==========================================================================\n";
	outFile.close();
	pinjam.close();
	if (!found){
			cout<<"Kode buku yang dimasukkan salah."; remove("pinjam.txt");
			remove("tmp.txt");
        }
	else if (found=true){
		remove(nama.c_str());
		rename("tmp.txt",nama.c_str());
	}
}

void hapusbuku(){
	cout<<"=================\n";
	cout<<"   Hapus Buku \n";
	cout<<"=================\n";
	int kode, count=0;
	bool found;
	string nama;
	menu:
	cout<<"Masukkan nama file tempat buku ingin dipinjam: ";cin>>nama;
	inFile.open(nama.c_str());

	if (!inFile){
    cout << "Tidak ada file dengan nama tersebut di dalam direktori" << endl;
    system("PAUSE");
	inFile.close();
    goto menu;
    }

	outFile.open("hapus.txt");
	panjang(count);
	get_data(count);
	output_data(count);
	inFile.close();
	cout<<"Buku yang ingin dihapus. Masukkan kode buku: ";cin>>kode;
	for (int i = 0; i < count; i++){
		if (kode != ListBuku[i].kodebuku){
			outFile<<ListBuku[i].kodebuku<<endl;
			outFile<<ListBuku[i].nama<<endl;
			outFile<<ListBuku[i].namapenerbit<<endl;
			outFile<<ListBuku[i].namapenulis <<endl;
			outFile<<ListBuku[i].tahun<<endl;
		}
		else{found=true;}
	}
	outFile.close();

	if (found=true){
		remove(nama.c_str());
		rename("hapus.txt",nama.c_str());
	}
	else{cout<<"Kode buku yang dimasukkan salah."; remove("hapus.txt");}
}

void pengembalian(){
	int kode, count=0;
	bool found;
	string nama;
	ofstream kembali;
	cout<<"=========================\n";
	cout<<"   Pengembalian Buku\n";
	cout<<"=========================\n";

	inFile.open("pinjam.txt");
	panjang(count);
	get_data(count);
	cout<<" Daftar Buku yang Dipinjam: \n";
	output_data(count);
	inFile.close();

	cout<<"Masukkan nama file tempat buku akan dikembalikan: ";cin>>nama;
	kembali.open(nama.c_str(), ios::app);
	outFile.open("kembali.txt");
	cout<<"Buku yang ingin dikembalikan. Masukkan kode buku: ";cin>>kode;
	for (int i = 0; i < count; i++){
		if (kode != ListBuku[i].kodebuku){
			outFile<<ListBuku[i].kodebuku<<endl;
			outFile<<ListBuku[i].nama<<endl;
			outFile<<ListBuku[i].namapenerbit<<endl;
			outFile<<ListBuku[i].namapenulis <<endl;
			outFile<<ListBuku[i].tahun<<endl;
		}
		else{found=true;
			kembali<<ListBuku[i].kodebuku<<endl;
			kembali<<ListBuku[i].nama<<endl;
			kembali<<ListBuku[i].namapenerbit<<endl;
			kembali<<ListBuku[i].namapenulis <<endl;
			kembali<<ListBuku[i].tahun<<endl;}
	}
	outFile.close();
	kembali.close();
	if (found=true){
		remove("pinjam.txt");
		rename("kembali.txt","pinjam.txt");
	}
	else{cout<<"Kode buku yang dimasukkan salah."; remove("kembali.txt");}
}

void sort(){
	int pilihan,count=0;
    char kembali,kembali2;
	string nama_file;
    menu:
    system("cls");
    cout<<"===================\n";
	cout<<"Sorting Berdasarkan\n";
	cout<<"===================\n";
    cout << "1. Nama\n2. Penerbit\n3. Penulis\n4. Kode Buku\n5. Tahun"<< endl;
    cout << "Masukkan Pilihan : "; cin >> pilihan;
	cout << "Masukkan Nama file : "; cin >> nama_file;
    inFile.open(nama_file.c_str());

	if (!inFile){
    cout << "Tidak ada file dengan nama tersebut di dalam direktori" << endl;
    system("PAUSE");
	inFile.close();
    goto menu;
    }

	panjang(count);
	cout<<count;
    get_data(count);
	output_data(count);
    inFile.close();

    switch (pilihan){
        case 1 : {
            system("cls");
            sortbynama(count);
            break;
        }case 2 : {
            system("cls");
            sortbypenerbit(count);
            break;
        }case 3 : {
            system("cls");
            sortbypenulis(count);
        break;
        }case 4 : {
            system("cls");
            sortbykode(count);
            break;
        }case 5 :{
            system("cls");
            sortbytahun(count);
            break;
        }default:
		cout<<"Salah memasukkan angka";
        system("PAUSE");
		goto menu;
    }
	output_data(count);
    cout<<"Ingin kembali ke menu sorting?(Y/N)";cin>>kembali;
	if (kembali=='Y'||kembali=='y'){
		goto menu;}
	else{
		cout<<"\nIngin kembali ke menu awal?(Y/N)";cin>>kembali2;
		if(kembali2=='Y'||kembali2=='y') {system("cls");main();}
		else {exit(1);}
		}
}

void sortp(){
	int pilihan,count=0;
    char kembali,kembali2;
    menu:
    system("cls");
    cout<<"=====================\n";
	cout<<" Sorting Data Pinjam\n";
	cout<<"=====================\n";
    cout << "1. Nama\n2. Penerbit\n3. Penulis\n4. Kode Buku\n5. Tahun"<< endl;
    cout << "Masukkan Pilihan "; cin >> pilihan;
    inFile.open("pinjam.txt");

	if (!inFile){
    cout << "Tidak ada file dengan nama tersebut di dalam direktori" << endl;
    system("PAUSE");
	inFile.close();
    goto menu;}

	panjang(count);
    get_data(count);
    inFile.close();

    switch (pilihan){
        case 1 : {
            system("cls");
            sortbynama(count);
            break;
        }case 2 : {
            system("cls");
            sortbypenerbit(count);
            break;
        }case 3 : {
            system("cls");
            sortbypenulis(count);
        break;
        }case 4 : {
            system("cls");
            sortbykode(count);
            break;
        }case 5 :{
            system("cls");
            sortbytahun(count);
            break;
        }default:
		cout<<"Salah memasukkan angka";
        system("PAUSE");
		goto menu;
    }
	output_data(count);
    cout<<"Ingin kembali ke menu sorting?(Y/N)";cin>>kembali;
	if (kembali=='Y'||kembali=='y'){
		goto menu;}
	else{
		cout<<"\nIngin kembali ke menu awal?(Y/N)";cin>>kembali2;
		if(kembali2=='Y'||kembali2=='y') {system("cls");main();}
		else {exit(1);}
		}
}

void sortbynama(int panjang){
	buku temp;
	for(int i = 0; i<panjang-1; i++){
		for(int j = 0; j<panjang-1-i; j++) {
		if(ListBuku[j].nama > ListBuku[j+1].nama){
			temp = ListBuku[j];
			ListBuku[j] = ListBuku[j+1];
			ListBuku[j+1] = temp;}
		}
	}
};
void sortbypenerbit(int panjang){
	buku temp;
	for(int i = 0; i<panjang-1; i++){
		for(int j = 0; j<panjang-1-i; j++) {
		if(ListBuku[j].namapenerbit > ListBuku[j+1].namapenerbit){
			temp = ListBuku[j];
			ListBuku[j] = ListBuku[j+1];
			ListBuku[j+1] = temp;}
		}
	}
};
void sortbypenulis(int panjang){
	buku temp;
	for(int current=0; current<panjang; current++)  
		{
			for(int j=current+1; j<panjang; j++)		 
			{
				if(ListBuku[current].namapenulis > ListBuku[j].namapenulis) {
				    temp = ListBuku[current];
				    ListBuku[current] = ListBuku[j];
				    ListBuku[j] = temp;
				}
			}
		}
};
void sortbytahun(int panjang){
	buku temp;
	int a, b;
	int temp2;
	for(a=1; a<panjang; a++){
		temp = ListBuku[a];
		temp2 = ListBuku[a].tahun;
		b = a - 1;
		while((temp2 < ListBuku[b].tahun) & (b >= 0))
		{
			ListBuku[b+1] = ListBuku[b];
			b = b - 1;
			ListBuku[b+1] = temp;
		}
	}				
};
void sortbykode(int panjang){
	int i, j, k;
	buku temp;
	for(k = panjang/2; k > 0; k /= 2){
		for(j = k; j < panjang; j++){
			for(i = j-k; i >= 0; i -= k){
			    if(ListBuku[i + k].kodebuku >= ListBuku[i].kodebuku)
			        break;
			    else{
			    	temp = ListBuku[i];
			        ListBuku[i] = ListBuku[i + k];
			        ListBuku[i + k] = temp;
			        }
			}
		}
	}
};
