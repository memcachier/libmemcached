#include "common.h"

/*
  This closes all connections (forces flush of input as well).
  
  Maybe add a host specific, or key specific version? 
  
  The reason we send "quit" is that in case we have buffered IO, this 
  will force data to be completed.
*/

void memcached_quit_server(memcached_st *ptr, unsigned int server_key)
{
  if (ptr->hosts == NULL || 
      ptr->number_of_hosts == 0 ||
      server_key > ptr->number_of_hosts)
    return;

  if (ptr->hosts[server_key].fd != -1)
  {
    if (ptr->flags & MEM_NO_BLOCK && ptr->hosts[server_key].stack_responses)
      memcached_io_flush(ptr, server_key);

    memcached_io_write(ptr, server_key, "quit\r\n", 6, 1);

    close(ptr->hosts[server_key].fd);
    ptr->hosts[server_key].fd= -1;
    ptr->hosts[server_key].stack_responses= 0;
    ptr->hosts[server_key].cursor_active= 0;
    ptr->hosts[server_key].write_buffer_offset= 0;
    ptr->hosts[server_key].read_buffer_length= 0;
    ptr->hosts[server_key].read_ptr= ptr->hosts[server_key].read_buffer;
    ptr->hosts[server_key].write_ptr= ptr->hosts[server_key].write_buffer;
  }

  ptr->connected--;
}

void memcached_quit(memcached_st *ptr)
{
  unsigned int x;

  if (ptr->hosts && ptr->number_of_hosts)
  {
    for (x= 0; x < ptr->number_of_hosts; x++)
      memcached_quit_server(ptr, x);
  }

  ptr->connected= 0;
}
