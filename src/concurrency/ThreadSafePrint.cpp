#include <iostream>
#include <thread>
#include <mutex>
#include "concurrency/PrintThreadSafe.h"

using namespace std;

std::mutex PrintThreadSafe::mtx;

