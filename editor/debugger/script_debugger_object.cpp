/*************************************************************************/
/*  script_debugger_object.cpp                                           */
/*************************************************************************/
/*                       This file is part of:                           */
/*                           GODOT ENGINE                                */
/*                      https://godotengine.org                          */
/*************************************************************************/
/* Copyright (c) 2007-2022 Juan Linietsky, Ariel Manzur.                 */
/* Copyright (c) 2014-2022 Godot Engine contributors (cf. AUTHORS.md).   */
/*                                                                       */
/* Permission is hereby granted, free of charge, to any person obtaining */
/* a copy of this software and associated documentation files (the       */
/* "Software"), to deal in the Software without restriction, including   */
/* without limitation the rights to use, copy, modify, merge, publish,   */
/* distribute, sublicense, and/or sell copies of the Software, and to    */
/* permit persons to whom the Software is furnished to do so, subject to */
/* the following conditions:                                             */
/*                                                                       */
/* The above copyright notice and this permission notice shall be        */
/* included in all copies or substantial portions of the Software.       */
/*                                                                       */
/* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,       */
/* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF    */
/* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.*/
/* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY  */
/* CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,  */
/* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE     */
/* SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                */
/*************************************************************************/

#include "script_debugger_object.h"

void ScriptDebuggerObject::_bind_methods() {
	ADD_SIGNAL(MethodInfo("clear_execution", PropertyInfo(Variant::OBJECT, "script", PROPERTY_HINT_RESOURCE_TYPE, "Script")));

	// Signals that potentially introduce new threads.
	ADD_SIGNAL(MethodInfo("thread_breaked",
			PropertyInfo(Variant::PACKED_BYTE_ARRAY, "debug_thread_id"),
			PropertyInfo(Variant::BOOL, "is_main_thread"),
			PropertyInfo(Variant::STRING, "reason"),
			PropertyInfo(Variant::INT, "severity_code"),
			PropertyInfo(Variant::BOOL, "can_debug")));
	ADD_SIGNAL(MethodInfo("thread_paused",
			PropertyInfo(Variant::PACKED_BYTE_ARRAY, "debug_thread_id"),
			PropertyInfo(Variant::BOOL, "is_main_thread")));
	ADD_SIGNAL(MethodInfo("thread_alert",
			PropertyInfo(Variant::PACKED_BYTE_ARRAY, "debug_thread_id"),
			PropertyInfo(Variant::BOOL, "is_main_thread"),
			PropertyInfo(Variant::STRING, "reason"),
			PropertyInfo(Variant::INT, "severity_code"),
			PropertyInfo(Variant::BOOL, "can_debug"),
			PropertyInfo(Variant::BOOL, "has_stack_dump")));

	// Signals referring to threads already known.
	ADD_SIGNAL(MethodInfo("thread_continued", PropertyInfo(Variant::PACKED_BYTE_ARRAY, "debug_thread_id")));
	ADD_SIGNAL(MethodInfo("thread_exited", PropertyInfo(Variant::PACKED_BYTE_ARRAY, "debug_thread_id")));
	ADD_SIGNAL(MethodInfo("thread_stack_dump", PropertyInfo(Variant::PACKED_BYTE_ARRAY, "debug_thread_id"), PropertyInfo(Variant::ARRAY, "stack_dump")));
	ADD_SIGNAL(MethodInfo("thread_stack_frame_vars", PropertyInfo(Variant::PACKED_BYTE_ARRAY, "debug_thread_id"), PropertyInfo(Variant::INT, "num_vars")));
	ADD_SIGNAL(MethodInfo("thread_stack_frame_var", PropertyInfo(Variant::PACKED_BYTE_ARRAY, "debug_thread_id"), PropertyInfo(Variant::ARRAY, "data")));
	ADD_SIGNAL(MethodInfo("thread_info",
			PropertyInfo(Variant::PACKED_BYTE_ARRAY, "debug_thread_id"),
			PropertyInfo(Variant::STRING, "language"),
			// Debug thread contexts that have the same value here are from the same thread, but for different language.
			// This is not guaranteed to be a real OS thread ID (even though it will be for core languages.)
			PropertyInfo(Variant::PACKED_BYTE_ARRAY, "thread_tag"),
			PropertyInfo(Variant::STRING, "name")));
}
