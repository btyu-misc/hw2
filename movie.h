#ifndef MOVIE_H
#define MOVIE_H
#include "product.h"

//Title, Price, Quantity, Genre, Age Rating

class Movie : public Product {
    public:
        Movie(const std::string category, const std::string name, double price, int qty,
        const std::string genre, const std::string rating);

        std::set<std::string> keywords() const override;

        std::string displayString() const override;

        bool isMatch(std::vector<std::string>& searchTerms) const;

        void dump(std::ostream& os) const;

    protected:
        std::string genre_;
        std::string rating_;
        std::set<std::string> keywords_;
};

#endif