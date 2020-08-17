// ParalelÖdev.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <chrono>

using namespace std;



struct table
{
	int s1;
	int s2;
	double score;
};

double minx = 10000;
double minscore = 0;
table scores[20];
int index = 0;
void add(int s1, int s2, int i, int j, double score);

#pragma omp_set_num_threads(4);
//#pragma  omp_set_dynamic(0); //Kendi karar vermeden 4 thread kullanmasýný zorlamak istediðimizde açarýz.

int main()
{
	string array[15000]; //Bir dosyada max 15000 sekans
	string line, filename;
	int loop = 0;
	int i, j, k;
	int doubleorfloat;


	cout << "Skorlar float olarak islensin istiyorsaniz 1 giriniz. (Default double)" << endl;
	cin >> doubleorfloat;

	if (doubleorfloat == 1)
	{
		float score = 0;

		//inFile.open("5K_Sequence.fasta");

		ifstream inFile;

		cout << "Hangi dosyayi acmak istersiniz?(Örnek 5K_Sequence.fasta ya da 10K, 15K ..)" << endl;
		cin >> filename;

		inFile.open(filename.c_str());


		if (!inFile.good()) { //Dosyayý açma da hata varsa error mesajý
			cerr << "Dosya açýlamadý." << endl;
			return -1;
		}

		auto start = chrono::steady_clock::now();


		while (!inFile.eof()) //Dosyanýn sonuna eriþilmediyse
		{
			getline(inFile, line); //Dosyadan bir satýr al
			if (!line.empty() && line[0] != '>') //Sadece sekanslarý almamýzý saðlar
			{
				array[loop] = line;
				//cout << array[loop] << endl << endl; //and output it
				loop++;
			}
		}

		for (i = 0; i < loop - 1; i++)
		{
			for (j = i + 1; j <= loop - 1; j++)
			{
//#pragma omp parallel for shared(k)			//Critical konsa bile output sýrasýna zarar veriyor.
				for (k = 1; k <= 200; k++) // i sekansý ile j sekansýný karþýlaþtýrýr.
				{
					#pragma omp critical
					{
						if (array[i].at(k) == ' ' || array[j].at(k) == ' ')
							score += 0;
						else if (array[i].at(k) == '-' || array[j].at(k) == '-')
							score += -1.832482334;
						else if (array[i].at(k) == array[j].at(k))
							score += 3.621354295;
						else if (array[i].at(k) != array[j].at(k))
							score += -2.451795405;
					}
				}
				add(i, j, i, j, score);
				//cout << j << "score" << ' ' << score << endl;
				score = 0;
			}
		}

		for (int i = 0; i < 20; i++)
		{
			for (int j = i + 1; j < 20; j++)
			{
				int temp, temp2; double tempscore;
				if (scores[i].score < scores[j].score)
				{
					tempscore = scores[i].score; temp = scores[i].s1; temp2 = scores[i].s2;
					scores[i].score = scores[j].score; scores[i].s1 = scores[j].s1; scores[i].s2 = scores[j].s2;
					scores[j].score = tempscore; scores[j].s1 = temp; scores[j].s2 = temp2;
				}
			}
		}

		auto end = chrono::steady_clock::now();
		auto timex = chrono::duration_cast<chrono::seconds>(end - start).count();

		for (i = 0; i < 20; i++)
			cout << scores[i].s1 << "    " << scores[i].s2 << "   skor:     " << scores[i].score << endl;
		cout << timex << " saniyede sonlandi" << endl;
		inFile.close();
	}

	else
	{
		double score = 0;

		//inFile.open("5K_Sequence.fasta");

		ifstream inFile;

		cout << "Hangi dosyayi acmak istersiniz?(Örnek 5K_Sequence.fasta ya da 10K, 15K ..)" << endl;
		cin >> filename;

		inFile.open(filename.c_str());


		if (!inFile.good()) { //Dosyayý açma da hata varsa error mesajý
			cerr << "Dosya açýlamadý." << endl;
			return -1;
		}

		auto start = chrono::steady_clock::now();

		while (!inFile.eof()) //Dosyanýn sonuna eriþilmediyse
		{
			getline(inFile, line); //Dosyadan bir satýr al
			if (!line.empty() && line[0] != '>') //Sadece sekanslarý almamýzý saðlar
			{
				array[loop] = line;
				//cout << array[loop] << endl << endl; //and output it
				loop++;
			}
		}


		for (i = 0; i < loop - 1; i++)
		{
			for (j = i + 1; j <= loop - 1; j++)
			{
//#pragma omp parallel for shared(k)			//Critical konsa bile output sýrasýna zarar veriyor.
				for (k = 1; k <= 200; k++) // i sekansý ile j sekansýný karþýlaþtýrýr.
				{
					#pragma omp critical
					{
						if (array[i].at(k) == ' ' || array[j].at(k) == ' ')
							score += 0;
						else if (array[i].at(k) == '-' || array[j].at(k) == '-')
							score += -1.832482334;
						else if (array[i].at(k) == array[j].at(k))
							score += 3.621354295;
						else if (array[i].at(k) != array[j].at(k))
							score += -2.451795405;
					}
				}

				add(i, j, i, j, score);
				//cout << j << "score" << ' ' << score << endl;
				score = 0;
			}
		}

		for (int i = 0; i < 20; i++)
		{
			for (int j = i + 1; j < 20; j++)
			{
				int temp, temp2; double tempscore;
				if (scores[i].score < scores[j].score)
				{
					tempscore = scores[i].score; temp = scores[i].s1; temp2 = scores[i].s2;
					scores[i].score = scores[j].score; scores[i].s1 = scores[j].s1; scores[i].s2 = scores[j].s2;
					scores[j].score = tempscore; scores[j].s1 = temp; scores[j].s2 = temp2;
				}
			}
		}

		auto end = chrono::steady_clock::now();
		auto timex = chrono::duration_cast<chrono::seconds>(end - start).count();

		for (i = 0; i < 20; i++)
			cout << scores[i].s1 << "    " << scores[i].s2 << "   skor:     " << scores[i].score << endl;
		cout << timex << " saniyede sonlandi" << endl;
		inFile.close();
	}
	return 0;
}

void add(int s1, int s2, int i, int j, double score)
{

	if (score > minscore && index < 20)
	{
		if (score < minx)
		{
			minx = score;
		}
		scores[index].s1 = s1;
		scores[index].s2 = s2;
		scores[index].score = score;
		index += 1;
	}
	else
	{
		if (score > minx)
		{
#pragma omp parallel for
			for (int i = 0; i < 20; i++)
			{
				if (scores[i].score == minx)
				{
					scores[i].s1 = s1;
					scores[i].s2 = s2;
					scores[i].score = score;
				}
			}
		}
#pragma omp parallel for
		for (int i = 0; i < 20; i++)
		{
			for (int j = 0; j < 20; j++)
			{
				if (scores[j].score < scores[i].score && scores[i].score != scores[j].score)
					minx = scores[j].score;
			}
		}
	}
}
