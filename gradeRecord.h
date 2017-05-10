/* Simple grade record having firstName, secondName and grade
*/
#include<string>

namespace gradeSorter
{
	
	struct Record 
	{
	public:
		Record() {}
		bool operator <(const Record& rhs) const
		{
			if(this->grade > rhs.grade)
				return true;
			if(this->grade == rhs.grade)
			{
				if(this->secondName_ < rhs.secondName_)
					return true;
				if(this->secondName_ == rhs.secondName_ && this->firstName_ < rhs.firstName_)	
					return true;
			}
		
			return false;
		}

		std::string firstName_;
		std::string secondName_;
		int grade;
	
	};

}