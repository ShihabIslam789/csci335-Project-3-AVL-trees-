//Shihab Islam


#include "avl_tree.h"
#include "sequence_map.h"
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <cstdlib>

using namespace std;

namespace {

    //  this function goes through the textfile  and inserts the
    //  SequenceMap object into the tree
    template <typename TreeType>
    void parser(const string& dbx_filename, TreeType& a_tree) {
        std::string dbx_line;
        std::string junk;
        std::ifstream fin(dbx_filename.c_str());


        for (int i = 0; i < 10; i++) {
            getline(fin, junk);
        }


        while (getline(fin, dbx_line)) {
            std::string an_enz_acro;
            std::string a_rec_seq;
            dbx_line = dbx_line.substr(0, dbx_line.length() - 2);
            std::stringstream strstream(dbx_line);
            getline(strstream, an_enz_acro, '/');
            while (getline(strstream, a_rec_seq, '/')) {
                SequenceMap new_sequence_map(a_rec_seq, an_enz_acro);
                a_tree.insert(new_sequence_map);
            }
        }

        //allow the user to input the wanted recognition sequence 
        std::string rec_seq_search;
        while (cin >> rec_seq_search) {
            SequenceMap temp(rec_seq_search, "");
            cout << a_tree.find(temp) << endl;
        }


        fin.close();
    }



    // this function calls the parses through the file
    template <typename TreeType>
    void QueryTree(const string& dbx_filename, TreeType& a_tree) {
        parser(dbx_filename, a_tree);
        cout << "   " << endl;
        a_tree.printTree();
    }


}

int main(int argc, char** argv) {
    if (argc != 2) {
        cout << "Usage: " << argv[0] << " <databasefilename>" << endl;
        return 0;
    }
    const string db_filename(argv[1]);
    cout << "Input filename is " << db_filename << endl;
    // Note that you will replace AvlTree<int> with AvlTree<SequenceMap>
    AvlTree<SequenceMap> a_tree;
    QueryTree(dbx_filename, a_tree);
    return 0;
}