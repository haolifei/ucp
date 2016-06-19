// Copyright (c) 2016, Baidu.com, Inc. All Rights Reserved
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
#include "task_runner.h"
#include "boost/smart_ptr/shared_ptr.hpp"
#include "glog/logging.h"

namespace baidu {
    namespace ucp {
        namespace task {
            TaskRunner::TaskRunner(boost::shared_ptr<Task> task) :
                task_(task),
                running_(false),
                status_(baidu::ucp::proto::kTaskPending) {
                
            }
            
            TaskRunner::~TaskRunner() {
                
            }
            
            baidu::ucp::system::ErrorCode TaskRunner::Setup() {
                input_ = baidu::ucp::input::Input::CreateInput(task_);
                if (NULL == input_) {
                    return ERRORCODE(-1, "create input failed");
                }
                
                processor_.reset(new baidu::ucp::processor::Processor(task_));
                baidu::ucp::system::ErrorCode ec = processor_->Setup();
                if (0 != ec.Code()) {
                    return ERRORCODE(-1, "set up processor failed: ", ec.Message().c_str());
                }
                
                output_ = baidu::ucp::output::Output::CreateOutput(task_);
                if (output_.get() == NULL) {
                    return ERRORCODE(-1, "create output failed");
                }
                
                ec = output_->Setup();
                if (0 != ec.Code()) {
                    return ERRORCODE(-1, "setup output failed:", ec.Message().c_str());
                }
                
                ec = input_->Setup();
                if (0 != ec.Code()) {
                    return ERRORCODE(-1, "setup input failed");
                }
                return ERRORCODE_OK;
            }



            boost::shared_ptr<baidu::ucp::task::Task> TaskRunner::GetTask() {
                return task_;
            }

            baidu::ucp::system::ErrorCode TaskRunner::ExecuteTask() {
                if (baidu::ucp::proto::kTaskRunning == status_) {
                    return ERRORCODE(-1, "task is runnunig now");
                }
                
                while (input_->HasNext()) {
                    int64_t ts = 0;
                    std::string key;
                    std::string value;
                    input_->Next(ts, key, value);
                    processor_->Process(ts, key, value);
                }
                
                return ERRORCODE_OK;
            }
            
            void TaskRunner::OutputRoutine() {
                while (running_) {
                    std::string key;
                    std::string value;
                    processor_->Output(key, value);
                    //if (!processor_->Valid()) {
                    //    return;
                    //}
                }
            }

            const std::string TaskRunner::CurrentRecord() {
                return processor_->CurrentRecord();
            }
            
            const std::string TaskRunner::TaskId() {
                return task_id_;
            }

            const std::string TaskRunner::JobId() {
                return job_id_;
            }


            baidu::ucp::proto::TaskStatus TaskRunner::Status() {
                return status_;
            }

            int64_t TaskRunner::InputRecord() {
                return processor_->InputRecord();
            }

            int64_t TaskRunner::OutputRecord() {
                return processor_->OutputRecord();
            }
            
            void TaskRunner::Quit(bool wait) {
                
            }
        }
    }
}
