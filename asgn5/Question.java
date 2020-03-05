
/**
 * A general Question object.
 * 
 * @author Victor Soriano Mendoza {@literal <soriano.victorm@student.clackamas.edu>}
 * @version 1.0
 *
 */
public abstract class Question {
	protected String question = "";
	protected String answer = "";
	protected boolean correct = false;
	
	/**
	 * Sets correct property to true
	 * 
	 * {@link Question#correct}
	 */
	public void markCorrect() {
		this.correct = true;
	}
	//--------------------------------------------------------------------------------------------------------------------------
	/**
	 * Gets the value of correct property
	 * 
	 * {@link Question#correct}
	 * 
	 * @return A boolean whose value is the value of the correct property.
	 */
	public boolean isCorrect() {
		return this.correct;
	}
	//--------------------------------------------------------------------------------------------------------------------------
	/**
	 * Adds data to the Question object.
	 * <p>
	 * Parses the question data and adds it to the question object. Will not validate data. This function does not handle malformed data.
	 * It is suggested that the data be validated before calling this function.
	 * 
	 * @param data  A string which should contain valid question data
	 */
	public abstract void loadData(String data);
	//--------------------------------------------------------------------------------------------------------------------------
	/**
	 * Prints the contents of the question property.
	 * <p>
	 * Defines the way the question property will be presented to the user.
	 */
	public abstract void showQuestion();
	//--------------------------------------------------------------------------------------------------------------------------
	/**
	 * Compares the passed parameter to the contents of the answer property.
	 * <p>
	 * The comparison should be case insensitive.
	 * 
	 * @param givenAnswer  The answer to compare against the answer property.
	 * 
	 * @return True if the contents of the answer property matches givenAnswer. False if it does not.
	 */
	public abstract boolean checkAnswer(String givenAnswer);
	//--------------------------------------------------------------------------------------------------------------------------
	/**
	 * Validates question data
	 * <p>
	 * Uses a QValidation object to validate question data.
	 * 
	 * @see QValidation#validate(String)
	 * 
	 * @param line  The question data to validate
	 * @param lineNumber  Line number of the question data in the data file.
	 * 
	 * @return True if and only if the QValidation's validate() method doesn't throw any exceptions. False otherwise.
	 */
	public abstract boolean validate(String line, int lineNumber);
	//--------------------------------------------------------------------------------------------------------------------------
	protected void lineErrorMessage(String line, int lineNumber, String errMsg) {
		StringBuilder sb = new StringBuilder();
		sb.append("Error: Line " + lineNumber + " - " + line + "\n");
		sb.append("\t" + errMsg);
		System.err.println(sb);
	}
	//--------------------------------------------------------------------------------------------------------------------------
  	/**
  	 * Checks whether a question data line is a comment.
  	 * <p>
  	 * Checks what the data line starts with. If it starts with a comment symbol, returns true.
  	 *
  	 * @param data 	A string containing question data
  	 *
  	 * @return True if the line is a comment. False if the line is not a comment.
  	 */
	public static boolean isComment(String data) {
		String trimmed = data.trim();
		if (trimmed.isEmpty()) {
			return false;
		}

		return trimmed.startsWith("#") || trimmed.startsWith("//");
	}
}
