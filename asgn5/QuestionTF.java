
public class QuestionTF extends Question {
	
	public QuestionTF(String line) {
		this.loadData(line);
	}
	
	public QuestionTF() {}

	@Override
	public void showQuestion() {
		// TODO Auto-generated method stub
		StringBuilder sb = new StringBuilder(this.question);
		sb.append(" (T/F)?");
		System.out.println(sb);
	}

	@Override
	public boolean checkAnswer(String givenAnswer) {
		char correct = this.answer.toLowerCase().charAt(0);
		char given = givenAnswer.toLowerCase().charAt(0);
		return correct == given;
	}
	
	@Override
	protected boolean validate(String line, int lineNumber) {
		QuestionTFValidation qv = new QuestionTFValidation();
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
