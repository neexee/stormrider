#include "PluginInputBuffer.h"

namespace stormrider
{
namespace vamp
{

PluginInputBuffer::PluginInputBuffer()
: channels_(0)
, block_size_(0)
, buffer_(nullptr)
{
}

PluginInputBuffer::PluginInputBuffer(IndexType channels, IndexType block_size)
: channels_(channels)
, block_size_(block_size)
{
	buffer_ = new float*[channels];
	for (int c = 0; c < channels; ++c)
	{
		buffer_[c] = new float[block_size_ + 2];
	}
}

PluginInputBuffer::~PluginInputBuffer()
{
	for (int i = 0; i < channels_; ++i)
	{
		delete [] buffer_[i];
	}
	delete [] buffer_;
}

float** PluginInputBuffer::GetBuffer() const
{
	return buffer_;
}

void PluginInputBuffer::SetValue(const IndexType channel, const IndexType index, float value)
{
	buffer_[channel][index] = value;
}

float* PluginInputBuffer::GetPointer(const IndexType channel, const IndexType block_index)
{
	return &buffer_[channel][block_index];
}

} // namespace vamp
} // namespace stormrider
