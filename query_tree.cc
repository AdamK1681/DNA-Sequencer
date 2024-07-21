/*
Adam Kucharzewski
Email: Adam.Kucharzewski94@myhunter.cuny.edu
Main file for Part2(a) of Homework 2.
This file containts the QueryTree function, which acts as a parser which creates a search tree, after being provided a database file and tree type from the user
*/
#include "avl_tree.h"
#include "bst_tree.h"
#include "sequence_map.h"

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

namespace {

bool getNextRecogSeq(const string &line, string &seq, int &slash) {
  int next_slash_position = line.find("/", slash+1);
  if (next_slash_position == string::npos) {
    return false;
  } 
  else {
    seq = line.substr(slash+1, next_slash_position-slash-1);
    slash = next_slash_position;
    return true;
  }
}

string getAcro(const string &line, const int &slash) {
  return (line.substr(0, slash));
}

// @db_filename: an input filename.
// @a_tree: an input tree of the type TreeType. It is assumed to be
//  empty.
template <typename TreeType>
void QueryTree(const string &db_filename, TreeType &a_tree) {
  ifstream file(db_filename);
  string garbage, lines, enzymeAcro; //Garbage is the initial lines of the document (which are to be ignored)
  for (int i = 0; i < 10; i++) {
    getline(file, garbage);
  }
  while(getline(file, lines)) {
      int slash = lines.find('/'); 
      string seq = lines.substr(0, slash);
      enzymeAcro = getAcro(lines, slash);
      while (getNextRecogSeq(lines, seq, slash)) {
        SequenceMap seqMap(seq, enzymeAcro); 
        a_tree.insert(seqMap); 
      }
  }

  string s1, s2, s3;
  cin >> s1 >> s2 >> s3;

  SequenceMap map1(s1, "");
  SequenceMap map2(s2, "");
  SequenceMap map3(s3, "");

	for (int i = 0; i < 3; i++)
	{}
	
  cout << a_tree.getEnzymeAcronym(map1) << endl;
  cout << a_tree.getEnzymeAcronym(map2) << endl;
  cout << a_tree.getEnzymeAcronym(map3) << endl;
}

}  // namespace

int
main(int argc, char **argv) {
  if (argc != 3) {
    cout << "Usage: " << argv[0] << " <databasefilename> <tree-type>" << endl;
    return 0;
  }
  const string db_filename(argv[1]);
  const string param_tree(argv[2]);
  cout << "Input filename is " << db_filename << endl;
  cout << "Type of tree is " << param_tree << endl;
  if (param_tree == "BST") {
    // Note that you will replace BinarySearchTree<int> with BinarySearchTree<SequenceMap>
    BinarySearchTree<SequenceMap> a_tree;
    QueryTree(db_filename, a_tree);
  } else if (param_tree == "AVL") {
    // Note that you will replace AvlTree<int> with AvlTree<SequenceMap>
    AvlTree<SequenceMap> a_tree;
    QueryTree(db_filename, a_tree);
  } else {
    cout << "Uknown tree type " << param_tree << " (User should provide BST, or AVL)" << endl;
  }
  return 0;
}
