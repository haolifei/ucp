
#include "worker/rpc/rpc_client.h"
#include "proto/master.pb.h"

// Copyright (c) 2016, Baidu.com, Inc. All Rights Reserved
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#pragma once
#include "rpc/master_proxy.h"
#include "util/error_code.h"
#include "task/task_runner.h"
#include "task_runner.h"
#include "thread_pool.h"

namespace baidu {
    namespace ucp {
        namespace task {
            
            class TaskFetcher {
            public:
                TaskFetcher(const std::string& nexus);
                ~TaskFetcher();
                
                baidu::ucp::system::ErrorCode Setup();
                void Run();
                
            private:
                void ExecuteTaskRutine(boost::shared_ptr<baidu::ucp::task::TaskRunner> runner);
                bool running_;
                boost::scoped_ptr<baidu::ucp::rpc::MasterProxy> master_proxy_;
                boost::shared_ptr<baidu::ucp::task::TaskRunner> task_runner_;
                baidu::common::ThreadPool task_exe_pool_;
            };
        }
    }
}
