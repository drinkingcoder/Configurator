#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <streambuf>
#include <sstream>
#include <assert.h>
#include <vector>
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

#define CHECK_CONDITION(cond, msg) assert(cond && msg)

class JsonParser {
public:
    JsonParser():allocator(doc.GetAllocator()) {
        doc.SetObject();
    }
    virtual ~JsonParser() {
    }

    bool ParseFile(const std::string &fname) {
        std::ifstream input_file(fname);
        if(!input_file) {
            std::cout << "Failed!" << std::endl;
        }
        std::cout << "file name: " << fname << std::endl;

        std::string content((std::istreambuf_iterator<char>(input_file)), std::istreambuf_iterator<char>());
        return ParseString(content);
    }
    bool ParseString(const std::string &content) {
        std::cout << "content :" << std::endl << content << std::endl;
        doc.Parse(content.c_str());
        std::cout << "Parsed." << std::endl;
        return true;
    }
    void PrintJson() {
        std::stringstream ss;
        ss.str("");
        rapidjson::StringBuffer str_buffer;
        rapidjson::Writer<rapidjson::StringBuffer> writer(str_buffer);
        doc.Accept(writer);
        std::cout << "---------------------Json Content---------------------" << std::endl;
        std::cout << str_buffer.GetString() << std::endl;
        std::cout << "------------------------------------------------------" << std::endl;
    }

    float GetFloat(const char *variable) {
        CHECK_CONDITION(doc[variable].IsFloat(), variable);
        return doc[variable].GetFloat();
    }
    int GetInt(const char *variable) {
        CHECK_CONDITION(doc[variable].IsInt(), variable);
        return doc[variable].GetInt();
    }
    const char * GetString(const char *variable) {
        CHECK_CONDITION(doc[variable].IsString(), variable);
        return doc[variable].GetString();
    }

    std::vector<float> GetFloatVec(const char * variable) {
        CHECK_CONDITION(doc[variable].IsArray(), variable);
        std::vector<float> res;
        const rapidjson::Value &v = doc[variable];
        for (auto i = 0; i < v.Size(); i++) {
            res[i] = v[i].GetFloat();
        }
        return res;
    }

    std::vector<int> GetIntVec(const char *variable) {
        CHECK_CONDITION(doc[variable].IsArray(), variable);
        std::vector<int> res;
        const rapidjson::Value &v = doc[variable];
        res.resize(v.Size());
        for (auto i = 0; i < v.Size(); i++) {
            res[i] = v[i].GetInt();
        }
        return res;
    }
protected:
private:
    rapidjson::Document doc;
    rapidjson::Document::AllocatorType &allocator;
};
