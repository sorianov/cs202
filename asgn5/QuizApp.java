
public class QuizApp {

	public static void main(String[] args) {
		String filename = null;
		if (args.length > 0) {
			filename = args[0];

		}

		Quiz q = new Quiz(filename);
		q.deliverQuiz();
		String prompt = "You have answered some questions incorrectly. ";
		prompt += "Would you like to reattempt them? [Y/n]";
		if (q.getIncorrectCount() > 0) {
			while(q.userSaysYes(prompt)) {
				q.deliverIncorrectQuiz();
				if (q.getIncorrectCount() == 0) {
					// No more questions to answer, we shouldn't prompt again.
					break;
				}
			}
		}
		q.printQuizSummary();
	}

}
