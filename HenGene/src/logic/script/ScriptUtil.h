
#pragma once

#define NOMINMAX

#include "logic/script/Script.h"

#include <chaiscript/chaiscript.hpp>
#include <functional>
#include <vector>

namespace logic
{
	namespace script
	{
		namespace util
		{
			void clearScriptData();
			void registerScriptData(const std::function<void(Script &)> & data);
			void applyScriptData(Script & script);

			// ...

			template<typename Enum>
			void addEnum(Script & script, const std::string & name, const std::vector<std::pair<Enum, std::string>> & pairs);
			template<typename Type>
			void addType(Script & script, const std::string & name);
			template<typename Parent, typename Child>
			void addRelation(Script & script);

			template<typename Type>
			void addVar(Script & script, Type && var, const std::string & name);
			template<typename Type>
			void addVarConst(Script & script, const Type & var, const std::string & name);
			template<typename Type>
			void addVarGlobal(Script & script, Type && var, const std::string & name);
			template<typename Type>
			void addVarGlobalConst(Script & script, const Type & var, const std::string & name);
			template<typename Type>
			void addAttribute(Script & script, Type && attr, const std::string & name);

			template<typename Ctor>
			void addCtor(Script & script, const std::string & name);
			template<typename Class, typename Ret, typename ...Params>
			void addFun(Script & script, Ret(Class::* fun)(Params...), const std::string & name);
			template<typename Class, typename Ret, typename ...Params>
			void addFun(Script & script, Ret(Class::* fun)(Params...) const, const std::string & name);
			template<typename Ret, typename ...Params>
			void addFun(Script & script, Ret(*fun)(Params...), const std::string & name);

			// ...

			template<typename Ret, typename ...Params>
			Ret execute(const Script & script, const std::function<Ret(Params...)> & shell, const Params & ...params);
			template<typename ...Params>
			inline bool execute(const Script & script, const std::function<void(Params...)> & shell, const Params & ...params);
			inline bool execute(const Script & script, const std::function<void()> & shell) { return script.execute(shell); }
			inline bool execute(const Script & script, const std::string & code) { return script.execute(code); }

			template<typename Type>
			Type get(const Script & script, const std::string & expression, const Type& def = Type{});
		}
	}
}

template<typename Enum>
inline void logic::script::util::addEnum(Script & script, const std::string & name, const std::vector<std::pair<Enum, std::string>> & pairs)
{
	chaiscript::ModulePtr ptr = std::make_shared<chaiscript::Module>();
	chaiscript::utility::add_class<Enum>(*ptr, name, pairs);
	script.getHandle().add(ptr);
}
template<typename Type>
inline void logic::script::util::addType(Script & script, const std::string & name)
{
	script.getHandle().add(chaiscript::user_type<Type>(), name);
}
template<typename Parent, typename Child>
inline void logic::script::util::addRelation(Script & script)
{
	script.getHandle().add(chaiscript::base_class<Parent, Child>());
}

template<typename Type>
inline void logic::script::util::addVar(Script & script, Type && var, const std::string & name)
{
	script.getHandle().add(chaiscript::var(var), name);
}
template<typename Type>
inline void logic::script::util::addVarConst(Script & script, const Type & var, const std::string & name)
{
	script.getHandle().add(chaiscript::const_var(var), name);
}
template<typename Type>
inline void logic::script::util::addVarGlobal(Script & script, Type && var, const std::string & name)
{
	script.getHandle().add_global(chaiscript::var(var), name);
}
template<typename Type>
inline void logic::script::util::addVarGlobalConst(Script & script, const Type & var, const std::string & name)
{
	script.getHandle().add_global_const(chaiscript::const_var(var), name);
}
template<typename Type>
inline void logic::script::util::addAttribute(Script & script, Type && attr, const std::string & name)
{
	script.getHandle().add(chaiscript::fun(attr), name);
}

template<typename Ctor>
inline void logic::script::util::addCtor(Script & script, const std::string & name)
{
	script.getHandle().add(chaiscript::constructor<Ctor>(), name);
}
template<typename Class, typename Ret, typename ...Params>
inline void logic::script::util::addFun(Script & script, Ret(Class::* fun)(Params...), const std::string & name)
{
	script.getHandle().add(chaiscript::fun(fun), name);
}
template<typename Class, typename Ret, typename ...Params>
inline void logic::script::util::addFun(Script & script, Ret(Class::* fun)(Params...) const, const std::string & name)
{
	script.getHandle().add(chaiscript::fun(fun), name);
}
template<typename Ret, typename ...Params>
inline void logic::script::util::addFun(Script & script, Ret(* fun)(Params...), const std::string & name)
{
	script.getHandle().add(chaiscript::fun(fun), name);
}

template<typename Ret, typename ...Params>
Ret logic::script::util::execute(const Script & script, const std::function<Ret(Params...)> & shell, const Params & ...params)
{
	Ret returned{};
	execute(script, [&]() { returned = shell(params...); });
	return returned;
}
template<typename ...Params>
bool logic::script::util::execute(const Script & script, const std::function<void(Params...)> & shell, const Params & ...params)
{
	return execute(script, [&]() { shell(params...); });
}

template<typename Type>
Type logic::script::util::get(const Script & script, const std::string & expression, const Type & def)
{
	try
	{
		return script.getHandle().eval<Type>(expression);
	}
	catch (const std::exception &)
	{
		return def;
	}
}
