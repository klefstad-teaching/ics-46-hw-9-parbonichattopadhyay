#include "ladder.h"

int main() {
    // Load the dictionary
    set<string> word_list;
    load_words(word_list, "words.txt");
    

    verify_word_ladder();
    return 0;
    
    string start_word, end_word;
    
    cout << "Welcome to Word Ladder Generator!" << endl;
    cout << "This program finds the shortest word ladder between two words." << endl;
    cout << endl;
    
    // Get input from user
    cout << "Enter start word: ";
    cin >> start_word;
    
    cout << "Enter end word: ";
    cin >> end_word;
    
    // Convert to lowercase for consistency
    transform(start_word.begin(), start_word.end(), start_word.begin(), ::tolower);
    transform(end_word.begin(), end_word.end(), end_word.begin(), ::tolower);
    
    // Check if start and end words are the same
    if (start_word == end_word) {
        error(start_word, end_word, "Start and end words cannot be the same");
        return 1;
    }
    
    cout << "Searching for word ladder from \"" << start_word << "\" to \"" << end_word << "\"..." << endl;
    
    // Generate the word ladder
    vector<string> ladder = generate_word_ladder(start_word, end_word, word_list);
    
    // Print the result
    if (ladder.empty()) {
        cout << "No word ladder found between \"" << start_word << "\" and \"" << end_word << "\"." << endl;
    } else {
        cout << "Found word ladder of length " << ladder.size() << ":" << endl;
        print_word_ladder(ladder);
    }
    
    return 0;
}