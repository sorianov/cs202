
public abstract class Question {
	protected String question = "";
	protected String answer = "";
	protected boolean correct = false;
	
	public void markCorrect() {
		this.correct = true;
	}
	
	public boolean isCorrect() {
		return this.correct;
	}
	
	public abstract void showQuestion();
	
	public abstract boolean checkAnswer(String givenAnswer);
	
}
