// Copyright (c) 2016, Baidu.com, Inc. All Rights Reserved
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#pragma once
#include "task/task.h"
#include "boost/shared_ptr.hpp"
#include "util/error_code.h"
#include <stdint.h>

namespace baidu {
    namespace ucp {
        namespace input {
            class InputRange {
            public:
                std::string begin_key;
                std::string end_key;
            };
            
            class Input {
            public:
                Input() {}
                virtual ~Input() {}

                virtual baidu::ucp::system::ErrorCode Setup() = 0;
                virtual bool HasNext() = 0;
                virtual baidu::ucp::system::ErrorCode Next(int64_t ts, const std::string& key, const std::string& value) =0;
                static boost::shared_ptr<Input> CreateInput(boost::shared_ptr<baidu::ucp::task::Task> task);
            };
        }
    }
}
