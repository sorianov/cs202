
public abstract class Question {
	protected String question = "";
	protected String answer = "";
	protected boolean correct = false;
	
	public void markCorrect() {
		this.correct = true;
	}
	
	public boolean isCorrect() {
		return this.correct;
	}
	
	public abstract void loadData(String data);
	
	public abstract void showQuestion();
	
	public abstract boolean checkAnswer(String givenAnswer);
	
	protected abstract boolean validate(String line, int lineNumber);
	
	protected void lineErrorMessage(String line, int lineNumber, String errMsg) {
		StringBuilder sb = new StringBuilder();
		sb.append("Error: Line " + lineNumber + " - " + line + "\n");
		sb.append("\t" + errMsg);
		System.err.println(sb);
	}
	
  	/**
  	 * Checks whether a question data line is a comment.
  	 *
  	 * @param 	data 		The question data
  	 *
  	 * @return 	boolean 	true if the line is a comment. false if the line is
  	 * 						not a comment.
  	 */
	public static boolean isComment(String data) {
		String trimmed = data.trim();
		if (trimmed.isEmpty()) {
			return false;
		}

		return trimmed.startsWith("#") || trimmed.startsWith("//");
	}
}
