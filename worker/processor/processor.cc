// Copyright (c) 2016, Baidu.com, Inc. All Rights Reserved
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "processor.h"
#include <sys/socket.h>
#include <sys/wait.h>

namespace baidu {
    namespace ucp {
        namespace processor {

            Processor::Processor() : pid_(-1) {
                fd_[0] = -1;
                fd_[1] = -1;
            }

            Processor::~Processor() {

            }

            baidu::ucp::system::ErrorCode Processor::Setup(const std::string& cmd) {
                if ((pid_ = fork()) == 0) {
                    close(fd_[0]);
                    dup2(fd_[1], STDOUT_FILENO);
                    dup2(fd_[1], STDIN_FILENO);
                    close(fd_[1]);

                    char* argv[] = {
                        const_cast<char*> ("sh"),
                        const_cast<char*> ("-c"),
                        const_cast<char*> (cmd.c_str()),
                        NULL
                    };
                    ::execv("/bin/sh", argv);
                    _exit(-1);
                } else if (pid_ != -1) {
                    close(fd_[1]);
                    close(fd_[0]);
                } else {
                    return PERRORCODE(-1, errno, "fork failed, cmd is: ", cmd.c_str());
                }

                return ERRORCODE_OK;
            }

            baidu::ucp::system::ErrorCode Processor::Process(int64_t ts, const std::string& key, const std::string& value) {
                assert(pid_ != -1);
                int ret = ::write(fd_[0], key.c_str(), key.size());
                if (-1 == ret) {
                    return PERRORCODE(-1, errno, "write key failed");
                }

                ret = ::write(fd_[0], value.data(), value.size());
                if (-1 == ret) {
                    return PERRORCODE(-1, errno, "write value failed");
                }

                ret = ::write(fd_[0], "\n", 1);
                if (-1 == ret) {
                    return PERRORCODE(-1, errno, "write ln failed");
                }
                return ERRORCODE_OK;
            }

            baidu::ucp::system::ErrorCode Processor::Output(const std::string& key, const std::string& value) {
                return ERRORCODE_OK;
            }

            void Processor::Quit(bool w) {
                if (-1 == pid_) {
                    return;
                }

                shutdown(fd_[0], SHUT_WR);
                if (w) {
                    // kill pid
                }
                ::waitpid(pid_, NULL, 0);
            }
        }
    }
}
