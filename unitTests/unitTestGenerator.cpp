/* A simple test file generator. It generates random string with random length for firstName and secondName.
   It also generates random grades. They are then sorted and clubed to form secondName,firstName,grade string.
   Since they are sorted already, the lower-ranked name would get higher ranked grade. 
   It is written to a original file. Then the string or records is shuffled and placed in another to-be-sorted file.
   This to-be-soreted file will be fed to the orignal program and the output can be 'diff'ed between the orginal file
   and the to-be-sorted-graded.txt. The diff should be 0.

   We ofcouse can edit the generated files to include duplicates and have higher-ranked name getting higer ranked grade
   and vice versa. This is not automated here.
*/   

#include<iostream>
#include<algorithm>
#include<string>
#include<vector>
#include<random>
#include<fstream>

using namespace std;

void generateNames(vector<string>& names, int numberOfRecords)
{
	static const char alphabet[] = "abcdefghijklmnopqrstuvwxyz";
	std::random_device rd;  
	std::mt19937 gen(rd()); 
	std::uniform_int_distribution<> distribution(0, 25);
	
	for(int i=0; i<numberOfRecords; ++i)
	{
		std::uniform_int_distribution<> strLenDis(2, 10);
		string str;
		int strLen = strLenDis(gen);
		str.reserve(strLen);
		
		std::generate_n(std::back_inserter(str), strLen,
		[&]() { return alphabet[distribution(gen)];}); 
		names.push_back(str);				   			   
	}
}

void generateGrades(vector<int>& grades, int numberOfRecords)
{
	std::random_device rd;  
	std::mt19937 gen(rd()); 
	std::uniform_int_distribution<> distribution(1, 100);
	
	generate_n(back_inserter(grades), numberOfRecords, [&]() { return distribution(gen); });
}

void writeIntoFile(string& outfilename, vector<string>& buffer)
{
	std::ofstream outputfile(outfilename);
	if (!outputfile)
	{
		outputfile.close();
		std::cerr << "can't open " << outfilename << '\n';
		return;
	}
	
	std::copy(buffer.begin(), buffer.end(), std::ostream_iterator<string>(outputfile, "\n"));
	outputfile.close();
}

int main()
{
	std::random_device rd;  //Will be used to obtain a seed for the random number engine
	std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
	std::uniform_int_distribution<> distribution(1, 1000);
	int numberOfRecords = distribution(gen);
	
	vector<int> grades;
	vector<string> firstNames;
	vector<string> secondNames;
			
	generateGrades(grades, numberOfRecords);	
	generateNames(firstNames, numberOfRecords);
	generateNames(secondNames, numberOfRecords);
	
	sort(grades.begin(), grades.end());	
	sort(firstNames.begin(), firstNames.end());
	sort(secondNames.begin(), secondNames.end());
	
	vector<string> buffer;
	for(int i=numberOfRecords-1, j = 0; i>=0; --i, ++j)
	{
		string str;
		str = secondNames[j]+", " + firstNames[j] + ", " + to_string(grades[i]);
		buffer.push_back(str);
	}
	
	string outFile = "gradesFileOriginal.txt";
	writeIntoFile(outFile, buffer);
	
	random_shuffle(buffer.begin(), buffer.end());
	
	string testOutFile = "gradesFileShuffled.txt";
	writeIntoFile(testOutFile, buffer);
	
}