// Copyright (c) 2016, Baidu.com, Inc. All Rights Reserved
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "task_fetcher.h"
#include "proto/master.pb.h"
#include "task_runner.h"
#include "task.h"

namespace baidu {
    namespace ucp {
        namespace task {

            TaskFetcher::TaskFetcher(const std::string& nexus) :
                running_(false),
                master_proxy_(new baidu::ucp::rpc::MasterProxy(nexus)),
                task_exe_pool_(1) {
            }

            TaskFetcher::~TaskFetcher() {

            }

            baidu::ucp::system::ErrorCode TaskFetcher::Setup() {
                return master_proxy_->Setup();
            }
            
            void TaskFetcher::ExecuteTaskRutine(boost::shared_ptr<baidu::ucp::task::TaskRunner> runner) {
                assert(NULL != runner.get());
                boost::shared_ptr<baidu::ucp::task::TaskRunner> r = runner;
                r->ExecuteTask();
            }

            void TaskFetcher::Run() {
                running_ = true;
                while(running_) {
                    baidu::ucp::proto::FetchTaskRequest req;
                    req.set_job_id("");
                    if (task_runner_.get() != NULL) {
                        req.set_task_id(task_runner_->TaskId());
                        req.set_status(task_runner_->Status());
                        req.set_current_record(task_runner_->CurrentRecord());
                        req.mutable_task_counter()->set_input_records(task_runner_->InputRecord());
                        req.mutable_task_counter()->set_output_records(task_runner_->OutputRecord());
                    }
                    
                    baidu::ucp::proto::FetchTaskResponse response;
                    baidu::ucp::system::ErrorCode ec = master_proxy_->FetchTask(req, response);
                    if (ec.Code() == 0) {
                        if (response.action() == baidu::ucp::proto::kQuit) {
                            if (NULL != task_runner_.get()) {
                                task_runner_->Quit(true);
                            }
                            exit(0);
                        }
                        
                        if (response.has_job_description()) {
                            if (NULL != task_runner_.get()) {
                                task_runner_->Quit(true);
                            }
                            
                            boost::shared_ptr<baidu::ucp::task::Task> task(new baidu::ucp::task::Task);
                            task->begin_key = response.start_key();
                            task->end_key = response.end_key();
                            task->job.CopyFrom(response.job_description());
                            
                            task_runner_.reset(new baidu::ucp::task::TaskRunner(task));
                            ec = task_runner_->Setup();
                            if (ec.Code() != 0) {
                                LOG(INFO) << "set up task runner failed: " << ec.Message();
                                task_runner_.reset();
                            } else {
                                task_exe_pool_.AddTask(boost::bind(&TaskFetcher::ExecuteTaskRutine, this, task_runner_));
                            }
                        }
                    }
                    
                    sleep(2);
                }
            }
        }
    }
}
