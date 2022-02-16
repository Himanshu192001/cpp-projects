#include<bits/stdc++.h>
using namespace std;
#define FILE_NAME "student_info.txt"
class Student
{
	private:
		int student_id;
		char name[50];
		char father_name[50];
		int month;
		int year;
		int date;
		
	public:
		void read_data();
		void show_data();
		int checkid();
		void add();
		void view_all();
		void search();
		void Delete();
		void update();
		void search_filter();
		
		int get_month()
		{
			return month;
		}	
		
		int get_date()
		{
			return date;
		}
		
		int get_year()
		{
			return year;
		}
		
		int get_studentid()
		{
			return student_id;
		}
		
		void set_id(int student_id)
		{
			this->student_id=student_id;
		}
		
};

int Student::checkid()
{
	int ID=1000;
	int i=0;
	fstream file;
	file.open(FILE_NAME,ios::in|ios::binary);
	Student obj;
	file.seekg(0,ios::end);
	if(file.tellg()==0)
	{
		return ID;
	}
	file.seekg(0);
	while(file.read((char*)&obj,sizeof(obj)))
	{
		ID=obj.get_studentid();
    }
	file.close();
	return ID;
}
void Student::read_data()
{
	cout<<"\n\n";
	cin.ignore();
	cout<<"\n ENTER THE STUDENT NAME:";
	cin.getline(name,49);
	cout<<"\n ENTER THE STUDENT'S FATHER NAME:";
	cin.getline(father_name,49);
	cout<<"\n ENTER THE DATE OF BIRTH ";
	while(1)
	{
		cout<<"\n YEAR:";
		cin>>year;
		if(year>0 || year<2022)
		{
			break;
		}
		else
		{
			cout<<"\n INVALID INPUT YEAR \n";
		}
	}
	while(1)
	{
		cout<<"\n MONTH:";
		cin>>month;
		if(month>0 || month<13)
		{
			break;
		}
		else
		{
			cout<<"\n INVALID INPUT MONTH \n";
		}
	}
	while(1)
	{
	cout<<"\n DATE:";
	cin>>date;
		if(date>0 ||date<32)
		{
			break;
		}
		else
		{
			cout<<"\n INVALID INPUT DATE \n";
		}
	}
	
	
}

void Student::show_data() 
{
	cout<<"\n";
	cout<<"\nSTUDENT ID:"<<student_id;
	cout<<"\nSTUDENT NAME:"<<name;
	cout<<"\nFATHER NAME:"<<father_name;
	cout<<"\nDATE OF BIRTH:";
	cout<<date<<"/"<<month<<"/"<<year;
	
	
}

void Student::add()
{
	fstream file;
	file.open(FILE_NAME,ios::out|ios::app|ios::binary);
	Student obj;
	int id=obj.checkid();
	obj.set_id(id+1);
	obj.read_data();
	file.write((char*)&obj,sizeof(obj));
	file.close();
}

void Student::view_all()
{
	fstream file;
	file.open(FILE_NAME,ios::in|ios::binary);
	Student obj;
	while(file.read((char*)&obj,sizeof(obj)))
	{
		obj.show_data();
	}
	file.close();
}
 
void Student::search()
{
	fstream file;
	file.open(FILE_NAME,ios::in|ios::binary);
	Student obj;
	int id;
	
	cout<<"\n ENTER STUDENT ID:";
	cin>>id;
	int size=sizeof(obj);
	bool get=false;
	while(file.read((char*)&obj,sizeof(obj)))
	{
		if(obj.get_studentid()==id)
		{
			get=true;
			break;
		}
		
	}
	
	if(get)
	{
		int position=size;
		position-=size;
		file.read((char*)&obj,position);
		obj.show_data();
		
	}
	else
	{
		cout<<"\n NO EXISTING STUDENT ID ";
	}
}

void Student::update()
{
	fstream file;
	file.open( FILE_NAME , ios::ate | ios::in | ios::out | ios::binary );
	
	Student obj;
	int size = sizeof( obj );
	int studentID;
	cout<<"\n ENTER THE STUDENT ID TO BE UPDATED: ";
	cin>>studentID;
	
	bool found = false;
	
	file.seekg(0);
	
	while( file.read( (char*)&obj, size) )
	{
		if( studentID==obj.get_studentid() )
		{
			found = true;
			break;
		}
	}	
	
	if( found==true)
	{
		cout<<"\n OLDER DETAILS \n";
		obj.show_data();

		int position = file.tellg();
		position -= size;
		obj.read_data();
		file.seekp( position );
		file.write((char*)&obj, size);
		
		cout<<"\nTHE RECORD IS UPDATED \n";		
	}
	else
	{
		cout<<"\n THERE IS NO RECORD WITH THIS STUDENT ID  \n";
	}
	file.close();
}

void Student::Delete()
{
	fstream file,temp;
	file.open(FILE_NAME,ios::in|ios::binary);
	temp.open("temp.txt",ios::out|ios::app|ios::binary);
	Student obj;
	int studentid;
	cout<<"\n ENTER THE STUDENT ID YOU  WANT TO REMOVE \n";
	cin>>studentid;
	bool get=false;
	while(file.read( (char*)&obj,sizeof(obj) ) ) 
	{
		cout<< obj.get_studentid() <<"\t" << studentid << endl;
		if(studentid==obj.get_studentid())
		{
			get=true;
			
		}
		else
		{
			temp.write((char*)&obj,sizeof(obj));
		}
	}
	file.close();
	temp.close();
	if(get==true)
	{
		remove( FILE_NAME );
		rename( "temp.txt", FILE_NAME );
		cout<<"\n THE RECORDS WITH STUDENT ID IS REMOVED  \n";
	}
	else
	{
		cout<<"\n THERE IS NO RECORD WITH THIS STUDENT ID \n";
	}
}

void Student::search_filter()
{
	fstream file;
	file.open(FILE_NAME,ios::in|ios::binary);
	Student obj;
	int year;
	while(1)
	{
		cout<<"\n ENTER THE BIRTH YEAR:";
		cin>>year;
		if(year>0 || year<2021)
		{
			break;
		}
		else
		{
			cout<<"\n INVALID INPUT PLEASE ENTER VALID INPUT \n";
		}
	}
	int end;
	bool get=false;
	int size=sizeof(obj);
	int position;
	while(file.read((char*)&obj,size))
	{
		
		if(obj.get_year()==year)
		{
			get=true;
			obj.show_data();	
		}
		
	}
	if(get==false)
	{
		cout<<"\nTHERE IS NO DETAILS WITH THIS BIRTH YEAR \n";
	}
	file.close();
}


int main()
{
	Student obj;
	
	int choice;
	while(1)
	{
		cout<<"\n\n";
		cout<<"\n PRESS 0 FOR EXIT";
		cout<<"\n PRESS 1 FOR ADD ";
		cout<<"\n PRESS 2 FOR VIEW ALL";
		cout<<"\n PRESS 3 FOR UPDATE";
		cout<<"\n PRESS 4 FOR DELETE";
		cout<<"\n PRESS 5 FOR SEARCH ";
		cout<<"\n PRESS 6 FOR SEARCH FILTER \n";
		cout<<"\nENTER YOUR CHOICE:";
		cin>>choice;
		if(choice==0)
		{
			break;
		}
		switch(choice)
		{
			case 1:
				obj.add();
				break;
			case 2:
				obj.view_all();
				break;
			case 3:
				obj.update();
				break;
			case 4:
				obj.Delete();
				break;
			case 5:
				obj.search();
				break;
			case 6:
				obj.search_filter();
				break;
			default:
				cout<<"\n INVALID INPUT \n";
				break;
		}
	}
	return 0;
}
