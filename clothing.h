#ifndef CLOTHING_H
#define CLOTHING_H
//Name, Price, Quantity, Size, Brand
#include "product.h"

//Title, Price, Quantity, Genre, Age Rating

class Clothing : public Product {
    public:
        Clothing(const std::string category, const std::string name, double price, int qty,
        const std::string size_, const std::string brand_);

        std::set<std::string> keywords() const override;

        std::string displayString() const override;

        bool isMatch(std::vector<std::string>& searchTerms) const;

        void dump(std::ostream& os) const;

    protected:
        std::string size_;
        std::string brand_;
        std::set<std::string> keywords_;
};
#endif