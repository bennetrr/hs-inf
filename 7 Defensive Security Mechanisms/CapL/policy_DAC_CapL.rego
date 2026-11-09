package capl_package

default allow := false

allow if {

        some permission in data.CapLUsers[input.user][input.object]
        permission == input.permission
}
