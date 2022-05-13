#include <iostream>
#include <vector>
#include <string>
#include <windows.h>
#include <fstream>
#include <limits>
#include "PersonTest.h"
vector<int> test_an;

int getAttrNum(int index){
    return test_an[index];
}
int getAttrSize(){
    return test_an.size();
}
//PersonTest section

string PersonTest::getName() {
    return this->name;
}

int PersonTest::getTestNumber() const {
    return test_num;
}

vector<double> PersonTest::getTestResults(){
    return test_res;
}

short PersonTest::compare(const PersonTest& b){
    if (this -> name != b.name){
        return ((this->name > b.name) * 2 -1);       //Simple math trick using the way c++ operates with booleans: 0 * 2 - 1 = 0; 1 * 2 - 1 = 1
    }
    else{
        if (b.test_num != this->test_num){
            return ((this->test_num > b.test_num) * 2 -1);
        }
        else return 0;
    }
}
void PersonTest::read(){
    cout << "-----------------------------------------------------------------" << '\n';
    cout << ">Type in the name of the test subject:\n" << ">";
    cin >> this -> name;
    while(!cin){                                    //Filtering all the unwanted user inputs
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << ">Type in the name of the test subject:\n" << ">";
        cin >> this -> name;
    }
    cout << ">Type in the number of the test taken:\n" << ">";
    cin >> this->test_num;
    while((!cin) or (this -> test_num < 0)) {      //Filtering all the unwanted user inputs
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << ">Type in the number of the test taken:\n" << ">";
        cin >> this->test_num;
    }
    if (test_an.size() < test_num+1){
        test_an.resize(test_num+1);
    }
    if (test_an[test_num] == 0){
        cout << ">Type in the number of the test attributes:\n" << ">";
        cin >> test_an[test_num];
        while((!cin) or (test_an[test_num]<=0)){    //Filtering all the unwanted user inputs
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout << ">Type in the number of the test attributes:\n" << ">";
            cin >> test_an[test_num];
        }
    }
    test_res.resize(test_an[test_num]);
    cout << ">Type in the test results (in points) separated by space:\n" << ">";
    for (int i = 0; i < test_an[test_num]; i++){
        cin >> test_res[i];
        while(!cin){                             //Filtering all the unwanted user inputs
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout << ">Type in the test results (in points) separated by space:\n" << ">";
            cin >> test_res[i];
        }
    }
    cout << "Initialization complete.\n" << "-----------------------------------------------------------------" << '\n';
}
void PersonTest::read(ifstream* fin){
    double e;
    if (fin->is_open()){
        *fin >> name;
        *fin >> test_num;
        if (test_an.size() < test_num+1){
            test_an.resize(test_num+1);
        }
        test_res.resize(0);
        while(*fin){
            *fin >> e;
            if((e!=INT_MAX) and (e!=-1)) {
                test_res.push_back(e);
            }
            if(e == -1){break;}
            e = INT_MAX;
        }
        if (test_an[test_num] == 0){
            test_an[test_num] = test_res.size();
        }
        else{
            if (test_res.size() >= test_an[test_num]){
                test_res.resize(test_an[test_num]);
            }
            else{
                cout << "Incorrect file is provided!" << endl;
                name = "NoName";
                test_num = 0;
                test_res.resize(1);
            }
        }
    }
    else{
        cout << "Unable to open the file.";
    }
}
void PersonTest::write(){
    cout << "-----------------------------------------------------------------" << '\n';
    cout << "Test subject name: " << name << '\n';
    cout << "Test number: " << test_num << '\n';
    cout << "Test results: ";
    for (auto i:test_res){
        cout << i << ' ';
    }
    cout << '\n' << "-----------------------------------------------------------------" << '\n' ;
}
void PersonTest::write(ofstream* fout){
    if (fout->is_open()){
        *fout << name << ' ' << test_num << ' ';
        for (auto i:test_res){
            *fout << i << ' ';
        }
        *fout << -1;
    }
    else{
        cout << "Unable to open the file";
    }
}
bool PersonTest::check(vector <double> &ulim, vector <double> &dlim,const string cname, const int ctnum){
    if(ulim.size()<test_res.size()){
        ulim.resize(test_res.size(),INT_MAX);
    }
    if(dlim.size()<test_res.size()){
        dlim.resize(test_res.size(),INT_MAX);
    }
    if((cname != this->name) and (cname != "-")){
        return false;
    }
    if((ctnum != this->test_num) and (ctnum != -1)){
        return false;
    }
    for (int i = 0; i < test_res.size(); i++) {
        if ((test_res[i] < dlim[i]) and (dlim[i]!=INT_MAX) ){
            return false;
        }
    }
    for (int i = 0; i < test_res.size(); i++) {
        if (test_res[i] > ulim[i]){
            return false;
        }
    }
    return true;
}
double PersonTest::getProperty(vector<double> weights){
    double property_sum = 0;
    for(int i = 0; i < test_res.size(); i++){
        property_sum += test_res[i]*weights[i];
    }
    return(property_sum);
}

PersonTest::PersonTest() {
    this -> name = "NoName";
    this -> test_num = 0;
    this -> test_res = vector<double>(1);
}
PersonTest::PersonTest(ifstream* fin) {
    this -> read(fin);
}

bool operator< (PersonTest A, PersonTest B){
    switch(A.compare(B)){
        case -1:{
            return true;
        };
        case 0:{
            return false;
        }
        case 1:{
            return false;
        }
    }
}

bool operator<= (PersonTest A, PersonTest B){
    switch(A.compare(B)){
        case -1:{
            return true;
        };
        case 0:{
            return true;
        }
        case 1:{
            return false;
        }
    }
}

bool operator> (PersonTest A, PersonTest B){
    switch(A.compare(B)){
        case -1:{
            return false;
        };
        case 0:{
            return false;
        }
        case 1:{
            return true;
        }
    }
}

bool operator>= (PersonTest A, PersonTest B){
    switch(A.compare(B)){
        case -1:{
            return false;
        }
        case 0:{
            return true;
        }
        case 1:{
            return true;
        }
    }
}


//PersonList section

PersonNode::PersonNode() {
    this->next = nullptr;
}

PersonList::PersonList() {
    this->head = nullptr;
    this->end = nullptr;
    this->s = 0;
}

PersonList::PersonList(int size) {
    this->head = nullptr;
    this->s = 0;
    PersonTest a;
    for (int i = 0; i < size; i++){
        this->add(a);
    }
}

PersonList::~PersonList(){
    vector<double> ulim,dlim;
    this->remove(ulim,dlim,"-",-1);
}

void PersonList::add(PersonTest& person) {
    PersonNode *node = new(PersonNode);
    node->data = person;
    if(this->head == nullptr){
        this->head = node;
        this->end = node;
        this->head->next = nullptr;
    }
    else{
        end->next = node;
        this->end = node;
        this->end->next = nullptr;
    }
    s++;
}

void PersonList::write(vector <double> &ulim, vector <double> &dlim, string cname, int ctnum) {
    PersonNode *current = this->head;
    while(current!=nullptr){
        if(current->data.check(ulim, dlim, cname, ctnum)){
            current->data.write();
        }
        current = current->next;
    }
}

void PersonList::remove(vector<double> &ulim, vector<double> &dlim, string cname, int ctnum) {
    while((this->head != nullptr) and (this->head->data.check(ulim, dlim, cname, ctnum))){
        auto* temp = this->head->next;
        delete(this->head);
        this->head = temp;
        this->s--;
    }
    if (this->head == nullptr){return;}
    PersonNode *current = this->head;
    while((current!=nullptr) and (current->next!=nullptr)){
        if(current->next->data.check(ulim, dlim, cname, ctnum)){
            auto* temp = current->next->next;
            delete(current->next);
            current->next = temp;
            this->s--;
        }
        else {
            current = current->next;
        }
    }
}

vector<vector <double>> PersonList::getBallList(int tnum){
    PersonNode *current = this->head;
    vector<vector<double>> res;
    while(current!=nullptr){
        if(current->data.getTestNumber() == tnum){
            res.push_back(current->data.getTestResults());
        }
        current = current->next;
    }
    return res;
}

ostream& operator<< (ostream &out, const PersonList &List){
    PersonNode *current = List.head;
    out <<"{";
    if (current == nullptr){
        out << "}";
    }
    while(current!=nullptr){
        out << "[\"" << current->data.getName() << "\", " << current->data.getTestNumber() << ", {";
        for(int i = 0; i < current->data.getTestResults().size()-1; i++){
            out << current->data.getTestResults()[i] << ", ";
        }
        if(current->next!=nullptr) {
            out << current->data.getTestResults()[current->data.getTestResults().size() - 1] << "}], ";
        }
        else{
            out << current->data.getTestResults()[current->data.getTestResults().size()-1] <<"}]}"<<endl;
        }
        current = current->next;
    }
    return out;
}

void operator>> (ifstream* fin, PersonList &List){
    while((*fin) and (fin->peek()!=EOF)){
        PersonTest a(fin);
        List.add(a);
    }
}

int PersonList::size() {
    return this->s;
}

PersonNode& PersonList::operator[](const int index) {
    if ((index > this->s - 1) or (index < 0)){
        throw "OUT_OF_BOUNDS";
    }
    else{
        PersonNode *current = this->head;
        for(int i = 0; i < index; i++){
            current = current->next;
        }
        return *current;
    }
}

PersonNode *PersonList::merge(PersonNode *firstNode, PersonNode *secondNode) {
    PersonNode* temp = new(PersonNode);
    PersonNode* thead;
    thead = temp;
    while ((firstNode != nullptr) and (secondNode != nullptr)){
        if (firstNode->data <= secondNode->data){
            temp->next = firstNode;
            firstNode = firstNode->next;
        }
        else{
            temp->next = secondNode;
            secondNode = secondNode->next;
        }
        temp = temp->next;
    }
    while(firstNode != nullptr){
        temp->next = firstNode;
        firstNode = firstNode->next;
        temp = temp->next;
    }
    while(secondNode != nullptr){
        temp->next = secondNode;
        secondNode = secondNode->next;
        temp = temp->next;
    }
    return thead->next;
}

PersonNode* PersonList::middle(PersonNode *head){
    PersonNode *slow = head;
    PersonNode *fast = head->next;
    while(slow->next != nullptr and (fast!=nullptr and fast->next!=nullptr)) {
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}

PersonNode *PersonList::sort(PersonNode *lhead) {
    if((lhead->next == nullptr) or (lhead == nullptr)){
        return lhead;
    }
    PersonNode *mid = nullptr;
    PersonNode *lhead2 = nullptr;
    mid = middle(lhead);
    lhead2 = mid->next;
    mid->next = nullptr;
    PersonNode *sortedhead = merge(sort(lhead),sort(lhead2));
    return sortedhead;
}

void PersonList::addToSorted(PersonTest& person) {
    PersonNode *current = this->head;
    for(int i = 0; i < this->size(); i++){
        if(person<=current->data){
            this->insert(person,i);
            return;
        }
        current = current->next;
    }
    this->add(person);
}

PersonNode *PersonList::insert(PersonTest& person, int pos) {
    auto *node = new(PersonNode);
    node->data = person;
    if((pos!=0) and (pos!=this->size())) {
        PersonNode *rel = &(*this)[pos - 1];
        node->next = rel->next;
        rel->next = node;
        return rel->next;
    }
    else{
        if(pos == 0) {
            node->next = this->head;
            this->head = node;
            return this->head;
        }
        else{
            this->add(person);
        }
    }
}

void PersonList::save(ofstream* fout) {
    PersonNode *current = this->head;
    for (int i = 0; i < this->size()-1; i++){
        current->data.write(fout);
        *fout<<' ';
        current = current->next;
    }
    this->end->data.write(fout);
}

PersonNode *PersonList::getHead(){
    return this->head;
}

void PersonList::setHead(PersonNode *nhead) {
    this->head = nhead;
    return;
}

void PersonList::resetEnd(){
    this->end = &(*this)[this->size()-1];
}

PersonNode *PersonList::getEnd(){
    return this->end;
}
