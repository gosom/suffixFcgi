#include <iostream>
#include <string>
#include <vector>
#include <regex>
#include <chrono>
#include "cedartrie.h"
#include "fcgi_stdio.h"
#include <stdlib.h>
#include <jsoncpp/json/json.h>

using namespace std::chrono;
using cedartrie::CeDarTrie;

std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems) {
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}

std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, elems);
    return elems;
}

int main()
{
    char *query_string;
    int count = 0;
    CeDarTrie trie;
    auto t0 = high_resolution_clock::now();
    trie.load("/home/giorgos/projects/suffixSearch/small.txt");
    auto t1 = high_resolution_clock::now();
    while(FCGI_Accept() >= 0){
        query_string = getenv("QUERY_STRING");
        if(query_string != NULL) {
            std::string qs(query_string);
            auto params = split(qs, '=');
            std::string prefix = params[1];
            auto res = trie.lookup(prefix);
            Json::Value ret;
            Json::Value array;
            for(auto&r: res){
                Json::Value o;
                o["kw"] = r.key;
                o["id"] = r.value;
                array.append(o);
            }
            ret["results"] = array;
            Json::StyledWriter styledWriter;
            printf("Content-type: text/html\r\n"
                   "\r\n"
                   "%s\n",
                   styledWriter.write(ret).c_str());
            }
        }
    return 0;
}
