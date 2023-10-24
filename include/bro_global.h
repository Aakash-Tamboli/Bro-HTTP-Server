#ifndef __BRO_GLOBAL__
#define __BRO_GLOBAL__ 1
#include<iostream>
#include<map>
#include<forward_list>
#include<set>
#include<queue>
#include<vector>
#include<unistd.h>
#include<string.h>
#include<sys/stat.h>
#include<bits/stdc++.h>
#ifdef _WIN32
#include<windows.h>
#endif
#ifdef linux
#include<arpa/inet.h>
#include<sys/socket.h>
#endif

using namespace std;
#define _forward_to(request,url) \
request.forwardTo(url); \
return;

extern const char *PATH_SEPRATOR;

enum __container_operation_failure_reason__ {__KEY_EXISTS__,__KEY_DOES_NOT_EXIST__,__OUT_OF_MEMORY__,__VALUE_SIZE_MISMATCH__};
enum __request_method__{__GET__,__POST__,__PUT__,__DELETE__,__CONNECT__,__TRACE__,__HEAD__,__OPTIONS__};
struct __URL__mapping;
#endif
