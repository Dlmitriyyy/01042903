#include <iostream>
#include <string>
using namespace std;

class stack_size_error : public std::length_error
{
public:
    explicit stack_size_error(const std::string& msg);
};

class stack_bad_alloc : public std::runtime_error
{
public:
    explicit stack_bad_alloc(const std::string& msg);
};

class stack_overflow : public std::logic_error
{
public:
    explicit stack_overflow(const std::string& msg);
};

class stack_empty : public std::logic_error
{
public:
    explicit stack_empty(const std::string& msg);
};

stack_size_error::stack_size_error(const std::string& msg) : std::length_error(msg) {}
stack_bad_alloc::stack_bad_alloc(const std::string& msg) : std::runtime_error(msg) {}
stack_overflow::stack_overflow(const std::string& msg) : std::logic_error(msg) {}
stack_empty::stack_empty(const std::string& msg) : std::logic_error(msg) {}

class Stack
{
private:
    int stk_size;
    int* stackstore;
    int stacksize;
    int SP;

public:
    Stack();
    ~Stack();
    void Set_Size(int& stk_size);
    int Get_size() const;
    void Display_Stack() const;
    void push(int value);
    int pop(void);
};

Stack::Stack() : stk_size(), stackstore(nullptr), stacksize(0), SP(0) {}

void Stack::Set_Size(int& stk_size)
{
    string temp;

    while (true)
    {
        cout << "Введіть розмір який бажаєте задати стеку: ";
        cin >> temp;

        bool isDigit = true;
        for (char c : temp)
        {
            if (!isdigit(c))
            {
                isDigit = false;
                break;
            }
        }

        if (isDigit)
        {
            stk_size = stoi(temp);
            if (stk_size > 0)
            {
                break;
            }
            else
            {
                cerr << "Невірно вказаний розмір стеку! Введіть розмір знову: ";
            }
        }
        else
        {
            cerr << "Помилка! Розмір стеку не може бути буквеним!" << endl;
        }

        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    stackstore = new int[stk_size];
    stacksize = stk_size;
    SP = 0;
}

void Stack::push(int value)
{
    if (SP == stacksize)
    {
        throw stack_overflow("Переповнення стеку!");
    }
    stackstore[SP++] = value;
}

int Stack::pop(void)
{
    if (SP <= 0)
    {
        throw stack_empty("Помилка, стек порожній!");
    }
    return stackstore[--SP];
}

int Stack::Get_size() const
{
    return stacksize;
}

void Stack::Display_Stack() const
{
    for (int i = SP - 1; i >= 0; i--)
    {
        cout << stackstore[i] << " ";
    }
    cout << endl;
}

Stack::~Stack(void)
{
    delete[] stackstore;
}

int main()
{
    setlocale(LC_ALL, ".1251");
    system("chcp 1251>nul");
    int stacksize;
    int input_num, SP;
    string input;

    cout << "Ця програма створює стек який містить у собі числа, при визові функції 'pop()' зменшується кількість елементів у стеку  на 1 елемент за ітерацію. Для визову функції видалення останнього елемента введіть 'REMOVE', для завершення програми    'EXIT': " << endl << endl;
    Stack stk;
    try
    {
        stk.Set_Size(stacksize);

        while (true)
        {
            cout << endl << "Введіть числа, які будуть додані до стеку. Для видалення останнього числа з стеку введіть 'REMOVE', для завершення програми 'EXIT': ";
            cin >> input;

            if (isdigit(input[0]) || (input[0] == '-' && isdigit(input[1])))
            {
                input_num = stoi(input);
                stk.push(input_num);
                cout << endl << "Елементи стеку: ";
                stk.Display_Stack();
            }
            else if (input == "REMOVE")
            {
                cout << "Стек після видалення елементу: ";
                stk.pop();
                stk.Display_Stack();
            }
            else if (input == "EXIT")
            {
                cout << endl << "Програма завершена." << endl;
                cout << "Елементи стеку: ";
                stk.Display_Stack();
                break;
            }
            else
            {
                cerr << "Помилка! Некоректний ввід елемента!" << endl;
            }
        }
    }
    catch (stack_bad_alloc& s_b)
    {
        cerr << "Помилка виділення пам'яті для стеку!" << endl;
    }
    catch (stack_overflow& s_o)
    {
        cerr << "Помилка, стек переповнений: елемент не був доданий." << endl;
        cout << "Програма завершена." << endl;
        return 0;
    }
    catch (stack_empty& s_em)
    {
        cerr << endl << "Помилка, стек порожній!" << endl;
        cout << "Програма завершена." << endl;
        return 0;
    }
    return 0;
}
