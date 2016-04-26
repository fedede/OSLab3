#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../include/concurrency_layer.h"

void init_concurrency_mechanisms() {
}

void destroy_concurrency_mechanisms() {
}

// Broker: inserts operations obtained from a batch file into the operations_queue of a given market.
void * broker(void * args) {
/*Input: broker_info --> 
1) char batch_file[256]
2) stock_market * market)
*/
    broker_info * currentInfo = (broker_info*) args; // Cast the *void pointer to a *broker_info pointer. 
    stock_market * currentMarket = currentInfo->market; // Create a stock_market pointer. This might not be necessary but handy in the enqueue_operation call.
    operation currentOperation; // operation struct to hold information of the operation on current batch line.
    iterator * brokerIterator = new_iterator(currentInfo->batch_file); // iterator that will parse each line of the batch file.

    if (brokerIterator == NULL) { // Error creating a new iterator. 
        perror("Error creating a new iterator. \n"); 
        return; // void calls return no value. This might show up as a warning however.
    }
    else { // Iterator was created succesfully
    	while (next_operation(brokerIterator, currentOperation.id, &currentOperation.type, &currentOperation.num_shares, &currentOperation.share_price) != EOF) {  // While there are still lines to read, continue.
		enqueue_operation(currentMarket->stock_operations, &currentOperation); // Enqueues the operation created by the next_operation call.
	}
    
	destroy_iterator(brokerIterator); // Destroys iterator to free resources.
    }
}


void* operation_executer(void * args) {
}


void* stats_reader(void * args) {
}
