// Copyright (c) 2016, Baidu.com, Inc. All Rights Reserved
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#pragma once
#include "util/error_code.h"
#include "proto/master.pb.h"
#include "boost/thread/mutex.hpp"
#include "task/task.h"
#include "input/input.h"
#include "output/output.h"
#include "processor/processor.h"

namespace baidu {
    namespace ucp {
        namespace task {
            
            //class Runner;
            class TaskRunner {
            public:
                TaskRunner(boost::shared_ptr<Task> task);
                ~TaskRunner();
                baidu::ucp::system::ErrorCode Setup();
                baidu::ucp::system::ErrorCode ExecuteTask();
                
                const std::string TaskId();
                const std::string JobId();
                baidu::ucp::proto::TaskStatus Status();
                const std::string CurrentRecord();
                int64_t InputRecord();
                int64_t OutputRecord();
                
                void Quit(bool wait);
                boost::shared_ptr<baidu::ucp::task::Task> GetTask();
            private:
                void OutputRoutine();
                boost::shared_ptr<Task> task_;
                bool running_;
                boost::mutex mutex_;
                baidu::ucp::proto::TaskStatus status_;
                std::string task_id_;
                std::string job_id_;
                std::string begin_key_;
                std::string end_key_;
                
                boost::shared_ptr<baidu::ucp::input::Input> input_;
                boost::shared_ptr<baidu::ucp::processor::Processor> processor_;
                boost::shared_ptr<baidu::ucp::output::Output> output_;
                
            };
        }
    }
}
