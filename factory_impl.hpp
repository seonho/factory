/**
 *	@file		factory_impl.hpp
 *	@brief		Factory implementation macro
 *	@author		seonho.oh@gmail.com
 *	@date		2013-06-10
 *	@version	1.0
 *
 *	@section	LICENSE
 *
 *		Copyright (c) 2007-2014, Seonho Oh
 *		All rights reserved. 
 * 
 *		Redistribution and use in source and binary forms, with or without  
 *		modification, are permitted provided that the following conditions are  
 *		met: 
 * 
 *		    * Redistributions of source code must retain the above copyright  
 *		    notice, this list of conditions and the following disclaimer. 
 *		    * Redistributions in binary form must reproduce the above copyright  
 *		    notice, this list of conditions and the following disclaimer in the  
 *		    documentation and/or other materials provided with the distribution. 
 *		    * Neither the name of the <ORGANIZATION> nor the names of its  
 *		    contributors may be used to endorse or promote products derived from  
 *		    this software without specific prior written permission. 
 * 
 *		THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS  
 *		IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED  
 *		TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A  
 *		PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER  
 *		OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,  
 *		EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,  
 *		PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR  
 *		PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF  
 *		LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING  
 *		NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS  
 *		SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. 
 */
#pragma once

#include <string>
#include <map>

#define DO_REGISTER(e) \
	registry_[#e] = &templated_creator<##e>::create;

//! Macro function that defines factory class.
#define FACTORY_IMPL(factoryname, producttype, products)	\
class factoryname											\
{															\
	typedef producttype* (*creator)();						\
	template <typename Derived_, typename Base_ = producttype> \
	class templated_creator									\
	{														\
	public:													\
		static Base_* create() { return new Derived_(); }	\
	};														\
public:														\
	factoryname()											\
	{														\
		products(DO_REGISTER)								\
	}														\
	inline producttype* create(const std::string& name)		\
	{														\
		auto itr = registry_.find(name);					\
		if (itr != registry_.end())							\
			return itr->second();							\
		return nullptr;										\
	}														\
	inline bool exist(const std::string& name)				\
	{														\
		return registry_.find(name) != registry_.end();		\
	}														\
private:													\
	std::map<std::string, creator>	registry_;				\
}