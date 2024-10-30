#include <iostream>
#include "Dictionary.h"
#include "utils.cpp"

int main()
{
    Dictionary d;
    d.add("ahoj", "privet");
    d.add("ahoj", "zdravstvuj");
    d.add("ahoj", "poka");

    auto translations_of_ahoj = d.find("ahoj");
    print_set(translations_of_ahoj);
}
