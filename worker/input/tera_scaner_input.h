// Copyright (c) 2016, Baidu.com, Inc. All Rights Reserved
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#pragma once
#include "input.h"
#include "tera_table.h"

namespace baidu {
    namespace ucp {
        namespace input {
            
            class TeraScanerInput : public Input {
            public:
                TeraScanerInput(boost::shared_ptr<baidu::ucp::task::Task> task) :
                    task_(task) {}
                    
                ~TeraScanerInput() {}
                
                bool HasNext();
                baidu::ucp::system::ErrorCode Next(int64_t ts, const std::string& key, const std::string& value);
                baidu::ucp::system::ErrorCode Setup();
                
            private:
                boost::shared_ptr<baidu::ucp::task::Task> task_;
                boost::shared_ptr<baidu::ucp::input::TeraTable> tera_table_;
                
                
            };
        }
    }
}
