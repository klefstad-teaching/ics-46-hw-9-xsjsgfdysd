#include <gtest/gtest.h>

#include "../src/dijkstras.h"
#include "../src/ladder.h"

// TEST(Replace, Me) {
//   EXPECT_TRUE(false);
// }




TEST(ladder, edit_distance_within){
  EXPECT_EQ(edit_distance_within("dog", "cat", 1), true);
}

TEST(ladder, edit_distance_within2){
  EXPECT_EQ(edit_distance_within("dog", "catch", 1), false);
}

TEST(ladder, is_adjacent){
  EXPECT_EQ(is_adjacent("bat", "cat"), true);
}

TEST(ladder, is_adjacent2){
  EXPECT_EQ(is_adjacent("dog", "cat"), false);
}

TEST(ladder, generate_word_ladder){
  set<string> words;
  load_words(words, "src/words.txt");
  vector<string> v;
  v = generate_word_ladder("sleep", "awake", words);
  EXPECT_EQ(v.size(), 8);
}

TEST(ladder, generate_word_ladder2){
  set<string> words;
  load_words(words, "src/words.txt");
  vector<string> v;
  v = generate_word_ladder("a", "a", words);
  EXPECT_EQ(v.size(), 0);
}



int main(){
  // set<string> words;
  // load_words(words, "src/words.txt");
  // // int count = 0;
  // // for (auto e: words){
  // //   if (count <= 500){
  // //   cout << e << " ";
  // //   count += 1;
  // //   }
  // // }
  // generate_word_ladder("cat", "dog", words);
  // verify_word_ladder();
  Graph G;
  file_to_graph("src/small.txt", G);
  vector<int> v(G.numVertices, -1);
  vector<int> distance;
  int a = 0;
  int b = 3;
  int c = 3;
  distance = dijkstra_shortest_path(G, a, v);
  for (auto e: distance){
    cout << e << endl;
  }
  vector<int> previous;
  previous = extract_shortest_path(distance, v, b);
  print_path(previous, c);
  return 0;
}
