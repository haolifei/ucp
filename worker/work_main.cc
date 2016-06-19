/***************************************************************************
 * 
 * Copyright (c) 2016 Baidu.com, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file work_main.cpp
 * @author haolifei(com@baidu.com)
 * @date 2016/06/18 12:33:32
 * @brief 
 *  
 **/

#include <iostream>
#include "task/task_fetcher.h"
#include "boost/scoped_ptr.hpp"
int main(int argc, char** argv) {

    boost::scoped_ptr<baidu::ucp::task::TaskFetcher> fetcher(new baidu::ucp::task::TaskFetcher(""));
    fetcher->Setup();
    fetcher->Run();
    return 0;
}





















/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
