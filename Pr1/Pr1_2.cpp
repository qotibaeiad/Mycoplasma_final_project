#ifndef _INC_Pr1_2
#define _INC_Pr1_2

#include "Pr1.h"

vector<ListFasta> Prim1::GetFileListFasta(string fileName)
{
	vector<ListFasta> dna_mas;
	ListFasta lf;
	char a;
	char buf[1000];
	int i;
	ifstream myfile(fileName);
	if (!myfile.is_open())
		cout << "Unable to open file";

	myfile >> a;
	while (!myfile.eof())
	{
		if (a != '>') continue;
		lf.header = "";
		lf.dna = "";
		myfile.getline(buf, 1000);
		lf.header = buf;
		while (!myfile.eof())
		{
			myfile >> a;
			if (a != '>')
				lf.dna += a;
			else break;
		}

		dna_mas.push_back(lf);
	}
	myfile.close();

	fileName = "list1_c";
	ofstream outfile(fileName);
	for (i = 0; i < dna_mas.size(); i++)
	{
		outfile << i << ")" << dna_mas[i].header << "\n" << dna_mas[i].dna << "\n";
	}

	outfile.close();
	return dna_mas;
}

void  Prim1::find_words_read_in_mp1_glob(string fileName, int prsz1)
{
	ListFasta lf;
	char a;
	char buf[1000];
	int i;
	ifstream myfile(fileName);
	if (!myfile.is_open())
		cout << "Unable to open file";

	fileName = "DNA_c";
	ofstream outfile(fileName);

	myfile >> a;
	while (!myfile.eof())
	{
		if (a != '>') continue;
		lf.header = "";
		lf.dna = "";
		myfile.getline(buf, 1000);
		lf.header = buf;

		cout << lf.header << endl;

		while (!myfile.eof())
		{
			myfile >> a;
			if (a != '>')
				lf.dna += toupper(a);
			else break;
		}

		find_words_in_mp1_glob(lf.dna, prsz1);
		outfile << "\n>" << lf.header << "\n" << lf.dna << "\n";
	}
	myfile.close();
	outfile.close();
}

void Prim1::read_map1(string fileName)
{
//	cerr << "t1";
	Prim_in_map pim;
	map_list1.clear();
	char a;
	int i;
	ifstream myfile(fileName);
	if (!myfile.is_open())
		cout << "Unable to open file";
//	cerr << "t2";
	while (!myfile.eof())
	{
		myfile >> i;
		myfile >> a;
		pim.seq = "";
		while (!myfile.eof())
		{
			myfile >> a;
			if (a != ',')
				pim.seq += a;
			else
			{
				myfile >> pim.num;
				map_list1.push_back(pim);
			//	cerr << "\n"<<i<<" "<< pim.seq<<" "<< pim.num<<" "<< map_list1.size();
				break;
			}

		}
	}
	myfile.close();

//	cin >> i;

	fileName = "map_list1_c";
	ofstream outfile(fileName);
	for (i = 0; i < map_list1.size(); i++)
	{
		outfile << i << "," << map_list1[i].seq << ", " << map_list1[i].num << "\n";
	}

	outfile.close();
}


#endif  // _INC_Pr1_2
