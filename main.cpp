#include <iostream>     // cout
#include <fstream>      // ofstream

using namespace std;

long getHash(string name);
string getScore(long key);

int main(int argc, char* argv[]) {

   cout << "At anytime to exit the program type 'exit'" << endl;

   ofstream ofile;          // cout replacement
   ofile.open("names.txt", ios::app);
   if (!ofile.is_open()) {
      cout << "Error: failed to open file for writing..." << endl;
      return -1;
   }

   int score = 0;
   while (ofile.is_open()) {
      cout << "Enter your name: ";
      string name;
      cin >> name;
      if (name.compare("exit") != 0) {
         long index = getHash(name);
         ofile << index << " " << name << " " << score++ << "\n";
         continue;
      }
      ofile.close();
   }
   cout << endl;

   while (true) {
      string name;
      cout << "Enter your name to see your score: ";
      cin >> name;
      if (name.compare("exit") == 0) {
         cout << "\n\nGoodbye..." << endl;
         break;
      }
      long key = getHash(name);
      string points = getScore(key);
      cout << name << ": " << points << endl;
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
   cout << "Sorry did not find your name" << endl;
   return "";
}

long getHash(string name) {
   long key = 0;
   for (int i = 0; i < name.length(); i++) {
      key = key * 7 + name[i];
   }
   return key;
}