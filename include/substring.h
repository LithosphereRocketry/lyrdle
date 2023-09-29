#ifndef SUBSTRING_H
#define SUBSTRING_H

#include <vector>

#include "token.h"

namespace substring {
    // Find the longest common substring between two strings
    // This should in theory be O(n+m)
    template <class T>
    std::vector<T> lcs(const std::vector<T>& a, const std::vector<T>& b) {
        // TODO: this should really accept all containers
        // there's probably a clean way to do that with
        // TMP and/or concepts but idk what it is

        static TokenSet<T, int> tks;

        std::vector<int> a_tok(a.size());
        for(size_t i = 0; i < a_tok.size(); i++) {
            a_tok[i] = tks.encode(a[i]);
        }

        std::vector<int> b_tok(b.size());
        for(size_t i = 0; i < a_tok.size(); i++) {
            a_tok[i] = tks.encode(a[i]);
        }
        
        std::cout << tks << "\n";

        return std::vector<T>();
    }

    // Find the k-th longest common substring between two strings
    // This should in theory be O((n+m)k)
    template <class T>
    std::vector<T> lcs(const std::vector<T>& a, const std::vector<T>& b, int k) {

        // TODO: write this function
    }

}

#endif