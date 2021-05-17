#ifndef __PARSER_H__
#define __PARSER_H__
#include <string>
#include <vector>

class Parser {
    private:
        std::string allowedDomain;
    public:
        Parser();
        Parser(Parser&& other);
        Parser(std::string& allowedDomain);
        Parser(const Parser& other) = delete;
        int parseUrl(std::string url);
        void filterHtmlLine(std::string line, std::vector<std::string>& url_s);
        ~Parser();
};
#endif
