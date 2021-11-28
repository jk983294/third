#include <rapidjson/document.h>
#include <rapidjson/istreamwrapper.h>
#include <rapidjson/ostreamwrapper.h>
#include <rapidjson/writer.h>
#include <fstream>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;
using namespace rapidjson;

void read_from_str();
void write_file();
void read_file();

int main() {
    read_from_str();
    write_file();
    read_file();
    return 0;
}

void read_file() {
    string path = "/tmp/demo.json";
    std::unordered_map<string, double> f2score;
    std::vector<string> formulas;
    std::ifstream ifs(path);
    rapidjson::IStreamWrapper isw(ifs);

    rapidjson::Document d;
    d.ParseStream(isw);

    if (d.HasMember("formula2fitness")) {
        const rapidjson::Value& formula2fitness = d["formula2fitness"];
        for (auto& m : formula2fitness.GetObject()) {
            f2score[string(m.name.GetString())] = m.value.GetDouble();
        }
    }

    if (d.HasMember("curr_exprs")) {
        const rapidjson::Value& curr_exprs = d["curr_exprs"];
        for (rapidjson::Value::ConstValueIterator itr = curr_exprs.Begin(); itr != curr_exprs.End(); ++itr) {
            formulas.emplace_back(itr->GetString());
        }
    }

    for (auto& item : f2score) {
        printf("f=%s, score=%f\n", item.first.c_str(), item.second);
    }
    for (auto& item : formulas) {
        printf("f=%s\n", item.c_str());
    }
}

void write_file() {
    string path = "/tmp/demo.json";
    std::vector<string> formulas = {"a", "b"};
    std::unordered_map<string, double> f2score = {{"a", 1.0}, {"b", 2.0}};
    rapidjson::Document d;
    d.SetObject();  // root 设置成 object类型,而不是 array类型
    rapidjson::Document::AllocatorType& allocator = d.GetAllocator();

    rapidjson::Value curr_exprs(rapidjson::kArrayType);
    for (const auto& f : formulas) {
        rapidjson::Value objValue;
        objValue.SetObject();
        objValue.SetString(f.c_str(), f.size(), allocator);
        curr_exprs.PushBack(objValue, allocator);
    }
    d.AddMember("curr_exprs", curr_exprs, allocator);

    rapidjson::Value formula2fitness(rapidjson::kObjectType);
    for (const auto& item : f2score) {
        rapidjson::Value keyObj;
        keyObj.SetString(item.first.c_str(), item.first.size(), allocator);
        rapidjson::Value valueObj;
        valueObj.SetDouble(item.second);
        formula2fitness.AddMember(keyObj, valueObj, allocator);
    }
    d.AddMember("formula2fitness", formula2fitness, allocator);

    ofstream ofs(path);
    rapidjson::OStreamWrapper osw(ofs);
    rapidjson::Writer<rapidjson::OStreamWrapper> writer(osw);
    d.Accept(writer);
    ofs.close();
    printf("dump formula to %s\n", path.c_str());
}

void read_from_str() {
    // Parse a JSON string into DOM.
    const char* json = "{\"project\":\"rapidjson\",\"stars\":10, \"null_key\":null, \"a\": [1, 2]}";
    Document d;
    d.Parse(json);

    cout << d.HasMember("project") << endl;
    cout << d["project"].IsString() << endl;
    cout << d["project"].GetString() << endl;
    cout << d["stars"].GetInt() << endl;
    cout << d["null_key"].IsNull() << endl;
    const Value& a = d["a"];
    assert(a.IsArray());
    cout << a.Empty() << endl;
    for (SizeType i = 0; i < a.Size(); i++) {
        cout << "a[" << i << "] = " << a[i].GetInt() << endl;
    }

    Value::ConstMemberIterator itr = d.FindMember("project");
    if (itr != d.MemberEnd()) {
        cout << "find project : " << itr->value.GetString() << endl;
    } else {
        cout << "cannot find member hello" << endl;
    }

    // loop all members
    static const char* kTypeNames[] = {"Null", "False", "True", "Object", "Array", "String", "Number"};
    for (auto& m : d.GetObject()) {
        cout << "member name is " << m.name.GetString() << "type is " << kTypeNames[m.value.GetType()] << endl;
    }

    // Modify it by DOM
    Value& s = d["stars"];
    s.SetInt(s.GetInt() + 1);

    Value arr(kArrayType);
    Document::AllocatorType& allocator = d.GetAllocator();
    arr.PushBack(Value().SetInt(42), allocator);  // fluent API
    arr.PushBack(Value(42).Move(), allocator);    // same as above line
    d.AddMember("my_arr", arr, allocator);

    Value author;
    const char* data = "data";
    author.SetString(data, strlen(data), d.GetAllocator());
    d.AddMember("author", author, allocator);

    Value x(kObjectType);
    x.AddMember("name", "Milo", d.GetAllocator());
    x.AddMember("married", true, d.GetAllocator());
    d.AddMember("x", x, allocator);

    // Stringify the DOM
    StringBuffer buffer;
    Writer<StringBuffer> writer(buffer);
    d.Accept(writer);
    std::cout << buffer.GetString() << std::endl;
}
