

#include<iostream>
#include<stdlib.h>
#include<conio.h>
#include<fstream>
#include<stdbool.h>
int Card_balance = 0;
int Debited_amt = 0;
int Credited_amt = 0;
bool receipt_rq = false;
#define max_attempt 3


using namespace std;


int c_balance;
bool is_valid_bool = false;
bool is_Admin_bool = false;
short check_attempt = 1;
bool is_tranferrable = false;

/**




            admin ------>
                            id  : 112233
                            pin : 123


    */
class Main_class;




class Main_class
{


public:

    long long c_num;
    string s_num;
    int c_cvc;
    string s_cvc;
    int c_balance;
    string s_balance;

    void set_card(long long num,int cvc,int bal); //done
    void check_card(); // done
    void is_valid(); // done
    void temp_edit_append();
    void temp_edit_erase();
    void is_Admin();
    friend void show_bal(Main_class myobj);
    void credit();
    int debit();
    void trans_detail();


    void check_attempted();

};Main_class temp_operator;

void Main_class::trans_detail()
{
    system("cls");
    for(int i=0;i<=31;i++)
    {
        cout<<"-";
        if(i==15)
        {
            cout<<endl;
            cout<<"    RECEIPT "<<endl;
        }

    }
    cout<<endl<<"CARD _NUM : "<<temp_operator.c_num<<endl;
    if(Credited_amt==0)
    {
        cout<<"Req. Amt  : "<<Debited_amt<<endl;
    }
    else{
        cout<<"Credit Amt : "<<Credited_amt<<endl;
    }

    cout<<endl<<"CURRENT BALANCE : "<<Card_balance;
    cout<<endl<<endl<<"ENTER ANY KEY TO LEAVE ";
    getch();
};




// Aquiring Details from input
void Main_class ::set_card(long long num,int cvc,int bal)
{

    this->c_num = num;
    this->c_cvc = cvc;
    this->c_balance = bal;


    this->s_num = to_string(num);
    this->s_cvc = to_string(cvc);
    this->s_balance = to_string(bal);
};



// Check Inputed Details
void Main_class ::check_card()
{
    system("cls");
    cout<<"Checking Begin...."<<endl;
    string retrived_num;
    string retrived_cvc;
    string retrived_bal;
    int i = 0;
    fstream file_handler("temp.txt");
    for(i = 0;i<50;i++)
    {
        int c_count = 0;
        getline(file_handler,retrived_num);
            if(retrived_num == s_num)
            {
                cout<<endl<<"ATTEMPT : "<<check_attempt<<endl;
                cout<<"CARD STATUS : VALID "<<endl;
                getline(file_handler,retrived_cvc);
                if(retrived_cvc == s_cvc)
                {

                    cout<<"LOGIN : SUCCESS "<<endl;
                    is_valid_bool = true;
                    i = 55;
                    cout<<"RETRIVING BALANCE : ";
                    getline(file_handler,retrived_bal);
                    c_balance = stof(retrived_bal);
                    cout<<endl<<"BALANCE -> "<<c_balance;
                    Card_balance = c_balance;

                    file_handler.close();

                }
            }
            else
            {
                cout<<i;
                cout<<endl<<"ATTEMPT : "<<check_attempt<<endl;
                cout<<"CARD STATUS : INVALID"<<endl;
                system("cls");
                if(i == 50)
                {

                    cout<<"SEARCH STATUS : Maximum Limit Exceeded ";
                    if(check_attempt<4)
                    {
                        cout<<endl<<"ATTEMPT : "<<check_attempt<<endl;
                        temp_operator.temp_edit_append();

                    }
                    else{
                        exit(0);
                    }
                }
            }
        }


};


// check whether Card Details is valid or not
void Main_class ::is_valid()
{
    if(is_valid_bool == false)
    {

        cout<<endl<<"ERROR OCCURED"<<endl;
        exit(1);
    }
    else
    {
        is_valid_bool = true;
    }
};




// Appends new card in temp file
void Main_class ::temp_edit_append()
{

    if(is_valid_bool == false)
    {

        cout<<"ERROR -> CARD DETAILS ARE NOT VALID " ;
        cout<<endl<<"LOGGING OUT "<<endl;
        exit(1);
    }
    else{
        temp_operator.is_Admin();
        if(is_Admin_bool == false)
        {
            cout<<endl<<"ERROR : INVALID DETAILS " <<endl;
            exit(1);
        }
        else
        {

            system("cls");
            cout<<"card  ---> "<<c_num<<endl;
            cout<<endl<<endl;
            fstream File_Handler;
            File_Handler.open("temp.txt",ios::app);
            string c_num_IN;
            string c_cvc_IN;
            cout<<"ENTER CARD NUMBER : ";
            cin>>c_num_IN;
            cout<<"ENTER CARD CVC    : ";
            cin>>c_cvc_IN;
            cout<<"ENTER BAL : ";
            string c_bal_IN;
            cin>>c_bal_IN;




        // INSERTION OF DETAILS


            File_Handler<<c_num_IN<<endl;
            File_Handler<<c_cvc_IN<<endl;
            File_Handler<<c_bal_IN<<endl;
            cout<<endl;
            File_Handler.close();
        }





    }


};


// checks if user is Admin or not
void Main_class ::is_Admin()
{

    cout<<" Authentication "<<endl;
    int Default_id=112233,In_id;
    int Default_pin=123,In_pin;
    cout<<"ENTER ID : ";
    cin>>In_id;
    cout<<endl<<"ENTER PIN : ";
    cin>>In_pin;
    if((In_id==Default_id)&&(In_pin==Default_pin))
    {

        cout<<"STATUS : Successed ";
        cout<<endl;
        is_Admin_bool = true;
    }
    else{
        cout<<"STATUS : Failed ";
        cout<<endl;
        exit(1);
    }

};



// Invokes Functions According to user's Input
void Choose_option()
{
    is_tranferrable = true;
    cout<<"SELECT OPERATION TO PERFORM : "<<endl<<"1. Credit Money "<<endl<<"2. Debit Money "<<endl<<"3. Add card ( requires admin authencation )"<<endl<<"4. Remove Card ( requires admin authencation )"<<endl;
    int Option;
    cin>>Option;
    switch(Option)
    {
    case 1:
        break;
    case 2:
        temp_operator.debit();
        break;
    case 3:
        temp_operator.temp_edit_append();
        break;
    case 4:
        temp_operator.temp_edit_erase();
        break;
    default:
        cout<<endl<<"INVALID OPTION SELECTED ";
        exit(1);
        break;
    }
};


// TO DEBIT MONEY
int Main_class ::debit()
{


    cout<<"ENTER AMOUNT TO DEBIT : ( bal : "<<Card_balance<<"  ) : ";
    int debt_amt;
    cin>>debt_amt;
    if(debt_amt<Card_balance)
    {
        cout<<endl<<debt_amt<<" is debited from your account "<<endl;
        Card_balance = Card_balance - debt_amt;

        cout<<endl<<" CURRENT BALANCE  ----> "<<Card_balance;
        c_balance = Card_balance;
        Debited_amt = debt_amt;
        cout<<endl<<"DO YOU WANT RECEIPT "<<endl<<"1.Yes"<<endl<<"Press other than 1 to leave "<<endl;
        int opt;
        cin>>opt;
        if(opt==1)
        {
            temp_operator.trans_detail();
        }
    }
    else{
        cout<<endl<<"INSUFFICIENT AMOUNT ";
        exit(0);
    }
};

// REMOVES CARD IF is_admin = true
void Main_class ::temp_edit_erase()
{

    /*

            ifstream handler - temp_file
            ofstream handler - cur_file


    */
    temp_operator.is_Admin();
    if(!is_Admin_bool==true)
    {

        cout<<endl<<"ERROR OCCURED " ;
        exit(0);
    }
    ifstream temp_file("temp.txt");
    ofstream cur_file("data.txt");

    string temp_data;
    system("cls");
    string cnum_to_delete;
    // Taking cvc & bal from txt file by reading file
    string ccvc_to_delete;
    string cbal_to_delete;
    cout<<"Enter details : ";
    cout<<"card number -> ";

    cin>>cnum_to_delete;cout<<endl;

    while(getline(temp_file,temp_data))
    {
        if(temp_data == cnum_to_delete)
        {
            for(int i=0;i!=1;i++)
            {
                getline(temp_file,ccvc_to_delete);
                getline(temp_file,cbal_to_delete);

            }
        }
        else if((temp_data != cnum_to_delete) && (temp_data != cnum_to_delete) && (temp_data!=cbal_to_delete) )
        {
            cur_file << temp_data <<endl;
        }
    }

    temp_file.close();
    cur_file.close();



};





/*
        ********************************************** MAIN **********************************************

*/

int main()
{

    long long I_num;
    int I_cvc;
    float bal;
    cout<<"ENTER CARD NUMBER : ";
    cin>>I_num;
    cout<<endl<<"ENTER CARD CVC : ";
    cin>>I_cvc;
    Main_class class_handler;
    class_handler.set_card(I_num,I_cvc,bal);
    class_handler.check_card();

    if(is_valid_bool == false)
    {

        cout<<"INVALID DETAILS "<<endl;
        exit(1);
    }
    else{
        cout<<endl<<"CONTINUE ( 0 ) OR EXIT ( 1- 9)   -> ";
        int Con_exit;
        cin>>Con_exit;
        if(Con_exit==0)
        {

            system("cls");
            Choose_option();
        }
        else{
            cout<<endl<<"LOGGING OUT ......" ;
            exit(1);
        }
    }
    cout<<endl<<endl;
    cout<<"PRESS ANY KEY TO EXIT "<<endl;
    getch();
    return 0;
};

    /***************************************************** --------------- /*****************************************************/
