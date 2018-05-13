#pragma once
/*************************************************************************
* Clockwork-Engine
* A C++/Opengl/GLFW3 game engine
* Website: clock-work.tk
*------------------------------------------------------------------------
* Copyright (C) 20017-2018 Niko Miklis <clock-work@gmx.de> - All Rights Reserved
*
* This software is provided 'as-is', without any express or implied
* warranty. In no event will the authors be held liable for any damages
* arising from the use of this software.
* You can use this software under the following License: https://github.com/Clock-work/Clockwork-Engine/blob/master/LICENSE
*************************************************************************/

#include <thread>
#include <mutex>
#include <vector>
#include <queue>

namespace clockwork {
	namespace utils {

		class ThreadPool ///aufgaben dürfen nicht zu klein/schnell sein, sonst bringt multithread nichts: müssen große aufgaben sein
		{

		private:

			struct Captree
			{

				struct Container
				{
					std::vector<std::function<void()>> tasks;
				};

				struct Capsule
				{
					Container* container;
					std::mutex lock;
					int size;
					Capsule()
						: size(0), container(new Container())
					{}
				};

				Capsule* capsules;
				int count;
				int bestpos;
				int counter;

				Captree(int threadCount)
					: count(threadCount), bestpos(0), counter(0)
				{
					capsules = new Capsule[count];
				}


			private:
				void findBestPos()
				{
					std::unique_lock<std::mutex> tempLock(capsules[bestpos].lock, std::defer_lock);
					tempLock.lock();
					int bestsize = capsules[bestpos].size;
					tempLock.unlock();
					for ( int i = 0; i < count; ++i )
					{
						if ( i == bestpos )
							continue;
						Capsule& cap = capsules[i];
						std::unique_lock<std::mutex> lock(cap.lock, std::defer_lock);
						lock.lock();
						int size = cap.size;
						lock.unlock();
						if ( size < bestsize )
						{
							bestsize = size;
							bestpos = i;
						}
					}
				}

			public:

				//container pointer muss danach gelöscht werden | wenn pointer null ist, sind keine tasks vorhanden
				//threads sollten testen ob nicht null, dann tasks ausführen, sonst relativ lange timeout warten
				Container* getTasks(int threadNumber)
				{
					Capsule& temp = capsules[threadNumber];
					std::unique_lock<std::mutex> lock(temp.lock, std::defer_lock);
					lock.lock();
					if ( temp.container->tasks.empty() )
					{
						lock.unlock();
						return nullptr;
					}
					Container* container = temp.container;
					temp.container = new Container();
					temp.size = 0;
					lock.unlock();
					return container;
				}

				void addTask(std::function<void()>&& task)
				{
					if ( counter == 6 )//bestpos after 5 tasks new calculated
					{
						findBestPos();
						counter = 0;
					}
					++counter;

					Capsule& cap = capsules[bestpos];
					std::unique_lock<std::mutex> lock(cap.lock, std::defer_lock);
					lock.lock();
					cap.container->tasks.push_back(std::move(task));
					++cap.size;
					lock.unlock();
				}

				bool isEmpty()
				{
					for ( unsigned int i = 0; i < count; ++i )
					{
						Capsule& temp = capsules[count];
						std::unique_lock<std::mutex> lock(temp.lock, std::defer_lock);
						bool test = lock.owns_lock();
						lock.lock();//crash/exception ? not working 
						if ( temp.size != 0 )
						{
							lock.unlock();
							return false;
						}
						lock.unlock();
					}
					return true;
				}

			};

		public:
			class ThreadWorker
			{
				friend class ThreadPool;

			private:
				ThreadPool* m_pool;
				bool m_running;
				bool m_working;
				std::mutex m_lock;
				int m_id;
				std::thread m_thread;

			public:
				ThreadWorker(ThreadPool* pool, int id) noexcept;
				void running() noexcept;

				~ThreadWorker() noexcept
				{
					m_running = false;//not working
					m_thread.join();
				}

			};

		private:
			bool m_started;
			int m_threadcount;
			std::vector<ThreadWorker*> m_workers;
			Captree m_tree;

		public:

			ThreadPool(unsigned int threadCount=4, unsigned int threadPriority=2)
				: m_started(false), m_threadcount(threadCount), m_tree(threadCount)
			{
				m_workers.reserve(threadCount);
				start();
			}

			~ThreadPool()
			{
				stop();

			}

			template<typename type, typename ...Args>
			void addTask(type* object,void ( type::*method )( Args...), Args&&... args)//as many method parameters as you want 
			{
				m_tree.addTask([=] (){
					( object->*method )( std::forward<Args>(args)... );//foward=lvalue, or rvalue arguments depending on function call and therfor template parame args(lvalue reference, or rvalue reference) 
				});			
			}

			void start()//not working
			{
				if (!m_started)
				{
					for ( unsigned int i = 0; i < m_threadcount; ++i )
					{
						m_workers.push_back(new ThreadWorker(this,i));
					}
					m_started = true;
				}
			}

			void stop()
			{
				if (m_started)
				{
					for ( unsigned int i = 0; i < m_threadcount; ++i )
					{
						delete m_workers.at(0);
						m_workers.erase(m_workers.begin());
					}
					m_started = false;
				}
			}

			bool isWorking()//funktioniert anscheinend vielleicht
			{
				//if ( !m_tree.isEmpty() )
					//return true;
				for ( unsigned int i = 0; i < m_threadcount; ++i )
				{
					std::unique_lock<std::mutex> lock(m_workers.at(i)->m_lock, std::defer_lock);
					lock.lock();
					if ( m_workers.at(i)->m_working )
					{
						lock.unlock();
						return true;
					}
					lock.unlock();
				}
				std::this_thread::sleep_for(std::chrono::duration<double>(0.5));
				for ( unsigned int i = 0; i < m_threadcount; ++i )
				{
					std::unique_lock<std::mutex> lock(m_workers.at(i)->m_lock, std::defer_lock);
					lock.lock();
					if ( m_workers.at(i)->m_working )
					{
						lock.unlock();
						return true;
					}
					lock.unlock();
				}
				return false;
			}

			bool isRunning()
			{
				return true;
			}

			void waitWorking()
			{

			}



		};

		ThreadPool::ThreadWorker::ThreadWorker(ThreadPool* pool, int id) noexcept
			: m_pool(pool), m_running(true), m_working(false), m_id(id), m_thread(&ThreadWorker::running, this)
		{

		}

		void ThreadPool::ThreadWorker::running() noexcept
		{
			while ( m_running )
			{
				std::unique_lock<std::mutex> lock(m_lock, std::defer_lock);
				lock.lock();
				m_working = true;
				lock.unlock();
				Captree::Container* container = m_pool->m_tree.getTasks(m_id);
				if ( container != nullptr )
				{
					for ( unsigned int i = 0; i < container->tasks.size(); ++i )
					{
						container->tasks.at(i)( );
					}
					delete container;
				}
				else
				{
					lock.lock();
					m_working = false;
					lock.unlock();
					std::this_thread::sleep_for(std::chrono::duration<double>(1));
				}
			}
		}

		struct str2
		{
			long long into = 10;
			std::mutex muti;
			void testi()
			{
				muti.lock();
				for ( int i = 0; i < 1000; ++i )
				{
					into += 10;
					into -= 10;
					into *= 2;
					into /= 2;
					into++;
					into--;
					into += 2;
					into -= 2;
					into++;
				}
				muti.unlock();
			}
		};

		void test3()
		{
			ThreadPool pool {6,6};
			str2 ob1;
			str2 ob2;
			str2 ob3;
			str2 ob4;
			str2 ob5;
			str2 ob6;
			str2 ob7;
			str2 ob8;
			std::cout << "START!" << std::endl;


			for ( int i = 0; i < 500000; ++i )
			{
				pool.addTask(&ob1, &str2::testi);
				pool.addTask(&ob2, &str2::testi);
				pool.addTask(&ob3, &str2::testi);
				pool.addTask(&ob4, &str2::testi);
				pool.addTask(&ob5, &str2::testi);
				pool.addTask(&ob6, &str2::testi);
				pool.addTask(&ob7, &str2::testi);
				pool.addTask(&ob8, &str2::testi);
			}

			//std::this_thread::sleep_for(std::chrono::duration<double>(10));

			while ( pool.isWorking() )
			{
				std::this_thread::sleep_for(std::chrono::duration<double>(0.1));
			}
			//std::this_thread::sleep_for(std::chrono::duration<double>(1));
			std::cout << "STOP!"<< ob1.into<<"  "<<ob2.into << ob3.into << ob4.into << ob5.into << ob6.into << ob7.into << ob8.into << std::endl;
		}

	}
}