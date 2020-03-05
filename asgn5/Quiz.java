import java.io.File;
import java.io.FileNotFoundException;
import java.text.DecimalFormat;
import java.util.ArrayList;
import java.util.Scanner;

/**
 * Handles all Quiz related functionality.
 * 
 * @author Victor Soriano Mendoza {@literal <soriano.victorm@student.clackamas.edu>}
 * @version 1.0
 */
public class Quiz {
	private ArrayList<Question> questions = new ArrayList<Question>();
	
	/*
	 * Constructor for a quiz
	 * <p>
	 * This is the only constructor for this class. The Quiz must be initialized using a filename.
	 * 
	 * @param datafile  A string which is the name of the file containing question data.
	 */
	public Quiz(String dataFile) {
		try {
			this.loadQuestions(dataFile);
		} catch (Exception e) {
			System.err.println(e.getMessage());
		}
	}
	//--------------------------------------------------------------------------------------------------------------------------
	/**
	 * Creates a Question object corresponding to a question code.
	 * <p>
	 * Will create a Question object pointing to a QuestionXX object where XX is an upper case question code.
	 * The supported codes are:
	 * 
	 * <ul>
	 * 	<li>SA</li>
	 * 	<li>TF</li>
	 * 	<li>MC</li>
	 * </ul>
	 * 
	 * This method should use a constructor which does not load the data into the object.
	 * 
	 * @see Question
	 * @see QuestionSA
	 * @see QuestionTF
	 * @see QuestionMC
	 * 
	 * @param line  A string which represents the question data to process.
	 * @return A Question object with unloaded data.
	 * @throws InvalidQuestionCodeException if an unsupported code is encountered and an object cannot be retrieved.
	 */
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
	//--------------------------------------------------------------------------------------------------------------------------
	/**
	 * Get the number of correct questions
	 * <p>
	 * Will process each question inside the question container and return the amount of correct questions.
	 * 
	 * @return An integer whose value is the number of correct questions.
	 */
	private int totalCorrectQuestions() {
		int correct = 0;
		for (Question q: this.questions) {
			if (q.isCorrect()) {
				++correct;
			}
		}
		return correct;
	}
	//--------------------------------------------------------------------------------------------------------------------------
	/**
	 * Prints information for the results of the quiz.
	 * <p>
	 * Divides the number of correct questions by the total amount of questions to get a percentage. Will not print anything
	 * if the total amount of questions available is zero. Output will be different depending on the results of the quiz.
	 */
	public void printQuizSummary() {
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
			sb.append("Great work!");
		}
		System.out.println(sb);
	}
	//--------------------------------------------------------------------------------------------------------------------------
	/**
	 * Loads a question into the question container.
	 * <p>
	 * Accepts a line from the question data file and tries to get a question object to hold the data. If an object cannot be
	 * retrieved, then a Question object is not added to the Question container. If the Question object's validate() method
	 * returns false, the Question object is not added to the Question container. Prints error information to stderr if a Question
	 * object could not be retrieved.
	 * 
	 * @param line  A string containing a line of question data
	 * @param lineNumber An integer whose value is the line number of the question data
	 * 
	 * @return True if the question was added to the question container. False if the question was not added to the container.
	 */
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
	//--------------------------------------------------------------------------------------------------------------------------
	/**
	 * Prints error information to standard error.
	 * <p>
	 * Prints a string containing:
	 * 
	 * <ul>
	 * 	<li>The question data content</li>
	 * 	<li>The line number of the question data</li>
	 * 	<li>Message describing the error</li>
	 * </ul>
	 * 
	 * to standard error.
	 * 
	 * @param line  A string containing question data.
	 * @param lineNumber  An integer whose value is the line number of the question data
	 * @param errMsg  A string describing the error.
	 */
	private void lineErrorMessage(String line, int lineNumber, String errMsg) {
		StringBuilder sb = new StringBuilder();
		sb.append("Error: Line ");
		sb.append(lineNumber);
		sb.append(" - ");
		sb.append(line + "\n");
		sb.append("\t" + errMsg + "\n");
		System.err.println(sb);
	}
	//--------------------------------------------------------------------------------------------------------------------------
	/**
	 * Loads questions from a data file into the question container.
	 * <p>
	 * Goes through every line of the data file and if the line is not a comment line or blank line, tries to parse the data
	 * and add it to the question container. Will return false if the data file cannot be processed or if an exception that wasn't
	 * accounted for is thrown.
	 * 
	 * @param dataFile  A string containing the name of the file to process.
	 * 
	 * @return True if the file could be opened and loading question data could be attempted. False if there was an error trying to access
	 * the file or an exception that was unaccounted for is thrown. This function returning true does not mean all questions in the file
	 * were successfully added to the question container.
	 */
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
					// No data to process here, keep moving forward.
					continue;
				}
				this.loadQuestion(line, lineNumber);
			}
			scn.close();
			return true;
		} catch (FileNotFoundException e) {
			System.err.println("Could not open " + dataFile);
			return false;
		} catch (Exception e) {
			System.err.println("An unknown error ocurred");
			return false;
		}
	}
	//--------------------------------------------------------------------------------------------------------------------------
	/**
	 * Returns the total number of questions in the question container.
	 * 
	 * @return The return value of the size() method of the container.
	 */
	public int totalQuestions() {
		return this.questions.size();
	}
	//--------------------------------------------------------------------------------------------------------------------------
	/**
	 * Validates that the parameter is a yes or no answer.
	 * <p>
	 * Only takes the first character of the string into account. Will compare the first character of the string to 'y' or 'n'. Returns true
	 * on blank strings as well.
	 * 
	 * @param maybe  The string to validate as yes or no.
	 * 
	 * @return True if the string can be interpreted as a yes or no answer. False if it cannot.
	 */
	private boolean validateYesNo(String maybe) {
		if (maybe.isBlank()) {
			return true;
		}
		
		char m = maybe.toLowerCase().charAt(0);
		if (m == 'y' || m == 'n') {
			return true;
		}
		return false;
	}
	//--------------------------------------------------------------------------------------------------------------------------
	/**
	 * Returns true if the passed parameter can be interpreted as yes
	 * <p>
	 * Looks at the first character of the parameter and returns true if it's equal to 'y' or the parameter is blank.
	 * 
	 * @param maybe  A string whose value can be interpreted as yes or no.
	 * 
	 * @return True if the string is interpreted as a yes, False if it's interpreted as a no.
	 */
	private boolean isYes(String maybe) {
		if (maybe.isBlank() || maybe.toLowerCase().charAt(0) == 'y' ) {
			return true;
		}
		return false;
	}
	//--------------------------------------------------------------------------------------------------------------------------
	/**
	 * Prints a prompt for user and returns whether the user responded yes to the prompt.
	 * <p>
	 * Prints the passed parameter as a prompt and waits for the user to respond with a "yes" or "no" answer. Will tell user
	 * to respond with 'y' or 'n' as to force the user to respond with a valid input.
	 * 
	 * @param prompt  A string that will be displayed as a prompt.
	 * @return True if the user responded with "yes" answer. False if the user responded with a "no" answer.
	 */
	public boolean userSaysYes(String prompt) {
		System.out.println(prompt);
		Scanner keyboard = new Scanner(System.in);
		String input = "";
		boolean ranOnce = false;
		do {
			if (ranOnce) {
				System.out.println("Please enter a 'y' or 'n'.");
			}
			input = keyboard.nextLine();
			ranOnce = true;
		} while (!this.validateYesNo(input));
		return this.isYes(input);
	}
	//--------------------------------------------------------------------------------------------------------------------------
	private void deliverQuestion(Question q) {
		Scanner keyboard = new Scanner(System.in);
		String answer = "";
		q.showQuestion();
		answer = keyboard.next();
		if (q.checkAnswer(answer)) {
			q.markCorrect();
			System.out.println("Correct! Good job!");
		} else {
			System.out.println("Incorrect.");
		}
		System.out.println();
	}
	//--------------------------------------------------------------------------------------------------------------------------
	private void deliverIncorrectQuestions() {
		for (Question q: this.questions) {
			if (!q.isCorrect()) {
				this.deliverQuestion(q);
			}
		}
	}
	//--------------------------------------------------------------------------------------------------------------------------
	/**
	 * Outputs questions in the question container as a quiz.
	 * <p>
	 * Will:
	 * 
	 * <ul>
	 * 	<li>Call Question.showQuestion()</li>
	 * 	<li>Take user answer</li>
	 * 	<li>Check user's answer</li>
	 * </ul>
	 * 
	 * for every Question object inside the question container whose isCorrect() method returns false. If the question's 
	 * checkAnswer() method returns true, will call markCorrect() on the Question object.
	 * 
	 * @see Question#showQuestion()
	 * @see Question#checkAnswer(String)
	 * @see Question#isCorrect()
	 */
	public void deliverIncorrectQuiz() {
		this.deliverIncorrectQuestions();
	}
	//--------------------------------------------------------------------------------------------------------------------------
	/**
	 * Outputs questions in the question container as a quiz.
	 * <p>
	 * Will:
	 * 
	 * <ul>
	 * 	<li>Call Question.showQuestion()</li>
	 * 	<li>Take user answer</li>
	 * 	<li>Check user's answer</li>
	 * </ul>
	 * 
	 * for every Question object inside the question container. If the question's checkAnswer() method returns true, will call 
	 * markCorrect() on the Question object.
	 * 
	 * @see Question#showQuestion()
	 * @see Question#checkAnswer(String)
	 * @see Question#isCorrect()
	 */
	public void deliverQuiz() {
		for (Question q: this.questions) {
			this.deliverQuestion(q);
		}
	}
	//--------------------------------------------------------------------------------------------------------------------------
	/**
	 * Returns the amount of questions whose isCorrect() method returns true
	 * 
	 * @return An integer whose value is the number of correct questions the container has.
	 */
	public int getCorrectCount() {
		int correct = 0;
		for (Question q: questions) {
			if (q.isCorrect()) {
				++correct;
			}
		}
		return correct;
	}
	//--------------------------------------------------------------------------------------------------------------------------
	/**
	 * Returns the difference between the total amount of questions and the number of correct questions.
	 * 
	 * @see Quiz#getCorrectCount()
	 * 
	 * @return An integer which holds the difference between the size of the question container and the number of correct questions inside
	 * the container.
	 */
	public int getIncorrectCount() {
		return this.questions.size() - this.getCorrectCount();
	}
}
