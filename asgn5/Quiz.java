import java.io.File;
import java.io.FileNotFoundException;
import java.text.DecimalFormat;
import java.util.ArrayList;
import java.util.Scanner;

public class Quiz {
	private ArrayList<Question> questions = new ArrayList<Question>();
	private String filename = "";
	private boolean filenameIsValid = true;
	
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
			q = new QuestionSA();
		} else if (code.contentEquals("tf")) {
			q = new QuestionTF();
		} else if (code.contentEquals("mc")) {
			q = new QuestionMC();
		} else {
			throw new InvalidQuestionCodeException();
		}
		return q;
	}
	
	private boolean loadQuestion(String line, int lineNumber) {
		try {
			Question q = null;
			q = this.getQuestionObject(line);
			if (q.validate(line, lineNumber)) {
				q.loadData(line);
				this.questions.add(q);
				return true;
			}
			return false;
		} catch (InvalidQuestionCodeException e) {
			this.lineErrorMessage(line, lineNumber, e.getMessage());
			return false;
		}
	}
	
	private void lineErrorMessage(String line, int lineNumber, String errMsg) {
		StringBuilder sb = new StringBuilder();
		sb.append("Error: Line ");
		sb.append(lineNumber);
		sb.append(" - ");
		sb.append(line + "\n");
		sb.append("\t" + errMsg);
		System.err.println(sb);
	}
	
	private int totalCorrectQuestions() {
		int correct = 0;
		for (Question q: this.questions) {
			if (q.isCorrect()) {
				++correct;
			}
		}
		return correct;
	}
	
	private void printQuizSummary() {
		double correct = this.totalCorrectQuestions();
		double totalQuestions = this.totalQuestions();
		if (totalQuestions == 0) {
			return;
		}
		double percentCorrect = (correct / totalQuestions) * 100;
		
		StringBuilder sb = new StringBuilder();
		DecimalFormat integer = new DecimalFormat("#");
		DecimalFormat percent = new DecimalFormat("###.##");
		
		sb.append("You got ");
		sb.append(integer.format(correct));
		sb.append(" of ");
		sb.append(integer.format(totalQuestions));
		sb.append(" correct: ");
		sb.append(percent.format(percentCorrect) + "%. ");
		
		if (correct < totalQuestions) {
			sb.append("Better study more!");
		}
		if (correct == totalQuestions) {
			sb.append("Great job!");
		}
		System.out.println(sb);
	}
	
	public boolean loadQuestions(String dataFile) {	
		if (dataFile == null) {
			return false;
		}
		File fh = new File(dataFile);
		String line = new String("");
		int lineNumber = 0;
		try {
			Scanner scn = new Scanner(fh);
			while(scn.hasNext()) {
				++lineNumber;
				line = scn.nextLine();
				if (Question.isComment(line) || line.isBlank()) {
					continue;
				}
				this.loadQuestion(line, lineNumber);
			}
			scn.close();
			return true;
		} catch (FileNotFoundException e) {
			System.err.println("Could not open " + filename);
			return false;
		} catch (Exception e) {
			System.err.println("An unknown error ocurred");
			return false;
		}
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
		this.printQuizSummary();
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
