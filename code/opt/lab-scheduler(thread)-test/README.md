# XV6 Testing Scheduler And Compare Tool

This Patch for XV6 provides a tool to test your algorithms and see the behavior of the various schedulers and compare them to choose the most appropriate one for your needs.

## Comparison Metrics
Tests are performed on a single CPU.
The comparison metrics used in this test are Makespan, Speedup and Efﬁciency:
- **MAKESPAN** - Makespan represents the point of time where computation of the last task is completes. 
- **SPEEDUP** - The speedup is defined as the fraction of the sequential computation time to the makespan of the schedule.
- **EFFICIENCY** - Efficiency is defined as the speedup divided by the quantity of processors used in each run.
For more info look the paper.

## How it is made
The test was created on the basis of "lab-scheduler-runtime", "lab-threads" and "06K - Scheduler (Policies)".
I used thread, so "lab-threads", to create process, in order to make the code more user friendly and facilitate possible future changes by other users.
To make possible a runtime changes scheduler, I used "lab-scheduler-runtime" and to add some scheduler I used "06K - Scheduler (Policies)";

## How to insert your stress algorithm
You can insert your algorithm into file `cmp_testing_scheduler.c`:
```c++
void thread1(void *arg)
{
	int i;
	int counter;

	sleep(10);

	for (i=0; i<TARGET_COUNT_PER_THREAD; i++) {
		/*Start critical section*/
		sem_wait(SEMAPHORE_NUM1, 1);
		/*Algorithm to stress Scheduler  --> change with what do you want*/ 
		counter = g_counter1;
		sleep(0);
		counter++;
		counter=counter*2;
		counter=counter/2;
		counter=counter*3;
		counter=counter/3;
		sleep(0);
		if(counter%700==0){
			printf(1,"%d",*(int*)arg);
		}
		g_counter1 = counter;
		/*End algorithm*/
		sem_signal(SEMAPHORE_NUM1, 1);
		/*End critical section*/
	}
	exit();
}
```
Before sem_wait() you can put the algorithm out of critical section. You can also change the number of iterations and threads by changing the value of `TARGET_COUNT_FOR_THREAD` and `NUM_THREADS` 
The example test uses two SEMAPHORE (you can delete or create new).
To add new scheduler look "lab-scheduler-runtime", but remember to change the `NUM_SCHEDULER` value and the fcfs scheduler remains in the same position.
The numbers printed correspond to the thread that is running. So, you can see the preemption generated by the scheduler. In this example the print occurs every 700 iterations to be more readable.

## Expected result
By executing the cmp_testing_scheduler we can have different results.
For example if the algorithms inside the critical section are more stressed for the CPU we expect that the best choice is a preemptive scheduler such as RR because we avoid a starvation problem by executing the same process until it's finished (It can take a long time);
Otherwise, if we have the opposite situation, we expect that the best choice is a non-preemptive scheduler such as FCFS, because the context-switch is a time consuming activity and it is similar to the cpu running time requested by these different algorithms. 

## Run It ##
The tool is fully integrated with the generate.sh script used to build the system's patches, all functions of previous labs are available.
To run it just use:
`$ sudo ./generate.sh -l <labn>`
Inside XV6 to run the test the command is:
`cmp_testing_scheduler`

## Contributors ##
* Biagio Ferri

## Credits ##
The functions to create this script were taken from previous labs.
The full paper is here:

* https://www.researchgate.net/publication/324278215_On_benchmarking_task_scheduling_algorithms_for_heterogeneous_computing_systems

Thanks to:

* Ashish Kumar Maurya
* Anil Tripathi
* Federico Campo
* Davide Iavicoli
