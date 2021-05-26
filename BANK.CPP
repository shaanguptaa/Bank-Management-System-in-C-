#include<iostream.h>
#include<conio.h>
#include<stdlib.h>
#include<graphics.h>
#include<string.h>
#include<dos.h>
#include<stdio.h>
#define MAX_SIZE 10
#define RECORDS 10

//-------------Global variables-------------------
int add_ac=0;

//-------------function declarations---------------
void loading();
void type(char);
void border();
void mainmenu();
int random();
void clr();
void m_arrow();

void main();
void c_pass();
void s_pass();
void mod_account();
void disp_all_account();
void del_account();
void bal_enquiry();
void withdraw();
void deposit();
void add_account();
void disp_all_account();
void disp_details();
int search_acc();
void disp_rec();
void restart();

//--------------- password class---------------------
class password
{
    private:
    char pass[10];

    public:

    password()
    {
        strcpy(pass,"password");
    }

    void set_pass()
    {
        clr();
        char p[10],c[10];
        cout<<"\n \n Enter New Password : "<<'\t';
        cin>>p;
        cout<<"\n \n Confirm Password : "<<'\t';
        cin>>c;

        if(strcmp(p,c)==0)
        {
            strcpy(pass,c);
        }
        else
        {
            cout<<"\n \n \n The Passwords Did Not Match !!!";
            cout<<"\n \n \n Press Any Key To Re-Enter The Password....";
            getch();
            set_pass();
        }
    }

    int check_pass(char p[10])
    {
	    if(strcmp(p,pass)==0)
            return 1;
        else
            return 0;
    }
};

password pass;

//---------------account class---------------
class account
{
    protected:
    int ac_no;
    unsigned long balance;
    char ac_holder_name[50];
    char branch[20];
    char ac_type[20];
    int rec_no;

    public:

    account()
    {
        rec_no=0;
    }

    int get_rec_no()
    {
        return rec_no;
    }

    unsigned long get_balance()
    {
        return balance;
    }

    void rec_no_incr()
    {
        rec_no++;
    }

    class record
    {
        private:
        long am_dep;
        long am_wd;
        unsigned long bal;

        public:

        void get_rec(long dep, long wd, long b)
        {
            am_dep=dep;
            am_wd=wd;
            bal=b;
        }

        void disp_record(int yc, int j)
        {
            if(am_dep != 0  ||  am_wd != 0)
            {
                gotoxy(1,yc);
                cout<<++j;

                if(am_dep != 0)
                {
                    gotoxy(12,yc);
                    cout<<am_dep;
                }
                else
                {
                    gotoxy(27,yc);
                    cout<<am_wd;
                }

                gotoxy(45,yc);
                cout<<bal;
            }
        }
    };

    record r[RECORDS];

    void get_ac()
    {
        clr();
        cout<<"\n Enter The Branch : "<<'\t';
        gets(branch);
	    cout<<"\n Enter The Name Of Account Holder : "<<'\t';
	    gets(ac_holder_name);
        cout<<"\n Enter The Type Of Account : "<<'\t';
        gets(ac_type);
        ac_no=random();
        balance=0;
    }

    void disp_ac_no()
    {
        cout<<'\t'<<ac_no;
    }
};

//---------------------customer class------------------
class customer : public account
{
    protected:
    int age;
    char address[100];
    char ph_no[11];
    char have_adhaar;
    char have_email;
    char adhaar_no[13];
    char email_id[50];

    public:
    void get_cust()
    {
        get_ac();
        cout<< "\n Enter Your Age : " << '\t';
        cin>>age;
        cout<< "\n Enter Your Address: " << '\t';
        gets(address);
        cout<< "\n Enter Your Contact No. : " << '\t';
        cin>>ph_no;
        cout<<"\n Do You Have Adhaar Card  (Y/N) : "<<'\t';
        cin>>have_adhaar;

        if(have_adhaar=='Y' || have_adhaar=='y')
        {
            cout<< "\n Enter Your Adhaar No. : " << '\t';
            cin>>adhaar_no;
        }
        else
	    strcpy(adhaar_no,"NA");

    	cout<<"\n Do You Have E-mail ID  (Y/N) : "<<'\t';
    	cin>>have_email;

	    if(have_email=='Y' || have_email=='y')
	    {
	        cout<< "\n Enter Your E-mail ID : " << '\t';
	        cin>>email_id;
	    }
	    else
	        strcpy(email_id,"NA");
    }

    void disp_ac_details()
    {
        clr();

        cout<<"\n Account Holder Name    :      "<<ac_holder_name;
        cout<<"\n Account No.            :      "<<ac_no;
        cout<<"\n Branch                 :      "<<branch;
        cout<<"\n Account Type           :      "<<ac_type;
        cout<<"\n Age                    :      "<<age;
	    cout<<"\n Address                :      ";disp_address();
        cout<<"\n Contact No.            :      "<<ph_no;
        cout<<"\n Adhaar No.             :      "<<adhaar_no;
        cout<<"\n E-mail ID              :      "<<email_id;
        cout<<"\n Balance                :      "<<balance;
    }

    int search(int no)
    {
        if(no==ac_no)
            return 1;
        else 
            return 0;
    }

    void disp_address();

    void disp_all_ac(int yc, int i)
    {
        if(ac_no!=0)
	    {
            gotoxy(1,yc);
            cout<<++i;

            gotoxy(12,yc);
            cout<<branch;

            gotoxy(27,yc);
            cout<<ac_no;

            gotoxy(42,yc);
            cout<<ac_type;

            gotoxy(55,yc);
            cout<<ac_holder_name;
        }
    }

    void deposit_amount(long amount)
    {
        clr();
        balance=balance+amount;
        cout<<"A total of "<<amount<<" Rs. Deposited to your Account No. :  "<<ac_no;

        balance_enquiry();
    }

    void withdraw_amount(long amount)
    {
        clr();
        if(amount<balance)
        {
            balance=balance-amount;
            cout<<"A total of "<<amount<<" Rs. Withdrawed from your Account No. - "<<ac_no;

            balance_enquiry();
        }
        else
	    cout<<"!! Amount can't be Withdrawed Due to Insufficient Balance...";
    }

    void balance_enquiry()
    {
        clr();
        cout<<"\n The Total Balance In Your Account is Rs. "<<balance;
    }

    void modify_account();

    void delete_account()
    {
        clr();
        char sure;
        disp_ac_details();
        cout<<"\n \n Are You Sure You Want To Delete This Account : (y/n)"<<'\t';
        cin>>sure;
        if(sure=='y' || sure=='Y')
        {
            clr();
            ac_no=0;
            cout<<"\n \n The Account Deleted Successfully.....";
        }

        if(add_ac==1)
            add_ac--;
    }

};

void customer::disp_address()
{
    int i;
    for(i=0;(i<100) && ((i!='\0') || (i!='\n'));i++)
        {
            if(address[i]==',')
                cout<<address[i]<<"\n                              ";
            else
                cout<<address[i];
        }
}

void customer::modify_account()
{
    int choice;

    cleardevice();
    gotoxy(1,4);
        
    cout<<"\n 1. Change Branch";
    cout<<"\n 2. Modify Account Type";
    cout<<"\n 3. Change Account Holder Name";
    cout<<"\n 4. Change Age";
    cout<<"\n 5. Change Address";
    cout<<"\n 6. Modify Contact No.";
    cout<<"\n 7. Link Different Adhaar No.";
    cout<<"\n 8. Change E=mail ID";

    cout<<"\n \n NOTE : ACCOUNT NUMBER CANNOT BE CHANGED ONCE ASSIGNED TO A CUSTOMER";

    cout<<"\n \n \n Enter Your Choice : "<<'\t';
    cin>>choice;

    m_arrow();

    cleardevice();
    gotoxy(1,4);

    switch(choice)
    {
        case 1 : cout<<"\n Previous Branch : "<<branch;
        cout<<"\n\n Enter New Branch : "<<'\t';
        gets(branch);
        break;

        case 2 : cout<<"\n Previous Account Type : "<<ac_type;
        cout<<"\n\n Enter Account Type : "<<'\t';
        gets(ac_type);
        break;

        case 3 : cout<<"\n Previous Account Holder Name : "<<ac_holder_name;
        cout<<"\n\n Enter Account Holder Name : "<<'\t';
        gets(ac_holder_name);
        break;

        case 4 : cout<<"\n Previous Age : "<<age;
        cout<<"\n\n Enter Current Age : "<<'\t';
        cin>>age;
        break;

        case 5 : cout<<"\n Previous Address : ";disp_address();
        cout<<"\n\n Enter Current Address : "<<'\t';
        gets(address);
        break;

        case 6 : cout<<"\n Previous Contact No. : "<<ph_no;
        cout<<"\n\n Enter Current Contact No. : "<<'\t';
        cin>>ph_no;
        break;

        case 7 : cout<<"\n Previously Linked Adhaar No. : "<<adhaar_no;
        cout<<"\n\n Enter Adhaar No. to be Linked : "<<'\t';
        cin>>adhaar_no;
        break;

        case 8 : cout<<"\n Previous E-mail ID : "<<email_id;
        cout<<"\n\n Enter Current E-mail ID : "<<'\t';
        cin>>email_id;
        break;

        default : cout<<"\n PLEASE ENTER A VALID CHOICE......\n PRESS ANY KEY TO CONTINUE.....";
  	    getch();
        m_arrow();
        modify_account();
    }

    m_arrow();
 
    cleardevice();
    gotoxy(1,4);

    cout<<"\n Branch                 :      "<<branch;
    cout<<"\n Account Type           :      "<<ac_type;
    cout<<"\n Account Holder Name    :      "<<ac_holder_name;
    cout<<"\n A/C no.                :      "<<ac_no;
    cout<<"\n Age                    :      "<<age;
    cout<<"\n Address                :      ";disp_address();
    cout<<"\n Contact No.            :      "<<ph_no;
    cout<<"\n Adhaar No.             :      "<<adhaar_no;
    cout<<"\n E-mail ID              :      "<<email_id;
    cout<<"\n Balance                :      "<<balance;

    if(choice==1)
        cout<<"\n \n \n Branch Changed Sucessfully";
    else if(choice==2)
        cout<<"\n \n \n Account Type Changed Successfully";
    else if(choice==3)
        cout<<"\n \n \n Account Holder Name Changed Successfully";
    else if(choice==4)
        cout<<"\n \n \n Age Changed Successfully";
    else if(choice==5)
        cout<<"\n \n \n Address Changed Successfully";
    else if(choice==6)
        cout<<"\n \n \n Contact No. Changed Successfully";
    else if(choice==7)
        cout<<"\n \n \n Adhaar No. Changed Successfully";
    else if(choice==8)
        cout<<"\n \n \n E-mail ID Changed Successfully";
}

customer c[MAX_SIZE];

void mainmenu()
{
    int choice,x;
    x=getmaxx();
    clr();
    settextstyle(BOLD_FONT,HORIZ_DIR,3);
    outtextxy(x/2-95,0,"MAIN MENU");
    line(0,50,x,50);


    gotoxy(10,7);
    cout<<"1. CREATE NEW ACCOUNT";

    gotoxy(10,9);
    cout<<"2. DEPOSIT AMOUNT";

    gotoxy(10,11);
    cout<<"3. WITHDRAW AMOUNT";

    gotoxy(10,13);
    cout<<"4. BALANCE ENQUIRY";

    gotoxy(10,15);
    cout<<"5. DISPLAY ACCOUNT DETAILS";

    gotoxy(45,7);
    cout<<"6. ALL ACCOUNT HOLDER";

    gotoxy(45,9);
    cout<<"7. CLOSE AN ACCOUNT";

    gotoxy(45,11);
    cout<<"8. MODIFY ACCOUNT DETAILS";

    gotoxy(45,13);
    cout<<"9. DISPLAY RECORDS FOR AN ACCOUNT";

    gotoxy(45,15);
    cout<<"10. SET NEW PASSWORD";

    gotoxy(37,17);
    cout<<"11. EXIT";

    cout<<"\n \n \n ENTER YOUR CHOICE: \t";
    cin>>choice;

    m_arrow();

    switch(choice)
    {

	    case 1 : add_account();
        break;

        case 2 : deposit();
        break;

        case 3 : withdraw();
        break;

        case 4 : bal_enquiry();
        break;
	    
        case 5 : disp_details();
        break;

        case 6 : disp_all_account();
        break;

        case 7 : del_account();
        break;

        case 8 : mod_account();
        break;

        case 9 : disp_rec();
        break;

        case 10 : s_pass();
        break;

        case 11 : exit(0);
        break;
        
        default : cout<<"\n PLEASE ENTER A VALID CHOICE......\n PRESS ANY KEY TO CONTINUE.....";
    	getch();
        m_arrow();
	    mainmenu();
    }
    getch();
}

void deposit()
{
    clr();
    int no,i,found,rec_no;
    unsigned long amount=0,balance=0;
    cout<<"\n \n \n Enter Your Account No. : "<<'\t';
    cin>>no;
    for(i=0;i<MAX_SIZE;i++)
    {
        found=c[i].search(no);
        if(found==1)
            break;
    }

    if(found==1)
    {
        cout<<"Enter the amount to be Deposited: "<<'\t';
        cin>>amount;

        rec_no=c[i].get_rec_no();

        balance=c[i].get_balance();

        c[i].r[rec_no].get_rec(amount,0,balance+amount);
        c[i].rec_no_incr();

        m_arrow();

        c[i].deposit_amount(amount);
    }
    else
        cout<<"\n\n\n Account Not Found.........";

    cout<<"\n\n\n\n PRESS ANY KEY TO CONTINUE........";
    getch();
    m_arrow();
    mainmenu();  
}

void withdraw()
{
    clr();
    int no,i,found,rec_no;
    unsigned long amount=0,balance=0;
    cout<<"\n \n \n Enter Your Account No. : "<<'\t';
    cin>>no;
    for(i=0;i<MAX_SIZE;i++)
    {
        found=c[i].search(no);
        if(found==1)
            break;
    }

    if(found==1)
    {
        cout<<"Enter the amount to be Withdrawed: "<<'\t';
        cin>>amount;

        m_arrow();

        balance=c[i].get_balance();
        if(amount<balance)
        {
            rec_no=c[i].get_rec_no();
            c[i].r[rec_no].get_rec(0,amount,balance-amount);
            c[i].rec_no_incr();
        }

        c[i].withdraw_amount(amount);
    }
    else
        cout<<"\n\n\n Account Not Found.........";

    cout<<"\n\n\n\n PRESS ANY KEY TO CONTINUE........";
    getch();
    m_arrow();
    mainmenu();
}

void bal_enquiry()
{
    clr();
    int no,i,found;
    cout<<"\n \n \n Enter Your Account No. : "<<'\t';
    cin>>no;
    for(i=0;i<MAX_SIZE;i++)
    {
        found=c[i].search(no);
        if(found==1)
            break;
    }

    if(found==1)
    {
        m_arrow();
        c[i].balance_enquiry();
    }
    else
        cout<<"\n\n\n Account Not Found.........";

    cout<<"\n\n\n\n PRESS ANY KEY TO CONTINUE........";
    getch();
    m_arrow();
    mainmenu();
}

void disp_rec()
{
    clr();
    int no,i,found,j,yc=4;;
    cout<<"\n \n \n Enter Your Account No. : "<<'\t';
    cin>>no;
    for(i=0;i<MAX_SIZE;i++)
    {
        found=c[i].search(no);
        if(found==1)
            break;
    }

    m_arrow();

    clr();

    if(found==1)
    {
        gotoxy(1,2);
        cout<<"REC NO.";

        gotoxy(12,2);
        cout<<"DEPOSIT";

        gotoxy(27,2);
        cout<<"WITHDRAW";

        gotoxy(45,2);
        cout<<"BALANCE";

        line(0,32,639,32);

        for(j=0;j<RECORDS;j++)
        {
            if(c[i].get_rec_no()==0)
            {
                gotoxy(25,15);
                cout<<"NO RECORDS FOUND FOR THIS ACCOUNT...";
                break;
            }
            c[i].r[j].disp_record(yc,j);
            yc++;
        }

    }
    else
        cout<<"\n\n\n Account Not Found.........";

    getch();
    m_arrow();
    mainmenu();
}

void mod_account()
{
    clr();
    int no,i,found;
    cout<<"\n \n \n Enter Your Account No. : "<<'\t';
    cin>>no;
    for(i=0;i<MAX_SIZE;i++)
    {
        found=c[i].search(no);
        if(found==1)
            break;
    }

    if(found==1)
    {
        m_arrow();
        c[i].modify_account();
    }
    else
        cout<<"\n\n\n Account Not Found.........";

    cout<<"\n\n\n\n PRESS ANY KEY TO CONTINUE........";
    getch();
    m_arrow();
    mainmenu();
}

void disp_details()
{
    clr();
    int no,i,found;
    cout<<"\n \n \n Enter Your Account No. : "<<'\t';
    cin>>no;
    for(i=0;i<MAX_SIZE;i++)
    {
        found=c[i].search(no);
        if(found==1)
            break;
    }

    if(found==1)
    {
        m_arrow();
        cout<<"                               Account Info. :                             \n \n \n";
        line(0,30,640,30);
        c[i].disp_ac_details();
    }
    else
        cout<<"\n\n\n Account Not Found.........";

    cout<<"\n\n\n\n PRESS ANY KEY TO CONTINUE........";
    getch();
    m_arrow();
    mainmenu();  
}

int search_acc()
{
    int no,i,found;
    cout<<"\n \n \n Enter Your Account No. : "<<'\t';
    cin>>no;
    for(i=0;i<MAX_SIZE;i++)
    {
        found=c[i].search(no);
        if(found==1)
            return 1;
    }
    if(found==0)
	return 0;

    return 0;
}

void del_account()
{
    clr();
    int no,i,found;
    cout<<"\n \n \n Enter Your Account No. : "<<'\t';
    cin>>no;
    for(i=0;i<MAX_SIZE;i++)
    {
        found=c[i].search(no);
        if(found==1)
            break;
    }

    m_arrow();

    if(found==1)
        c[i].delete_account();
    else
        cout<<"\n\n\n Account Not Found.........";

    cout<<"\n\n\n\n PRESS ANY KEY TO CONTINUE........";
    getch();
    m_arrow();
    mainmenu();
}

void add_account()
{
    clr();
    c[add_ac].get_cust();
    cout<<"\n \n Account Created Successfully.........";
    cout<<"\n \n Press Any Key To Continue.........";
    getch();
    m_arrow();

    clr();
    cout<<"\n The Account No. Assigned To You Is : \n"<<'\n'<<'\t'<<'\t'<<'\t';
    c[add_ac].disp_ac_no();
    cout<<"\n \n \n Press Any Key To Continue.........";
    getch();
    m_arrow();

    clr();
    c[add_ac].disp_ac_details();
    cout<<"\n \n \n Press Any Key To Continue.........";
    getch();
    m_arrow();

    add_ac++;

    mainmenu();
}

void disp_all_account()
{
    int i,yc=4;
    clr();

    gotoxy(1,2);
    cout<<"SR.NO.";

    gotoxy(12,2);
    cout<<"BRANCH NAME";

    gotoxy(27,2);
    cout<<"ACCOUNT NO.";

    gotoxy(42,2);
    cout<<"TYPE";

    gotoxy(55,2);
    cout<<"ACCOUNT HOLDER NAME";

    line(0,32,639,32);

    for(i=0;i<MAX_SIZE;i++)
    {
        if(add_ac==0)
        {
            gotoxy(33,15);
            cout<<"NO RECORDS FOUND...";
            break;
        }
        else
        {
            c[i].disp_all_ac(yc,i);
            yc++;
        }
    }
    getch();
    m_arrow();
    mainmenu();
}

void s_pass()
{
    clr();
    char p[10];
    cout<<"\n \n Enter Old Password \n  ( Enter \" EXIT \" To Go Back Without Changing The Password ) : "<<"\n  ";
    cin>>p;

    m_arrow();

    if(pass.check_pass(p)==1)
    {
	    pass.set_pass();
        cout<<"\n \n \n New Password Set Successfully......";
        cout<<"\n \n \n !!! For Security Reasons The System Will Reboot !!!";
        cout<<"\n \n Press Any Key To Cotinue.....";
        getch();
        m_arrow();
        restart();
    }
    else if(strcmpi(p,"EXIT")==0)
    {
        mainmenu();
    }
    else
    {
        cout<<"\n \n \n \n !! Invalid Password !!";
        cout<<"\n \n \n Press Any Key To Continue.....";
        getch();
        m_arrow();
        s_pass();
    }
}

void c_pass()
{
    clr();
    char p[10];
    int i=3;

    ABCD:
        cout<<"\n \n Enter The Password : "<<'\t';
        cin>>p;

        m_arrow();

        if(pass.check_pass(p)!=1)
        {
            if(i>1)
            {
                clr();
                cout<<"\n \n \n \n !! Invalid Password !!";
                cout<<"\n \n \n Press Any Key To Continue.....";
                getch();
                m_arrow();
                i--;
                goto ABCD;
            }
            else if(i==1)
            {
                clr();
                cout<<"\n \n !!!!! WARNING !!!!!";
                cout<<"\n \n !!! You Have Only Last Chance Left To Enter The Password !!!";
                cout<<"\n \n !!! If You Enter Wrong Password Again, The System Will Then Reboot !!!";
                cout<<"\n \n \n Press Any Key To Continue.....";
                getch();
                m_arrow();
                i--;
                goto ABCD;
            }
            else
            {
                clr();
                cout<<"\n \n !!! WARNING !!!";
                cout<<"\n \n !! You Entered Wrong Password !!";
                delay(2000);
                m_arrow();
                restart();
            }
        }
}

void restart()
{
    int i;
    
    for(i=5;i>=0;i--)
    {
        clr();
	cout<<"\n \n \n \t \t \t " ;
        if(i==5)
            cout<<"System Will Reboot In "<<i<<" seconds.";
        else if(i==4)
            cout<<"System Will Reboot In "<<i<<" seconds..";
        else if(i==3)
            cout<<"System Will Reboot In "<<i<<" second...";
        else if(i==2)
            cout<<"System Will Reboot In "<<i<<" second.";   
        else if(i==1)
            cout<<"System Will Reboot In "<<i<<" second..";
        else    
            cout<<"System Will Reboot In "<<i<<" second...";
        delay(1000);
    }
    clr();
    delay(1000);
    main();
}

void loading()
{
    int xl,p=0;
    int x=getmaxx();
    int y=getmaxy();
    xl=x/2-100;
    cleardevice();



    rectangle(x/2-100,y-98,x/2+100,y-75);

    while(xl<=x/2+100)
    {
	if(xl<x/2-60)
		outtextxy(x/2-165,y-120,"Please wait while the program is loading");

	else if(xl<x/2-20)
		outtextxy(x/2-165,y-120,"Please wait while the program is loading.");

	else if(xl<x/2+20)
		outtextxy(x/2-165,y-120,"Please wait while the program is loading..");

	else if(xl<x/2+60)
		outtextxy(x/2-165,y-120,"Please wait while the program is loading...");

	else
		outtextxy(x/2-165,y-120,"Please wait while the program is loading....");

	line(xl,y-98,xl,y-75);
	gotoxy(39,25);
	cout<<" "<<p/2<<" %";
	xl++;
	p++;
	delay(20);
    }
    delay(200);
}

int random()
{
    int r=rand();
    if(r<1000)
        r=r*10;
    else if(r>9999)
        r=r/10;

    return r;
}

void type(char *p)
{
    if(NULL==p)
	return;
    while(*p)
    {
	cout<<*p++<<'\xDB';
	delay(100);
	cout<<'\b'<<" "<<'\b';
	delay(100);
    }
}

void border()
{
    int i;
    int x=getmaxx();
    int y=getmaxy();
    int w=textwidth("*"),h=textheight("*");

    for(i=0;i<x;i = i+w+1)
    {
	    outtextxy(i,0,"*");
	    outtextxy(i,y-h,"*");
    }

    for(i=h;i<y;i=i+h+1)
    {
	    outtextxy(0,i,"*");
	    outtextxy(x-w,i,"*");
    }
}

void clr()
{
    cleardevice();
    gotoxy(2,2);
}

void m_arrow()
{
	for(int i=1;i<=80;i++)
	{
        delay(6);
        gotoxy(i,24);
        cout<<">";
    }

	for(i=1;i<=80;i++)
	{
        delay(6);
        gotoxy(i,24);
        cout<<" ";
    }
}

void main()
{
    int gd,gm;
    gd=DETECT;
    initgraph(&gd,&gm,"C:\\TC\\BGI");

    c_pass();

    loading();

    cleardevice();

    WELLCOME_SCREEN:
    {
        border();
        gotoxy(37,5);
        type("WELLCOME");
        gotoxy(40,7);
        type("TO");
        gotoxy(29,9);
        type("BANK  MANAGEMENT  SYSTEM");

        gotoxy(40,21);
        type("DEVELOPED  BY :-");
        gotoxy(50,23);
        type("SAHIL  GUPTA");
        gotoxy(50,24);
        type("ANURAG  NADKARNI");
        gotoxy(50,25);
        type("YASH  DHAWANE");
        delay(700);
    }

    mainmenu();

    getch();
    closegraph();
}
