#include <string>

class TestClass{
    int a;
public:
    //const static std::string HOGE;
    //const static int HOGE;
    int hoge;
    TestClass(int hoge);
    //void init();
    int get_hoge(void);
    std::string get_string(void);
};