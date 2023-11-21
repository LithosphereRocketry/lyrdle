#ifndef TOKEN_H
#define TOKEN_H

#include <vector>
#include <map>
#include <iostream>

template <class T, class I=long>
class TokenSet {
    static_assert(std::is_integral<I>::value,
        "Index to TokenSet must be of integral type");
    public:
        I encode (T item) const {
            return val_to_tok.at(item);
        }
        I encode(T item) {
            try {
                return val_to_tok.at(item);
            } catch(std::out_of_range& e) {
                int index = tok_to_val.size();
                tok_to_val.push_back(item);
                val_to_tok[item] = index;
                return index;
            }
        }
        T decode(I token) const {
            return tok_to_val[token];
        }
        size_t size() {
            return tok_to_val.size();
        }
    private:
        std::vector<T> tok_to_val;
        std::map<T, I> val_to_tok;
};

// make printable
template <class T, class I=long>
inline std::ostream& operator << (std::ostream& os, TokenSet<T, I> ts) {
    for(size_t i = 0; i < ts.size(); i++) {
        os << i << " : " << ts.decode(i) << "\n";
    }
    return os;
}

#endif