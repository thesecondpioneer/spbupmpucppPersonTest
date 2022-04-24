
#ifndef T1_1_PERSONTEST_H
#define T1_1_PERSONTEST_H

#endif //T1_1_PERSONTEST_H
#include <string>
#include <vector>
using namespace std;

int getAttrNum(int index);
int getAttrSize();

class PersonTest{
private:
    string name;
    int test_num;
    vector <double> test_res;


public:
    PersonTest();
    PersonTest(ifstream* fin);

    string getName();

    int getTestNumber() const;

    vector<double> getTestResults();

    short compare(const PersonTest& b);

    void read();
    void read(ifstream* fin);
    void write();
    void write(ofstream* fout);

    bool check(vector <double> &ulim, vector <double> &dlim, string cname, int ctnum);
    double getProperty(vector<double> weights);

    friend bool operator< (const PersonTest A, const PersonTest B);
};

struct PersonNode{
    PersonNode();

    PersonTest data;
    PersonNode *next;
};

class PersonList{
private:
    PersonNode *head;
    PersonNode *end;
    int s;
    PersonNode *merge(PersonNode *firstNode, PersonNode *secondNode);
    PersonNode* middle(PersonNode *head);
public:
    PersonList();
    PersonList(int size);
    ~PersonList();
    int size();

    PersonNode *getHead();
    PersonNode *getEnd();
    void resetEnd();
    void setHead(PersonNode *nhead);

    void add(PersonTest&);
    PersonNode *sort(PersonNode *lhead);
    void addToSorted(PersonTest&);
    void write(vector <double> &ulim, vector <double> &dlim, string cname, int ctnum);
    void remove(vector <double> &ulim, vector <double> &dlim, string cname, int ctnum);
    PersonNode *insert(PersonTest&, int pos);
    void save(ofstream* fout);

    vector<vector <double>> getBallList(int tnum);

    friend ostream& operator<< (ostream &out, const PersonList &List);
    friend void operator>> (ifstream* fin, PersonList &List);
    PersonNode& operator[](const int index);
};