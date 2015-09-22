#pragma once
#include <cstdlib>
namespace stormrider
{
namespace vamp
{

class PluginInputBuffer
{
private:
	typedef int IndexType;
public:
	PluginInputBuffer();
	PluginInputBuffer(IndexType channels, IndexType block_size);
	~PluginInputBuffer();
	float** GetBuffer() const;
	void SetValue(const int channel, const IndexType index, float value);
	float* GetPointer(const IndexType channel, const IndexType block_index);
private:
	IndexType channels_;
	IndexType block_size_;
	float** buffer_;
};

} // namespace vamp
} // namespace stormrider
