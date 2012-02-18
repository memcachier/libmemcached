/*  vim:expandtab:shiftwidth=2:tabstop=2:smarttab:
 * 
 *  LibMemcached
 *
 *  Copyright (C) 2011 Data Differential, http://datadifferential.com/
 *  All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions are
 *  met:
 *
 *      * Redistributions of source code must retain the above copyright
 *  notice, this list of conditions and the following disclaimer.
 *
 *      * Redistributions in binary form must reproduce the above
 *  copyright notice, this list of conditions and the following disclaimer
 *  in the documentation and/or other materials provided with the
 *  distribution.
 *
 *      * The names of its contributors may not be used to endorse or
 *  promote products derived from this software without specific prior
 *  written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#pragma once

/* These are private */ 
#define memcached_is_allocated(__object) ((__object)->options.is_allocated)
#define memcached_is_udp(__object) ((__object)->flags.use_udp)
#define memcached_is_verify_key(__object) ((__object)->flags.verify_key)
#define memcached_is_binary(__object) ((__object)->flags.binary_protocol)
#define memcached_is_initialized(__object) ((__object)->options.is_initialized)
#define memcached_is_purging(__object) ((__object)->state.is_purging)
#define memcached_is_processing_input(__object) ((__object)->state.is_processing_input)

#define memcached_is_buffering(__object) ((__object)->flags.buffer_requests)
#define memcached_is_replying(__object) ((__object)->flags.reply)

#define memcached_has_error(__object) ((__object)->error_messages)

#define memcached_has_replicas(__object) ((__object)->root->number_of_replicas)

#define memcached_set_purging(__object, __value) ((__object)->state.is_purging= (__value))
#define memcached_set_processing_input(__object, __value) ((__object)->state.is_processing_input= (__value))
#define memcached_set_initialized(__object, __value) ((__object)->options.is_initialized(= (__value))
#define memcached_set_allocated(__object, __value) ((__object)->options.is_allocated= (__value))
