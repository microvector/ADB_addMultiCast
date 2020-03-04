/*
 * Copyright (C) 2015 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef __ADB_LISTENERS_H
#define __ADB_LISTENERS_H

#include "adb.h"

#include <string>

#include <android-base/macros.h>

/* add by king begin!! */
#ifdef _WIN32
#include <winsock2.h>
#else
#include <arpa/inet.h>
#include <sys/socket.h>
#endif

#include <string.h>
#include <atomic>
#include <iostream>
#include <errno.h>
#include <list>
#include <mutex>


#define BUF_SIZE 150
#define MCAST_ADDR "224.1.1.8" /*临时组播地址，用户可用，全网有效 224.0.2.0~238.255.255.255*/
#define MCAST_PORT 9999

/* add by king end!! */

// error/status codes for install_listener.
enum InstallStatus {
  INSTALL_STATUS_OK = 0,
  INSTALL_STATUS_INTERNAL_ERROR = -1,
  INSTALL_STATUS_CANNOT_BIND = -2,
  INSTALL_STATUS_CANNOT_REBIND = -3,
  INSTALL_STATUS_LISTENER_NOT_FOUND = -4,
};

InstallStatus install_listener(const std::string& local_name, const char* connect_to,
                               atransport* transport, int no_rebind, int* resolved_tcp_port,
                               std::string* error);

std::string format_listeners();

InstallStatus remove_listener(const char* local_name, atransport* transport);
void remove_all_listeners(void);

void close_smartsockets();
/* add by king begin!!*/
static auto& get_device_lock = *new std::recursive_mutex();

// host connected to local_net`s device
static std::atomic<bool> connect_success(false);
// host receive data from local_net`s device
static std::atomic<bool> reve_info_valid(false);
// local_net`s device list
static auto& local_devices_list = *new std::list<std::string>();
bool get_device(std::list<std::string> result_list,std::string *device_info);
void reve_mcasts();

/* add by king end!!*/


#endif /* __ADB_LISTENERS_H */
