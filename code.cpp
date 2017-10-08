#include <iostream>
#include <fstream>
#include <string>

using namespace std;
class patient{
public:
    int UID;
    string name;
    string specialist;
    
    void getdata();
    void showdata();
};

void patient::getdata(){
    int r=0;
    cout<<"\nenter the UID: ";
    cin>>UID;
    cout<<"\nenter name: ";
    cin>>name;
    cout<<"\nshould the patient be referred to higher tier health facility(enter 1 or 0): ";
    cin>>r;
    if(r){
        cin>>specialist;
    }
    else
        specialist="none";

}


void patient::showdata(){
    cout<<"\npatient name is: "<<name;
    cout<<"\nspecialist is: "<<specialist;

}
int main(){
    int again=1;
    while(again){
        int n;
        cout<<"\nenter 1 for new patient: \nenter 2 for case status: \nenter 3 for patients' records ";
        cin>>n;
        switch(n){
            case 1:{
                patient obj1;
                obj1.getdata();
                ofstream outfile;
                outfile.open("clinic.txt",ios::out );
                outfile.write((char*)&obj1,sizeof(obj1));
                outfile.close();
            }
            break;
            case 2:{
                patient obj2;
                int uid;
                cout<<"\nenter the patient UID: ";
                cin>>uid;
                fstream file;
                file.open("clinic.txt",ios::in | ios::out);
                file.read((char*)&obj2,sizeof(obj2));
                while(!file.eof()){
                    if(obj2.UID==uid){
                        cout<<"\nfound, patient name is: "<<obj2.name;
                        if(obj2.specialist!="none"){
                            patient objedit;
                            objedit=obj2; 
                            file.seekp(-sizeof(obj2),ios::cur);
                            cout<<"\npatient is referred to: "<<obj2.specialist;
                            cout<<"\npatients gets the earliest possible appointment ";
                            cout<<"\nclosing the case.......";
                            objedit.specialist="none";
                            file.write((char*)&objedit,sizeof(objedit)); 
                        }
                        else
                            cout<<"\npatient case is closed";
                        break;
                    }
                    file.read((char*)&obj2,sizeof(obj2));
                }

                file.close();
            }
            break;
            
            case 3:{
                patient obj3;
                int uid;
                cout<<"\nenter the patient UID: ";
                cin>>uid;
                ifstream infile;
                infile.open("clinic.txt",ios::in ); 
                infile.read((char*)&obj3,sizeof(obj3)); 
                infile.seekg(0,ios::beg);
                while(!infile.eof()){
                    if(obj3.UID==uid){
                        obj3.showdata();
                        break;
                    }
                    infile.read((char*)&obj3,sizeof(obj3));
                }

                infile.close();  
            }
            break;
            default:
                cout<<"\ninvalid input ";
        }
        cout<<"\nis there another patient(enter 1 or 0): ";
        cin>>again;
    }
    return 0;
}
        