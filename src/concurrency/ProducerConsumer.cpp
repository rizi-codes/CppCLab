#include <iostream>
#include <mutex>
#include <thread>
#include "concurrency/ProducerConsumer.h"



ProducerConsumer::ProducerConsumer(int maxSize) :maxSize(maxSize), buffer(maxSize) {
}


void ProducerConsumer::consume() {
    
}


void ProducerConsumer::produce() {
    
}
