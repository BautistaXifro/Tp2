#include "parser.h"
#include <algorithm>
#include <utility>

static int findDomain(std::string& url_s, std::string allowedDomain);

Parser::Parser(const std::string& allowedDomain){
    this->allowedDomain = allowedDomain;
}

Parser::Parser(Parser&& other){
    this->allowedDomain = std::move(other.allowedDomain);

    other.allowedDomain.clear();
}

int Parser::parseUrl(std::string url){
    std::string aux = url;
    std::string http = "http://";
    if (aux.compare(0, http.length(), http) == 0 &&
        findDomain(aux.erase(0,http.length()), this->allowedDomain) == 0)
        return 0;

    return -1;
}

static int findDomain(std::string& url_s, std::string allowedDomain) {
    std::string prot_end("/");
    std::string::iterator prot_i = std::search(url_s.begin(),
             url_s.end(), prot_end.begin(), prot_end.end());

    int start_position = prot_i - url_s.begin();

    url_s.erase(start_position, url_s.length());

    prot_i = std::search(url_s.begin(), url_s.end(),
         allowedDomain.begin(), allowedDomain.end());

    start_position = prot_i - url_s.begin();

    if (prot_i != url_s.end()){
        url_s.erase(0, allowedDomain.length() + start_position);
        if (url_s.length() == 0){
            return 0;
        }else{
            return -1;
        } 
    }
    return -1;
}

void Parser::filterHtmlLine(std::string line, std::vector<std::string>& url_s){
    std::string aux_string;
    while (line.length() != 0){
        std::string prot_end("http");
        std::string::iterator prot_i = std::search(line.begin(),
                line.end(), prot_end.begin(), prot_end.end());
        int start_of_link = prot_i - line.begin();

        //borro todo lo que esta antes del http
        line.erase(0, start_of_link);

        std::string prot_end_two(" ");
        prot_i = std::search(line.begin(), line.end(),
            prot_end_two.begin(), prot_end_two.end());
        int end_of_link = prot_i - line.begin();

        //copy html encounter
        char* aux = new char[end_of_link + 1];
        std::size_t length = line.copy(aux, end_of_link, 0);
        aux[length] = '\0';
        aux_string = aux;
        if (aux_string.size() != 0){
            auto it = url_s.begin();
            url_s.insert(it, aux_string);
        }
        //borro de la linea el link copiado
        line.erase(0, end_of_link);
        delete[] aux;
    }
}

Parser::~Parser(){}
