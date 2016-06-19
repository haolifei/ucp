// Copyright (c) 2016, Baidu.com, Inc. All Rights Reserved
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#pragma once
#include "util/error_code.h"
#include "task/task.h"
#include "boost/shared_ptr.hpp"
#include "boost/thread/mutex.hpp"
#include <sys/types.h>
#include <unistd.h>

namespace baidu {
    namespace ucp {
        namespace processor {
            class Processor {
            public:
                Processor(boost::shared_ptr<baidu::ucp::task::Task> task);
                virtual ~Processor();
                
                baidu::ucp::system::ErrorCode Setup();
                baidu::ucp::system::ErrorCode Process(int64_t ts, const std::string& key, const std::string& value);
                baidu::ucp::system::ErrorCode Output(const std::string& key, const std::string& value);
                bool Valid();
                const std::string CurrentRecord();
                int64_t InputRecord();
                int64_t OutputRecord();
                void Quit(bool wait);
                
            private:
                boost::shared_ptr<baidu::ucp::task::Task> task_;
                int fd_[2];
                pid_t pid_;
                boost::mutex mutex_;
                int64_t input_record_;
                int64_t output_record_;
                std::string record_;
            };
        }
    }
}
