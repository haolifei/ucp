
// Copyright (c) 2016, Baidu.com, Inc. All Rights Reserved
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#pragma once
#include "util/error_code.h"
#include "rpc/rpc_client.h"
#include "proto/master.pb.h"
#include "util/watcher.h"
#include "boost/scoped_ptr.hpp"
#include "boost/thread/mutex.hpp"

namespace baidu {
    namespace ucp {
        namespace rpc {
            
            class MasterProxy {
            public:
                explicit MasterProxy(const std::string& nexus);
                ~MasterProxy();
                
                baidu::ucp::system::ErrorCode Setup();
                baidu::ucp::system::ErrorCode FetchTask(const baidu::ucp::proto::FetchTaskRequest& request,
                    baidu::ucp::proto::FetchTaskResponse& response);
                
            private:
                void HandleMasterChange(const std::string& new_master_endpoint);
                
                const std::string nexus_;
                boost::scoped_ptr<baidu::util::RpcClient> rpc_client_;
                baidu::ucp::proto::UcpMaster_Stub* master_stub_;
                boost::scoped_ptr<baidu::ucp::Watcher> master_watcher_;
                boost::mutex rpc_mutex_;
                std::string master_endpoint_;
            };
        }
      
    }
}
