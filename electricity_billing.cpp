#include<iostream>
#include<string.h>
#include<stdexcept>
#include<exception>
#include<typeinfo>
#include<vector>
#include <thread>
//voice header
#include<windows.h>
#include<mmsystem.h>
#include<time.h>
using namespace std;
// using namespace std::this_thread;

class Admin;
class Employee;
class User;
class Domestic;
class Commercial;
void debitAmount(double);
int g=0;

void sound()
{
    int f,t;
    srand(time(0));
    f=(rand()%10);
    t=(rand()%100)+1000;
    Beep(500,200);
    Beep(500,200);
    Beep(500,200);
    Beep(f,500);
    Beep(587,500);
    Beep(698,t);
    return;
}

/**Exception class**/
class Exception1
{
public:
    string msg;

    Exception1(string m):msg(m){}
     void show()
    {
        cout<<msg;
    }
};


/**User Bank Account class**/
class UserAccount{
public:
    string bankName;
    long accNo;
    double accBal;

UserAccount():bankName(""),accNo(0),accBal(0){}

void accountDetails()
{
    cout<<"Bank Name : "<<bankName<<endl;
    cout<<"Account Number : "<<accNo<<endl;
    cout<<"Account Balance : "<<accBal<<endl;
}

//If no account is created then the function is called
 void createAccount()
    {
        cout<<"Enter Bank Name\n";
        cin>>bankName;
        cout<<"\nAccount Number: ";
        cin>>accNo;
        cout<<"\n\nAccount Successfully created with default Balance\n";
        accBal=1000.0;  //Minimum balance;
        return;
    }
};

/** User class **/
class User{
private:
    string name;
    string address;
    string userName;
    string password;

    UserAccount* account;

public:
    int id;
    int units;
    string userType;
    double billAmount;
    int status;
    static int dCnt;
    static vector<User> ulist;

User(){}

User(string n,int a,string ad,string ut,string un,string p, int u)
{
    name=n;
    id=a;
    address=ad;
    userType=ut;
    userName=un;
    password=p;
    units=u;
    billAmount=0;
    account=NULL;
    status=0;
    }

    void setUser();

    int login(int chance)
    {
       string a, b;
       int i;
        cout<<"Enter User Name and Password\n";
        cin>>a>>b;

        if(a!=userName){
            cout<<"User Name not registered\nRetry\n";
            i=login(chance-1);
            return i;
            }

        else if(b!=password){
            cout<<"Wrong Password\nRetry\n";
            i=login(chance-1);
            return i;}

        else
        {
             cout<<"You have successfully logged into your account\n\n";
            return 1;
            }
    }

virtual void viewBill(){cout<<"Total Bill= "<<billAmount<<endl;}

virtual void userProfile()
{
    cout<<"User Name : "<<name<<endl;
    cout<<"User ID : "<<id<<endl;
    cout<<"User Address : "<<address<<endl;
    cout<<"User Type : "<<userType<<endl;
    return;
}


void viewAccount()
    {
        if(!account)
        {
            cout<<"Bank Account is not linked to the system.\nDo you want to link your account?\n Enter 1 to agree\n";
            int a;
            cin>>a;
            if(a==1){
                    account= new UserAccount;
                    account->createAccount();}
            else
            {
                cout<<"Returning\n";
            }
        }
        else
            account->accountDetails();
    }

 //   void friend debitAmount(Admin* a, User u);

    void payBill()
    {
        if(!account)
        {
            cout<<"\nYour Bank Account is not registered with the system\n";
            cout<<"Add account to process Transactions\n\n";
            return;
        }

        else if(billAmount==0)
        {
            cout<<"\nBill Amount="<<billAmount;
            cout<<"\nNo Due\n";
            return;
        }

        else if(account->accBal >= billAmount)
        {
            cout<<"Payment under process. . .\n";
            // sleep_for(1000ns);
            cout<<"Paying bill   "<<billAmount;
//             sleep_for(1000ns);
            sound();
            cout<<"\nTransaction Successful\n";
            account->accBal-=billAmount;
            //  sleep_for(1000ns);
            cout<<"\nCurrent Balance= "<<account->accBal;
            status=1;
        }
        else
        {
            cout<<"\nInsufficient Balance. Kindly Try again later\n\n";
            return;
        }
    }

     void displayAllCustomers(vector<User>* u)
    {
        vector<User>::iterator it;
        for(it=u->begin();it!=u->end(); it++)
        {
            it->userProfile();
            cout<<"*****************************************************\n";
        }
    }

    virtual void addUser(){}

    vector<User>* getUser()
    {
        if(ulist.empty())
            return NULL;
        return &ulist;
    }
};
vector<User> User::ulist;
//UserAccount* User::account=0;
int User::dCnt=0;



/**Domestic User class inherits User class publicly**/
class Domestic:public User{
private:
    string mailid;
public:

Domestic():User(){}
Domestic(string n,int a,string m,string ad,string ut,string un,string p,int u):User(n,a,ad,ut,un,p,u)
{dCnt++;
mailid=m;
//cout<<"Domestic user added\n";
}


void userProfile()
{
    User::userProfile();
    cout<<"User mail Id : "<<mailid<<endl;
    cout<<"Total Units consumed : "<<units<<endl;
    cout<<"\n**********************************************\n";
}

void viewBill()
{
    User::viewBill();
}
};
//int Domestic::dCnt=0;


class Commercial:public User
{
public:
  //  static int dCnt;
Commercial():User(){}
Commercial(string n,int a,string ad,string ut,string un,string p,int u):User(n,a,ad,ut,un,p,u)
{
    dCnt++;
   // cout<<"Commercial user added\n";

}

void userProfile()
{
    User::userProfile();
    cout<<"Total Units consumed : "<<units<<endl;
    cout<<"\n*********************************************\n";
}

void viewBill()
{
    User::viewBill();
}

};
//int Commercial::dCnt=0;

void User::setUser()
{
    //User dd;
    Domestic d1("Jaya",1001,"jaya@gmail.com","Hubli", "Domestic","1001","1001",200);
    Domestic d2("Suma", 1002, "suma@gmail.com", "Hubli", "Domestic","1002","1002",350);
    Domestic d3("Arnav",1003, "arnav@gmail.com", "Hubli", "Domestic" ,"1003","1003",230);
    Domestic d4("Jaby",1004,"jaby@gmail.com","Hubli","Domestic","1004","1004",360);
    Domestic d5("Vishnu",1005,"vishnu@gmail.com","Hubli","Domestic","1005","1005",310);
    Domestic d6("Jaya",1006,"jaya@gmail.com","Hubli", "Domestic","1006","1006",280);
    Domestic d7("Suma", 1007, "suma@gmail.com", "Hubli", "Domestic","1007","1007",340);
    Domestic d8("Arnav",1008, "arnav@gmail.com", "Hubli", "Domestic" ,"1008","1008",250);
    Domestic ddd[]={d1,d2,d3,d4,d5,d6,d7,d8};
    for(int i=0; i<8; i++)
        ulist.push_back(ddd[i]);

    Commercial c1("AT limited",2001,"Hubli", "Commercial","2001","2001",600);
    Commercial c2("Hitech",2002,"Hubli", "Commercial","2002","2002",680);
    Commercial c3(" Expert",2003,"Hubli", "Commercial","2003","2003",720);
    Commercial c4("Jaby transport",2004,"Hubli", "Commercial","2004","2004",750);
    Commercial c5("Vishnu meals",2005,"Hubli", "Commercial","2001","2001",550);
    Commercial c6("Fundoota",2006,"Hubli", "Commercial","2001","2001",634);
    Commercial c7("ONGC oils",2007,"Hubli", "Commercial","2001","2001",810);
    Commercial c8("SBI lho",2008,"Hubli", "Commercial","2001","2001",1000);
    Commercial ccc[]={c1,c2,c3,c4,c5,c6,c7,c8};

    for(int i=8; i<16; i++)
        ulist.push_back(ccc[i-8]);
}

////////////////////////////////////////////////////////////////////


class Employee
{
private:
    string name;
    double salary;
    string userName;
    string password;

public:
    static vector <User>* users;
    int employeeId;
    static int eCnt;


    Employee(){}
    Employee(string n,double s,string un,string pw,int eid)
    {
        name=n;
        salary=s;
        userName=un;
        password=pw;
        employeeId=eid;
      //  users=NULL;
        cout<<"Employee added\n";
        eCnt++;
    }

    void printEmployee()
    {
        cout<<"Name= "<<name<<"\nID= "<<employeeId<<"\nSalary="<<salary<<endl;
        cout<<"\n***************************************************\n";
    }

    void appointUser()
    {
        User u;
        users=u.getUser();
    }

   void generateBill()
   {
       if(users==NULL)
       {
           cout<<"\nNO USERS ADDED\n please add users to continue. . .\n";
           return ;
       }
       cout<<"\nEnter the start and end index of userlist to Generate their bill\n";
       int id1, id2;
       try{
       cin>>id1>>id2;}
       catch(Exception1& e1){e1.show();}

       if(id1<0 || id2<0 || id1>15 ||id2>15|| id1>id2)
        throw Exception1("\nInvalid Range of users\n");

       else
       {
           double amt=0;
           for(int i=id1; i<=id2; i++)
           {
               if(users->at(i).userType=="Domestic")
               {
                    int units=users->at(i).units ;
                    if(units>=1&&units<=200)
                        amt=units*3;
                    else if (units>=201&&units<=400)
                        amt=200*3+(units-200)*4.5;
                    else if(units>=400&&units<=800)
                        amt=200*3+200*4.5+(units-400)*6.5;
                    else if(units>=800&&units<=1200)
                        amt=200*3+200*4.5+400*6.5+(units-800)*7;
                    else if(units>1200)
                        amt=200*3+200*4.5+400*6.5+400*7+(units-1200)*8;
                    else
                        cout<<"\nInvalid units\n"<<endl;
                    cout<<"\nTotalBill of the user= "<<amt;
                    users->at(i).billAmount=amt;
               }
               else
               {
                    int units=users->at(i).units;
                    if(units>=1&&units<=200)
                        amt=units*5;
                    else if (units>=201&&units<=400)
                        amt=200*5+(units-200)*6.5;
                    else if(units>=400&&units<=800)
                        amt=200*5+200*6.5+(units-400)*8;
                    else if(units>=800&&units<=1200)
                        amt=200*5+200*6.5+400*8+(units-800)*9;
                    else if(units>1200)
                        amt=200*5+200*6.5+400*8+400*9+(units-1200)*10;
                    else
                        cout<<"Invalid units..."<<endl;
                    cout<<"\nTotalBill of the user= "<<amt;
                     users->at(i).billAmount=amt;
               }
           }
            // sleep_for(10ns);
           cout<<"\n\nBill Generation successful\n";
       }
   }

   void viewUser()
   {
       if(users==NULL)
       {
            cout<<"\nNO USERS ADDED\n please add users to continue. . .\n";
            return ;
       }

        users->at(0).displayAllCustomers(users);
   }

    int login(int ch);

};
int Employee::eCnt=0;
vector<User>* Employee::users=NULL;



int Employee::login(int chance)
    {
        if(chance==0)
            return 0;
      //  int chance=3;
      else
        {
            int ss;
       string a, b;
        cout<<"Enter User Name and Password\n";
        cin>>a>>b;

        if(a!=userName)
        {
            cout<<"Incorrect User Name. Try Again\n";
            ss=login(chance-1);
            return ss;
        }
        else if(b!=password)
        {
            cout<<"Wrong Password. Try Again\n";
            ss=login(chance-1);
            return ss;
        }
        else
        {
             cout<<"You have successfully logged into your account\n\n";
             return 1;
        }
        }
    }


class AdminAccount
{
public:
    string bankName;
    string IFSC;
    long accountNumber;
    double accountBalance;


   void createAccount()
    {
        cout<<"Enter Bank Name\n";
        cin>>bankName;
        cout<<"\nEnter IFSC\n";
        cin>>IFSC;
        cout<<"\nAccount Number: ";
        cin>>accountNumber;
        cout<<"\n\nAccount Successfully created with default Balance\n";
        accountBalance=1000.0;
        return;
    }

    void accountDetails()
    {
        cout<<"BANK NAME: "<<bankName<<endl;
        cout<<"BANK IFSC: "<<IFSC<<endl;
        cout<<"ACCOUNT NUMBER: "<<accountNumber<<endl;
        cout<<"ACCOUNT BALANCE: "<<accountBalance<<endl;
    }
};


class Admin
{
private:
    string name;
    int adminId;
    long long phone;
    string userName;
    string password;
    static AdminAccount* account;
    static Admin* instance;

public:

    Employee employee[50];

     Admin():name(""){}

    static Admin* createAdmin()
    {
        if(!instance)
            instance= new Admin;
        return instance;
    }

    void setAdminData()
    {
        cout<<"Admin Name: ";
        cin>>name;
        cout<<"Admin Id: ";
        cin>>adminId;
        cout<<"Contact Number: ";
        cin>>phone;
        cout<<"Just One more step to take and you are ready to go!!\n\n";
        cout<<"Set User Name: ";
        cin>>userName;
        cout<<"Set Password: ";
        cin>>password;
        cout<<"CONGRATULATIONS on being new Admin to the system. Please login to your account to continue.\n";
        cout<<"Do not Share your credentials with anybody.\n";
    }


    int login(int chance)
    {
        if(chance==0)
            return 0;

      else
        {
            int ss;
       string a, b;
        cout<<"Enter Employee Name and Password\n";
        cin>>a>>b;

        if(a!=userName)
        {
            cout<<"Incorrect User Name. Try Again\n";
            ss=login(chance-1);
            return ss;
        }
        else if(b!=password)
        {
            cout<<"Wrong Password. Try Again\n";
            ss=login(chance-1);
            return ss;
        }
        else
        {
             cout<<"You have successfully logged into your account\n\n";
             return 1;
        }
        }
    }


    void viewAccount()
    {
        if(!account)
        {
            cout<<"Bank Account not linked to the system\nDo you want to link?\n Enter 1 to agree\n";
            int a;
            cin>>a;
            if(a==1){
                    account= new AdminAccount;
                account->createAccount();
                }
            else
            {
                cout<<"\nReturning. . .\n";
            }
        }
        else
            account->accountDetails();
    }


    void adminProfile()
    {
        cout<<"Name: "<<name<<endl;
        cout<<"AdminID: " <<adminId<<endl;
        cout<<"Registered Phone: " <<phone<<endl;
        cout<<"Account User Name: " <<userName<<endl;
        cout<<"Password: " <<password<<endl;
        cout<<endl;
        return;
    }


    void viewEmployees()
    {
        if(employee[0].eCnt==0)
        {
            cout<<"\nNO EMPLOYEES ADDED TO THE SYSTEM\n";
            return;
        }
        else
        {
            int c=employee[0].eCnt;
            for(int i=0; i<c; i++)
            {
                employee[i].printEmployee();
            }
        }
        return;
    }


   void appointEmployee()
   {
        Employee e1("Arijit",25000.0,"arijit","arijit",111);
        employee[0]=e1;
        Employee e2("Atif",25000.0,"atif","atif",112);
        employee[1]=e2;
        Employee e3("Shreya",30000.0,"shreya","shreya",113);
        employee[2]=e3;
        Employee e4("Pritam",45000.0,"pritam","pritam",114);
        employee[3]=e4;


        cout<<"\nEmployees created successfully\ncount="<<employee[0].eCnt<<endl;
        cout<<endl;
        return;
   }

   void addEmployee()
   {
       if(employee[0].eCnt==0)
       {
           cout<<"\nYou cannot recruit Employee without default employees in the system\n";
           return;
       }
       string n,u,p;
       int id;
       double sal;
       cout<<"\nProvide Employee Details\n";
       cout<<"Name\n";
       cin>>n;
       cout<<"\nid\n";
       cin>>id;
        cout<<"\nsalary\n"; //    username     password
        cin>>sal;
        cout<<"\n set username and password\n";
        cin>>u>>p;
        Employee e1(n,sal,u,p,id);
        employee[e1.eCnt-1]=e1;
   }

   void removeEmployee()
   {
       int id;
       int i;
       if(employee[0].eCnt==0)
       {
           cout<<"\nNo Employee appointed\n";
           return;
       }

       cout<<"\nEnter employee ID to remove\n";
       cin>>id;
       for(i=0; i<employee[0].eCnt; i++)
       {
           if(employee[i].employeeId==id)
            break;
       }
       if(i<=employee[0].eCnt)
       {
           int n=employee[0].eCnt-1;
           for(int j=i; j<n; j++)
                employee[j]=employee[j+1];
            employee[0].eCnt-=1;
            cout<<"\nEmployee suspended successfully\n";
       }
       else
       {
           cout<<"\nNo employee found\n";
           return;
       }
   }


   Employee getEmployee(int id)
   {
       for(int i=0; i<employee[0].eCnt-1; i++)
       {
           if(employee[i].employeeId==id)
            return employee[i];
       }
       cout<<"\nEmployee not found\n";
   }

     void viewBillStatus()
   {
       int flag=0;
       if(!account)
       {
           cout<<"\nNo Bank Account linked with the system\nCannot process the function\n\n";
           return;
       }
        if(employee[0].eCnt==0)
        {
            cout<<"\nNo Users registered to the System\n";
            return;
        }
        if(employee[0].users->at(0).dCnt==0)
        {
            cout<<"\nNo Users registered to the system\n";
            return;
        }

       for(unsigned i=0; i<employee[0].users->size(); ++i)
       {
           if(employee[0].users->at(i).status==1)
           {
               flag=1;
               cout<<"\nBill Paid by="<<employee[0].users->at(i).id;
               cout<<"\nPayment Status=SUCCESS\n";
               cout<<"\nInitial Balance="<<account->accountBalance;
                account->accountBalance+=employee[0].users->at(i).billAmount;
                cout<<"\nCurrent Balance="<<account->accountBalance;
                employee[0].users->at(i).billAmount=0;
                employee[0].users->at(i).status=0;
                cout<<"\n************************************************\n\n ";
           }
       }
        if(flag==1)
        cout<<"\nUser account reset done successfully\n\n";
        else
        {
            cout<<"\nNO PAYMENTS FOUND\n";
        }
       return;
   }
};
Admin* Admin::instance=0;
AdminAccount* Admin::account=0;


///ADMIN MENU************************************************************************///

void adminMenu()
{


    if(g==0){
        Admin* krish=krish->createAdmin();
        krish->setAdminData();g=1;}

        Admin* krish=krish->createAdmin();

    cout<<"\nLogin before you continue\n";
    int s=krish->login(3);
    if(s==1)
    {
        cout<<"\n*********************************************\n";
                int num;

                while(1)
                    {
                cout<<"\n\n1-View your Profile\n2-Bank Account Details\n3-Appoint Employee\n4-View employee details\n5-add employee\n6-Remove Employee\n7-Check user bill Status\n8-log out\n";
                cout<<"\n********************************************\n\n";
                cin>>num;
                switch(num)
                {
                case 1:krish->adminProfile();break;
                case 2:krish->viewAccount();break;
                case 3:krish->appointEmployee();break;
                case 4:krish->viewEmployees();break;
                case 5:krish->addEmployee();break;
                case 6:krish->removeEmployee();break;
                case 7:krish->viewBillStatus();break;
                case 8:cout<<"Logging out. . .\n";return;
                }
                }
    }
    //krish->viewBillStatus();break;
    else
    {
        cout<<"\n\nLogin Failed\n\n";
    }
    return;
}


///EMPLOYEE MENU****************************************************************///
int searchemp(Employee* e, int id);
void employeeMenu()
{

    try{
    Employee* emp;
    if(emp->eCnt==0)
        throw Exception1("No Employee recruited\n");

    Admin* a=a->createAdmin();

    emp=a->employee;

    cout<<"\nEnter your ID to Login\n\n";
    int id;
    cin>>id;

    int idd=searchemp(emp, id);
    if(idd==-1)
        return;

    int s=emp[idd].login(3);
    if(s==1)
    {
        emp[idd].appointUser();
//        emp[idd].users=dd;
        //setEmployee(emp);
         cout<<"\n*********************************************\n";
         int num;
         while(1)
         {
            cout<<"\n\n1-View your Profile\n2-Generate Bill\n3-view Users\n4-logout\n";
            cout<<"\n********************************************\n\n";
            cin>>num;
            switch(num)
            {
                case 1:emp[idd].printEmployee();break;
                case 2:emp[idd].generateBill();break;
                case 3:emp[idd].viewUser();break;
                case 4:cout<<"Logging out\n";return;
            }
        }
    } }
    catch(Exception1 &e)
    {
        e.show();
    }
    return;
}


int searchemp(Employee* e, int id)
{
    cout<<"\n\n";
    for(int i=0; i<e[0].eCnt; i++)
    {
        if(id==e[i].employeeId)
            return i;
    }
    cout<<"\nEmployee not found\n";
    return -1;
}

///USERMENU**********************************************************************///


void userMenu()
{
    if(g==0)
    {
        cout<<"\nSYSTEM HAS NO ADMIN\nCannot proceed without admin\n";
        return;
    }

    User u;
    u.setUser();
    int n1, num=-1;
    while(1)
    {
        cout<<"\nEnter ID to login\n";
        cin>>n1;

       for(unsigned i=0; i<u.ulist.size(); ++i)
       {
           if(n1==u.ulist.at(i).id)
                {cout<<"\nSearch Successful\n\n";
                num=i;
                break;}
       }
       if(num==-1)
       {
           cout<<"No User found\n";
           return;
       }

        int n1=u.ulist.at(num).login(3);
        if(n1==1)
    {
         cout<<"\n*********************************************\n";

         while(1)
         {
             int numm=0;
            cout<<"\n\n1-View your Profile\n2-View Account\n3-View Bill\n4-Pay Bill\n5-logout\n";
            cout<<"\n********************************************\n\n";
            cin>>numm;
            switch(numm)
            {
                case 1:u.ulist.at(num).userProfile();break;
                case 2:u.ulist.at(num).viewAccount();break;
                case 3:u.ulist.at(num).viewBill();break;
                case 4:u.ulist.at(num).payBill();break;
                case 5:cout<<"Logging out\n\n";return;
            }
        }
    }

    else
    {
        cout<<"\nLogin failed\n";
    }
    return;
    }
}


///MENU***************************************************************************///
void menu()
{
      int choice;

    while(1)
    {
        cout<<"\n\nHow do you want to initiate the system\n";
        cout<<"1-Admin\n2-Employee\n3-User\n4-exit\n\n";
        cin>>choice;
        switch(choice)
        {
            case 1: adminMenu();break;
            case 2: employeeMenu();break;
            case 3: userMenu();break;
            case 4: exit(0);
            default: exit(0);
        }
    }

}


void welcomePage()
{
    system("cls");

     cout << "\n\n\n\n\n";
    cout << "\t\t\t\t ************************************************\n";
    cout << "\t\t\t\t ||                                            ||\n";
    cout << "\t\t\t\t ||                                            ||\n";
    cout << "\t\t\t\t ||              _WELCOME TO _                 ||\n";
    cout << "\t\t\t\t ||                                            ||\n";
    cout << "\t\t\t\t ||   _ELECTRICITY BILL GENERATING SYSTEM _    ||\n";
    cout << "\t\t\t\t ||                                            ||\n";
    cout << "\t\t\t\t ||                                            ||\n";
    cout << "\t\t\t\t ************************************************\n\n\n";
    menu();
}


int main()
{
    welcomePage();
    return 0;
}



