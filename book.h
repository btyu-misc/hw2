#ifndef BOOK_H
#define BOOK_H
//Title, Price, Quantity, ISBN, Author

#include "product.h"

//Title, Price, Quantity, Genre, Age Rating

class Book : public Product {
    public:
        Book(const std::string category, const std::string name, double price, int qty,
        const std::string isbn, const std::string author);

        std::set<std::string> keywords() const override;

        std::string displayString() const override;

        bool isMatch(std::vector<std::string>& searchTerms) const;

        void dump(std::ostream& os) const;

    protected:
        std::string isbn_;
        std::string author_;
        std::set<std::string> keywords_;
};
#endif