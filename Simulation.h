#pragma once
#include <iostream>
#include <ctime>

using namespace std;

#include "Customer.h"
#include "Timer.h"
#include "DynamicQueue.h"


const int NUM_CATEGORIES = 5;
class Simulation {

   public:

       //default constructor
       Simulation() {
          

           avgCustomerServiceTime = 0;
           avgCustomerWaitingTime = 0;
           avgCashierIdleTime = 0;
           totalServiceTime = 0;
           totalCustomerWaitingTime = 0;
           totalCashierIdleTime = 0;
           totalNumberOfCustomers = 0;
           customersRemaining = 0;

           servicePercent = new int[NUM_CATEGORIES];
           allCashiers = new dynamic_queue<Customer>[numCashiers];
          

           //get inputs for simulation
           cout << "Please enter the average arrival rate of customers in number per minute: " << endl;
           cin >> arrivalRate;

           cout << "Please enter the number of registers: " << endl;
           cin >> numCashiers;

           //create the correct number of cashiers
           for(int i = 0; i < numCashiers; i++) {
              
               allCashiers[i] = *new dynamic_queue<Customer>;
           }

           cout << "Please enter the length of time to run the simulation in minutes: " << endl;
           cin >> lengthOfSimulation;

           //cout << "Please enter the distribution of customer service times: " << endl;
           int percent = 0;
           int   sum = 0;
           for (int i = 0; i < NUM_CATEGORIES; i++) {

               //cout << " <= " << (i + 1) << " min. ";  
               //cin >> percent;
               //servicePercent[i] = percent;
               //sum += percent;
               //cout << "sum: " << sum << endl;
               servicePercent[i] = 20 + sum;
               sum += 20;
           }

           //check to make sure the inputs add up to 100
           while (sum != 100) {
              
               cout << "Invalid distribution. Must add up to 100 %" << endl;
               cout << "old sum was: " << sum << endl;
               sum = 0;
               for (int i = 0; i < NUM_CATEGORIES; i++) {
                  
                   cout << " <= " << i + 1 << " min. ";   cin >> percent;
                   servicePercent[i] = percent;
                   sum += percent;
                   cout << "sum: " << sum << endl;
               }
           }          

           //set the countdown timer
           myTimer.set(lengthOfSimulation);      

           //intialize random number generator
           long seed = long(time(0));
           srand(seed);
       }
       //destructor
       //deletes all dynamically created elements of allCashiers[]
       //deletes dynamically created member arrays
       ~Simulation() {

           for (int i = 0; i < numCashiers - 1; i++) {
          
               delete &allCashiers[i];
           }

           delete [] allCashiers;
           delete [] servicePercent;
       }
       //this function is the 'brains' of the simulation. It computes and processes customers and cashiers for the runtime specified.
       void run() {
          
           while (myTimer.timeRemaining() > 0) {

               //go through each cashier and run the service function which will check
               //if their customer is ready to check out and do so if able
               for (int i = 0; i < numCashiers; i++) {
                  
                   if (!allCashiers[i].isEmpty()) {
              
                       int busyTimeLeft = allCashiers[i].getHead().getServiceTime();
                      
                       service(busyTimeLeft, i);                  
                   }
                   else {

                       totalCashierIdleTime++;
                   }
               }              
               checkForNewCustomer();
               myTimer.tick();
           }

           cout << "\nNot accepting any more customers -- service remaining customers in line" << endl;
          
           for (int i = 0; i < numCashiers; i++) {

               while (!allCashiers[i].isEmpty()) {

                   int busyTimeLeft = allCashiers[i].getHead().getServiceTime();
                   service(busyTimeLeft, i);                  
               }
           }

           display(cout);
       }
       //function is passed the remaining service time of the customer in the front of the line
       // as well as the cashier the customer is in line for
       void service(int& busyTimeRemaining, int cashier) {
      
           if (busyTimeRemaining > 0) { //the head customer still has more service time to process

               busyTimeRemaining--;
               allCashiers[cashier].getHead().setServiceTime(busyTimeRemaining);

               //add waiting time of the customers in line to the total
               totalCustomerWaitingTime += allCashiers[cashier].getSize() - 1;

               return;
           }
           else {
               //check to see if this cashier are nonempty and if they are have each on
               if (!allCashiers[cashier].isEmpty()) { //there is a customer ready to check out

                   int arrivalTime = allCashiers[cashier].getHead().getArrivalTime();

                   allCashiers[cashier].dequeue();   //cash out head customer
                  
                   if (!allCashiers[cashier].isEmpty()) {

                       Customer nextCust = allCashiers[cashier].getHead();
                       busyTimeRemaining = nextCust.getServiceTime();
                   }

                   customersRemaining--;                  
               }
           }          
       }
       //This function checks for and adds customers to the smallest line of a cashier
       void checkForNewCustomer() {

           //activates new customer procedure for each arrival per minute. Case1: arrivalRate > 1
           for (int i = 0; i < arrivalRate; i++) {

               //a new customer is ready to get in line, create random service time
               int r = rand() % 100;
               int serviceTime = 0;
               int culmServiceTime = servicePercent[serviceTime];

               while (r > culmServiceTime) {

                   culmServiceTime += servicePercent[serviceTime];
                   serviceTime++;
               }

               totalServiceTime += serviceTime + 1;

               //create a new customer and add it to the smallest line at a cashier
               Customer newCust(myTimer, serviceTime + 1);
               totalNumberOfCustomers++;
               customersRemaining++;

               int min = 9999999;
               int smallestLine = 0;
               for (int i = 0; i < numCashiers; i++) {

                   if (allCashiers[i].getSize() < min) {

                       min = allCashiers[i].getSize();
                       smallestLine = i;
                   }
               }

               allCashiers[smallestLine].enqueue(newCust);
              
           }

           if (arrivalRate < 1) { //Case 2: arrivalRate < 1
              
               //random number between 0 and 99
               int x = rand() % 100;

               //calculates the probability that a customer has arrived
               if (x < 100 * arrivalRate) {

                   //a new customer is ready to get in line, create random service time
                   int r = rand() % 100;
                   int serviceTime = 0;
                   int culmServiceTime = servicePercent[serviceTime];

                   while (r > culmServiceTime) {

                       culmServiceTime += servicePercent[serviceTime];
                       serviceTime++;
                   }

                   totalServiceTime += serviceTime + 1;

                   //create a new customer and add it to the smallest line at a cashier
                   Customer newCust(myTimer, serviceTime + 1);
                   totalNumberOfCustomers++;
                   customersRemaining++;

                   int min = 9999999;
                   int smallestLine = 0;
                   for (int i = 0; i < numCashiers; i++) {

                       if (allCashiers[i].getSize() < min) {

                           min = allCashiers[i].getSize();
                           smallestLine = i;
                       }
                   }

                   allCashiers[smallestLine].enqueue(newCust);
               }          
           }
       }
       //Displays the average customer service and wait time as well as the average cashier idle time
       void display(ostream &out) {

           //cout << totalNumberOfCustomers;

           cout << "\n\ntotal number of customers :" << totalNumberOfCustomers << endl;

           cout << " totalservice time: " << totalServiceTime << endl;
           cout << " total customer waiting time: " << totalCustomerWaitingTime << endl;
           cout << " total cashier idle time: " << totalCashierIdleTime << endl;


           avgCustomerServiceTime = (double) totalServiceTime / totalNumberOfCustomers;
           avgCustomerWaitingTime = (double)totalCustomerWaitingTime / totalNumberOfCustomers;
           avgCashierIdleTime = (double)totalCashierIdleTime / numCashiers;


           cout << "\nThe average customer service time was: " << avgCustomerServiceTime << " minutes";
           cout << "\nThe average customer waiting time was: " << avgCustomerWaitingTime << " minutes";
           cout << "\nThe average cashier idle time was: " << avgCashierIdleTime << " minutes";
       }
   private:

       //inputs
       int lengthOfSimulation;
       double arrivalRate;
       int * servicePercent;

       //tracking variables
       int totalServiceTime;
       int totalCustomerWaitingTime;
       int totalCashierIdleTime;
       int totalNumberOfCustomers;
       int customersRemaining;

       //outputs
       double avgCustomerServiceTime;
       double avgCustomerWaitingTime;
       double avgCashierIdleTime;

       //countdown timer
       Timer myTimer;

       //Number of cashiers, set at runtime
       int numCashiers;

       //array of queues that house customers
       dynamic_queue<Customer> * allCashiers;
};
