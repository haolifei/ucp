// Copyright (c) 2016, Baidu.com, Inc. All Rights Reserved
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "task_fetcher.h"

namespace baidu {
    namespace ucp {
        namespace agent {

            TaskFetcher::TaskFetcher(const std::string& nexus) :
                running_(false),
                master_proxy_(new baidu::ucp::rpc::MasterProxy(nexus)) {
            }

            TaskFetcher::~TaskFetcher() {

            }

            baidu::ucp::system::ErrorCode TaskFetcher::Setup() {
                return master_proxy_->Setup();
            }

            void TaskFetcher::Run() {
                running_ = true;
                while(running_) {
                    
                }
            }
        }
    }
}
