#include "Header.h"
using namespace std;

int priority(char op) {   // ������� ��� ����������� ���������� ���������
	if (op == '+' || op == '-') return 1;
	if (op == '*' || op == '/') return 2;
	return 0;
}
double apply_op(double num1, double num2, char op) {   // ������� ��� ���������� ��������
    switch (op) {
    case '+':
        return num1 + num2;

    case '-':
        return num1 - num2;

    case '*':
        return num1 * num2;

    case '/':
        if (num1 / 0)
            cout << "�� ���� ������ ������!";
        break;
       
    default:
        return 0;   // ��������� �� ������, ���� �������� �� ��������
    }
}

double evaluate(string expr) {   // ������� ��� ���������� �������� ���������
    stack<double> values;   // ���� ��� �������� �����
    stack<char> ops;   // ���� ��� �������� ����������

    for (int i = 0; i < expr.length(); i++) {
        if (expr[i] == ' ') continue;   // ���������� �������

        if (expr[i] == '(') {   // ���� ��������� ����������� ������
            ops.push(expr[i]);
        }

        else if (isdigit(expr[i])) {   // ���� ��������� �����
            double num = 0;
            while (i < expr.length() && isdigit(expr[i])) {
                num = num * 10 + (expr[i] - '0');
                i++;
            }
            i--;

            values.push(num);
        }

        else if (expr[i] == ')') {   // ���� ��������� ����������� ������
            while (!ops.empty() && ops.top() != '(') { //empty - ���������, �������� �� stack ������.  pop -	������� ������� �� ������� ����� stack.
                double num2 = values.top(); values.pop();
                double num1 = values.top(); values.pop();
                char op = ops.top(); ops.pop();

                values.push(apply_op(num1, num2, op)); //push ��������� ������� � ������� ����� stack.
            }
            if (!ops.empty()) ops.pop();   // ������� ����������� ������
        }

        else {   // ���� ��������� ��������
            while (!ops.empty() && priority(ops.top()) >= priority(expr[i])) {
                double num2 = values.top(); values.pop();
                double num1 = values.top(); values.pop();
                char op = ops.top(); ops.pop();

                values.push(apply_op(num1, num2, op));
            }

            ops.push(expr[i]);
        }
    }

    while (!ops.empty()) { // ��������� ���������� ��������
        double num2 = values.top(); values.pop();
        double num1 = values.top(); values.pop();
        char op = ops.top(); ops.pop();
        values.push(apply_op(num1, num2, op));
    }

    return values.top(); // ���������� ���������
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
    cout << "������� ���������: ";
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
        cout << "���������� ���������";
        if (Select == 1)
            SetColor(colSelFon, colSelSym);
        else
            SetColor(colunselFon, colunselSym);
        SetPos(menuRow + 1, menuCol);
        cout << "�����";
        

        if (_kbhit())
        {
            int key;
            key = _getch();
            // ���� ������������ ����� �� ������ - ������ �������� ������
            // � �������� ������
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
	
