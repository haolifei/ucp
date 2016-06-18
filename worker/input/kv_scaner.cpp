#include "kv_scaner.h"
#include "tera_table.h"
#include "base/smart_ptr/shared_ptr.hpp"
#include "base/timer.h"

#include <glog/logging.h>

#include <assert.h>

#include <iostream>

namespace saverng {
namespace storage {

class KvScaner::Ref {
    public:
        Ref(const std::string& begin, const std::string& end) :
            _desc(begin),
            _begin_key(begin),
            _end_key(end) {
        }

        comm::ptr::shared_ptr<tera::ResultStream> _stream;

        void init(KvScaner* scaner) {
            _desc.SetEnd(_end_key);
            _desc.SetAsync(false);
            _desc.AddColumnFamily(scaner->_op->cf());
            _desc.SetBufferSize(scaner->_op->buffer_size());
            _desc.SetTimeRange(scaner->_op->end_time(), scaner->_op->begin_time());
            tera::ErrorCode err_code;
            assert(scaner->_op->tera_table()->table() != NULL);
            assert(&_desc != NULL);
            _stream.reset(scaner->_op->tera_table()->table()->Scan(_desc, &err_code));

            if (tera::ErrorCode::kOK != err_code.GetType()) {
                LOG(FATAL) << "create scan stream failure";
                abort();
                return;
            }
        }

    private:
        tera::ScanDescriptor _desc;
        std::string _begin_key;
        std::string _end_key;
};

/*****************************scaner********************************/
KvScaner::KvScaner(comm::ptr::shared_ptr<KvScaner::Option> op) :
    _op(op),
    _counter(0),
    _counter_start_time(0) {
}

KvScaner::~KvScaner() {
}


void KvScaner::reset(const std::string& begin, const std::string& end) {
    _ref.reset(new Ref(begin, end));
    _ref->init(this);
}

bool KvScaner::has_next() {
    return !_ref->_stream->Done();
}

void KvScaner::next(std::string& key, std::string& value) {
    int64_t ts;
    next(key, value, ts);
}

void KvScaner::next(std::string& key, std::string& value, int64_t& ts_us) {
    key = _ref->_stream->RowName();
    value = _ref->_stream->Value();
    ts_us = _ref->_stream->Timestamp();
    _ref->_stream->Next();
    speed_limit();
}

void KvScaner::speed_limit() {
    if (_op->speed() > 0) {
        ++_counter;
        if (0 == _counter_start_time) {
            _counter_start_time = comm::timer::get_micros();
        }

        if (_counter % 10000 == 0) {
            int64_t now = comm::timer::get_micros();
            int64_t real_time = now - _counter_start_time;
            int64_t expect_time = 10000L * 1000000L / _op->speed(); // ×¢ÒâÒç³ö
            int64_t delta = expect_time - real_time;

            if (delta > 0) {
                usleep(delta);
            }
            _counter_start_time = now;
        }
    }
}


}
}
