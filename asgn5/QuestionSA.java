/**
 * An object for short answer type questions.
 * 
 * @author Victor Soriano Mendoza {@literal <soriano.victorm@student.clackamas.edu>}
 * @version 1.0
 */
public class QuestionSA extends Question {
	
	/**
	 * A constructor for validating and loading data.
	 * <p>
	 * Use this constructor when the data should be validated and loaded upon object creation. If validation fails,
	 * the data is not loaded.
	 * 
	 * @see QuestionSA#validate(String, int)
	 * @see QuestionSA#loadData(String)
	 * 
	 * @param line  A string containing question data
	 * @param lineNumber  An integer whose value is the line number of the question data
	 */
	public QuestionSA(String line, int lineNumber) {
		if (this.validate(line, lineNumber)) {
			this.loadData(line);
		}
	}
	//--------------------------------------------------------------------------------------------------------------------------
	/**
	 * Basic constructor
	 * <p>
	 * Use this constructor when validation and data loading should be handled separately.
	 */
	public QuestionSA() {}
	//--------------------------------------------------------------------------------------------------------------------------
	@Override
	public void showQuestion() {
		StringBuilder sb = new StringBuilder(this.question);
		sb.append("?");
		System.out.println(sb);
	}
	//--------------------------------------------------------------------------------------------------------------------------
	@Override
	public boolean checkAnswer(String givenAnswer) {
		String correct = this.answer.toLowerCase();
		String given = givenAnswer.toLowerCase();
		return correct.contentEquals(given);
	}
	//--------------------------------------------------------------------------------------------------------------------------
	@Override
	public boolean validate(String line, int lineNumber) {
		QuestionSAValidation qv = new QuestionSAValidation();
		try {
			qv.validate(line);
			return true;
		} catch (Exception e) {
			this.lineErrorMessage(line, lineNumber, e.getMessage());
			return false;
		}
	}
	//--------------------------------------------------------------------------------------------------------------------------
	@Override
	public void loadData(String line) {
		String[] tokens = line.split("\\|");
		this.question = tokens[2];
		this.answer = tokens[3];
	}


}
