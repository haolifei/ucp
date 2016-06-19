/***************************************************************************
 * 
 * Copyright (c) 2016 Baidu.com, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file worker/input/tera_scaner_input.cc
 * @author haolifei(com@baidu.com)
 * @date 2016/06/19 14:57:32
 * @brief 
 *  
 **/

#include "tera_scaner_input.h"
namespace baidu {
    namespace ucp {
        namespace input {
            bool TeraScanerInput::HasNext() {
                return false;
            }

            baidu::ucp::system::ErrorCode TeraScanerInput::Next(int64_t ts, const std::string& key, const std::string& value) {
                return ERRORCODE_OK;
            }


            baidu::ucp::system::ErrorCode TeraScanerInput::Setup() {
                return ERRORCODE_OK;
            }

        }
    }
}
