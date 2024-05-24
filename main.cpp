#include <cstdio>
#include <csignal>
#include <iostream>
#include <string>
#include <vector>

void signal_event(int sig);
int to_number(std::string& s, int base);
std::vector<std::string> split_string(const std::string& str, int* op);
int get_base(const std::string& str);

bool should_close = false;

class Number
{
private:
    int n = 0;

public:
    Number() : n(0) { }
    explicit Number(int a) : n(a) { }

    void set(int a)
    {
        n = a;
    }

    void print() const
    {
        printf("hex = %8x , oct = %6o , dec = %10d\n", n, n, n);
    }
};

int main()
{
    signal(SIGINT, signal_event);

    while (!should_close)
    {
        Number a(0);
        Number b(0);
        Number r(0);

        int op = 0;
        int aa = 0;
        int bb = 0;
        int res = 0;

        std::string s;
        std::vector<std::string> s2;

        while (std::getline(std::cin >> std::ws, s))
        {
            if(s == "q" || s == "quit")
            {
                should_close = true;
                break;
            }
            printf("------------------------------\n");
            s2 = split_string(s, &op);
            int base_aa = get_base(s2[0]);
            int base_bb = get_base(s2[1]);
            aa = to_number(s2[0], base_aa);
            bb = to_number(s2[1], base_bb);

            a.set(aa);
            b.set(bb);


            if(op == 1)
            {
                res = aa + bb;
            } else if(op == 2)
            {
                res = aa - bb;
            }
            else
            {
                res = aa * bb;
            }
            r.set(res);

            printf("%4s : ", s2[0].c_str());
            a.print();
            printf("%4s : ", s2[1].c_str());
            b.print();
            printf("%4s : ", "res");
            r.print();
        }

        if(should_close)
        {
            // 由 Ctrl + C 中断信号使得 should_close = true
            break;
        }
    }

    system("pause");
    return 0;
}

std::vector<std::string> split_string(const std::string& str, int* op)
{
    std::vector<std::string> parts;
    std::string current_part;

    for (char c : str)
    {
        if (c == '+' || c == '-' || c == '*')
        {
            if(c == '+')
            {
                *op = 1;
            }
            else if(c == '-')
            {
                *op = 2;
            }
            else
            {
                *op = 3;
            }
            parts.push_back(current_part);
            current_part.clear();
        }
        else if(c != ' ')
        {
            current_part += c;
        }
    }

    parts.push_back(current_part);
    return parts;
}

int to_number(std::string& s, int base)
{
    return std::stoi(s, nullptr, base);
}

int get_base(const std::string& str)
{
    if (str.size() >= 2 && str[0] == '0' && (str[1] == 'x' || str[1] == 'X')) {
        return 16;
    } else if (!str.empty() && str[0] == '0') {
        return 8;
    } else {
        return 10; // 10 进制
    }
}

void signal_event(int sig)
{
    should_close = true;
    printf("\n");
    printf("Hex Calc Exit");
}
