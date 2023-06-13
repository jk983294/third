#include <cereal/archives/binary.hpp>
#include <cereal/types/deque.hpp>
#include <cereal/types/list.hpp>
#include <cereal/types/map.hpp>
#include <cereal/types/memory.hpp>
#include <cereal/types/vector.hpp>
#include <cereal/types/polymorphic.hpp>
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
    int var1{0};
    int var3{0};

    virtual void sayType() {
        printf("MyBase::sayType\n");
    }

    template <class Archive>
    void serialize(Archive& ar) {
        ar& var1;
    }
};

struct MyDerive : public MyBase {
    int var2{0};
    int var4{0};

    virtual void sayType() {
        printf("MyDerive::sayType\n");
    }

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

CEREAL_REGISTER_TYPE(MyDerive)
CEREAL_REGISTER_POLYMORPHIC_RELATION(MyBase, MyDerive)

void polymorphism_demo() {
    std::shared_ptr<MyBase> a(new MyDerive);
    a->var1 = 1;
    a->var3 = 3;
    ((MyDerive*)a.get())->var2 = 2;
    ((MyDerive*)a.get())->var4 = 4;

    string file_ = "/tmp/f.bin";
    {  // save data to archive
        std::ofstream ofs(file_);
        cereal::BinaryOutputArchive oa(ofs);
        oa << a;
    }

    std::shared_ptr<MyBase> b = make_shared<MyBase>();
    b->var3 = 42;
    {
        std::ifstream ifs(file_);
        cereal::BinaryInputArchive ia(ifs);
        ia >> b;
    }
    MyDerive* b_cast = (MyDerive*)b.get();
    printf("from %s %d,%d,%d,%d\n", file_.c_str(), b->var1, b->var3, b_cast->var2, b_cast->var4);
    b->sayType();
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
    polymorphism_demo();
    std_demo();
    return 0;
}
