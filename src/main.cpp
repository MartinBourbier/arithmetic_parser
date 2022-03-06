#include "reducto.h"

#include <iostream>
#include <string>

int main(void)
{
    while (true)
    {
        std::cout << "> ";

        std::string expr;
        std::getline(std::cin, expr);

        if (expr.size() == 0)
            continue;

        std::cout << Reducto::Parse(expr).ToString() << '\n';
    }

    std::cout << std::endl;

    return 0;
}
