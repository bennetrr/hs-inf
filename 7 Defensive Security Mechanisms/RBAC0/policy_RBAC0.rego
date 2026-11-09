package rbac0_package

default allow := false

allow if {

        some role in data.user_roles[input.user]
        some permission in data.role_permissions[role]
        permission == input.permission
}
