import java.util.ArrayList;

public class QuestionMC extends Question {
	private ArrayList<String> answerChoices = new ArrayList<String>();
	
	public QuestionMC(String line) {
		this.loadData(line);
	}
	
	public QuestionMC() {}
	
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

	@Override
	public boolean checkAnswer(String givenAnswer) {
		char correct = this.answer.toLowerCase().charAt(0);
		char given = givenAnswer.toLowerCase().charAt(0);
		return correct == given;
	}
	
	@Override
	protected boolean validate(String line, int lineNumber) {
		QuestionMCValidation qv = new QuestionMCValidation();
		try {
			qv.validate(line);
			return true;
		} catch (Exception e) {
			this.lineErrorMessage(line, lineNumber, e.getMessage());
			return false;
		}
	}
	
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
