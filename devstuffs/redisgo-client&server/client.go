package main

import (
    "context"
    "fmt"
    "log"

    "github.com/go-redis/redis/v8"
)

var ctx = context.Background()

func main() {
    rdb := redis.NewClient(&redis.Options{
        Addr: "localhost:6379", 
    })

    _, err := rdb.Ping(ctx).Result()
    if err != nil {
        log.Fatalf("Could not connect to Redis: %v", err)
    }
    fmt.Println("Connected to Redis")

    err = rdb.Set(ctx, "key", "value", 0).Err()
    if err != nil {
        log.Fatalf("Could not set key: %v", err)
    }

    // Get the value of the key
    val, err := rdb.Get(ctx, "key").Result()
    if err != nil {
        log.Fatalf("Could not get key: %v", err)
    }
    fmt.Printf("key: %s\n", val)
}
