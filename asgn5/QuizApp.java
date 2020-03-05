/**
 * Instantiate and deliver a Quiz.
 * 
 * @author Victor Soriano Mendoza {@literal <soriano.victorm@student.clackamas.edu>}
 * @version 1.0
 */
public class QuizApp {

	/**
	 * Instantiates a quiz object and delivers it.
	 * <p>
	 * Will only deliver quiz if a filename is passed in the commandline arguments. Prints usage if a filename can't be found.
	 * 
	 * @param args String array holding command line arguments
	 */
	public static void main(String[] args) {
		String filename = null;
		if (args.length == 0) {
			printUsage();
			return;
		}
		
		filename = args[0];
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
	
	/**
	 * Outputs text describing how to use application.
	 */
	public static void printUsage() {
		System.out.println();
		System.out.println("java QuizApp <filename>");
		System.out.println();
		System.out.println("\tfilename\tName of file that contains question data");
	}

}
