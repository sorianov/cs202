import java.util.ArrayList;

/**
 * An object for multiple choice type questions.
 * 
 * @author Victor Soriano Mendoza {@literal <soriano.victorm@student.clackamas.edu>}
 * @version 1.0
 */
public class QuestionMC extends Question {
	private ArrayList<String> answerChoices = new ArrayList<String>();
	
	/**
	 * A constructor for validating and loading data.
	 * <p>
	 * Use this constructor when the data should be validated and loaded upon object creation. If validation fails,
	 * the data is not loaded.
	 * 
	 * @see QuestionMC#validate(String, int)
	 * @see QuestionMC#loadData(String)
	 * 
	 * @param line  A string containing question data
	 * @param lineNumber  An integer whose value is the line number of the question data
	 */
	public QuestionMC(String line, int lineNumber) {
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
	public QuestionMC() {}
	//--------------------------------------------------------------------------------------------------------------------------
	@Override
	public void showQuestion() {
		String alphabet = "abcdefghijkl";
		StringBuilder sb = new StringBuilder(this.question);
		sb.append("?\n");
		int i = 0;
		for (String str: this.answerChoices) {
			sb.append("\t" + alphabet.charAt(i) + ") ");
			sb.append(str);
			sb.append("\n");
			++i;
		}
		System.out.print(sb);
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
		QuestionMCValidation qv = new QuestionMCValidation();
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
		for (String str: tokens[3].split(":")) {
			this.answerChoices.add(str);
		}
		this.answer = tokens[4];
	}

}
