#pragma once

#include <vector>
#include <stdexcept>
#include <net/inet_common.hpp>

namespace net{
    
  /** Network buffer storage for uniformely sized buffers. 
      @note : The buffer store is intended to be used by Packet, which is a semi-intelligent buffer wrapper, used throughout the IP-stack. There shouldn't be any need for raw buffers in services.  **/
  class BufferStore {
    size_t bufcount_ = INITIAL_BUFCOUNT;
    const size_t bufsize_ = MTUSIZE;
    size_t offset_ = 0;
    buffer pool_ = 0;
    std::vector<buffer> available_buffers_;    

  public:
    
    using release_del = delegate<void(net::buffer, size_t)>;
    
    BufferStore(BufferStore& cpy) = delete;
    BufferStore(BufferStore&& cpy) = delete;
    BufferStore& operator=(BufferStore& cpy) = delete;
    BufferStore operator=(BufferStore&& mv) = delete;
    BufferStore() = delete;
    
    inline size_t bufsize(){ return bufsize_; }
    
    /** Free all the buffers **/
    ~BufferStore();
  
    BufferStore(int num, size_t bufsize, size_t offset);
  
    /** Get a free buffer */
    buffer get();
  
    /** Return a buffer. */
    void release(buffer b, size_t);
    
    /** Return a buffer, offset by offset_ bytes from actual buffer. */
    void release_offset(buffer b, size_t);
    
    
    /** Check if a buffer belongs here */
    inline bool address_is_from_pool(buffer addr)
    { return addr >= pool_ and addr < pool_ + (bufcount_ * bufsize_); }
    
    /** Check if an address is the start of a buffer */
    inline bool address_is_bufstart(buffer addr)
    { return (addr - pool_) % bufsize_ == 0; }
    
    /** Check if an address is the start of a buffer */
    inline bool address_is_offset_bufstart(buffer addr)
    { return (addr - pool_ - offset_) % bufsize_ == 0; }

    		
  private:
    
    void increaseStorage();

    
  };
  

}
