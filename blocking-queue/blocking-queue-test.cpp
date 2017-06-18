#define BOOST_TEST_MODULE First_TestSuite
#define BOOST_TEST_DYN_LINK

#include <boost/test/unit_test.hpp>
#include "blocking-queue.hpp"
#include <thread>

using namespace std::chrono;

BOOST_AUTO_TEST_CASE( EnqueueTwoDequeueTwo )
{
	BoundedQueue<string> queue(10);

	queue.Enqueue("hello");
	queue.Enqueue("world");

	BOOST_CHECK_EQUAL("hello", queue.Dequeue());
	BOOST_CHECK_EQUAL("world", queue.Dequeue());
}

void delayedThread(BoundedQueue<string> *queue)
{
	this_thread::sleep_for(seconds(1));
	queue->Enqueue("delayed");
}

BOOST_AUTO_TEST_CASE(DelayedDequeue)
{
	BoundedQueue<string> queue(10);

	thread delayed(delayedThread, &queue);

	queue.Enqueue("hello");
	queue.Enqueue("world");

	delayed.join();

	BOOST_CHECK_EQUAL("hello", queue.Dequeue());
	BOOST_CHECK_EQUAL("world", queue.Dequeue());
	BOOST_CHECK_EQUAL("delayed", queue.Dequeue());
}

void delayedDequeueThread(BoundedQueue<string> *queue)
{
	this_thread::sleep_for(seconds(1));
	queue->Dequeue();
}
BOOST_AUTO_TEST_CASE(DelayedEnqueue)
{
	BoundedQueue<string> queue(2);

	thread delayed(delayedDequeueThread, &queue);

	queue.Enqueue("delayed");
	queue.Enqueue("hello");
	queue.Enqueue("world");

	delayed.join();

	BOOST_CHECK_EQUAL("hello", queue.Dequeue());
	BOOST_CHECK_EQUAL("world", queue.Dequeue());
}
