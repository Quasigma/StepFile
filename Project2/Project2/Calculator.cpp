#include "Header.h"
using namespace std;

int priority(char op) {   // функция для определения приоритета оператора
	if (op == '+' || op == '-') return 1;
	if (op == '*' || op == '/') return 2;
	return 0;
}
double apply_op(double num1, double num2, char op) {   // функция для выполнения операции
    switch (op) {
    case '+':
        return num1 + num2;

    case '-':
        return num1 - num2;

    case '*':
        return num1 * num2;

    case '/':
        if (num1 / 0)
            cout << "На ноль делить нельзя!";
        break;
       
    default:
        return 0;   // сообщение об ошибке, если оператор не допустим
    }
}

double evaluate(string expr) {   // функция для вычисления значения выражения
    stack<double> values;   // стек для хранения чисел
    stack<char> ops;   // стек для хранения операторов

    for (int i = 0; i < expr.length(); i++) {
        if (expr[i] == ' ') continue;   // пропускаем пробелы

        if (expr[i] == '(') {   // если встретили открывающую скобку
            ops.push(expr[i]);
        }

        else if (isdigit(expr[i])) {   // если встретили цифру
            double num = 0;
            while (i < expr.length() && isdigit(expr[i])) {
                num = num * 10 + (expr[i] - '0');
                i++;
            }
            i--;

            values.push(num);
        }

        else if (expr[i] == ')') {   // если встретили закрывающую скобку
            while (!ops.empty() && ops.top() != '(') { //empty - Проверяет, является ли stack пустым.  pop -	Удаляет элемент из верхней части stack.
                double num2 = values.top(); values.pop();
                double num1 = values.top(); values.pop();
                char op = ops.top(); ops.pop();

                values.push(apply_op(num1, num2, op)); //push Добавляет элемент в верхнюю часть stack.
            }
            if (!ops.empty()) ops.pop();   // удаляем открывающую скобку
        }

        else {   // если встретили оператор
            while (!ops.empty() && priority(ops.top()) >= priority(expr[i])) {
                double num2 = values.top(); values.pop();
                double num1 = values.top(); values.pop();
                char op = ops.top(); ops.pop();

                values.push(apply_op(num1, num2, op));
            }

            ops.push(expr[i]);
        }
    }

    while (!ops.empty()) { // выполняем оставшиеся операции
        double num2 = values.top(); values.pop();
        double num1 = values.top(); values.pop();
        char op = ops.top(); ops.pop();
        values.push(apply_op(num1, num2, op));
    }

    return values.top(); // возвращаем результат
}
void Init()
{
    setlocale(LC_ALL, "rus");
    system("color 07");

    CursorHide(FALSE, 20);
}
void StartCalc()
{
    system("cls");
    string expr;
    cout << "Введите выражение: ";
    getline(cin, expr);
    double result = evaluate(expr);
    cout << "Result = " << result << endl;
    system("pause");
    system("cls");
    
}
int menuRow = 3; int menuCol = 6;
int gameRow = 3; int gameCol = 6;
int Select = 0;
int FieldX = 0;
int colSelFon = _COLOR::light_green;
int colSelSym = _COLOR::red;
int colunselFon = _COLOR::black;
int colunselSym = _COLOR::white;

void CalcLoop()
{

    while (true)
    {
        if (Select == 0)
            SetColor(colSelFon, colSelSym);
        else
            SetColor(colunselFon, colunselSym);
        SetPos(menuRow + 0, menuCol);
        cout << "Вычисление Выражений";
        if (Select == 1)
            SetColor(colSelFon, colSelSym);
        else
            SetColor(colunselFon, colunselSym);
        SetPos(menuRow + 1, menuCol);
        cout << "Выход";
        

        if (_kbhit())
        {
            int key;
            key = _getch();
            // если пользователь нажал на кнопку - узнать какаяэта кнопка
            // и изменить селект
            switch (key)
            {
            case _KEY::UP:
                if (Select == 0)
                    Select = 1;
                else
                    Select--;
                break;
            case _KEY::DOWN:
                if (Select == 1)
                    Select = 0;
                else
                    Select++;
                break;
            case _KEY::ENTER:
                switch (Select)
                {
                case 0: StartCalc(); break;
                case 1: return;
                default:
                    break;
                }
            default:
                break;
            }
        }
    }
   
}
int main()
{
    Init();
    CalcLoop();

    return 0;
}
	
