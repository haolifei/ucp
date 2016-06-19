// Copyright (c) 2016, Baidu.com, Inc. All Rights Reserved
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
#include "input.h"
#include "tera_scaner_input.h"
#include "boost/smart_ptr/shared_ptr.hpp"

namespace baidu {
    namespace ucp {
        namespace input {
            
            // simple factory
            boost::shared_ptr<Input> Input::CreateInput(boost::shared_ptr<baidu::ucp::task::Task> task) {
                boost::shared_ptr<TeraScanerInput> input(new TeraScanerInput(task));
                return input;
            }
        }
    }
}
