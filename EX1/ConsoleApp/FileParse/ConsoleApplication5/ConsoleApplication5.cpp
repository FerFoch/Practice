#include <iostream>
#include <unordered_map>
#include <map>
#include <fstream>
#include <sstream>
#include <set>
using namespace std;

void PrintAllSymbols(unordered_map<char, int>& symbols, string fileName)
{
    unordered_map<char, int> ::iterator it = symbols.begin(); // итератор для map символов
    ofstream outputFile;
    outputFile.open(fileName); // открываем файл для записи
    if (outputFile.is_open())
    {
        for (; it != symbols.end(); it++)
        {
            outputFile << it->first << ": " << it->second << endl; // выводим в файл
        }
    }
    outputFile.close();
}
void ParseAllSymbols(string str, unordered_map<char, int>& symbols)
{
    unordered_map<char, int> ::iterator it; // итератор для unordered_map символов

    for (int i = 0; i < str.length(); i++)
    {
        it = symbols.find(str[i]); //Добавляем символ в unordered_map
        if (it == symbols.end())
        {
            symbols.insert(make_pair(str[i], 1));
        }
        else
        {
            it->second++; // прибавляет количество всех символов в файле
        }
    }
}

void ParseAndPrintWords(set<string> words, string fileNamein, string fileNameout) // контейнер set для хранения только уникальных значений
{
    ifstream inputFile(fileNamein); // для ввода(чтения) данных из файла
    ofstream outputFile(fileNameout); // для вывода(записи) данных в файл
    string word;

    int fileSize = 0; // переменная для определения размера файла

    inputFile.seekg(0, ios::end); // перемещаем указатель в конец файла
    fileSize = inputFile.tellg(); // fileSize = общее количество символов в файле
    inputFile.seekg(ios::beg); // возвращаем указатель в начало файла
    char* text; // указатель char на text
    text = new char[fileSize]; // создаем массив символов по числу символов в файле

    inputFile.read(text, fileSize); // считываем весь текст в созданный ранее массив

    for (int i = 0; i < fileSize; i++)
    {
        switch (text[i])  // проверяем указывает ли индекс на символ означающий конец текста
        {
        case '"':
        case '\'':
        case ' ':
        case '  ':
        case '…':
        case '»':
        case '—':
        case '«':
        case ',':
        case '.':
        case ';':
        case '!':
        case '?':
        case ':':
        case '\n':
        case '\r':
        case '\t':
        case '(':
        case ')':
        case '*':
        case '/':
        case '-':
        case ' –':
            if (word.size() != 0)  // если это так, то помещаем полученное слово в set words и очищаем его
            {
                words.insert(word);
                word.clear();
            }
            break;

            default:
                word.push_back(text[i]); // если нет, то добавляем к слову символ
            }
        }

    if (word.size() != 0)
        words.insert(word); //  оставшиеся слов помещаем в set

    for (const string& word : words) // выводим наш set в файл (уже отсортирован)
        outputFile << word << endl;

    inputFile.close(); // закрываем файл
    outputFile.close(); // закрываем файл

    delete[] text; // удаление массива
}


int main()
{
    setlocale(LC_ALL, "Russian"); // подключение русского языка для корректного вывода
    unordered_map<char, int> symbols; // unordered_map для символов
    set<string> words; // set для слов (уже отсортирован)

    string line;
    ifstream in("Parse.txt"); // открываем файл для чтения
    ofstream outw("Words.txt"); // открываем файл для записи
    ofstream outs("Symbols.txt"); // открываем файл для записи
    if (in.is_open())
    {
        while (getline(in, line))
        {
            ParseAllSymbols(line, symbols);// получаем все символы и храним их в map
        }
    }
    ParseAndPrintWords(words, "Parse.txt", "Words.txt"); // парсим и сразу выводим все нужные слова
    in.close();// закрываем файл
    PrintAllSymbols(symbols, "Symbols.txt"); // вывод символов в файл
    outw.close(); // закрываем файл
    outs.close(); // закрываем файл
}



