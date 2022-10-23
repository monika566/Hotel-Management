#include <fstream>
#include <conio.h>
#include <string.h>
#include <iomanip>
#include <iostream>

using namespace std;

class Hotel
{
    int room_number;
    char name[30];
    char address[50];
    char phone[10];
    public:
    void add_customer()
    {
        cout<<"\nEnter the room number: ";
        cin>>room_number;
        cout<<"\nEnter the customer name: ";
        cin.ignore();
        cin.getline(name,30);
        cout<<"\nEnter the customer address: ";
        cin.ignore();
        cin.getline(address,50);
        cout<<"\nEnter the customer's phone number: ";
        cin.ignore();
        cin.getline(phone,10);
        cout<<"\t\t\nCustomer added succesfully....";
        
    }
    void show_customer()
    {
        cout<<"\nRoom Number :"<<room_number;
        cout<<"\nCustomer's Name :"<<name;
        cout<<"\nCustomer's Address :"<<address;
        cout<<"\nCustomer;s Phone Number :"<<phone;
    }
    void modify_customer_record()
    {
        cout<<"\nRoom Number "<<room_number;
        cout<<"\nModify Customer's Name :";
        cin.ignore();
        cin.getline(name,30);
        cout<<"\nModify Customer's Address: ";
        cin.ignore();
        cin.getline(address,50);
        cout<<"\nModify Customer's Phonenumber: ";
        cin.ignore();
        cin.getline(phone,10);
    }
    int getRoomNumber()
    {
        return room_number;
    }
    char * getName()
    {
        return name;
    }
    char * getAddress()
    {
        return address;
    }
    char *getPhone()
    {
        return phone;
    }
    void report()
    {
        cout<<room_number<<setw(10)<<name<<setw(20)<<address<<setw(20)<<phone<<endl;
    }
};

fstream fp;
Hotel h;
void save_customer()
{
    
    int option;
    fp.open("hotel.dat",ios::out|ios::app);
    do{
        h.add_customer();
        fp.write((char*)&h,sizeof(Hotel));
        cout<<"\nPress 1 to add more customers ";
        cout<<"\nPress 2 to return to main menu \n";
        cout<<"Option: ";
        cin>>option;

    }
    while(option==1);
    fp.close();
}
void display_a_customer(int r_number){
   
    cout<<"\nCUSTOMER DETAILS\n";
    int check=0;
    fp.open("hotel.dat",ios::in);
    while(fp.read((char*)&h,sizeof(Hotel)))
    {
        if(h.getRoomNumber()==r_number){
            h.show_customer();
            check=1;
        }
    }
    fp.close();
    if (check==0)
    cout<<"\nCustomer does not exist ";
    getch();
}
void modify_customer(){
    
    int r_number;
    int found=0;
    cout<<"\n\nMODIFY CUSTOMER'S RECORD ";
    cout<<"\nEnter the room number ";
    cin>>r_number;
    fp.open("hotel.dat",ios::in|ios::out);
    while(fp.read((char*)&h,sizeof(Hotel))&& found==0)
    {
        if(h.getRoomNumber()==r_number){
            h.show_customer();
            cout<<"\nEnter customer's new information "<<endl;
            h.modify_customer_record();
            int pos=1*sizeof(h);
            fp.seekp(pos,ios::cur);
            fp.write((char*)&h,sizeof(Hotel));
            cout<<"\n\n\tRecord Updated Successfully...";
            found=1;
        }
    }
    fp.close();
    if(found==0)
    cout<<"\n\nRecord Not Found ";
    getch();
}
void delete_customer(){
    
    char r_number;
    int flag=0;
    cout<<"\n\n\n\tDELETE CUSTOMER ";
    cout<<"\nENTER THE ROOM NUMBER OF CUSTOMER YOU WANT TO DELETE ";
    cin>>r_number;
    fp.open("hotel.dat",ios::in|ios::out);
    fstream fp2;
    fp2.open("Temp.dat",ios::out);

    fp.seekg(0,ios::beg);
    while(fp.read((char*)&h,sizeof(Hotel))){
        if(h.getRoomNumber()==r_number){
            fp2.write((char*)&h,sizeof(Hotel));
        }
        else 
        flag=1;
    }
    fp2.close();
    fp.close();
    remove("hotel.dat");
    rename("Temp.dat","hotel.dat");
    if(flag==1)
    cout<<"\n\n\tRecord Deleted ";
    else
    cout<<"\n\nRecord not found ";
    getch();
}
void display_all_customer(){
    
    fp.open("hotel.dat",ios::in);
    if(!fp){
        cout<<"ERROR!!! FILE COULD NOT BE OPEN ";
        getch();
        return;
    }
    cout<<"\n\n\tCUSTOMER LIST\n\n";
    cout<<"==================================================================\n";
    cout<<"\tROOM NUMBER."<<setw(10)<<"NAME"<<setw(20)<<"ADDRESS"<<setw(20)<<"PHONE"<<endl;
    cout<<"===================================================================\n";
    while(fp.read((char*)&h,sizeof(Hotel))){
        h.report();
    }
    fp.close();
    getch();
}
void main_menu(){
    int option;
    for(;;)
    {
        cout<<"\n\t\t#######################################################";
        cout<<"\n\t\tPress 1 to book a room ";
        cout<<"\n\t\tPress 2 to display all rooms alloted ";
        cout<<"\n\t\tPress 3 to display specific customer record ";
        cout<<"\n\t\tPress 4 to modify customer record ";
        cout<<"\n\t\tPress 5 to delete customer record ";
        cout<<"\n\t\tPress 6 to exit ";
        cout<<"\n\t\t#######################################################";
        cout<<"\n\t\tOption: ";
        cin>>option;
        switch(option){
            case 1:
            save_customer();
            
            break;
            case 2:
            display_all_customer();
            
            break;
            case 3:
            int r_number;
           
            cout<<"\n\nPlease enter customer's room number ";
            cin>>r_number;
            display_a_customer(r_number);
            break;
            case 4:
            modify_customer();
            
            break;
            case 5:
            delete_customer();
            
            break;
            case 6:
            exit(0);
            break;
            default:
            cout<<"\a";
        }
    }
}
void intro(){
    system("white");
    system("cls");
} 
int main(int argc,char *argv[]){
    intro();
    main_menu();
    return 0;
}
