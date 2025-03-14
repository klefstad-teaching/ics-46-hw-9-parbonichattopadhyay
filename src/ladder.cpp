#include "ladder.h"

// Print error message and exit
void error(string word1, string word2, string msg) {
    cout << "Error: " << msg << " for words \"" << word1 << "\" and \"" << word2 << "\"" << endl;
}

// Check if two strings are within edit distance d
bool edit_distance_within(const std::string& str1, const std::string& str2, int d) {
    // Return early if the strings differ in length by more than d
    if (abs(int(str1.length()) - int(str2.length())) > d) {
        return false;
    }
    
    // Handle edge cases
    if (str1.empty()) return str2.length() <= d;
    if (str2.empty()) return str1.length() <= d;
    
    // For our algorithm, we only care about d=1
    if (str1.length() == str2.length()) {
        // Check if they differ by exactly one character (replacement)
        int differences = 0;
        for (size_t i = 0; i < str1.length(); i++) {
            if (str1[i] != str2[i]) {
                differences++;
                if (differences > d) {
                    return false;
                }
            }
        }
        return true;
    } else {
        // Check if one is an insertion/deletion of the other
        const string& shorter = (str1.length() < str2.length()) ? str1 : str2;
        const string& longer = (str1.length() > str2.length()) ? str1 : str2;
        
        // We already know they differ by at most d in length
        // For d=1, try to match chars in shorter to a substring of longer
        size_t i = 0, j = 0;
        bool skipped = false;
        
        while (i < shorter.length() && j < longer.length()) {
            if (shorter[i] != longer[j]) {
                if (skipped) {
                    return false; // Already skipped one character
                }
                skipped = true;
                j++; // Skip this character in the longer word
            } else {
                i++;
                j++;
            }
        }
        
        return true;
    }
}

// Check if two words are adjacent (edit distance of 1)
bool is_adjacent(const string& word1, const string& word2) {
    return edit_distance_within(word1, word2, 1);
}

// Generate a word ladder from begin_word to end_word using word_list
vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list) {
    // Check if start and end are the same
    if (begin_word == end_word) {
        return {begin_word};
    }
    
    // Initialize queue of ladders
    queue<vector<string>> ladder_queue;
    ladder_queue.push({begin_word});
    
    // Track visited words
    set<string> visited;
    visited.insert(begin_word);
    
    while (!ladder_queue.empty()) {
        vector<string> ladder = ladder_queue.front();
        ladder_queue.pop();
        
        string last_word = ladder.back();
        
        // Check if last word is adjacent to the target
        if (is_adjacent(last_word, end_word)) {
            ladder.push_back(end_word);
            return ladder;
        }
        
        // Try all words in the dictionary
        for (const string& word : word_list) {
            if (visited.find(word) == visited.end() && is_adjacent(last_word, word)) {
                visited.insert(word);
                vector<string> new_ladder = ladder;
                new_ladder.push_back(word);
                
                // If we found the end word, return the ladder
                if (word == end_word) {
                    return new_ladder;
                }
                
                ladder_queue.push(new_ladder);
            }
        }
    }
    
    // No ladder found
    return {};
}

// Load words from file into the word_list set
void load_words(set<string>& word_list, const string& file_name) {
    ifstream file(file_name);
    string word;
    
    if (!file.is_open()) {
        cerr << "Error: Could not open file " << file_name << endl;
        return;
    }
    
    while (file >> word) {
        // Convert to lowercase for case insensitivity
        transform(word.begin(), word.end(), word.begin(), ::tolower);
        word_list.insert(word);
    }
}

// Print a word ladder
void print_word_ladder(const vector<string>& ladder) {
    if (ladder.empty()) {
        cout << "No word ladder found." << endl;
        return;
    }
    
    for (size_t i = 0; i < ladder.size(); i++) {
        cout << ladder[i];
        if (i < ladder.size() - 1) {
            cout << " → ";
        }
    }
    cout << endl;
}

// Verify word ladder implementation with test cases
void verify_word_ladder() {
    set<string> word_list;
    load_words(word_list, "words.txt");
    
    #define my_assert(e) {cout << #e << ((e) ? " passed": " failed") << endl;}
    
    my_assert(generate_word_ladder("cat", "dog", word_list).size() == 4);
    my_assert(generate_word_ladder("marty", "curls", word_list).size() == 6);
    my_assert(generate_word_ladder("code", "data", word_list).size() == 6);
    my_assert(generate_word_ladder("work", "play", word_list).size() == 6);
    my_assert(generate_word_ladder("sleep", "awake", word_list).size() == 8);
    my_assert(generate_word_ladder("car", "cheat", word_list).size() == 4);
}