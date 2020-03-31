#ifndef DRAWING_SUBMITTABLE
#define DRAWING_SUBMITTABLE
#include <array>
#include <cstddef> // std::size_t
#include <vector>

namespace Drawing
{

template<typename T>
class Submittable
{
public:
	using ValueType = T;
	
	virtual void Submit(const T* data, std::size_t length) = 0;
	
	template<std::size_t Length>
	inline void Submit(const T(&data)[Length])
	{
		Submit(data, Length);
	}
	
	template<std::size_t Length>
	inline void Submit(const std::array<T, Length>& array)
	{
		Submit(array.data(), Length);
	}
	
	inline void Submit(const std::vector<T>& vec)
	{
		Submit(vec.data(), vec.size());
	}
};

} // namespace Drawing

#endif // DRAWING_SUBMITTABLE
