#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<cstdlib>

using namespace std;

char score2grade(int score){
    if(score >= 80) return 'A';
    if(score >= 70) return 'B';
    if(score >= 60) return 'C';
    if(score >= 50) return 'D';
    else return 'F';
}

string toUpperStr(string x){
    string y = x;
    for(unsigned i = 0; i < x.size();i++) y[i] = toupper(x[i]);
    return y;
}

void importDataFromFile(string filename, vector<string> &names, vector<int> &scores, vector<char> &grades){
  ifstream input(filename);
    string text;
    char name[100];
    int s1, s2, s3;
    char format[] = "%[^:]:%d %d %d";

    while (getline(input, text))
    {
        const char *texts = text.c_str();
        sscanf(texts, format, name, &s1, &s2, &s3);
        names.push_back(name);
        scores.push_back(s1 + s2 + s3);
        grades.push_back(score2grade(s1 + s2 + s3));
    }
}

void getCommand(string &command, string &key){
cout << "Please input your command: ";
    cin >> command;
    if (toUpperStr(command) == "GRADE" || toUpperStr(command) == "NAME")
    {
        cin.ignore();
        getline(cin, key);
    }
}
void searchName(vector<string> &name, vector<int> &score, vector<char> &grade, string key){
cout << "---------------------------------" << endl;
    bool isFound = false;
    key = toUpperStr(key);
    for (unsigned int i = 0; i < name.size(); i++)
    {
        if (key == toUpperStr(name[i]))
        {
            cout << name[i] << "'s score = " << score[i] << endl;
            cout << name[i] << "'s grade = " << grade[i] << endl;
            isFound = 1;
        }
        else if (isFound == 0 && i == name.size() - 1)
        {
            cout << "Cannot found." << endl;
        }
    }
    cout << "---------------------------------" << endl;
}

void searchGrade(vector<string> &names, vector<int> &scores, vector<char> &grades, string key)
{
    int j = names.size();
    bool x = false;
    cout << "---------------------------------" << endl;
    for(int i = 0; i < j; i++){
    if(grades[i] == *key.c_str()){
    cout << names[i] << " (" << scores[i] << ") " << endl;
    x = true;
    }else if(x == false && i == j-1){
    cout << "Cannot found." << endl;
}
}

    cout << "---------------------------------\n";
}


int main(){
    string filename = "name_score.txt";
    vector<string> names;
    vector<int> scores;
    vector<char> grades; 
    importDataFromFile(filename, names, scores, grades);
    
    do{
        string command, key;
        getCommand(command,key);
        command = toUpperStr(command);
        key = toUpperStr(key);
        if(command == "EXIT") break;
        else if(command == "GRADE") searchGrade(names, scores, grades, key);
        else if(command == "NAME") searchName(names, scores, grades, key);
        else{
            cout << "---------------------------------\n";
            cout << "Invalid command.\n";
            cout << "---------------------------------\n";
        }
    }while(true);
    
    return 0;
}