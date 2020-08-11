/* Copyright (C) 2015-2020, Wazuh Inc.
 * Copyright (C) 2009 Trend Micro Inc.
 * All rights reserved.
 *
 * This program is free software; you can redistribute it
 * and/or modify it under the terms of the GNU General Public
 * License (version 2) as published by the FSF - Free Software
 * Foundation
 */

#include "audit_op_wrappers.h"
#include <stddef.h>
#include <stdarg.h>
#include <setjmp.h>
#include <cmocka.h>


int __wrap_audit_add_rule() {
    return mock();
}

int __wrap_audit_get_rule_list() {
    return mock();
}

int __wrap_audit_restart() {
    return mock();
}

int __wrap_audit_set_db_consistency() {
    return 1;
}

int __wrap_search_audit_rule() {
    return mock();
}

int __wrap_audit_delete_rule(const char *path, const char *key) {
    check_expected(path);
    check_expected(key);

    return mock();
}
