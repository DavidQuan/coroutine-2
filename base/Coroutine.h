//
//  Coroutine.h
//  coroutine
//
//  Created by Marcin Świderski on 8/9/12.
//  Copyright (c) 2012 Marcin Świderski.
//
//  This software is provided 'as-is', without any express or implied
//  warranty.  In no event will the authors be held liable for any damages
//  arising from the use of this software.
//  
//  Permission is granted to anyone to use this software for any purpose,
//  including commercial applications, and to alter it and redistribute it
//  freely, subject to the following restrictions:
//  
//  1. The origin of this software must not be misrepresented; you must not
//     claim that you wrote the original software. If you use this software
//     in a product, an acknowledgment in the product documentation would be
//     appreciated but is not required.
//  2. Altered source versions must be plainly marked as such, and must not be
//     misrepresented as being the original software.
//  3. This notice may not be removed or altered from any source distribution.
//

#ifndef coroutine_Coroutine_h
#define coroutine_Coroutine_h

#if defined(__i386__)
#define COROUTINE_I386

#elif defined(__x86_64__)
#define COROUTINE_X86_64
#define COROUTINE_64BIT

#elif defined(__arm__)
#define COROUTINE_ARMV7

#else
#error "Coroutine: architecture not supported!!!"

#endif

#ifndef COROUTINE_64BIT

#define COROUTINE_STACK_SIZE			4096

#define COROUTINE_OFFSET_STATEFLAGS		4
#define COROUTINE_OFFSET_STACK			8
#define COROUTINE_OFFSET_STACKBASE		12
#define COROUTINE_OFFSET_STACKPOINTER	16

#define COROUTINE_VTABLE_RUN			8

#else

#define COROUTINE_STACK_SIZE			8192

#define COROUTINE_OFFSET_STATEFLAGS		8
#define COROUTINE_OFFSET_STACK			16
#define COROUTINE_OFFSET_STACKBASE		24
#define COROUTINE_OFFSET_STACKPOINTER	32

#define COROUTINE_VTABLE_RUN			16

#endif

#if DEBUG
#define COROUTINE_SAFE					1
#define COROUTINE_ON_OUT_OF_BOUNDS()	assert(false && "Coroutine exceeded its stack!!!");
#endif

#ifndef COROUTINE_ASM

#include <cstddef>
#include <cassert>
#include <stdint.h>

class Coroutine {
	enum {
		StateStarted	= 0x1,
		StateFinished	= 0x2,
		StackOwned		= 0x4
	};

	unsigned long	_flags;
	uint8_t*		_stack;				// Heap allocated stack for coroutine.
	uint8_t*		_stackBase;			// Pointer to base of the coroutine stack.
	uint8_t*		_stackPointer;		// Coroutine stack pointer.
	
	// Architecture defined stack aligning.
	void alignStackBase();

public:
	Coroutine();
	Coroutine(uint8_t* stack, uint8_t* stackBase, bool deleteStack = false);
	virtual ~Coroutine();
	
	int operator()();
	
	bool didFinish() const { return _flags & StateFinished; }
	bool isStackOwned() const { return _flags & StackOwned; }
	
	uint8_t* getStack() const { return _stack; }
	uint8_t* getStackBase() const { return _stackBase; }
	uint8_t* getStackPointer() const { return _stackPointer; }

#if COROUTINE_SAFE

	size_t estimateUsedStackSize() const;
	
#endif

protected:
	virtual int run() = 0;
	
	void yield(int ret);

#if COROUTINE_SAFE

	void validate() const;
	
#endif
};

#endif // COROUTINE_ASM

#endif
