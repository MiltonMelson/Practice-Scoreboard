#include <iostream>     // cout
#include <fstream>      // ofstream
#include <random>
#include <queue>

using namespace std;

string getHash(string name);
string getScore(string key);
void enterName();
void viewScore();
void lowercase(string &name);
void scoreboard();
void enterLobby();

int main(int argc, char* argv[]) {
   enterLobby();
   return 0;
}

void enterLobby() {
   cout << "\nWelcome, this program stores names in a database and gives them random score.";
   cout << " You can also search specific names in the database to view their score.\n\n\n";
   int input = 0;
   while (input != 4) {
      cout << "Please select an option:\n";
      cout << "1. To enter your name into the database.\n";
      cout << "2. To view a individuals score.\n";
      cout << "3. To view the scoreboard.\n";
      cout << "4. To exit.\n";
      cin >> input;
      switch(input) {
         case 1:
            enterName();
            break;
         case 2:
            viewScore();
            break;
         case 3:
            scoreboard();
            break;
         case 4:
            return;
         default:
            continue;
      }
   }
}
string getScore(string key) {
   ifstream ifile;
   ifile.open("names.txt");
   if (!ifile.is_open()) {
      cout << "Error: failed to open file for reading..." << endl;
   }

   string word;
   while (ifile >> word) {
      if (word.compare(key) == 0) {
         ifile >> word >> word;
         ifile.close();
         return word;
      }
   }
   return "-1";
}

string getHash(string name) {
   string key = "";
   for (int i = 0; i < name.length(); i++) {
      key += ((name[i]*7)%32)+33;
   }
   return key;
}

void enterName() {
   ofstream ofile;          // cout replacement
   ofile.open("names.txt", ios::app);
   if (!ofile.is_open()) {
      cout << "Error: failed to open file for writing..." << endl;
      return;
   }
   int score = -1;
   while (score == -1) {
      cout << "Enter your name: ";
      string name;
      cin >> name;
      lowercase(name);
      string index = getHash(name);
      if (getScore(index) != "-1") {
         cout << "Sorry that username is already taken, try again." << endl;
      }
      else {
         score = rand()%100;
         ofile << index << " " << name << " " << score << "\n";
      }
   }
   cout << endl;
   ofile.close();
}

void lowercase(string &name) {
   for (int i = 0; i < name.length(); i++) {
      if (name[i] > 'A' && name[i] < 'Z') {
         name[i] = name[i] + 32;
      }
   }
}

void viewScore() {
   while (true) {
      string name;
      cout << "To see your score, please enter your name: ";
      cin >> name;
      if (name.compare("done") == 0) {
         cout << "\n\nGoodbye..." << endl;
         return;
      }
      lowercase(name);
      string key = getHash(name);
      string points = getScore(key);
      if (points != "-1") {
         cout << name << ": " << points << endl;
         cout << endl;
      }
      else {
         cout << "Sorry that name is not in our database." << endl;
      }
      cout << "If you want to see more scores type 'more', otherwise type 'done'" << endl;
      cin >> name;
      if (name.compare("done") == 0) {
         return;
      }
   }
}

void scoreboard() {
   ifstream ifile("names.txt");
   if (!ifile.is_open()) {
      cout << "Error: opening file for scoreboard..." << endl;
      return;
   }
   priority_queue< pair<int, string> > pq;
   string name;
   string points;
   while (ifile >> name) {
      ifile >> name;
      ifile >> points;
      pq.push(make_pair(stoi(points), name));
   }
   cout << "\n\n~~ HIGH SCORES ~~\n" << endl;
   while (!pq.empty()) {
      name = pq.top().second;
      int p = pq.top().first;
      pq.pop();
      cout << name;
      for (int i = name.length(); i < 15; i++) {
         cout << " ";
      }
      cout << p << endl;
   }
   cout << "\n-----------------\n\n";
}