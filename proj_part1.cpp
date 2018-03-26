// Export file content.cpp : Defines the entry point for the console application.
//

/*
 1- apenas devem ser guardadas no ficheiro resultante as PALAVRAS SIMPLES, isto é, constituídas por letras ('A'-'Z');

 2- entradas como AARD-VARK, AARON'S ROD e ATELETS SAUCE devem ser totalmente ignoradas, isto é,
nenhuma das palavras deve ser tida em conta porque surgirão certamente como palavras/entradas isoladas;

 3- pode acontecer que haja entradas ("headlines") que ocupem mais do que uma linha, como acontece,
com "CONSOLATION GAME; CONSOLATION MATCH; CONSOLATION POT; CONSOLATION RACE" em que a palavra RACE aparece isolada numa linha;
neste caso não há problema em considerar a palavra RACE, a qual voltará a aparecer nas entradas que começam por "R" mas,
no final, será considerada apenas uma vez, quando forem eliminadas as palavras repetidas.
*/

#include <iostream>
#include <fstream>
#include <ctime>
#include <string>

using namespace std;

void readLine(ifstream &inFile, ofstream &outfile); // Prototipo readLine
bool validLine(string &line); // Prototipo validLine
void writeLine(string &line, ofstream &outFile); // Prototipo writeLine

int main()
{
	string inputFile_name, outputFile_name; // Inicializacao das strings (nomes de ficheiros)

	cout << "EXTRACTION OF WORD LIST FROM DICTIONARY" << endl;
	cout << "=======================================" << endl << endl;

	cout << "Dictionary File ?"; // ficheiro de input
	cin >> inputFile_name;

	ifstream infile;
	infile.open(inputFile_name); // Abre ficheiro de input

	if (!infile.is_open()) // Se o ficheiro de input nao estiver aberto
	{
		cerr << "Couldn't open the file" << endl;
		exit(1);
	}

	cout << "Word list file ?"; // ficheiro de output
	cin >> outputFile_name;

	ofstream outfile;
	outfile.open(outputFile_name); // Abre ficheiro de output

	if (!outfile.is_open()) // Se o ficheiro de output nao estiver aberto
	{
		cerr << "Couldn't open the file" << endl;
		exit(1);
	}

	readLine(infile, outfile);

	return 0;
}

void readLine(ifstream &inFile, ofstream &outfile) // Acho que esta função pode estar dentro do main...
{
	string s;
	while (!inFile.eof())
	{
		getline(inFile, s);
		// cout << s << endl; So um teste para ver se dava 
		if (validLine(s))   // Se validLine =  true ----> processar a linha; Else passar para  a proxima 
		{
			writeLine(s, outfile);
		}
	}
}

void writeLine(string &line, ofstream &outFile) // errado, fiz isto antes de ler o e-mail do stor
{
	char next;
	for (size_t i = 0; i < line.length(); i++)
	{
		next = line[i]; // vai buscar um a um os chars da linha
		if ((int)next == 59 || (int)next == 39 || (int)next == 45) //Tests if char is ';' , ''' or '-'
			outFile << '\n'; // Assim separa as palavras (ESQUCI-ME DE CONTABILIZAR OS CODIGO ASCII PARA O SPACE)
		else
			outFile << next; // escreve o char
	}
}

bool validLine(string &line) // Penso que esta tudo bem aqui :)
{
	int letter;
	bool valid_Line = false; //mudei o nome da variavel porque os alunos mais velhos disseram que pode causar erros se for igual ao nome da funcao
	for (size_t i = 0; i < line.length(); i++)
	{
		letter = line[i];
		if ((letter < 91 && letter > 64) || letter == 59 || letter == 39 || letter == 45)   //Tests if char belongs in A-Z or is either ';' , ''' or '-'.... Condicoes complexas... Erro provavel
			valid_Line = true;
		else
		{
			valid_Line = false;
			break; // para logo o ciclo se vê que
		}
	}
	return valid_Line;
}




