

public class Validate {

	public static void main(String[] args) {
		String filename = null;
		if (args.length > 0) {
			filename = args[0];
//			System.out.println("Validating " + filename + "...\n");
//			Validation v = new Validation(filename);
//			v.validateFile();
		}
//		QuestionTF tf = new QuestionTF("TF|1|The capital of Germany is Munich|False");
//		tf.showQuestion();
//		QuestionMC mc = new QuestionMC("MC|2|What is the capital of Kansas|Topeka:Kansas City:Salt Lake City:Portland|A");
//		mc.showQuestion();
//		QuestionSA sa = new QuestionSA("SA|2|What is the capital of Italy|Rome");
//		sa.showQuestion();
		Quiz q = new Quiz(filename);
		q.deliverQuiz();
		
	}

}
