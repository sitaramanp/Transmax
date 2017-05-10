/* sortByGrade takes the filename. It has a deque buffer into which the data is read.
   This buffer is then sorted and the sorted sequence written into out-file.
*/
#include<algorithm>
#include<deque>
#include<fstream>
#include<string>
#include"parserUtilities.h"

namespace gradeSorter
{
	class sortByGrade
	{
	public:
		sortByGrade(std::string& file) : filename(file) {}
		void writeSortedGrades();
		void parseAndSortGrades(bool verbose=true);

	private:
		std::string filename;
		std::deque<Record> buffer;
		void printBuffer();
	};
	
	void sortByGrade::writeSortedGrades()
	{
		std::string::size_type idx;
		idx = filename.rfind('.');
		
		std::string outfilename;
		if(idx != std::string::npos)
			outfilename = filename.substr(0, idx);
		else
			outfilename = filename;
		
		outfilename = outfilename + "-graded.txt";
		
		std::ofstream outputfile(outfilename);
		if (!outputfile)
		{
			outputfile.close();
			std::cerr << "can't open " << outfilename << '\n';
			return;
		}
		
		std::copy(buffer.begin(), buffer.end(), std::ostream_iterator<Record>(outputfile, "\n"));
		outputfile.close();
		std::cout << "Finished: Created " << outfilename << std::endl;		 		
	}
	
	void sortByGrade::printBuffer()
	{
		std::for_each(buffer.begin(), buffer.end(), [](Record& r) { 
			if(r.grade != std::numeric_limits<int>::min())
				std::cout << r.secondName_ << ", " << r.firstName_ << ", " << r.grade << std::endl;
		});		
	}
	
	void sortByGrade::parseAndSortGrades(bool verbose)
	{
		std::ifstream infile(filename);
		if (!infile)
		{
			infile.close();
			std::cerr << "can't open " << filename << '\n';
			return;
		}

		std::locale commaAndSpaceDelim(std::locale::classic(), new my_ctype);
		infile.imbue(commaAndSpaceDelim);

		std::copy((std::istream_iterator<Record>(infile)), (std::istream_iterator<Record>()), std::back_inserter(buffer));
		infile.close();

		std::sort(buffer.begin(), buffer.end()); 
		
		if(verbose)
			printBuffer();
		
		writeSortedGrades();
	}
	
}

int main(int argc, char *argv[])
{
	std::string filename;
	
	if(argc != 2)
	{
		std::cout << "Usage should include one file name" << std::endl;
		return 1;
	} 
	
	filename = argv[1];
	gradeSorter::sortByGrade sortFile(filename);
	sortFile.parseAndSortGrades();
	return 0;
}
