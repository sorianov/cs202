
public class QuestionTF extends Question {
	
	public QuestionTF(String line) {
		String[] tokens = line.split("\\|");
		this.question = tokens[2];
		this.answer = tokens[3];
	}

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

}
