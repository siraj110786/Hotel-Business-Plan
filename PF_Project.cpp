#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
using namespace std;

//********************* Declaration of Function ********************
void manualAppend(const char* filename, const string& newData);
int findAvailableRoom(char type);
bool adminLogin();
void bookRoom();
void bookEvent();
void removeCustomer();
void searchCustomer();
void loadBookedRooms();

//*************** Global Variables ****************
const int MAX=51;
bool rooms[MAX]={false}; // Room 1 to 50, index 0 is unused

int main(){
	loadBookedRooms();
    int choice;
	while(true){
        system("cls");
	cout<<"----------------------------------------------------------------------\n\n\n";
	cout<<"\t\t\tWelcome to Suhana Hotel\t\t\t\t\n\n\n";
	cout<<"----------------------------------------------------------------------\n\n";
        cout<<"\n1. Admin Login\n2. Customer Menu\n3. Exit\nEnter choice: ";
        cin>>choice;
       
             if(cin.fail()){
              cin.clear();
              cin.ignore(10000, '\n');
              cout<<"Invalid input. Please enter a number.\n";
              system("pause");
              continue;
}


        if(choice==1){
            if(!adminLogin()){
            	system("cls");
                cout<<"Invalid password.\n";
                system("pause");
                return -1;
            } else {
                int adminChoice;
                while(true){
                    system("cls");
                    cout<<"\nAdmin Menu:\n1. View History\n2. Search Customer\n3. Remove Customer\n4. Exit Admin\nEnter choice: ";
                    cin>>adminChoice;
                    
                     if(cin.fail()){
                       cin.clear();
                       cin.ignore(10000, '\n');
                       cout<<"Invalid input. Please enter a number.\n";
                       system("pause");
                       continue;
}

                    if(adminChoice==1){
                        system("cls");
                        ifstream file("hotel.txt");
                        string line;
                        cout<<"Serial \tName \t\tCNIC \t\tContact\t\t\tRoom\t\tArrival\t\tLeave\n";
                        while(getline(file, line)) 
						cout<<line<<endl;
                        file.close();
                        system("pause");
                    } else if(adminChoice==2){
                        system("cls");
                        searchCustomer();
                        system("pause");
                    } else if(adminChoice==3){
                        system("cls");
                        removeCustomer();
                        system("pause");
                    } else 
                    system("pause");
					break;
                }
            }
        }
        else if(choice==2){
            int custChoice;
            while(true){
                system("cls");
                cout<<"\nCustomer Menu:\n1. Book Room\n2. Book Event\n3. Back\nEnter choice: ";
                cin>>custChoice;
                             
                  if(cin.fail()){
                   cin.clear();
                   cin.ignore(10000, '\n');
                   cout<<"Invalid input. Please enter a number.\n";
                   system("pause");
                   continue;
           }

                if(custChoice==1){
                    system("cls");
                    bookRoom();
                    system("pause");
                } else if(custChoice==2){
                    system("cls");
                    bookEvent();
                    system("pause");
                } else 
				break;
            }
        }
        else if(choice==3){
        	cout<<"Thank you for coming........\n";
        	system("cls");
            break;
        }
        else {
            cout<<"\nInvalid Choice........\n";
            system("pause");
        }
    }
    return 0;
}

//********************* Manual append function ***************************

void manualAppend(const char* filename, const string& newData){
    ifstream inFile(filename);
    string oldData="", line;
    while(getline(inFile, line)){
        oldData+=line+"\n";
    }
    inFile.close();

    ofstream outFile(filename);
    outFile<<oldData;
    outFile<<newData;
    outFile.close();
}

//********************** Auto room assignment Function ****************************

int findAvailableRoom(char type){
    int start=1, end=0;
    	
	if(type=='S'){
	 start=1;
	 end=30;
	
	  } 
	  else if(type=='M'){ 
	     start=31; 
		 end=40; 
	
		 }
           else if(type=='L'){
		    start=41; end=50;
		    
		 }

    for(int i=start; i<=end; ++i){
        if(!rooms[i]){
            rooms[i]=true;
            return i;
        }
    }
    return -1;
}


//******************************* Admin login Function *********************************

bool adminLogin(){
    string pass;
    int count=3;
    system("cls");
    while(count>0){
        cout<<"Enter admin password: ";
        cin>>pass;
     
        if(pass=="admin123")
            return true;
        else {
            count--;
            system("cls");
            cout<<"Wrong password. Remaining attempts: "<<count<<endl;
        }
    }
    
    return false;
}


//*********************** Booking function *****************************

void bookRoom(){
    string name, cnic, contact, arrival, leave;
    char type;
    
    int serial=1;
    ifstream serialIn("serial.txt");
    if(serialIn>>serial)
        serialIn.close();
    else
        serial=1;

    ofstream serialOut("serial.txt");
    serialOut<<(serial+1);
    serialOut.close();
    
    cout<<"Enter Name: ";
    cin>>name;
    cout<<"Enter CNIC: ";
    cin>>cnic;
    cout<<"Enter Contact No: ";
    cin>>contact;
    cout<<"Enter Room Type (S=Simple 150$, M=Moderate 180$, L=Luxury 210$): ";
    cin>>type;

    int room=findAvailableRoom(type);
  
    if(room==-1){
        cout<<"No rooms available in selected category.\n";
        return;
    }

    cout<<"Enter Arrival Date (dd-mm-yyyy): ";
    cin>>arrival;
    
    leave="____";
                       

    ostringstream oss;
    oss<<serial<<".\t"<<name<<"\t\t"<<cnic<<"\t\t"<<contact<<"\t\t\t"<<room<<"\t\t"<<arrival<<"\t"<<leave<<"\n";
    string data=oss.str();

    manualAppend("hotel.txt", data);
    cout<<"Room booked successfully! Room No: "<<room<<endl;
}


//************************** Event booking Function ******************************

void bookEvent(){
    string name, day;
    cout<<"Enter your name: ";
    cin>>name;
    cout<<"Enter event day (dd-mm-yyyy): ";
    cin>>day;
    string entry=name+"\tEvent on: "+day+"\n";
    manualAppend("events.txt", entry);
    cout<<"Event booked successfully!\n";
}

//********************** Delete customer and archive Function ************************

void removeCustomer(){
    string targetCnic;
    cout<<"Enter CNIC of customer to remove: ";
    cin>>targetCnic;

    ifstream inFile("hotel.txt");
    ofstream tempFile("temp.txt");
    ofstream archive("archive.txt", ios::app);
    string line;
    bool found=false;
      while(getline(inFile, line)){
    istringstream iss(line);
    string word;
    bool match=false;

    while(iss>>word){
        if(word==targetCnic){
            match=true;
            break;
        }
    }

    if(match){
        archive<<line<<"\n";
        found=true;
    }else{
        tempFile<<line<<"\n";
    }
}

    inFile.close();
    tempFile.close();
    archive.close();

    remove("hotel.txt");
    rename("temp.txt", "hotel.txt");

    if(found) 
        cout<<"Customer removed and archived successfully.\n";
    else 
        cout<<"Customer not found.\n";
}


//************************* Search customer by CNIC Function ********************************

void searchCustomer(){
    string search;
    cout<<"Enter CNIC to search: ";
    cin>>search;
    ifstream file("hotel.txt");
    string line;
    bool found=false;
 while(getline(file, line)){
    istringstream iss(line);
    string word;
    bool match=false;

    while(iss>>word){
        if(word==search){
            match=true;
            break;
        }
    }

    if(match){
        cout<<line<<endl;
        found=true;
    }
}

    file.close();
    if(!found) 
        cout<<"Customer not found.\n";
}


//************************** Load already booked rooms ***********************************

void loadBookedRooms(){
    ifstream file("hotel.txt");
    string line;
    while(getline(file, line)){
        istringstream iss(line);
        string temp;
        int count=0, roomNum=0;
        while(iss>>temp){
            count++;
            if(count==5){
                try {
                    stringstream ss(temp);
                    ss>>roomNum;
                    if(roomNum>0 && roomNum<MAX)
                        rooms[roomNum]=true;
                } catch (...) {
				
				}
                break;
            }
        }
    }
    file.close();
}

//====================================== The End =================================================================





