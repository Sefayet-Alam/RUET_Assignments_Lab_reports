// Name:Khandoker Sefayet Alam
// Roll:2003121
// Section:C Question 01

#include<iostream>
#include<iomanip>
#include<algorithm>
#include<vector>
using namespace std;

class Employee
{
    string name, manager;
    int employee_code, salary, age;

    public:
        Employee(string name,int employee_code,int salary,int age,string manager);
        Employee();

        string get_name();
        string get_manager();
        int get_code();
        int get_salary();
        int get_age();

        void set_name(string name);
        void set_manager(string manager);
        void set_code(int code);
        void set_salary(int salary);
        void set_age(int age);

        void modify_manager();
        void display_info();

    protected:
        void display_manager();
};

class Manager: public Employee
{
    Employee emp_list[10];
    int emp_index;

    public:
        Manager(string name,int employee_code,int salary,int age,string manager);
        Manager();

        void add_emplyee();
        bool delete_emplyee();
        bool change_emplyee();

        void display_info();
};

void create_manager();
void create_employee();
void print_manager();
void print_employee();
void change_manager();
void change_employee();
void menu();

vector<Manager>manager_list;
vector<Employee>employee_list;

int main()
{
    int option=-1;
    int code;

    while(option!=7)
    {
        menu();
        cout<<"Enter option: "; cin>>option;

        switch(option)
        {
            case 1:
            {
                create_manager();
                break;
            }

            case 2:
            {
                create_employee();
                break;
            }

            case 3:
            {
                print_manager();
                break;
            }

            case 4:
            {
                print_employee();
                break;
            }

            case 5:
            {
                change_manager();
                break;
            }

            case 6:
            {
                change_employee();
                break;
            }
        }
    }


    return 0;
}


//employee methods
Employee::Employee(string name,int employee_code,int salary,int age,string manager)
{
    this->name=name;
    this->manager=manager;
    this->employee_code=employee_code;
    this->salary=salary;
    this->age=age;
}

Employee::Employee()
{
    this->name="";
    this->employee_code=0;
    this->salary=0;
    this->age=-1;
    this->manager="";
}

string Employee::get_name()
{
    return this->name;
}

string Employee::get_manager()
{
    return this->manager;
}

int Employee::get_code()
{
    return this->employee_code;
}

int Employee::get_salary()
{
    return this->salary;
}

int Employee::get_age()
{
    return this->age;
}

void Employee::set_name(string name)
{
    this->name=name;
}

void Employee::set_manager(string manager)
{
    this->manager=manager;
}

void Employee::set_code(int code)
{
    this->employee_code=code;
}

void Employee::set_salary(int salary)
{
    this->salary=salary;
}

void Employee::set_age(int age)
{
    this->age=age;
}

void Employee::modify_manager()
{
    string code;
    cout<<"\nEnter current manager code: "; cin>>code;

    if(code!=this->manager)
    {
        cout<<"\nManager code did not match\n";
        return;
    }

    cout<<"New manager code: "; cin>>code;
    this->set_manager(code);
}

void Employee::display_info()
{
    cout << "Employee info: " << endl;
    cout << "\tName: " << name << endl;
    cout << "\tCode: " << employee_code << endl;
    cout << "\tSalary: " << salary << endl;
    cout << "\tAge: " << age << endl;
}

void Employee::display_manager()
{
    cout << "Manager info: " << endl;
    cout << "\tName: " << name << endl;
    cout << "\tSalary: " << salary << endl;
    cout << "\tAge: " << age << endl;
}

//Manager methods
Manager::Manager(string name, int employee_code, int salary, int age,string manager):Employee(name,employee_code,salary,age,manager)
{
    this->emp_index=0;
}

Manager::Manager():Employee()
{
    this->emp_index=0;
}

void Manager::add_emplyee()
{
    if(emp_index==10)
    {
        cout<<"\nEmployee limit reached\n\n";
        return;
    }

    int code;
    cout<<"\nEnter employee code: "; cin>>code;

    int id=-1;
    for(int i=0;i<employee_list.size();++i)
    {
        if(employee_list[i].get_code()==code)
        {
            id=i; break;
        }
    }

    if(id==-1)
    {
        cout<<"\nEmployee not found\n\n";
        return;
    }

    this->emp_list[emp_index++]=employee_list[id];
}

bool Manager::delete_emplyee()
{
    string name;
    int code;

    cout<<"\nEmployee Name: "; cin>>name;
    cout<<"\nEmployee Code: "; cin>>code;

    int id=-1;
    for(int i=0;i<this->emp_index;++i)
    {
        if(emp_list[i].get_code()==code)
        {
            id=i; break;
        }
    }

    if(id==-1)
    {
        cout<<"\nEmployee not found\n\n";
        return false;
    }

    for(int i=id;i<emp_index-1;++i) this->emp_list[i]=this->emp_list[i+1];
    --emp_index;

    return true;
}

bool Manager::change_emplyee()
{
    int code;

    cout<<"\nEnter employee code: "; cin>>code;

    int id=-1;
    for(int i=0;i<this->emp_index;++i)
    {
        if(emp_list[i].get_code()==code)
        {
            id=i; break;
        }
    }

    if(id==-1)
    {
        cout<<"\nEmployee not found\n\n";
        return false;
    }

    cout<<"\nNew Employee code: "; cin>>code;
    int id1=-1;
    for(int i=0;i<employee_list.size();++i)
    {
        if(employee_list[i].get_code()==code)
        {
            id1=i; break;
        }
    }

    if(id1==-1)
    {
        cout<<"\nemployee not found\n";
        return false;
    }

    this->emp_list[id]=employee_list[id1];

    return true;
}

void Manager::display_info()
{
    Employee::display_manager();
    for(int i=0;i<this->emp_index;++i) cout<<this->emp_list[i].get_name()<<endl;
}


void menu()
{
    cout <<endl<<"****Options****" << endl;
    cout << "\t1. Create manager" << endl;
    cout << "\t2. Create employee" << endl;
    cout << "\t3. print manager data" << endl;
    cout << "\t4. print employee data" << endl;
    cout << "\t5. Change manager" << endl;
    cout << "\t6. Change Employee" << endl;
    cout << "\t7. exit" << endl<<endl;
}

void create_manager()
{
    string name,manager;
    int code,salary,age;

    cout<<"\nName: "; cin>>name;
    cout<<"\nManager Code: "; cin>>code;
    cout<<"\nSalary: "; cin>>salary;
    cout<<"\nAge: "; cin>>age;
    cout<<"\n";

    Manager temp=Manager(name,code,salary,age,"");
    manager_list.push_back(temp);
}

void create_employee()
{
    string name,manager;
    int code,salary,age;

    cout<<"\nName: "; cin>>name;
    cout<<"\nEmployee Code: "; cin>>code;
    cout<<"\nSalary: "; cin>>salary;
    cout<<"\nAge: "; cin>>age;
    cout<<"\nSupervising Manager: "; cin>>manager;
    cout<<"\n";

    Employee temp = Employee(name,code,salary,age,manager);
    employee_list.push_back(temp);
}

void print_manager()
{
    int code;
    cout<<"\nEnter manager code: "; cin>>code;

    int id=-1;
    for(int i=0;i<manager_list.size();++i)
    {
        if(manager_list[i].get_code()==code)
        {
            id=i; break;
        }
    }

    if(id==-1)
    {
        cout<<"\nManager not found\n\n";
        return;
    }

    manager_list[id].display_info();
}

void print_employee()
{
    int code;
    cout<<"\nEnter employee code: "; cin>>code;

    int id=-1;
    for(int i=0;i<employee_list.size();++i)
    {
        if(employee_list[i].get_code()==code)
        {
            id=i; break;
        }
    }

    if(id==-1)
    {
        cout<<"\nemployee not found\n\n";
        return;
    }

    employee_list[id].display_info();
}

void change_manager()
{
    int code;
    cout<<"\nEnter employee code: "; cin>>code;

    int id=-1;
    for(int i=0;i<employee_list.size();++i)
    {
        if(employee_list[i].get_code()==code)
        {
            id=i; break;
        }
    }

    if(id==-1)
    {
        cout<<"\nemployee not found\n";
        return;
    }

    employee_list[id].modify_manager();
}

void change_employee()
{
    int code;
    cout<<"\nEnter manager code: "; cin>>code;

    int id=-1;
    for(int i=0;i<manager_list.size();++i)
    {
        if(manager_list[i].get_code()==code)
        {
            id=i; break;
        }
    }

    if(id==-1)
    {
        cout<<"\nManager not found\n\n";
        return;
    }

    manager_list[id].change_emplyee();
}
