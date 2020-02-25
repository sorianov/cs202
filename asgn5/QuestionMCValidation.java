
class InvalidChoicesException extends Exception {
	private static final long serialVersionUID = 1055634682772547735L;

	public InvalidChoicesException() {
		super("Choices are invalid.");
	}
}
public class QuestionMCValidation extends QValidation {
	private static final int NUM_FIELDS = 5;
	private static final String FIELD_DELIMITER = "\\|";
	private static final String QUESTION_CODE = "mc";
	private static final String CHOICE_DELIMITER = ":";
	private static final int MIN_ANSWER_CHOICES = 2;
	private static final int MAX_ANSWER_CHOICES = 10;
	private int choicesLength = 0;

	
	@Override
	public boolean validate(String line) throws InvalidFieldCountException, 
		InvalidQuestionCodeException, 
		InvalidQuestionLevelException, 
		InvalidQuestionException, 
		InvalidChoicesException 
	{
		String[] parts = null;
		if (!this.validNumFields(line, NUM_FIELDS, FIELD_DELIMITER)) {
			throw new InvalidFieldCountException(NUM_FIELDS);
		}
		parts = line.split(FIELD_DELIMITER);
		String code = parts[0];
		String level = parts[1];
		String question = parts[2];
		String answerChoices = parts[3];
		String answer = parts[4];
		if (this.isValidQuestionCode(code, QUESTION_CODE)
				&& this.isValidLevel(level)
				&& this.isValidQuestion(question)
				&& this.areValidChoices(answerChoices)
				&& this.isValidAnswer(answer)) {
			return true;
		}

		return false;
	}
	
	@Override
	public boolean isValidAnswer(String answer) {
		String alphabet = "abcdefghij";

		if (this.choicesLength == 0 || answer.isBlank()) {
			return false;
		} else {
			// make a substring of acceptable answers
			String options = alphabet.substring(0, this.choicesLength);
			// if the answer from the question data exists in the 
			// substring, we know it's a valid answer
			if (options.indexOf(answer.charAt(0)) > -1) {
				return true;
			}
			return false;
		}
	}
	
	private boolean areValidChoices(String choices) throws InvalidChoicesException {
		String[] possibleAnswers = choices.split(CHOICE_DELIMITER);

		if (possibleAnswers.length < MIN_ANSWER_CHOICES
				|| possibleAnswers.length > MAX_ANSWER_CHOICES) {
			throw new InvalidChoicesException();
		}
		
		this.choicesLength = possibleAnswers.length;
		return true;
	}

}
