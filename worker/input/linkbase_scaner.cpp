/***************************************************************************
 *
 * Copyright (c) 2015 Baidu.com, Inc. All Rights Reserved
 *
 **************************************************************************/



/**
 * @file src/storage/linkbase_scaner.cpp
 * @author haolifei(com@baidu.com)
 * @date 2015/11/03 16:45:31
 * @brief
 *
 **/
#include "linkbase_scaner.h"

namespace saverng {
namespace storage {

LinkbaseScaner::LinkbaseScaner(comm::ptr::shared_ptr<saverng::storage::KvScaner::Option> op) {
    assert(NULL != op.get());
    assert("RAW" == op->cf());
    _scaner.reset(new KvScaner(op));
}

LinkbaseScaner::~LinkbaseScaner() {
}

void LinkbaseScaner::reset(const std::string& begin, const std::string& end) {
	_scaner->reset(begin, end);
}

void LinkbaseScaner::set_resetter(comm::ptr::shared_ptr<saverng::storage::Resetter> resetter) {
    _resetter = resetter;
}

bool LinkbaseScaner::has_next() {
    return _scaner->has_next();
}

bool LinkbaseScaner::next(std::string& key, SharedLink& link) {
    int64_t ts;
    return next(key, link, ts);
}

bool LinkbaseScaner::next(std::string& key, SharedLink& link, int64_t& ts_us) {
    std::string value;
    _scaner->next(key, value, ts_us);

    link.reset(new saverng::type::Link());

    int ret = link->parse(value);
    if (0 == ret) {
        if (NULL != _resetter.get()) {
            _resetter->reset(link.get(), (int64_t)ts_us / 1000000);
        }
        return true;
    }

    return false;
}

}
}

