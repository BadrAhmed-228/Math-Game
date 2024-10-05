#include <iostream>
#include <string>

using namespace std;

enum enOperations { add = 1, subtract = 2, multiply = 3, division = 4, MixOperator = 5 };

enum enQuestionLevel { Easy = 1, Medium = 2, Hard = 3, MixLevels = 4 };

struct stGameData {

	int numberOfQuestions;
	int rightAnwers = 0;
	int wrongAnswers = 0;
	enQuestionLevel level;
};

int validateNumber() {

	int number = 0;
	cin >> number;

	while (cin.fail()) {

		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		cout << "Invalide Key please try again : " << endl;
		cin >> number;
	}
	return number;
}

int getRandomNumber(int from, int to) {

	return rand() % (to - from) + from;
}

int readNumberOfQuestions() {

	int number = 0; 

	do
	{
		cout << "How many Questions you want to solve ? ";
		number = validateNumber();
		
		if (number < 0) {
			cout << "Invalide number please try again" << endl;
		}

	} while (number < 0);
	
	return number;
}

enOperations readOperation() {

	short number = 0;

	do
	{
		cout << "\noperations [1]: Add, [2]: subtract, [3]: Multiply, [4]: Dividion, [5]: Mix" << endl;
		cout << "Please Enter Your Operation Number : ";
	    number = validateNumber();

		if (number > 5 || number < 1) {
			cout << "\ninvalide number Enter number between 1 and 5" << endl;
		}

	} while (number > 5 || number < 1);

	return enOperations(number);
}

enQuestionLevel readQuestionLevel(stGameData& gameData) 
{
	short number = 0;

	do
	{
		cout << "\nLevel [1]: Easy, [2]: Medium, [3]: Hard, [4]: Mix" << endl;
		cout << "Please Enter your choice number : ";
		number = validateNumber();
		if (number > 4 || number < 1) {
			cout << "\nInvalide number Enter number between 1 and 4" << endl;
		}

	} while (number > 4 || number < 1);

	gameData.level = enQuestionLevel(number);

	return enQuestionLevel(number);
}

int readUserAnswer() {

	int userAnswer = 0;

	userAnswer = validateNumber();
	return userAnswer;
}

void isRight(int userAnswer, int Answer, stGameData& gameData) {

	if (userAnswer == Answer) {
		gameData.rightAnwers++;
		cout << "Right Answer :-)" << endl;
		system("color 2F");
	}
	else {
		gameData.wrongAnswers++;
		cout << "Wrong Answer :-(" << endl;
		cout << "Answer is : " << Answer << endl;
		system("color 4F");
		cout << "\a";
	}
}

bool isPass(stGameData gameData) {

	return gameData.rightAnwers >= gameData.wrongAnswers;
}

enOperations mixOPeration() {

	short mix = getRandomNumber(1, 4);

	return enOperations(mix);
}

enQuestionLevel mixLevel() {

	short mix = getRandomNumber(1, 3);

	return enQuestionLevel(mix);
}

int generateQuestionAndReturnAnswer(enOperations operation, enQuestionLevel questionLevel) {

	short number1, number2;

	if (questionLevel == enQuestionLevel::MixLevels) 
	{
		questionLevel = mixLevel();
	}

	if (questionLevel == enQuestionLevel::Easy)
	{
		number1 = getRandomNumber(1, 10);
		number2 = getRandomNumber(1, 10);
	}
	else if (questionLevel == enQuestionLevel::Medium) {

		number1 = getRandomNumber(1, 50);
		number2 = getRandomNumber(1, 50);
	}
	else {

		number1 = getRandomNumber(10, 100);
		number2 = getRandomNumber(10, 100);
	}

	if (operation == enOperations::MixOperator){

		operation = mixOPeration();
	}

		switch (operation)
		{
		case enOperations::add: {

			cout << " " << number1 << endl;
			cout << "    +\n" << " " << number2 << endl;
			cout << "--------" << endl;
			return number1 + number2;
		}
		case enOperations::subtract: {

			cout << " " << number1 << endl;
			cout << "   -\n" << " " << number2 << endl;
			cout << "--------" << endl;
			return number1 - number2;
		}
		case enOperations::multiply: {

			cout << " " << number1 << endl;
			cout << "   *\n" << " " << number2 << endl;
			cout << "--------" << endl;
			return number1 * number2;
		}
		case enOperations::division: {

			cout << " " << number1 << endl;
			cout << "   /\n" << " " << number2 << endl;
			cout << "--------" << endl;
			return number1 / number2;
		}
		}
}

string printLevels(enQuestionLevel QuestionLevel) {

	string arr[4] = { "Easy", "Medium", "Hard", "Mix Levels"};

	return arr[QuestionLevel - 1];
}

string tabs(short numberOfTabs) {

	string tabs = "";
	
	for (int i = 1; i <= numberOfTabs; i++) {

		tabs += "\t";
	}
	return tabs;
}

void printGameData(stGameData gameData) {

	cout << endl;
	cout << tabs(3) << "--------------------------------------- \n";
	cout << tabs(3) << "            Final Results" << endl;
	cout << tabs(3) << "--------------------------------------- \n" << endl;

	cout << tabs(2) << "Number of questions     : " << gameData.numberOfQuestions << endl;
	cout << tabs(2) << "Questions level         : " << printLevels(gameData.level) << endl;
	cout << tabs(2) << "Number of right answers : " << gameData.rightAnwers << endl;
	cout << tabs(2) << "Number of wrong answers : " << gameData.wrongAnswers << endl;

	if (isPass(gameData)) 
	{
		cout << tabs(2) << "Congrats you pass :-)\n" << endl;
		system("color 2F");
	}
	else 
	{
		cout << tabs(2) << "You got fail :-(\n" << endl;
		system("color 4F");
		cout << "\a";
	}
}

void resetScreen() {

	system("cls");
	system("color 0F");
}

bool isPlayAgain() {

	char YN = ' ';

	cout << "Do you want to play again Y/N" << endl;
	cout << "\nEnter your choice -----> ";
	cin >> YN;

	if (YN == 'Y' || YN == 'y') {
		
		resetScreen();
		return 1;
	}
	return 0;
}

void startGame() {

	do
	{
		stGameData gameData;

		gameData.numberOfQuestions = readNumberOfQuestions(); //updated to optimize(decrease) memory usage in program

		enQuestionLevel questionLevel = readQuestionLevel(gameData);

		enOperations operation = readOperation();

		for (int i = 1; i <= gameData.numberOfQuestions; i++)
		{
			cout << "\n\n-------------Question [ " << i << " / " << gameData.numberOfQuestions << " ]-------------\n" << endl;

			int Answer = generateQuestionAndReturnAnswer(operation, questionLevel);

			int userAnswer = readUserAnswer();

			isRight(userAnswer, Answer, gameData);

			cout << "--------------------------------------" << endl;
		}

		printGameData(gameData);

	} while (isPlayAgain());

}

int main() {

	srand((unsigned)time(NULL));
	
	startGame();

	return 0;
} 