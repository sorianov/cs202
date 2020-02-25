import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

class CodeNotFoundException extends Exception {
	/**
	 * 
	 */
	private static final long serialVersionUID = 6542671038660855841L;
	public CodeNotFoundException() {
		super("Question code is invalid");
	}
	public CodeNotFoundException(String msg) {
		super(msg);
	}
}

public class Validation {
	private int processed = 0;
	private int errors = 0;
	private String filename = "";
	
	public Validation(String filename) {
		this.filename = filename;
	}
	
	public void validateLine(String line, int lineNumber, QValidation qv) {
		try {
			if (this.isCommentLine(line) || line.isBlank()) {
				return;
			};
			qv = getQuestionObject(line);
			if (qv == null) {
				throw new CodeNotFoundException();
			}
			++this.processed;
			qv.validate(line);
		} catch (Exception e) {
			++this.errors;
			System.err.println(errorLine(lineNumber, line));
			System.err.println("\t" + e.getMessage());
			return;
		}
	}
	
	public boolean validateFile() {
		File fh = new File(this.filename);
		String line = new String("");
		int lineNumber = 0;
		QValidation qv = null;
		try {
			Scanner scn = new Scanner(fh);
			while(scn.hasNext()) {
				++lineNumber;
				line = scn.nextLine();
				this.validateLine(line, lineNumber, qv);
			}
			scn.close();
		} catch (FileNotFoundException e) {
			System.err.println("Could not open " + filename);
			return false;
		}
		printSummary();
		return true;
	}
	
	public void printSummary() {
		String msg = new String();
		msg = String.valueOf(this.processed) + " questions processed.\n";
		msg += String.valueOf(this.errors) + " errors found.";
		System.out.println("\n" + msg);
	}
	
	public QValidation getQuestionObject(String line) {
		String[] fields = line.split("\\|");
		String code = null;
		QValidation q;
		if (fields.length > 0) {
			code = fields[0].toLowerCase();
		}

		if (code.contentEquals("sa")) {
			q = new QuestionSAValidation();
		} else if (code.contentEquals("tf")) {
			q = new QuestionTFValidation();
		} else if (code.contentEquals("mc")) {
			q = new QuestionMCValidation();
		} else if (code.contentEquals("ma")) {
			q = new QuestionMAValidation();
		} else {
			q = null;
		}
		return q;
	}
	
	public String errorLine(int lineNumber, String line) {
		String msg = new String();
		msg = "Line " + String.valueOf(lineNumber) + " - ";
		msg += line;
		return msg;
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
}

