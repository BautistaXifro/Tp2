#include "parser.h"
#include <algorithm>

static int findDomain(std::string& url_s, std::string& allowedDomain);

Parser::Parser(){}

Parser::Parser(std::string& allowedDomain){
    this->allowedDomain = allowedDomain;
}

int Parser::parseUrl(std::string url){
    std::string aux = url;
    std::string http = "http://";
    if (aux.compare(0, http.length(), http) == 0 &&
        findDomain(aux.erase(0,http.length()), this->allowedDomain) == 0)
        return 0;

    return -1;
}

static int findDomain(std::string& url_s, std::string& allowedDomain) {
    std::string prot_end("/");
    std::string::iterator prot_i = std::search(url_s.begin(), url_s.end(), prot_end.begin(), prot_end.end());

    int start_position = prot_i-url_s.begin();

    //borro todo lo que esta despues de la '/', si la '/' no existe no borra nada
    url_s.erase(start_position, url_s.length());

    prot_i = std::search(url_s.begin(), url_s.end(), allowedDomain.begin(), allowedDomain.end());

    start_position = prot_i-url_s.begin();

    if (prot_i!=url_s.end()){
        // sumo la cantidad de chars que hay detras del domain (start_position).
        url_s.erase(0, allowedDomain.length() + start_position);
        if (url_s.length() == 0) return 0;
        else return -1; //ignorar URL no posee el allowedDomain
    }
    return -1; //ignorar URL no posee el allowedDomain
}

void Parser::filter_html_line(std::string& line){
    std::string prot_end("http");
    std::string::iterator prot_i = std::search(line.begin(), line.end(), prot_end.begin(), prot_end.end());
    int start_of_link = prot_i-line.begin();

    //borro todo lo que esta antes del http
    line.erase(0, start_of_link);

    std::string prot_end_two(" ");
    prot_i = std::search(line.begin(), line.end(), prot_end_two.begin(), prot_end_two.end());
    int end_of_link = prot_i-line.begin();

    //borro todo lo que esta despues del link
    line.erase(end_of_link, line.length());
}

Parser::~Parser(){
    this->allowedDomain.clear();
    delete this;
}
