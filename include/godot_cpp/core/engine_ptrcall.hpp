/**************************************************************************/
/*  engine_ptrcall.hpp                                                    */
/**************************************************************************/
/*                         This file is part of:                          */
/*                             GODOT ENGINE                               */
/*                        https://godotengine.org                         */
/**************************************************************************/
/* Copyright (c) 2014-present Godot Engine contributors (see AUTHORS.md). */
/* Copyright (c) 2007-2014 Juan Linietsky, Ariel Manzur.                  */
/*                                                                        */
/* Permission is hereby granted, free of charge, to any person obtaining  */
/* a copy of this software and associated documentation files (the        */
/* "Software"), to deal in the Software without restriction, including    */
/* without limitation the rights to use, copy, modify, merge, publish,    */
/* distribute, sublicense, and/or sell copies of the Software, and to     */
/* permit persons to whom the Software is furnished to do so, subject to  */
/* the following conditions:                                              */
/*                                                                        */
/* The above copyright notice and this permission notice shall be         */
/* included in all copies or substantial portions of the Software.        */
/*                                                                        */
/* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,        */
/* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF     */
/* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. */
/* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY   */
/* CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,   */
/* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE      */
/* SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                 */
/**************************************************************************/

#ifndef GODOT_ENGINE_PTRCALL_HPP
#define GODOT_ENGINE_PTRCALL_HPP

#include <gdextension_interface.h>

#include <godot_cpp/core/binder_common.hpp>
#include <godot_cpp/core/object.hpp>
#include <godot_cpp/godot.hpp>

#include <array>

namespace godot {

namespace internal {

template <class O, class... Args>
O *_call_native_mb_ret_obj(const GDExtensionMethodBindPtr mb, void *instance, const Args &...args) {
	GodotObject *ret = nullptr;
	std::array<GDExtensionConstTypePtr, sizeof...(Args)> mb_args = { { (GDExtensionConstTypePtr)args... } };
	internal::gdextension_interface_object_method_bind_ptrcall(mb, instance, mb_args.data(), &ret);
	if (ret == nullptr) {
		return nullptr;
	}
	return reinterpret_cast<O *>(internal::gdextension_interface_object_get_instance_binding(ret, internal::token, &O::___binding_callbacks));
}

template <class R, class... Args>
R _call_native_mb_ret(const GDExtensionMethodBindPtr mb, void *instance, const Args &...args) {
	R ret;
	std::array<GDExtensionConstTypePtr, sizeof...(Args)> mb_args = { { (GDExtensionConstTypePtr)args... } };
	internal::gdextension_interface_object_method_bind_ptrcall(mb, instance, mb_args.data(), &ret);
	return ret;
}

template <class... Args>
void _call_native_mb_no_ret(const GDExtensionMethodBindPtr mb, void *instance, const Args &...args) {
	std::array<GDExtensionConstTypePtr, sizeof...(Args)> mb_args = { { (GDExtensionConstTypePtr)args... } };
	internal::gdextension_interface_object_method_bind_ptrcall(mb, instance, mb_args.data(), nullptr);
}

template <class R, class... Args>
R _call_utility_ret(GDExtensionPtrUtilityFunction func, const Args &...args) {
	R ret;
	std::array<GDExtensionConstTypePtr, sizeof...(Args)> mb_args = { { (GDExtensionConstTypePtr)args... } };
	func(&ret, mb_args.data(), mb_args.size());
	return ret;
}

template <class... Args>
Object *_call_utility_ret_obj(const GDExtensionPtrUtilityFunction func, void *instance, const Args &...args) {
	GodotObject *ret = nullptr;
	std::array<GDExtensionConstTypePtr, sizeof...(Args)> mb_args = { { (GDExtensionConstTypePtr)args... } };
	func(&ret, mb_args.data(), mb_args.size());
	return (Object *)internal::gdextension_interface_object_get_instance_binding(ret, internal::token, &Object::___binding_callbacks);
}

template <class... Args>
void _call_utility_no_ret(const GDExtensionPtrUtilityFunction func, const Args &...args) {
	std::array<GDExtensionConstTypePtr, sizeof...(Args)> mb_args = { { (GDExtensionConstTypePtr)args... } };
	func(nullptr, mb_args.data(), mb_args.size());
}

} // namespace internal

} // namespace godot

#endif // GODOT_ENGINE_PTRCALL_HPP
