
public class QuestionSAValidation extends QValidation {
	private static final int NUM_FIELDS = 4;
	private static final String FIELD_DELIMITER = "|";
	
	@Override
	public boolean validate(String line) {
		String[] parts = null;
		if (this.validNumFields(line, NUM_FIELDS, FIELD_DELIMITER)) {
			parts = line.split(FIELD_DELIMITER);
		}
		String code = parts[0];
		String level = parts[1];
		String question = parts[2];
		String answer = parts[3];
		if (this.isValidQuestionCode(code)
				&& this.isValidLevel(level)
				&& this.isValidQuestion(question)
				&& this.isValidAnswer(answer)) {
			return true;
		}

		return false;
	}

	@Override
	public boolean isValidQuestionCode(String code) {
		return code.toLowerCase().equals("sa");
	}

	@Override
	public boolean isValidAnswer(String answer) {
		return !answer.isBlank();
	}

}
