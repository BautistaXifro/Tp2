#ifndef __PARSER_H__
#define __PARSER_H__
#include <string>
#include <vector>

class Parser {
    private:
        std::string allowedDomain;
    public:
        explicit Parser(const std::string& allowedDomain);
        Parser(Parser&& other);
        Parser(Parser& other) = delete;
        int parseUrl(std::string url);
        void filterHtmlLine(std::string line, std::vector<std::string>& url_s);
        ~Parser();
};
#endif
