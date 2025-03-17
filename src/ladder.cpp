#include "ladder.h"
#include <algorithm>
void error(string word1, string word2, string msg){
    cout << word1 << " " << word2 << " " << msg << endl;
}
bool edit_distance_within(const std::string& str1, const std::string& str2, int d){
    if (abs(static_cast<ptrdiff_t>(str1.size()) - static_cast<ptrdiff_t>(str2.size())) > d){
        return false;
    }
    if (str1 == str2){
        return false;
    }
    int m = str1.size() + 1;
    int n = str2.size() + 1;
    vector<vector<int>> v(m, vector<int>(n));
    // for (int i = 0; i < m; ++i){
    //     for (int j = 0; j < n; ++j){
    //         v[i][j] = 0;
    //     }
    // }
    for (int i = 1; i < m; ++i){
        v[i][0] = i;
    }
    for (int i = 1; i < n; ++i){
        v[0][i] = i;
    }
    for (int i = 1; i < m; ++i){
        for (int j = 1; j < n; ++j){
            int c = 0;
            if (str1[i-1] != str2[j-1]){
                c = 1;
            }
            v[i][j] = min({v[i-1][j] + 1, v[i][j-1] + 1, v[i-1][j-1] + c});
        }
    }
    return v[m-1][n-1] <= d;
}
bool is_adjacent(const string& word1, const string& word2){
    // if (!edit_distance_within(word1, word2, 1)){
    //     return false;
    // }
    if (abs(static_cast<ptrdiff_t>(word1.size()) - static_cast<ptrdiff_t>(word2.size())) > 1){
        return false;
    }
    if (word1 == word2){
        return false;
    }
    int m = word1.size() + 1;
    int n = word2.size() + 1;
    vector<vector<int>> v(m, vector<int>(n));
    // for (int i = 0; i < m; ++i){
    //     for (int j = 0; j < n; ++j){
    //         v[i][j] = 0;
    //     }
    // }
    for (int i = 1; i < m; ++i){
        v[i][0] = i;
    }
    for (int i = 1; i < n; ++i){
        v[0][i] = i;
    }
    for (int i = 1; i < m; ++i){
        for (int j = 1; j < n; ++j){
            int c = 0;
            if (word1[i-1] != word2[j-1]){
                c = 1;
            }
            v[i][j] = min({v[i-1][j] + 1, v[i][j-1] + 1, v[i-1][j-1] + c});
        }
    }
    return v[m-1][n-1] == 1;
}
vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list){
    if (begin_word == end_word){//or end_word not in word_list?
        error(begin_word, end_word, "are the same");
        return vector<string>();
    }
    bool continue0 = true;
    bool continue1 = false;
    for (auto e: word_list){
        // if (e == begin_word){
        //     error(begin_word, " ", "is in word_list");
        //     continue0 = false;
        //     return vector<string>();
        // }
        if (e == end_word){
            continue1 = true;
            break;
        }
    }
    if (continue1 && continue0){
    queue<vector<string>> q;
    q.push({begin_word});
    set<string> visited;
    visited.insert(begin_word);
    while (!q.empty()){
        vector<string> v = q.front();
        q.pop();
        string last = v[v.size()-1];
        for (auto word : word_list){
            if (is_adjacent(last, word)){
                if (visited.find(word) == visited.end()){
                    visited.insert(word);
                    vector<string> v2{v};
                    v2.push_back(word);
                    if (word == end_word){
                        return v2;
                    }
                    q.push(v2);
                }
            }
        }
    }
    }
    return vector<string>();
}
void load_words(set<string> & word_list, const string& file_name){
    ifstream file(file_name);
    string line;
    if (!file){
        cout << "file not found" << endl;
        return;
    }
    while(file >> line){
        for (char &e: line){
            e = tolower(e);
        }
        word_list.insert(line);
    }
    file.close();
}
void print_word_ladder(const vector<string>& ladder){
    if (ladder.size() == 0){
        cout << "No word ladder found." << endl;
    }
    else {
    cout << "Word ladder found: ";
    for (auto e: ladder){
        cout << e << " ";
    }
    cout << endl;
    }
}
void verify_word_ladder(){
    set<string> word_list;
    load_words(word_list, "src/words.txt");
    my_assert(generate_word_ladder("cat", "dog", word_list).size() == 4);
    my_assert(generate_word_ladder("marty", "curls", word_list).size() == 6);
    my_assert(generate_word_ladder("code", "data", word_list).size() == 6);
    my_assert(generate_word_ladder("work", "play", word_list).size() == 6);
    my_assert(generate_word_ladder("sleep", "awake", word_list).size() == 8);
    my_assert(generate_word_ladder("car", "cheat", word_list).size() == 4);
}
void my_assert(bool e){
    cout << "e" << ((e) ? " passed" : " failed") << endl;
}
// bool is_adjacent(const string& word1, const string& word2){
//     if (!edit_distance_within(word1, word2, 1)){
//         return false;
//     }
//     int count = 0;
//     if (word1.size() == word2.size()){
//         for (int i = 0; i < word1.size(); ++i){
//             if (word1[i] != word2[i]){
//                 ++count;
//             }
//         }
//         if (count != 1){
//             return false;
//         }
//         return true;
//     }
//     else{
//         int size = 0;
//         if (word1.size()>word2.size()){
//             size = word2.size();
//         }
//         else {
//             size = word1.size();
//         }
//         for (int i = 0; i < size; ++i){
//             if (word1[i] != word2[i]){
//                 ++count;
//             }
//         }
//         if (count >= 2){
//             return false;
//         }
//         else if (count == 0){
//             return true;
//         }
//         else { //different by 1 before the last letter

//         }
//     }
// }