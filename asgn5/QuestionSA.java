
public class QuestionSA extends Question {
	
	public QuestionSA(String line) {
		this.loadData(line);
	}
	
	public QuestionSA() {}

	@Override
	public void showQuestion() {
		StringBuilder sb = new StringBuilder(this.question);
		sb.append("?\n");
		System.out.println(sb);
	}

	@Override
	public boolean checkAnswer(String givenAnswer) {
		String correct = this.answer.toLowerCase();
		String given = givenAnswer.toLowerCase();
		return correct.contentEquals(given);
	}
	
	@Override
	protected boolean validate(String line, int lineNumber) {
		QuestionSAValidation qv = new QuestionSAValidation();
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
		this.answer = tokens[3];
	}


}
