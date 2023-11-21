#include <string>
#include <map>

#include "substring.h"

using namespace std;
using namespace substring;

int main(int argc, char** argv) {
    string str1 = "MISSISSIPPI$";
    vector<TOK> iw1(str1.begin(), str1.end());

    Classification c = classify(iw1);
    cout << "S: ";
    for(IND i : c.S) {
        cout << i+1 << ", ";
    }
    cout << "\nL: ";
    for(IND i : c.L) {
        cout << i+1 << ", ";
    }
    cout << "\n\n";
    
    for(int i = 0; i < str1.size(); i++) {
        cout << i << "\t";
    }
    cout << "\n";
    for(char c : str1) {
        cout << c << "\t";
    }
    cout << "\n\n";
    std::vector<IND> dist = sDist(c.S);
    for(IND i : dist) {
        cout << i << "\t";
    }
    cout << "\n\n";
    
    BucketedStr b = bucket(iw1);
    std::vector<char> legend(iw1.size(), '-');
    for(pair<TOK, Bucket> p : b.buckets) {
       legend[p.second.pos] = p.first;
    }
    for(char c : legend) {
        cout << c << "\t";
    }
    cout << "\n";
    for(IND c : b.contents) {
        cout << (c+1) << "\t";
    }
    cout << "\n";

}