
#ifndef JHLIB_MSG_QUEUE_H
#define JHLIB_MSG_QUEUE_H

typedef struct _msgQueue_t msgQueue_t;


typedef struct
{
	sint32 msgId;
	uint32 paramA;
	uint32 paramB;
	void* data; // additional dynamic data, automatically freed
}msgInfo_t;

typedef struct _msgInfoLink_t
{
	msgInfo_t msgInfo;
	// next
	_msgInfoLink_t *next;
}msgInfoLink_t;

typedef struct _msgQueue_t
{
#ifdef _WIN32
	CRITICAL_SECTION criticalSection;
#else
  pthread_mutex_t criticalSection;
#endif
	sint32 nameId;
	msgInfoLink_t *first;
	msgInfoLink_t *last; // for fast appending
	// message queue callback
#ifdef _WIN32
	void (JHCALLBACK *messageProc)(msgQueue_t* msgQueue, sint32 msgId, uint32 param1, uint32 param2, void* data);
#else
  void *messageProc(msgQueue_t* msgQueue, sint32 msgId, uint32 param1, uint32 param2, void* data);
#endif
	void* custom;
}msgQueue_t;


void msgQueue_init();

sint32 msgQueue_generateUniqueNameId();

#ifdef _WIN32
msgQueue_t* msgQueue_create(sint32 nameId, void (JHCALLBACK *messageProc)(msgQueue_t* msgQueue, sint32 msgId, uint32 param1, uint32 param2, void* data));
#else
msgQueue_t* msgQueue_create(sint32 nameId, void *messageProc(msgQueue_t* msgQueue, sint32 msgId, uint32 param1, uint32 param2, void* data));
#endif
//void msgQueue_activate(msgQueue_t* msgQueue);

bool msgQueue_check(msgQueue_t* msgQueue);
bool msgQueue_postMessage(sint32 destNameId, sint32 msgId, uint32 param1, uint32 param2, void* data);

#define msgQueue_setCustom(x, v)	(x)->custom = v
#define msgQueue_getCustom(x)		(x)->custom

#endif

