#ifndef _LUAOBJECT_H
#define _LUAOBJECT_H

#include <stdint.h>

#include "LuaManager.h"
#include "DeleteEmitter.h"

//
// LuaObject provides proxy objects and tracking facilities to safely get
// objects in and out of lua. the basic idea is that for every class you want
// to expose to lua, you define LuaSubObject wrapper class that defines the
// lua name lua name, methods and metamethods for that class. you then call
// methods on this class to push and pull objects to and from the lua stack
//
//
// if you just want to use it, do something like:
//
// push a value onto the lua stack before method call or return (you (c++)
// remains responsible for deallocating the object)
//
//   Ship *s = new Ship("Eagle Long Range Fighter");
//   LuaShip::PushToLua(s);
//
// push a value onto the lua stack (lua will deallocate the object when it
// goes out of scope and the garbage collector runs. OBJECT MUST BE
// HEAP-ALLOCATED)
//
//   Ship *s = new Ship("Eagle Long Range Fighter");
//   LuaShip::PushToLuaGC(s);
//
// pull a value from lua the lua stack after method call (causes lua exception
// the object doesn't exist or the types don't match):
//
//   Ship *s = LuaShip::PullFromLua();
//
// note that it uses the singleton lua state provided by LuaManager. there's
// no facility to use a different lua state. if you think you need to you're
// probably doing something wrong. ask the devs if you're not sure.
//
//
// if you need to expose a new class to lua, do this (using Ship/LuaShip as an
// example)
//
//  - have your class inherit from DeleteEmitter
//
//  - add a typedef for the wrapper class to the bottom of LuaObject.h:
//      class Ship;
//      typedef LuaSubObject<Ship> LuaShip;
//
//  - arrange for the wrapper class RegisterClass() method to be called in
//    LuaManager::Init in LuaManager.cpp
//      LuaShip::RegisterClass();
//
//  - make a new file LuaShip.cpp with static data for the lua class name and
//  method/metamethod pointer tables (copy from one of the others to get the
//  idea)
//
//  - add the new file to the build system
//
//  - implement your lua methods in that file
// 
//
// if you can't add DeleteEmitter to your class for some reason (usually
// because it needs to be copyable or its heavily used by the core and would
// add significant overhead), then you'll need to subclass your class and then
// subclass LuaSubObject<T> instead of typedefing to add methods that can
// convert while pushing/pullng objects of the original class. See
// LuaSBodyPath for an example, and ask - this is tricky.
//
//
// if you want to understand how this works, read on :)
//
// the basic premise of all this is that lua never holds a pointer to the c++
// object. instead, when a c++ object is pushed to the lua stack a lua object
// (that is, a value with a metatable) is created that internally has a
// numeric identifier. the original object is added to a hashtable (the
// registry) with the identifier as the key. when lua calls a method against
// the object, the appropriate method/metamethod is called with the lua object
// on the stack. the method implementation (c++) then pulls these objects from
// the stack via wrapper classes that handle the details of looking up the
// real object in the registry
//
// objects are removed from the registry when either the c++ or the lua side
// releases them. on the lua side this is handled by the __gc metamethod. on
// the c++ side this is done via the DeleteEmitter class that all wrapped
// classes are expected to inherit from. a callback is add to the onDelete
// signal when the object is registered. when either of these things are
// called the object is removed from the registry. the callback will also
// delete the object if it was pushed with PushToLuaGC to indicate that lua
// owns the object
//

// type for internal object identifiers
typedef uintptr_t lid;

class LuaObject {
public:
	virtual ~LuaObject() {}

	// pull an LuaObject wrapper from the registry given an id. returns NULL
	// if the object is not in the registry
	static LuaObject *Lookup(lid id);

	// accessors to get the object id, pointer to the c++ object and the lua
	// type string
	inline lid GetId() const { return m_id; }
	inline DeleteEmitter *GetObject() const { return m_object; }
	inline const char *GetType() const { return m_type; }

protected:
	// instantiate an object wrapper. it gets added to the registry in
	// preparation for pushing it to the lua stack (which always happens).
	// type is the lua type string. wantdelete indicates if LuaObject should
	// delete the c++ object when it is removed from the registry
	//
	// XXX make this do PushToLua() immediately. there's no good reason not to
	LuaObject(DeleteEmitter *o, const char *type, bool wantdelete) : m_object(o), m_type(type), m_wantDelete(wantdelete) { Register(this); }

	// creates a class in the lua vm with the given name and attaches the
	// listed methods to it and the listed metamethods to its metaclass
	static void CreateClass(const char *type, const luaL_reg methods[], const luaL_reg meta[]);

	// pulls an object off the lua stack and returns its associated c++
	// object. want_type is the lua type string of the object. a lua exception
	// is triggered if the object on the stack is not of this type
	static DeleteEmitter *PullFromLua(const char *want_type);

	// creates a new lua object corresponding to the passed object wrapper
	// (already in the registry)
	static void PushToLua(LuaObject *lo);

private:
	LuaObject(const LuaObject &) {}

	// add/remove an object from the registry. Deregister() will delete the
	// LuaObject passed to it and the underlying c++ object if it ownership
	// was earlier given to LuaObject
	static void Register(LuaObject *lo);
	static void Deregister(LuaObject *lo);

	// the lua object "destructor" that gets called by the garbage collector.
	// its only part of the class so that it can call Deregister()
	static int GC(lua_State *l);

	// object id, pointer to the c++ object and lua type string
	lid            m_id;
	DeleteEmitter *m_object;
	const char    *m_type;

	// flag to indicate that lua owns the object and should delete it when its
	// deregistered
	bool m_wantDelete;

	// the wrapper object's connection to the deletion signal. this gets
	// connected on registration and disconnected on deregistration
	sigc::connection m_deleteConnection;
};


// template for a wrapper class
template <typename T>
class LuaSubObject : public LuaObject {
public:

	// registers the class with the lua vm
	static inline void RegisterClass() {
		CreateClass(s_type, s_methods, s_meta);
	};

	// wrap the object and push it onto the lua stack
	static inline LuaObject *PushToLua(T *o) {
		LuaSubObject *lo = new LuaSubObject(o, false);
		LuaObject::PushToLua(lo);
		return lo;
	}

	// wrap the object and push it onto the lua stack, taking ownership of it
	static inline LuaObject *PushToLuaGC(T *o) {
		LuaSubObject *lo = new LuaSubObject(o, true);
		LuaObject::PushToLua(lo);
		return lo;
	}

	// pull an object off the the stack, unwrap it and return it
	static inline T *PullFromLua() {
		return dynamic_cast<T *>(LuaObject::PullFromLua(s_type));
	}

private:
	LuaSubObject(T *o, bool wantdelete) : LuaObject(o, s_type, wantdelete) {}

	// lua type string, method table and metamethod table. these are defined
	// per wrapper class in the appropriate .cpp file
	static const char *s_type;
	static const luaL_reg s_methods[];
	static const luaL_reg s_meta[];
};


// these are push/pull functions to provide a consistent interface for
// primitive types
namespace LuaString {
	inline void PushToLua(const char *s) {
		assert(s);
		lua_State *l = LuaManager::Instance()->GetLuaState();
		lua_pushstring(l, s);
	}
	inline const char *PullFromLua() {
		lua_State *l = LuaManager::Instance()->GetLuaState();
		const char *s = luaL_checkstring(l, 1);
		lua_remove(l, 1);
		return s;
	}
};

namespace LuaFloat {
	inline void PushToLua(double n) {
		lua_State *l = LuaManager::Instance()->GetLuaState();
		lua_pushnumber(l, n);
	}
	inline double PullFromLua() {
		lua_State *l = LuaManager::Instance()->GetLuaState();
		double n = luaL_checknumber(l, 1);
		lua_remove(l, 1);
		return n;
	}
};

namespace LuaInt {
	inline void PushToLua(int n) {
		lua_State *l = LuaManager::Instance()->GetLuaState();
		lua_pushinteger(l, n);
	}
	inline int PullFromLua() {
		lua_State *l = LuaManager::Instance()->GetLuaState();
		int n = luaL_checkinteger(l, 1);
		lua_remove(l, 1);
		return n;
	}
};


// define some types for things we need
class Ship;
typedef LuaSubObject<Ship> LuaShip;

class SpaceStation;
typedef LuaSubObject<SpaceStation> LuaSpaceStation;

class Planet;
typedef LuaSubObject<Planet> LuaPlanet;

class Star;
typedef LuaSubObject<Star> LuaStar;

class StarSystem;
typedef LuaSubObject<StarSystem> LuaStarSystem;


// this one is more complicated. SBodyPath needs to be copyable (its used
// everywhere) which means it can't be a DeleteEmitter as required to be
// wrapped by LuaSubObject. so we create a new class and inherit from both
#include "StarSystem.h"

class UncopyableSBodyPath : public SBodyPath, public DeleteEmitter {
public:
	UncopyableSBodyPath(const SBodyPath &p) : SBodyPath(p), DeleteEmitter() {}
};

// if we wanted we could just use the UncopyableSBodyPath as-is, but that
// would mean having to create a copy of every SBodyPath before passing it to
// PushToLua() and casting the return from PullFromLua(). instead we subclass
// the subobject and implement some wrapper methods for the "real" types.
//
// XXX template this if we ever need it again
class LuaSBodyPath : LuaSubObject<UncopyableSBodyPath> {
public:
	static inline void RegisterClass() { LuaSubObject<UncopyableSBodyPath>::RegisterClass(); }

	// create an uncopyable version and pass it in. we use PushToLuaGC because
	// this is our object and we have to clean it up
	static inline LuaObject *PushToLua(SBodyPath *p) {
		UncopyableSBodyPath *up = new UncopyableSBodyPath(*p);
		return LuaSubObject<UncopyableSBodyPath>::PushToLuaGC(up);
	}

	// same idea, but caller asked us to clean it up when we're done so we
	// have to do that straight away
	static inline LuaObject *PushToLuaGC(SBodyPath *p) {
		UncopyableSBodyPath *up = new UncopyableSBodyPath(*p);
		delete p;
		return LuaSubObject<UncopyableSBodyPath>::PushToLuaGC(up);
	}

	// pull from lua, casting back to the original type
	static inline SBodyPath *PullFromLua() {
		return dynamic_cast<SBodyPath*>(LuaSubObject<UncopyableSBodyPath>::PullFromLua());
	}
};

#endif
