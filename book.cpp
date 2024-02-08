#include "util.h"
#include "book.h"

    Book::Book(const std::string category, const std::string name, double price, int qty,
    const std::string isbn, const std::string author) : Product(category, name, price, qty) {
        isbn_ = isbn;
        author_ = author;
        std::string raw = name_ + "." + isbn_ + "." + author_;
        keywords_ = parseStringToWords(raw); 

        //debug
        //std::set<std::string>::iterator it;
        //for (it = keywords_.begin(); it != keywords_.end(); ++it) std::cout << *it << "yeah" << std::endl;
    }

    std::set<std::string> Book::keywords() const{
        //cout << hi;
        return keywords_;
    }

    std::string Book::displayString() const {
        return name_ + "\n" + "Author: " + author_ + " ISBN: " + isbn_ + "\n" + std::to_string(price_) + " " + std::to_string(qty_) + "left." + "\n";
    }

    bool Book::isMatch(std::vector<std::string>& searchTerms) const {
        std::set<std::string> temp;
        std::set<std::string> temp2;
        for (size_t i = 0; i < searchTerms.size(); i++) {
            temp.insert(searchTerms[i]);
        }
        typename std::set<std::string>::iterator it;
        //!!!!!!!!
        //prime time for errors. *it is a dereferenced pointer. does it insert a duplicate, or the original data?
        for (it = keywords_.begin(); it != keywords_.end(); ++it) {
            temp2.insert(*it);
        }
        std::set<std::string> inter = setIntersection(temp, temp2);
        if (inter.size() > 0) return true;
        return false;
    }

    void Book::dump(std::ostream& os) const {
        Product::dump(os);
        os << isbn_ << "\n" << author_ << std::endl;
    }

