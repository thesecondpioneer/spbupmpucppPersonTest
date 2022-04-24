#include <iostream>
#include <vector>
#include <string>
#include <windows.h>
#include <fstream>
#include "PersonTest.h"
#include <map>
#include <limits>
using namespace std;


int main() {
    PersonTest p1, p2;
    PersonList list(0);
    int cnum = 0;
    vector<double> ulim(0),dlim(0);
    string command;
    map<string, int> commands = {{"-help", 1}, {"-clear", 2}, {"-load", 3}, {"-save", 4}, {"-add", 5},
                                {"-sort", 6}, {"-find", 7}, {"-delete", 8}, {"-exit", 9}, {"-write",10},
                                {"-insert", 11},{"-testinfo",12}};
   // ifstream fin("E:/All/Work/Code/SPbU/OsP/2sem/T1_1/persondata.txt"),listfin("E:/All/Work/Code/SPbU/OsP/2sem/T1_1/personlistdata.txt");
    cout << "Welcome to the PersonTest and PersonList showcase program, type \"-help\" to see the command list" << endl;
    while(cin){
        cin >> command;
        try {
            cnum = commands.at(command);
        }
        catch (out_of_range) {
            cnum = -1;
        }
        switch (cnum){
            case -1:{
                cout << "Incorrect command. Please type in \"-help\" to see the command list." << endl;
                break;
            }
            case 1:{
                cout << "-clear - Clear the list." << endl <<
                "-load <file path> - Load the list from the file." << endl <<
                "-write - See the whole list" << endl <<
                "-save <file path> - Save the list to the file." <<  endl <<
                "-add - Add the object to the list." <<  endl <<
                "-sort - Sort the list lexicographically." <<  endl <<
                "-find - Find all the list elements that satisfy the provided terms." <<  endl <<
                "-delete - Delete all the list elements that satisfy the provided terms." << endl <<
                "-insert - Insert the person into a specified position"
                "-exit - Exit the program." << endl;
                break;
            }
            case 2:{
                list.~PersonList();
                cout << "The list was cleared succesfully." << endl;
                break;
            }
            case 3:{
                string fpath;
                cin >> fpath;
                ifstream fin(fpath);
                if (fin.is_open()) {
                    list.remove(ulim, dlim, "-", -1);
                    &fin >> list;
                    cout << list;
                    break;
                }
                else{
                    cout << "Incorrect file path. Please try again." << endl;
                    break;
                }
            }
            case 4:{
                string fpath;
                cin >> fpath;
                ofstream fout(fpath);
                if(fout.is_open()){
                    list.save(&fout);
                    cout << "The list has been succesfully saved to " << fpath << endl;
                    break;
                }
                else{
                    cout << "Incorrect file path. Please try again." << endl;
                    break;
                }
            }
            case 5:{
                PersonTest a;
                list.add(a);
                list.getEnd()->data.read();
                break;
            }
            case 6:{
                PersonNode *shead;
                shead = list.sort(list.getHead());
                list.setHead(shead);
                list.resetEnd();
                cout << "The list was succesfully sorted." << endl << list;
                break;
            }
            case 7:{
                ulim.resize(0);
                dlim.resize(0);
                string cname;
                int ctnum;
                double e;
                cout << ">Enter the test subject's name. " <<
                    "Ultimately, go with \"-\", if you don't want to search by this parameter." << endl << ">";
                while(!cin){                             //Filtering all the unwanted user inputs
                    cin.clear();
                    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    cout << ">Enter the test subject's name. " <<
                         "Ultimately, go with \"-\", if you don't want to search by this parameter." << endl << ">";
                    cin >> cname;
                }
                cout << ">Enter the test number." <<
                    "Ultimately, go with \"-1\", if you don't want to search by this parameter." << endl << ">";
                while(!cin){                             //Filtering all the unwanted user inputs
                    cin.clear();
                    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    cout << ">Enter the test number." <<
                         "Ultimately, go with \"-1\", if you don't want to search by this parameter." << endl << ">";
                    cin >> ctnum;
                }
                if((ctnum >=0) and (ctnum <=getAttrSize()-1) and (getAttrNum(ctnum)!=0)) {
                    cout << ">Enter the upper limiter vector (" << getAttrNum(ctnum) << " elements separated by space)." <<
                        "Ultimately, go with \"-1\", if you don't want to search by this parameter." << endl << ">";
                    for(int i = 0; i < getAttrNum(ctnum); i++){
                        while(!cin){                             //Filtering all the unwanted user inputs
                            cin.clear();
                            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                            cin >> e;
                        }
                        ulim.push_back(e);
                        if (e==-1){
                            ulim.resize(0);
                            break;
                        }
                    }
                    cout << ">Enter the lower limiter vector (" << getAttrNum(ctnum) << " elements separated by space)." <<
                         "Ultimately, go with \"-1\", if you don't want to search by this parameter." << endl << ">";
                    for(int i = 0; i < getAttrNum(ctnum); i++){
                        while(!cin){                             //Filtering all the unwanted user inputs
                            cin.clear();
                            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                            cin >> e;
                        }
                        dlim.push_back(e);
                        if (e==-1){
                            dlim.resize(0);
                            break;
                        }
                    }
                }
                bool sww = false;
                for(int i = 0; i < list.size(); i++){
                    if(list[i].data.check(ulim,dlim,cname,ctnum)){
                        list[i].data.write();
                        sww = true;
                    }
                }
                if(!sww){
                    cout << "No matching elements were found in the list." << endl;
                }
                break;
            }
            case 8:{
                string cname;
                int ctnum;
                double e;
                cout << ">Enter the test subject's name. " <<
                     "Ultimately, go with \"-\", if you don't want to search by this parameter." << endl << ">";
                while(!cin){                             //Filtering all the unwanted user inputs
                    cin.clear();
                    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    cout << ">Enter the test subject's name. " <<
                         "Ultimately, go with \"-\", if you don't want to search by this parameter." << endl << ">";
                    cin >> cname;
                }
                cout << ">Enter the test number." <<
                     "Ultimately, go with \"-1\", if you don't want to search by this parameter." << endl << ">";
                while(!cin){                             //Filtering all the unwanted user inputs
                    cin.clear();
                    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    cout << ">Enter the test number." <<
                         "Ultimately, go with \"-1\", if you don't want to search by this parameter." << endl << ">";
                    cin >> ctnum;
                }
                if((ctnum >=0) and (ctnum <=getAttrSize()-1) and (getAttrNum(ctnum)!=0)) {
                    cout << ">Enter the upper limiter vector (" << getAttrNum(ctnum) << " elements separated by space)." <<
                         "Ultimately, go with \"-1\", if you don't want to search by this parameter." << endl << ">";
                    for(int i = 0; i < getAttrNum(ctnum); i++){
                        while(!cin){                             //Filtering all the unwanted user inputs
                            cin.clear();
                            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                            cin >> e;
                        }
                        ulim.push_back(e);
                        if (e==-1){
                            ulim.resize(0);
                            break;
                        }
                    }
                    cout << ">Enter the lower limiter vector (" << getAttrNum(ctnum) << " elements separated by space)." <<
                         "Ultimately, go with \"-1\", if you don't want to search by this parameter." << endl << ">";
                    for(int i = 0; i < getAttrNum(ctnum); i++){
                        while(!cin){                             //Filtering all the unwanted user inputs
                            cin.clear();
                            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                            cin >> e;
                        }
                        dlim.push_back(e);
                        if (e==-1){
                            dlim.resize(0);
                            break;
                        }
                    }
                }
                int chck = list.size();
                list.remove(ulim,dlim,cname,ctnum);
                if(list.size()==chck){
                    cout << "Nothing was deleted from the list." << endl;
                }
                else{
                    cout << "Successfully deleted " << chck-list.size() << "elements." << endl;
                }
                break;
            }
            case 9:{
                return 0;
            }
            case 10:{
                cout << list << endl;
                break;
            }
            case 11:{
                int pos;
                PersonTest a;
                while(!cin){                             //Filtering all the unwanted user inputs
                    cin.clear();
                    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    cin >> pos;
                }
                list.insert(a,pos-1)->data.read();
                break;
            }
            case 12:{
                int tnum;
                cin >> tnum;
                while(!cin){                             //Filtering all the unwanted user inputs
                    cin.clear();
                    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    cin >> tnum;
                }
                vector <vector <double>> s = list.getBallList(tnum);
                cout << "{";
                if (!s.empty()) {
                    for (int i = 0; i < s.size() - 1; i++) {
                        cout << "{";
                        for (int j = 0; j < s[i].size() - 1; j++) {
                            cout << s[i][j] << ", ";
                        }
                        cout << s[i][s[i].size() - 1] << "}, ";
                    }
                    cout << "{";
                    for (int j = 0; j < s[s.size() - 1].size() - 1; j++) {
                        cout << s[s.size() - 1][j] << ", ";
                    }
                    cout << s[s.size() - 1][s[s.size() - 1].size() - 1] << "}";
                }
                cout << "}" << endl;
                break;
            }
        }
    }
}
