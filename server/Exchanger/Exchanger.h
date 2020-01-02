#pragma once

#include "Core.h"

namespace ServWork
{
	class Exchanger
	{
	public:
		Exchanger() = default;

		Exchanger(const Exchanger&) = delete;
		Exchanger(Exchanger&&) = default;

		Exchanger& operator=(const Exchanger&) = delete;
		Exchanger& operator=(Exchanger&&) = default;

		virtual ~Exchanger() { Deallocate(); }

		void Allocate(size_t size);
		void Deallocate() noexcept;

		inline size_t GetTotalSize() const noexcept { return maxSize; }
		inline size_t GetCurSize() const noexcept { return curSize; }
	
		double GetPercent() const;

	protected:
		char* data;
		size_t maxSize;
		size_t curSize;
	};
}