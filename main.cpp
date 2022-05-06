#include <bits/stdc++.h>
#define all(v) ((vec).begin()), ((vec).end())
#define sz(v)  (int (v).size())
#define endl '\n'
using namespace std;

const int MAX_SPECIALIZATION = 20 ;
const int MAX_QUEUE = 5 ;

string names[MAX_SPECIALIZATION+1][MAX_QUEUE] ;
int status [MAX_SPECIALIZATION][MAX_QUEUE] ; // 0 regular , 1 urgent
int queue_length[MAX_SPECIALIZATION+1];
void shift_right(int spec, string names_sp[], int status_sp[])
{
    int len = queue_length[spec] ;
    for (int i= len -1 ; i >= 0 ;--i){
        names_sp[i+1] = names_sp[i];
        status_sp[i-1] = status_sp[i];
    }
    queue_length[spec]++;
}
void shift_left(int spec, string names_sp[], int status_sp[])
{
    int len = queue_length[spec];
    for (int i = 1; i < len ;++i)
    {
        names_sp[i-1] = names_sp[i];
        status_sp[i-1] = status_sp[i];
    }
    queue_length[spec]--;
}

bool add_new_patient()
{
    int spec , st ;
    string name ;

    cout << "Enter specialization, name, status: "<<endl;
    cin >> spec >> name >> st ;

    int pos = queue_length[spec] ;
    if (pos >= MAX_QUEUE){
        cout << "Sorry we can't add more patients for this specialization"<<endl;
        return false ;
    }

    if (st == 0){
        names[spec][pos] = name ; // add to end , regular
        status[spec][pos] = st ;
        queue_length[spec]++;
    }else // urgent add first shift then add
    {
        shift_right(spec, names[spec], status[spec]);
        names[spec][0] = name ;
        status[spec][0] = st ;
    }
    return true ;

}

void print_patient(int spec, string names_sp[], int status_sp[])
{
    int len = queue_length[spec] ;
    if (len == 0)
        return ;

    cout << "There are "<< len << " patients in specialization " << spec <<endl;
    for (int i = 0 ;i < len ;++i)
    {
        cout << names_sp[i] << " ";
        if (status_sp[i])
            cout << "Urgent" << endl;
        else cout << "Regular" << endl;
    }
    cout << endl ;
}
void print_patients()
{
    cout << "*********************************"<<endl;
    for (int spec = 0 ; spec < MAX_SPECIALIZATION ; ++spec)
    {
        print_patient(spec, names[spec], status[spec]);
    }
}

void get_next_patient()
{
    int spec ;
    cout << "Enter specialization: ";
    cin >> spec ;
    int len = queue_length[spec] ;
    if (len == 0)
    {
        cout << "NO patients at the moment ... have a rest, Dr" << endl;
        return ;
    }
    cout << names[spec][0] << "please go with the Dr" ;
    shift_left(spec, names[spec], status[spec]);
}

int menu()
{
    int choice = -1 ;
    while (choice == -1)
    {
        cout << endl <<"Enter Your Choice:" << endl;
        cout << "1) Add new patient" << endl;
        cout << "2) Print all patients" << endl;
        cout << "3) Get next patient" << endl;
        cout << "4) Exit" << endl;

        cin >> choice ;
        if (!(1 <= choice && choice <= 4)) {
			cout << "Invalid choice .. Please Try again\n";
			choice = -1 ;
		}
    }
}

void hospital_system()
{
    while (true){
    int choice = menu();

    if (choice == 1)
        add_new_patient();
    else if (choice == 2)
        print_patients();
    else if (choice == 3)
        get_next_patient();
    else
        break;
    }
}


int main(){

    hospital_system();
	return 0;

}
