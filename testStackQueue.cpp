#define CATCH_CONFIG_MAIN
#include <iostream>
#include "cs221util/catch.hpp"
#include "stack.h"
#include "queue.h"
//using namespace cs221util;
using namespace std;

TEST_CASE("deque::basic functions","[weight=1][part=deque]"){

    Deque<int> intDeque;
    vector<int> result;
    vector<int> expected;
    for (int i = 10; i > 0; i--) {
        expected.push_back(i);
    }
/*    printf("expected: ");
    for (int i = 10; i > 0; i--) {
        printf("%d ", expected[i]);
    }*/
    for (int i = 1; i <= 10; i++) { 
        intDeque.pushR(i);
        printf("\n result:%d ", intDeque.peekR());

    }

/*    printf("\nresult: ");
    for (int i = 10; i > 0; i--) {
        printf("\n%d ", intDeque.popR());
  
    }*/

    while (!intDeque.isEmpty()) {
        result.push_back(intDeque.popR());
    }

    REQUIRE(result == expected);
}



TEST_CASE("stack::basic functions","[weight=1][part=stack]"){
    //cout << "Testing Stack..." << endl;
    Stack<int> intStack;
    vector<int> result;
    vector<int> expected;
    for (int i = 10; i > 0; i--) {
        expected.push_back(i);
    }
    for (int i = 1; i <= 10; i++) {
        intStack.push(i);
    }
    while (!intStack.isEmpty()) {
        result.push_back(intStack.pop());
    }

    REQUIRE( result == expected);
}


TEST_CASE("queue::basic functions","[weight=1][part=queue]"){
    Queue<int> intQueue;
    vector<int> result;
    vector<int> expected;
    for (int i = 1; i <= 10; i++) {
        expected.push_back(i); 
    }
    for (int i = 1; i <= 10; i++) {
        intQueue.enqueue(i);
        printf("\n result:%d ", intQueue.peek());

    }
    while (!intQueue.isEmpty()) {
        result.push_back(intQueue.dequeue());
    }
    REQUIRE( result == expected);
} 

