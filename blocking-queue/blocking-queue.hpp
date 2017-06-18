#ifndef BOUNDED_QUEUE_H_INCLUDED
#define BOUNDED_QUEUE_H_INCLUDED

#include <queue>
#include <mutex>
#include <condition_variable>

using namespace std;

template <class T> class BoundedQueue {
	private:
		queue<T> m_queue;
		int m_size;
		condition_variable cv_not_empty;
		condition_variable cv_not_full;
		mutex mtx;
	public:
		BoundedQueue(int size)
		{
			m_size = size;
		};

		void Enqueue(T element)
		{
			unique_lock<mutex> lck(mtx);
			while (Count() == Size()) cv_not_full.wait(lck);

			m_queue.push(element);
			cv_not_empty.notify_all();
		};

		T Dequeue()
		{
			unique_lock<mutex> lck(mtx);
			while (m_queue.empty()) cv_not_empty.wait(lck);

			auto result = m_queue.front();
			m_queue.pop();
			cv_not_full.notify_all();

			return result;
		};

		int Count()
		{
			return m_queue.size();
		};

		int Size()
		{
			return m_size;
		};
};

#endif // BOUNDED_QUEUE_H_INCLUDED
