#include "QuestionMC.h"

QuestionMC::QuestionMC() {
   questionText = "";
   answerText = "";
   correct = false;
}

QuestionMC::QuestionMC(std::string question, std::string answer) {
    questionText = question;

}
