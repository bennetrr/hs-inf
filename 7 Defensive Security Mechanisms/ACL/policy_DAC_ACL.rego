package acl_package

default allow := false

allow if {

        some permission in data.ACLObjects[input.object][input.user]
        permission == input.permission
}
