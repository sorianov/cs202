
public class QuestionTFValidation extends QValidation {
	private static final int NUM_FIELDS = 4;
	private static final String FIELD_DELIMITER = "\\|";
	private static final String QUESTION_CODE = "tf";
	
	@Override
	public boolean validate(String line) throws InvalidFieldCountException, 
		InvalidQuestionCodeException, 
		InvalidQuestionLevelException, 
		InvalidQuestionException 
	{
		String[] parts = null;
		if (this.validNumFields(line, NUM_FIELDS, FIELD_DELIMITER)) {
			parts = line.split(FIELD_DELIMITER);
		}
		String code = parts[0];
		String level = parts[1];
		String question = parts[2];
		String answer = parts[3];
		if (this.isValidQuestionCode(code, QUESTION_CODE)
				&& this.isValidLevel(level)
				&& this.isValidQuestion(question)
				&& this.isValidAnswer(answer)) {
			return true;
		}

		return false;
	}

	@Override
	public boolean isValidAnswer(String answer) {
		if (answer.isBlank()) {
			return false;
		}
		return answer.toLowerCase().charAt(0) == 't' 
				|| answer.toLowerCase().charAt(0) == 'f';
	}

}