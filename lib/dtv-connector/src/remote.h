#pragma once

#include <boost/thread/thread.hpp>

#define GINGA_SHARED_MEMORY "connector_remote_memory"
#define GINGA_SHARED_MUTEX  "connector_remote_mutex"
#define GINGA_SHARED_SEM    "connector_remote_sem"

namespace boost {
namespace interprocess {
	class shared_memory_object;
	class remove_shared_memory_on_destroy;
	class mapped_region;
	class named_mutex;
	class named_semaphore;
}
}

namespace connector {

namespace ipc = boost::interprocess;

class Remote {
public:
	Remote( int memSize );
	virtual ~Remote();

	virtual bool start();
	virtual void stop();

protected:
	virtual void render()=0;
	void lockMemory();
	void unlockMemory();
	char *addr() const;
	int size() const;
	void clean();
	void renderThread();

private:
	int _memSize;
	boost::thread _thread;	
	ipc::shared_memory_object *_shm;
	ipc::mapped_region *_mmap;
	ipc::named_mutex *_nMutex;
	ipc::named_semaphore *_nSem;
	bool _exit;
};

}

