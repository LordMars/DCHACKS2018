#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>

using namespace std;

bool isBold(char);
void isDefining(ifstream&, ofstream&);//determines if a statement is defining something
void summarize(ifstream &myfile, unordered_map<string, int> &wordMap, unordered_map<string, int > &sentenceMap); 
void wordOccurance(unordered_map<string, int> &wordMap);
void wordImportance(string word);
void sentenceImportance();   


int main(int argc, char *argv[]){
    unordered_map<string, int> wordMap; //using a hashmap for word importance
	unordered_map<string, int> sentenceMap; //and one for sentencce importance
    if(argc!=2){
        cout << "Please give a text documents name with the program when executing." << endl;
        return -1;
    }//exits with an error if no file name is given on the command line


    ifstream myfile;
    ofstream outfile;

    myfile.open(argv[1]);//opens the file name provided on the command line
    outfile.open("output.txt");

    summarize(myfile, wordMap, sentenceMap);
    wordOccurance(wordMap);
    
    myfile.close();
    myfile.open(argv[1]);

    isDefining(myfile, outfile);
    myfile.close();

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
            if(found == true && firsthalf.length() > 60 ){
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

void summarize(ifstream &myfile, unordered_map<string, int> &wordMap, unordered_map<string, int > &sentenceMap) {
	string word = "";
	string sentence = "";

	while (myfile >> word)
	{
		if (wordMap.find(word) == wordMap.end()){ //Word not in wordmap. Therefore add it.
			wordMap.insert({ word, 1 });
			//sentence += word;
		}
		else{ //otherwise add the new key to the hashmap and set the value at 1
			wordMap.at(word) += 1;
			//sentence += word;
		}
	}
	//sentenceMap(sentence);
}

void wordOccurance(unordered_map<string, int> &wordMap) {
	unordered_map<string, int>::iterator it;
	for (it = wordMap.begin(); it != wordMap.end(); it++) {
		cout << "Word: " << it->first << "    " << "Count: " << it->second << endl;
	}
	return;
}

bool isBold(char letter){//will determine if a character is bolded or not

}

//wordImportance determines the importance of each word
void wordImportance(string word) {


}

//sentenceImportance determines the importance of each sentence
void sentenceImportance() {


}

/*
� Ranking sentences by importance using the core algorithm.
� Reorganizing the summary to focus on a topic; by selection of a keyword.
� Removing transition phrases.
� Removing unnecessary clauses.
� Removing excessive examples.

1) Associate words with their grammatical counterparts. (e.g. "city" and "cities")
2) Calculate the occurrence of each word in the text.
3) Assign each word with points depending on their popularity.
4) Detect which periods represent the end of a sentence. (e.g "Mr." does not).
5) Split up the text into individual sentences.
6) Rank sentences by the sum of their words' points.
7) Return X of the most highly ranked sentences in chronological order.
*/
