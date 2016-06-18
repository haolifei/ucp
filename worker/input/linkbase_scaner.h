/***************************************************************************
 *
 * Copyright (c) 2015 Baidu.com, Inc. All Rights Reserved
 *
 **************************************************************************/

#include "resetter.h"
#include "kv_scaner.h"




/**
 * @file linkbase_scaner.h
 * @author haolifei(com@baidu.com)
 * @date 2015/09/24 14:38:19
 * @brief
 *
 **/

#pragma once
#include "kv_scaner.h"
#include "type/type.h"
#include "base/smart_ptr/shared_ptr.hpp"
#include <string>

namespace saverng {
namespace storage {

class LinkbaseScaner {
public:
    explicit LinkbaseScaner(comm::ptr::shared_ptr<saverng::storage::KvScaner::Option> op);
    ~LinkbaseScaner();
	void reset(const std::string& begin, const std::string& end);
    void set_resetter(comm::ptr::shared_ptr<saverng::storage::Resetter> resetter);
    bool has_next();
    bool next(std::string& key, SharedLink& link);
    bool next(std::string& key, SharedLink& link, int64_t& ts_us);

private:
    LinkbaseScaner(const LinkbaseScaner&);
    void operator =(const LinkbaseScaner&);
    comm::ptr::scoped_ptr<saverng::storage::KvScaner> _scaner;
    comm::ptr::shared_ptr<saverng::storage::Resetter> _resetter;

};

}
}


/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
