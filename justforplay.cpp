#include <iostream>
#include <ranges>
#include <string>
#include <sstream>
#include <fstream>
#include <map>
#include <iomanip>
#include <vector>
#include <algorithm>

int main()
{


    std::ofstream fout("88w.cpp");

    std::stringstream ssbuffer;

    ssbuffer<<"#include <iostream>"<<std::endl;
    ssbuffer<<"#include <string>"<<std::endl;

    ssbuffer<<"using namespace std;"<<std::endl;

    ssbuffer<<"int main(int argc,char* argv[]){"<<std::endl;

    ssbuffer<<"cout<<"<<std::quoted("请给出一个不多于5位的正整数:")<<"<<endl;"<<std::endl;
    ssbuffer<<"int x;"<<std::endl<<"cin>>x;"<<std::endl;

    ssbuffer<<"switch(x){"<<std::endl;
    std::vector<std::string> dilist={"个位数是：","十位数是：","百位数是：","千位数是：","万位数是："};
    std::ranges::for_each(std::views::iota(1,100000)
                          |std::views::transform([](int32_t i){return std::to_string(i);})
                          |std::views::transform([&dilist](std::string input)
            {

                std::stringstream buffer;
                buffer<<"case "<<input<<":\n";
                buffer<<"cout<<"<<std::quoted("是"+std::to_string(input.length())+"位数")<<"<<endl;\n";
                int offset=0;
                std::ranges::for_each(input|std::views::reverse,[&](auto ch){buffer<<"cout<<"<<std::quoted(dilist[offset++]+std::string(1,ch))<<"<<endl;\n";} );
                buffer<<"cout<<"<<std::quoted("倒过来是:"+std::string(input.rbegin(),input.rend()))<<"<<endl;\n";
                buffer<<"break;\n";
                return buffer.str();
            }),[&](std::string buffer){ssbuffer<<buffer;});



    ssbuffer<<"default:break;\n";
    ssbuffer<<"}"<<std::endl;

    ssbuffer<<"return 0;}"<<std::endl;
    fout<<ssbuffer.str();
    fout.close();
    return 0;
}
