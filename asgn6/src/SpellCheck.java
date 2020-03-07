import java.io.File;
import java.io.FileNotFoundException;
import java.util.HashSet;
import java.util.Scanner;
import java.util.TreeMap;
import java.util.function.BiConsumer;

public class SpellCheck {
	private static final String DEFAULT_DICTIONARY_FILENAME = "words.txt";
	private static HashSet<String> dictSet = null;
	private static TreeMap<String, Integer> misspellings = new TreeMap<String, Integer>();
	private static int correct = 0;
	private static int incorrect = 0;
	private static int numChecked = 0;
	
	public static void main(String[] args) {
		String filename = getFilename(args);
		String dictionary = getDictionary(args);
		
		System.out.printf("Spell-checking %s using %s as a dictionary...\n",
				filename, dictionary);
		dictSet = buildDictionary(dictionary);
		spellcheck(filename, dictionary);

	}
	
	/**
	 * Add words from a file to a HashSet.
	 * <p>
	 * Assumes there is only one word per line. Will return an empty HashSet if 
	 * there is an error while processing the given filename. Behavior is undefined
	 * if there is more than one string per line in the file.
	 * 
	 * @param dictionary  A string whose value is the name of the file containing words.
	 * 
	 * @return A HashSet<String> containing every line from the file.
	 */
	private static HashSet<String> buildDictionary(String dictionary) {
		HashSet<String> dict = new HashSet<String>();
		Scanner file = null;
		try {
			File handle = new File(dictionary);
			file = new Scanner(handle);
			while (file.hasNext()) {
				dict.add(file.nextLine());
			}
		} catch (FileNotFoundException e) {
			System.err.printf("There was an error reading from %s\n",
					dictionary);
		} finally {
			file.close();
		}
		return dict;
	}
	
	private static void reportResults() {
		System.out.printf("Words checked: %d\n", numChecked);
		System.out.printf("Words misspelled: %d\n", incorrect);
		System.out.printf("Words spelled correctly: %d\n", correct);
	}
	
	private static void reportMisspellings() {
		BiConsumer<String, Integer> print = (key, val) -> {
			System.out.printf("%s(%d)\n", key, val);
		};
		misspellings.forEach(print);
	}
	
	private static String[] getWords(String line) {
		// replace non lower case alphabetic characters with a space
		String alphaOnly = line.toLowerCase().replaceAll("[^a-z]", " ");
		// replace multiple side-by-side whitespace characters with a single space
		String alphaTrimmed = alphaOnly.trim().replaceAll("( )+", " ");

		return alphaTrimmed.split(" ");
	}
	
	private static void spellCheckWords(String[] words) {
		for (String word : words) {
			++numChecked;
			if (!dictSet.contains(word)) {
				++incorrect;
				System.out.printf("Misspelled: %s\n", word);
				
				if (misspellings.containsKey(word)) {
					misspellings.put(word, misspellings.get(word) + 1);
				} else {
					misspellings.put(word, 1);
				}
				
			} else {
				++correct;
			}
		}
	}
	
	private static void spellcheck(String filename, String dictionary) {
		Scanner file = null;

		try {
			File handle = new File(filename);
			file = new Scanner(handle);
			while (file.hasNext()) {
				String line = file.nextLine();
				if (line.isBlank()) {
					// Skip blank lines
					continue;
				}
				String[] words = getWords(line);
				spellCheckWords(words);
				
			}
		} catch (FileNotFoundException e) {
			System.err.printf("There was an error reading from %s\n",
					filename);
		} finally {
			file.close();
		}
		reportMisspellings();
		reportResults();
	}

	private static String getFilename(String[] args) {
		if (args.length == 0) {
			Scanner keyboard = new Scanner(System.in);
			System.out.print("Please enter a filename: ");
			return keyboard.next();
		}
		return args[0];
	}
	
	private static String getDictionary(String[] args) {
		if (args.length < 2) {
			return DEFAULT_DICTIONARY_FILENAME;
		}
		return args[1];
	}
}
