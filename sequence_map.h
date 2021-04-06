// Shihab Islam
/* This file contains a class for sequence map.
   Also implements the big five for sequencemaps
*/

#ifndef SEQUENCE_MAP_H
#define SEQUENCE_MAP_H
#include <vector>
#include <iostream>
#include <string>
using namespace std;

class SequenceMap {
	// Big five

	// default constructor
	SequenceMap() = default;
	//copy constructor
	SequenceMap(const SequenceMap& rhs) = default;
	//move constructor
	SequenceMap(SequenceMap&& rhs) = default;
	// copy assignment
	SequenceMap& operator = (const SequenceMap& rhs) = default;
	// move assignment
	SequenceMap& operator = (SequenceMap&& rhs) = default;
	//destructor 
	~SequenceMap() = default;

	//  parametrized  constructor which creates the sequencemap object from 2 strings
	SequenceMap(const string& a_rec_seq, const string& an_enz_acro) {
		recognition_sequence_ = a_rec_seq;
		enzyme_acronyms_.push_back(an_enz_acro);
	}
	// compares the comaprisons between recognition_sequence-strings
	bool operator< (const SequenceMap& rhs) const {
		return this->recognition_sequence_ < rhs.recognition_sequence_;
	}
	// object that prints enzyme_acronyms_ vector
	friend std::ostream& operator << (std::ostream& out, const SequenceMap& some_sequence_map) {
		for (size_t i{ 0 }; i < some_sequence_map.enzyme_acronyms_.size(); i++) {
			out << some_sequence_map.enzyme_acronyms_[i] << '  ';
		}
		return out;
	}
	// joins objects of sequencemap with current output 
	void Merge(const SequenceMap& other_sequence) {
		for (const auto& x : other_sequence.enzyme_acronyms_) {
			this->enzyme_acronyms_.push_back(x);
		}
	}


private:
	string recognition_sequence_;
	vector<string> enzyme_acronyms_;
};

#endif