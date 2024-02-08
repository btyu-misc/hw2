#include "util.h"
#include "movie.h"

    Movie::Movie(const std::string category, const std::string name, double price, int qty,
    const std::string genre, const std::string rating) : Product(category, name, price, qty) {
        genre_ = genre;
        rating_ = rating;
        std::string raw = name_ + "." + genre_;
        keywords_ = parseStringToWords(raw); 
    }

    std::set<std::string> Movie::keywords() const{
        //cout << hi;
        return keywords_;
    }

    std::string Movie::displayString() const {
        return name_ + "\n" + "Genre: " + genre_ + " Rating: " + rating_ + "\n" + std::to_string(price_) + " " + std::to_string(qty_) + "left." + "\n";
    }

    bool Movie::isMatch(std::vector<std::string>& searchTerms) const {
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

    void Movie::dump(std::ostream& os) const {
        Product::dump(os);
        os << genre_ << "\n" << rating_ << std::endl;
    }

