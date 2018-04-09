// playwords.cpp : Defines the entry point for the console application.
//

#include <vector>
#include <iostream>
#include <fstream>
#include <ctime>
#include <string>
#include <algorithm>
#include <random>


using namespace std;

void outInterface(vector<string> wordVector); // Receber vetor para usar nas funcoes
void wordBelong(vector<string> wordVector); // Ver se palavra pertence a lista
void wordScramble(vector<string> wordVector); // Mistura letras e devolve uma palavra com as letras trocadas
void wordFinder(vector<string> wordVector); //Recebe N letras e imprime as palavras que e possivel formar com as N-letras
bool matching(string const userLetters, string const vectorWord);
void buildWordFromSet(vector<string> wordVector); // O programa manda N letras a sorte, e o utilizador tem que construir uma palavra com essas letras
vector<char> buildLargerSet(vector<string> wordVector); // 

int main()
{ 
	string wordFile = "C:\\Users\\tiago\\Desktop\\PROG_PROJ1\\29765-8_w.txt"; //"29765-8_w.txt"; // Colocar diretorio!!! 
	// DIRETORIO DO MARANTES ===> C:\\Users\\gonca\\Documents\\GitHub\\proj_part1\\proj_part1\\29765-8_w.txt
	// DIRETORIO DO TIAGAO ===> C:\\Users\\tiago\\Desktop\\PROG_PROJ1\\29765-8_w.txt"
	ifstream file;
	vector<string> wordVector;

	file.open(wordFile);

	if (!file.is_open()) // Se o ficheiro de input nao estiver aberto
	{
		cerr << "Couldn't open the file" << endl;
		exit(1);
	}
	
	while (!file.eof())      // Extracao de palavras para vetor 
	{
		string word;
		getline(file, word);
		wordVector.push_back(word);
	}
	wordVector.pop_back(); // Apaga o ultimo elemento que é um paragrafo
	
	outInterface(wordVector);  // Funcao de interface
	
    return 0;
}

void outInterface(vector<string> wordVector) // Receber vetor para usar nas funcoes
{
	int funct = 1;
	while (funct != 0)
	{
		cout << "Choose between these..." << endl;

		cout << "1 - Find if word is in the file" << endl;
		cout << "2 - Word Scramble" << endl;
		cout << "3 - Words that can be written with the chosen letters" << endl;
		cout << "4 - Build a word with randomly chosen letters" << endl;
		cout << "5 - Wildcard words" << endl;
		cout << "0 - Close the program" << endl;

		cin >> funct;  // Escolher funcao

		switch (funct)
		{
		case 1:
			wordBelong(wordVector);
			break;
		case 2:
			wordScramble(wordVector);
			break;
		case 3:
			wordFinder(wordVector);
			break;
		case 4:
			buildWordFromSet(wordVector);
			break;
		case 5:
			//...
			break;
		}
	}
}

void wordBelong(vector<string> wordVector) // Ver se palavra pertence a lista
{
	string word;

	cout << "Enter a word..." << endl;  
	cin >> word;

	bool isInFile = false;
	int position = 0;

	for (unsigned i = 0; i < wordVector.size(); i++)    // Percorrer o vetor 
	{

		if (word == wordVector[i])  // Se a palavra for igual a do vetor break com isInFile = true 
		{
			isInFile = true;
			position = i + 1; // Posicao da palavra no vetor
			break;
		}
	}

	if (isInFile)
		cout << "The word is in the file, position no. " << position << endl;  // Se isInFile == true  faz o cout
	else
		cout << "The word is not in the file" << endl;  // Else ....
}

void wordScramble(vector<string> wordVector)
{
	const unsigned int vectorSize = wordVector.size(); //Tamanho do vetor
	random_device rd;     // only used once to initialise (seed) engine
	mt19937 rng(rd());    // random-number engine used (Mersenne-Twister in this case)
	uniform_int_distribution<int> uni(0, vectorSize - 1); // guaranteed unbiased

	auto randomIndex = uni(rng); // Numero aleatorio entre 0 e (vectorSize - 1) = 95902

	string word = wordVector[randomIndex]; // Palavra aleatorio do dicionario
	string scrambledWord = word; // Copia da word para ser scrambled

	int x = scrambledWord.length();
	for (int y = x; y > 0; y--) //
	{
		int pos = rand() % x;
		char tmp = scrambledWord[y - 1];
		scrambledWord[y - 1] = scrambledWord[pos];
		scrambledWord[pos] = tmp;
	}
	string guess; // Tentativa do utilizador
	int attempts = 0; // Numero de tentativas
	do
	{
		cout << scrambledWord << endl;
		cout << "Write your guess..." << endl;
		cin >> guess;
		transform(guess.begin(), guess.end(), guess.begin(), ::toupper); // Transforma o guess em upper case

		if (guess == word)
		{
			cout << "Correct!" << endl << endl;
			break;
		}
		if (attempts < 2)
			cout << "Try again..." << endl << endl;
		else
			cout << "Max attempts reached..." << endl << endl;
		attempts++;
	} while (attempts < 3);
}

void wordFinder(vector<string> wordVector)
{
	string userLetters;
	vector<string> auxVector;

	cout << "Enter a N set of letters: ";
	cin >> userLetters;

	if (cin.fail())
		cerr << endl << "Invalid entry" << endl;

	for (unsigned int i = 0; i < wordVector.size(); i++) //Acede a todas as palavras do dicionario(alocadas no vetor)
	{
		if (matching(userLetters, wordVector[i]))   // Se match = true entao coloca a palavra em auxVector
			auxVector.push_back(wordVector[i]);
	}

	if (auxVector.size() == 0)
		cout << endl << "No words can be written using those letters :(" << endl;
	else
		for (unsigned int i = 0; i < auxVector.size(); i++)
			cout << auxVector[i] << endl;

}

/* Devolve:
-true se as letras da palavra do vetor estiverem todas nas letras inseridas pelo utilizador e estas estiverem todas as ser utilizadas

-false em caso contrario
*/
bool matching(string const userLetters, string const vectorWord)
{
	bool wordMatch = true;

	if (userLetters.length() > vectorWord.length())
		wordMatch = false;

	for (unsigned int i = 0; i < vectorWord.length(); i++)  // Verifica se as letras da palavra do dicionario estao nas letras do user
	{
		bool letterMatch = false;
		for (unsigned int j = 0; j < userLetters.length(); j++) // Se a letra [i] da palvra do vetor estiver em userLetters letterMatch = true
			if (vectorWord[i] == userLetters[j])
			{
				letterMatch = true;
				break;
			}
		if (!letterMatch)   // Se alguma das letras da palavra do vetor nao estiver em userLetters, interrompe o ciclo e sai com match a devolver false
		{
			wordMatch = false;
			break;
		}
	}
	for (unsigned int i = 0; i < userLetters.length(); i++)  // Verifica se todas as letras inseridas pelo user estão a ser utilzadas
		if (vectorWord.find_first_of(userLetters[i]) == -1)
			wordMatch = false;

	return wordMatch;
}

void buildWordFromSet(vector<string> wordVector)
{
	vector<char> letterVector = buildLargerSet(wordVector); // Este vetor ira conter o set de letras que é proporcional ao numero de letras do vetor palavras

	srand(time(NULL));
	int randomNumberOfLetters = (rand() % 20) + 0; // numero aleatorio entre 0 e 20
}

vector<char> buildLargerSet(vector<string> wordVector)
{
	vector<char> largerSet; // Vetor que ira ser retornado e contem todos os chars em numero proporcional ao numero total de chars do wordVector
	int count[26]; // Array onde vai ser guardado o numero de ocorrencias de cada char

	for (int i = 0; i < 26; i++) // Ciclo que coloca a 0 todos os elementos do array
		count[i] = 0;
	
	for (int i = 0; i < wordVector.size(); i++) // Ciclo que percorre todas as palavras do vetor
	{
		string word = wordVector[i];
		for (int k = 0; k < word.length(); k++) // Ciclo que percorre todos os chars da palavra
		{
			count[(int)(word[k] - 'A')]++; // Incrementa consoante o char retirado
		}
	}

	int smallestIndex = 0;
	for (int i = 0; i < 26; i++) // Ciclo que encontra a posicao do char com menos numero de ocorrencias
		if (count[smallestIndex] > count[i])
			smallestIndex = i;

	char smallestChar = smallestIndex + 'A'; // char que ocorre menos vezes

	int countSum = 0;
	for (int i = 0; i < 26; i++) // Ciclo que soma todas as ocorrencias de todas as palavras
		countSum += count[i];

	double letterProportions[26];
	for (int i = 0; i < 26; i++) // Ciclo que constroi o a probabilidade de sair qualquer letra
		letterProportions[i] = count[i] / countSum;

	double directProportion = 2 / letterProportions[smallestIndex]; // Relacao de proporcionalidade direta
	for (int i = 0; i < 26; i++) // Ciclo que constroi o vetor com as proporçoes certas
	{
		double k = directProportion * letterProportions[i];
		while (k > 0)
		{
			largerSet.push_back(i + 'A');
			k--;
		}
	}

	return largerSet;
}