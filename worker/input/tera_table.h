#pragma once

#include "util/error_code.h"
#include "tera.h"
#include <string>

namespace tera {
class Client;
class Table;
}

namespace baidu {
namespace ucp {
namespace input {

class TeraTable {
public:
    explicit TeraTable(const std::string& table_name);
    ~TeraTable();

    bool IsOpen();
    baidu::ucp::system::ErrorCode GetLastError();
    static void set_up(const std::string& tera_flag);
    static void tear_down();
    static const std::string& tera_flag();

    tera::Table* table();

private:
    TeraTable();
    TeraTable(const TeraTable&);

    int open();
    int close();

    static tera::Client* _s_tc;
    static std::string _s_tera_flag;
    std::string _table_name;
    tera::Table* _table;
    bool _opened;
    baidu::ucp::system::ErrorCode ec_;

};

}
}
}
