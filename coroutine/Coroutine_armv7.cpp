//
//  Coroutine_armv7.cpp
//  coroutine
//
//  Created by Marcin Świderski on 8/9/12.
//  Copyright (c) 2012 Marcin Świderski. All rights reserved.
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

#include "Coroutine.h"

#ifdef COROUTINE_ARMV7

Coroutine::Coroutine()
	: _stateFlags(0)
	, _stack(new uint8_t[COROUTINE_STACK_SIZE])
	, _stackBase(_stack + COROUTINE_STACK_SIZE) {}

Coroutine::~Coroutine() {
	delete [] _stack;
}

#endif // COROUTINE_ARMV7