#include "util.h"
#include "clothing.h"

    Clothing::Clothing(const std::string category, const std::string name, double price, int qty,
    const std::string size, const std::string brand) : Product(category, name, price, qty) {
        size_ = size;
        brand_ = brand;
        std::string raw = name_ + "." + size_ + "." + brand_;
        keywords_ = parseStringToWords(raw); 
    }

    std::set<std::string> Clothing::keywords() const{
        //cout << hi;
        return keywords_;
    }

    std::string Clothing::displayString() const {
        return name_ + "\n" + "Size: " + size_ + " Brand: " + brand_ + "\n" + std::to_string(price_) + " " + std::to_string(qty_) + "left." + "\n";
    }

    bool Clothing::isMatch(std::vector<std::string>& searchTerms) const {
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

    void Clothing::dump(std::ostream& os) const {
        Product::dump(os);
        os << size_ << "\n" << brand_ << std::endl;
    }

