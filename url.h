#ifndef __URL_H__
#define __URL_H__
#include <string>

class Url{
    private:
        std::string url;
        std::string state;
    public:
        explicit Url(const std::string& url);
        Url(Url&& other); //move constructor
        Url& operator=(Url&& other);
        Url(const Url& other) = delete;
        void explored();
        void dead();
        std::string getState();
        std::string getUrl();
        ~Url();
};
#endif
