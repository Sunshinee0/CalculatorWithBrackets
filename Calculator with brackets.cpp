#include <iostream>
#include <string>
#include <stack>

using namespace std;

// Функция, которая определяет, является ли символ оператором
bool IsOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

// Функция, которая возвращает приоритет оператора
int Priority(char c) {
    if (c == '*' || c == '/')
        return 2;
    else if (c == '+' || c == '-')
        return 1;
    else
        return 0;
}

// Функция, которая выполняет операцию между двумя операндами
int Operation(char operation, int operand1, int operand2) {
    switch (operation) {
    case '+':
        return operand1 + operand2;
    case '-':
        return operand1 - operand2;
    case '*':
        return operand1 * operand2;
    case '/':
        return operand1 / operand2;
    default:
        return 0;
    }
}

// Функция, которая вычисляет значение арифметического выражения
int EvaluateExpression(const string& expression) {
    stack<int> operandStack;
    stack<char> operatorStack;

    int len = expression.length();
    for (int i = 0; i < len; i++) {
        char currentChar = expression[i];

        if (currentChar == ' ')
            continue; // Пропускаем пробелы

        if (isdigit(currentChar)) {
            // Если текущий символ - цифра, получаем полное число и добавляем его в стек операндов
            int number = 0;
            while (i < len && isdigit(expression[i])) {
                number = number * 10 + (expression[i] - '0');
                i++;
                /*Когда мы считываем символы строки и встречаем цифру, мы начинаем формировать полное
                число, умножая его текущее значение на 10 и добавляя следующую цифру. Например, если встретили число 123, то вначале будет 0 * 10 + 1 = 1,
                затем 1 * 10 + 2 = 12, и наконец, 12 * 10 + 3 = 123. Таким образом, мы формируем полное число 123.*/
            }
            i--; // Возвращаемся на символ перед числом, чтобы правильно обработать следующий символ
            operandStack.push(number); //добавляем число в стек операндов
        }
        else if (currentChar == '(') {
            // Если текущий символ - открывающая скобка, добавляем ее в стек операторов
            operatorStack.push(currentChar);
        }
        else if (currentChar == ')') {
            // Если текущий символ - закрывающая скобка, выполняем операции до открывающей скобки
            while (!operatorStack.empty() && operatorStack.top() != '(') {
                char op = operatorStack.top();
                operatorStack.pop();

                int operand2 = operandStack.top();
                operandStack.pop();

                int operand1 = operandStack.top();
                operandStack.pop();

                int result = Operation(op, operand1, operand2);
                operandStack.push(result);
            }

            // Удаляем открывающую скобку из стека операторов
            if (!operatorStack.empty())
                operatorStack.pop();
        }
        else if (IsOperator(currentChar)) {
            // Если текущий символ - оператор, выполняем операции с операторами большим или равным приоритетом
            while (!operatorStack.empty() && Priority(operatorStack.top()) >= Priority(currentChar)) {
                char op = operatorStack.top();
                op = operatorStack.top();
                operatorStack.pop();

                int operand2 = operandStack.top();
                operandStack.pop();

                int operand1 = operandStack.top();
                operandStack.pop();

                int result = Operation(op, operand1, operand2);
                operandStack.push(result);
            }

            // Добавляем текущий оператор в стек операторов
            operatorStack.push(currentChar);
        }
    }

    // Выполняем оставшиеся операции в стеках
    while (!operatorStack.empty()) {
        char op = operatorStack.top();
        operatorStack.pop();

        int operand2 = operandStack.top();
        operandStack.pop();

        int operand1 = operandStack.top();
        operandStack.pop();

        int result = Operation(op, operand1, operand2);
        operandStack.push(result);
    }

    // Возвращаем результат вычислений
    return operandStack.top();
}

int main() {
    setlocale(LC_ALL, "");
    string expression;
    while (true) {
        cout << "Введите арифметическое выражение: ";
        getline(cin, expression);
        if (expression == "0") {
            break;
        }
        system("cls");
        int result = EvaluateExpression(expression);
        cout << expression << " = " << result << endl << endl;
        system("pause");
        system("cls");
    }
    return 0;
}