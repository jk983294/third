#include <cereal/archives/binary.hpp>
#include <cereal/types/deque.hpp>
#include <cereal/types/list.hpp>
#include <cereal/types/map.hpp>
#include <cereal/types/memory.hpp>
#include <cereal/types/vector.hpp>
#include <cstdio>
#include <deque>
#include <fstream>
#include <iostream>
#include <list>
#include <map>

using namespace std;

struct MyObj1 {
    int a;

    template <class Archive>
    void serialize(Archive& ar) {
        ar& a;
    }
};

struct MyObj2 {
    int a;
};

// non-intrusive way
template <class Archive>
void serialize(Archive& ar, MyObj2& g) {
    ar& g.a;
}

struct MyClass1 {
    int var1, var2;
    MyObj1 obj1;
    MyObj2 obj2;

    template <class Archive>
    void serialize(Archive& ar) {
        ar& var1& var2& obj1& obj2;
    }
};

struct MyBase {
    int var1;

    template <class Archive>
    void serialize(Archive& ar) {
        ar& var1;
    }
};

struct MyDerive : public MyBase {
    int var2;

    template <class Archive>
    void serialize(Archive& ar) {
        ar& cereal::base_class<MyBase>(this);
        ar& var2;
    }
};

void basic_demo() {
    MyObj1 a;
    a.a = 42;

    string file_ = "/tmp/a.bin";
    {  // save data to archive
        std::ofstream ofs(file_);
        cereal::BinaryOutputArchive oa(ofs);
        oa << a;
    }

    MyObj1 b;
    {
        std::ifstream ifs(file_);
        cereal::BinaryInputArchive ia(ifs);
        ia >> b;
    }
    printf("from %s %d\n", file_.c_str(), b.a);
}

void basic_demo1() {
    MyObj2 a;
    a.a = 42;

    string file_ = "/tmp/b.bin";
    {  // save data to archive
        std::ofstream ofs(file_);
        cereal::BinaryOutputArchive oa(ofs);
        oa << a;
    }

    MyObj2 b;
    {
        std::ifstream ifs(file_);
        cereal::BinaryInputArchive ia(ifs);
        ia >> b;
    }
    printf("from %s %d\n", file_.c_str(), b.a);
}

void basic_demo2() {
    MyClass1 a;
    a.var1 = 42;
    a.var2 = 43;
    a.obj1.a = 44;
    a.obj2.a = 45;

    string file_ = "/tmp/c.bin";
    {  // save data to archive
        std::ofstream ofs(file_);
        cereal::BinaryOutputArchive oa(ofs);
        oa << a;
    }

    MyClass1 b;
    {
        std::ifstream ifs(file_);
        cereal::BinaryInputArchive ia(ifs);
        ia >> b;
    }
    printf("from %s %d,%d,%d,%d\n", file_.c_str(), b.var1, b.var2, b.obj1.a, b.obj2.a);
}

void derive_demo() {
    MyDerive a;
    a.var1 = 1;
    a.var2 = 2;

    string file_ = "/tmp/d.bin";
    {  // save data to archive
        std::ofstream ofs(file_);
        cereal::BinaryOutputArchive oa(ofs);
        oa << a;
    }

    MyDerive b;
    {
        std::ifstream ifs(file_);
        cereal::BinaryInputArchive ia(ifs);
        ia >> b;
    }
    printf("from %s %d,%d\n", file_.c_str(), b.var1, b.var2);
}

struct MyStdObj {
    std::map<string, string> a;
    vector<int> b;
    deque<double> c;
    list<float> d;
    vector<vector<MyObj1>> e;

    template <class Archive>
    void serialize(Archive& ar) {
        ar& a& b& c& d& e;
    }
};

void std_demo() {
    MyStdObj x;
    x.a["1"] = "1";
    x.b.push_back(2);
    x.c.push_back(3.0);
    x.d.push_back(4.0f);
    x.e.resize(1);
    x.e.back().push_back({42});

    string file_ = "/tmp/e.bin";
    {  // save data to archive
        std::ofstream ofs(file_);
        cereal::BinaryOutputArchive oa(ofs);
        oa << x;
    }

    MyStdObj y;
    {
        std::ifstream ifs(file_);
        cereal::BinaryInputArchive ia(ifs);
        ia >> y;
    }
    cout << y.a["1"] << " " << y.b.front() << " " << y.c.front() << " " << y.d.front() << " " << y.e.front().front().a
         << endl;
}

int main() {
    basic_demo();
    basic_demo1();
    basic_demo2();
    derive_demo();
    std_demo();
    return 0;
}
