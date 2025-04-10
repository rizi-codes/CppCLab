#include "concurrency/ThreadSafePrint.h"
#include <iostream>
#include <mutex>
#include <thread>

using namespace std;

std::mutex ThreadSafePrint::mtx;
