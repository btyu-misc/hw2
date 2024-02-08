#include "datastore.h"
#include <map>
#include <fstream>
#include "movie.h"
#include "clothing.h"
#include "book.h"

class MyDataStore : public DataStore {
    public: 
        MyDataStore() {}
        ~MyDataStore();

        void addProduct(Product* p);

        void addUser(User* u);

        std::vector<Product*> search(std::vector<std::string>& terms, int type);

        void dump(std::ostream& ofile);

        void addToCart(std::vector<Product*> hits, std::string username, int num);

        std::string viewCart(std::string username);

        void buyCart(std::string username);

        void quit(std::string filename);

        bool checkUser(std::string username);

    protected:
        std::vector<Product*> products_;
        std::map<std::string, User*> usernames_;
        std::map<User*, std::vector<Product*>*> users_;
        std::map<std::string, std::vector<Product*>*> keyProd_;
};