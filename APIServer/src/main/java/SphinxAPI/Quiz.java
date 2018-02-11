package CreolePleaseAPI;

import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.lang.StringBuilder;
import java.lang.ProcessBuilder;
import java.lang.Process;
import java.util.concurrent.TimeUnit;
import java.util.ArrayList;


/*Stores original and converted text*/
public class Quiz {

    private final StringBuilder question;
    private final StringBuilder answer;
    private final ArrayList<String> question_list;
    private final ArrayList<String> answer_list;
 

    public Quiz() {
        this.question = new StringBuilder("");
        this.answer = new StringBuilder("");
        this.question_list = new ArrayList<String>(); 
        this.answer_list = new ArrayList<String>();  

        /*Read text from file*/
        String fileName = "../QuestionGenerator/output.txt";
        String question = null;
        String answer = null;

        try {
            FileReader fileReader = new FileReader(fileName);
            // Always wrap FileReader in BufferedReader.
            BufferedReader bufferedReader = new BufferedReader(fileReader);

            //while file not empty. Add the question then its answer right after
            while((question = bufferedReader.readLine()) != null) {
                question_list.add(question);
                answer = bufferedReader.readLine();
                answer_list.add(answer); 
            }   
            bufferedReader.close();         
        }catch(IOException e) {
            e.printStackTrace();
        }

    }

    public ArrayList<String> getQuestions() {
        return question_list;
    }

    public ArrayList<String> getAnswers() {
        return answer_list;
    }

}