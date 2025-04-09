#include "concurrency/PrintThreadSafe.h"
#include <iostream>
#include <mutex>
#include <thread>

using namespace std;

std::mutex PrintThreadSafe::mtx;
