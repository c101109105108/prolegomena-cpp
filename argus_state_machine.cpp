#include <iostream>
#include <thread>
#include <chrono>
#include <cmath>
#include <thread>
#include <fstream>
#include <pigpio.h>  

enum ArgusState {

IDLE
SEARCH_T
SEARCH_L
SEARCH_TL
FOUND_T
FOUND_L
FOUND_TL
TRACK
}

int main() { 
  ArgusState sleeeeeeeeepy_state = IDLE;
