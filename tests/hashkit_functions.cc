/*  vim:expandtab:shiftwidth=2:tabstop=2:smarttab:
 * 
 *  libHashKit Functions Test
 *
 *  Copyright (C) 2011 Data Differential, http://datadifferential.com/
 *  Copyright (C) 2006-2009 Brian Aker All rights reserved.
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

#include <config.h>
#include <libtest/test.hpp>

using namespace libtest;

#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <libhashkit/hashkit.h>

#include "hash_results.h"

static hashkit_st global_hashk;

/**
  @brief hash_test_st is a structure we use in testing. It is currently empty.
*/
typedef struct hash_test_st hash_test_st;

struct hash_test_st
{
  bool _unused;
};

static test_return_t init_test(void *not_used)
{
  hashkit_st hashk;
  hashkit_st *hashk_ptr;
  (void)not_used;

  hashk_ptr= hashkit_create(&hashk);
  test_true(hashk_ptr);
  test_true(hashk_ptr == &hashk);
  test_true(hashkit_is_allocated(hashk_ptr) == false);

  hashkit_free(hashk_ptr);

  return TEST_SUCCESS;
}

static test_return_t allocation_test(void *not_used)
{
  hashkit_st *hashk_ptr;
  (void)not_used;

  hashk_ptr= hashkit_create(NULL);
  test_true(hashk_ptr);
  test_true(hashkit_is_allocated(hashk_ptr) == true);
  hashkit_free(hashk_ptr);

  return TEST_SUCCESS;
}

static test_return_t clone_test(hashkit_st *hashk)
{
  // First we make sure that the testing system is giving us what we expect.
  assert(&global_hashk == hashk);

  // Second we test if hashk is even valid

  /* All null? */
  {
    hashkit_st *hashk_ptr;
    hashk_ptr= hashkit_clone(NULL, NULL);
    test_true(hashk_ptr);
    test_true(hashkit_is_allocated(hashk_ptr));
    hashkit_free(hashk_ptr);
  }

  /* Can we init from null? */
  {
    hashkit_st *hashk_ptr;

    hashk_ptr= hashkit_clone(NULL, hashk);

    test_true(hashk_ptr);
    test_true(hashkit_is_allocated(hashk_ptr));

    hashkit_free(hashk_ptr);
  }

  /* Can we init from struct? */
  {
    hashkit_st declared_clone;
    hashkit_st *hash_clone;

    hash_clone= hashkit_clone(&declared_clone, NULL);
    test_true(hash_clone);
    test_true(hash_clone == &declared_clone);
    test_false(hashkit_is_allocated(hash_clone));

    hashkit_free(hash_clone);
  }

  /* Can we init from struct? */
  {
    hashkit_st declared_clone;
    hashkit_st *hash_clone;

    hash_clone= hashkit_clone(&declared_clone, hashk);
    test_true(hash_clone);
    test_true(hash_clone == &declared_clone);
    test_false(hashkit_is_allocated(hash_clone));

    hashkit_free(hash_clone);
  }

  return TEST_SUCCESS;
}

static test_return_t one_at_a_time_run (hashkit_st *hashk)
{
  uint32_t x;
  const char **ptr;
  (void)hashk;

  for (ptr= list_to_hash, x= 0; *ptr; ptr++, x++)
  {
    uint32_t hash_val;

    hash_val= libhashkit_one_at_a_time(*ptr, strlen(*ptr));
    test_true(one_at_a_time_values[x] == hash_val);
  }

  return TEST_SUCCESS;
}

static test_return_t md5_run (hashkit_st *hashk)
{
  uint32_t x;
  const char **ptr;
  (void)hashk;

  for (ptr= list_to_hash, x= 0; *ptr; ptr++, x++)
  {
    uint32_t hash_val;

    hash_val= libhashkit_md5(*ptr, strlen(*ptr));
    test_true(md5_values[x] == hash_val);
  }

  return TEST_SUCCESS;
}

static test_return_t crc_run (hashkit_st *hashk)
{
  uint32_t x;
  const char **ptr;
  (void)hashk;

  for (ptr= list_to_hash, x= 0; *ptr; ptr++, x++)
  {
    uint32_t hash_val;

    hash_val= libhashkit_crc32(*ptr, strlen(*ptr));
    assert(crc_values[x] == hash_val);
  }

  return TEST_SUCCESS;
}

static test_return_t fnv1_64_run (hashkit_st *hashk)
{
  uint32_t x;
  const char **ptr;
  (void)hashk;

  for (ptr= list_to_hash, x= 0; *ptr; ptr++, x++)
  {
    uint32_t hash_val;

    hash_val= libhashkit_fnv1_64(*ptr, strlen(*ptr));
    assert(fnv1_64_values[x] == hash_val);
  }

  return TEST_SUCCESS;
}

static test_return_t fnv1a_64_run (hashkit_st *hashk)
{
  uint32_t x;
  const char **ptr;
  (void)hashk;

  for (ptr= list_to_hash, x= 0; *ptr; ptr++, x++)
  {
    uint32_t hash_val;

    hash_val= libhashkit_fnv1a_64(*ptr, strlen(*ptr));
    assert(fnv1a_64_values[x] == hash_val);
  }

  return TEST_SUCCESS;
}

static test_return_t fnv1_32_run (hashkit_st *hashk)
{
  uint32_t x;
  const char **ptr;
  (void)hashk;

  for (ptr= list_to_hash, x= 0; *ptr; ptr++, x++)
  {
    uint32_t hash_val;

    hash_val= libhashkit_fnv1_32(*ptr, strlen(*ptr));
    assert(fnv1_32_values[x] == hash_val);
  }

  return TEST_SUCCESS;
}

static test_return_t fnv1a_32_run (hashkit_st *hashk)
{
  uint32_t x;
  const char **ptr;
  (void)hashk;

  for (ptr= list_to_hash, x= 0; *ptr; ptr++, x++)
  {
    uint32_t hash_val;

    hash_val= libhashkit_fnv1a_32(*ptr, strlen(*ptr));
    assert(fnv1a_32_values[x] == hash_val);
  }

  return TEST_SUCCESS;
}

static test_return_t hsieh_run (hashkit_st *hashk)
{
  uint32_t x;
  const char **ptr;
  (void)hashk;

  for (ptr= list_to_hash, x= 0; *ptr; ptr++, x++)
  {
    uint32_t hash_val;

#ifdef HAVE_HSIEH_HASH
    hash_val= libhashkit_hsieh(*ptr, strlen(*ptr));
#else
    hash_val= 1;
#endif
    assert(hsieh_values[x] == hash_val);
  }

  return TEST_SUCCESS;
}

static test_return_t murmur_run (hashkit_st *hashk)
{
  (void)hashk;

#ifdef WORDS_BIGENDIAN
  (void)murmur_values;
  return TEST_SKIPPED;
#else
  uint32_t x;
  const char **ptr;

  for (ptr= list_to_hash, x= 0; *ptr; ptr++, x++)
  {
    uint32_t hash_val;

#ifdef HAVE_MURMUR_HASH
    hash_val= libhashkit_murmur(*ptr, strlen(*ptr));
#else
    hash_val= 1;
#endif
    assert(murmur_values[x] == hash_val);
  }

  return TEST_SUCCESS;
#endif
}

static test_return_t jenkins_run (hashkit_st *hashk)
{
  uint32_t x;
  const char **ptr;
  (void)hashk;

  for (ptr= list_to_hash, x= 0; *ptr; ptr++, x++)
  {
    uint32_t hash_val;

    hash_val= libhashkit_jenkins(*ptr, strlen(*ptr));
    assert(jenkins_values[x] == hash_val);
  }

  return TEST_SUCCESS;
}




/**
  @brief now we list out the tests.
*/

test_st allocation[]= {
  {"init", 0, (test_callback_fn*)init_test},
  {"create and free", 0, (test_callback_fn*)allocation_test},
  {"clone", 0, (test_callback_fn*)clone_test},
  {0, 0, 0}
};

static test_return_t hashkit_digest_test(hashkit_st *hashk)
{
  uint32_t value;
  value= hashkit_digest(hashk, "a", sizeof("a"));

  return TEST_SUCCESS;
}

static test_return_t hashkit_set_function_test(hashkit_st *hashk)
{
  for (int algo= int(HASHKIT_HASH_DEFAULT); algo < int(HASHKIT_HASH_MAX); algo++)
  {
    uint32_t x;
    const char **ptr;
    uint32_t *list;

    hashkit_return_t rc= hashkit_set_function(hashk, static_cast<hashkit_hash_algorithm_t>(algo));

    /* Hsieh is disabled most of the time for patent issues */
#ifndef HAVE_HSIEH_HASH
    if (rc == HASHKIT_FAILURE && algo == HASHKIT_HASH_HSIEH)
      continue;
#endif

#ifndef HAVE_MURMUR_HASH
    if (rc == HASHKIT_FAILURE && algo == HASHKIT_HASH_MURMUR)
      continue;
#endif

    if (rc == HASHKIT_INVALID_ARGUMENT && algo == HASHKIT_HASH_CUSTOM)
      continue;

    test_true_got(rc == HASHKIT_SUCCESS, hashkit_strerror(NULL, rc));

    switch (algo)
    {
    case HASHKIT_HASH_DEFAULT:
      list= one_at_a_time_values;
      break;
    case HASHKIT_HASH_MD5:
      list= md5_values;
      break;
    case HASHKIT_HASH_CRC:
      list= crc_values;
      break;
    case HASHKIT_HASH_FNV1_64:
      list= fnv1_64_values;
      break;
    case HASHKIT_HASH_FNV1A_64:
      list= fnv1a_64_values;
      break;
    case HASHKIT_HASH_FNV1_32:
      list= fnv1_32_values;
      break;
    case HASHKIT_HASH_FNV1A_32:
      list= fnv1a_32_values;
      break;
    case HASHKIT_HASH_HSIEH:
      list= hsieh_values;
      break;
    case HASHKIT_HASH_MURMUR:
      list= murmur_values;
      break;
    case HASHKIT_HASH_JENKINS:
      list= jenkins_values;
      break;
    case HASHKIT_HASH_CUSTOM:
    case HASHKIT_HASH_MAX:
    default:
      list= NULL;
      break;
    }

    // Now we make sure we did set the hash correctly.
    if (list)
    {
      for (ptr= list_to_hash, x= 0; *ptr; ptr++, x++)
      {
        uint32_t hash_val;

        hash_val= hashkit_digest(hashk, *ptr, strlen(*ptr));
        test_true(list[x] == hash_val);
      }
    }
    else
    {
      return TEST_FAILURE;
    }
  }

  return TEST_SUCCESS;
}

static uint32_t hash_test_function(const char *string, size_t string_length, void *context)
{
  (void)context;
  return libhashkit_md5(string, string_length);
}

static test_return_t hashkit_set_custom_function_test(hashkit_st *hashk)
{
  hashkit_return_t rc;
  uint32_t x;
  const char **ptr;


  rc= hashkit_set_custom_function(hashk, hash_test_function, NULL);
  test_true(rc == HASHKIT_SUCCESS);

  for (ptr= list_to_hash, x= 0; *ptr; ptr++, x++)
  {
    uint32_t hash_val;

    hash_val= hashkit_digest(hashk, *ptr, strlen(*ptr));
    test_true(md5_values[x] == hash_val);
  }

  return TEST_SUCCESS;
}

static test_return_t hashkit_set_distribution_function_test(hashkit_st *hashk)
{
  for (int algo= int(HASHKIT_HASH_DEFAULT); algo < int(HASHKIT_HASH_MAX); algo++)
  {
    hashkit_return_t rc= hashkit_set_distribution_function(hashk, static_cast<hashkit_hash_algorithm_t>(algo));

    /* Hsieh is disabled most of the time for patent issues */
    if (rc == HASHKIT_FAILURE && algo == HASHKIT_HASH_HSIEH)
      continue;

    if (rc == HASHKIT_INVALID_ARGUMENT && algo == HASHKIT_HASH_CUSTOM)
      continue;

    test_true(rc == HASHKIT_SUCCESS);
  }

  return TEST_SUCCESS;
}

static test_return_t hashkit_set_custom_distribution_function_test(hashkit_st *hashk)
{
  hashkit_return_t rc= hashkit_set_custom_distribution_function(hashk, hash_test_function, NULL);
  test_true(rc == HASHKIT_SUCCESS);

  return TEST_SUCCESS;
}


static test_return_t hashkit_get_function_test(hashkit_st *hashk)
{
  for (int algo= int(HASHKIT_HASH_DEFAULT); algo < int(HASHKIT_HASH_MAX); algo++)
  {

    if (HASHKIT_HASH_CUSTOM or HASHKIT_HASH_HSIEH)
      continue;

    hashkit_return_t rc= hashkit_set_function(hashk, static_cast<hashkit_hash_algorithm_t>(algo));
    test_true(rc == HASHKIT_SUCCESS);

    test_true(hashkit_get_function(hashk) == algo);
  }
  return TEST_SUCCESS;
}

static test_return_t hashkit_compare_test(hashkit_st *hashk)
{
  hashkit_st *clone= hashkit_clone(NULL, hashk);

  test_true(hashkit_compare(clone, hashk));
  hashkit_free(clone);

  return TEST_SUCCESS;
}

test_st hashkit_st_functions[] ={
  {"hashkit_digest", 0, (test_callback_fn*)hashkit_digest_test},
  {"hashkit_set_function", 0, (test_callback_fn*)hashkit_set_function_test},
  {"hashkit_set_custom_function", 0, (test_callback_fn*)hashkit_set_custom_function_test},
  {"hashkit_get_function", 0, (test_callback_fn*)hashkit_get_function_test},
  {"hashkit_set_distribution_function", 0, (test_callback_fn*)hashkit_set_distribution_function_test},
  {"hashkit_set_custom_distribution_function", 0, (test_callback_fn*)hashkit_set_custom_distribution_function_test},
  {"hashkit_compare", 0, (test_callback_fn*)hashkit_compare_test},
  {0, 0, 0}
};

static test_return_t libhashkit_digest_test(hashkit_st *hashk)
{

  (void)hashk;

  uint32_t value= libhashkit_digest("a", sizeof("a"), HASHKIT_HASH_DEFAULT);
  test_true(value);

  return TEST_SUCCESS;
}

test_st library_functions[] ={
  {"libhashkit_digest", 0, (test_callback_fn*)libhashkit_digest_test},
  {0, 0, 0}
};

test_st hash_tests[] ={
  {"one_at_a_time", 0, (test_callback_fn*)one_at_a_time_run },
  {"md5", 0, (test_callback_fn*)md5_run },
  {"crc", 0, (test_callback_fn*)crc_run },
  {"fnv1_64", 0, (test_callback_fn*)fnv1_64_run },
  {"fnv1a_64", 0, (test_callback_fn*)fnv1a_64_run },
  {"fnv1_32", 0, (test_callback_fn*)fnv1_32_run },
  {"fnv1a_32", 0, (test_callback_fn*)fnv1a_32_run },
  {"hsieh", 0, (test_callback_fn*)hsieh_run },
  {"murmur", 0, (test_callback_fn*)murmur_run },
  {"jenkis", 0, (test_callback_fn*)jenkins_run },
  {0, 0, (test_callback_fn*)0}
};

/*
 * The following test suite is used to verify that we don't introduce
 * regression bugs. If you want more information about the bug / test,
 * you should look in the bug report at
 *   http://bugs.launchpad.net/libmemcached
 */
test_st regression[]= {
  {0, 0, 0}
};

collection_st collection[] ={
  {"allocation", 0, 0, allocation},
  {"hashkit_st_functions", 0, 0, hashkit_st_functions},
  {"library_functions", 0, 0, library_functions},
  {"hashing", 0, 0, hash_tests},
  {"regression", 0, 0, regression},
  {0, 0, 0, 0}
};

static void *world_create(libtest::server_startup_st&, test_return_t& error)
{
  hashkit_st *hashk_ptr= hashkit_create(&global_hashk);

  if (hashk_ptr != &global_hashk)
  {
    error= TEST_FAILURE;
    return NULL;
  }

  if (hashkit_is_allocated(hashk_ptr) == true)
  {
    error= TEST_FAILURE;
    return NULL;
  }

  return hashk_ptr;
}


static bool world_destroy(void *object)
{
  hashkit_st *hashk= (hashkit_st *)object;
  // Did we get back what we expected?
  test_true(hashkit_is_allocated(hashk) == false);
  hashkit_free(&global_hashk);

  return TEST_SUCCESS;
}

void get_world(Framework *world)
{
  world->collections= collection;
  world->_create= world_create;
  world->_destroy= world_destroy;
}
