/*****************************
**    Otel Yönetim Programı
**    @author:Hakan ERYÜCEL 
******************************/
#include <iostream>
#include <fstream>
#include <string>
#include <ctype.h>
#include <cstdlib>
#include <locale.h>

using namespace std;

class otelim {
private:
	string odaNo;
	string ucret;
	string musteri;

	string ad;
	string soyad;
	string TC;
	string musteriNo;
	string oda;

	char tus;
public:

	otelim()
	{
		musteri = "yok";
		oda = "yok";
	}


	void odaEkle()
	{
		string tmpNokt, tmpNokt2, tmpNo, pause,tmpUcret;
		int sayac = 0, kontrol = 0;
		ifstream dosyaOku;
		ofstream dosyaYaz;

		do
		{
			kontrol = 0;
			dosyaYaz.open("Odalar.csv", ios::app);
			dosyaOku.open("Odalar.csv");
			sayac = 0;
			system("cls");
			cout << "Eklenecek odanın bilgilerini giriniz." << endl;
			for (;;)    //Girilenlerin rakamlardan oluştuğunu kontrol eden döngü.
			{
				cout << "Oda numarası = ";cin >> tmpNo;
				for (int i = 0;i < tmpNo.length();i++)
				{
					if (!isdigit(tmpNo[i]))
					{
						kontrol++;
					}
				}
				if (kontrol != 0)
				{
					system("cls");
					cout << "Yanlış tuşlama yaptınız. Oda numarası sadece rakamlardan oluşmalıdır.\nDevam etmek için bir tuş giriniz.";cin >> pause;
					kontrol = 0;tus = 'e';system("cls");
				}
				else
					break;
			}
			for (;;)    //Girilenlerin rakamlardan oluştuğunu kontrol eden döngü.
			{
				cout << endl << "Oda ücreti = ";cin >> tmpUcret;
				for (int i = 0;i < tmpUcret.length();i++)
				{
					if (!isdigit(tmpUcret[i]))
					{
						kontrol++;
					}
				}
				if (kontrol != 0)
				{
					system("cls");
					cout << "Yanlış tuşlama yaptınız. Ücret sadece rakamlardan oluşmalıdır.\nDevam etmek için bir tuş giriniz.";cin >> pause;
					kontrol = 0;tus = 'e';system("cls");
				}
				else
					break;
			}
			while (dosyaOku >> odaNo >> tmpNokt >> ucret >> tmpNokt2 >> musteri)
			{
				if (tmpNo == odaNo)
					sayac++;
			}
			if (sayac == 0)
			{
				dosyaYaz << tmpNo << " " << ";" << " " << tmpUcret << " " << ";" << " " << musteri << endl;
				for (;;)
				{
					system("cls");
					cout << "Oda ekleme işlemi başarılı.\Başka bir oda eklemek istiyor musunuz ? (e/h)";cin >> tus;

					if (tus != 'e' && tus != 'E' && tus != 'h' && tus != 'H')
					{
						system("cls");
						cout << "Yanlış seçim yaptınız." << endl << "Devam etmek için bir tuş giriniz.";cin >> pause;
					}
					else
						break;
				}
			}
			else
			{
				for (;;)    //Aynı oda numarası verilmesini engeller.
				{
					system("cls");
					cout << "Oda ekleme işlemi başarısız.Oynı oda numarası olan başka bir oda var.\nFarklı bir oda eklemek istiyor musunuz ? (e/h)";cin >> tus;

					if (tus != 'e' && tus != 'E' && tus != 'h' && tus != 'H')
					{
						system("cls");
						cout << "Yanlış seçim yaptınız." << endl << "Devam etmek için bir tuş giriniz.";cin >> pause;
					}
					else
						break;
				}
			}

			dosyaYaz.close();dosyaOku.close();
			musteri = "yok";
			oda = "yok";
		} while (tus != 'h'&&tus != 'H');

	}
	void odaSil()
	{
		int sayac = 0, kontrol = 0, sayac2 = 0;
		string tmpNo, tmpNokt, tmpNokt2, pause;
		ifstream dosyaOku;ofstream dosyaYaz;
		do
		{
			sayac = 0;kontrol = 0;sayac2 = 0;
			system("cls");
			cout << "Silinecek odanın bilgilerini giriniz." << endl;
			cout << "Oda numarası = ";cin >> tmpNo;
			for (int i = 0;i < tmpNo.length();i++)    //Girilenleri kontrol eden döngü.
			{
				if (!isdigit(tmpNo[i]))
				{
					kontrol++;
				}
			}
			if (kontrol != 0)
			{
				system("cls");
				cout << "Yanlış tuşlama yaptınız. Oda numarası sadece rakamlardan oluşmalıdır.\nDevam etmek için bir tuş giriniz.";cin >> pause;
				tus = 'e';kontrol = 0;continue;
			}

			dosyaOku.open("Odalar.csv");
			dosyaYaz.open("OdalarTmp.csv", ios::app);
			while (dosyaOku >> odaNo >> tmpNokt >> ucret >> tmpNokt2 >> musteri)    //Girilen no lu müşteriyi silen döngü.
			{
				if (tmpNo == odaNo&&musteri != "yok")    //Müşterinin rezervasyonu kontrol edilir.
				{
					dosyaYaz << odaNo << " " << ";" << " " << ucret << " " << ";" << " " << musteri << endl;
					sayac2++;
				}
				if (tmpNo == odaNo)
					sayac++;
				if (tmpNo != odaNo)
					dosyaYaz << odaNo << " " << ";" << " " << ucret << " " << ";" << " " << musteri << endl;
			}
			dosyaOku.close();dosyaYaz.close();
			remove("Odalar.csv");rename("OdalarTmp.csv", "Odalar.csv");
			if (sayac == 0)
			{
				for (;;)
				{
					system("cls");
					cout << "Silmek istediğiniz oda numaralı bir oda bulunmamaktadır.\nBaşka oda silmek istiyor musunuz ? (e/h)";cin >> tus;

					if (tus != 'e' && tus != 'E' && tus != 'h' && tus != 'H')
					{
						system("cls");
						cout << "Yanlış seçim yaptınız." << endl << "Devam etmek için bir tuş giriniz.";cin >> pause;
					}
					else
						break;

				}
				sayac = 0;continue;
			}

			if (sayac2 != 0)
			{
				for (;;)
				{
					system("cls");
					cout << "Silmek istediğiniz odada bir müşteri bulunmaktadır.Lütfen ilk önce rezervasyonunu siliniz.\nBaşka oda silmek istiyor musunuz ? (e/h)";cin >> tus;

					if (tus != 'e' && tus != 'E' && tus != 'h' && tus != 'H')
					{
						system("cls");
						cout << "Yanlış seçim yaptınız." << endl << "Devam etmek için bir tuş giriniz.";cin >> pause;
					}
					else
						break;

				}
				sayac = 0;continue;
			}

			for (;;)
			{
				system("cls");
				cout << "Oda silme işlemi başarılı.\nBaşka oda silmek istiyor musunuz ? (e/h)";cin >> tus;

				if (tus != 'e' && tus != 'E' && tus != 'h' && tus != 'H')
				{
					system("cls");
					cout << "Yanlış seçim yaptınız." << endl << "Devam etmek için bir tuş giriniz.";cin >> pause;
				}
				else
					break;
			}
			musteri = "yok";
			oda = "yok";
		} while (tus != 'h' && tus != 'H');
	}
	void odaListele()
	{
		int sayac = 0;
		string tmpNokt, tmpNokt2;
		system("cls");
		ifstream dosyaOku;
		dosyaOku.open("Odalar.csv");
		while (dosyaOku >> odaNo >> tmpNokt >> ucret >> tmpNokt2 >> musteri)    //Tüm odalar sırayla yazdırılır.
		{
			sayac++;
			cout << "Oda no = " << odaNo << endl << "Oda ücreti = " << ucret << endl;
			if (musteri != "yok")
				cout << "Odada " << musteri << " no'lu müşteri kalmaktadır." << endl << "============================================================" << endl;
			else
				cout << "Odada müşteri " << musteri << "tur." << endl << "============================================================" << endl;
		}
		dosyaOku.close();
		if (sayac == 0)
			cout << endl << "Hiç odanız bulunmamaktadır.";
		cout << endl << endl << "Devam etmek için bir tuş giriniz.";cin >> tmpNokt;sayac = 0;
	}
	void musteriEkle()
	{
		string pause, tmpNokt, tmpNokt2, tmpNokt3, tmpNokt4, tmpNo, tmpMusteriNo, tmpTC,tmpAd,tmpSoyad;int sayac = 0, sayac2 = 0, sayac3 = 0, kontrol = 0;
		ofstream dosyaYaz;ifstream dosyaOku;

		do
		{
			sayac = 0;sayac2 = 0;sayac3 = 0,kontrol=0;
			dosyaOku.open("Musteriler.csv");
			dosyaYaz.open("Musteriler.csv", ios::app);
			system("cls");
			cout << "Eklenecek müşterinin bilgilerini giriniz." << endl;
			for (;;)    //Girilenleri kontrol eder.
			{
				cout << "Ad = ";cin >> tmpAd;
				for (int i = 0;i < tmpAd.length();i++)
				{
					if (!isalpha(tmpAd[i]))
					{
						kontrol++;
					}
				}
				if (kontrol != 0)
				{
					system("cls");
					cout << "Yanlış tuşlama yaptınız. Ad sadece harflerden oluşmalıdır ve Türkçe karakter içermemelidir.\nDevam etmek için bir tuş giriniz.";cin >> pause;
					kontrol = 0;tus = 'e';system("cls");
				}
				else
					break;
			}
			for (;;)    //Girilenleri kontrol eder.
			{
				cout << endl << "Soyad = ";cin >> tmpSoyad;
				for (int i = 0;i < tmpSoyad.length();i++)
				{
					if (!isalpha(tmpSoyad[i]))
					{
						kontrol++;
					}
				}
				if (kontrol != 0)
				{
					system("cls");
					cout << "Yanlış tuşlama yaptınız. Soyad sadece harflerden oluşmalıdır ve Türkçe karakter içermemelidir.\nDevam etmek için bir tuş giriniz.";cin >> pause;
					kontrol = 0;tus = 'e';system("cls");
				}
				else
					break;
			}
			for (;;)    //Girilenleri kontrol eder.
			{
				cout << endl << "Tc kimlik numarası = ";cin >> tmpTC;
				for (int i = 0;i < tmpTC.length();i++)
				{
					if (!isdigit(tmpTC[i]))
					{
						kontrol++;
					}
				}
				if (kontrol != 0)
				{
					system("cls");
					cout << "Yanlış tuşlama yaptınız. Tc kimlik numarası sadece rakamlardan oluşmalıdır.\nDevam etmek için bir tuş giriniz.";cin >> pause;
					kontrol = 0;tus = 'e';system("cls");continue;
				}
				if (tmpTC.length() != 11)
				{
					system("cls");
					cout << "Yanlış tuşlama yaptınız. Tc kimlik numarası 11 haneli olmalıdır.\nDevam etmek için bir tuş giriniz.";cin >> pause;
					tus = 'e';system("cls");continue;
				}
				break;
			}
			for (;;)    //Girilenleri kontrol eder.
			{
				cout << endl << "Müşteri numarası = ";cin >> tmpMusteriNo;
				for (int i = 0;i < tmpMusteriNo.length();i++)
				{
					if (!isdigit(tmpMusteriNo[i]))
					{
						kontrol++;
					}
				}
				if (kontrol != 0)
				{
					system("cls");
					cout << "Yanlış tuşlama yaptınız. Müşteri numarası sadece rakamlardan oluşmalıdır.\nDevam etmek için bir tuş giriniz.";cin >> pause;
					kontrol = 0;tus = 'e';system("cls");continue;
				}
				break;
			}

			while (dosyaOku >> ad >> tmpNokt >> soyad >> tmpNokt2 >> TC >> tmpNokt3 >> musteriNo >> tmpNokt4 >> oda)
			{
				if (tmpMusteriNo == musteriNo || tmpTC == TC)    //Aynı bilgilere sahip müşteri olmasını engeller.
					sayac++;
				if (tmpMusteriNo == musteriNo)    //Aynı müşteri numarası olmasını engeller.
					sayac2++;
				if (tmpTC == TC)    //Aynı TC olmasını engeller.
					sayac3++;
			}
			if (sayac == 0)
			{
				dosyaYaz << tmpAd << " " << ";" << " " << tmpSoyad << " " << ";" << " " << tmpTC << " " << ";" << " " << tmpMusteriNo << " " << ";" << " " << oda << endl;
				for (;;)
				{
					system("cls");
					cout << "Müşteri başarıyla eklendi.\nYeni müşteri eklemek istiyor musunuz ? (e/h)";cin >> tus;

					if (tus != 'e' && tus != 'E' && tus != 'h' && tus != 'H')
					{
						system("cls");
						cout << "Yanlış seçim yaptınız." << endl << "Devam etmek için bir tuş giriniz.";cin >> pause;
					}
					else
						break;
				}
			}
			else if (sayac2 != 0)
			{
				for (;;)
				{
					system("cls");
					cout << "Müşteri ekleme işlemi başarısız.Aynı müşteri numarasına sahip bir müşteri daha var.\nFarklı bir müşteri eklemek istiyor musunuz ? (e/h)";cin >> tus;

					if (tus != 'e' && tus != 'E' && tus != 'h' && tus != 'H')
					{
						system("cls");
						cout << "Yanlış seçim yaptınız." << endl << "Devam etmek için bir tuş giriniz.";cin >> pause;
					}
					else
						break;
				}
			}
			else if (sayac3 != 0)
			{
				for (;;)
				{
					system("cls");
					cout << "Müşteri ekleme işlemi başarısız.Aynı tc kimlik numarasına sahip bir müşteri daha var.\nFarklı bir müşteri eklemek istiyor musunuz ? (e/h)";cin >> tus;

					if (tus != 'e' && tus != 'E' && tus != 'h' && tus != 'H')
					{
						system("cls");
						cout << "Yanlış seçim yaptınız." << endl << "Devam etmek için bir tuş giriniz.";cin >> pause;
					}
					else
						break;
				}
			}

			dosyaYaz.close();dosyaOku.close();
			musteri = "yok";
			oda = "yok";
		} while (tus != 'h'&&tus != 'H');

	}
	void musteriSil()
	{
		int sayac = 0,sayac2=0;
		string tmpNo, pause, tmpNokt, tmpNokt2, tmpNokt3, tmpNokt4;
		ifstream dosyaOku;ofstream dosyaYaz;
		do
		{
			sayac = 0;sayac2 = 0;
			dosyaOku.open("Musteriler.csv");
			dosyaYaz.open("MusterilerTmp.csv", ios::app);
			system("cls");
			cout << "Silinecek müşterinin bilgilerini giriniz." << endl;
			cout << "Müşteri numarası = ";cin >> tmpNo;
			while (dosyaOku >> ad >> tmpNokt >> soyad >> tmpNokt2 >> TC >> tmpNokt3 >> musteriNo >> tmpNokt4 >> oda)
			{
				if (tmpNo == musteriNo&&oda != "yok")    //Müşterinin rezervasyonunu kontrol eder.
				{
					dosyaYaz << ad << " " << ";" << " " << soyad << " " << ";" << " " << TC << " " << ";" << " " << musteriNo << " " << ";" << " " << oda << endl;
					sayac2++;
				}
				if (tmpNo == musteriNo)    //Girilen numarada müşteri olup olmadığı kontrol edilir.
					sayac++;
				if (tmpNo != musteriNo)
					dosyaYaz << ad << " " << ";" << " " << soyad << " " << ";" << " " << TC << " " << ";" << " " << musteriNo << " " << ";" << " " << oda << endl;
			}
			dosyaOku.close();dosyaYaz.close();
			remove("Musteriler.csv");rename("MusterilerTmp.csv", "Musteriler.csv");
			if (sayac == 0)
			{
				for (;;)
				{
					system("cls");
					cout << "Silmek istediğiniz müşteri numaralı bir müşteri bulunmamaktadır.\nBaşka bir müşteri silmek istiyor musunuz ? (e/h)";cin >> tus;

					if (tus != 'e' && tus != 'E' && tus != 'h' && tus != 'H')
					{
						system("cls");
						cout << "Yanlış seçim yaptınız." << endl << "Devam etmek için bir tuş giriniz.";cin >> pause;
					}
					else
						break;

				}
				continue;
			}

			if (sayac2 != 0)
			{
				for (;;)
				{
					system("cls");
					cout << "Silmek istediğiniz müşteri bir odada kalmaktadır.Lütfen ilk önce rezervasyonunu siliniz.\nBaşka bir müşteri silmek istiyor musunuz ? (e/h)";cin >> tus;

					if (tus != 'e' && tus != 'E' && tus != 'h' && tus != 'H')
					{
						system("cls");
						cout << "Yanlış seçim yaptınız." << endl << "Devam etmek için bir tuş giriniz.";cin >> pause;
					}
					else
						break;

				}
				continue;
			}

			for (;;)
			{
				system("cls");
				cout << "Müşteri silme işlemi başarılı.\nBaşka müşteri silmek istiyor musunuz ? (e/h)";cin >> tus;

				if (tus != 'e' && tus != 'E' && tus != 'h' && tus != 'H')
				{
					system("cls");
					cout << "Yanlış seçim yaptınız." << endl << "Devam etmek için bir tuş giriniz.";cin >> pause;
				}
				else
					break;
			}
			musteri = "yok";
			oda = "yok";
		} while (tus != 'h' && tus != 'H');
	}
	void musteriListele()
	{
		string tmpNokt, tmpNokt2, tmpNokt3, tmpNokt4;int sayac = 0;
		system("cls");
		ifstream dosyaOku;
		dosyaOku.open("Musteriler.csv");
		while (dosyaOku >> ad >> tmpNokt >> soyad >> tmpNokt2 >> TC >> tmpNokt3 >> musteriNo >> tmpNokt4 >> oda)    //Müşterileri sırayla listeler.
		{
			sayac++;
			cout << "Ad = " << ad << endl << "Soyad = " << soyad << endl << "Tc kimlik no  = " << TC << endl << "Müşteri numarası = " << musteriNo << endl;
			if (oda != "yok")
				cout << "Müşteri " << oda << " no'lu odada kalmaktadır." << endl << "============================================================" << endl;
			else
				cout << "Müşterinin odası " << oda << "tur." << endl << "============================================================" << endl;
		}
		dosyaOku.close();
		if (sayac == 0)
			cout << endl << "Hiç müşteriniz bulunmamaktadır.";
		cout << endl << endl << "Devam etmek için bir tuş giriniz.";cin >> tmpNokt;sayac = 0;
	}
	void rezervEkle()
	{
		int sayac = 0, sayac2 = 0, sayac3 = 0, sayac4 = 0;
		string pause, tmpOda, tmpMusteri, tmpNokt, tmpNokt2, tmpNokt3, tmpNokt4;
		ifstream dosyaOku;
		ofstream dosyaYaz;

		do
		{
			sayac = 0;sayac2 = 0, sayac3 = 0;sayac4 = 0;
			system("cls");
			cout << "Rezervasyon yapmak için bilgileri giriniz\n" << endl;
			cout << "Müşteriye vermek istediğiniz oda numarası = ";cin >> tmpOda;
			dosyaOku.open("Odalar.csv");
			while (dosyaOku >> odaNo >> tmpNokt >> ucret >> tmpNokt2 >> musteri)
			{
				if (tmpOda == odaNo)    //Odanın dolu bir oda olmasını engeller.
				{
					sayac2++;
					if (musteri != "yok")
						sayac3++;
				}
			}
			dosyaOku.close();
			if (sayac2 == 0)
			{
				for (;;)
				{
					system("cls");
					cout << "Rezerve etmek istediğiniz oda numaralı bir oda bulunmamaktadır.\nBaşka oda rezerve etmek istiyor musunuz ? (e/h)";cin >> tus;

					if (tus != 'e' && tus != 'E' && tus != 'h' && tus != 'H')
					{
						system("cls");
						cout << "Yanlış seçim yaptınız." << endl << "Devam etmek için bir tuş giriniz.";cin >> pause;
					}
					else
						break;

				}
				continue;
			}
			if (sayac3 != 0)
			{
				for (;;)
				{
					system("cls");
					cout << "Rezerve etmek istediğiniz odada başka bir müşteri bulunmaktadır.\nBaşka oda rezerve etmek istiyor musunuz ? (e/h)";cin >> tus;

					if (tus != 'e' && tus != 'E' && tus != 'h' && tus != 'H')
					{
						system("cls");
						cout << "Yanlış seçim yaptınız." << endl << "Devam etmek için bir tuş giriniz.";cin >> pause;
					}
					else
						break;
				}
				continue;
			}

			cout << endl << "Müşteri numarası = " << endl;cin >> tmpMusteri;

			dosyaOku.open("Musteriler.csv");
			while (dosyaOku >> ad >> tmpNokt >> soyad >> tmpNokt2 >> TC >> tmpNokt3 >> musteriNo >> tmpNokt4 >> oda)
			{

				if (tmpMusteri == musteriNo)    //Müşterinin önceden odasının olmasını engeller.
				{
					sayac++;
					if (oda != "yok")
						sayac4++;
				}
			}
			dosyaOku.close();
			if (sayac == 0)
			{
				for (;;)
				{
					system("cls");
					cout << "Girdiğiniz müşteri numarasına sahip bir müşteri bulunmamaktadır.\nBaşka bir müşteriye oda rezerve etmek istiyor musunuz ? (e/h)";cin >> tus;

					if (tus != 'e' && tus != 'E' && tus != 'h' && tus != 'H')
					{
						system("cls");
						cout << "Yanlış seçim yaptınız." << endl << "Devam etmek için bir tuş giriniz.";cin >> pause;
					}
					else
						break;

				}
				continue;
			}
			if (sayac4 != 0)
			{
				for (;;)
				{
					system("cls");
					cout << "Girdiğiniz müşteri numarasına sahip müşteri başka bir odada bulunmaktadır.\nBaşka bir müşteriye oda rezerve etmek istiyor musunuz ? (e/h)";cin >> tus;

					if (tus != 'e' && tus != 'E' && tus != 'h' && tus != 'H')
					{
						system("cls");
						cout << "Yanlış seçim yaptınız." << endl << "Devam etmek için bir tuş giriniz.";cin >> pause;
					}
					else
						break;

				}
				continue;
			}


			if (sayac == 1 && sayac2 == 1)
			{
				dosyaYaz.open("MusterilerTmp.csv", ios::app);
				dosyaOku.open("Musteriler.csv");
				while (dosyaOku >> ad >> tmpNokt >> soyad >> tmpNokt2 >> TC >> tmpNokt3 >> musteriNo >> tmpNokt4 >> oda)    //Rezervasyonları kaydeder.
				{
					if (tmpMusteri == musteriNo)
						dosyaYaz << ad << " " << ";" << " " << soyad << " " << ";" << " " << TC << " " << ";" << " " << musteriNo << " " << ";" << " " << tmpOda << endl;
					else
						dosyaYaz << ad << " " << ";" << " " << soyad << " " << ";" << " " << TC << " " << ";" << " " << musteriNo << " " << ";" << " " << oda << endl;
				}
				dosyaOku.close();dosyaYaz.close();
				remove("Musteriler.csv");rename("MusterilerTmp.csv", "Musteriler.csv");
				dosyaOku.open("Odalar.csv");dosyaYaz.open("OdalarTmp.csv", ios::app);
				while (dosyaOku >> odaNo >> tmpNokt >> ucret >> tmpNokt2 >> musteri)
				{
					if (tmpOda == odaNo)
						dosyaYaz << odaNo << " " << ";" << " " << ucret << " " << ";" << " " << tmpMusteri << endl;
					else
						dosyaYaz << odaNo << " " << ";" << " " << ucret << " " << ";" << " " << musteri << endl;
				}
				dosyaOku.close();dosyaYaz.close();
				remove("Odalar.csv");rename("OdalarTmp.csv", "Odalar.csv");
			}
			if (sayac == 1 && sayac2 == 1)
			{
				dosyaYaz.open("Rezervasyonlar.csv", ios::app);
				dosyaYaz << tmpOda << " " << ";" << " " << tmpMusteri << endl;
				dosyaYaz.close();
			}

			for (;;)
			{
				system("cls");
				cout << "Rezervasyon işlemi başarılı.\nBaşka rezervasyon yapmak istiyor musunuz ? (e/h)";cin >> tus;

				if (tus != 'e' && tus != 'E' && tus != 'h' && tus != 'H')
				{
					system("cls");
					cout << "Yanlış seçim yaptınız." << endl << "Devam etmek için bir tuş giriniz.";cin >> pause;
				}
				else
					break;
			}
			musteri = "yok";
			oda = "yok";
		} while (tus != 'h'&&tus != 'H');
	}
	void rezervSil()
	{
		int sayac = 0, sayac2 = 0, sayac3 = 0, sayac4 = 0;
		string pause, tmpOda, tmpMusteri, tmpNokt, tmpNokt2, tmpNokt3, tmpNokt4;
		ifstream dosyaOku;
		ofstream dosyaYaz;

		do
		{
			sayac = 0; sayac2 = 0;sayac3 = 0;sayac4 = 0;
			system("cls");
			cout << "Rezervasyonunu silmek iştediğiniz müşterinin müşteri numarası = ";cin >> tmpMusteri;
			dosyaOku.open("Musteriler.csv");
			while (dosyaOku >> ad >> tmpNokt >> soyad >> tmpNokt2 >> TC >> tmpNokt3 >> musteriNo >> tmpNokt4 >> oda)
			{
				if (tmpMusteri == musteriNo)    //Girilen numaralı müşterinin olup olmadığını kontrol eder.Ve rezervasyonunu kontrol eder.
				{
					sayac++;tmpOda = oda;
					if (oda == "yok")
						sayac3++;
				}
			}
			dosyaOku.close();
			if (sayac == 0)
			{
				for (;;)
				{
					system("cls");
					cout << "Girdiğiniz müşteri numarasına sahip bir müşteri bulunmamaktadır.\nBaşka bir müşterinin rezervasyonunu silmek istiyor musunuz ? (e/h)";cin >> tus;

					if (tus != 'e' && tus != 'E' && tus != 'h' && tus != 'H')
					{
						system("cls");
						cout << "Yanlış seçim yaptınız." << endl << "Devam etmek için bir tuş giriniz.";cin >> pause;
					}
					else
						break;

				}
				continue;
			}
			if (sayac3 != 0)
			{
				for (;;)
				{
					system("cls");
					cout << "Girdiğiniz müşteri numarasına sahip müşterinin odası bulunmamaktadır.\nBaşka bir müşterinin rezervasyonunu silmek istiyor musunuz ? (e/h)";cin >> tus;

					if (tus != 'e' && tus != 'E' && tus != 'h' && tus != 'H')
					{
						system("cls");
						cout << "Yanlış seçim yaptınız." << endl << "Devam etmek için bir tuş giriniz.";cin >> pause;
					}
					else
						break;
				}
				continue;
			}

			dosyaYaz.open("tmpRezervasyonlar.csv", ios::app);
			dosyaOku.open("Rezervasyonlar.csv");
			while (dosyaOku >> odaNo >> tmpNokt >> musteriNo)    //Rezervasyonları sırayla kaydeder.
			{
				if (tmpMusteri != musteriNo)
					dosyaYaz << odaNo << " " << ";" << " " << musteriNo << endl;
			}
			dosyaOku.close();dosyaYaz.close();
			remove("Rezervasyonlar.csv");rename("tmpRezervasyonlar.csv", "Rezervasyonlar.csv");

			dosyaOku.open("Musteriler.csv");
			dosyaYaz.open("MusterilerTmp.csv", ios::app);
			while (dosyaOku >> ad >> tmpNokt >> soyad >> tmpNokt2 >> TC >> tmpNokt3 >> musteriNo >> tmpNokt4 >> oda)    //Müşterinin odasını silerek kaydeder.
			{
				if (tmpMusteri != musteriNo)
					dosyaYaz << ad << " " << ";" << " " << soyad << " " << ";" << " " << TC << " " << ";" << " " << musteriNo << " " << ";" << " " << oda << endl;
				else
					dosyaYaz << ad << " " << ";" << " " << soyad << " " << ";" << " " << TC << " " << ";" << " " << musteriNo << " " << ";" << " " << "yok" << endl;
			}
			dosyaOku.close();dosyaYaz.close();
			remove("Musteriler.csv");rename("MusterilerTmp.csv", "Musteriler.csv");

			dosyaOku.open("Odalar.csv");dosyaYaz.open("OdalarTmp.csv", ios::app);
			while (dosyaOku >> odaNo >> tmpNokt >> ucret >> tmpNokt2 >> musteri)    //Odadaki müşteriyi silip kaydeder.
			{
				if (tmpOda != odaNo)
					dosyaYaz << odaNo << " " << ";" << " " << ucret << " " << ";" << " " << musteri << endl;
				else
					dosyaYaz << odaNo << " " << ";" << " " << ucret << " " << ";" << " " << "yok" << endl;
			}
			dosyaOku.close();dosyaYaz.close();
			remove("Odalar.csv");rename("OdalarTmp.csv", "Odalar.csv");

			for (;;)
			{
				system("cls");
				cout << "Rezervasyon silme işlemi başarılı.\nBaşka rezervasyon silmek istiyor musunuz ? (e/h)";cin >> tus;

				if (tus != 'e' && tus != 'E' && tus != 'h' && tus != 'H')
				{
					system("cls");
					cout << "Yanlış seçim yaptınız." << endl << "Devam etmek için bir tuş giriniz.";cin >> pause;
				}
				else
					break;
			}
			musteri = "yok";
			oda = "yok";
		} while (tus != 'h'&&tus != 'H');
	}
	void rezervListele()
	{
		string tmpNokt, tmpNokt2;int sayac = 0;
		system("cls");
		ifstream dosyaOku;
		dosyaOku.open("Rezervasyonlar.csv");
		while (dosyaOku >> odaNo >> tmpNokt >> musteriNo)    //Rezervasyonları sırayla listeler.
		{
			cout << odaNo << " no'lu odada " << musteriNo << " no'lu müşteri kalmaktadır." << endl << "============================================================" << endl;
			sayac++;
		}
		dosyaOku.close();
		if (sayac == 0)
			cout << endl << "Hiç rezervasyon bulunmamaktadır.";
		cout << endl << endl << "Devam etmek için bir tuş giriniz.";cin >> tmpNokt;
	}
};


int main() {
	setlocale(LC_ALL, "Turkish");
	system("color 0A");
	int secim;char pause;string tmpSecim;
	otelim otel;
	do {     //Ana menü döngüsü.99 a basılana kadar devam edecek.
		system("cls");
		cout << "Otel işlemleri" << endl << "============================================================" << endl << endl;
		cout << "1. Oda işlemleri" << endl << "2. Müşteri işlemleri" << endl << "3. Oda-kayıt işlemleri" << endl << "99. Çıkış" << endl << "Lütfen seçiminizi yapınız = ";
		cin >> tmpSecim;
		if (tmpSecim != "1" && tmpSecim != "2" && tmpSecim != "3" && tmpSecim != "99")
		{
			system("cls");
			cout << "Hatalı seçim yaptınız.\n Lütfen ana menüye dönmek için bir tuş giriniz.";
			cin >> tmpSecim;
			continue;
		};
		secim = stoi(tmpSecim);
		switch (secim)
		{
		case 1:

			do
			{    //Ara menü döngüsü.99 a basılana kadar devam edecek.
				system("cls");
				cout << "Oda işlemleri" << endl << "============================================================" << endl << endl;
				cout << "1. Oda ekle" << endl << "2. Oda sil" << endl << "3. Odaları listele" << endl << "99. Üst menü" << endl << "Lütfen seçiminizi yapınız = ";
				cin >> tmpSecim;
				if (tmpSecim != "1" && tmpSecim != "2" && tmpSecim != "3" && tmpSecim != "99")
				{
					system("cls");
					cout << "Hatalı seçim yaptınız.\n Lütfen üst menüye dönmek için bir tuş giriniz.";
					cin >> tmpSecim;
					secim = 1;
					continue;
				};
				secim = stoi(tmpSecim);
				switch (secim)
				{
				case 1:
					otel.odaEkle();break;
				case 2:
					otel.odaSil();break;
				case 3:
					otel.odaListele();break;
				}
			} while (secim != 99);
			secim = 1;break;

		case 2:

			do
			{    //Ara menü döngüsü. 99 a basılana kadar devam edecek.
				system("cls");
				cout << "Müşteri işlemleri" << endl << "============================================================" << endl << endl;
				cout << "1. Müşteri ekle" << endl << "2. Müşteri sil" << endl << "3. Müşterileri listele" << endl << "99. Üst menü" << endl << "Lütfen seçiminizi yapınız = ";
				cin >> tmpSecim;
				if (tmpSecim != "1" && tmpSecim != "2" && tmpSecim != "3" && tmpSecim != "99")
				{
					system("cls");
					cout << "Hatalı seçim yaptınız.\n Lütfen üst menüye dönmek için bir tuş giriniz.";
					cin >> tmpSecim;
					secim = 1;
					continue;
				};
				secim = stoi(tmpSecim);
				switch (secim)
				{
				case 1:
					otel.musteriEkle();break;
				case 2:
					otel.musteriSil();break;
				case 3:
					otel.musteriListele();break;
				}
			} while (secim != 99);
			secim = 1;break;

		case 3:
			do
			{    //Ara menü döngüsü. 99 a basılana kadar devam edecek.
				system("cls");
				cout << "Oda-kayıt işlemleri" << endl << "============================================================" << endl << endl;
				cout << "1. Rezervasyon ekle" << endl << "2. Rezervasyon sil" << endl << "3. Rezervasyonları listele" << endl << "99. Üst menü" << endl << "Lütfen seçiminizi yapınız = ";
				cin >> tmpSecim;
				if (tmpSecim != "1" && tmpSecim != "2" && tmpSecim != "3" && tmpSecim != "99")
				{
					system("cls");
					cout << "Hatalı seçim yaptınız.\n Lütfen üst menüye dönmek için bir tuş giriniz.";
					cin >> tmpSecim;
					secim = 1;
					continue;
				};
				secim = stoi(tmpSecim);
				switch (secim)
				{
				case 1:
					otel.rezervEkle();break;
				case 2:
					otel.rezervSil();break;
				case 3:
					otel.rezervListele();break;
				}
			} while (secim != 99);
			secim = 1;break;
		}
	} while (secim != 99);
	return 0;
}