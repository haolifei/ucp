// Copyright (c) 2016, Baidu.com, Inc. All Rights Reserved
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "master_proxy.h"
#include "glog/logging.h"

namespace baidu {
    namespace ucp {
        namespace rpc {

            MasterProxy::MasterProxy(const std::string& nexus) :
                nexus_(nexus) {
                }

            MasterProxy::~MasterProxy() {
            }

            baidu::ucp::system::ErrorCode MasterProxy::Setup() {
                //if (!master_watcher_->Init(boost::bind(&MasterProxy::HandleMasterChange, this, _1))) {
                //    VLOG(10) << "init master watch failed";
                //    return ERRORCODE_OK(-1, "init master watch failed");
                //}
                return ERRORCODE_OK;
            }

            baidu::ucp::system::ErrorCode MasterProxy::FetchTask(const baidu::ucp::proto::FetchTaskRequest& request,
                        baidu::ucp::proto::FetchTaskResponse& response
                        ) {
                boost::mutex::scoped_lock lock(rpc_mutex_);
                if (!rpc_client_->SendRequest(master_stub_,
                                &baidu::ucp::proto::UcpMaster_Stub::FetchTask,
                                &request,
                                &response,
                                5,
                                1)) {
                    return ERRORCODE(-1, "");
                }
                return ERRORCODE_OK;
            }

            void MasterProxy::HandleMasterChange(const std::string& new_master_endpoint) {
                if (new_master_endpoint.empty()) {
                    LOG(WARNING) << "endpoint of master is deleted from nexus";
                }
                if (new_master_endpoint != master_endpoint_) {
                    boost::mutex::scoped_lock lock(rpc_mutex_);
                    LOG(INFO) << "master changes to " << new_master_endpoint.c_str();
                    master_endpoint_ = new_master_endpoint;

                    if (master_stub_) {
                        delete master_stub_;
                        master_stub_ = NULL;
                    }

                    if (!rpc_client_->GetStub(master_endpoint_, &master_stub_)) {
                        LOG(WARNING) << "connect master failed: " << master_endpoint_.c_str();
                        return;
                    }
                }
            }
        }

    }
}
