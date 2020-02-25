

public class Validate {

	public static void main(String[] args) {
		String filename = null;
		if (args.length > 0) {
			filename = args[0];
			System.out.println("Validating " + filename + "...\n");
			Validation v = new Validation(filename);
			v.validateFile();
		}
	}

}
