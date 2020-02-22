/**
 * @author Victor Soriano Mendoza
 *
 */
public abstract class QValidation {

	/**
	 * Validates a question data line
	 *
	 * @param 	line		String containing question data to validate
	 *
	 * @return	boolean		true if the question data is valid, false if
	 * 						the question data is not valid
	 */
	public abstract boolean validate(String line);
	/**
	 * Validates question code
	 *
	 * @param 	code	Question code to validate
	 * @return	boolean	true if the question code is valid,
	 * 					false if the question code is invalid.
	 */
	public abstract boolean isValidQuestionCode(String code);
	/**
	 * Validates question answer
	 *
	 * @param 	answer	Question answer to validate
	 * @return	boolean	true if the answer is valid,
	 * 					false if answer is invalid
	 */
	public abstract boolean isValidAnswer(String answer);
	/**
	 * Validates the number of fields in the question data.
	 *
	 * @param 	line		A line of question data
	 * @param	numFields	Number of fields the data line should have
	 * @return	boolean		true if the number of fields is valid,
	 * 						false if the number of fields in invalid.
	 */
	public boolean validNumFields(String line, int numFields, String delimiter) {
		String[] parts = line.split(delimiter);
		return parts.length == numFields;
	}

	/**
	 * Checks whether the question field is valid.
	 *
	 * @param 	question 	Value of the question field.
	 *
	 * @return 	boolean 	true if the field is value,
	 * 						false if the field is invalid.
	 */
	public boolean isValidQuestion(String question) {
		return !question.isBlank();
	}

  	/**
  	 * Checks whether a question data line is a comment.
  	 *
  	 * @param 	line 		The question data
  	 *
  	 * @return 	boolean 	true if the line is a comment. false if the line is
  	 * 						not a comment.
  	 */
	public boolean isCommentLine(String line) {
		String trimmed = line.trim();
		if (trimmed.isEmpty()) {
			return false;
		}

		return trimmed.startsWith("#") || trimmed.startsWith("//");
	}

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

	/**
	 * Validates the level of the question.
	 *
	 * @param 	level	Value of the level field of the question
	 *
	 * @return	boolean	true if the level is valid,
	 * 					false if the level is invalid.
	 */
	public boolean isValidLevel(String level) {
		int lvl = Integer.parseInt(level);
		return lvl <= 9 && lvl >=1;
	}

}
