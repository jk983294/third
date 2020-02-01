#include <iostream>
#include "rapidjson/document.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/writer.h"

using namespace std;
using namespace rapidjson;

int main() {
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
    return 0;
}
