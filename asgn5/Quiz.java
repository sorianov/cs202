import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.Scanner;

public class Quiz {
	private ArrayList<Question> questions = new ArrayList<Question>();
	private String filename = "";
	private boolean filenameIsValid = true;
	private int correct = 0;
	
	public Quiz(String dataFile) {
		try {
			this.loadQuestions(dataFile);
		} catch (Exception e) {
			System.err.println(e.getMessage());
		}
	}
	
	private Question getQuestionObject(String line) throws InvalidQuestionCodeException {
		Question q = null;
		String[] tokens = line.split("\\|");
		String code = tokens[0].toLowerCase();
		if (code.contentEquals("sa")) {
			q = new QuestionSA(line);
		} else if (code.contentEquals("tf")) {
			q = new QuestionTF(line);
		} else if (code.contentEquals("mc")) {
			q = new QuestionMC(line);
		} else {
			throw new InvalidQuestionCodeException();
		}
		return q;
	}
	
	private boolean loadQuestion(String line, int lineNumber) {
		Validation v = new Validation();
		QValidation qv = null;
		if (v.validateLine(line, lineNumber, qv)) {
			try {
				Question q = null;
				q = this.getQuestionObject(line);
				this.questions.add(q);
			} catch (InvalidQuestionCodeException e) {
				System.err.println(v.errorLine(lineNumber, line));
				System.err.println("\t" + e.getMessage());
				return false;
			}
			return true;
		}
		return false;
	}
	
	public boolean loadQuestions(String dataFile) {	
		File fh = new File(dataFile);
		String line = new String("");
		int lineNumber = 0;
		try {
			Scanner scn = new Scanner(fh);
			while(scn.hasNext()) {
				++lineNumber;
				line = scn.nextLine();
				this.loadQuestion(line, lineNumber);
			}
			scn.close();
		} catch (FileNotFoundException e) {
			System.err.println("Could not open " + filename);
			return false;
		}
		return true;
	}
	
	public int totalQuestions() {
		return this.questions.size();
	}
	
	public void deliverQuiz() {
		Scanner sc = new Scanner(System.in);
		for (Question q: this.questions) {
			q.showQuestion();
			String answer = sc.next();
			if (q.checkAnswer(answer)) {
				q.markCorrect();
				System.out.println("Correct! Good job!");
			} else {
				System.out.println("Incorrect.");
			};
		}
		sc.close();
	}
	
	public int getCorrectCount() {
		int correct = 0;
		for (Question q: questions) {
			if (q.isCorrect()) {
				++correct;
			}
		}
		return correct;
	}
	public int getIncorrectCount() {
		return this.questions.size() - this.getCorrectCount();
	}
}
