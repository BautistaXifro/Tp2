#ifndef __PARSER_H__
#define __PARSER_H__
#include <string>

class Parser {
    private:
        std::string allowedDomain;
    public:
        Parser();
        Parser(std::string& allowedDomain);
        int parseUrl(std::string url);
        void filter_html_line(std::string& line);
        ~Parser();
};
#endif
