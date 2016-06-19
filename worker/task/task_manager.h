
#include "util/error_code.h"

// Copyright (c) 2016, Baidu.com, Inc. All Rights Reserved
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#pragma once


namespace baidu {
    namespace ucp {
        namespace task {
            
            //class Runner;
            class TaskRunner {
            public:
                TaskRunner(const baidu::ucp::proto::JobDescription& job);
                ~TaskRunner();
                
                baidu::ucp::system::ErrorCode ConstructError();
                
                baidu::ucp::system::ErrorCode ExecuteTask(const std::string& id,
                    const std::string& begin_key,
                    const std::string& end_key
                );
                
                const std::string TaskId();
                const std::string JobId();
                baidu::ucp::proto::TaskStatus Status();
                int64_t InputRecord();
                int64_t OutputRecord();
                
            private:
                std::string task_id_;
                std::string begin_key_;
                std::string end_key_;
            };
        }
    }
}