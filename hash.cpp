#include <iostream>
#include <vector>
#include <cstdlib>
#include <iomanip>
using namespace std;

const int MAX= 9999;

struct Student{
  string name;
  string id;
  int age;
  float gpa;
};

vector<Student> students[MAX];

//function performs the DJBX33A algorithm
long hashFunction(string key)
{
  long hash = 5381;//hash initialized
  int keyLen = key.length();
  for (int i = 0; i < keyLen; ++i) {
    hash = (hash * 33 + key[i])%MAX;
  }
  return hash%MAX;//mode for separate chaining

}
//function used to find student in the table
Student findStudent(string key)
{
  long pos = hashFunction(key);//students position
  for(int i=0;i<students[pos].size();++i)
    {
      if(students[pos][i].id == key)
        return students[pos][i];
    }
  Student stu;
  stu.id = "-1";
  return stu;
}

//Function to insert student into hash table
void insertStudent(string id,string name,int age,int gpa)
{
  Student stu; 
  stu.id = id;
  stu.name = name;
  stu.age = age;
  stu.gpa = gpa;
  long hash = hashFunction(id);
  students[hash].push_back(stu);
}

//function is used to display a certain student's record
void display(Student stu)
{
  cout<<"Id : "<<stu.id<<"\n";
  cout<<"Name : "<<stu.name<<"\n";
  cout<<"Age : "<<stu.age<<"\n";
  cout<<setprecision(2) << "GPA : "<<stu.gpa<<"\n";
}

int main()
{
  char command = 'y';
  cout<<"enter 1 to enter a student record\n";
  cout<<"enter 2 to display a record\n";
  cout<<"enter N to quit\n";
  while(command!='n' && command!='N')
    {
      int input;
      cout<<"enter a choice : ";
      cin>>input;
      if(input==1)
        {
          cout<<"Enter student id : ";
          string id;
          cin>>id;
          cout<<"Enter student name : ";
          string name;
          cin>>name;
          cout<<"Enter student age : ";
          int age;
          cin>>age;
          cout<<"Enter student gpa : ";
          float gpa;
          cin>>gpa;
          insertStudent(id,name,age,gpa);
          cout<<"Record inserted\n";
        }
      else if(input==2)
        {
          cout<<"enter the ID of student\n";
          string id;
          cin>>id;
          Student res = findStudent(id);
          if(res.id == "-1")
            cout<<"No student with this id has been found\n";
          else
            {
              display(res);
            }
        }
      cout<<"enter Y to continue or N to quit : ";
      cin>>command;
    }
  return 0;
}
