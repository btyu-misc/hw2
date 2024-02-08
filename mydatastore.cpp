#include "mydatastore.h"
#include "util.h"
#include "movie.h"
#include "clothing.h"
#include "book.h"
#include "user.h"

        MyDataStore::~MyDataStore() {
            for (size_t i = 0; i < products_.size(); i++) {
                delete products_[i];
            }
            std::map<User*, std::vector<Product*>*>::iterator it;
            for (it = users_.begin(); it != users_.end(); ++it) {
                delete it->first;
                //i should delete the cart since it's not a pointer
                delete it->second;
            } //MAKE SURE TO DELETE PRODUCT ARRAY FOR KEYWORDS!! NOT DONE YET

            std::map<std::string, std::vector<Product*>*>::iterator it2;
            for (it2 = keyProd_.begin(); it2 != keyProd_.end(); ++it2) {
                delete it2->second;
            }
        }

        void MyDataStore::addProduct(Product* p) {

            products_.push_back(p);
            std::set<std::string> keywords = p->keywords();
            std::set<std::string>::iterator it;

            //debug
            //for (it = keywords.begin(); it != keywords.end(); ++it) std::cout << *it << "yeah" << std::endl;
            //std::cout << "before for loop" << std::endl;

            for (it = keywords.begin(); it != keywords.end(); ++it) {
                //std::cout << *it << std::endl;
                if (keyProd_.find(*it) != keyProd_.end()) keyProd_.find(*it)->second->push_back(p); 
                else {
                    std::vector<Product*>* bro = new std::vector<Product*>;
                    bro->push_back(p);
                    keyProd_.insert(make_pair(convToLower(*it), bro)); 
                }
            }
        }

        void MyDataStore::addUser(User* u) {
            usernames_.insert(make_pair(u->getName(), u));
            users_.insert(make_pair(u, new std::vector<Product*>));
        }

        std::vector<Product*> MyDataStore::search(std::vector<std::string>& terms, int type) {
            std::vector<Product*> ret;

            //for (size_t i = 0; i < terms.size(); i++) std::cout << terms[i] << std::endl;
            //std::cout << std::endl;
            //std::map<std::string, Product*>::iterator keyit;
            //for (keyit = keyProd_.begin(); keyit != keyProd_.end(); ++keyit) std::cout << keyit->first << std::endl;

            //AND
            if (type == 0) {
                for (size_t i = 0; i < terms.size(); i++) {

                    //std::cout<< "AND init" << std::endl;

                    if (keyProd_.find(terms[i]) != keyProd_.end()) {
                        //std::map<std::string, Product*>::iterator it;
                        std::vector<Product*>* temp = keyProd_.find(terms[i])->second;

                        for (size_t k = 0; k < temp->size(); k++) {
                            std::set<std::string> s1; //for search terms
                            std::set<std::string> s2 = temp->at(k)->keywords(); //for product keywords

                            for (size_t j = 0; j < terms.size(); j++) {
                                s1.insert(terms[j]);
                            }

                            //std::set<std::string>::iterator it; 
                            //for (it = s1.begin(); it != s1.end(); ++it) std::cout << *it << std::endl;
                            //for (it = s2.begin(); it != s2.end(); ++it) std::cout << *it << std::endl;                            

                            //if all search terms appear in product keywords
                            //if product is not already in return vector
                            if (setIntersection(s1,s2).size() == s1.size()) {
                                bool dupe = false;
                                for (size_t j = 0; j < ret.size(); j++) {
                                    if (ret[j] == temp->at(k)) {
                                        dupe = true;
                                        break;
                                    }
                                }
                                if (!dupe) ret.push_back(temp->at(k));
                            }

                        } //end of for loop

                    } else std::cout << terms[i] << " is not a keyword!" << std::endl;

                }
            }
            //OR
            else if (type == 1) {

            //std::cout<< "OR init" << std::endl; 
                for (size_t i = 0; i < terms.size(); i++) {
                    //we don't need the UNION function?? all we need to know is if it has the search terms
                    if (keyProd_.find(terms[i]) != keyProd_.end())  {
                        std::vector<Product*>* temp = keyProd_.find(terms[i])->second;
                        for (size_t k = 0; k < temp->size(); k++) {
                            bool dupe = false;
                            for (size_t j = 0; j < ret.size(); j++) {
                                if (ret[j] == temp->at(k)) {
                                        dupe = true;
                                        break;
                                }
                            }
                            if (!dupe) ret.push_back(temp->at(k));
                        }
                    }
                }
            }

            /*for (size_t i = 0; i < ret.size(); i++) {
                std::cout << ret[i] << std::endl;
            }*/

            return ret;
        }
    
        void MyDataStore::dump(std::ostream& ofile) {
            ofile << "<products>" << std::endl;
            for (size_t i = 0; i < products_.size(); i++) {
                products_[i]->dump(ofile);
            }
            ofile << "</products>" << std::endl;
            ofile << "<users>" << std::endl;

            std::map<User*, std::vector<Product*>*>::iterator it;
            for (it = users_.begin(); it != users_.end(); ++it) {
                it->first->dump(ofile);
            }
            ofile << "</users>" << std::endl;
        }

        void MyDataStore::addToCart(std::vector<Product*> hits, std::string username, int num) {
            //find the user given username and their cart
            std::map<User*, std::vector<Product*>*>::iterator it = users_.find(usernames_.find(username)->second);
            it->second->push_back(hits[num]);
        }
        
        std::string MyDataStore::viewCart(std::string username) {
            //main implementation guarantees valid username
            
            std::string ret = "";
            std::map<User*, std::vector<Product*>*>::iterator it = users_.find(usernames_.find(username)->second);
            for (size_t i = 0; i < it->second->size(); i++) {
                ret += "Item " + std::to_string(i + 1) + ":\n";
                ret += it->second->at(i)->displayString();
            }
            return ret;
        }

        void MyDataStore::buyCart(std::string username) {
            std::map<User*, std::vector<Product*>*>::iterator it = users_.find(usernames_.find(username)->second);
            User* curUser = it->first;
            //offset accounts for products that can't be purchased
            size_t offset = 0;
            while (it->second->size() != offset) {
                Product* p = it->second->at(offset);
                if (curUser->getBalance() >= p->getPrice() && p->getQty() != 0) {
                    p->subtractQty(1);
                    curUser->deductAmount(p->getPrice());
                    it->second->erase(it->second->begin() + offset);
                }
                else offset++;
            }
        }

        void MyDataStore::quit(std::string filename) {
            std::ofstream ofile;
            ofile.open("database_copy.txt"); //does this overwrite or add?
            dump(ofile);
            ofile.close();
        }

        bool MyDataStore::checkUser(std::string username) {
            return usernames_.find(username) != usernames_.end();
        }