#include <iostream>
#include <ranges>
#include <string>
#include <sstream>
#include <fstream>
#include <map>
#include <vector>

#define ORIGIN_VERSION

//#define LOOP_VERSION

//#define CPP20

using namespace std;

int main()
{

#ifdef LOOP_VERSION
    ofstream fout("88w_loop.cpp");
#endif

#ifdef ORIGIN_VERSION
    ofstream fout("88w.cpp");
#endif // ORIGIN_VERSION
    fout<<"#include <iostream>"<<endl;
    fout<<"#include <string>"<<endl;
#ifdef LOOP_VERSION
    fout<<"#include <ctime>"<<endl;
#ifdef CPP20
    fout<<"#include <ranges>"<<endl;
#endif // CPP20
#endif // LOOP_VERSON

    fout<<"#include \"xorshift128p.h\""<<endl;
    fout<<"using namespace std;"<<endl;

    fout<<"int main(int argc,char* argv[]){"<<endl;
#ifdef ORIGIN_VERSION
    fout<<"cout<<\"请给出一个不多于5位的正整数:\";"<<endl;
    fout<<"int x;"<<endl<<"cin>>x;"<<endl;
#endif // ORIGIN_VERSION

#ifdef LOOP_VERSION

    fout<<"long maxtime=10000;"<<endl;
    fout<<"if (argc==2)"<<endl;
    fout<<"maxtime=stoi(string(argv[1]));"<<endl;

    fout<<"cout<<maxtime<<endl;"<<endl;
    fout<<"long used=0;"<<endl;
#ifndef CPP20
    fout<<"sxorshift128p(time(0));"<<endl;
    fout<<"for (long loop_time=0;loop_time<maxtime;loop_time++)"<<endl;

#endif // CPP20

    fout<<"{"<<endl;
    fout<<"long x=(xorshift128p()%100000)+1;"<<endl;
#endif // LOOP_VERSION

    fout<<"switch(x){"<<endl;
    vector<string> dilist(5);

    dilist[0]="个位数是：";
    dilist[1]="十位数是：";
    dilist[2]="白位数是：";
    dilist[3]="千位数是：";
    dilist[4]="万位数是：";
    for (auto index:views::iota(1,100000))
    {
        if (index%100==0)
            cout<<"working on:"<<index<<endl;
        string now=to_string(index);
        stringstream ssbuffer;
        ssbuffer<<"case "<<now<<":\n";
        #ifdef ORIGIN_VERSION
        ssbuffer<<"cout << \"是"<<now.length()<<"位数\"<<endl;\n";
        int offset=0;
        for (auto di:now)
        {
            ssbuffer<<"cout<<\""<<dilist[offset++]<<di<<"\"<<endl;\n";
        }
        ssbuffer<<"cout<<\"倒过来是:"<<string(now.rbegin(),now.rend())<<"\"<<endl;\n";
        #endif // ORIGIN_VERSION

        #ifdef LOOP_VERSION
        ssbuffer<<"used+="<<now<<";\n";
        #endif // LOOP_VERSION

        ssbuffer<<"break;\n";
        fout<<ssbuffer.str();
    }
    fout<<"default:break;\n";
    fout<<"}"<<endl;

#ifdef LOOP_VERSION
    fout<<"}"<<endl;
#endif // LOOP_VERSION
    fout<<"cout<<used<<endl;"<<endl;
    fout<<"return 0;}"<<endl;

    fout.close();
    return 0;
}
