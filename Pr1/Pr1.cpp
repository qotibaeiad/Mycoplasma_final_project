#include "Pr1.h"
//#include "Pr1_1.cpp"

int main(int argc, char* argv[]) 
{
	if (argc < 2) {
        cerr << "Error: No file path provided." << endl;
        return 1;
    }
	const char* file_path1 = argv[1];  // Use file_path1
	Prim1 pp;
	pp.conserv_calc();
	// cout << "Processing file: " << file_path1 << endl;  // Make sure to print this

	int i,j, prsz1 = 20;
	string pattern;
	const char *file_path = argv[1];
	 std::cout << "Processing file: " << file_path << std::endl;
    // printf("Processing file: %s\n", file_path);
	string path1 = "SEQs\\";
	string fname2, fname1 = path1 + "sc.fasta";
	
	string dna2, dna1 = GetFileFasta(fname1);
	pp.make_map1(dna1, prsz1);
	//cerr << "dnd" << dna;
	fname2 = "sc";
	ofstream outfile(fname2);
	outfile <<"dna "<< dna1.size()<< "\n" <<dna1;
	outfile.close();

	pair<map<string, int>::iterator, bool> ret;
	map<string, int>::iterator it;
	
//	fname2 = path1 + "\\s3.fasta";
//	dna2 = GetFileFasta(fname2);

	fname2 = path1 + "\\Maps\\1\\mp3_c_20";
	pp.read_map1(fname2);

	fname2 = "map_list1_c2";
	outfile.open(fname2);
	for (i = 0; i < pp.map_list1.size(); i++)
	{
		if (!pp.prim_filter1(pp.map_list1[i].seq)) pp.map_list1[i].num = -2;
		pp.map_list1[i].l = pp.prim_5_check(pp.map_list1[i].seq);
		pp.map_list1[i].r = pp.prim_3_check(pp.map_list1[i].seq);
		pp.map_list1[i].tm = pp.prime_Tm(pp.map_list1[i].seq);
		outfile << i << "," << pp.map_list1[i].seq << ", " << pp.map_list1[i].num << ", ";
		if (pp.map_list1[i].num == -1)
		{
			if (pp.map_list1[i].l)
				outfile << "l, ";
			if (pp.map_list1[i].r)
				outfile << "r, ";
		}
		outfile << pp.map_list1[i].tm <<"\n";

	}

	outfile.close();

	pp.select_pairs(dna1, prsz1);
	std::string result = "DNA processing complete"; // Replace with actual results
    std::cout << result << std::endl;
	return 0;

//	fname2 = "c2";
//	outfile.open(fname2);
//	outfile << "dna " << dna2.size() << "\n" << dna2;
//	outfile.close();
	pp.make_map1(dna1, prsz1);
//	find_words_in_map(mp1, dna2, prsz1);
//	vector <Prim_adr> pr_mas = map_prim_adr1(mp1, dna1, dna2, prsz1);

	


	fname2 = path1 + "seqdump.txt";
	vector<ListFasta> dna_mas = pp.GetFileListFasta(fname2);
	for (i = 41; i < dna_mas.size(); i++)
	{
		pp.find_words_in_mp1_glob(dna_mas[i].dna, prsz1);
	}

	outfile.open("mp2_c");
	i = 1;
	for (auto& x : pp.mp1_glob) {
		outfile << i << "," << x.first << ", " << x.second << endl;
		i++;
	}
	
	outfile.close();


	fname1 = path1 + "hu\\GCF_000001405.39_GRCh38.p13_genomic.fna";
	pp.find_words_read_in_mp1_glob(fname1, prsz1);

	outfile.open("mp3_c");
	i = 1;
	for (auto& x : pp.mp1_glob) {
		outfile << i << "," << x.first << ", " << x.second << endl;
		i++;
	}

	outfile.close();
	return(0);
}

void Prim1::conserv_calc()
{
	string prims[6];
	prims[0] = "TGATGGCTTTATGGGTAGAATT";
	prims[1] = "TGTGCCTTTCAACTCTCATG";
	prims[2] = "CCAGTTGCGTCACCAAATGAATG";
	
	prims[3] = polindrom(prims[0]);
	prims[4] = polindrom(prims[1]);
	prims[5] = polindrom(prims[2]);

	int i,j,k,d,d1, prsz1;
//	string pattern, path1 = "C:\\programs\\Marcela\\Pr1\\SEQs\\";
	string pattern, path1 = "SEQs\\";
	string fname1 = path1 + "sc.fasta";
//	string fname2 = path1 + "seqdump.txt";
	string fname2 = path1 + "New viruses for Zecharia1.txt";
	vector<ListFasta> dna_mas = GetFileListFasta(fname2);

	vector<int> p[6];
	string dna1 = GetFileFasta(fname1);

	ofstream outfile[6];

	for (k = 0; k < 6; k++)
	{
		outfile[k].open(prims[k]);

		prsz1 = prims[k].length();
		pattern = prims[k];
		d = 0;
//		for (i = 41; i < dna_mas.size(); i++)
		for (i = 0; i < dna_mas.size(); i++)
		{
			d1 = find_closest_dist(dna_mas[i].dna, pattern);
			d += d1;

			outfile[k] << i << "\t" << dna_mas[i].header << "\n" << d1 << "\n";
			for (j = 0; j < seq_glob1.size(); j++)
				outfile[k] << j << ")\t" << seq_glob1[j] << "\n";
		}
		p[k].push_back(d);

		outfile[k].close();

		continue;

		for (j = 0; j <= dna1.length() - prsz1; j = j+ prsz1)
		{
			cerr << k << " " << j << "\n";
			pattern = dna1.substr(j, prsz1);
			d = 0;
			//for (i = 41; i < dna_mas.size(); i++)
			for (i = 0; i < 41; i++)
			{
				d1 = find_closest_dist(dna_mas[i].dna, pattern);
				d += d1;
			}
			p[k].push_back(d);
		}
	}

	return;

	for (k = 0; k < 3; k++)
	{
		outfile[k].open(prims[k]);
		for (i = 0; i < p[k].size(); i++)
			outfile[k] << i << "\t" << p[k][i] << "\n";
		outfile[k].close();
	}
}

int Prim1::find_closest_dist(string s1, string s2)
{
	seq_glob1.clear();
	int i,j,d,min = s2.length();
	for (i = 0; i <= s1.length() - s2.length(); i++)
	{
		d = 0;
		for (j = 0; j < s2.length(); j++)
		{
			if (s1[i + j] != s2[j])
			{
				d++;
//				if (d == min) break;
			}
		}

		if (d == 5)
			seq_glob1.push_back(s1.substr(i, s2.length()));

		if (d < min)
			min = d;

		if (min == 0) break;
			
	}
	return min;
}

string Prim1::polindrom(string s)
{
	int i;
	string ss = "";

	for (i = 0; i < s.length(); i++)
	{
		if (s[s.length() - i - 1] == 'A')
			ss = ss + 'T';
		if (s[s.length() - i - 1] == 'T')
			ss = ss + 'A';
		if (s[s.length() - i - 1] == 'C')
			ss = ss + 'G';
		if (s[s.length() - i - 1] == 'G')
			ss = ss + 'C';
	}

	return (ss);

}