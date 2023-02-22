#include <iostream>     // cout
#include <fstream>      // ofstream

using namespace std;

long getHash(string name);
string getScore(long key);
void enterName();
void viewScore();

int main(int argc, char* argv[]) {
   cout << "\nWelcome, this program stores names in a database and gives them random score.\n";
   cout << " You can then search names in the database to view their score.\n";
   string exit = "";
   while (exit.compare("exit") != 0) {
      enterName();
      viewScore();
      cout << "To enter more names type 'more', otherwise type 'exit': ";
      cin >> exit;
      if (exit.compare("exit") == 0) {
         break;
      }
   }
   return 0;
}

string getScore(long key) {
   ifstream ifile;
   ifile.open("names.txt");
   if (!ifile.is_open()) {
      cout << "Error: failed to open file for reading..." << endl;
   }

   string word;
   string index = to_string(key);
   while (ifile >> word) {
      if (word.compare(index) == 0) {
         ifile >> word >> word;
         ifile.close();
         return word;
      }
   }
   return "-1";
}

long getHash(string name) {
   long key = 0;
   for (int i = 0; i < name.length(); i++) {
      key = key * 7 + name[i];
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
      long index = getHash(name);
      if (getScore(index) != "-1") {
         cout << "Sorry that username is already taken, try again." << endl;
      }
      else {
         score = index%10;
         ofile << index << " " << name << " " << score << "\n";
      }
   }
   cout << endl;
   ofile.close();
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
      long key = getHash(name);
      string points = getScore(key);
      cout << name << ": " << points << endl;
      cout << endl;
      cout << "If you want to see more scores type 'more', otherwise type 'done'" << endl;
      cin >> name;
      if (name.compare("done") == 0) {
         return;
      }
   }
}