/*
echo.go implements a simple TCP echo server that receives from a connection and
writes back to that connection; use 'nc localhost 8080' to connect to the running
server; more advanced features can easily be implemented using the io.ReadWriteCloser
interface and associated methods
*/
package main

import (
	"fmt"
	"io"
	"net"
)

const listenaddr = "127.0.0.1:8080"

func main() {
	l, err := net.Listen("tcp", listenaddr)
	if err != nil {
		fmt.Printf("error while listening on %s: %v\n", listenaddr, err)
	}
	for {
		conn, err := l.Accept()
		if err != nil {
			fmt.Printf("error accepting incoming connection: %v\n", err)
		}
		go copy(conn)
	}
}

func copy(c net.Conn) {
	b, err := io.Copy(c, c)
	if err != nil {
		fmt.Printf("error writing to connection: %v\n", err)
	}
	defer fmt.Printf("wrote %d bytes\n", b)
}
