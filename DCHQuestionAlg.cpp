#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char *argv[]){
    if(argc!=2){
        cout << "Please give a text documents name with the program when executing." << endl;
        return -1;
    }//exits with an error if no file name is given on the command line

    ifstream myfile;
    myfile.open(argv[1]);//opens the file name provided on the command line

}