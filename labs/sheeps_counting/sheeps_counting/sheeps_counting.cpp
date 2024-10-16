#include <iostream>
#include <cctype>
#include <string>
#include <vector>
#include <algorithm>

/// Character is anything that can be stored in char.
/// Word      is anything that is separated by whitespace (' ', '\t', '\n', '\r' or whatever for which cctype.isspace(char) emits `true`)
/// Sentence  is anything that is separated by a sentence-delimiter ('.', '!', '?') AND a whitespace (or end of stream).

class SheepCounter {
private:
    int __was_last_alnum = false;
    int __was_last_sentence_separator = false;

    int __was_alnum_on_the_line = false;
    int __was_word_in_sentence = false;
    std::string __last_10_chars = "xxxxxxxxxx";     // fill with some default value. used to check dates in "xx.yy.zzzz" format

    std::vector<char> __sentence_separators = { '.', '!', '?' };

    bool is_sentence_separator(const char& c) {
        return std::find(__sentence_separators.begin(), __sentence_separators.end(), c) != __sentence_separators.end();
    }

    // TODO: ugly. can be done better?
    bool check_for_date() {
        if (__last_10_chars.length() != 10)
            throw std::invalid_argument(std::format("String {} should have exactly 10 characters long! Something is not right with how you append and/or erase characters."));
        
        std::vector<int> digit_positions = { 0,1,3,4,6,7,8,9 };
        std::vector<int> dot_positions = { 2,5 };
        bool result = true;
        for (int idx : digit_positions)
            result &= isdigit(__last_10_chars[idx]);
    
        for (int idx : dot_positions)
            result &= __last_10_chars[idx] == '.';

        return result;
    }

    void process(const char& c) {
        ++number_of_characters;

        if (isalnum(c))
            __was_alnum_on_the_line = true;

        if (!__was_last_alnum && isalpha(c)) {
            __was_word_in_sentence = true;
            ++number_of_words;
        }

        if (!__was_last_alnum && isdigit(c))
            ++number_of_numbers;

        if (__was_word_in_sentence && is_sentence_separator(c)) {
            ++number_of_sentences;
            __was_word_in_sentence = false;
        }

        if (c == '\n') {
            if (__was_alnum_on_the_line)
                ++number_of_lines;

            __was_alnum_on_the_line = false;
        }

        if (check_for_date())   // "xx.yy.zzzz" should not be regarded as 3 sentences. if last 10 chars are date, we have 2 extra sentences.
            number_of_sentences -= 2;

        __last_10_chars.append(c);
        __last_10_chars.erase(0, 1);
        
        __was_last_sentence_separator = is_sentence_separator(c);
        __was_last_alnum = isalnum(c);
    }

public:
    int number_of_characters = 0;
    int number_of_words = 0;
    int number_of_numbers = 0;
    int number_of_sentences = 0;
    int number_of_lines = 0; // TODO?

    void count(std::istream& s) {
        char c;
        for (;;) {
            c = s.get();
            if (s.fail())
                break;
            process(c);
        }

        if (!__was_last_alnum) {   // we should regard end of stream as whitespace or sentence separator.
            ++number_of_words;
            ++number_of_lines;// TODO: wrong!
        }
    }

    void count(std:vector<std::istream&> sources) {
        for (auto& s : sources) {
            count(s);
        }
    }
};

