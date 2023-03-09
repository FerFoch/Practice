#include <vector>
#include <iostream>
#include <string>
#include <string.h>
#include <fstream>
using namespace std;
enum { R = 1, L = -1, H = 0 }; // перечисление/определение своих типов для движения машины
struct State // структура для текущего состояния машины
{
	string q;
	char sym;
};

struct Rule
{
	string text; // содержимое правила
	string curQ; // текущее состояние
	string nextQ; // следующее состояние
	char curSym; // текущий символ
	char nextSym; // следующий символ
	char cmd; // команда на перемещение
};
// структура создана для шаблона ввода состояний, так если мы будем вводить q00*->q01xR, то переменные внутри будут равны :
	// text – q00* ->q01xR
	// curQ – q00
	// nextQ – q01
	// curSym –*
	// nextSym – x
	// cmd – R
	// cmd – R
class MT
{
public:
	MT(string mem, string beg_state, int width) { // конструктор
		this->mem = mem; // память / сама строка
		this->width = width; // ширина записи состояний
		curPos = 0;
		curState.q = beg_state;
		curState.sym = mem[curPos]; // считывание текущего символа который видит машина
		rNum = 0;
	};
	char getSym()const {
		return mem[curPos]; // селектор возврата символа из тек. позиции
	}
	string getState()const { // селектор возврата текущего состояния
		return curState.q;
	}
	string getMem()const { // селектор возврата содержимого ленты
		return mem;
	}
	bool addState(string rule) { // добавление/считывание правила из строки в bool
		rules.push_back(*new Rule);
		rules[rNum].text = rule;
		rules[rNum].curQ.assign(rule, 0, width);
		rules[rNum].curSym = rule[width];
		size_t pos = rule.find("->") + (width - 1);
		rules[rNum].nextQ.assign(rule, pos, width);
		rules[rNum].cmd = rule[rule.length() - 1];
		rules[rNum++].nextSym = rule[rule.length() - 2];
		return true;
	};
	void step() { // шаг машины (влево/вправо)
		int i;
		for (i = 0;i < rNum;i++) {
			if (curState.q == rules[i].curQ && curState.sym == rules[i].curSym)
			{
				if (rules[i].nextSym != ' ')
					mem[curPos] = rules[i].nextSym;
				process(i);
			}
		}
	};
private:
	void process(int i) { // метод/функция процесса работы программы
		if (rules[i].cmd == 'L') // движение влево
			curPos += L;
		else if (rules[i].cmd == 'R') // движение вправо
			curPos += R;
		curState.q = rules[i].nextQ; // переход к следующему состоянию
		if (curPos < 0)
			return;
		if (curPos >= mem.length())
			mem.resize(mem.size() + 1, '^');
		curState.sym = mem[curPos];
	};
	string mem; // содержимое ленты
	int width; // ширина поля записи состояния
	int curPos; // текущая позиция на ленте
	State curState; // текущее состояние машины
	vector<Rule> rules; // вектор правил (программа)
	int rNum; // количество правил
	void EnterData() {
		string mem; // содержимое ленты
		string beg_state; // Начальное состояние машины
		int width; // Ширина поля записи состояний
		cout << "Введите содержимое ленты" << endl; // Ввод ленты
		cin >> mem;
		cout << "Введите начальное состояние" << endl; // Начальное состояние машины
		cin >> beg_state;
		cout << "Введите ширину поля записи состояния" << endl; // Ширина поля записи состояний
		cin >> width;
	}
};
int main() {
	setlocale(LC_ALL, "Russian");
	string mem; // содержимое ленты
	string beg_state; // Начальное состояние машины
	int width; // Ширина поля записи состояний
	void EnterData();
	ofstream outres;
	outres.open("Result.txt");
	MT Machine(mem, beg_state, width); // Пример: "*11x11=*", "q00", 3
	Machine.addState("q00*->q00 R"); // добавления правил(состояний)
	Machine.addState("q001->q00 R");
	Machine.addState("q00x->q01xR");
	Machine.addState("q011->q02aR");
	Machine.addState("q021->q021L");
	Machine.addState("q02a->q02aL");
	Machine.addState("q02=->q02=L");
	Machine.addState("q02x->q03xL");
	Machine.addState("q031->q04aR");
	Machine.addState("q03a->q03aL");
	Machine.addState("q03*->q06*R");
	Machine.addState("q04x->q04xR");
	Machine.addState("q04a->q04aR");
	Machine.addState("q04=->q04=R");
	Machine.addState("q041->q041R");
	Machine.addState("q04*->q051R");
	Machine.addState("q05^->q02*L");
	Machine.addState("q06a->q061R");
	Machine.addState("q06x->q07xR");
	Machine.addState("q07a->q07aR");
	Machine.addState("q071->q02aR");
	Machine.addState("q07=->q08=L");
	Machine.addState("q08a->q081L");
	Machine.addState("q08x->q09 H");
	outres << Machine.getMem() << " " << Machine.getState() << " " << Machine.getSym() << endl; // вывод в консоль getMem - лента, getState - текущее состояние, getSym - символ на котром сейчас указатель
	for (;;) {
		Machine.step(); // шаг машины
		outres << Machine.getMem()<< " " << Machine.getState()<< " " << Machine.getSym() << endl;
		if (Machine.getState() == "q09") // завершение работы после перехода в состояние q09
			break;
	}
	outres.close();
	return 0;
}