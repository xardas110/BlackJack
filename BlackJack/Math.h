#pragma once
namespace Math
{ 
	template<typename T>
	inline T Abs(T val)
	{
		val < 0 ? val *= -1 : 0;
		return val;
	};
	template<typename T>
	inline T Max(T val1, T val2)
	{
		T result;
		val1 > val2 ? result = val1 : result = val2;
		return result;
	}
	template<typename T>
	inline T Min(T val1, T val2)
	{
		T result;
		val1 < val2 ? result = val1 : result = val2;
		return result;
	}
}