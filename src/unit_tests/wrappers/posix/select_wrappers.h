/* Copyright (C) 2015-2020, Wazuh Inc.
 * All rights reserved.
 *
 * This program is free software; you can redistribute it
 * and/or modify it under the terms of the GNU General Public
 * License (version 2) as published by the FSF - Free Software
 * Foundation
 */


#ifndef SELECT_WRAPPERS_H
#define SELECT_WRAPPERS_H

#include <sys/time.h>
#include <sys/select.h>

int __wrap_select(int nfds,
                  fd_set *restrict readfds,
                  fd_set *restrict writefds,
                  fd_set *restrict errorfds,
                  struct timeval *restrict timeout);

#endif
