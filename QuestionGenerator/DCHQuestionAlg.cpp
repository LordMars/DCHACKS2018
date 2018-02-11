#include <iostream>
#include <fstream>
#include <unordered_map>
#include <deque>
#include <algorithm>

using namespace std;

void isDefining(ifstream&, ofstream&, unordered_map<string, int> &wordMap, unordered_map<string, int > &sentenceMap);//determines if a statement is defining something
void wordValue(ifstream &myfile, unordered_map<string, int> &wordMap); 
//void wordOccurance(unordered_map<string, int> &wordMap);
void wordImportance(string word);
//void sentenceOccurance(unordered_map<string, int> &sentenceMap); 
void questionSelecter(unordered_map<string, int > &sentenceMap, int amount, ifstream &myfile);
//void sentenceImportance();   


int main(int argc, char *argv[]){
	int amount = 0;
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

    wordValue(myfile, wordMap);
    //wordOccurance(wordMap);
    //sentenceOccurance(sentenceMap);
    
    myfile.close();
    myfile.open(argv[1]);

    isDefining(myfile, outfile, wordMap, sentenceMap);
	outfile.close();
    myfile.close();

	myfile.open("output.txt");

	cout << "How many questions do you want to generate? (enter a number please)" << endl;
	cin >> amount;
	questionSelecter(sentenceMap, amount, myfile);

	myfile.close();
}

void isDefining(ifstream &myfile, ofstream &outfile, unordered_map<string, int> &wordMap, unordered_map<string, int > &sentenceMap){
	int sentvalue = 0;
    //checks if sentence contains the word is. The chances are, all letters in the sentence after is are defining something in the first part of the sentence
    string firsthalf = ""; //first part of the sentence to be used when forming a question
    string secondhalf = "";
    string curword;//current word in the sentence
    myfile >> curword;
    firsthalf += curword + " ";

	sentvalue += wordMap.at(curword);

    bool found = false;

    while(myfile){
        /*if(curword.back() == ','){
            string secclause;//holds the second clause within the comma list
            while(myfile){
                
            }
        }*/
        if(curword.back() == '!' || curword.back() == '.' || curword.back() == '?'){//if te
            if(found == true && firsthalf.length() > 60 && secondhalf.length() < 200){
				firsthalf += "_______?\n\n\n" + secondhalf;
                outfile << firsthalf << endl << endl << endl;
                //outfile << secondhalf << endl << endl;
				sentvalue += wordMap.at(curword);
				sentenceMap.insert({ firsthalf, sentvalue }); //insert the new sentence and value into the hashmap
            }


            myfile >> curword;
            secondhalf = "";
            firsthalf = curword + " ";//resets first half
			sentvalue = wordMap.at(curword);
            found = false;
        }
        else if((curword == "is" || curword == "was" || curword == "are" || curword == "include") && found == false){//checks if any of these words exisits int eh sentence{
            myfile >> curword;
            secondhalf += curword + " ";

			sentvalue += wordMap.at(curword);

            found = true;
        }
        else if(found == true){
            myfile >> curword;
            secondhalf += curword + " ";

			sentvalue += wordMap.at(curword);

        }
        else{
            myfile >> curword;
            firsthalf += curword + " ";

			sentvalue += wordMap.at(curword);

        }
    }
}
//summarize gets the summarized version of the text

void wordValue(ifstream &myfile, unordered_map<string, int> &wordMap) {
	string word = "";
	string sentence = "";
	int value = 0;
	//get word values
	while (myfile >> word)
	{
		/*if (word.back() == '.' || word.back() == '?' || word.back() == '!') //if the end of the word is a period
		{
			word = word.substr(0, (word.length() - 1)); //get rid of the period
		}*/
		if (wordMap.find(word) == wordMap.end()){ //Word not in wordmap. Therefore add it.
			wordMap.insert({ word, 1 });
		}
		else{ //otherwise increase the value
			wordMap.at(word) += 1;
		}
	}

	myfile.clear(); //clear myfile so it resets
	myfile.seekg(0, ios::beg);
	/*
	//get sentence values
	while (myfile >> word) {
		if (word[word.length() - 1] != '.') //if this is not the last word
		{
			sentence += word; //add the word to the sentence
			value += wordMap.at(word); //add the value of the word to the value of the sentence
		}
		else { //if it is the last word
			word = word.substr(0, (word.length() - 1)); //get rid of the period
			sentence += word; //add to the sentence
			value += wordMap.at(word); //add the value of the word to the value of the sentence
			sentenceMap.insert({ sentence, value }); //insert the new sentence and value into the hashmap
			sentence = ""; //reset sentence
		}
	}*/
}

/*iterates through and prints the word hashmap
void wordOccurance(unordered_map<string, int> &wordMap) {
	unordered_map<string, int>::iterator it;
	for (it = wordMap.begin(); it != wordMap.end(); it++) {
		cout << "Word: " << it->first << "    " << "Count: " << it->second << endl;
	}
	return;
}*/

/*iterates through and prints the sentences
void sentenceOccurance(unordered_map<string, int> &sentenceMap) {
	unordered_map<string, int>::iterator it;
	for (it = sentenceMap.begin(); it != sentenceMap.end(); it++) {
		cout << "Sentence: " << it->first << "    " << "Value: " << it->second << endl;
	}
	return;
}*/


void questionSelecter(unordered_map<string, int> &sentenceMap, int amount, ifstream &myfile) {
	string whole, first, second;
	char temp;
	ofstream finalQuestions;
	finalQuestions.open("Final_Questions.txt");

	deque<string> final_q;

	unordered_map<string, int>::iterator it;

	final_q.push_back(sentenceMap.begin()->first);
	for (it = sentenceMap.begin(); it != sentenceMap.end(); it++) {
		if (it->second > sentenceMap[final_q.front()]) {
			final_q.push_back(it->first);
		}
		if (final_q.size() > amount) {
			final_q.pop_front();
		}
	}

	for (auto it = final_q.begin(); it != final_q.end(); it++) {
		finalQuestions << *it << endl << endl << endl << endl;
	}
}
/*
	while (myfile) {
		first = "";
		second = "";
		temp = '\0';
		while (temp != '?' && myfile) {
			first += temp; 
			myfile >> temp;
		}
		temp = '\0';
		while (temp != '.' && myfile) {
			second += temp;
			myfile >> temp;
		}

		whole = first + second;

		remove(whole.begin(), whole.end(), ' ');
		remove(whole.begin(), whole.end(), '?');
		remove(whole.begin(), whole.end(), '_');
		remove(whole.begin(), whole.end(), '.');
		remove(whole.begin(), whole.end(), '\0');
		remove(whole.begin(), whole.end(), '\n');

		//std::cout << "string without spaces: " << whole << '\n';
#if 0
		for (auto c : whole) {
			std::cout << "char: " << c << " int: " << static_cast<int>(c) << '\n';
		}
#endif
		for (auto it = final_q.begin(); it != final_q.end(); it++) {
			//cout << whole << endl << endl;
			//cout << *it << endl << endl;

			if (*it == whole) {
				cout << *it << endl;
				//continue;
			}
		}
	}

	



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