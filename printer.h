#ifndef __PRINTER_H__
#define __PRINTER_H__
#include "url.h"
#include <list>
#include <mutex>

class Printer {
    private:
        std::list<Url> container;
        std::mutex printer_mutex;
    public:
        Printer();
        Printer(Printer&& other);
        Printer(const Printer& other) = delete;
        void almacenate(Url& url);
        void print();
        ~Printer();
};
#endif
