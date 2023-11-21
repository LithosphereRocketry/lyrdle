#ifndef SUBSTRING_H
#define SUBSTRING_H

#include <vector>
#include <set>

#include "token.h"

namespace substring {
    typedef int TOK;
    typedef size_t IND;
    typedef std::map<TOK, IND> MAP;
    struct Bucket {
        IND pos;
        IND len = 0;
    };
    typedef std::map<TOK, Bucket> BMAP;

    struct Classification {
        std::vector<IND> S;
        std::vector<IND> L;
    };

    struct BucketedStr {
        BMAP buckets;
        std::vector<IND> contents;
    };

    // Based on Ko and Aluru, 2005
    // O(n) time
    Classification classify(std::vector<TOK> str) {
        Classification result;
        IND done_ind = 0;
        for(IND i = done_ind+1; i < str.size(); i++) {
            if(str[i] > str[done_ind]) {
                for(; done_ind < i; done_ind++) {
                    result.S.push_back(done_ind);
                }
            }
            if(str[i] < str[done_ind]) {
                for(; done_ind < i; done_ind++) {
                    result.L.push_back(done_ind);
                }
            }
        }
        result.L.push_back(str.size()-1);
        result.S.push_back(str.size()-1);
        return result;
    }
    // O(n log n + k), O(n + k) if substituted for unordered_map
    // where k is alphabet size
    BucketedStr bucket(std::vector<TOK> str) {
        BucketedStr result;
        
        TOK tmin = str[0];
        TOK tmax = str[0];
        for(TOK t : str) {
            result.buckets[t].len ++;
            tmin = std::min(tmin, t);
            tmax = std::max(tmax, t);
        }
        IND ind = 0;
        for(TOK t = tmin; t <= tmax; t++) {
            if(result.buckets.contains(t)) {
                result.buckets[t].pos = ind;
                ind += result.buckets[t].len;
            }
        }
        MAP indices;
        result.contents.resize(str.size());
        for(int i = 0; i < str.size(); i++) {
            TOK t = str[i];
            result.contents[result.buckets[t].pos + indices[t]] = i;
            indices[t] ++;
        }
        return result;
    }

    // O(n log n), O(n) with unordered_set
    std::vector<IND> sDist(std::vector<IND> S) {
        IND imax = 0;
        std::set<IND> S_set;
        for(IND i : S) {
            S_set.insert(i);
            imax = std::max(i, imax);
        }
        std::vector<IND> result(imax+1);
        IND lastS = -1;
        for(int i = 0; i <= imax; i++) {
            result[i] = (lastS == -1) ? 0 : i-lastS;
            if(S_set.contains(i)) { lastS = i; }
        }
        return result;
    }

    std::vector<IND> suffixArray(std::vector<TOK> str) {
        Classification c = classify(str);
        BucketedStr b = bucket(str);
        
        return std::vector<IND>();
    }


    // Find the longest common substring between two strings
    // This should in theory be O(n+m)
    template <class T>
    std::vector<T> lcs(const std::vector<T>& a, const std::vector<T>& b) {
        // TODO: this should really accept all containers
        // there's probably a clean way to do that with
        // TMP and/or concepts but idk what it is

        static TokenSet<T, TOK> tks;

        std::vector<TOK> a_tok(a.size()+1);
        for(size_t i = 0; i < a_tok.size(); i++) {
            a_tok[i] = tks.encode(a[i]);
        }
        a_tok[a.size()] = -1;

        std::vector<TOK> b_tok(b.size()+1);
        for(size_t i = 0; i < b_tok.size(); i++) {
            b_tok[i] = tks.encode(b[i]);
        }
        b_tok[b.size()] = -1;

        // in progress

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