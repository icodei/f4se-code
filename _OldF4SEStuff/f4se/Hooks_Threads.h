#pragma once
#include "f4se/GameThreads.h"

#include <functional>

void Hooks_Threads_Init(void);
void Hooks_Threads_Commit(void);

namespace TaskInterface {
//private:
	/*
	decltype(auto) GetProxy() const noexcept {
		return reinterpret_cast<const F4SETaskInterface&>(*this);
	}
	*/

	class TaskDelegate : public ITaskDelegate {
	public:
		explicit TaskDelegate(std::function<void()> a_task) noexcept : _impl(std::move(a_task)) {}

		void Run() override { _impl(); }

	private:
		std::function<void()> _impl;
	};

//public:
	void AddTask(ITaskDelegate* task);
	void AddTaskFunc(std::function<void()> a_task);
	void AddUITask(ITaskDelegate* task);
	void AddUITaskFunc(std::function<void()> a_task);
};
