#include <iostream>
#include <fstream>
#include <string>

using namespace std;

bool isBold(char);
void isDefining(ifstream&, ofstream&);//determines if a statement is defining something

int main(int argc, char *argv[]){
    if(argc!=2){
        cout << "Please give a text documents name with the program when executing." << endl;
        return -1;
    }//exits with an error if no file name is given on the command line

    ifstream myfile;
    ofstream outfile;
    myfile.open(argv[1]);//opens the file name provided on the command line
    outfile.open("output.txt");
    isDefining(myfile, outfile);
    //here is where the code determines word importance by occurence count

}

void isDefining(ifstream &myfile, ofstream &outfile){
    //checks if sentence contains the word is. The chances are, all letters in the sentence after is are defining something in the first part of the sentence
    string firsthalf = ""; //first part of the sentence to be used when forming a question
    string curword;//current word in the sentence
    myfile >> curword;
    firsthalf += curword + " ";

    bool found = false;

    while(myfile){
        if(curword.back() == '!' || curword.back() == '.' || curword.back() == '?'){//if te
            if(found == true){
                outfile << firsthalf << "_______?" << endl;
            }
            myfile >> curword;
            firsthalf = curword + " ";//resets first half
            found = false;
        }
        else if((curword == "is" || curword == "was" || curword == "are" || curword == "include") && found == false){//checks if any of these words exisits int eh sentence{
            myfile >> curword;
            found = true;
        }
        else if(found == true){
            myfile >> curword;
        }
        else{
            myfile >> curword;
            firsthalf += curword + " ";
        }
    }
}

bool isBold(char letter){//will determine if a character is bolded or not

}