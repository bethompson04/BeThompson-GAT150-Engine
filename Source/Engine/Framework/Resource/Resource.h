#pragma once
#include <string>
#include <memory>

namespace MEN
{
	class Resource
	{
	public:
		virtual ~Resource() = default;

		virtual bool Create(std::string fileName, ...) = 0;

	private:
	};

	template<typename T>
	using res_t = std::shared_ptr<T>;
}