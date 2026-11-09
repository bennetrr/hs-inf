package acl_package

test_1 if {
        allow with input as { "object": "X", "user": "Alice", "permission": "read"  }
}
test_2 if {
        not allow with input as { "object": "Y", "user": "Bob", "permission": "read"  } 
}
test_3 if {
        not allow with input as { "object": "Z", "user": "Alice", "permission": "append"  }
}
test_4 if {
        allow with input as { "object": "Y", "user": "Bob", "permission": "write"  }
}
test_5 if {
        allow with input as { "object": "X", "user": "Alice", "permission": "execute"  }
}
test_6 if {
        not allow with input as { "object": "Z", "user": "Bob", "permission": "write"  }
}
