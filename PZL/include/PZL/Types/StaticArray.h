#pragma once

#include "PZL/Types/Object.h"

namespace PZL::Type
{

	template<typename T, size_t S>
	struct StaticArray : public Object
	{
	public:
		StaticArray(const std::initializer_list<T>& List)
		{
			size_t Index = 0;
			for (auto Item : List)
			{
				Data[Index] = std::move(Item);
				Index++;
			}

			Type = ObjectType::StaticArray;
		}

		StaticArray() : Data(0)
		{
			Type = ObjectType::StaticArray;
		}

		~StaticArray()
		{
		}

		T& operator[](size_t Index)
		{
			return Data[Index];
		}

		T& operator[](size_t Index) const
		{
			return Data[Index];
		}

	public:
		T Data[S];
	};
}