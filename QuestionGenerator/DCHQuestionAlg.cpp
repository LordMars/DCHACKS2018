#include <iostream>
#include <fstream>
#include <unordered_map>

using namespace std;

bool isBold(char);
void isDefining(ifstream&, ofstream&);//determines if a statement is defining something
void summarize(ifstream &myfile, unordered_map<string, int> &wordMap, unordered_map<string, int > &sentenceMap); 
void wordOccurance(unordered_map<string, int> &wordMap);
void wordImportance(string word);
void sentenceOccurance(unordered_map<string, int> &sentenceMap); 
//void sentenceImportance();   


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
    sentenceOccurance(sentenceMap);
    
    myfile.close();
    myfile.open(argv[1]);

    isDefining(myfile, outfile);
    myfile.close();

}

void isDefining(ifstream &myfile, ofstream &outfile){
    //checks if sentence contains the word is. The chances are, all letters in the sentence after is are defining something in the first part of the sentence
    string firsthalf = ""; //first part of the sentence to be used when forming a question
    string secondhalf = "";
    string curword;//current word in the sentence
    myfile >> curword;
    firsthalf += curword + " ";

    bool found = false;

    while(myfile){
        /*if(curword.back() == ','){
            string secclause;//holds the second clause within the comma list
            while(myfile){
                
            }
        }*/
        if(curword.back() == '!' || curword.back() == '.' || curword.back() == '?'){//if te
            if(found == true && firsthalf.length() > 60 && secondhalf.length() < 300){
                outfile << firsthalf << "_______?" << endl;
                outfile << secondhalf << endl << endl;
            }
            myfile >> curword;
            secondhalf = "";
            firsthalf = curword + " ";//resets first half
            found = false;
        }
        else if((curword == "is" || curword == "was" || curword == "are" || curword == "include") && found == false){//checks if any of these words exisits int eh sentence{
            myfile >> curword;
            secondhalf += curword + " ";
            found = true;
        }
        else if(found == true){
            myfile >> curword;
            secondhalf += curword + " ";
        }
        else{
            myfile >> curword;
            firsthalf += curword + " ";
        }
    }
}
//summarize gets the summarized version of the text

void summarize(ifstream &myfile, unordered_map<string, int> &wordMap, unordered_map<string, int > &sentenceMap) {
	string word = "";
	string sentence = "";
	int value = 0;
	//get word values
	while (myfile >> word)
	{
		if (word[word.length() - 1] == '.')
		{
			word = word.substr(0, (word.length() - 1));
		}
		if (wordMap.find(word) == wordMap.end()){ //Word not in wordmap. Therefore add it.
			wordMap.insert({ word, 1 });
		}
		else{ //otherwise add the new key to the hashmap and set the value at 1
			wordMap.at(word) += 1;
		}
	}

	myfile.clear();
	myfile.seekg(0, ios::beg);
	//get sentence values
	while (myfile >> word) {
		if (word[word.length() - 1] != '.')
		{
			sentence += word;
			value += wordMap.at(word);
		}
		else {
			word = word.substr(0, (word.length() - 1));
			sentence += word;
			value += wordMap.at(word);
			sentenceMap.insert({ sentence, value });
			sentence = "";
		}
	}
}

//iterates through and prints the word hashmap
void wordOccurance(unordered_map<string, int> &wordMap) {
	unordered_map<string, int>::iterator it;
	for (it = wordMap.begin(); it != wordMap.end(); it++) {
		cout << "Word: " << it->first << "    " << "Count: " << it->second << endl;
	}
	return;
}

//iterates through and prints the sentences
void sentenceOccurance(unordered_map<string, int> &sentenceMap) {
	unordered_map<string, int>::iterator it;
	for (it = sentenceMap.begin(); it != sentenceMap.end(); it++) {
		cout << "Sentence: " << it->first << "    " << "Value: " << it->second << endl;
	}
	return;
}

/*//sentenceImportance determines the importance of each sentence
void sentenceImportance() {


}*/

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