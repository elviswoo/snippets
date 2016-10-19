/*
 * select.cc
 *
 *  Created on: 2016年10月19日
 *      Author: elviswu
 */



//connect
//1.socket()
SOCKET sock_fd = socket(...);
if (sock_fd = INVALID_SOCKET)
	return;
//2.设置sock_fd为非阻塞
if (0!=socket_set_nobio(sock_fd))
	return;

int ret = connect(socket_fd, addr...);

if (0!=return && IS_NOBLOCK_CONNECT_ERRNO(socket_errno)) {
	socket_close(sock_fd);
	return;
}
SocketSelectBreaker conn_breaker;
SocketSelect conn_sel(conn_breaker);
conn_sel.PreSelect();
conn_sel.Write_FD_SET(socket_fd);
conn_sel.Exception_FD_SET(socket_fd);

int sel_ret = conn_sel.Select(timeout_conn);

if (sel_ret < 0) {
	//select error
}
if (conn_sel.IsException()) {
	//breakfd exception
}
if (conn_sel.IsBreak()) {
	//user break
}
if (conn_sel.Exception_FD_ISSET(sock_fd)) {
	//sock_fd exception
}

if (conn_sel.Write_FD_ISSET(sock_fd)) {
	int error = 0;
	socklen_t len = sizeof(error);
	if (0 != getsockopt(sock_fd, SOL_SOCKET, SO_ERROR, &error, &len)) {
		error = socket_errno;
	}
	if (0!=error) {
		socket_close(sock_fd);
		return;
	}
	//connect success
}






while (true) {
	//read write
	SocketSelectBreaker rw_breaker;
	SocketSelect sel(rw_breaker);

	sel.PreSelect();
	sel.Read_FD_SET(sock_fd);
	sel.Write_FD_SET(sock_fd);
	sel.Exception_FD_SET(socket_fd);
	sel_ret = sel.Select(timeout_rw);

	if (sel_ret < 0) {
		//select error
	}

	if (sel.IsException()) {
		//breakfd exception
	}

	if (sel.IsBreak()) {
		//usr break
	}

	if (sel.Exception_FD_ISSET(sock_fd)) {
		//sock_fd exception
	}

	if (sel.Write_FD_ISSET(sock_fd)) {
		//打包
		send(...);
	}
	if (sel.Read_FD_ISSET(sock_fd)) {
		recv(...);
		//解包
	}

}

