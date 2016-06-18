// Copyright (c) 2016, Baidu.com, Inc. All Rights Reserved
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#pragma once
#include "util/error_code.h"
#include <sys/types.h>
#include <unistd.h>

namespace baidu {
    namespace ucp {
        namespace processor {
            class Processor {
            public:
                Processor();
                virtual ~Processor();
                
                baidu::ucp::system::ErrorCode Setup(const std::string& cmd);
                baidu::ucp::system::ErrorCode Process(int64_t ts, const std::string& key, const std::string& value);
                baidu::ucp::system::ErrorCode Output(const std::string& key, const std::string& value);
                void Quit(bool wait);
                
            private:
                int fd_[2];
                pid_t pid_;
                
                
            };
        }
    }
}
