#ifndef SEQUENCE_MAP_H_
#define SEQUENCE_MAP_H_

#include <iostream>
#include <vector>

/*
Adam Kucharzewski
Email: Adam.Kucharzewski94@myhunter.cuny.edu
Main file for Part2(a) of Homework 2.
This file containts the SequenceMap Class, which holds an enzyme acronym, and its possible recognition sequences.
*/

class SequenceMap{
    public:

    //Big-Five and default constructor
    SequenceMap() = default; //Zero Parameter constructor
    SequenceMap(const SequenceMap &sM) = default; //Copy Consturctor
    SequenceMap& operator=(const SequenceMap &sM) = default; //Copy assignment
    SequenceMap(SequenceMap &&sM) = default; // Move consturctor
    SequenceMap& operator=(SequenceMap &&sM) = default; //Move Assignment
    ~SequenceMap() = default; //Destructor


    //Parameterized constructor. Note that the enzyme_acronyms_ should only have 1 element after this constructor is called 
    SequenceMap(const std::string &a_rec_seq, const std::string &an_enz_acro){
        recongition_sequence_ = a_rec_seq;
        enzyme_acronyms_.push_back(an_enz_acro);
    }

    //Overload for the < operator, meant to compare strings
    bool operator<(const SequenceMap &rhs) const{
        return recongition_sequence_ < rhs.recongition_sequence_;
    }

    //Overload for the > operator, not asked for, but felt necessary
    bool operator>(const SequenceMap &rhs) const{
        return recongition_sequence_ > rhs.recongition_sequence_;
    }

    //Overload for the << operator, prints every element of enzyme_acronyms_ first, then recognition_sequence_
    friend std::ostream &operator<<(std::ostream &out, const SequenceMap &sM){
        for(int i = 0; i < sM.enzyme_acronyms_.size(); ++i){
            out << sM.enzyme_acronyms_[i] << " ";
        }
        out << std::endl;
        return out;
    }

    //Function that merges the enzyme vecotr of 2 Sequeunce Maps
    void Merge(const SequenceMap &other_sequence){
          for(int i = 0; i< other_sequence.enzyme_acronyms_.size(); i++)
              enzyme_acronyms_.push_back(other_sequence.enzyme_acronyms_[i]);
    }

    private:
    std::string recongition_sequence_;
    std::vector<std::string> enzyme_acronyms_;
};

#endif
