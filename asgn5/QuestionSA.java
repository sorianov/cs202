
public class QuestionSA extends Question {
	
	public QuestionSA(String line) {
		String[] tokens = line.split("\\|");
		this.question = tokens[2];
		this.answer = tokens[3];
	}

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

}
