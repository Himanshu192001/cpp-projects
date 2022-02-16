#include<bits/stdc++.h>
using namespace std;
#define FILE_NAME "COURSE.txt"

class Courses
{
    private:
        int course_id;
        char course_name[100];
        float course_fee;
    public:
        void Read_data();
        void Show_data();
        bool checkid(int);
        
        int get_courseid()
        {
        	return course_id;
		}
		
		float get_fee()
		{
			return course_fee;
		}

};

void Courses::Read_data()
{
	
	Courses obj;
	while(1)
	{
	
		cout<<"\n";
	    cout<<"\n ENTER THE COURSE ID: ";
	    cin>>course_id;
	    bool get=obj.checkid(course_id);
	    if(get==false)
	    {
	    	break;
		}
		else
		{
			cout<<"\n THE COURSE ID ALREADY EXIST \n";
		}
	
	}
    cout<<"\n ENTER THE COURSE NAME:";
    cin.ignore();
    cin.getline(course_name,99);
	
	while(1)
	{
	
	    cout<<"\n ENTER THE COURSE FEE: ";
	    cin>>course_fee;
	    if(course_fee>0)
	    {
	    	break;
		}
		else
		{
			cout<<"\n ENTER VALID COURSE FEE\n";
		}
	}
	
}

void Courses::Show_data()
{
	cout<<"\n";
    cout<<"\n COURSE NAME:"<<course_name;
    cout<<"\n COURSE ID:"<<course_id;
    cout<<"\n COURSE FEE:"<<course_fee;
}

class Course_operation
{
    private:
        Courses obj;
        fstream file;
    public:
        void add();
        void update();
        void view_all();
        void search_filter();
        void search();
		
};

bool Courses::checkid(int id)
{
	fstream file;
	file.open(FILE_NAME,ios::in|ios::binary);
	Courses obj;
	int size=sizeof(obj);

	
	bool get=false;
	file.seekg(0);
	
	while(file.read((char*)&obj, sizeof(obj)))
	{
		if(id==obj.get_courseid())
		{
			get=true;
			break;
		}
	}
	file.close();
	return get;
}

void Course_operation::add()
{

	file.open( FILE_NAME , ios::out | ios::app | ios::binary );
	
	obj.Read_data();
	
	obj.Show_data();
	
	file.write( (char*)&obj, sizeof(obj));
	
	file.close();
    
}

void Course_operation::view_all()
{
	
	file.open(FILE_NAME , ios::in | ios::binary);
	
		Courses ob;
		
		while(file.read((char*)&ob, sizeof(ob)))
		{
			ob.Show_data();
		}
	
	file.close();
}

void Course_operation::update()
{
	file.open(FILE_NAME,ios::ate|ios::in|ios::out|ios::binary);
	int size=sizeof(obj);
	
	int courseID;
	cout<<"\n ENTER THE COURSE ID:";
	cin>>courseID;
	
	bool get=false;
	file.seekg(0);
	
	while(file.read((char*)&obj, sizeof(obj)))
	{
		if(courseID==obj.get_courseid())
		{
			get=true;
			break;
		}
	}
	
	if(get==true)
	{
		cout<<"\n OLDER DETAILS \n";
		obj.Show_data();
		cout<<"\n ENTER UPDATED DATA \n";
		obj.Read_data();
		
		int position = file.tellg();
		position -= size;
		
		file.seekp(position);
		file.write((char*)&obj,size);
		cout<<"\n RECORD IS UPDATED \n";
	}
	else
	{
		cout<<"THERE IS NO RECORD WITH THIS COURSE ID";
	}
}

void Course_operation::search()
{
	
	file.open(FILE_NAME,ios::in|ios::binary);
	int size=sizeof(obj);
	
	int courseID;
	cout<<"\n ENTER THE COURSE ID:";
	cin>>courseID;
	
	bool get=false;
	file.seekg(0);
	
	while(file.read((char*)&obj, sizeof(obj)))
	{
		if(courseID==obj.get_courseid())
		{
			get=true;
			break;
		}
	}
	if(get)
	{
		int position=size;
		position-=size;
		
		file.read((char*)&obj, position);
		
		obj.Show_data();
	
		file.close();
		
	}
	else
	{
		cout<<"\n FALSE \n";
	}
}



int main ()
{
	int choice;
	Course_operation data;
	while(1)
	{
		cout<<"\n";
		cout<<"\nPRESS 0 FOR EXIT"<<endl;
		cout<<"\nPRESS 1 FOR ADD"<<endl;
		cout<<"\nPRESS 2 FOR UPDATE"<<endl;
		cout<<"\nPRESS 3 FOR SEARCH"<<endl;
		cout<<"\nPRESS 4 FOR VIEW ALL "<<endl;
		cout<<"\n ENTER YOUR CHOICE";
		cin>>choice;
		if(choice==0)
		{
			break;
		}
		switch(choice)
		{
			case 1:
				data.add();
				break;
			case 2:
				data.update();
				break;
			case 3:
				data.search();
				break;
			case 4:
				data.view_all();
				break;
			default:
				cout<<"\n NO VALID INPUT \n";
				break;
		}
	}
		
	
	
	return 0;
}
