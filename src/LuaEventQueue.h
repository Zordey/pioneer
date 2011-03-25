#ifndef _LUAEVENTQUEUE_H
#define _LUAEVENTQUEUE_H

#include "LuaManager.h"
#include "LuaObject.h"
#include "DeleteEmitter.h"

#include <list>

class LuaEventBase {
public:
	virtual ~LuaEventBase() {}
};

template <typename T0, typename T1>
class LuaEvent : public LuaEventBase {
public:
	LuaEvent(T0 *arg0, T1 *arg1) : m_arg0(arg0), m_arg1(arg1) { }
	virtual ~LuaEvent() {}
	
	T0 *m_arg0;
	T1 *m_arg1;
};

template <typename T0>
class LuaEvent<T0,void> : public LuaEventBase {
public:
	LuaEvent(T0 *arg0) : m_arg0(arg0) { }
	virtual ~LuaEvent() {}
	
	T0 *m_arg0;
};

template <>
class LuaEvent<void,void> : public LuaEventBase {
public:
	LuaEvent() { }
	virtual ~LuaEvent() {}
};


class LuaEventQueueBase : public DeleteEmitter {
	friend class LuaSubObject<LuaEventQueueBase>;

public:
	void RegisterEventQueue();
	void ClearEvents();
	void Emit();

protected:
	LuaEventQueueBase(const char *name) : m_name(name) {}
	virtual ~LuaEventQueueBase() { ClearEvents(); }

	const char *m_name;

	std::list<LuaEventBase*> m_events;

private:
	static int l_connect(lua_State *l);
	static int l_disconnect(lua_State *l);

	virtual void PrepareLuaStack(lua_State *l, const LuaEventBase *eb) = 0;
};

template <typename T0=void, typename T1=void>
class LuaEventQueue : public LuaEventQueueBase {
public:
	LuaEventQueue(const char *name) : LuaEventQueueBase(name) { }

	inline void Queue(T0 *arg0, T1 *arg1) {
		m_events.push_back(new LuaEvent<T0,T1>(arg0, arg1));
	}

protected:
	inline void PrepareLuaStack(lua_State *l, const LuaEventBase *eb) {
		const LuaEvent<T0,T1> *e = static_cast<const LuaEvent<T0,T1>*>(eb);
		LuaSubObject<T0>::PushToLua(e->m_arg0);
		LuaSubObject<T1>::PushToLua(e->m_arg1);
	}
};

template <typename T0>
class LuaEventQueue<T0,void> : public LuaEventQueueBase {
public:
	LuaEventQueue(const char *name) : LuaEventQueueBase(name) { }

	inline void Queue(T0 *arg0) {
		m_events.push_back(new LuaEvent<T0,void>(arg0));
	}

protected:
	inline void PrepareLuaStack(lua_State *l, const LuaEventBase *eb) {
		const LuaEvent<T0,void> *e = static_cast<const LuaEvent<T0,void>*>(eb);
		LuaSubObject<T0>::PushToLua(e->m_arg0);
	}
};

template <>
class LuaEventQueue<void,void> : public LuaEventQueueBase {
public:
	LuaEventQueue(const char *name) : LuaEventQueueBase(name) { }

	inline void Queue() {
		m_events.push_back(new LuaEvent<void,void>());
	}

protected:
	inline void PrepareLuaStack(lua_State *l, const LuaEventBase *eb) { }
};

#endif
