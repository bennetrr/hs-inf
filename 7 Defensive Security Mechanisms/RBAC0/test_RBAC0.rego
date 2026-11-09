package rbac0_package

test_1 if {
        allow with input as { "user": "Alice", "permission": "READ_SOURCE_CODE"  }
}
test_2 if {
        not allow with input as { "user": "Alice", "permission": "WRITE_SOURCE_CODE"  }
}
test_3 if {
        allow with input as { "user": "Alice", "permission": "DEPLOY_APPLICATION"  }
}
test_4 if {
        allow with input as { "user": "Bob", "permission": "READ_SOURCE_CODE"  }
}
test_5 if {
        allow with input as { "user": "Bob", "permission": "WRITE_SOURCE_CODE"  }
}
test_6 if {
        not allow with input as { "user": "Bob", "permission": "DEPLOY_APPLICATION"  }
}
test_7 if {
        allow with input as { "user": "Carol", "permission": "READ_EMPLOYEE_DATA"  }
}
test_8 if {
        not allow with input as { "user": "Carol", "permission": "READ_SOURCE_CODE"  }
}
test_9 if {
        allow with input as { "user": "Dave", "permission": "RESET_PASSWORD"  }
}
test_10 if {
        not allow with input as { "user": "Dave", "permission": "READ_EMPLOYEE_DATA"  }
}
test_11 if {
        allow with input as { "user": "Emma", "permission": "WRITE_SOURCE_CODE"  }
}
test_12 if {
        not allow with input as { "user": "Emma", "permission": "CLOSE_TICKETS"  }
}
