add_files(
    address.cpp
    address.h
    config.cpp
    config.h
    core.cpp
    core.h
    game_info.cpp
    game_info.h
    host.cpp
    host.h
    http.h
    os_abstraction.cpp
    os_abstraction.h
    packet.cpp
    packet.h
    tcp.cpp
    tcp.h
    tcp_admin.cpp
    tcp_admin.h
    tcp_connect.cpp
    tcp_content.cpp
    tcp_content.h
    tcp_content_type.h
    tcp_coordinator.cpp
    tcp_coordinator.h
    tcp_game.cpp
    tcp_game.h
    tcp_listen.h
    tcp_stun.cpp
    tcp_stun.h
    tcp_turn.cpp
    tcp_turn.h
    udp.cpp
    udp.h
)

add_files(
    http_curl.cpp
    CONDITION CURL_FOUND
)
add_files(
    http_winhttp.cpp
    CONDITION WIN32
)
add_files(
    http_none.cpp
    CONDITION NOT CURL_FOUND AND NOT WIN32
)
