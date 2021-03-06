/*
 * Copyright (c) 2007, OmniTI Computer Consulting, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 * 
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above
 *       copyright notice, this list of conditions and the following
 *       disclaimer in the documentation and/or other materials provided
 *       with the distribution.
 *     * Neither the name OmniTI Computer Consulting, Inc. nor the names
 *       of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written
 *       permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef _NOIT_STRATCON_IEP_H
#define _NOIT_STRATCON_IEP_H

#include "noit_defines.h"
#include "eventer/eventer.h"
#include "utils/noit_hash.h"
#include "stratcon_datastore.h"
#include "stratcon_jlog_streamer.h"

#include <sys/types.h>
#include <sys/socket.h>

API_EXPORT(void)
  stratcon_iep_init();

API_EXPORT(void)
  stratcon_iep_line_processor(stratcon_datastore_op_t op,
                              struct sockaddr *remote, const char *remote_cn,
                              void *operand, eventer_t completion);

API_EXPORT(jlog_streamer_ctx_t *)
  stratcon_jlog_streamer_iep_ctx_alloc(void);

typedef struct iep_thread_driver iep_thread_driver_t;

typedef struct mq_driver {
  iep_thread_driver_t *(*allocate)(noit_conf_section_t);

  int (*connect)(iep_thread_driver_t *driver);
  /* connect returns:
      -1 for failure,
       0 for successful new connection,
       1 for already connected
   */

  int (*submit)(iep_thread_driver_t *driver, const char *payload, size_t payloadlen);
  /* submit returns: 0 on success, -1 on failure */

  int (*disconnect)(iep_thread_driver_t *driver);
  /* disconnect returns:
      -1 for already disconnected
       0 successful discnonect
   */

  void (*deallocate)(iep_thread_driver_t *driver);
} mq_driver_t;

API_EXPORT(void)
  stratcon_iep_mq_driver_register(const char *, mq_driver_t *);

API_EXPORT(int)
  stratcon_iep_get_enabled();

API_EXPORT(void)
  stratcon_iep_set_enabled(int);

#endif
