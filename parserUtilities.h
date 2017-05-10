/* This file deals with overloading operator >> and operator << for the input output streams
   The delimiter it uses for parsing is space and ,
   When we read from the file, if we encounter a problem of say bad formatting, we don't quit.
   We print a error log, skip till new line is reached and then read further data from the stream
   We differentiate this bad data by making value of grade to int_min(). This value can be checked 
   before writing into file/buffer.	 
*/
#include<limits>
#include<locale>
#include<iostream>
#include"gradeRecord.h"

namespace gradeSorter
{
	// We need to add ',' also as a delimiter. Default is only space.
	// If more delimiters are needed like ';', we have to add here. Right now on the fly delimiter chage 
	// 	of set/get is not provided.
	class my_ctype : public	std::ctype<char>
	{
	    mask my_table[table_size];
	public:
	    my_ctype(size_t refs = 0)  
	        : std::ctype<char>(&my_table[0], false, refs)
	    {
	        std::copy_n(classic_table(), table_size, my_table);
	        my_table[','] = (mask)space;
        
	    }
	};

	std::istream& operator>>(std::istream& is, Record& aRecord)
	{
		is >> aRecord.secondName_ ;
		if(! is.eof() && ! is.fail())	
			is >> aRecord.firstName_ ;
		if(! is.eof() && ! is.fail())	
			is>> aRecord.grade;
				
		if(is.fail() && ! is.eof()){
				std::cout << " Format error. Skipping till new line" << std::endl;
				is.clear();
				is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				aRecord.grade = std::numeric_limits<int>::min();
			}
			
	    return is;
	}

	std::ostream& operator<<(std::ostream& is, const Record& aRecord)
	{
		if(aRecord.grade != std::numeric_limits<int>::min())
			is << aRecord.secondName_ << ", " << aRecord.firstName_ << ", " << aRecord.grade;

	    return is;
	}
	
}