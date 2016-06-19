/*
 * File:   scaner.h
 * Author: haolifei
 *
 * Created on 2015年8月6日, 下午3:15
 */

#pragma once
#include "base/smart_ptr/shared_ptr.hpp"
#include <tera.h>

#include <stdint.h>
#include <string>

namespace saverng {
namespace storage {
class TeraTable;
class KvScaner {
public:
    class Option {
    public:
        Option():
            _buffer_size(10000),
            _begin_time(0),
            _end_time(31536000000000000L),
			_cf("cf"),
            _speed(500) {
        }
      
        Option* set_buffer_size(uint32_t size) {
            _buffer_size = size;
            return this;
        }

        Option* set_time_range(int64_t begin, int64_t end) {
            _begin_time = begin;
            _end_time = end;
            return this;
        }

        Option* set_cf(const std::string& cf) {
            _cf = cf;
            return this;
        }

        Option* set_table(comm::ptr::shared_ptr<TeraTable> table) {
            _tera_table = table;
            return this;
        }

        Option* set_speed(int speed) {
            _speed = speed;
            return this;
        }

        uint32_t buffer_size() const {
            return _buffer_size;
        }

        comm::ptr::shared_ptr<TeraTable> tera_table() {
            return _tera_table;
        }

        const std::string& cf() const {
            return _cf;
        }

        int speed() const {
            return _speed;
        }

        int64_t begin_time() const {
            return _begin_time;
        }

        int64_t end_time() const {
            return _end_time;
        }

    private:
        uint32_t _buffer_size;
        int64_t _begin_time;
        int64_t _end_time;
        comm::ptr::shared_ptr<TeraTable> _tera_table;
        std::string _cf;
        int _speed;
    };

public:
    KvScaner(comm::ptr::shared_ptr<Option> op);
    ~KvScaner();
	void reset(const std::string& begin, const std::string& end);
    bool has_next();
    void next(std::string& key, std::string& value);
    void next(std::string& key, std::string& value, int64_t& ts_us);
    int64_t speed();
    int64_t counter();
    int64_t start_time();

private:
    KvScaner();
    KvScaner(const KvScaner&);
    KvScaner& operator=(const KvScaner&);

    void speed_limit();
    comm::ptr::shared_ptr<Option> _op;

    class Ref;
    comm::ptr::shared_ptr<Ref> _ref;

    int64_t _counter;
    int64_t _counter_start_time;
    int64_t _start_time;
};

}
}
