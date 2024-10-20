#include <iostream>
#include <cctype>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>

class SheepCounter
{
private:
    bool __was_last_alnum = false;
    bool __was_last_sentence_separator = false;
    bool __was_date = false;
    bool __was_alnum_on_the_line = false;
    bool __was_word_in_sentence = false; 

    // Buffer which stores the last 10 characters of the stream
    // Used to check if the last 10 characters were of format DD.MM.YYYY
    std::string __last_10_chars = "xxxxxxxxxx"; 

    // Buffer which stores consecutive digits.
    // Used to calculate the sum of all numbers in the stream(s).
    std::string __digits_buffer = "";

    std::vector<char> __sentence_separators = {'.', '!', '?'};

    bool is_sentence_separator(const char &c)
    {
        return std::find(__sentence_separators.begin(), __sentence_separators.end(), c) != __sentence_separators.end();
    }

    bool were_last_10_chars_a_date()
    {
        if (__last_10_chars.length() != 10)
            throw std::invalid_argument("Buffer should have exactly 10 characters long! Something is not right with how you append and/or erase characters.");

        std::vector<int> digit_positions = {0, 1, 3, 4, 6, 7, 8, 9};
        std::vector<int> dot_positions = {2, 5};
        bool result = true;
        for (int idx : digit_positions)
            result &= isdigit(__last_10_chars[idx]);

        for (int idx : dot_positions)
            result &= __last_10_chars[idx] == '.';

        return result;
    }

    void check_for_new_words_and_numbers(char c) 
    {
        if (!__was_last_alnum && isalpha(c))
        {
            __was_word_in_sentence = true;
            ++number_of_words;
        }

        if (!__was_last_alnum && isdigit(c))
            ++number_of_numbers;
    }

    void check_for_new_lines(char c) 
    {
        if (c == '\n')
        {
            if (__was_alnum_on_the_line)
                ++number_of_lines;

            __was_alnum_on_the_line = false;
        }
    }

    void check_for_date(char c) 
    {
        /*
            How the below works: 
            
            When we encounter first dot of the date, we increase the number of sentences (given that we saw alphanumerical character in this sentence already).
            So we need to make sure that we don't increase sentence counter again (because we already counted this sentence, although not the right place...)
            To prevent this, consider two cases:

            1) after DD.MM.YYYY, we get sentence separator (meaning, there were no alphanumerical chars beetween last `Y` and the sentence separator)
                then, we don't count ".YYYY{ |.|!|?}" as a sentence because of how we agreed what a sentence is - it has to have at least one alphanumerical character.
                therefore, sentence ends and we do nothing. just continue.

            2) after DD.MM.YYYY, we encounter an alphanumerical character before the sentence separator.
                this means that now we will increment number of sentences, counting `YYYY[a-Z|0-9]*[.!?]` as a sentence.
                it is wrong, so just decrement the sentence counter. 
        */
        if (__was_date && is_sentence_separator(c))
            __was_date = false;
        else if (__was_date && isalpha(c)) 
        {
            number_of_sentences -= 1;
            __was_date = false;
        }

        if (were_last_10_chars_a_date())
            __was_date = true;

        __last_10_chars.push_back(c);
        __last_10_chars.erase(0, 1);
    }

    void process_digits_buffer(char c) 
    {
        if (isdigit(c))
            __digits_buffer.push_back(c);
        else if (!__digits_buffer.empty()) 
        {
            uint number = std::stoi(__digits_buffer);
            numbers_sum += number;
            __digits_buffer.clear();
        }
    }

    void check_for_new_sententence(char c) {
        if (__was_word_in_sentence && is_sentence_separator(c))
        {
            ++number_of_sentences;
            __was_word_in_sentence = false;
        }
    }

    void process(const char &c)
    {
        ++number_of_characters;

        if (isalnum(c))
            __was_alnum_on_the_line = true;

        check_for_new_words_and_numbers(c);

        check_for_new_sententence(c);
        check_for_new_lines(c);

        check_for_date(c);
        process_digits_buffer(c);

        __was_last_sentence_separator = is_sentence_separator(c);
        __was_last_alnum = isalnum(c);
    }

public:
    uint number_of_characters = 0;
    uint number_of_words = 0;
    uint number_of_numbers = 0;
    uint number_of_sentences = 0;
    uint number_of_lines = 0;
    uint numbers_sum = 0;

    void count(std::istream &s)
    {
        char c;
        for (;;)
        {
            c = s.get();
            if (s.fail())
                break;
            process(c);
        }

        if (__was_alnum_on_the_line)
            ++number_of_lines; 

        if (__was_word_in_sentence) 
            ++number_of_sentences;
    }

    void count(char* sources[], int n)
    {
        for (int i = 1; i < n; i++)
        {
            std::ifstream f;
            std::string source = sources[i];
            f.open(source);
            if (f.good())
                count(f);
        }
    }

    void print() 
    {
        std::cout << "znaku: "  << number_of_characters << std::endl;
        std::cout << "slov: "   << number_of_words      << std::endl;
        std::cout << "vet: "    << number_of_sentences  << std::endl;
        std::cout << "radku: "  << number_of_lines      << std::endl;
        std::cout << "cisel: "  << number_of_numbers    << std::endl;
        std::cout << "soucet: " << numbers_sum          << std::endl;
    }
};

int main(int argc, char* argv[]) {
    SheepCounter counter;
    
    if (argc == 1) {
        counter.count(std::cin);
    } else {
        counter.count(argv, argc);
    }

    counter.print();
    return 0;
}