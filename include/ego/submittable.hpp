#ifndef EGO_SUBMITTABLE
#define EGO_SUBMITTABLE
#include <array>
#include <cstddef> // std::size_t
#include <vector>

namespace Ego
{

template<typename T>
class Submittable
{
public:
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
protected:
	inline ~Submittable() = default;
};

} // namespace Ego

#endif // EGO_SUBMITTABLE
