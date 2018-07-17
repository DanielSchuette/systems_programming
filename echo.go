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

const (
	listenaddr = "127.0.0.1:8080"
	maxConn    = 2
)

func main() {
	l, err := net.Listen("tcp", listenaddr)
	if err != nil {
		fmt.Printf("error while listening on %s: %v\n", listenaddr, err)
	}
	queue := make(chan struct{}, maxConn)
	for {
		conn, err := l.Accept()
		select {
		case queue <- struct{}{}:
			if err != nil {
				fmt.Printf("error accepting incoming connection: %v\n", err)
			}
			conn.Write([]byte("connection open, start writing...\n"))
			go copy(conn, queue)
		default:
			conn.Write([]byte("cannot accept more connections, closing...\n"))
			conn.Close()
		}
	}
}

func copy(c net.Conn, q chan struct{}) {
	b, err := io.Copy(c, c)
	if err != nil {
		fmt.Printf("error writing to connection: %v\n", err)
	}
	defer func(q chan struct{}) {
		fmt.Printf("wrote %d bytes and removed goroutine from queue\n", b)
		<-q
	}(q)
}
