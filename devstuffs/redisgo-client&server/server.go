package main

import (
    "log"
    "net"
    "github.com/gomodule/redigo/redis"
)

func main() {
    ln, err := net.Listen("tcp", ":6379")
    if err != nil {
        log.Fatalf("Error starting server: %v", err)
    }
    defer ln.Close()

    log.Println("Redis server is running on port 6379")

    for {
        conn, err := ln.Accept()
        if err != nil {
            log.Printf("Error accepting connection: %v", err)
            continue
        }

        go handleConnection(conn)
    }
}

func handleConnection(conn net.Conn) {
    defer conn.Close()
    c := redis.NewConn(conn, 0, 0)

    for {
        msg, err := c.Receive()
        if err != nil {
            log.Printf("Error receiving message: %v", err)
            return
        }

        _, err = c.Send("RESPONSE", msg)
        if err != nil {
            log.Printf("Error sending response: %v", err)
            return
        }
    }
}
