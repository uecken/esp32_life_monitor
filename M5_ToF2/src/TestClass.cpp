#include "TestClass.h"
#include "string"

//const int TestClass::HOGE=1234;

TestClass::TestClass(int hoge =1234){
    TestClass::hoge = 123;
    //Serial.print("TestConstructor");
}
#ifdef false
void TestClass::init(int){
    TestClass::hoge = "hoge_init";
    //Serial.print("TestClass");
}
#endif

int TestClass::get_hoge(void){
    return TestClass::hoge;
}

std::string TestClass::get_string(void){
    return "aaaaa";
}

#ifdef false
std::string TestClass::gethoge(){
    return hoge;
}
#endif