/**
 * An object for true/false type questions.
 * 
 * @author Victor Soriano Mendoza {@literal <soriano.victorm@student.clackamas.edu>}
 * @version 1.0
 */
public class QuestionTF extends Question {
	
	/**
	 * A constructor for validating and loading data.
	 * <p>
	 * Use this constructor when the data should be validated and loaded upon object creation. If validation fails,
	 * the data is not loaded.
	 * 
	 * @see QuestionTF#validate(String, int)
	 * @see QuestionTF#loadData(String)
	 * 
	 * @param line  A string containing question data
	 * @param lineNumber  An integer whose value is the line number of the question data
	 */
	public QuestionTF(String line, int lineNumber) {
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
	public QuestionTF() {}
	//--------------------------------------------------------------------------------------------------------------------------
	@Override
	public void showQuestion() {
		// TODO Auto-generated method stub
		StringBuilder sb = new StringBuilder(this.question);
		sb.append(" (T/F)?");
		System.out.println(sb);
	}
	//--------------------------------------------------------------------------------------------------------------------------
	@Override
	public boolean checkAnswer(String givenAnswer) {
		char correct = this.answer.toLowerCase().charAt(0);
		char given = givenAnswer.toLowerCase().charAt(0);
		return correct == given;
	}
	//--------------------------------------------------------------------------------------------------------------------------
	@Override
	public boolean validate(String line, int lineNumber) {
		QuestionTFValidation qv = new QuestionTFValidation();
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
