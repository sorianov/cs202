/**
 * A general Question validation class.
 * 
 * @author Victor Soriano Mendoza {@literal <soriano.victorm@student.clackamas.edu>}
 * @version 1.0
 */

class InvalidFieldCountException extends Exception {
	private static final long serialVersionUID = 5267215075575109999L;
	
	public InvalidFieldCountException() {
		super("Number of fields is invalid.");
	}
	//--------------------------------------------------------------------------------------------------------------------------
	public InvalidFieldCountException(String msg) {
		super(msg);
	}
	//--------------------------------------------------------------------------------------------------------------------------
	public InvalidFieldCountException(int req) {
		super("Number of fields is invalid. "
				+ "There must be " + String.valueOf(req) + ".");
	}
}

class InvalidQuestionCodeException extends Exception {
	private static final long serialVersionUID = 6348577435419646119L;
	
	public InvalidQuestionCodeException() {
		super("Question code is invalid");
	}
	//--------------------------------------------------------------------------------------------------------------------------
	public InvalidQuestionCodeException(String msg) {
		super(msg);
	}
}

class InvalidQuestionException extends Exception {
	private static final long serialVersionUID = 4849221316372993371L;

	public InvalidQuestionException() {
		super("Invalid question");
	}
}

class InvalidQuestionLevelException extends Exception {
	private static final long serialVersionUID = -5780710823909918879L;

	public InvalidQuestionLevelException() {
		super("Invalid question level");
	}
}

class InvalidAnswerException extends Exception {
	private static final long serialVersionUID = -6062364977140280113L;

	public InvalidAnswerException() {
		super("Answer is invalid.");
	}
}

class InvalidChoicesException extends Exception {
	private static final long serialVersionUID = 1055634682772547735L;

	public InvalidChoicesException() {
		super("Choices are invalid.");
	}
}

public abstract class QValidation {

	/**
	 * Validates a question data line
	 *
	 * @param 	line		String containing question data to validate
	 *
	 * @return	boolean		true if the question data is valid, false if
	 * 						the question data is not valid
	 * 
	 * @throws InvalidFieldCountException if the number of fields is too large or too small
	 * @throws InvalidQuestionException if the question field is blank
	 * @throws InvalidQuestionLevelException if the question level is out of acceptable bounds
	 * @throws InvalidQuestionCodeException if an unsupported question code if encountered
	 * @throws InvalidChoicesException if the number of answer choices outside of the accepted range
	 * @throws InvalidAnswerException if the answer field is blank or doesn't conform to the object
	 */
	public abstract boolean validate(String line) throws InvalidFieldCountException, 
		InvalidQuestionCodeException, 
		InvalidQuestionLevelException, 
		InvalidQuestionException, 
		InvalidChoicesException, 
		InvalidAnswerException;
	//--------------------------------------------------------------------------------------------------------------------------
	/**
	 * Validates question code
	 *
	 * @param 	code		Question code to validate
	 * @param	validCode	What the code parameter should be.
	 * 
	 * @return	boolean	True if the contents of the code parameter matches value of validCode
	 * 
	 * @throws InvalidQuestionCodeException if an unsupported question code if encountered
	 */
	public boolean isValidQuestionCode(String code, String validCode) throws InvalidQuestionCodeException {
		String validLower = validCode.toLowerCase();
		if (!code.toLowerCase().contentEquals(validLower)) {
			throw new InvalidQuestionCodeException(code);
		}
		return true;
	}
	//--------------------------------------------------------------------------------------------------------------------------
	/**
	 * Validates question answer
	 *
	 * @param 	answer	Question answer to validate
	 * @return	boolean	true if the answer is valid,
	 * 					false if answer is invalid
	 *
	 * @throws InvalidAnswerException if the answer field is blank or doesn't conform to the object
	 */
	public abstract boolean isValidAnswer(String answer) throws InvalidAnswerException;
	//--------------------------------------------------------------------------------------------------------------------------
	/**
	 * Validates the number of fields in the question data.
	 *
	 * @param 	line		A line of question data
	 * @param	numFields	Number of fields the data line should have
	 * @param 	delimiter	String to use as a delimiter when splitting the fields.
	 * 
	 * @return	boolean		true if the number of fields is valid,
	 * 						false if the number of fields in invalid.
	 * 
	 * @throws InvalidFieldCountException if the size of the fields don't match the numFields parameter
	 */
	public boolean validNumFields(String line, int numFields, String delimiter) throws InvalidFieldCountException {
		String[] parts = line.split(delimiter);
		if (!(parts.length == numFields)) {
			throw new InvalidFieldCountException(numFields);
		}
		return true;
	}
	//--------------------------------------------------------------------------------------------------------------------------
	/**
	 * Checks whether the question field is valid.
	 *
	 * @param 	question 	Value of the question field.
	 *
	 * @return 	boolean 	true if the field is valid
	 * 
	 * @throws InvalidQuestionException if the question parameter is blank
	 */
	public boolean isValidQuestion(String question) throws InvalidQuestionException {
		if (question.isBlank()) {
			throw new InvalidQuestionException();
		}
		return true;
	}
	//--------------------------------------------------------------------------------------------------------------------------
	/**
	 * Checks whether a question data line is a blank line.
	 *
	 * @param 	line		The question data
	 *
	 * @return 	boolean		true if the line is blank,
	 * 						false if the line is not blank.
	 *
	 */
	public boolean isBlankLine(String line) {
		return line.isBlank();
	}
	//--------------------------------------------------------------------------------------------------------------------------
	/**
	 * Validates the level of the question.
	 *
	 * @param 	level	Value of the level field of the question
	 *
	 * @return	boolean	true if the level is valid,
	 * 					false if the level is invalid.
	 * 
	 * @throws InvalidQuestionLevelException if the question level is out of acceptable bounds 
	 */
	public boolean isValidLevel(String level) throws InvalidQuestionLevelException {
		if (level.isBlank()) {
			throw new InvalidQuestionLevelException();
		}
		try {
			int lvl = Integer.parseInt(level);
			if (lvl > 9 || lvl < 1) {
				throw new InvalidQuestionLevelException();
			}
		} catch (NumberFormatException e) {
			throw new InvalidQuestionLevelException();
		}

		return true;
	}

}
