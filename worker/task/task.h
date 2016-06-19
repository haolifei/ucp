// Copyright (c) 2016, Baidu.com, Inc. All Rights Reserved
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#pragma once
#include "proto/master.pb.h"
#include <string>

namespace baidu {
    namespace ucp {
        namespace task {
            
            class Task {
            public:
                baidu::ucp::proto::JobDescription job;
                std::string begin_key;
                std::string end_key;
            };
        }
    }
}
