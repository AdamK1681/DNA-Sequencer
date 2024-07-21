/*
Adam Kucharzewski
Email: Adam.Kucharzewski94@myhunter.cuny.edu
Main file for Part2(b) of Homework 2.
This file containts the Test function, which acts as a parser which creates a search tree, after being provided a database file and tree type from the user
as well as prints certain assets of the tree.
These assets include, but are not limited to, the number of nodes, average depth, the number of sequences that can be found.
*/
#include "avl_tree.h"
#include "bst_tree.h"
#include "sequence_map.h"

#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
using namespace std;

namespace {

//Helper function returns an enzyme acronym, l stands for line.
string acro(const string &l) 
{
  string acro = "";
  for (int i = 0; i < l.size(); i++) 
  {
    if (l[i] == '/') 
    {
      return acro;
    }
    acro += l[i];
  }
  return acro;
}

vector<string> getRecSeq(string& l)
{
  vector<string> seq;
  string temp = "";
  for (int i = 0; i < l.size(); i++)
  {
    if (temp != "" && l[i] == '/')
    {
      seq.push_back(temp);
      temp = "";
    }
    else
    {
      temp += l[i];
    }
  }
  return seq;
}

// @db_filename: an input database filename.
// @seq_filename: an input sequences filename.
// @a_tree: an input tree of the type TreeType. It is assumed to be
//  empty.
template <typename TreeType>
void TestTree(const string &db_filename, const string &seq_filename, TreeType &a_tree) {
  cout << "here 1" ; 
  fstream f;
  f.open(db_filename, ios::in);
  string l;
  while (getline(f, l))
  {
    string acronym = acro(l);
    vector<string> seq = getRecSeq(l);
    for (int i = 1; i < seq.size(); i++)
    {
      SequenceMap new_map(seq[i], acronym);
      a_tree.insert(new_map);
    }
  }
  cout << "here";
  f.close();
  cout << "2: " << a_tree.nodeNum() << endl; 
  float avg = a_tree.depth()/a_tree.nodeNum(); 
  cout << "3a: " << avg << endl;
  cout << "3b:" << avg/log2(a_tree.nodeNum()) << endl;

  ifstream sequence(seq_filename);
  string str; //Current string to be inspected
  int x = 0; //Number of strings found/succesful quieries
  float y = 0; //Variable that keeps track of number of recursive calls
  while (!sequence.eof())
  {
    getline(sequence, str);
    SequenceMap seqMap(str, "");
    if(!(a_tree.find(seqMap, y))){
      x++;
    }
  }
  sequence.close();
  x++; //For some reason there is an undercount of 1
  cout << "4a: " << x << endl;
  cout << "4b: " << (y/1.5)/x << endl;

  int counter = 2;
  int numDels = 0; //Number of deleted Sequences
  float numRecur = 0; //Number of recursion of the remove function
  string whatever;
  ifstream sequenceDel(seq_filename);
  while(!sequenceDel.eof()){
    getline(sequenceDel,whatever);
    SequenceMap seqDel(whatever, "");
    if(!(a_tree.find(seqDel,numRecur))){
      if(counter % 2 == 0){
        numDels++;
        a_tree.removeRecur(seqDel,y);
      }
    }
    counter++;
  }
  cout << numRecur << " " << numDels << endl;
  cout << "5a: " << numDels << endl;
  cout << "5b: " << numRecur/numDels << endl;
  cout << "6a: " << a_tree.nodeNum() << endl;
  avg = a_tree.depth()/a_tree.nodeNum(); 
  cout << "6b: " << avg << endl;
  cout << "6c: " << avg/log2(a_tree.nodeNum());
  
}

}  // namespace

int 
main(int argc, char **argv) {
  if (argc != 4) {
    cout << "Usage: " << argv[0] << " <databasefilename> <queryfilename> <tree-type>" << endl;
    return 0;
  }
  const string db_filename(argv[1]);
  const string seq_filename(argv[2]);
  const string param_tree(argv[3]);
  cout << "Input file is " << db_filename << ", and sequences file is " << seq_filename << endl;
  cout << "Type of tree is " << param_tree << endl;
  if (param_tree == "BST") {
    BinarySearchTree<SequenceMap> a_tree;
    TestTree(db_filename, seq_filename, a_tree);
  } else if (param_tree == "AVL") {
    AvlTree<SequenceMap> a_tree;
   TestTree(db_filename, seq_filename, a_tree);
  } else {
    cout << "Uknown tree type " << param_tree << " (User should provide BST, or AVL)" << endl;
  }
  return 0;
}
